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


// This contains CT_DataSIPTransactionBase

#include "t_csiptransactionbase.h"
#include "T_SIPUtil.h"
#include <utf.h> 

/*@{*/
_LIT(KCmdIsSIPClientTransaction,			"IsSIPClientTransaction");
_LIT(KCmdStateL,						    "StateL");
_LIT(KCmdType,								"Type");
_LIT(KCmdCompare,  							"==");

_LIT(KFldExpected, 							"expected");
_LIT(KFldSIPTransaction,                    "siptransaction");

_LIT(KLogError,								"Error=%d");
_LIT(KLogMissingParameter, 					"Missing parameter '%S'");
_LIT(KLogNotExpectedValue,                  "Not expected value, actual=%d, expect=%d");
_LIT(KLogNotExpectedValue1,                 "Not expected value, actual=%S, expect=%S");
/*}@*/

CT_DataSIPTransactionBase::CT_DataSIPTransactionBase(): CDataWrapperBase()
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
TBool CT_DataSIPTransactionBase::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
	{
	TBool	retVal = ETrue;

    if( aCommand == KCmdIsSIPClientTransaction )
        {
        DoCmdIsSIPClientTransaction(aSection);
        }
    else if( aCommand == KCmdStateL )
        {
        DoCmdStateL(aSection);
        }
	else if( aCommand == KCmdType )
		{
		DoCmdType(aSection);
		}
    else if( aCommand == KCmdCompare )
        {
        DoCmdCompare(aSection);
        }
	else
		{
		retVal = EFalse;
		}
	return retVal;  
	}

void CT_DataSIPTransactionBase::DoCmdType(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPTransactionBase::Type()"));
    RStringF ret = GetSIPTransactionBaseObject()->Type();
    INFO_PRINTF2(_L("Type : %S"), ret.DesC());
    
    RStringF expected;
    if( CT_SIPUtil::GetStringF(*this, aSection, KFldExpected, expected) )
        {
        if(ret != expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue1, ret.DesC(), expected.DesC());
            SetBlockResult(EFail);
            }
        expected.Close();
        }
    
    ret.Close();
    }

void CT_DataSIPTransactionBase::DoCmdStateL(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPTransactionBase::StateL()"));
    CSIPTransactionBase::TState ret;
    TRAPD(err, ret = GetSIPTransactionBaseObject()->StateL());
    INFO_PRINTF2(_L("State : %d"), ret);
    
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        CSIPTransactionBase::TState expected;
        if( CT_SIPUtil::GetState(*this, aSection, KFldExpected, expected) )
            {
            if(ret != expected)
                {
                ERR_PRINTF3(KLogNotExpectedValue, (TInt)ret, (TInt)expected);
                SetBlockResult(EFail);
                }
            }        
        }
    }

void CT_DataSIPTransactionBase::DoCmdIsSIPClientTransaction(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPTransactionBase::IsSIPClientTransaction()"));
    TBool ret = GetSIPTransactionBaseObject()->IsSIPClientTransaction();
    INFO_PRINTF2(_L("Return : %d"), (TInt)ret);
    
    TBool expected;
    if( GetBoolFromConfig(aSection, KFldExpected, expected) )
        {
        if(!ret != !expected)
            {
            ERR_PRINTF3(KLogNotExpectedValue, (TInt)ret, (TInt)expected);
            SetBlockResult(EFail);
            }
        }
    }

// operator ==()
void CT_DataSIPTransactionBase::DoCmdCompare(const TTEFSectionName& aSection)
    {
    CSIPTransactionBase* siptransaction;
    if( !CT_SIPUtil::GetSIPTransactionL(*this, aSection, KFldSIPTransaction, siptransaction) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPTransaction);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPTransactionBase::==(const CSIPTransactionBase&)")); 
        TBool ret = (*GetSIPTransactionBaseObject() == *siptransaction);
        INFO_PRINTF2(_L("Return : %d"), (TInt)ret);
        
        TBool expected;
        if( GetBoolFromConfig(aSection, KFldExpected, expected) )
            {
            if(!ret != !expected)
                {
                ERR_PRINTF3(KLogNotExpectedValue, (TInt)ret, (TInt)expected);
                SetBlockResult(EFail);
                }
            }
        }
    }

