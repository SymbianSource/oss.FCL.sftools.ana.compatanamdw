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


#include <sipdialogassocbase.h>
#include <sipinvitedialogassoc.h>
#include <utf.h>
#include <sipprofile.h> 

#include "T_SIPUtil.h"
#include "t_csipinvitedialogassoc.h"
#include "t_csipmessageelements.h"
#include "t_csipclienttransaction.h"
#include "t_csipdialog.h"
#include "t_csipfromheader.h"
#include "t_csiptoheader.h"
#include "t_csipcontactheader.h"

// Command
_LIT(KCmdNewL,              "NewL");
_LIT(KCmdNewLC,             "NewLC");
_LIT(KCmdSendAckL,          "SendAckL");
_LIT(KCmdSendByeL,          "SendByeL");
_LIT(KCmdSendInviteL,       "SendInviteL");
_LIT(KCmdSendPrackL,        "SendPrackL");
_LIT(KCmdSendUpdateL,       "SendUpdateL");
_LIT(KCmdDestructor,        "~");

// Field
//_LIT(KFldExpected,                  "expected");
_LIT(KFldMessageElements,           "msgelems");
_LIT(KFldTransaction,               "transaction");
_LIT(KFldDialog,                    "dialog");
_LIT(KFldConnection,                "connection");
_LIT(KFldSIPRegistrationContext,    "context");
_LIT(KFldRemoteUri,                 "rmturi");
_LIT(KFldToHeader,                  "tohdr");
_LIT(KFldFromHeader,                "fromhdr");
_LIT(KFldContactHeader,             "contacthdr");

// Error
_LIT(KLogError, "Error=%d");
_LIT(KMissingParameter, "missing parameter '%S'");

CT_DataSIPInviteDialogAssoc* CT_DataSIPInviteDialogAssoc::NewL()
    {
    CT_DataSIPInviteDialogAssoc* self = new (ELeave) CT_DataSIPInviteDialogAssoc();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CT_DataSIPInviteDialogAssoc::~CT_DataSIPInviteDialogAssoc()
    {
    DestroyData();
    }

CT_DataSIPInviteDialogAssoc::CT_DataSIPInviteDialogAssoc() :
CT_DataSIPDialogAssocBase(), iInviteDlgAssoc(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPInviteDialogAssoc::ConstructL()
    {

    }

CSIPDialogAssocBase *CT_DataSIPInviteDialogAssoc::GetSIPDialogAssocBase() const
    {
    return iInviteDlgAssoc;
    }

void CT_DataSIPInviteDialogAssoc::DestroyData()
    {
    if (iIsOwner)
        {
        delete iInviteDlgAssoc;
        iInviteDlgAssoc = NULL;
        iIsOwner = EFalse;
        }
    }

void CT_DataSIPInviteDialogAssoc::DoCmdDestructor()
    {
    INFO_PRINTF1(_L("call CSIPInviteDialogAssoc::~CSIPInviteDialogAssoc()"));
    DestroyData();
    }

TBool CT_DataSIPInviteDialogAssoc::DoCommandL(const TTEFFunction& aCommand,
        const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
    {
    TBool ret = ETrue;
    if (aCommand == KCmdNewL)
        {
        DoCmdNewL(aSection);
        }
    else if (aCommand == KCmdNewLC)
        {
        DoCmdNewLC(aSection);
        }
    else if (aCommand == KCmdSendAckL)
        {
        DoCmdSendAckL(aSection);
        }
    else if (aCommand == KCmdSendByeL)
        {
        DoCmdSendByeL(aSection);
        }
    else if (aCommand == KCmdSendInviteL)
        {
        DoCmdSendInviteL(aSection);
        }
    else if (aCommand == KCmdSendPrackL)
        {
        DoCmdSendPrackL(aSection);
        }
    else if (aCommand == KCmdSendUpdateL)
        {
        DoCmdSendUpdateL(aSection);
        }
    else if (aCommand == KCmdDestructor)
        {
        DoCmdDestructor();
        }
    else
        {
        ret = CT_DataSIPDialogAssocBase::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
        }
    return ret;
    }

TAny* CT_DataSIPInviteDialogAssoc::GetObject()
    {
    return iInviteDlgAssoc;
    }

void CT_DataSIPInviteDialogAssoc::SetObjectL(TAny* aAny)
    {
    DestroyData();
    iInviteDlgAssoc = static_cast<CSIPInviteDialogAssoc*> (aAny);
    }

void CT_DataSIPInviteDialogAssoc::DisownObjectL()
    {
    iInviteDlgAssoc = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPInviteDialogAssoc::DoCmdNewL(const TTEFSectionName& aSection)
    {
    CSIPDialog* dlg = NULL;
    CSIPTransactionBase* transaction = NULL;
    CSIPConnection* conn = NULL;
    CSIPProfile* context = NULL;
    CUri8* rmtUri = NULL;
    CSIPToHeader* to = NULL;
    CSIPFromHeader* from = NULL;
    CSIPContactHeader* contact = NULL;
    TInt err = KErrNone;
    TBool dataOk = EFalse;
    
    if (CT_SIPUtil::GetSIPDialogL(*this, aSection, KFldDialog, dlg))
        {
        // Only object of CSIPDialog provided.
        dataOk = ETrue;
        INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::NewL(CSIPDialog &)"));
        TRAP(err, iInviteDlgAssoc = CSIPInviteDialogAssoc::NewL(*dlg));
        }
    else if (CT_SIPUtil::GetSIPTransactionL(*this, aSection, KFldTransaction, transaction))
        {
        CSIPServerTransaction* srvTranxn = (CSIPServerTransaction*)transaction;
        // 2 overloads.
        if (!CT_SIPUtil::GetSIPProfile(*this, aSection, KFldSIPRegistrationContext, context))
            {
            // Only object of CSIPServerTransaction provided.
            dataOk = ETrue;
            INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::NewL(CSIPServerTransaction &)"));
            TRAP(err, iInviteDlgAssoc = CSIPInviteDialogAssoc::NewL(*srvTranxn));
            }
        else
            {
            // Objects of CSIPServerTransaction and MSIPRegistrationContext provided.
            dataOk = ETrue;
            INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::NewL(CSIPServerTransaction &, const MSIPRegistrationContext &)"));
            TRAP(err, iInviteDlgAssoc = CSIPInviteDialogAssoc::NewL(*srvTranxn, *context));
            }
        }
    else if (CT_SIPUtil::GetSIPConnectionL(*this, aSection, KFldConnection, conn))
        {
        // Object of CSIPConnection provided.
        // 2 overloads.
        if (CT_SIPUtil::GetUri8L(*this, aSection, KFldRemoteUri, rmtUri))
            {
            // Objects of CUri8, CSIPFromHeader(optional / mandatory), CSIPToHeader(optional) and CSIPContactHeader(optional) provided.
            (void)CT_SIPUtil::GetSIPToHeaderL(*this, aSection, KFldToHeader, to);
            (void)CT_SIPUtil::GetSIPContactHeaderL(*this, aSection, KFldContactHeader, contact);
            if (CT_SIPUtil::GetSIPProfile(*this, aSection, KFldSIPRegistrationContext, context))
                {
                // Object of MSIPRegistrationContext provided and object of CSIPFromHeader is optional.
                dataOk = ETrue;
                (void)CT_SIPUtil::GetSIPFromHeaderL(*this, aSection, KFldFromHeader, from);
                INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::NewL(CSIPConnection &, CUri8 *, const MSIPRegistrationContext &, CSIPFromHeader *, CSIPToHeader *, CSIPContactHeader *)"));
                TRAP(err, iInviteDlgAssoc = CSIPInviteDialogAssoc::NewL(*conn, rmtUri, *context, from, to, contact));
                }
            else
                {
                if (CT_SIPUtil::GetSIPFromHeaderL(*this, aSection, KFldFromHeader, from))
                    {
                    // Mandatory object of CSIPFromHeader provided.
                    dataOk = ETrue;
                    INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::NewL(CSIPConnection &, CSIPFromHeader *, CUri8 *, CSIPToHeader *, CSIPContactHeader *)"));
                    TRAP(err, iInviteDlgAssoc = CSIPInviteDialogAssoc::NewL(*conn, from, rmtUri, to, contact));
                    }
                else
                    {
                    ERR_PRINTF2(KMissingParameter, &KFldFromHeader);
                    SetBlockResult(EFail);
                    }
                }
            }
        else
            {
            ERR_PRINTF2(KMissingParameter, &KFldRemoteUri);
            SetBlockResult(EFail);
            }
        }
        
    if (dataOk)
        {
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iIsOwner = ETrue;
            // Transfer ownership
            TPtrC name;
            if (from != NULL)
                {
                // Ignore return value 'cause name exists if from not null;
                GetStringFromConfig(aSection, KFldFromHeader, name);
                CT_DataSIPFromHeader* wrapper = static_cast<CT_DataSIPFromHeader*>(GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }
            if (to != NULL)
                {
                // Ignore return value 'cause name exists if to not null;
                GetStringFromConfig(aSection, KFldToHeader, name);
                CT_DataSIPToHeader* wrapper = static_cast<CT_DataSIPToHeader*>(GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }
            if (contact != NULL)
                {
                // Ignore return value 'cause name exists if contact not null;
                GetStringFromConfig(aSection, KFldContactHeader, name);
                CT_DataSIPContactHeader* wrapper = static_cast<CT_DataSIPContactHeader*>(GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }
            } 
        }
    else
        {
        INFO_PRINTF1(_L("Missing one of following mandatory parameters:"));
        ERR_PRINTF2(KMissingParameter, &KFldDialog);
        ERR_PRINTF2(KMissingParameter, &KFldTransaction);
        ERR_PRINTF2(KMissingParameter, &KFldConnection);
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPInviteDialogAssoc::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    CSIPDialog* dlg = NULL;
    CSIPTransactionBase* transaction = NULL;
    CSIPConnection* conn = NULL;
    CSIPProfile* context = NULL;
    CUri8* rmtUri = NULL;
    CSIPToHeader* to = NULL;
    CSIPFromHeader* from = NULL;
    CSIPContactHeader* contact = NULL;
    TInt err = KErrNone;
    TBool dataOk = EFalse;
    
    if (CT_SIPUtil::GetSIPDialogL(*this, aSection, KFldDialog, dlg))
        {
        // Only object of CSIPDialog provided.
        dataOk = ETrue;
        INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::NewLC(CSIPDialog &)"));
        TRAP(err, iInviteDlgAssoc = CSIPInviteDialogAssoc::NewLC(*dlg); CleanupStack::Pop(iInviteDlgAssoc));
        }
    else if (CT_SIPUtil::GetSIPTransactionL(*this, aSection, KFldTransaction, transaction))
        {
        CSIPServerTransaction* srvTranxn = (CSIPServerTransaction*)transaction;
        // 2 overloads.
        if (!CT_SIPUtil::GetSIPProfile(*this, aSection, KFldSIPRegistrationContext, context))
            {
            // Only object of CSIPServerTransaction provided.
            dataOk = ETrue;
            INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::NewLC(CSIPServerTransaction &)"));
            TRAP(err, iInviteDlgAssoc = CSIPInviteDialogAssoc::NewLC(*srvTranxn); CleanupStack::Pop(iInviteDlgAssoc));
            }
        else
            {
            // Objects of CSIPServerTransaction and MSIPRegistrationContext provided.
            dataOk = ETrue;
            INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::NewLC(CSIPServerTransaction &, const MSIPRegistrationContext &)"));
            TRAP(err, iInviteDlgAssoc = CSIPInviteDialogAssoc::NewLC(*srvTranxn, *context); CleanupStack::Pop(iInviteDlgAssoc));
            }
        }
    else if (CT_SIPUtil::GetSIPConnectionL(*this, aSection, KFldConnection, conn))
        {
        // Object of CSIPConnection provided.
        // 2 overloads.
        if (CT_SIPUtil::GetUri8L(*this, aSection, KFldRemoteUri, rmtUri))
            {
            // Objects of CUri8, CSIPFromHeader(optional / mandatory), CSIPToHeader(optional) and CSIPContactHeader(optional) provided.
            (void)CT_SIPUtil::GetSIPToHeaderL(*this, aSection, KFldToHeader, to);
            (void)CT_SIPUtil::GetSIPContactHeaderL(*this, aSection, KFldContactHeader, contact);
            if (CT_SIPUtil::GetSIPProfile(*this, aSection, KFldSIPRegistrationContext, context))
                {
                // Object of MSIPRegistrationContext provided and object of CSIPFromHeader is optional.
                dataOk = ETrue;
                (void)CT_SIPUtil::GetSIPFromHeaderL(*this, aSection, KFldFromHeader, from);
                INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::NewLC(CSIPConnection &, CUri8 *, const MSIPRegistrationContext &, CSIPFromHeader *, CSIPToHeader *, CSIPContactHeader *)"));
                TRAP(err, iInviteDlgAssoc = CSIPInviteDialogAssoc::NewLC(*conn, rmtUri, *context, from, to, contact); CleanupStack::Pop(iInviteDlgAssoc));
                }
            else
                {
                if (CT_SIPUtil::GetSIPFromHeaderL(*this, aSection, KFldFromHeader, from))
                    {
                    // Mandatory object of CSIPFromHeader provided.
                    dataOk = ETrue;
                    INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::NewLC(CSIPConnection &, CSIPFromHeader *, CUri8 *, CSIPToHeader *, CSIPContactHeader *)"));
                    TRAP(err, iInviteDlgAssoc = CSIPInviteDialogAssoc::NewLC(*conn, from, rmtUri, to, contact); CleanupStack::Pop(iInviteDlgAssoc));
                    }
                else
                    {
                    ERR_PRINTF2(KMissingParameter, &KFldFromHeader);
                    SetBlockResult(EFail);
                    }
                }
            }
        else
            {
            ERR_PRINTF2(KMissingParameter, &KFldRemoteUri);
            SetBlockResult(EFail);
            }
        }
        
    if (dataOk)
        {
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            iIsOwner = ETrue;
            // Transfer ownership
            TPtrC name;
            if (from != NULL)
                {
                // Ignore return value 'cause name exists if from not null;
                GetStringFromConfig(aSection, KFldFromHeader, name);
                CT_DataSIPFromHeader* wrapper = static_cast<CT_DataSIPFromHeader*>(GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }
            if (to != NULL)
                {
                // Ignore return value 'cause name exists if to not null;
                GetStringFromConfig(aSection, KFldToHeader, name);
                CT_DataSIPToHeader* wrapper = static_cast<CT_DataSIPToHeader*>(GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }
            if (contact != NULL)
                {
                // Ignore return value 'cause name exists if contact not null;
                GetStringFromConfig(aSection, KFldContactHeader, name);
                CT_DataSIPContactHeader* wrapper = static_cast<CT_DataSIPContactHeader*>(GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }
            } 
        }
    else
        {
        INFO_PRINTF1(_L("Missing one of following mandatory parameters:"));
        ERR_PRINTF2(KMissingParameter, &KFldDialog);
        ERR_PRINTF2(KMissingParameter, &KFldTransaction);
        ERR_PRINTF2(KMissingParameter, &KFldConnection);
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPInviteDialogAssoc::DoCmdSendAckL(
        const TTEFSectionName& aSection)
    {
    CSIPTransactionBase* transaction;
    if (CT_SIPUtil::GetSIPTransactionL(*this, aSection, KFldTransaction, transaction))
        {
        CSIPMessageElements* msgElems = NULL;
        // Ignore return value 'cause default parameter of CSIPMessageElements* is NULL.
        (void) CT_SIPUtil::GetSIPMessageElements(*this, aSection, KFldMessageElements, msgElems);
        INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::SendAckL(const CSIPClientTransaction&, CSIPMessageElements*)"));
        TRAPD(err, iInviteDlgAssoc->SendAckL(*((CSIPClientTransaction*)transaction), msgElems));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            // Transfer ownership of CSIPMessageElements object
            TPtrC name;
            if (GetStringFromConfig(aSection, KFldMessageElements, name))
                {
                CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*> (GetDataWrapperL(name));
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

void CT_DataSIPInviteDialogAssoc::DoCmdSendByeL(
        const TTEFSectionName& aSection)
    {
    TPtrC transactionName;
    if (GetStringFromConfig(aSection, KFldTransaction, transactionName))
        {
        CSIPMessageElements* msgElems = NULL;
        CSIPClientTransaction* transaction = NULL;
        // Ignore return value 'cause default parameter of CSIPMessageElements* is NULL.
        (void) CT_SIPUtil::GetSIPMessageElements(*this, aSection, KFldMessageElements, msgElems);
        INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::SendByeL(CSIPMessageElements*)"));
        TRAPD(err, transaction = iInviteDlgAssoc->SendByeL(msgElems));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            TPtrC name;
            if (GetStringFromConfig(aSection, KFldMessageElements, name))
                {
                // Get ownership.
                CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*> (GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }

            if (transaction != NULL)
                {
                // Set ownership.
                CT_DataSIPClientTransaction* wrapper = static_cast<CT_DataSIPClientTransaction*> (GetDataWrapperL(transactionName));
                wrapper->SetIsOwner(ETrue);
                SetDataObjectL(transactionName, transaction);
                }
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldTransaction());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPInviteDialogAssoc::DoCmdSendInviteL(
        const TTEFSectionName& aSection)
    {
    TPtrC transactionName;
    if (GetStringFromConfig(aSection, KFldTransaction, transactionName))
        {
        CSIPMessageElements* msgElems = NULL;
        CSIPClientTransaction* transaction = NULL;
        // Ignore return value 'cause default parameter of CSIPMessageElements* is NULL.
        (void) CT_SIPUtil::GetSIPMessageElements(*this, aSection, KFldMessageElements, msgElems);
        INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::SendInviteL(CSIPMessageElements*)"));
        TRAPD(err, transaction = iInviteDlgAssoc->SendInviteL(msgElems));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            TPtrC name;
            if (GetStringFromConfig(aSection, KFldMessageElements, name))
                {
                // Get ownership.
                CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*> (GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }

            if (transaction != NULL)
                {
                // Set ownership.
                CT_DataSIPClientTransaction* wrapper = static_cast<CT_DataSIPClientTransaction*> (GetDataWrapperL(transactionName));
                wrapper->SetIsOwner(ETrue);
                SetDataObjectL(transactionName, transaction);
                }
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldTransaction());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPInviteDialogAssoc::DoCmdSendPrackL(
        const TTEFSectionName& aSection)
    {
    TPtrC transactionName;
    if (GetStringFromConfig(aSection, KFldTransaction, transactionName))
        {
        CSIPMessageElements* msgElems = NULL;
        CSIPClientTransaction* transaction = NULL;
        // Ignore return value 'cause default parameter of CSIPMessageElements* is NULL.
        (void) CT_SIPUtil::GetSIPMessageElements(*this, aSection, KFldMessageElements, msgElems);
        INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::SendPrackL(CSIPMessageElements*)"));
        TRAPD(err, transaction = iInviteDlgAssoc->SendPrackL(msgElems));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            TPtrC name;
            if (GetStringFromConfig(aSection, KFldMessageElements, name))
                {
                // Get ownership.
                CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*> (GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }

            if (transaction != NULL)
                {
                // Set ownership.
                CT_DataSIPClientTransaction* wrapper = static_cast<CT_DataSIPClientTransaction*> (GetDataWrapperL(transactionName));
                wrapper->SetIsOwner(ETrue);
                SetDataObjectL(transactionName, transaction);
                }
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldTransaction());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPInviteDialogAssoc::DoCmdSendUpdateL(
        const TTEFSectionName& aSection)
    {
    TPtrC transactionName;
    if (GetStringFromConfig(aSection, KFldTransaction, transactionName))
        {
        CSIPMessageElements* msgElems = NULL;
        CSIPClientTransaction* transaction = NULL;
        // Ignore return value 'cause default parameter of CSIPMessageElements* is NULL.
        (void) CT_SIPUtil::GetSIPMessageElements(*this, aSection, KFldMessageElements, msgElems);
        INFO_PRINTF1(_L("execute CSIPInviteDialogAssoc::SendUpdateL(CSIPMessageElements*)"));
        TRAPD(err, transaction = iInviteDlgAssoc->SendUpdateL(msgElems));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            TPtrC name;
            if (GetStringFromConfig(aSection, KFldMessageElements, name))
                {
                // Get ownership.
                CT_DataSIPMessageElements* wrapper = static_cast<CT_DataSIPMessageElements*> (GetDataWrapperL(name));
                wrapper->SetIsOwner(EFalse);
                }

            if (transaction != NULL)
                {
                // Set ownership.
                CT_DataSIPClientTransaction* wrapper = static_cast<CT_DataSIPClientTransaction*> (GetDataWrapperL(transactionName));
                wrapper->SetIsOwner(ETrue);
                SetDataObjectL(transactionName, transaction);
                }
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldTransaction());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPInviteDialogAssoc::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
