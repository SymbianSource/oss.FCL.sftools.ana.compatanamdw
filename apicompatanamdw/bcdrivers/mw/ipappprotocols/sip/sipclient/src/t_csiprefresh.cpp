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

#include "t_csiprefresh.h"
#include "T_SIPUtil.h"
#include <siprefresh.h>
#include <sipmessageelements.h>
#include "t_csipclienttransaction.h"
#include "t_csipmessageelements.h"

// Command
_LIT(KCmdIntervalL,            "IntervalL");
_LIT(KCmdIsStandAlone,         "IsStandAlone");
_LIT(KCmdNewL,                 "NewL");
_LIT(KCmdNewLC,                "NewLC");
_LIT(KCmdSIPTransaction,       "SIPTransaction");
_LIT(KCmdSetIntervalL,         "SetIntervalL");
_LIT(KCmdState,                "State");
_LIT(KCmdTerminateL,           "TerminateL");
_LIT(KCmdUpdateL,               "UpdateL");
_LIT(KCmdOperatorEqual,         "==");
_LIT(KCmdDestructor,           "~");

// Field
_LIT(KFldExpected,              "expected");
_LIT(KFldTransaction,       "transaction");
_LIT(KFldMessageElements,   "msgelems");
_LIT(KFldSIPRefresh,        "siprefresh");
_LIT(KFldInterval,          "interval");


// Error
_LIT(KLogError, "Error=%d");
_LIT(KMissingParameter, "missing parameter '%S'");

CT_DataSIPRefresh* CT_DataSIPRefresh::NewL()
    {
    CT_DataSIPRefresh* self = new (ELeave) CT_DataSIPRefresh();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CT_DataSIPRefresh::~CT_DataSIPRefresh()
    {
    DestroyData();
    }

CT_DataSIPRefresh::CT_DataSIPRefresh() :
    CDataWrapperBase(),iRefresh(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPRefresh::ConstructL()
    {

    }

void CT_DataSIPRefresh::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }

void CT_DataSIPRefresh::DestroyData()
    {
    if (iIsOwner)
        {
        delete iRefresh;
        iRefresh = NULL;
        iIsOwner = EFalse;    
        }    
    }

TAny* CT_DataSIPRefresh::GetObject()
    {
    return iRefresh;
    }

void CT_DataSIPRefresh::SetObjectL(TAny* aAny)
    {
    DestroyData();
    iRefresh = static_cast<CSIPRefresh*> (aAny);
    }

void CT_DataSIPRefresh::DisownObjectL()
    {
    iRefresh = NULL;
    iIsOwner = EFalse;
    }

TBool CT_DataSIPRefresh::DoCommandL(const TTEFFunction& aCommand,
        const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
    {
    TBool ret = ETrue;
    if (aCommand == KCmdIntervalL)
        {
        DoCmdIntervalL(aSection);
        }
    else if (aCommand == KCmdIsStandAlone)
        {
        DoCmdIsStandAlone(aSection);
        }
    else if (aCommand == KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if (aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if (aCommand == KCmdSIPTransaction)
        {
        DoCmdSIPTransactionL(aSection);
        }
    else if (aCommand == KCmdSetIntervalL)
        {
        DoCmdSetIntervalL(aSection);
        }
    else if (aCommand == KCmdState)
        {
        DoCmdState(aSection);
        }
    else if (aCommand == KCmdTerminateL)
        {
        DoCmdTerminateL(aSection);
        }
    else if (aCommand == KCmdUpdateL)
        {
        DoCmdUpdateL(aSection);
        }
    else if (aCommand == KCmdOperatorEqual)
        {
        DoCmdOperatorEqualL(aSection);
        }
    else if (aCommand == KCmdDestructor)
        {
        DoCmdDestructor(aSection);
        }
    else
        {
        ret = EFalse;
        }
    return ret;
    }

void CT_DataSIPRefresh::DoCmdIntervalL(const TTEFSectionName& aSection)
    {
    TUint actual;
    INFO_PRINTF1(_L("execute CSIPRefresh::IntervalL()"));
    TRAPD(err, actual = iRefresh->IntervalL());
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        INFO_PRINTF2(_L("Interval: %u"), actual);

        TUint expected;
        if (GetTUintFromConfig(aSection, KFldExpected, expected))
            {
            if (actual != expected)
                {
                ERR_PRINTF3(_L("actual value is not as expected, expected: %u, actual: %u"), expected, actual);
                SetBlockResult(EFail);
                }
            }
        }
    }

void CT_DataSIPRefresh::DoCmdIsStandAlone(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPRefresh::IsStandAlone()"));
    TBool actual = iRefresh->IsStandAlone();
    INFO_PRINTF2(_L("Is standalone: %d"), actual);
    
    TBool expected;
    if (GetBoolFromConfig(aSection, KFldExpected, expected))
        {
        if (!actual != !expected)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected: %d, actual: %d"), (TInt)expected, (TInt)actual);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPRefresh::DoCmdNewL(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("execute CSIPRefresh::NewL()"));
    TRAPD(err, iRefresh = CSIPRefresh::NewL());
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        iIsOwner = ETrue;
        }
    }

void CT_DataSIPRefresh::DoCmdNewLC(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("execute CSIPRefresh::NewLC()"));
    TRAPD(err, iRefresh = CSIPRefresh::NewLC(); CleanupStack::Pop(iRefresh));
    if (err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        iIsOwner = ETrue;
        }
    }

void CT_DataSIPRefresh::DoCmdSIPTransactionL(const TTEFSectionName& aSection)
    {
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldTransaction, name))
        {
        INFO_PRINTF1(_L("execute CSIPRefresh::SIPTransaction()"));
        const CSIPClientTransaction* actual = iRefresh->SIPTransaction();
        
        if (actual != NULL)
            {
            CT_DataSIPClientTransaction* wrapper = static_cast<CT_DataSIPClientTransaction*> (GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            SetDataObjectL(name, (void*) actual);
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldTransaction());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRefresh::DoCmdSetIntervalL(const TTEFSectionName& aSection)
    {
    TUint interval;
    if (GetTUintFromConfig(aSection, KFldInterval, interval))
        {
        INFO_PRINTF1(_L("execute CSIPRefresh::SetIntervalL(TUint)"));
        TRAPD(err, iRefresh->SetIntervalL(interval));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldInterval());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRefresh::DoCmdState(const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPRefresh::State()"));
    CSIPRefresh::TState actual = iRefresh->State();
    INFO_PRINTF2(_L("State: %d"), (TInt)actual);
    
    CSIPRefresh::TState expected;
    if (CT_SIPUtil::GetSIPRefreshState(*this, aSection, KFldExpected, expected))
        {
        if (actual != expected)
            {
            ERR_PRINTF3(_L("actual value is not as expected, expected State: %d, actual State: %d"), (TInt)expected, (TInt)actual);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPRefresh::DoCmdTerminateL(const TTEFSectionName& aSection)
    {
    CSIPMessageElements* msgElems = NULL;
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldTransaction, name))
        {
        CSIPClientTransaction* transaction;
        // No need to check return value 'cause default parameter of TerminateL is NULL.
        (void) CT_SIPUtil::GetSIPMessageElements(*this, aSection, KFldMessageElements, msgElems);
        INFO_PRINTF1(_L("execute CSIPRefresh::TerminateL(CSIPMessageElements *)"));
        TRAPD(err, transaction = iRefresh->TerminateL(msgElems));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            if (transaction != NULL)
                {
                CT_DataSIPClientTransaction* wrapper = static_cast<CT_DataSIPClientTransaction*>(GetDataWrapperL(name));
                wrapper->SetIsOwner(ETrue);
                SetDataObjectL(name, transaction);
                }
            TPtrC msgElemsName;
            if (GetStringFromConfig(aSection, KFldMessageElements, msgElemsName))
                {
                CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*>(GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldTransaction());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRefresh::DoCmdUpdateL(const TTEFSectionName& aSection)
    {
    CSIPMessageElements* msgElems = NULL;
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldTransaction, name))
        {
        CSIPClientTransaction* transaction;
        (void) CT_SIPUtil::GetSIPMessageElements(*this, aSection, KFldMessageElements, msgElems);
        INFO_PRINTF1(_L("execute CSIPRefresh::UpdateL(CSIPMessageElements *)"));
        TRAPD(err, transaction = iRefresh->UpdateL(msgElems));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            if (transaction != NULL)
                {
                CT_DataSIPClientTransaction* wrapper = static_cast<CT_DataSIPClientTransaction*>(GetDataWrapperL(name));
                wrapper->SetIsOwner(ETrue);
                SetDataObjectL(name, transaction);
                }
            TPtrC msgElemsName;
            if (GetStringFromConfig(aSection, KFldMessageElements, msgElemsName))
                {
                CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*>(GetDataWrapperL(msgElemsName));
                wrapper->SetIsOwner(EFalse);
                }
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldTransaction());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRefresh::DoCmdOperatorEqualL(const TTEFSectionName& aSection)
    {
    CSIPRefresh* sipRefresh;
    if (CT_SIPUtil::GetSIPRefreshL(*this, aSection, KFldSIPRefresh, sipRefresh))
        {
        INFO_PRINTF1(_L("execute CSIPRefresh::operator==(const CSIPRefresh &)"));
        TBool actual = (*iRefresh) == (*sipRefresh);
        INFO_PRINTF2(_L("operator==() = %d"), actual);
        
        TBool expected;
        if (GetBoolFromConfig(aSection, KFldExpected, expected))
            {
            if (!expected != !actual)
                {
                ERR_PRINTF3(_L("actual value is not as expected, expected: %d, actual: %d"), expected, actual);
                SetBlockResult(EFail);
                }
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldSIPRefresh());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRefresh::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("execute CSIPRefresh::~CSIPRefresh()"));
    DestroyData();
    }
