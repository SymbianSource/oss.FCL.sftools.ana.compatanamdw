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


// This contains CT_DataSIPNotifyDialogAssoc

#include "t_csipnotifydialogassoc.h"
#include "t_csipeventheader.h"
#include "t_csipsubscriptionstateheader.h"
#include "t_csipmessageelements.h"
#include "T_SIPUtil.h"
#include <sipclienttransaction.h>
#include <sipregistrationcontext.h> 


/*@{*/
_LIT(KCmdNewL,						        "NewL");
_LIT(KCmdNewLC,                             "NewLC");
_LIT(KCmdEvent,                             "Event");
_LIT(KCmdSendNotifyL,                       "SendNotifyL");
_LIT(KCmdSubscriptionState,                 "SubscriptionState");
_LIT(KCmdDestructor,                        "~");


_LIT(KFldSIPServerTransaction,              "ServerTransaction");
_LIT(KFldSIPEventHeader,                    "EventHeader");
_LIT(KFldSIPSubscriptionStateHeader,        "SubscriptionStateHeader");
_LIT(KFldSIPRegistrationContext,            "RegistrationContext");
_LIT(KFldSIPMessageElements,                "MessageElements");
_LIT(KFldSIPClientTransaction,              "ClientTransaction");
_LIT(KFldBeConst,                           "beconst");
//_LIT(KFldExpected,                          "expected");

_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
//_LIT(KLogNotExpectedValue,                  "Not expected value, actual=%d, expect=%d");
/*}@*/


CT_DataSIPNotifyDialogAssoc*  CT_DataSIPNotifyDialogAssoc::NewL()
    {
    CT_DataSIPNotifyDialogAssoc* self = new (ELeave) CT_DataSIPNotifyDialogAssoc();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPNotifyDialogAssoc::~CT_DataSIPNotifyDialogAssoc()
    {
    DestroyData();
    }

CT_DataSIPNotifyDialogAssoc::CT_DataSIPNotifyDialogAssoc()
:   CT_DataSIPDialogAssocBase(), iSIPNotifyDialogAssoc(NULL), iIsOwner(ETrue)
	{
	}

void CT_DataSIPNotifyDialogAssoc::ConstructL()
    {
    }

TAny* CT_DataSIPNotifyDialogAssoc::GetObject()
    {
    return iSIPNotifyDialogAssoc;
    }

void CT_DataSIPNotifyDialogAssoc::SetObjectL(TAny* aAny)
    {
    iSIPNotifyDialogAssoc = static_cast<CSIPNotifyDialogAssoc*>(aAny);
    }

void CT_DataSIPNotifyDialogAssoc::DisownObjectL()
    {
    iSIPNotifyDialogAssoc = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPNotifyDialogAssoc::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

void CT_DataSIPNotifyDialogAssoc::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPNotifyDialogAssoc;
        iSIPNotifyDialogAssoc = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPDialogAssocBase* CT_DataSIPNotifyDialogAssoc::GetSIPDialogAssocBase() const
    {
    return iSIPNotifyDialogAssoc;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPNotifyDialogAssoc::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	TBool	retVal = ETrue;

    if( aCommand == KCmdNewL )
        {
        DoCmdNewL(aSection);
        }
    else if( aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if( aCommand == KCmdEvent)
        {
        DoCmdEvent(aSection);
        }
    else if( aCommand == KCmdSendNotifyL)
        {
        DoCmdSendNotifyL(aSection);
        }
    else if( aCommand == KCmdSubscriptionState)
        {
        DoCmdSubscriptionState(aSection);
        }
    else if( aCommand == KCmdDestructor)
        {
        DoCmdDestructor(aSection);
        }
	else
		{
		retVal = CT_DataSIPDialogAssocBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);;
		}
	return retVal;  
	}

void CT_DataSIPNotifyDialogAssoc::DoCmdNewL(const TTEFSectionName& aSection)
    {
    TBool dataOK = ETrue;
    
    TPtrC strServerTransaction;
    TPtrC strEventHeader;
    TPtrC strSubscriptionStateHeader;
    if(!GetStringFromConfig(aSection, KFldSIPServerTransaction, strServerTransaction))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPServerTransaction());
        dataOK = EFalse;
        }
    if(!GetStringFromConfig(aSection, KFldSIPEventHeader, strEventHeader))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPEventHeader());
        dataOK = EFalse;
        }
    if(!GetStringFromConfig(aSection, KFldSIPSubscriptionStateHeader, strSubscriptionStateHeader))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPSubscriptionStateHeader());
        dataOK = EFalse;
        }
    
    if(dataOK == EFalse)
        {
        SetBlockResult(EFail);
        return;
        }
    
    CSIPServerTransaction* serverTransaction = static_cast<CSIPServerTransaction*>(GetDataObjectL(strServerTransaction));
    CSIPEventHeader* eventHeader = static_cast<CSIPEventHeader*>(GetDataObjectL(strEventHeader));
    CSIPSubscriptionStateHeader* subscriptionStateHeader = static_cast<CSIPSubscriptionStateHeader*>(GetDataObjectL(strSubscriptionStateHeader));
    
    TPtrC strSIPRegistrationContext;
    TInt err = KErrNone;
    if(GetStringFromConfig(aSection, KFldSIPRegistrationContext, strSIPRegistrationContext))
        {
        INFO_PRINTF1(_L("call CSIPNotifyDialogAssoc::NewL(CSIPServerTransaction&, const MSIPRegistrationContext&, CSIPEventHeader*, CSIPSubscriptionStateHeader*)"));
        MSIPRegistrationContext* registrationContext = static_cast<MSIPRegistrationContext*>(GetDataObjectL(strSIPRegistrationContext));
        TRAP(err, iSIPNotifyDialogAssoc = CSIPNotifyDialogAssoc::NewL(*serverTransaction, *registrationContext, eventHeader, subscriptionStateHeader));
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPNotifyDialogAssoc::NewL(CSIPServerTransaction&, CSIPEventHeader*, CSIPSubscriptionStateHeader*)"));
        TRAP(err, iSIPNotifyDialogAssoc = CSIPNotifyDialogAssoc::NewL(*serverTransaction, eventHeader, subscriptionStateHeader));
        }
    
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        CT_DataSIPEventHeader* eventHeaderWrapper = static_cast<CT_DataSIPEventHeader*>(GetDataWrapperL(strEventHeader));
        eventHeaderWrapper->SetIsOwner(EFalse);

        CT_DataSIPSubscriptionStateHeader* subscriptionStateHeaderWrapper = static_cast<CT_DataSIPSubscriptionStateHeader*>(GetDataWrapperL(strSubscriptionStateHeader));
        subscriptionStateHeaderWrapper->SetIsOwner(EFalse);
        }
    }

void CT_DataSIPNotifyDialogAssoc::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TBool dataOK = ETrue;
     
     TPtrC strServerTransaction;
     TPtrC strEventHeader;
     TPtrC strSubscriptionStateHeader;
     if(!GetStringFromConfig(aSection, KFldSIPServerTransaction, strServerTransaction))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldSIPServerTransaction());
         dataOK = EFalse;
         }
     if(!GetStringFromConfig(aSection, KFldSIPEventHeader, strEventHeader))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldSIPEventHeader());
         dataOK = EFalse;
         }
     if(!GetStringFromConfig(aSection, KFldSIPSubscriptionStateHeader, strSubscriptionStateHeader))
         {
         ERR_PRINTF2(KLogMissingParameter, &KFldSIPSubscriptionStateHeader());
         dataOK = EFalse;
         }
     
     if(dataOK == EFalse)
         {
         SetBlockResult(EFail);
         return;
         }
     
     CSIPServerTransaction* serverTransaction = static_cast<CSIPServerTransaction*>(GetDataObjectL(strServerTransaction));
     CSIPEventHeader* eventHeader = static_cast<CSIPEventHeader*>(GetDataObjectL(strEventHeader));
     CSIPSubscriptionStateHeader* subscriptionStateHeader = static_cast<CSIPSubscriptionStateHeader*>(GetDataObjectL(strSubscriptionStateHeader));
     
     TPtrC strSIPRegistrationContext;
     TInt err = KErrNone;
     if(GetStringFromConfig(aSection, KFldSIPRegistrationContext, strSIPRegistrationContext))
         {
         INFO_PRINTF1(_L("call CSIPNotifyDialogAssoc::NewLC(CSIPServerTransaction&, const MSIPRegistrationContext&, CSIPEventHeader*, CSIPSubscriptionStateHeader*)"));
         MSIPRegistrationContext* registrationContext = static_cast<MSIPRegistrationContext*>(GetDataObjectL(strSIPRegistrationContext));
         TRAP(err, iSIPNotifyDialogAssoc = CSIPNotifyDialogAssoc::NewLC(*serverTransaction, *registrationContext, eventHeader, subscriptionStateHeader); CleanupStack::Pop(iSIPNotifyDialogAssoc));
         }
     else
         {
         INFO_PRINTF1(_L("call CSIPNotifyDialogAssoc::NewLC(CSIPServerTransaction&, CSIPEventHeader*, CSIPSubscriptionStateHeader*)"));
         TRAP(err, iSIPNotifyDialogAssoc = CSIPNotifyDialogAssoc::NewLC(*serverTransaction, eventHeader, subscriptionStateHeader); CleanupStack::Pop(iSIPNotifyDialogAssoc));
         }
     
     if(err != KErrNone)
         {
         ERR_PRINTF2(KLogError, err);
         SetError(err);
         }
     else
         {
         CT_DataSIPEventHeader* eventHeaderWrapper = static_cast<CT_DataSIPEventHeader*>(GetDataWrapperL(strEventHeader));
         eventHeaderWrapper->SetIsOwner(EFalse);

         CT_DataSIPSubscriptionStateHeader* subscriptionStateHeaderWrapper = static_cast<CT_DataSIPSubscriptionStateHeader*>(GetDataWrapperL(strSubscriptionStateHeader));
         subscriptionStateHeaderWrapper->SetIsOwner(EFalse);
         }
    }

void CT_DataSIPNotifyDialogAssoc::DoCmdEvent(const TTEFSectionName& aSection)
    {
    TPtrC strSIPEventHeader;
    if(!GetStringFromConfig(aSection, KFldSIPEventHeader, strSIPEventHeader))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPEventHeader());
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("call CSIPNotifyDialogAssoc::Event()"));
    const CSIPEventHeader& eventHeader = iSIPNotifyDialogAssoc->Event();
    SetDataObjectL(strSIPEventHeader, const_cast<CSIPEventHeader*>(&eventHeader));
    
    CT_DataSIPEventHeader* wrapper = static_cast<CT_DataSIPEventHeader*>(GetDataWrapperL(strSIPEventHeader));
    wrapper->SetIsOwner(EFalse);
    }

void CT_DataSIPNotifyDialogAssoc::DoCmdSendNotifyL(const TTEFSectionName& aSection)
    {
    CSIPMessageElements* messageElements = NULL;
    CSIPClientTransaction* clientTransaction = NULL;
    TPtrC strSIPMessageElements;
    TInt err = KErrNone;
    if(GetStringFromConfig(aSection, KFldSIPMessageElements, strSIPMessageElements))
        {
        INFO_PRINTF1(_L("call CSIPNotifyDialogAssoc::(CSIPMessageElements *aElements)"));
        messageElements = static_cast<CSIPMessageElements*>(GetDataObjectL(strSIPMessageElements));
        TRAP(err, clientTransaction = iSIPNotifyDialogAssoc->SendNotifyL(messageElements));
        
        CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*>(GetDataWrapperL(strSIPMessageElements));
        wrapper->SetIsOwner(EFalse);
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPNotifyDialogAssoc::(CSIPMessageElements *aElements=0)"));
        TRAP(err, clientTransaction = iSIPNotifyDialogAssoc->SendNotifyL());
        }
    
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    
    TPtrC strClientTransaction;
    if(GetStringFromConfig(aSection, KFldSIPClientTransaction, strClientTransaction))
        {
        SetDataObjectL(strClientTransaction, clientTransaction);
        }
    else
        {
        delete clientTransaction;
        }
    }

void CT_DataSIPNotifyDialogAssoc::DoCmdSubscriptionState(const TTEFSectionName& aSection)
    {
    TPtrC strSubscriptionStateHeader;
    if(!GetStringFromConfig(aSection, KFldSIPSubscriptionStateHeader, strSubscriptionStateHeader))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPSubscriptionStateHeader());
        SetBlockResult(EFail);
        return;
        }
    
    TBool beConst = EFalse;
    if(GetBoolFromConfig(aSection, KFldBeConst, beConst) && beConst )
        {
        INFO_PRINTF1(_L("call const CSIPSubscriptionStateHeader& CSIPNotifyDialogAssoc::SubscriptionState() const"));
        const CSIPSubscriptionStateHeader& subscriptionState = iSIPNotifyDialogAssoc->SubscriptionState();
        SetDataObjectL(strSubscriptionStateHeader, const_cast<CSIPSubscriptionStateHeader*>(&subscriptionState));
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPSubscriptionStateHeader& CSIPNotifyDialogAssoc::SubscriptionState()"));
        CSIPSubscriptionStateHeader& subscriptionState = iSIPNotifyDialogAssoc->SubscriptionState();
        SetDataObjectL(strSubscriptionStateHeader, &subscriptionState);
        }
    }

void CT_DataSIPNotifyDialogAssoc::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPNotifyDialogAssoc::~CSIPNotifyDialogAssoc()"));
    DestroyData();
    }

