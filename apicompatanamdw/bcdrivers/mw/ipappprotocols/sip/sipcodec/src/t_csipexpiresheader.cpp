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


#include "t_csipexpiresheader.h"
#include <utf.h>
#include <s32file.h>


/*@{*/
_LIT(KDestructor,                   "~");
_LIT(KCmdDecodeL,                   "DecodeL");
_LIT(KCmdNewL,                      "NewL");
_LIT(KCmdInternalizeValueL,         "InternalizeValueL");

// Fields 
_LIT(KFldInterval,                  "interval");
_LIT(KFldExpireValue,               "expirevalue");
_LIT(KFldFileName,                  "filename");

// Error
_LIT(KLogError,                     "Error=%d");
_LIT(KMissingParameter,             "missing parameter '%S'");
//Info

CT_DataSIPExpiresHeader* CT_DataSIPExpiresHeader::NewL()
    {
    CT_DataSIPExpiresHeader* self = new (ELeave) CT_DataSIPExpiresHeader();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }
    
CT_DataSIPExpiresHeader::~CT_DataSIPExpiresHeader()
    {
    DestroyData();
    }

void CT_DataSIPExpiresHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPExpiresHeader;
        iSIPExpiresHeader = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPHeaderBase* CT_DataSIPExpiresHeader::GetSIPHeaderBase() const
    {
    return iSIPExpiresHeader;
    }

TAny* CT_DataSIPExpiresHeader::GetObject()
    {
    return iSIPExpiresHeader;
    }

void CT_DataSIPExpiresHeader::SetObjectL(TAny* aAny)
    {
    DestroyData();
    iSIPExpiresHeader = static_cast<CSIPExpiresHeader*> (aAny);
    }

void CT_DataSIPExpiresHeader::DisownObjectL()
    {
    iSIPExpiresHeader = NULL;
    iIsOwner = EFalse;
    }

CT_DataSIPExpiresHeader::CT_DataSIPExpiresHeader() :CT_DataSIPHeaderBase(), iSIPExpiresHeader(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPExpiresHeader::ConstructL()
    {
    }

void CT_DataSIPExpiresHeader::DoCmdDestructor()
    {
    DestroyData();
    }

TBool CT_DataSIPExpiresHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret = ETrue;
    if (aCommand == KDestructor)
        {
        DoCmdDestructor();
        }
    else if(aCommand == KCmdDecodeL)
        {
        DoCmdDecodeL(aSection);
        }
    else if(aCommand == KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if(aCommand == KCmdInternalizeValueL)
        {
        DoCmdInternalizeValueL(aSection);
        }
    else
        {
        ret = CT_DataSIPHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
    return ret;
    }

void CT_DataSIPExpiresHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    TUint value;

    // Parameter of CSIPAddress type.
    if (GetTUintFromConfig(aSection, KFldInterval, value))
        {
        INFO_PRINTF1(_L("execute CSIPExpiresHeader::CSIPExpiresHeader(TUint)"));
        TRAPD(err,iSIPExpiresHeader= new (ELeave)CSIPExpiresHeader(value));
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

void CT_DataSIPExpiresHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    delete iSIPExpiresHeader;
    iSIPExpiresHeader = NULL;
    
    TPtrC FileName;
    if ( !GetStringFromConfig(aSection, KFldFileName, FileName) )
        {
        ERR_PRINTF2(KMissingParameter, &KFldFileName);
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
        INFO_PRINTF1(_L("execute CSIPExpiresHeader::InternalizeValueL(RReadStream &)"));
        CSIPHeaderBase* base = NULL;
        TRAPD(err, base = CSIPExpiresHeader::InternalizeValueL(readstrm));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iSIPExpiresHeader = dynamic_cast<CSIPExpiresHeader*>(base);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, readstore);
        }  
    }

void CT_DataSIPExpiresHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {  
    TPtrC str;
     if(!GetStringFromConfig(aSection, KFldExpireValue, str))
         {
         ERR_PRINTF2(KMissingParameter, &KFldExpireValue());
         SetBlockResult(EFail);
         return;
         }
     
     TBuf8<KMaxTestExecuteCommandLength> value;
     CnvUtfConverter::ConvertFromUnicodeToUtf8(value, str);
     INFO_PRINTF1(_L("call CSIPExpiresHeader::DecodeL(const TDesC8 &)"));
     TRAPD(err, iSIPExpiresHeader = CSIPExpiresHeader::DecodeL(value));
     if(KErrNone != err)
         {
         ERR_PRINTF2(KLogError, err);
         SetError(err);
         } 
    }

void CT_DataSIPExpiresHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
