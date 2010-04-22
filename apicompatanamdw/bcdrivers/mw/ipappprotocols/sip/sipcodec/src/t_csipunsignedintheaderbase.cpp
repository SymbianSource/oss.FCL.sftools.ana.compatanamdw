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


// This contains CT_DataSIPUnsignedIntHeaderBase
#include "t_csipunsignedintheaderbase.h"
#include <utf.h>
#include <s32file.h>
#include "T_SIPUtil.h"

/*@{*/
_LIT(KCmdSetValue,                 "SetValue");
_LIT(KCmdValue,                     "Value");

// Fields 
_LIT(KFldValue,                     "value");
_LIT(KFldExpected,                  "expected");

// Error
_LIT(KLogError,                     "Error=%d");
_LIT(KLogMissingParameter,          "missing parameter '%S'");
//Info


CT_DataSIPUnsignedIntHeaderBase::CT_DataSIPUnsignedIntHeaderBase() :
CT_DataSIPHeaderBase()
    {
    }

TBool CT_DataSIPUnsignedIntHeaderBase::DoCommandL(const TTEFFunction& aCommand,
        const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret = ETrue;

    if (aCommand == KCmdSetValue)
        {
        DoCmdSetValue(aSection);
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

void CT_DataSIPUnsignedIntHeaderBase::DoCmdSetValue(const TTEFSectionName& aSection)
    {
    TUint value;
    if (!GetTUintFromConfig(aSection, KFldValue, value))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldValue);
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("execute CSIPUnsignedIntHeaderBase::SetValue(TUint)"));
    TRAPD(err, GetSIPUnsignedIntHeaderBase()->SetValue(value));
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPUnsignedIntHeaderBase::DoCmdValue(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPUnsignedIntHeaderBase::Value()"));
    TUint actual = GetSIPUnsignedIntHeaderBase()->Value();
    INFO_PRINTF2(_L("CSIPUnsignedIntHeaderBase::Value() = %u"), actual);
    
    TUint expected;
    if (GetTUintFromConfig(aSection, KFldExpected, expected) )
        {
        if (actual != expected)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %u, actual: %u"), expected, actual);
            SetBlockResult(EFail);
            }
        }
    }
