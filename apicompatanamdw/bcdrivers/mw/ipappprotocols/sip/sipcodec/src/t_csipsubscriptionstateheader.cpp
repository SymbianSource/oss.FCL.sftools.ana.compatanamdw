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


// This contains CT_DataSIPSubscriptionStateHeader

#include "t_csipsubscriptionstateheader.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

//  Epoc Includes

/*@{*/
_LIT(KCmdNewL,                              "NewL");
_LIT(KCmdNewLC,                             "NewLC");
_LIT(KCmdDecodeL,                           "DecodeL");
_LIT(KCmdExpiresParameter,                  "ExpiresParameter");
_LIT(KCmdInternalizeValueL,                 "InternalizeValueL");
_LIT(KCmdRetryAfterParameter,               "RetryAfterParameter");
_LIT(KCmdSetExpiresParameterL,              "SetExpiresParameterL");
_LIT(KCmdSetRetryAfterParameterL,           "SetRetryAfterParameterL");
_LIT(KCmdSetSubStateValueL,                 "SetSubStateValueL");
_LIT(KCmdSubStateValue,                     "SubStateValue");
_LIT(KCmdDestructor,                        "~");


_LIT(KFldExpected,                          "expected");
_LIT(KFldSubStateValue,                     "substatevalue");
_LIT(KFldExpiresParam,                      "expiresparam");    
_LIT(KFldRetryAfterParam,                   "retryafter");
_LIT(KFldFileName,                          "filename");

_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
_LIT(KLogNotExpectedValueStr,               "Not expected value, actual=%S, expect=%S");
_LIT(KLogNotExpectedValueInt,               "Not expected value, actual=%d, expect=%d");


CT_DataSIPSubscriptionStateHeader* CT_DataSIPSubscriptionStateHeader::NewL()
    {
    CT_DataSIPSubscriptionStateHeader* ret=new (ELeave) CT_DataSIPSubscriptionStateHeader();
    CleanupStack::PushL(ret);
    ret->ConstructL();
    CleanupStack::Pop(ret);
    return ret;
    }

CT_DataSIPSubscriptionStateHeader::CT_DataSIPSubscriptionStateHeader():CT_DataSIPParameterHeaderBase(), iIsOwner(EFalse)

    {
    }

void CT_DataSIPSubscriptionStateHeader::ConstructL()
    {
    }

CT_DataSIPSubscriptionStateHeader::~CT_DataSIPSubscriptionStateHeader()
    {
    DestroyData();
    }

/**
* Return a pointer to the object that the data wraps
*
* @return pointer to the object that the data wraps
*/
TAny* CT_DataSIPSubscriptionStateHeader::GetObject()
    {
    return iSIPSubscriptionStateHeader;
    }

void CT_DataSIPSubscriptionStateHeader::SetObjectL(TAny* aAny)
    {
    iSIPSubscriptionStateHeader=static_cast<CSIPSubscriptionStateHeader*> (aAny);
    }

void CT_DataSIPSubscriptionStateHeader::DisownObjectL()
    {
    iSIPSubscriptionStateHeader=NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPSubscriptionStateHeader::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPSubscriptionStateHeader;
        iSIPSubscriptionStateHeader = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPHeaderBase* CT_DataSIPSubscriptionStateHeader::GetSIPHeaderBase() const
    {
    return iSIPSubscriptionStateHeader;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPSubscriptionStateHeader::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool   retVal = ETrue;
    
    if( aCommand == KCmdDestructor )
        {
        DoCmdDestructor(aSection);
        }
    else if (aCommand == KCmdDecodeL)
        {
        DoCmdDecodeL(aSection);
        }
    else if (aCommand == KCmdExpiresParameter)
        {
        DoCmdExpiresParameter(aSection);
        }
    else if (aCommand == KCmdInternalizeValueL)
        {
        DoCmdInternalizeValueL(aSection);
        }
    else if (aCommand == KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if (aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if (aCommand == KCmdRetryAfterParameter)
        {
        DoCmdRetryAfterParameter(aSection);
        }
    else if (aCommand == KCmdSetExpiresParameterL)
        {
        DoCmdSetExpiresParameterL(aSection);
        }
    else if (aCommand == KCmdSetRetryAfterParameterL)
        {
        DoCmdSetRetryAfterParameterL(aSection);
        }
    else if (aCommand == KCmdSetSubStateValueL)
        {
        DoCmdSetSubStateValueL(aSection);
        }
    else if (aCommand == KCmdSubStateValue)
        {
        DoCmdSubStateValue(aSection);
        }
     else
        {
        retVal = CT_DataSIPParameterHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
    return retVal;  
    }

void  CT_DataSIPSubscriptionStateHeader::DoCmdDecodeL(const TTEFSectionName& aSection)
    {
    TPtrC value;
     if (!GetStringFromConfig(aSection, KFldSubStateValue, value))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldSubStateValue);
         SetBlockResult(EFail);
         return;
         }
     TBuf8<KMaxTestExecuteCommandLength> value8;
     CnvUtfConverter::ConvertFromUnicodeToUtf8(value8, value);
     INFO_PRINTF1(_L("call CSIPSubscriptionStateHeader::DecodeL(const TDesC8&)"));
     TRAPD(err, iSIPSubscriptionStateHeader = CSIPSubscriptionStateHeader::DecodeL(value8));
     if (err != KErrNone)
         {
         ERR_PRINTF2(KLogError, err);
         SetError(err);
         }
     iIsOwner = err == KErrNone;
    }

void  CT_DataSIPSubscriptionStateHeader::DoCmdExpiresParameter(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPSubscriptionStateHeader::ExpiresParameter()"));
    TInt actual = iSIPSubscriptionStateHeader->ExpiresParameter();
    INFO_PRINTF2(_L("ExpiresParameter() = %d"), actual);
    
    TInt expected;
    if (GetIntFromConfig(aSection, KFldExpected, expected))
        {
        if (actual != expected)
            {
            ERR_PRINTF3(KLogNotExpectedValueInt, actual, expected);
            SetBlockResult(EFail);
            }
        }
    }

void  CT_DataSIPSubscriptionStateHeader::DoCmdInternalizeValueL(const TTEFSectionName& aSection)
    {
    TPtrC datFileName;
    if( !GetStringFromConfig(aSection, KFldFileName, datFileName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldFileName);
        SetBlockResult(EFail);
        }
    else
        {
        CDirectFileStore*   readstore = CDirectFileStore::OpenL(FileServer(), datFileName, EFileStream | EFileRead);
        CleanupStack::PushL(readstore);
        TStreamId           headerid = readstore->Root();
        RStoreReadStream    readstrm;

        readstrm.OpenL(*readstore, headerid);
        CleanupClosePushL(readstrm);
        
        INFO_PRINTF1(_L("call CSIPSubscriptionStateHeader::InternalizeValueL(RReadStream&)"));
        TRAPD(err, iSIPSubscriptionStateHeader = (CSIPSubscriptionStateHeader*)CSIPSubscriptionStateHeader::InternalizeValueL(readstrm));
        
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        iIsOwner = err == KErrNone;
        CleanupStack::PopAndDestroy(2);
        }
    }

void  CT_DataSIPSubscriptionStateHeader::DoCmdNewL(const TTEFSectionName& aSection)
    {
    TPtrC value;
    if (!GetStringFromConfig(aSection, KFldSubStateValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSubStateValue);
        SetBlockResult(EFail);
        return;
        }
    TBuf8<KMaxTestExecuteCommandLength> value8;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(value8, value);
    INFO_PRINTF1(_L("call CSIPSubscriptionStateHeader::NewL(const TDesC8&)"));
    TRAPD(err, iSIPSubscriptionStateHeader = CSIPSubscriptionStateHeader::NewL(value8));
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = err == KErrNone;
    }

void  CT_DataSIPSubscriptionStateHeader::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TPtrC value;
    if (!GetStringFromConfig(aSection, KFldSubStateValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSubStateValue);
        SetBlockResult(EFail);
        return;
        }
    TBuf8<KMaxTestExecuteCommandLength> value8;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(value8, value);
    INFO_PRINTF1(_L("call CSIPSubscriptionStateHeader::NewLC(const TDesC8&)"));
    TRAPD(err, iSIPSubscriptionStateHeader = CSIPSubscriptionStateHeader::NewLC(value8); CleanupStack::Pop(iSIPSubscriptionStateHeader));
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = err == KErrNone;
    }

void  CT_DataSIPSubscriptionStateHeader::DoCmdRetryAfterParameter(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPSubscriptionStateHeader::RetryAfterParameter()"));
    TInt actual = iSIPSubscriptionStateHeader->RetryAfterParameter();
    INFO_PRINTF2(_L("RetryAferParameter() = %d"), actual);
    
    TInt expected;
    if (GetIntFromConfig(aSection, KFldExpected, expected))
        {
        if (actual != expected)
            {
            ERR_PRINTF3(KLogNotExpectedValueInt, actual, expected);
            SetBlockResult(EFail);
            }
        }
    }

void  CT_DataSIPSubscriptionStateHeader::DoCmdSetExpiresParameterL(const TTEFSectionName& aSection)
    {
    TInt expires;
    if (!GetIntFromConfig(aSection, KFldExpiresParam, expires))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldExpiresParam);
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("call CSIPSubscriptionStateHeader::SetExpiresParameterL(TInt)"));
    TRAPD(err, iSIPSubscriptionStateHeader->SetExpiresParameterL(expires));
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void  CT_DataSIPSubscriptionStateHeader::DoCmdSetRetryAfterParameterL(const TTEFSectionName& aSection)
    {
    TInt retryafter;
    if (!GetIntFromConfig(aSection, KFldRetryAfterParam, retryafter))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldRetryAfterParam);
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("call CSIPSubscriptionStateHeader::SetRetryAfterParameterL(TInt)"));
    TRAPD(err, iSIPSubscriptionStateHeader->SetRetryAfterParameterL(retryafter));
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void  CT_DataSIPSubscriptionStateHeader::DoCmdSetSubStateValueL(const TTEFSectionName& aSection)
    {
    TPtrC value;
    if (!GetStringFromConfig(aSection, KFldSubStateValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSubStateValue);
        SetBlockResult(EFail);
        return;
        }
    TBuf8<KMaxTestExecuteCommandLength> value8;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(value8, value);
    INFO_PRINTF1(_L("call CSIPSubscriptionStateHeader::SetSubStateValueL(const TDesC8&)"));
    TRAPD(err, iSIPSubscriptionStateHeader->SetSubStateValueL(value8));
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void  CT_DataSIPSubscriptionStateHeader::DoCmdSubStateValue(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPSubscriptionStateHeader::SubStateValue()"));
    const TDesC8& actual8 = iSIPSubscriptionStateHeader->SubStateValue();
    TBuf<KMaxTestExecuteCommandLength> actual;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(actual, actual8);
    INFO_PRINTF2(_L("SubStateValue() = %S"), &actual);
    
    TPtrC expected;
    if (GetStringFromConfig(aSection, KFldExpected, expected))
        {
        if(actual.Compare(expected) != 0)
            {
            ERR_PRINTF3(KLogNotExpectedValueStr, &actual, &expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPSubscriptionStateHeader::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPSubscriptionStateHeader::~CSIPSubscriptionStateHeader()"));
    DestroyData();
    }

void CT_DataSIPSubscriptionStateHeader::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
