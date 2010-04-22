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


// This contains CT_DataSIPHeaderBase
#include "t_csipheaderbase.h"
#include <utf.h>
#include <s32file.h>
#include "T_SIPUtil.h"

/*@{*/
_LIT(KCmdCloneL,                    "CloneL");
_LIT(KCmdName,                      "Name");
_LIT(KCmdToTextL,                   "ToTextL");
_LIT(KCmdToTextLC,                  "ToTextLC");
_LIT(KCmdToTextValueL,              "ToTextValueL");
_LIT(KCmdToTextValueLC,             "ToTextValueLC");
_LIT(KCmdExternalizeL,              "ExternalizeL");
_LIT(KCmdExternalizeSupported,      "ExternalizeSupported");
_LIT(KCmdPushLC,                    "PushLC");

// Fields 
_LIT(KFldSIPHeaderBase,             "sipheaderbase");
_LIT(KFldExpected,                  "expected");
_LIT(KFldFileName,                  "filename");
_LIT(KFldSIPHeaders,                "sipheaders");
_LIT(KFldAddName,                   "addname");

// Error
_LIT(KLogError,                     "Error=%d");
_LIT(KMissingParameter,             "missing parameter '%S'");
//Info


CT_DataSIPHeaderBase::CT_DataSIPHeaderBase() :
CDataWrapperBase()
    {
    }

TBool CT_DataSIPHeaderBase::DoCommandL(const TTEFFunction& aCommand,
        const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
    {
    TBool ret = ETrue;

    if (aCommand == KCmdCloneL)
        {
        DoCmdCloneL(aSection);
        }
    else if (aCommand == KCmdName)
        {
        DoCmdName(aSection);
        }
    else if (aCommand == KCmdToTextL)
        {
        DoCmdToTextL(aSection);
        }
    else if (aCommand == KCmdToTextLC)
        {
        DoCmdToTextLC(aSection);
        }
    else if (aCommand == KCmdToTextValueL)
        {
        DoCmdToTextValueL(aSection);
        }
    else if (aCommand == KCmdToTextValueLC)
        {
        DoCmdToTextValueLC(aSection);
        }
    else if (aCommand == KCmdExternalizeL)
        {
        DoCmdExternalizeL(aSection);
        }
    else if (aCommand == KCmdExternalizeSupported)
        {
        DoCmdExternalizeSupported(aSection);
        }
    else if (aCommand == KCmdPushLC)
        {
        DoCmdPushLC(aSection);
        }
    else
        {
        ret = EFalse;
        }       
    return ret;
    }


void CT_DataSIPHeaderBase::DoCmdCloneL(const TTEFSectionName& aSection)
    {
    CSIPHeaderBase* sipHeaderBase = NULL;
    TPtrC datSipHeaderBase;
    if (!GetStringFromConfig(aSection, KFldSIPHeaderBase, datSipHeaderBase))
        {
        ERR_PRINTF2(KMissingParameter, &KFldSIPHeaderBase());
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPHeaderBase::CloneL()"));
        TRAPD(err,sipHeaderBase=GetSIPHeaderBase()->CloneL());
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            SetDataObjectL(datSipHeaderBase, sipHeaderBase);
            }
        }    
    }

void CT_DataSIPHeaderBase::DoCmdName(const TTEFSectionName& aSection)
    {
    RStringF  stringF;
    INFO_PRINTF1(_L("execute CSIPHeaderBase::Name"));
    stringF = GetSIPHeaderBase()->Name();
    const TDesC8 &name = stringF.DesC();
    TBuf<KMaxTestExecuteCommandLength> actual;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(actual, name);
    INFO_PRINTF2(_L("Header Name is , name: %S"), &actual);
    
    TPtrC expected;
    if (GetStringFromConfig(aSection, KFldExpected, expected) )
        {
        if (expected.Compare(actual) != 0)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %S, actual: %S"), &expected, &actual);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPHeaderBase::DoCmdToTextL(const TTEFSectionName& aSection)
    {    
    HBufC8* val ;
    TPtrC expected;
    
    INFO_PRINTF1(_L("execute CSIPHeaderBase::ToTextL()"));
    TRAPD(err,val=GetSIPHeaderBase()->ToTextL());
    TBuf<KMaxTestExecuteCommandLength> actual;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(actual, val->Des());
    INFO_PRINTF2(_L("Header Name&Value is , name: %S"), &actual);
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else if(GetStringFromConfig(aSection, KFldExpected, expected))
        {
        if (expected.Compare(actual) != 0)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %S, actual: %S"), &expected, &actual);
            SetBlockResult(EFail);
            }
        delete val;
        val = NULL;
        }
    }

void CT_DataSIPHeaderBase::DoCmdToTextLC(const TTEFSectionName& aSection)
    {
    HBufC8* val ;
    TPtrC expected;
    
    INFO_PRINTF1(_L("execute CSIPHeaderBase::ToTextLC()"));
    TRAPD(err,val=GetSIPHeaderBase()->ToTextLC(); CleanupStack::Pop());
    TBuf<KMaxTestExecuteCommandLength> actual;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(actual, val->Des());
    INFO_PRINTF2(_L("Header Name&Value is , name: %S"), &actual);
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }    
    else if (GetStringFromConfig(aSection, KFldExpected, expected))
        {
        if (expected.Compare(actual) != 0)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %S, actual: %S"), &expected, &actual);
            SetBlockResult(EFail);
            }
        delete val;
        val = NULL;
        }  
    }

void CT_DataSIPHeaderBase::DoCmdToTextValueL(const TTEFSectionName& aSection)
    {
    HBufC8* val ;
    TPtrC expected;
    
    INFO_PRINTF1(_L("execute CSIPHeaderBase::ToTextValueL()"));
    TRAPD(err,val=GetSIPHeaderBase()->ToTextValueL());
    TBuf<KMaxTestExecuteCommandLength> actual;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(actual, val->Des());
    INFO_PRINTF2(_L("Header Name's Value is , name value: %S"), &actual);
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }    
    else if (GetStringFromConfig(aSection, KFldExpected, expected))
        {
        if (expected.Compare(actual) != 0)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %S, actual: %S"), &expected, &actual);
            SetBlockResult(EFail);
            }
        delete val;
        val = NULL;
        }    
    }

void CT_DataSIPHeaderBase::DoCmdToTextValueLC(const TTEFSectionName& aSection)
    {
    HBufC8* val ;
    TPtrC expected;
    
    INFO_PRINTF1(_L("execute CSIPHeaderBase::ToTextValueLC()"));
    TRAPD(err,val=GetSIPHeaderBase()->ToTextValueLC(); CleanupStack::Pop());
    TBuf<KMaxTestExecuteCommandLength> actual;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(actual, val->Des());
    INFO_PRINTF2(_L("Header Name's Value is , name value: %S"), &actual);
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }    
    else if (GetStringFromConfig(aSection, KFldExpected, expected))
        {
        if (expected.Compare(actual) != 0)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %S, actual: %S"), &expected, &actual);
            SetBlockResult(EFail);
            }
        delete val;
        val = NULL;
        }
    }

void CT_DataSIPHeaderBase::DoCmdExternalizeL(const TTEFSectionName& aSection)
    {
    TPtrC datFileName;
    if ( !GetStringFromConfig(aSection, KFldFileName, datFileName) )
        {
        ERR_PRINTF2(KMissingParameter, &KFldFileName);
        SetBlockResult(EFail);
        }
    else
        {
        CDirectFileStore* writestore = CDirectFileStore::ReplaceL(FileServer(), datFileName, EFileStream | EFileWrite);
        CleanupStack::PushL(writestore);        
        writestore->SetTypeL(TUidType(KDirectFileStoreLayoutUid));
        RStoreWriteStream writestrm;
        CleanupClosePushL(writestrm);
        TStreamId headerid = writestrm.CreateL(*writestore);
        writestore->SetRootL(headerid);

        // Execute command and log parameters
        INFO_PRINTF1(_L("execute CSIPHeaderBase::InternalizeValueL(RReadStream &)"));
        TBool addname = ETrue;
        (void)GetBoolFromConfig(aSection, KFldAddName, addname);        
        TRAPD(err, GetSIPHeaderBase()->ExternalizeL(writestrm, addname));
        if ( err!=KErrNone )
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        // Cleanup
        CleanupStack::PopAndDestroy(2, writestore);
        }
    }

void CT_DataSIPHeaderBase::DoCmdExternalizeSupported(const TTEFSectionName& aSection)
    {
    TBool expected;  
    
    INFO_PRINTF1(_L("execute CSIPHeaderBase::ExternalizeSupported()"));
    TBool actual = GetSIPHeaderBase()->ExternalizeSupported();
    if (GetBoolFromConfig(aSection, KFldExpected, expected))
        {
        if (!expected != !actual)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %d, actual: %d"), expected, actual);
            SetBlockResult(EFail);
            }
        }    
    }

void CT_DataSIPHeaderBase::DoCmdPushLC(const TTEFSectionName& aSection)
    {
    RPointerArray<CSIPHeaderBase> *array = new(ELeave)RPointerArray<CSIPHeaderBase>;
    if(!CT_SIPUtil::GetSIPHeadersL(*this,aSection,KFldSIPHeaders,*array))
        {
        ERR_PRINTF2(KMissingParameter, &KFldSIPHeaders);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPHeaderBase::PushLC(RPointerArray<CSIPHeaderBase> *aArray)"));
        TRAPD(err, CSIPHeaderBase::PushLC(array); CleanupStack::Pop());
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    }
