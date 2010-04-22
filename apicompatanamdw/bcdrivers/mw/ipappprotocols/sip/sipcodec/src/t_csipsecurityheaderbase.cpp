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


// This contains CT_DataSIPSecurityHeaderBase

#include "t_csipsecurityheaderbase.h"
#include "T_SIPUtil.h"
#include <utf.h>
#include <s32file.h>

//  Epoc Includes

/*@{*/
_LIT(KCmdMechanismName,                     "MechanismName");
_LIT(KCmdPreferenceParam,                   "PreferenceParam");
_LIT(KCmdSetMechanismNameL,                 "SetMechanismNameL");
_LIT(KCmdSetPreferenceParamL,               "SetPreferenceParamL");
_LIT(KCmdDestructor,                        "~");

_LIT(KFldExpected,                          "expected");
_LIT(KFldMechanismName,                     "mechanismname");
_LIT(KFldTReal,                             "treal");

_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
_LIT(KLogNotExpectedValueReal,              "Not expected value, actual=%f, expect=%f");            

CT_DataSIPSecurityHeaderBase::CT_DataSIPSecurityHeaderBase():CT_DataSIPParameterHeaderBase()
    {
    
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPSecurityHeaderBase::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool   retVal = ETrue;
    
    if( aCommand == KCmdDestructor )
        {
        DoCmdDestructor(aSection);
        }
    else if (aCommand == KCmdMechanismName)
        {
        DoCmdMechanismName(aSection);
        }
    else if (aCommand == KCmdPreferenceParam)
        {
        DoCmdPreferenceParam(aSection);
        }
    else if (aCommand == KCmdSetMechanismNameL)
        {
        DoCmdSetMechanismNameL(aSection);
        }
    else if (aCommand == KCmdSetPreferenceParamL)
        {
        DoCmdSetPreferenceParamL(aSection);
        }
     else
        {
        retVal = CT_DataSIPParameterHeaderBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
    return retVal;  
    }

void  CT_DataSIPSecurityHeaderBase::DoCmdMechanismName(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPSecurityHeaderBase::MechanismName()"));
    
    const TDesC8& mechanismname = ((CSIPSecurityHeaderBase*)GetSIPHeaderBase())->MechanismName();
    
    TBuf<KMaxTestExecuteCommandLength> str;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(str, mechanismname);
    INFO_PRINTF2(_L("The actual mechanism name is: %S "), &str);
    
    TPtrC expected;
    if(GetStringFromConfig(aSection, KFldExpected, expected))
        {
        if(expected != str)
            {
            ERR_PRINTF2(_L("The expected mechanism name is: %S"), &expected);
            SetBlockResult(EFail);
            }
        }
    }

void  CT_DataSIPSecurityHeaderBase::DoCmdPreferenceParam(const TTEFSectionName& aSection)
    {
    TReal retTReal;
    TReal expected;

    INFO_PRINTF1(_L("call CSIPSecurityHeaderBase::PreferenceParam()")); 
    retTReal = ((CSIPSecurityHeaderBase*)GetSIPHeaderBase())->PreferenceParam();
    INFO_PRINTF2(_L("The value of the Preference parameter is : %f"), retTReal);
    if (CT_SIPUtil::GetTRealFromConfig(*this, aSection, KFldExpected, expected))
        {
        if(!CT_SIPUtil::CompareTReal(retTReal, expected ))
            {
            ERR_PRINTF3(KLogNotExpectedValueReal, retTReal, expected);
            SetBlockResult(EFail);
            }
        }
    }

void  CT_DataSIPSecurityHeaderBase::DoCmdSetMechanismNameL(const TTEFSectionName& aSection)
    {
    TPtrC str;
    if(!GetStringFromConfig(aSection, KFldMechanismName, str))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldMechanismName());
        SetBlockResult(EFail);
        return;
        }
    
    TBuf8<KMaxTestExecuteCommandLength> mechanismname;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(mechanismname, str);
    
    INFO_PRINTF1(_L("call CSIPSecurityHeaderBase::SetMechanismNameL(const TDesC8 &)"));
    
    TRAPD(err, ((CSIPSecurityHeaderBase*)GetSIPHeaderBase())->SetMechanismNameL(mechanismname));
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }   
    }

void  CT_DataSIPSecurityHeaderBase::DoCmdSetPreferenceParamL(const TTEFSectionName& aSection)
    {
    TReal dattreal;
    if(!CT_SIPUtil::GetTRealFromConfig(*this, aSection, KFldTReal, dattreal) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldTReal);
        SetBlockResult(EFail);
        return;
        }    
    INFO_PRINTF1(_L("execute CSIPSecurityHeaderBase::SetPreferenceParamL(TReal)")); 
    TRAPD(err, ((CSIPSecurityHeaderBase*)GetSIPHeaderBase())->SetPreferenceParamL(dattreal));
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    }

void CT_DataSIPSecurityHeaderBase::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPSecurityHeaderBase::~CSIPSecurityHeaderBase()"));
    }
