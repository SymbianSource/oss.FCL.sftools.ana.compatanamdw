/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description: 
*
*/
// DrmPreconfig.cpp
//
// Created: 10/16/08
// Author:  
// Copyright (c) . All rights reserved.
//

#include "CommonFramework.h"
#include <s32file.h>
#include <stdio.h>
#include <string.h>
#include <UTF.H>
#include <tzconverter.h>
#include <tz.h>
#include <e32base.h>


//Domain API
#include <DRMMessageParser.h>
#include <dcfrep.h>
#include <dcfentry.h>

//SDK API
#include <Oma1DcfCreator.h>

//USER Headers
#include "DRMClockClient.h"
#include "DrmPreconfig.h"

#include <e32debug.h>


const TInt KBufferSize = 20000;
_LIT(KDRMLogFileName, "c:\\logs\\TestFramework\\DRM\\DRM_Preconfig.txt");


LOCAL_C void DrmPreconfigL()
    {
    
	RFs iFs;

	TBuf8<100> bufLogMessage;
 	RFile drmLogFile;
	TUint ret;
	
   	TUint aEncryptedCount = 0;
    TUint aRightsCount = 0;
    TUint aMessagesProcessed = 0;
 	
	User::LeaveIfError(iFs.Connect());
	CleanupClosePushL(iFs);
	iFs.MkDirAll(_L("c:\\logs\\TestFramework\\DRM\\"));
	drmLogFile.Replace(iFs, KDRMLogFileName, EFileShareAny|EFileWrite);
	
	
	
	drmLogFile.Write(_L8("PreConfig file of DRM Settings application\n"));
    
	_LIT(KDRMPreconfigMessage,"Running Drm Helper API BC Driver Preconfiguration!\n");
	console->Printf(KDRMPreconfigMessage);
	
	ret = EncryptL(aEncryptedCount, aRightsCount, aMessagesProcessed);
	if(ret>=0)
	{
		_LIT(KDRMROMessage, "%d Rights Objects Encrypted\n");
		TBuf<100> tmpBufMessage;
		tmpBufMessage.Format(KDRMROMessage, ret);
		bufLogMessage.Copy(tmpBufMessage);
		drmLogFile.Write(_L8("preconfig result : passed\n"));

	}
	else
	{
		_LIT8(KDRMROMessage, "Error in Rights Objects Encryption\n");
		bufLogMessage.Copy(KDRMROMessage);
		drmLogFile.Write(_L8("preconfig result : failed\n"));

	}
	


	SetDrmClockL(drmLogFile);
	
	drmLogFile.Close();
	CleanupStack::Pop();
	iFs.Close();
	
	}


TUint EncryptL(TUint& aEncryptedCount, TUint& aRightsCount, TUint& aMessagesProcessed)
    {
    TInt i;
    CDir* files;
    TFileName input;
    TFileName output;
    TUint inputNameSize = 0;
    TUint outputNameSize = 0;
    RFs fs;
    User::LeaveIfError(fs.Connect());
    TInt aMultiplier(1);


#ifdef __WINS__
    input.Append(_L("c:\\data\\DRM\\"));
    output.Append(_L("c:\\data\\Others\\"));
#else
    input.Append(_L("e:\\DRM\\"));
    output.Append(_L("e:\\Others\\"));
#endif

    inputNameSize = input.Length();
    outputNameSize = output.Length();

     
    fs.MkDir(input);
    fs.MkDir(output);

    fs.GetDir(input, KEntryAttNormal, ESortNone, files);
    for (i = 0; i < files->Count(); i++)
        {
        input.Append((*files)[i].iName);

        output.Append((*files)[i].iName);

        if (input.Right(2).CompareF(_L("dm")) == 0)
            {

            for(TInt ii = 0; ii < aMultiplier ; ++ii)
                {
                output.Delete(outputNameSize +(*files)[i].iName.Length() , output.Length()-1);
                output.Append(_L("-"));
                output.AppendNum(ii);
                output.Append(_L(".dcf"));
                ProcessMessageL(input, output);
                ++aMessagesProcessed;
                }
            }
        else if (input.Right(3).CompareF(_L("oro")) == 0 ||
                input.Right(3).CompareF(_L("drc")) == 0 ||
                input.Right(2).CompareF(_L("ro")) == 0 ||
                input.Right(2).CompareF(_L("dr")) == 0 )
            {
            for (TInt iii = 0; iii < aMultiplier; ++iii)
                {
                ProcessRightsL(input);
                ++aRightsCount;
                }
            }
        else if (input.Right(3).CompareF(_L("dcf")) != 0)
            {
            output.Append(_L(".dcf"));
__UHEAP_MARK;
            EncryptFileL(input, output, aMultiplier);
__UHEAP_MARKEND;
            ++aEncryptedCount;
            }

        //restore paths
        input.Delete(inputNameSize, input.Length()-1);
        output.Delete(outputNameSize, output.Length()-1);
        }

    fs.Close();
    delete files;

    return (aEncryptedCount*aMultiplier + aRightsCount + aMessagesProcessed);
    }
    
    
 
 TUint SetDrmClockL(RFile &aDRMLogFile)
    {
    RDRMClockClient client;
	TTime utcTime;
	RTz tzServer;

    TInt aTimeZone;
    TTime drmTime;

	TBuf<100> bufferTmp;
	TBuf8<100> bufferDRMTime;


    DRMClock::ESecurityLevel secLevel = DRMClock::KInsecure;


	utcTime.UniversalTime();

	User::LeaveIfError(tzServer.Connect());
	CleanupClosePushL(tzServer);
	
	CActiveScheduler * timeActiveScheduler = new CActiveScheduler();
	CleanupStack::PushL(timeActiveScheduler);
	
	CActiveScheduler::Install(timeActiveScheduler);
		
	CTzConverter *tzConverter = CTzConverter::NewL(tzServer);
	CleanupStack::PushL(tzConverter);

	tzConverter->ConvertToLocalTime(utcTime);

    User::LeaveIfError(client.Connect());
    CleanupClosePushL(client);

    client.GetSecureTime(drmTime, aTimeZone, secLevel);

        TUint ret = client.UpdateSecureTime(utcTime, aTimeZone);
        
        if(ret>0)
        {
			_LIT(KFormatTxt, "%1%2%3:%H%T%S");
			_LIT8(KDRMTime, "DRM Time Set To : ");
			utcTime.FormatL(bufferTmp, KFormatTxt);
			
			bufferDRMTime.Copy(bufferTmp);
			
			aDRMLogFile.Write(KDRMTime);
			aDRMLogFile.Write(bufferDRMTime);
        	
        }
        
    CleanupStack::Pop();
    CleanupStack::PopAndDestroy(tzConverter);
	CleanupStack::PopAndDestroy(timeActiveScheduler);
    CleanupStack::Pop();

    client.Close();
	tzServer.Close();

    return ret;
    }
 
 
 void ProcessMessageL(const TDesC& aFile, const TDesC& aOutput)
    {
    CDRMMessageParser* c = NULL;
    HBufC8* d = NULL;
    RFs fs;
    TPtr8 inRead(NULL, 0);
    TInt error = 1;
    __UHEAP_MARK;

    User::LeaveIfError(fs.Connect());
    CleanupClosePushL(fs);
    c = CDRMMessageParser::NewL();
    CleanupStack::PushL(c);

    d = HBufC8::NewLC( KBufferSize );

    RFile input;
    User::LeaveIfError(input.Open( fs, aFile, EFileRead ));
    CleanupClosePushL( input );

    RFileWriteStream output;
    output.Replace( fs, aOutput, EFileWrite );
    CleanupClosePushL( output );

    c->InitializeMessageParserL( output );

    while( error )
        {
        inRead.Set( const_cast<TUint8*>(d->Ptr()),0,KBufferSize);
        error = input.Read( inRead );

        if( error )
            {
            c->FinalizeMessageParserL();

            User::Leave( error );
            }
        else
            {
            error = inRead.Length();
            }

        if( error )
            {
            c->ProcessMessageDataL(inRead);
            }
        }

    c->FinalizeMessageParserL();


    CleanupStack::PopAndDestroy( 5 ); // fs, c, d, input, output
    UpdateDCFRepositoryL( aOutput );
    __UHEAP_MARKEND;
    }   
    
  void ProcessRightsL(const TDesC& aFile)
    {
    CDRMMessageParser* c = NULL;
    HBufC8* d = NULL;
    RFs fs;
    RPointerArray<CDRMRights> rights;

    User::LeaveIfError(fs.Connect());
    c = CDRMMessageParser::NewL();
    ReadFileL(d, aFile, fs);
    c->ProcessRightsObject(*d, rights);
    rights.ResetAndDestroy();
    delete d;
    delete c;
    fs.Close();
    }
  
void EncryptFileL(const TDesC& aFile, TDesC& aOutput, TInt aMultiplier)
    {
    COma1DcfCreator* c = NULL;
    CDRMRights* rights = NULL;
    TBuf8<64> mime;
    RFs fs;
    TFileName aDcfFile;
    TInt aOriginalFileNameLength(aOutput.Length() - 4);
RDebug::Print( _L("Vaibhav 1.") );

    User::LeaveIfError(fs.Connect());
    if (aFile.Right(3).CompareF(_L("amr")) == 0) //AMR
        {
        mime.Copy(_L8("audio/amr"));
        }
    else if (aFile.Right(3).CompareF(_L("awb")) == 0) //AMR-AWB
        {
        mime.Copy(_L8("audio/amr-wb"));
        }
    else if (aFile.Right(3).CompareF(_L("mp3")) == 0) //MP3
        {
        mime.Copy(_L8("audio/mpeg"));
        }
    else if (aFile.Right(3).CompareF(_L("mp4")) == 0) //MP4
        {
        mime.Copy(_L8("audio/mp4"));
        }
    else if (aFile.Right(3).CompareF(_L("m4a")) == 0) //M4A
        {
        mime.Copy(_L8("audio/mp4"));
        }
    else if (aFile.Right(3).CompareF(_L("3gp")) == 0) //3GPP
        {
        mime.Copy(_L8("audio/3gpp"));
        }
    else if (aFile.Right(3).CompareF(_L("3g2")) == 0) //3GPP2
        {
        mime.Copy(_L8("audio/3gpp2"));
        }
    else if (aFile.Right(3).CompareF(_L("qcp")) == 0) //QCELP
        {
        mime.Copy(_L8("audio/qcelp"));
        }
    else if (aFile.Right(3).CompareF(_L("aac")) == 0) //AAC
        {
        mime.Copy(_L8("audio/aac"));
        }
    else if (aFile.Right(3).CompareF(_L("mid")) == 0) //MIDI
        {
        mime.Copy(_L8("audio/midi"));
        }
    else if (aFile.Right(5).CompareF(_L(".spmid")) == 0) //SP-MIDI
        {
        mime.Copy(_L8("audio/sp-midi"));
        }
    else if (aFile.Right(3).CompareF(_L("rmf")) == 0) //RMF
        {
        mime.Copy(_L8("audio/rmf"));
        }
    else if (aFile.Right(4).CompareF(_L("mxmf")) == 0) //Mobile-XMF
        {
        mime.Copy(_L8("audio/mobile-xmf"));
        }
    else if (aFile.Right(3).CompareF(_L("wav")) == 0) //WAV
        {
        mime.Copy(_L8("audio/x-wav"));
        }
    else if (aFile.Right(3).CompareF(_L("gif")) == 0) // GIF
        {
        mime.Copy(_L8("image/gif"));
        }
    else if (aFile.Right(3).CompareF(_L("jpg")) == 0) // JPEG
        {
        mime.Copy(_L8("image/jpeg"));
        }
    else if (aFile.Right(3).CompareF(_L("txt")) == 0)
        {
        mime.Copy(_L8("text/plain"));
        }
    else if (aFile.Right(3).CompareF(_L("pip")) == 0)
        {
        mime.Copy(_L8("application/x-pip"));
        }

    aDcfFile.Append(aOutput);

    for(TInt i = 0; i < aMultiplier ; ++i)
        {
        aDcfFile.Delete(aOriginalFileNameLength, aDcfFile.Length());
        aDcfFile.Append(_L("-"));
        aDcfFile.AppendNum(i);
        aDcfFile.Append(_L(".dcf"));
        c = COma1DcfCreator::NewL();
        CleanupStack::PushL(c);
        fs.Delete(aOutput);
        c->EncryptFileL(aFile, aDcfFile, mime, rights);
        UpdateDCFRepositoryL( aDcfFile );
        delete rights;
        CleanupStack::PopAndDestroy(); // c
        }
    fs.Close();

    }    
    
    
    
 // ---------------------------------------------------------
// UpdateDCFRepositoryL()
// Update saved file to DCFRepository
// ---------------------------------------------------------
//
LOCAL_C void UpdateDCFRepositoryL( const TDesC& aFileName)
    {
    CDcfEntry* dcf( NULL );
    CDcfRep* dcfRep( NULL );

    dcf = CDcfEntry::NewL();
    CleanupStack::PushL( dcf );

    dcfRep = CDcfRep::NewL();
    CleanupStack::PushL( dcfRep );

    dcf->SetLocationL( aFileName, 0 );
    dcfRep->UpdateL( dcf );

    CleanupStack::PopAndDestroy(2); // dcf, dcfRep
    }

 
 LOCAL_C void ReadFileL(HBufC8*& aContent, const TDesC& aName, RFs& aFs)
    {
    TInt size = 0;
    RFile file;
    User::LeaveIfError(file.Open(aFs, aName, EFileRead));
    User::LeaveIfError(file.Size(size));
    aContent = HBufC8::NewLC(size);
    TPtr8 ptr(aContent->Des());
    User::LeaveIfError(file.Read(ptr, size));
    CleanupStack::Pop(); //aContent
    }
  
