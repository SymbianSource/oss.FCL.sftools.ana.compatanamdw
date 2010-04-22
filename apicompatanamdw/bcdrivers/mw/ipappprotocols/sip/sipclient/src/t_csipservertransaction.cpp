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


// This contains CT_DataSIPServerTransaction

#include "t_csipservertransaction.h"
#include "t_csiprequestelements.h"
#include "t_csipresponseelements.h"
#include "T_SIPUtil.h"
#include <utf.h> 

/*@{*/
_LIT(KCmdRequestElements,					"RequestElements");
_LIT(KCmdResponseAllowed,                   "ResponseAllowed");
_LIT(KCmdSendResponseL,                     "SendResponseL");
_LIT(KCmdDestructor,                        "~");

_LIT(KFldExpected,                          "expected");
_LIT(KFldSIPResponseElements,               "sipresponseelements");
_LIT(KFldSIPRequestElements,                "siprequestelements");

_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,                  "Not expected value, actual=%d, expect=%d");
/*}@*/


CT_DataSIPServerTransaction*  CT_DataSIPServerTransaction::NewL()
    {
    CT_DataSIPServerTransaction* self = new (ELeave) CT_DataSIPServerTransaction();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPServerTransaction::~CT_DataSIPServerTransaction()
    {
    DestroyData();
    }

CT_DataSIPServerTransaction::CT_DataSIPServerTransaction()
:   CT_DataSIPTransactionBase(), iSIPServerTransaction(NULL)
	{
	}

void CT_DataSIPServerTransaction::ConstructL()
    {
    }

TAny* CT_DataSIPServerTransaction::GetObject()
    {
    return iSIPServerTransaction;
    }

void CT_DataSIPServerTransaction::SetObjectL(TAny* aAny)
    {
    iSIPServerTransaction = static_cast<CSIPServerTransaction*>(aAny);
    }

void CT_DataSIPServerTransaction::DisownObjectL()
    {
    iSIPServerTransaction = NULL;
    }

void CT_DataSIPServerTransaction::DestroyData()
    {
    delete iSIPServerTransaction;
    iSIPServerTransaction = NULL;  
    }

CSIPTransactionBase* CT_DataSIPServerTransaction::GetSIPTransactionBaseObject() const
    {
    return iSIPServerTransaction;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPServerTransaction::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	TBool	retVal = ETrue;

	if( aCommand == KCmdRequestElements)
	    {
	    DoCmdRequestElementsL(aSection);
	    }
	else if( aCommand == KCmdResponseAllowed )
        {
        DoCmdResponseAllowed(aSection);
        }
	else if( aCommand == KCmdSendResponseL)
        {
        DoCmdSendResponseL(aSection);
        }
	else if( aCommand == KCmdDestructor )
        {
        DoCmdDestructor(aSection);
        }
	else
		{
		retVal = CT_DataSIPTransactionBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
		}
	return retVal;  
	}

void CT_DataSIPServerTransaction::DoCmdRequestElementsL(const TTEFSectionName& aSection)
    {
    TPtrC wrapperName;
    if( !GetStringFromConfig(aSection, KFldSIPRequestElements, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPRequestElements);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPServerTransaction::RequestElements()"));
        const CSIPRequestElements* ret = iSIPServerTransaction->RequestElements();
        
        CT_DataSIPRequestElements* wrapper = static_cast<CT_DataSIPRequestElements*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, (CSIPRequestElements*)ret);
        }
    }

void CT_DataSIPServerTransaction::DoCmdResponseAllowed(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("call CSIPServerTransaction::ResponseAllowed()"));
    TBool ret = iSIPServerTransaction->ResponseAllowed();
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

void CT_DataSIPServerTransaction::DoCmdSendResponseL(const TTEFSectionName& aSection)
    {
    CSIPResponseElements* elem = NULL;
    if( !CT_SIPUtil::GetSIPResponseElements(*this, aSection, KFldSIPResponseElements, elem) )
        {
        ERR_PRINTF2(KLogMissingParameter, KFldSIPResponseElements);
        SetBlockResult(EFail);        
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPServerTransaction::SendResponseL(CSIPResponseElements*)"));        
        TRAPD(err, iSIPServerTransaction->SendResponseL(elem));
        TPtrC name;
        GetStringFromConfig(aSection, KFldSIPResponseElements, name);
        CT_DataSIPResponseElements* wrapper = static_cast<CT_DataSIPResponseElements*> (GetDataWrapperL(name));
        wrapper->SetIsOwner(EFalse);
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }        
        }
    }

void CT_DataSIPServerTransaction::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPServerTransaction::~CSIPServerTransaction()"));
    DestroyData();
    }

