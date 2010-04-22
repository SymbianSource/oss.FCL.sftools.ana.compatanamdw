/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:      ?Description
*
*/

// INCLUDE FILES
#include <apmrec.h>
#include <apgcli.h>
#include <eikappui.h>
#include <eikenv.h>
#include <eikbtgpc.h>
#include "BrCtlBCTestObserver.h"
#include <avkon.hrh>
#include <aknmessagequerydialog.h>

#ifndef RD_PF_SEC_APPARC
//#include <genericparam.h>  
#else
#include "AiwGenericParam.h"
#endif


// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CBrCtlBCTestObserver::UpdateBrowserVScrollBarL
// ---------------------------------------------------------
//
void CBrCtlBCTestObserver::UpdateBrowserVScrollBarL(TInt aDocumentHeight, 
                                      TInt aDisplayHeight,
                                      TInt aDisplayPosY ) 
    {
    _LIT(KUpdateScrollbar, "Document height = %d, Display height = %d, Display pos = %d");
    if (iCanLog)
        {
        iFileLogger.WriteFormat(KUpdateScrollbar, aDocumentHeight, aDisplayHeight, aDisplayPosY);
        }
    }

// ---------------------------------------------------------
// CBrCtlBCTestObserver::UpdateBrowserHScrollBarL
// ---------------------------------------------------------
//
void CBrCtlBCTestObserver::UpdateBrowserHScrollBarL(TInt aDocumentWidth, 
                                      TInt aDisplayWidth,
                                      TInt aDisplayPosX ) 
    {
    _LIT(KUpdateScrollbar, "Document width = %d, Display width = %d, Display pos = %d");
    if (iCanLog)
        {
        iFileLogger.WriteFormat(KUpdateScrollbar, aDocumentWidth, aDisplayWidth, aDisplayPosX);
        }
    }

// ---------------------------------------------------------
// CBrCtlBCTestObserver::NotifyLayoutChange
// ---------------------------------------------------------
//
void CBrCtlBCTestObserver::NotifyLayoutChange( TBrCtlLayout aNewLayout ) 
    {
    _LIT(KUpdateLayout, "New layout is  %d");
    if (iCanLog)
        {
        iFileLogger.WriteFormat(KUpdateLayout, aNewLayout);
        }
    }

// ---------------------------------------------------------
// CBrCtlSampleAppLayoutObserver::UpdateTitle
// ---------------------------------------------------------
//
void CBrCtlBCTestObserver::UpdateTitleL( const TDesC& /*aTitle*/ )
    {
    }

// ---------------------------------------------------------
// CBrCtlBCTestObserver::UpdateSoftkeyL
// ---------------------------------------------------------
//
void CBrCtlBCTestObserver::UpdateSoftkeyL(TBrCtlKeySoftkey aKeySoftkey,
                            const TDesC& aLabel,
                            TUint32 aCommandId,
                            TBrCtlSoftkeyChangeReason /* aBrCtlSoftkeyChangeReason */) 
    {
    _LIT(KUpdateSoftkey, "Update softkey %d with label :%s: command id %d, reason %d");
        
    return;
    CEikButtonGroupContainer* current = CEikButtonGroupContainer::Current();
    switch (aKeySoftkey)
        {
        case EKeyLeft:
            current->SetCommandL(0, aCommandId, aLabel);
            break;

        case EKeyRight:
            current->SetCommandL(1, aCommandId, aLabel);
            break;
        }
    }

// ---------------------------------------------------------
// CBrCtlBCTestObserver::NetworkConnectionNeededL
// ---------------------------------------------------------
//
void CBrCtlBCTestObserver::NetworkConnectionNeededL(TInt* /*aConnectionPtr*/,
                                      TInt* /*aSockSvrHandle*/,
                                      TBool* /*aNewConn*/,
                                      TApBearerType* /*aBearerType*/) 
    {
    _LIT(KNetworkConnectionNeeded, "Network connection needed");
        
    if (iCanLog)
        {
        iFileLogger.WriteFormat(KNetworkConnectionNeeded);
        }
    }

// ---------------------------------------------------------
// CBrCtlBCTestObserver::HandleRequestL
// ---------------------------------------------------------
//
TBool CBrCtlBCTestObserver::HandleRequestL(RArray<TUint>* aTypeArray, CDesCArrayFlat* aDesArray) 
    {

    TInt i;
    _LIT(KHandleRequest, "HandleRequest url name :%s:");
	
    // The 2 arrays must be in sync. Each element in iTypeArray 
    // identifies the type of the corresponding element in iDesArray.
    if( aTypeArray->Count() != aDesArray->Count() )
        {
        User::Leave( KErrArgument );
        }

	// get url
    HBufC* url = NULL;
    // Serach url in the param list
    for(i = 0; i < aTypeArray->Count(); i++)
        {
        if( (*aTypeArray)[i] == EParamRequestUrl )
            {
            // the url is found
            url = HBufC::NewLC( (*aDesArray)[i].Length() );
            url->Des().Copy( (*aDesArray)[i] );
            break;
            }
        }
    if( !url )
        {
        // The url wasn't found. 
        User::Leave( KErrArgument );
        }

	// get referrer header
    HBufC* refererHeader = NULL;
    // Serach url in the param list
    for( i = 0; i < aTypeArray->Count(); i++ )
        {
        if( (*aTypeArray)[i] == EParamRefererHeader )
            {
            // the referer Header is found
            refererHeader = HBufC::NewLC( (*aDesArray)[i].Length() );
            refererHeader->Des().Copy( (*aDesArray)[i] );
            break;
            }
        }

    if( refererHeader )
		{
			CleanupStack::PopAndDestroy( 1 ); // refererHeader
		}

    CleanupStack::PopAndDestroy( 1 ); // url

    return ETrue;
    }

// ---------------------------------------------------------
// CBrCtlBCTestObserver::HandleDownloadL
// ---------------------------------------------------------
//
TBool CBrCtlBCTestObserver::HandleDownloadL(RArray<TUint>* aTypeArray, CDesCArrayFlat* aDesArray)
    {
    TInt i = 0;
    TInt count = aTypeArray->Count();
    for (i = 0; i < count; i++)
        {
        if ((*aTypeArray)[i] == EParamLocalFileName && aDesArray[i].Length() > 0)
            {
            TInt j = 0;
            for (j = 0; j < count; j++)
                {
                if ((*aTypeArray)[j] == EParamReceivedContentType)
                    {
                    HBufC8* dataType8 = HBufC8::NewLC((*aDesArray)[j].Length());
                    dataType8->Des().Copy((*aDesArray)[j]);
                    TDataType dataType(*dataType8);
                    iHandler->OpenFileEmbeddedL((*aDesArray)[i], dataType);
                    CleanupStack::PopAndDestroy();
                    break;
                    }
                }
            break;
            }
        }
    return EFalse;
    }

// ---------------------------------------------------------
// CBrCtlBCTestObserver::HandleBrowserLoadEventL
// ---------------------------------------------------------
//
void CBrCtlBCTestObserver::HandleBrowserLoadEventL(TBrCtlDefs::TBrCtlLoadEvent aLoadEvent,
                                                 TUint aSize, TUint16 aTransactionId) 
    {
    _LIT(KHandleBrowserLoadEvent, "Handle load event, event = %d, size = %d, trId = %d");
        
    if (iCanLog)
        {
        iFileLogger.WriteFormat(KHandleBrowserLoadEvent, aLoadEvent, aSize, aTransactionId);
        }
    }

// ---------------------------------------------------------
// CBrCtlBCTestObserver::ResolveEmbeddedLinkL
// ---------------------------------------------------------
//
TBool CBrCtlBCTestObserver::ResolveEmbeddedLinkL(const TDesC& aEmbeddedUrl,
    		                       const TDesC& /* aCurrentUrl */,
        	                       TBrCtlLoadContentType /* aLoadContentType */, 
                                   MBrCtlLinkContent& aEmbeddedLinkContent) 
    {
    _LIT(KResolveEmbeddedLink, "Resolve embedded link  aEmbeddedUrl = :%s:, aCurrentUrl = :%s:, aLoadContentType = %d");
        
    if (iCanLog)
        {
//        iFileLogger.WriteFormat(KResolveEmbeddedLink, aEmbeddedUrl, aCurrentUrl, aLoadContentType);
        }
    if (IsFileScheme(aEmbeddedUrl))
        {
        GetFileNameL(aEmbeddedUrl);
        HBufC8* buf = ReadFileLC(*iFileName);
        HBufC* contentType = NULL;
        TPtrC p(NULL, 0);
        contentType = RecognizeLC(*iFileName, *buf);
        aEmbeddedLinkContent.HandleResolveComplete(*contentType, p, buf);        
        CleanupStack::PopAndDestroy(2); // contentType, buf
        return ETrue;
        }
    return EFalse;
    }

// ---------------------------------------------------------
// CBrCtlBCTestObserver::ResolveLinkL
// ---------------------------------------------------------
//
TBool CBrCtlBCTestObserver::ResolveLinkL(const TDesC& aUrl, const TDesC& /* aCurrentUrl */,
                   MBrCtlLinkContent& aBrCtlLinkContent) 
    {
    _LIT(KResolveLink, "Resolve embedded link  aUrl = :%s:, aCurrentUrl = :%s:");
        
    if (iCanLog)
        {
//        iFileLogger.WriteFormat(KResolveLink, aUrl, aCurrentUrl);
        }



    if (IsFileScheme(aUrl))
        {
        GetFileNameL(aUrl);
        HBufC8* buf = ReadFileLC(*iFileName);
        HBufC* contentType = NULL;
        TPtrC p(NULL, 0);
        contentType = RecognizeLC(*iFileName, *buf);
        aBrCtlLinkContent.HandleResolveComplete(*contentType, p, buf);        
        CleanupStack::PopAndDestroy(2); // contentType, buf
        return ETrue;
        }
    return EFalse;
    }


// ---------------------------------------------------------
// CBrCtlBCTestObserver::CancelAll
// ---------------------------------------------------------
//
void CBrCtlBCTestObserver::CancelAll() 
    {
    _LIT(KCancelAll, "All requests canceled");
        
    if (iCanLog)
        {
        iFileLogger.WriteFormat(KCancelAll);
        }
    }


// ---------------------------------------------------------
// CBrCtlBCTestObserver::ConstructL
// ---------------------------------------------------------
//
void CBrCtlBCTestObserver::ConstructL()
    {
    _LIT(KDir, "BrCtlBCTest");
    _LIT(KFile, "BrCtl.log");
    TInt err = 0;
    
    err = iFileLogger.Connect();
    if (err == KErrNone)
        {
        iFileLogger.CreateLog(KDir(), KFile(), EFileLoggingModeOverwrite);
        iCanLog = ETrue;
        }
    iHandler = CDocumentHandler::NewL(CEikonEnv::Static()->Process()) ;
    }

// ---------------------------------------------------------
// CBrCtlBCTestObserver::~CBrCtlBCTestObserver
// ---------------------------------------------------------
//
CBrCtlBCTestObserver::~CBrCtlBCTestObserver()
    {
    if (iCanLog)
        {
        iFileLogger.CloseLog();
        iFileLogger.Close();
        }
    delete iFileName;
    delete iHandler;
    }


// ---------------------------------------------------------
// CBrCtlBCTestObserver::NewL
// ---------------------------------------------------------
//
CBrCtlBCTestObserver* CBrCtlBCTestObserver::NewL()
{
  CBrCtlBCTestObserver* self = new(ELeave)CBrCtlBCTestObserver;
  CleanupStack::PushL(self);
  self->ConstructL();
  CleanupStack::Pop();
  return self;
}

// ---------------------------------------------------------
// CBrCtlBCTestObserver::IsFileScheme
// ---------------------------------------------------------
//

TBool CBrCtlBCTestObserver::IsFileScheme(const TDesC& aFileName)
    {
    _LIT(KFileScheme, "file://");
    if (aFileName.Length() > 0 && aFileName.Ptr() != NULL)
        {
        if (aFileName.FindF(KFileScheme) == 0)
            {
            return ETrue;
            }
        }
    return EFalse;
    }

// ---------------------------------------------------------
// CBrCtlBCTestObserver::ReadFile
// ---------------------------------------------------------
//
HBufC8* CBrCtlBCTestObserver::ReadFileLC(const TDesC& aFileName)
    {
    RFs rfs;
    RFile file;
    User::LeaveIfError(rfs.Connect());
    CleanupClosePushL(rfs);
    User::LeaveIfError(file.Open(rfs, aFileName, EFileRead));
    CleanupClosePushL(file);
    TInt size;
    User::LeaveIfError(file.Size(size));
    HBufC8* buf = HBufC8::NewLC(size);
    TPtr8 bufPtr(buf->Des());
    User::LeaveIfError(file.Read(bufPtr));
    CleanupStack::Pop(); // buf
    CleanupStack::PopAndDestroy(2); // file, rfs
    CleanupStack::PushL(buf);
    return buf;
    }

// ---------------------------------------------------------
// CBrCtlBCTestObserver::RecognizeL
// ---------------------------------------------------------
//
HBufC* CBrCtlBCTestObserver::RecognizeLC(const TDesC& aFileName, const TDesC8& aData)
    {
    TDataRecognitionResult dataType;
    RApaLsSession apaSession;
    TInt ret;
    HBufC* contentTypeString = NULL;

    User::LeaveIfError(apaSession.Connect());
    // Ask the application architecture to find the file type
    ret = apaSession.RecognizeData(aFileName, aData, dataType);
    apaSession.Close();

    if (ret == KErrNone &&
        (dataType.iConfidence == CApaDataRecognizerType::ECertain) ||
        (dataType.iConfidence == CApaDataRecognizerType::EProbable))
        {
        // If the file type was found, try to match it to a known file type
        TPtrC8 mimeTypePtr = dataType.iDataType.Des8();
        TInt len = mimeTypePtr.Length() + 1;
        contentTypeString = HBufC::NewL(len); 
        contentTypeString->Des().Copy(mimeTypePtr);
        contentTypeString->Des().ZeroTerminate();
        }
    CleanupStack::PushL(contentTypeString);
    return contentTypeString;
    }

// -----------------------------------------------------------------------------
// CBrCtlBCTestObserver::GetFileNameL
// Translate the file name from a URL to a valid file name in the system.
// -----------------------------------------------------------------------------
//
TBool CBrCtlBCTestObserver::GetFileNameL(const TDesC& aFileName)
    {
    // This function accepts URLs in the following format:
    // file://filename.xxx
    // file:///filename.xxx
    // file://c:/filename.xxx
    // file:///c:/filename.xxx
    //
    _LIT(KFileScheme, "file://");
    _LIT(KDefaultDrivePath, "C:\\");
    _LIT(KPathChar, "\\");
    
    TInt count;
    TInt index = 0;
    TBool drvLetter = EFalse;
    TUint16 c;
    
    // Verify the file scheme
    TPtrC urlPtr(aFileName);
    if (urlPtr.FindF(KFileScheme) != 0)
        {
        return EFalse;
        }
    urlPtr.Set(urlPtr.Mid(KFileScheme().Length()));
    
    // make sure there are enough characters in the filename before
    // trying to check them
    count = urlPtr.Length();
    if(count == 0)
        {
        return EFalse;            // no filename, so can't look at urlPtr[0]
        }
    
    // Skip the first '/' if there is one
    if (urlPtr[0] == '/')
        {
        urlPtr.Set(urlPtr.Mid(1));
        }
    count = urlPtr.Length();
    
    // Is there a drive letter?
    if(count > 1)
        {
        // can check for drive letter
        if (urlPtr[1 + index] == ':')
            {
            drvLetter = ETrue;
            }
        }
    if(drvLetter == EFalse)
        {
        // 3 additional characters for the string "c:\"
        count = urlPtr.Length() + 3;
        }
    iFileName = HBufC::NewL(count);
    if (!drvLetter)
        {
        iFileName->Des().Append(KDefaultDrivePath);
        }
    
    TBool fragment(EFalse);
    // Convert relative path containing /./ and /../ to absolute path
    for (; index < urlPtr.Length() && !fragment; index ++)
        {
        switch(urlPtr[index])
            {
            case '#':    //Check if there is a fragment '#'
                {
                fragment = ETrue;
                continue; // Just stop there
                }
                
            case '/':
                {
                iFileName->Des().Append(KPathChar);
                break;
                }
            case '.':
                {
                if (index > 1 && urlPtr[index - 1] == '/')
                    {
                    if (index < count - 1 && urlPtr[index + 1] == '/')
                        {
                        index ++; // skip  ./
                        break;
                        }
                    if (index > 2 && index < count - 3 &&
                        urlPtr[index + 1] == '.' && urlPtr[index + 2] == '/')
                        {
                        TInt i = index - 2;
                        
                        for (; i > 0 && urlPtr[i] != '/'; i--) {} // skip  /../
                        
                        iFileName->Des().SetLength(iFileName->Des().Length() - (index - i));
                        index += 2;
                        break;
                        }
                    }
                }
                // no break
                //lint -fallthrough
                
            default:
                {
                c = urlPtr[index];
                iFileName->Des().Append(&c, 1);
                break;
                }
            }	// end of switch
        }
    return ETrue;
}

// ---------------------------------------------------------
// CBrCtlBCTestObserver::NewDownloadL
// ---------------------------------------------------------
//
TBool CBrCtlBCTestObserver::NewDownloadL(TUint /* aTransactionID */,
									   const TDesC& /* aFileName */,
									   const TDesC& /* aContentType */,
									   const TDesC& /* aUrl */)
{
	_LIT(KNewDownload1L, "New Download with Trans ID %d, Local filename :%s:");
	_LIT(KNewDownload2L, "New Download with Trans ID %d, Content Type :%s:");
	_LIT(KNewDownload3L, "New Download with Trans ID %d, URL :%s:");
        
    if (iCanLog)
        {
//        iFileLogger.WriteFormat(KNewDownload1L, aTransactionID, aFileName.Ptr());
//		iFileLogger.WriteFormat(KNewDownload2L, aTransactionID, aContentType.Ptr());
//		iFileLogger.WriteFormat(KNewDownload3L, aTransactionID, aUrl.Ptr());
        }
	return ETrue;
}

void CBrCtlBCTestObserver::ResumeDownloadL(TUint /* aTransactionID */,
                                         TUint /* aLength */,
									   const TDesC& /* aFileName */,
									   const TDesC& /* aContentType */,
									   const TDesC& /* aUrl */)
{
	_LIT(KNewDownload1L, "New Download with Trans ID %d, Local filename :%s:");
	_LIT(KNewDownload2L, "New Download with Trans ID %d, Content Type :%s:");
	_LIT(KNewDownload3L, "New Download with Trans ID %d, URL :%s:");
        
    if (iCanLog)
        {
//        iFileLogger.WriteFormat(KNewDownload1L, aTransactionID, aFileName.Ptr());
//		iFileLogger.WriteFormat(KNewDownload2L, aTransactionID, aContentType.Ptr());
//		iFileLogger.WriteFormat(KNewDownload3L, aTransactionID, aUrl.Ptr());
        }
}

void CBrCtlBCTestObserver::HandleDownloadEventL(TUint aTransactionID, 
											  TBrCtlDownloadEvent aDownloadEvent,
											  TUint aValue)
{
    _LIT(KDownloadEvent, "Download Event with Trans ID %d, Event %d, Value %d");
        
    if (iCanLog)
        {
        iFileLogger.WriteFormat(KDownloadEvent, aTransactionID, aDownloadEvent, aValue);
        }
}
// End of File  
