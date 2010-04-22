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


#include "t_csipsubscribedialogassoc.h"
#include "t_csipeventheader.h"
#include "t_csiptoheader.h"
#include "t_csipfromheader.h"
#include "t_csipcontactheader.h"
#include "t_csipmessageelements.h"
#include "t_csiprefresh.h"
#include "T_SIPUtil.h"
#include <sipclienttransaction.h>
#include <sipregistrationcontext.h> 
/*@{*/
_LIT(KCmdNewL,                              "NewL");
_LIT(KCmdNewLC,                             "NewLC");
_LIT(KCmdEvent,                             "Event");
_LIT(KCmdSIPRefresh,                        "SIPRefresh");
_LIT(KCmdSendSubscribeL,                    "SendSubscribeL");
_LIT(KCmdSendUnsubscribeL,                  "SendUnsubscribeL");
_LIT(KCmdUpdateL,                           "UpdateL");
_LIT(KCmdDestructor,                        "~");


_LIT(KFldSIPConnection,                     "Connection");
_LIT(KFldUri8,                               "Uri8");
_LIT(KFldSIPFromHeader,                     "FromHeader");
_LIT(KFldSIPToHeader,                       "ToHeader");
_LIT(KFldSIPContactHeader,                  "ContactHeader");
_LIT(KFldSIPEventHeader,                    "EventHeader");
_LIT(KFldSIPRefresh,                        "SIPRefresh");
_LIT(KFldSIPRegistrationContext,            "RegistrationContext");
_LIT(KFldSIPDialog,                         "Dialog");
_LIT(KFldSIPMessageElements,                "MessageElements");
_LIT(KFldSIPClientTransaction,              "ClientTransaction");
//_LIT(KFldBeConst,                           "beconst");
//_LIT(KFldExpected,                          "expected");

_LIT(KLogError,                             "Error=%d");
_LIT(KLogMissingParameter,                  "Missing parameter '%S'");
//_LIT(KLogNotExpectedValue,                  "Not expected value, actual=%d, expect=%d");
/*}@*/


CT_DataSIPSubscribeDialogAssoc*  CT_DataSIPSubscribeDialogAssoc::NewL()
    {
    CT_DataSIPSubscribeDialogAssoc* self = new (ELeave) CT_DataSIPSubscribeDialogAssoc();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;    
    }

CT_DataSIPSubscribeDialogAssoc::~CT_DataSIPSubscribeDialogAssoc()
    {
    DestroyData();
    }

CT_DataSIPSubscribeDialogAssoc::CT_DataSIPSubscribeDialogAssoc()
:   CT_DataSIPDialogAssocBase(), iSIPSubscribeDialogAssoc(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPSubscribeDialogAssoc::ConstructL()
    {
    }

TAny* CT_DataSIPSubscribeDialogAssoc::GetObject()
    {
    return iSIPSubscribeDialogAssoc;
    }

void CT_DataSIPSubscribeDialogAssoc::SetObjectL(TAny* aAny)
    {
    iSIPSubscribeDialogAssoc = static_cast<CSIPSubscribeDialogAssoc*>(aAny);
    }

void CT_DataSIPSubscribeDialogAssoc::DisownObjectL()
    {
    iSIPSubscribeDialogAssoc = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPSubscribeDialogAssoc::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

void CT_DataSIPSubscribeDialogAssoc::DestroyData()
    {
    if (iIsOwner)
        {
        delete iSIPSubscribeDialogAssoc;
        iSIPSubscribeDialogAssoc = NULL;
        iIsOwner = EFalse;
        }
    }

CSIPDialogAssocBase* CT_DataSIPSubscribeDialogAssoc::GetSIPDialogAssocBase() const
    {
    return iSIPSubscribeDialogAssoc;
    }

/**
Delegates the commands to a function

* @internalComponent
* @param aCommand Current command
* @param aSection Current ini file command section
* @param aAsyncErrorIndex index of command for SetAsyncError()
* @return TBool Returns whether the command was executed or not
*/
TBool CT_DataSIPSubscribeDialogAssoc::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool   retVal = ETrue;

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
    else if( aCommand == KCmdSIPRefresh)
        {
        DoCmdSIPRefresh(aSection);
        }
    else if( aCommand == KCmdSendSubscribeL)
        {
        DoCmdSendSubscribeL(aSection);
        }
    else if( aCommand == KCmdSendUnsubscribeL)
        {
        DoCmdSendUnsubscribeL(aSection);
        }
    else if( aCommand == KCmdUpdateL)
        {
        DoCmdUpdateL(aSection);
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

void CT_DataSIPSubscribeDialogAssoc::DoCmdNewL(const TTEFSectionName& aSection)
    {
    TInt err = KErrNone;
    TPtrC strSIPDialog;
    TPtrC strEventHeader;
    TPtrC strSIPConnection;
    TPtrC strSIPFromHeader;
    TPtrC strSIPToHeader;
    TPtrC strSIPContactHeader;
    TPtrC strSIPRegistrationContext;
    
    CSIPDialog* dialog = NULL;
    CUri8* uri8 = NULL;
    CSIPConnection* connection = NULL;
    CSIPFromHeader* fromHeader = NULL;
    CSIPToHeader* toHeader = NULL;
    CSIPEventHeader* eventHeader = NULL;
    CSIPContactHeader* contactHeader = NULL;
    
    if(!GetStringFromConfig(aSection, KFldSIPEventHeader, strEventHeader))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPEventHeader());
        SetBlockResult(EFail);
        return;
        }
    eventHeader = static_cast<CSIPEventHeader*>(GetDataObjectL(strEventHeader));
      
    if(GetStringFromConfig(aSection, KFldSIPDialog, strSIPDialog))
        {
        dialog = static_cast<CSIPDialog*>(GetDataObjectL(strSIPDialog));
        INFO_PRINTF1(_L("call CSIPSubscribeDialogAssoc::NewL(CSIPDialog &,CSIPEventHeader *)"));
        TRAP(err, iSIPSubscribeDialogAssoc = CSIPSubscribeDialogAssoc::NewL(*dialog, eventHeader));
        }
    else
        {
        TBool dataOK = ETrue;
        TBool hasSIPRegistrationContext = EFalse;
        
        if(GetStringFromConfig(aSection, KFldSIPRegistrationContext, strSIPRegistrationContext))
            {
            hasSIPRegistrationContext = ETrue;
            }
        
        if(!CT_SIPUtil::GetUri8L(*this, aSection, KFldUri8, uri8))
            {
            ERR_PRINTF2(KLogMissingParameter, &KFldUri8());
            dataOK = EFalse;
            }
        if(!GetStringFromConfig(aSection, KFldSIPConnection, strSIPConnection))
            {
            ERR_PRINTF2(KLogMissingParameter, &KFldSIPConnection());
            dataOK = EFalse;
            }
        else
            {
            connection = static_cast<CSIPConnection*>(GetDataObjectL(strSIPConnection));
            }
        
        if(!GetStringFromConfig(aSection, KFldSIPFromHeader, strSIPFromHeader))
            {
            if(hasSIPRegistrationContext)
                {
                INFO_PRINTF1(_L("CSIPFromHeader *aFrom=0"));
                }
            else
                {
                ERR_PRINTF2(KLogMissingParameter, &KFldSIPFromHeader());
                dataOK = EFalse;
                }
            }
        else
            {
            fromHeader = static_cast<CSIPFromHeader*>(GetDataObjectL(strSIPFromHeader));
            }
        
        if(!GetStringFromConfig(aSection, KFldSIPToHeader, strSIPToHeader))
            {
            INFO_PRINTF1(_L("CSIPToHeader *aTo=0"));
            }
        else
            {
            toHeader = static_cast<CSIPToHeader*>(GetDataObjectL(strSIPToHeader));
            }

        if(!GetStringFromConfig(aSection, KFldSIPContactHeader, strSIPContactHeader))
            {
            INFO_PRINTF1(_L("CSIPContactHeader *aContact=0"));
            }
        else
            {
            contactHeader = static_cast<CSIPContactHeader*>(GetDataObjectL(strSIPContactHeader));
            }
        
        if(dataOK == EFalse)
            {
            SetBlockResult(EFail);
            return;
            }
       
        if(hasSIPRegistrationContext)
            {
            INFO_PRINTF1(_L("call CSIPSubscribeDialogAssoc::NewL(CSIPConnection &,CUri8 *,const MSIPRegistrationContext &,CSIPEventHeader *,CSIPFromHeader *,CSIPToHeader *,CSIPContactHeader *)"));
            MSIPRegistrationContext* registrationContext = static_cast<MSIPRegistrationContext*>(GetDataObjectL(strSIPRegistrationContext));
            TRAP(err, iSIPSubscribeDialogAssoc = CSIPSubscribeDialogAssoc::NewL(*connection, uri8, *registrationContext, eventHeader, fromHeader, toHeader,contactHeader));
            }
        else
            {
            INFO_PRINTF1(_L("call CSIPSubscribeDialogAssoc::NewL(CSIPConnection &,CSIPFromHeader *,CUri8 *,CSIPEventHeader *,CSIPToHeader *,CSIPContactHeader *)"));
            TRAP(err, iSIPSubscribeDialogAssoc = CSIPSubscribeDialogAssoc::NewL(*connection, fromHeader, uri8, eventHeader, toHeader,contactHeader));
            }
        }
   
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        if(fromHeader)
            {
            CT_DataSIPFromHeader* fromHeaderWrapper = static_cast<CT_DataSIPFromHeader*>(GetDataWrapperL(strSIPFromHeader));
            fromHeaderWrapper->SetIsOwner(EFalse);
            }
        if(toHeader)
            {
            CT_DataSIPToHeader* toHeaderWrapper = static_cast<CT_DataSIPToHeader*>(GetDataWrapperL(strSIPToHeader));
            toHeaderWrapper->SetIsOwner(EFalse);
            }
        if(eventHeader)
            {
            CT_DataSIPEventHeader* eventHeaderWrapper = static_cast<CT_DataSIPEventHeader*>(GetDataWrapperL(strEventHeader));
            eventHeaderWrapper->SetIsOwner(EFalse);
            }
        if(contactHeader)
            {
            CT_DataSIPContactHeader* contactHeaderWrapper = static_cast<CT_DataSIPContactHeader*>(GetDataWrapperL(strSIPContactHeader));
            contactHeaderWrapper->SetIsOwner(EFalse);
            }
        }
    }

void CT_DataSIPSubscribeDialogAssoc::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TInt err = KErrNone;
    TPtrC strSIPDialog;
    TPtrC strEventHeader;
    TPtrC strSIPConnection;
    TPtrC strSIPFromHeader;
    TPtrC strSIPToHeader;
    //TPtrC strSIPEventHeader;
    TPtrC strSIPContactHeader;
    TPtrC strSIPRegistrationContext;
    
    CSIPDialog* dialog = NULL;
    CUri8* uri8 = NULL;
    CSIPConnection* connection = NULL;
    CSIPFromHeader* fromHeader = NULL;
    CSIPToHeader* toHeader = NULL;
    CSIPEventHeader* eventHeader = NULL;
    CSIPContactHeader* contactHeader = NULL;
    
    if(!GetStringFromConfig(aSection, KFldSIPEventHeader, strEventHeader))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPEventHeader());
        SetBlockResult(EFail);
        return;
        }
    eventHeader = static_cast<CSIPEventHeader*>(GetDataObjectL(strEventHeader));
      
    if(GetStringFromConfig(aSection, KFldSIPDialog, strSIPDialog))
        {
        dialog = static_cast<CSIPDialog*>(GetDataObjectL(strSIPDialog));
        INFO_PRINTF1(_L("call CSIPSubscribeDialogAssoc::NewLC(CSIPDialog &,CSIPEventHeader *)"));
        TRAP(err, iSIPSubscribeDialogAssoc = CSIPSubscribeDialogAssoc::NewLC(*dialog, eventHeader); CleanupStack::Pop(iSIPSubscribeDialogAssoc));
        }
    else
        {
        TBool dataOK = ETrue;
        TBool hasSIPRegistrationContext = EFalse;
        
        if(GetStringFromConfig(aSection, KFldSIPRegistrationContext, strSIPRegistrationContext))
            {
            hasSIPRegistrationContext = ETrue;
            }
        
        if(!CT_SIPUtil::GetUri8L(*this, aSection, KFldUri8, uri8))
            {
            ERR_PRINTF2(KLogMissingParameter, &KFldUri8());
            dataOK = EFalse;
            }
        if(!GetStringFromConfig(aSection, KFldSIPConnection, strSIPConnection))
            {
            ERR_PRINTF2(KLogMissingParameter, &KFldSIPConnection());
            dataOK = EFalse;
            }
        else
            {
            connection = static_cast<CSIPConnection*>(GetDataObjectL(strSIPConnection));
            }
         
        if(!GetStringFromConfig(aSection, KFldSIPFromHeader, strSIPFromHeader))
            {
            if(hasSIPRegistrationContext)
                {
                INFO_PRINTF1(_L("CSIPFromHeader *aFrom=0"));
                }
            else
                {
                ERR_PRINTF2(KLogMissingParameter, &KFldSIPFromHeader());
                dataOK = EFalse;
                }
            }
        else
            {
            fromHeader = static_cast<CSIPFromHeader*>(GetDataObjectL(strSIPFromHeader));
            }
        
        if(!GetStringFromConfig(aSection, KFldSIPToHeader, strSIPToHeader))
            {
            INFO_PRINTF1(_L("CSIPToHeader *aTo=0"));
            }
        else
            {
            toHeader = static_cast<CSIPToHeader*>(GetDataObjectL(strSIPToHeader));
            }

        if(!GetStringFromConfig(aSection, KFldSIPContactHeader, strSIPContactHeader))
            {
            INFO_PRINTF1(_L("CSIPContactHeader *aContact=0"));
            }
        else
            {
            contactHeader = static_cast<CSIPContactHeader*>(GetDataObjectL(strSIPContactHeader));
            }
        
        if(dataOK == EFalse)
            {
            SetBlockResult(EFail);
            return;
            }
       
        if(hasSIPRegistrationContext)
            {
            INFO_PRINTF1(_L("call CSIPSubscribeDialogAssoc::NewLC(CSIPConnection &,CUri8 *,const MSIPRegistrationContext &,CSIPEventHeader *,CSIPFromHeader *,CSIPToHeader *,CSIPContactHeader *)"));
            MSIPRegistrationContext* registrationContext = static_cast<MSIPRegistrationContext*>(GetDataObjectL(strSIPRegistrationContext));
            TRAP(err, iSIPSubscribeDialogAssoc = CSIPSubscribeDialogAssoc::NewLC(*connection, uri8, *registrationContext, eventHeader, fromHeader, toHeader,contactHeader); CleanupStack::Pop(iSIPSubscribeDialogAssoc));
            }
        else
            {
            INFO_PRINTF1(_L("call CSIPSubscribeDialogAssoc::NewLC(CSIPConnection &,CSIPFromHeader *,CUri8 *,CSIPEventHeader *,CSIPToHeader *,CSIPContactHeader *)"));
            TRAP(err, iSIPSubscribeDialogAssoc = CSIPSubscribeDialogAssoc::NewLC(*connection, fromHeader, uri8, eventHeader, toHeader,contactHeader); CleanupStack::Pop(iSIPSubscribeDialogAssoc));
            }
        }
   
    if(err != KErrNone)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        if(fromHeader)
            {
            CT_DataSIPFromHeader* fromHeaderWrapper = static_cast<CT_DataSIPFromHeader*>(GetDataWrapperL(strSIPFromHeader));
            fromHeaderWrapper->SetIsOwner(EFalse);
            }
        if(toHeader)
            {
            CT_DataSIPToHeader* toHeaderWrapper = static_cast<CT_DataSIPToHeader*>(GetDataWrapperL(strSIPToHeader));
            toHeaderWrapper->SetIsOwner(EFalse);
            }
        if(eventHeader)
            {
            CT_DataSIPEventHeader* eventHeaderWrapper = static_cast<CT_DataSIPEventHeader*>(GetDataWrapperL(strEventHeader));
            eventHeaderWrapper->SetIsOwner(EFalse);
            }
        if(contactHeader)
            {
            CT_DataSIPContactHeader* contactHeaderWrapper = static_cast<CT_DataSIPContactHeader*>(GetDataWrapperL(strSIPContactHeader));
            contactHeaderWrapper->SetIsOwner(EFalse);
            }
        }
    }

void CT_DataSIPSubscribeDialogAssoc::DoCmdEvent(const TTEFSectionName& aSection)
    {
    TPtrC strSIPEventHeader;
    if(!GetStringFromConfig(aSection, KFldSIPEventHeader, strSIPEventHeader))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPEventHeader());
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("call CSIPSubscribeDialogAssoc::Event()"));
    const CSIPEventHeader& eventHeader = iSIPSubscribeDialogAssoc->Event();
    SetDataObjectL(strSIPEventHeader, const_cast<CSIPEventHeader*>(&eventHeader));
    CT_DataSIPEventHeader* eventHeaderWrapper = static_cast<CT_DataSIPEventHeader*>(GetDataWrapperL(strSIPEventHeader));
    eventHeaderWrapper->SetIsOwner(EFalse);
    }

void CT_DataSIPSubscribeDialogAssoc::DoCmdSIPRefresh(const TTEFSectionName& aSection)
    {
    TPtrC strSIPRefresh;
    if(!GetStringFromConfig(aSection, KFldSIPRefresh, strSIPRefresh))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPRefresh());
        SetBlockResult(EFail);
        return;
        }
    INFO_PRINTF1(_L("call CSIPSubscribeDialogAssoc::SIPRefresh()"));
    const CSIPRefresh* refresh = iSIPSubscribeDialogAssoc->SIPRefresh();
    if(strSIPRefresh.Compare(_L("NULL")) == 0)
        {
        if(refresh == NULL)
            {
            INFO_PRINTF1(_L("The user has not requested a refresh."));
            }
        else
            {
            ERR_PRINTF1(_L("The refresh is not NULL as expected."));
            SetBlockResult(EFail);
            }
        }
    else
        {
        SetDataObjectL(strSIPRefresh, const_cast<CSIPRefresh*>(refresh));
        CT_DataSIPRefresh* wrapper = static_cast<CT_DataSIPRefresh*>(GetDataWrapperL(strSIPRefresh));
        wrapper->SetIsOwner(EFalse);
        }
    }

void CT_DataSIPSubscribeDialogAssoc::DoCmdUpdateL(const TTEFSectionName& aSection)
    {
    CSIPMessageElements* messageElements = NULL;
    CSIPClientTransaction* clientTransaction = NULL;
    TPtrC strSIPMessageElements;
    TInt err = KErrNone;
    if(!GetStringFromConfig(aSection, KFldSIPMessageElements, strSIPMessageElements))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPMessageElements());
        SetBlockResult(EFail);
        return;
        }

    INFO_PRINTF1(_L("call CSIPSubscribeDialogAssoc::UpdateL(CSIPMessageElements *aElements)"));
    messageElements = static_cast<CSIPMessageElements*>(GetDataObjectL(strSIPMessageElements));
    TRAP(err, clientTransaction = iSIPSubscribeDialogAssoc->UpdateL(messageElements));
    CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*>(GetDataWrapperL(strSIPMessageElements));
    wrapper->SetIsOwner(EFalse);
    
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

void CT_DataSIPSubscribeDialogAssoc::DoCmdSendSubscribeL(const TTEFSectionName& aSection)
    {
    CSIPMessageElements* messageElements = NULL;
    CSIPRefresh* refresh = NULL;
    CSIPClientTransaction* clientTransaction = NULL;
    TPtrC strSIPMessageElements;
    TPtrC strSIPRefresh;
    TInt err = KErrNone;

    if(!GetStringFromConfig(aSection, KFldSIPMessageElements, strSIPMessageElements))
        {
        INFO_PRINTF2(KLogMissingParameter, &KFldSIPMessageElements());
        }
    else
        {
        messageElements = static_cast<CSIPMessageElements*>(GetDataObjectL(strSIPMessageElements));
        }
        
    if(!GetStringFromConfig(aSection, KFldSIPRefresh, strSIPRefresh))
        {
        INFO_PRINTF2(KLogMissingParameter, &KFldSIPRefresh());
        }
    else
        {
        refresh = static_cast<CSIPRefresh*>(GetDataObjectL(strSIPRefresh));
        }

    INFO_PRINTF1(_L("call CSIPSubscribeDialogAssoc::SendSubscribeL(CSIPMessageElements *,CSIPRefresh *)"));
        
    TRAP(err, clientTransaction = iSIPSubscribeDialogAssoc->SendSubscribeL(messageElements,refresh));
    CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*>(GetDataWrapperL(strSIPMessageElements));
    wrapper->SetIsOwner(EFalse);
    
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

void CT_DataSIPSubscribeDialogAssoc::DoCmdSendUnsubscribeL(const TTEFSectionName& aSection)
    {
    CSIPMessageElements* messageElements = NULL;
    CSIPClientTransaction* clientTransaction = NULL;
    TPtrC strSIPMessageElements;
    TInt err = KErrNone;
    if(!GetStringFromConfig(aSection, KFldSIPMessageElements, strSIPMessageElements))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPMessageElements());
        SetBlockResult(EFail);
        return;
        }

    INFO_PRINTF1(_L("call CSIPSubscribeDialogAssoc::SendUnsubscribeL(CSIPMessageElements *aElements)"));
    messageElements = static_cast<CSIPMessageElements*>(GetDataObjectL(strSIPMessageElements));
    TRAP(err, clientTransaction = iSIPSubscribeDialogAssoc->SendUnsubscribeL(messageElements));
    CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*>(GetDataWrapperL(strSIPMessageElements));
    wrapper->SetIsOwner(EFalse);
    
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

void CT_DataSIPSubscribeDialogAssoc::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPSubscribeDialogAssoc::~CSIPSubscribeDialogAssoc()"));
    DestroyData();
    }
