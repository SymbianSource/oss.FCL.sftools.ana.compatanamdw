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


// This contains CT_DataSIPTokenHeaderBase
#include "t_csiptokenheaderbase.h"
#include <utf.h>
#include <s32file.h>
#include "T_SIPUtil.h"

/*@{*/
_LIT(KCmdSetValueL,                 "SetValueL");
_LIT(KCmdValue,                     "Value");

// Fields 
_LIT(KFldValue,                     "value");
_LIT(KFldExpected,                  "expected");

// Error
_LIT(KLogError,                     "Error=%d");
_LIT(KLogMissingParameter,          "missing parameter '%S'");
//Info


CT_DataSIPTokenHeaderBase::CT_DataSIPTokenHeaderBase() :
CT_DataSIPHeaderBase()
    {
    }

TBool CT_DataSIPTokenHeaderBase::DoCommandL(const TTEFFunction& aCommand,
        const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret = ETrue;

    if (aCommand == KCmdSetValueL)
        {
        DoCmdSetValueL(aSection);
        }
    else if (aCommand == KCmdValue)
        {
        DoCmdValue(aSection);
        }
    else
        {
        ret = CT_DataSIPHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }       
    return ret;
    }

void CT_DataSIPTokenHeaderBase::DoCmdSetValueL(const TTEFSectionName& aSection)
    {
    RStringF value;
    if (!CT_SIPUtil::GetStringF(*this, aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("execute CSIPTokenHeaderBase::SetValueL(RStringF)"));
    TRAPD(err, GetSIPTokenHeaderBase()->SetValueL(value));
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPTokenHeaderBase::DoCmdValue(const TTEFSectionName& aSection)
    {
    RStringF  stringF;
    INFO_PRINTF1(_L("execute CSIPTokenHeaderBase::Value()"));
    stringF = GetSIPTokenHeaderBase()->Value();
    const TDesC8 &actual8 = stringF.DesC();
    TBuf<KMaxTestExecuteCommandLength> actual;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(actual, actual8);
    INFO_PRINTF2(_L("CSIPTokenHeaderBase::Value() = %S"), &actual);
    
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
