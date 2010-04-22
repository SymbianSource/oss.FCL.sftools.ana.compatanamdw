/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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


// This contains CT_DataSIPRSeqHeader

#include "t_csiprseqheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

/*@{*/
//Commands
_LIT(KCmdNewL,					"CSIPRSeqHeader");
_LIT(KCmdDecodeL,               "DecodeL");
_LIT(KCmdInternalizeValueL,     "InternalizeValueL");
_LIT(KCmdDestructor,            "~");
//Fields
_LIT(KFldInterval,              "interval");
_LIT(KFldFileName,              "filename");
_LIT(KFldValue,                 "Value");
//Logs
_LIT(KLogError,                 "Error=%d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");

/*}@*/


CT_DataSIPRSeqHeader*  CT_DataSIPRSeqHeader::NewL()
    {
    CT_DataSIPRSeqHeader* self = new (ELeave) CT_DataSIPRSeqHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPRSeqHeader::~CT_DataSIPRSeqHeader()
    {
    DestroyData();
    }

CT_DataSIPRSeqHeader::CT_DataSIPRSeqHeader()
:   CT_DataSIPUnsignedIntHeaderBase(), iSIPRSeqHeader(NULL), iIsOwner(ETrue)
	{
	}

void CT_DataSIPRSeqHeader::ConstructL()
    {
    }

TAny* CT_DataSIPRSeqHeader::GetObject()
    {
    return iSIPRSeqHeader;
    }

void CT_DataSIPRSeqHeader::SetObjectL(TAny* aAny)
    {
    iSIPRSeqHeader = static_cast<CSIPRSeqHeader*>(aAny);
    }

void CT_DataSIPRSeqHeader::DisownObjectL()
    {
    iSIPRSeqHeader = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPRSeqHeader::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

void CT_DataSIPRSeqHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPRSeqHeader;
        iSIPRSeqHeader = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPUnsignedIntHeaderBase* CT_DataSIPRSeqHeader::GetSIPUnsignedIntHeaderBase() const
    {
    return iSIPRSeqHeader;
    }

CSIPHeaderBase* CT_DataSIPRSeqHeader::GetSIPHeaderBase() const
    {
    return iSIPRSeqHeader;
    }


/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPRSeqHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	TBool	retVal = ETrue;
    if(aCommand == KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if( aCommand == KCmdDecodeL)
        {
        DoCmdDecodeL(aSection);
        }
    else if( aCommand == KCmdInternalizeValueL)
        {
        DoCmdInternalizeValueL(aSection);
        }
    else if( aCommand == KCmdDestructor)
        {
        DoCmdDestructor(aSection);
        }
	else
		{
		retVal = CT_DataSIPUnsignedIntHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
		}
	return retVal;  
	}

void CT_DataSIPRSeqHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    TUint value;

    if (GetTUintFromConfig(aSection, KFldInterval, value))
        {
        INFO_PRINTF1(_L("execute CSIPRSeqHeader::CSIPRSeqHeader(TUint)"));
        TRAPD(err,iSIPRSeqHeader= new (ELeave)CSIPRSeqHeader(value));
        if ( err!=KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iIsOwner = ETrue;
            }
        }
    }


void CT_DataSIPRSeqHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    delete iSIPRSeqHeader;
    iSIPRSeqHeader = NULL;
    
    TPtrC str;
     if(!GetStringFromConfig(aSection, KFldValue, str))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldValue());
         SetBlockResult(EFail);
         return;
         }
     
     TBuf8<KMaxTestExecuteCommandLength> value;
     CnvUtfConverter::ConvertFromUnicodeToUtf8(value, str);
     INFO_PRINTF1(_L("call CSIPRSeqHeader::DecodeL(const TDesC8 &)")); 
     TRAPD(err, iSIPRSeqHeader = CSIPRSeqHeader::DecodeL(value));
     if(KErrNone != err)
         {
         ERR_PRINTF2(KLogError, err);
         SetError(err);
         } 
     else
         {
         iIsOwner = ETrue;
         }
    }

void CT_DataSIPRSeqHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    delete iSIPRSeqHeader;
    iSIPRSeqHeader = NULL;
    
    TPtrC FileName;
    if ( !GetStringFromConfig(aSection, KFldFileName, FileName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldFileName);
        SetBlockResult(EFail);
        }
    else
        {
        CDirectFileStore*   readstore = CDirectFileStore::OpenL(FileServer(), FileName, EFileStream | EFileRead);
        CleanupStack::PushL(readstore);
        TStreamId           headerid = readstore->Root();
        RStoreReadStream    readstrm;

        readstrm.OpenL(*readstore, headerid);
        CleanupClosePushL(readstrm);
        // Execute command and log parameters
        INFO_PRINTF1(_L("execute CSIPRSeqHeader::InternalizeValueL(RReadStream &)"));
        CSIPHeaderBase* base = NULL;
        TRAPD(err, base = CSIPRSeqHeader::InternalizeValueL(readstrm));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iSIPRSeqHeader = dynamic_cast<CSIPRSeqHeader*>(base);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, readstore);
        }  
    }

void CT_DataSIPRSeqHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPRSeqHeader::~CSIPRSeqHeader()"));
    DestroyData();
    }
