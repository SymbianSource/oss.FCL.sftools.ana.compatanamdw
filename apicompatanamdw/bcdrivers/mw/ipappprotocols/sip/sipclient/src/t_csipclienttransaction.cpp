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


// This contains CT_DataSIPClientTransaction

#include "t_csipclienttransaction.h"
#include "t_csiprefresh.h"
#include "t_csipresponseelements.h"
#include "T_SIPUtil.h"
#include <utf.h> 

/*@{*/
_LIT(KCmdCancelAllowed,						"CancelAllowed");
_LIT(KCmdCancelL,                           "CancelL");
_LIT(KCmdRefresh,                           "Refresh");
_LIT(KCmdResponseElements,                  "ResponseElements");
_LIT(KCmdDestructor,                        "~");

_LIT(KFldSIPClientTransaction,              "sipclienttransaction");
_LIT(KFldSIPRefresh,                        "siprefresh");
_LIT(KFldSIPResponseElements,               "sipresponseelements");
_LIT(KFldExpected,                          "expected");

_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,                  "Not expected value, actual=%d, expect=%d");
/*}@*/


CT_DataSIPClientTransaction*  CT_DataSIPClientTransaction::NewL()
    {
    CT_DataSIPClientTransaction* self = new (ELeave) CT_DataSIPClientTransaction();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPClientTransaction::~CT_DataSIPClientTransaction()
    {
    DestroyData();
    }

CT_DataSIPClientTransaction::CT_DataSIPClientTransaction()
:   CT_DataSIPTransactionBase(), iSIPClientTransaction(NULL), iIsOwner(ETrue)
	{
	}

void CT_DataSIPClientTransaction::ConstructL()
    {
    }

TAny* CT_DataSIPClientTransaction::GetObject()
    {
    return iSIPClientTransaction;
    }

void CT_DataSIPClientTransaction::SetObjectL(TAny* aAny)
    {
    iSIPClientTransaction = static_cast<CSIPClientTransaction*>(aAny);
    }

void CT_DataSIPClientTransaction::DisownObjectL()
    {
    iSIPClientTransaction = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPClientTransaction::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

void CT_DataSIPClientTransaction::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPClientTransaction;
        iSIPClientTransaction = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPTransactionBase* CT_DataSIPClientTransaction::GetSIPTransactionBaseObject() const
    {
    return iSIPClientTransaction;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPClientTransaction::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	TBool	retVal = ETrue;

    if( aCommand == KCmdCancelAllowed )
        {
        DoCmdCancelAllowed(aSection);
        }
    else if( aCommand == KCmdCancelL)
        {
        DoCmdCancelL(aSection);
        }
    else if( aCommand == KCmdRefresh)
        {
        DoCmdRefreshL(aSection);
        }
    else if( aCommand == KCmdResponseElements)
        {
        DoCmdResponseElementsL(aSection);
        }
    else if( aCommand == KCmdDestructor)
        {
        DoCmdDestructor(aSection);
        }
	else
		{
		retVal = CT_DataSIPTransactionBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
		}
	return retVal;  
	}

void CT_DataSIPClientTransaction::DoCmdCancelAllowed(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPClientTransaction::CancelAllowed()"));
    TBool ret = iSIPClientTransaction->CancelAllowed();
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

void CT_DataSIPClientTransaction::DoCmdCancelL(const TTEFSectionName& aSection)
    {
    TPtrC wrapperName;
    if( !GetStringFromConfig(aSection, KFldSIPClientTransaction, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPClientTransaction);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPClientTransaction::CancelL()"));
        CSIPClientTransaction* ret = NULL;
        TRAPD(err, ret = iSIPClientTransaction->CancelL());
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            SetDataObjectL(wrapperName, ret);
            }
        }
    }

void CT_DataSIPClientTransaction::DoCmdRefreshL(const TTEFSectionName& aSection)
    {
    TPtrC wrapperName;
    if( !GetStringFromConfig(aSection, KFldSIPRefresh, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPRefresh);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPClientTransaction::Refresh()"));
        const CSIPRefresh* ret = ((const CSIPClientTransaction*)iSIPClientTransaction)->Refresh();

        CT_DataSIPRefresh* wrapper = static_cast<CT_DataSIPRefresh*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, (CSIPRefresh*)ret);
        }
    }

void CT_DataSIPClientTransaction::DoCmdResponseElementsL(const TTEFSectionName& aSection)
    {
    TPtrC wrapperName;
    if( !GetStringFromConfig(aSection, KFldSIPResponseElements, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPResponseElements);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPClientTransaction::ResponseElements()"));
        const CSIPResponseElements* ret = iSIPClientTransaction->ResponseElements();
        
        CT_DataSIPResponseElements* wrapper = static_cast<CT_DataSIPResponseElements*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, (CSIPResponseElements*)ret);
        }
    }

void CT_DataSIPClientTransaction::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPClientTransaction::~CSIPClientTransaction()"));
    DestroyData();
    }

