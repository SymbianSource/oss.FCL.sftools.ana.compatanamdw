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


#include <sipstrings.h>
#include "T_SIPUtil.h"
#include "t_csipparameterheaderbase.h"

/*@{*/
_LIT(KCmdHasParam,                          "HasParam");
_LIT(KCmdParamValue,                        "ParamValue");
_LIT(KCmdSetParamL,                         "SetParamL");
_LIT(KCmdDeleteParam,                       "DeleteParam");
_LIT(KCmdParamCount,                        "ParamCount");
_LIT(KCmdParam,                             "Param");

//Fields 
_LIT(KFldParameterName,                     "ParameterName");
_LIT(KFldParameterValue,                    "ParameterValue");
_LIT(KFldParameterIndex,                    "ParameterIndex");
_LIT(KFldExpected,                          "expected");

// Logging
_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
_LIT(KLogNotExpectedIntValue,               "Not expected value, actual=%d, expect=%d");
_LIT(KLogNotExpectedStringValue,            "Not expected value, actual=%S, expect=%S");


/**
* Constructor. First phase construction
*/
CT_DataSIPParameterHeaderBase::CT_DataSIPParameterHeaderBase()
:   CT_DataSIPHeaderBase()
    {
    
    }

/**
* Process a command read from the ini file
*
* @param aDataWrapper   test step requiring command to be processed
* @param aCommand   the command to process
* @param aSection       the entry in the ini file requiring the command to be processed
*
* @return ETrue if the command is processed
*/
TBool CT_DataSIPParameterHeaderBase::DoCommandL(const TTEFFunction& aCommand, 
        const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret = ETrue;
    
    if ( aCommand==KCmdHasParam )
        {
        DoCmdHasParam(aSection);
        }
    else if ( aCommand==KCmdParamValue )
        {
        DoCmdParamValue(aSection);
        }
    else if (aCommand==KCmdSetParamL)
        {
        DoCmdSetParamL(aSection);
        }
    else if (aCommand==KCmdDeleteParam)
        {
        DoCmdDeleteParam(aSection);
        }
    else if (aCommand==KCmdParamCount)
        {
        DoCmdParamCount(aSection);
        }
    else if (aCommand==KCmdParam)
        {
        DoCmdParam(aSection);
        }  
    else
        {
        ret=CT_DataSIPHeaderBase::DoCommandL(aCommand,aSection,aAsyncErrorIndex);
        }
    
    return ret;
    }

//Checks if a parameter is present
void CT_DataSIPParameterHeaderBase::DoCmdHasParam(const TTEFSectionName& aSection)
    {
    TBool actual = EFalse;
    TBool expected = EFalse;
    RStringF paramname;
    
    if( !CT_SIPUtil::GetStringF(*this, aSection, KFldParameterName, paramname) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParameterName);
        SetBlockResult(EFail);
        }
    else
        {
        
        INFO_PRINTF1(_L("call CSIPParameterHeaderBase::HasParam(aName)"));
        
        actual = ((CSIPParameterHeaderBase*)GetSIPHeaderBase())->HasParam(paramname);
        
        INFO_PRINTF2(_L("The actual value for HasParam() is %d"), actual);
        
        if (GetBoolFromConfig(aSection, KFldExpected, expected))
            {
            if (actual == expected)
                {
                INFO_PRINTF1(_L("call CSIPParameterHeaderBase::HasParam() successfully!"));
                }
            else
                {
                ERR_PRINTF3(KLogNotExpectedIntValue, actual, expected);
                SetBlockResult(EFail);
                }
            }
       
        }
    }

//Gets a special parameter value
void CT_DataSIPParameterHeaderBase::DoCmdParamValue(const TTEFSectionName& aSection)
    {
    RStringF    paramname;
    RStringF    actualStringF;
    RStringF    expectedStringF;

    if( !CT_SIPUtil::GetStringF(*this, aSection, KFldParameterName, paramname) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParameterName);
        SetBlockResult(EFail);
        }
    else
        {

        INFO_PRINTF1(_L("call CSIPParameterHeaderBase::ParamValue(aName)"));
        actualStringF = ((CSIPParameterHeaderBase*)GetSIPHeaderBase())->ParamValue(paramname);
        
        TBuf<60> actual;
        CT_SIPUtil::ConvertToUnicode(actualStringF.DesC(), actual);
        
        INFO_PRINTF2(_L("The actual value for ParamValue() is %S"), &actual);
        
        if (CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldExpected, SIPStrings::Pool(), expectedStringF))
            {
            if (actualStringF == expectedStringF)
                {
                INFO_PRINTF1(_L("call CSIPParameterHeaderBase::ParamValue() successfully!"));
                }
            else
                {
                TBuf<60> expected;
                CT_SIPUtil::ConvertToUnicode(expectedStringF.DesC(), expected);
                ERR_PRINTF3(KLogNotExpectedStringValue, &actual, &expected);
                SetBlockResult(EFail);
                }
            }
        }
    }

//Sets a parameter with a value, or sets a parameter without a value
void CT_DataSIPParameterHeaderBase::DoCmdSetParamL(const TTEFSectionName& aSection)
    {
    RStringF paramname;
    RStringF paramvalue;
    TPtrC expected;

    if( !CT_SIPUtil::GetStringF(*this, aSection, KFldParameterName, paramname) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParameterName);
        SetBlockResult(EFail);
        }
    else
        {
        if( CT_SIPUtil::GetStringFFromConfigL(*this, aSection, KFldParameterValue, SIPStrings::Pool(), paramvalue))
            {
            //CSIPParameterHeaderBase::SetParamL(name,value)
            INFO_PRINTF1(_L("call CSIPParameterHeaderBase::SetParamL(name,value)"));
            TRAPD(err, ((CSIPParameterHeaderBase*)GetSIPHeaderBase())->SetParamL(paramname, paramvalue));
            if(err == KErrNone)
                {
                INFO_PRINTF1(_L("call CSIPParameterHeaderBase::SetParamL(name, value) successfully"));
                }
            else
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            }
        else 
            {
            //CSIPParameterHeaderBase::SetParamL(name)
            INFO_PRINTF1(_L("call CSIPParameterHeaderBase::SetParamL(name)"));
            TRAPD(err, ((CSIPParameterHeaderBase*)GetSIPHeaderBase())->SetParamL(paramname));  
            if(err == KErrNone)
                {
                INFO_PRINTF1(_L("call CSIPParameterHeaderBase::SetParamL(name) successfully"));
                }
            else
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            }        
        }
    }

//Deletes a specified  parameter
void CT_DataSIPParameterHeaderBase::DoCmdDeleteParam(const TTEFSectionName& aSection)
    {
    RStringF paramname;
    
    if( !CT_SIPUtil::GetStringF(*this, aSection, KFldParameterName, paramname) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParameterName);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPParameterHeaderBase::DeleteParam(aName)"));
        ((CSIPParameterHeaderBase*)GetSIPHeaderBase())->DeleteParam(paramname);
        }
    }

//Gets the count of header parameters
void CT_DataSIPParameterHeaderBase::DoCmdParamCount(const TTEFSectionName& aSection)
    {
    TInt actual(0);
    TInt expected(0);
            
    INFO_PRINTF1(_L("call CSIPParameterHeaderBase::ParamCount()"));
    
    actual = ((CSIPParameterHeaderBase*)GetSIPHeaderBase())->ParamCount();
    
    INFO_PRINTF2(_L("The actual value for ParamCount() is %d"), actual);
    
    if (GetIntFromConfig(aSection,KFldExpected,expected))
        {
        if (actual == expected)
            {
            INFO_PRINTF1(_L("call CSIPParameterHeaderBase::ParamCount() successfully!"));
            }
        else
            {
            ERR_PRINTF3(KLogNotExpectedIntValue, actual, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPParameterHeaderBase::DoCmdParam(const TTEFSectionName& aSection)
    {
    TInt index(0);
    TInt err(0);
    
    if( !GetIntFromConfig(aSection, KFldParameterIndex, index) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldParameterIndex);
        SetBlockResult(EFail);
        }
    else
        {
        RStringF    paramname;
        RStringF    expectedStringF;
        
        INFO_PRINTF1(_L("call CSIPParameterHeaderBase::Param(aIndex,aName)"));
        err = ((CSIPParameterHeaderBase*)GetSIPHeaderBase())->Param(index, paramname);
        if(err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        
        if (CT_SIPUtil::GetStringF(*this, aSection,KFldExpected,expectedStringF))
            {
            if (paramname == expectedStringF)
                {
                INFO_PRINTF1(_L("call CSIPParameterHeaderBase::Param(aIndex,aName) successfully!"));
                }
            else
                {
                TBuf<60> actual;
                TBuf<60> expected;
                CT_SIPUtil::ConvertToUnicode(paramname.DesC(), actual);
                CT_SIPUtil::ConvertToUnicode(expectedStringF.DesC(), expected);
                ERR_PRINTF3(KLogNotExpectedStringValue,&actual, &expected);
                SetBlockResult(EFail);
                }
            }
        }
    }
