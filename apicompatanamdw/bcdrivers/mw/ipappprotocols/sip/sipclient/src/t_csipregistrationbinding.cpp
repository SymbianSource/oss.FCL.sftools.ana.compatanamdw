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

#include <sipregistrationbinding.h>
#include <sipmessageelements.h>

#include "T_SIPUtil.h"
#include "t_csipregistrationbinding.h"
#include "t_csiptoheader.h"
#include "t_csipcontactheader.h"
#include "t_csipfromheader.h"
#include "t_csipheaderbase.h"
#include "t_csiprefresh.h"
#include "t_csipclienttransaction.h"
#include "t_csipmessageelements.h"
#include "t_csiprouteheader.h"
#include "t_csipconnection.h"

// Command
_LIT(KCmdNewL,                  "NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdIsContextActiveL,      "IsContextActive");
_LIT(KCmdContextIdL,            "ContextId");
_LIT(KCmdRegisterL,             "RegisterL");
_LIT(KCmdDeregisterL,           "DeregisterL");
_LIT(KCmdUpdateL,               "UpdateL");
_LIT(KCmdConnectionL,           "Connection");
_LIT(KCmdSetOutboundProxyL,     "SetOutboundProxyL");
_LIT(KCmdAor,                   "Aor");
_LIT(KCmdContactHeaderL,        "ContactHeader");
_LIT(KCmdOutboundProxy,         "OutboundProxy");
_LIT(KCmdSIPRefresh,            "SIPRefresh");
_LIT(KCmdOperatorEqual,         "==");
_LIT(KCmdRegisteredContactL,    "RegisteredContact");
_LIT(KCmdDestructor,            "~");

// Field
_LIT(KFldExpected,                  "expected");
_LIT(KFldRefresh,                   "refresh");
_LIT(KFldFromHeader,                "fromhdr");
_LIT(KFldRemoteUri,                 "uri");
_LIT(KFldRouteHeader,               "outboundproxy");
_LIT(KFldConnection,                "conn");
_LIT(KFldToHeader,                  "tohdr");
_LIT(KFldContactHeader,             "contact");
_LIT(KFldMessageElements,           "msgelems");
_LIT(KFldTransaction,               "transaction");
_LIT(KFldExpiration,                "expiration");
_LIT(KFldModifiable,                "modifiable");
_LIT(KFldSIPRegistrationBinding,    "sipregistrationbinding");


// Error
_LIT(KLogError, "Error=%d");
_LIT(KMissingParameter, "missing parameter '%S'");
_LIT(KLogNotExpectedValue,          "Not expected value, actual=%d, expect=%d");

CT_DataSIPRegistrationBinding* CT_DataSIPRegistrationBinding::NewL()
    {
    CT_DataSIPRegistrationBinding* self = new (ELeave) CT_DataSIPRegistrationBinding();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CT_DataSIPRegistrationBinding::~CT_DataSIPRegistrationBinding()
    {
    DestroyData();
    }

CT_DataSIPRegistrationBinding::CT_DataSIPRegistrationBinding() :
CDataWrapperBase(), iRegBinding(NULL), iIsOwner(ETrue)
    {
    }

void CT_DataSIPRegistrationBinding::ConstructL()
    {

    }

void CT_DataSIPRegistrationBinding::DestroyData()
    {
    if (iIsOwner)
        {
        delete iRegBinding;
        iRegBinding = NULL;
        iIsOwner = EFalse;
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdDestructor()
    {
    INFO_PRINTF1(_L("call CSIPRegistrationBinding::~CSIPRegistrationBinding()"));
    DestroyData();
    }

TBool CT_DataSIPRegistrationBinding::DoCommandL(const TTEFFunction& aCommand,
        const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
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
    else if (aCommand == KCmdIsContextActiveL)
        {
        DoCmdIsContextActive(aSection);
        }
    else if (aCommand == KCmdContextIdL)
        {
        DoCmdContextId(aSection);
        }
    else if (aCommand == KCmdRegisterL)
        {
        DoCmdRegisterL(aSection);
        }
    else if (aCommand == KCmdDeregisterL)
        {
        DoCmdDeregisterL(aSection);
        }
    else if (aCommand == KCmdUpdateL)
        {
        DoCmdUpdateL(aSection);
        }
    else if (aCommand == KCmdConnectionL)
        {
        DoCmdConnectionL(aSection);
        }
    else if (aCommand == KCmdSetOutboundProxyL)
        {
        DoCmdSetOutboundProxyL(aSection);
        }
    else if (aCommand == KCmdAor)
        {
        DoCmdAor(aSection);
        }
    else if (aCommand == KCmdContactHeaderL)
        {
        DoCmdContactHeaderL(aSection);
        }
    else if (aCommand == KCmdOutboundProxy)
        {
        DoCmdOutboundProxy(aSection);
        }
    else if (aCommand == KCmdSIPRefresh)
        {
        DoCmdSIPRefreshL(aSection);
        }
    else if (aCommand == KCmdOperatorEqual)
        {
        DoCmdOperatorEqualL(aSection);
        }
    else if (aCommand == KCmdRegisteredContactL)
        {
        DoCmdRegisteredContactL(aSection);
        }
    else if (aCommand == KCmdDestructor)
        {
        DoCmdDestructor();
        }
    else
        {
        ret = EFalse; // TODO: Maybe need to call DoCommandL of MSIPRegistrationContext wrapper.
        }
    return ret;
    }

TAny* CT_DataSIPRegistrationBinding::GetObject()
    {
    return iRegBinding;
    }

void CT_DataSIPRegistrationBinding::SetObjectL(TAny* aAny)
    {
    DestroyData();
    iRegBinding = static_cast<CSIPRegistrationBinding*> (aAny);
    }

void CT_DataSIPRegistrationBinding::DisownObjectL()
    {
    iRegBinding = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPRegistrationBinding::DoCmdNewL(const TTEFSectionName& aSection)
    {
    CSIPConnection* conn = NULL;
    CSIPToHeader* aor = NULL;
    CSIPContactHeader* contact = NULL;
    CSIPRefresh* refresh = NULL;
    CSIPRouteHeader* outboundProxy = NULL;
    CUri8* rmtUri = NULL;
    CSIPFromHeader* from = NULL;
    TInt err = KErrNone;
    TBool dataOk = EFalse;
    
    // Ignore return values 'cause objects of CSIPRefresh, CSIPRouteHeader, CUri8, and CSIPFromHeader are optional.
    (void)CT_SIPUtil::GetSIPRefreshL(*this, aSection, KFldRefresh, refresh);
    (void)CT_SIPUtil::GetSIPRouteHeaderL(*this, aSection, KFldRouteHeader, outboundProxy);
    (void)CT_SIPUtil::GetSIPFromHeaderL(*this, aSection, KFldFromHeader, from);
    (void)CT_SIPUtil::GetUri8L(*this, aSection, KFldRemoteUri, rmtUri);

    if (CT_SIPUtil::GetSIPConnectionL(*this, aSection, KFldConnection, conn))
        {
        if (CT_SIPUtil::GetSIPToHeaderL(*this, aSection, KFldToHeader, aor))
            {
            if (CT_SIPUtil::GetSIPContactHeaderL(*this, aSection, KFldContactHeader, contact))
                {
                dataOk = ETrue;
                INFO_PRINTF1(_L("execute CSIPRegistrationBinding::NewL(CSIPConnection&, CSIPToHeader*, CSIPContactHeader*, CSIPRefresh*, CSIPRouteHeader*, CUri8*, CSIPFromHeader*)"));
                TRAP(err, iRegBinding = CSIPRegistrationBinding::NewL(*conn, aor,
                        contact, refresh, outboundProxy, rmtUri, from));
                if (err != KErrNone)
                    {
                    ERR_PRINTF2(KLogError, err);
                    SetError(err);
                    }
                }
            else
                {
                ERR_PRINTF2(KMissingParameter, &KFldContactHeader());
                SetBlockResult(EFail);
                }
            }
        else
            {
            ERR_PRINTF2(KMissingParameter, &KFldToHeader());
            SetBlockResult(EFail);
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldConnection());
        SetBlockResult(EFail);
        }
    if (dataOk && err == KErrNone)
        {
        iIsOwner = ETrue;
        
        // Transfer ownerships.
        TPtrC name;
        (void)GetStringFromConfig(aSection, KFldToHeader, name);
        CT_DataSIPToHeader* toWrapper = static_cast<CT_DataSIPToHeader*>(GetDataWrapperL(name));
        toWrapper->SetIsOwner(EFalse);
        
        (void)GetStringFromConfig(aSection, KFldContactHeader, name);
        CT_DataSIPContactHeader* contactWrapper = static_cast<CT_DataSIPContactHeader*>(GetDataWrapperL(name));
        contactWrapper->SetIsOwner(EFalse);
        
        if (GetStringFromConfig(aSection, KFldRefresh, name))
            {
            CT_DataSIPRefresh* wrapper = static_cast<CT_DataSIPRefresh*> (GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        
        if (GetStringFromConfig(aSection, KFldRouteHeader, name))
            {
            CT_DataSIPRouteHeader* wrapper = static_cast<CT_DataSIPRouteHeader*> (GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        
        if (GetStringFromConfig(aSection, KFldFromHeader, name))
            {
            CT_DataSIPFromHeader* wrapper = static_cast<CT_DataSIPFromHeader*> (GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdNewLC(
        const TTEFSectionName& aSection)
    {
    CSIPConnection* conn = NULL;
    CSIPToHeader* aor = NULL;
    CSIPContactHeader* contact = NULL;
    CSIPRefresh* refresh = NULL;
    CSIPRouteHeader* outboundProxy = NULL;
    CUri8* rmtUri = NULL;
    CSIPFromHeader* from = NULL;
    TInt err = KErrNone;
    TBool dataOk = EFalse;
    
    // Ignore return values 'cause objects of CSIPRefresh, CSIPRouteHeader, CUri8, and CSIPFromHeader are optional.
    (void)CT_SIPUtil::GetSIPRefreshL(*this, aSection, KFldRefresh, refresh);
    (void)CT_SIPUtil::GetSIPRouteHeaderL(*this, aSection, KFldRouteHeader, outboundProxy);
    (void)CT_SIPUtil::GetSIPFromHeaderL(*this, aSection, KFldFromHeader, from);
    (void)CT_SIPUtil::GetUri8L(*this, aSection, KFldRemoteUri, rmtUri);

    if (CT_SIPUtil::GetSIPConnectionL(*this, aSection, KFldConnection, conn))
        {
        if (CT_SIPUtil::GetSIPToHeaderL(*this, aSection, KFldToHeader, aor))
            {
            if (CT_SIPUtil::GetSIPContactHeaderL(*this, aSection, KFldContactHeader, contact))
                {
                dataOk = ETrue;
                INFO_PRINTF1(_L("execute CSIPRegistrationBinding::NewLC(CSIPConnection&, CSIPToHeader*, CSIPContactHeader*, CSIPRefresh*, CSIPRouteHeader*, CUri8*, CSIPFromHeader*)"));
                TRAP(err, iRegBinding = CSIPRegistrationBinding::NewLC(*conn, aor,
                        contact, refresh, outboundProxy, rmtUri, from);
                        CleanupStack::Pop(iRegBinding));
                if (err != KErrNone)
                    {
                    ERR_PRINTF2(KLogError, err);
                    SetError(err);
                    }
                }
            else
                {
                ERR_PRINTF2(KMissingParameter, &KFldContactHeader());
                SetBlockResult(EFail);
                }
            }
        else
            {
            ERR_PRINTF2(KMissingParameter, &KFldToHeader());
            SetBlockResult(EFail);
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldConnection());
        SetBlockResult(EFail);
        }
    if (dataOk && err == KErrNone)
        {
        iIsOwner = ETrue;
        
        // Transfer ownerships.
        TPtrC name;
        (void)GetStringFromConfig(aSection, KFldToHeader, name);
        CT_DataSIPToHeader* toWrapper = static_cast<CT_DataSIPToHeader*>(GetDataWrapperL(name));
        toWrapper->SetIsOwner(EFalse);
        
        (void)GetStringFromConfig(aSection, KFldContactHeader, name);
        CT_DataSIPContactHeader* contactWrapper = static_cast<CT_DataSIPContactHeader*>(GetDataWrapperL(name));
        contactWrapper->SetIsOwner(EFalse);
        
        if (GetStringFromConfig(aSection, KFldRefresh, name))
            {
            CT_DataSIPRefresh* wrapper = static_cast<CT_DataSIPRefresh*> (GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        
        if (GetStringFromConfig(aSection, KFldRouteHeader, name))
            {
            CT_DataSIPRouteHeader* wrapper = static_cast<CT_DataSIPRouteHeader*> (GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        
        if (GetStringFromConfig(aSection, KFldFromHeader, name))
            {
            CT_DataSIPFromHeader* wrapper = static_cast<CT_DataSIPFromHeader*> (GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdIsContextActive(
        const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPRegistrationBinding::IsContextActive()"));
    TBool actual = iRegBinding->IsContextActive();
    
    TBool expected;
    if (GetBoolFromConfig(aSection, KFldExpected, expected))
        {
        if (!actual != !expected)
            {
            ERR_PRINTF3(_L("returned value is not as expected: actual = %d, expected = %d"), actual, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdContextId(
        const TTEFSectionName& aSection)
    {
    INFO_PRINTF1(_L("execute CSIPRegistrationBinding::ContextId()"));
    TUint32 actual = iRegBinding->ContextId();
    
    TUint32 expected;
    if (GetTUint32FromConfig(aSection, KFldExpected, expected))
        {
        if (actual != expected)
            {
            ERR_PRINTF3(_L("returned value is not as expected: actual = %u, expected = %u"), actual, expected);
            SetBlockResult(EFail);
            }
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdRegisterL(
        const TTEFSectionName& aSection)
    {
    CSIPMessageElements* msgElems = NULL;
    CSIPClientTransaction* transaction = NULL;
    TPtrC wrapperName;
    
    if (GetStringFromConfig(aSection, KFldTransaction, wrapperName))
        {
        // Ignore return value 'cause the object is optional.
        (void) CT_SIPUtil::GetSIPMessageElements(*this, aSection, KFldMessageElements, msgElems);
        INFO_PRINTF1(_L("execute CSIPRegistrationBinding::RegisterL(CSIPMessageElements*)"));
        TRAPD(err, transaction = iRegBinding->RegisterL(msgElems));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            // Transfer ownerships.
            CT_DataSIPClientTransaction* transactionWrapper = static_cast<CT_DataSIPClientTransaction*>(GetDataWrapperL(wrapperName));
            transactionWrapper->SetIsOwner(ETrue);
            SetDataObjectL(wrapperName, transaction);
            
            if (GetStringFromConfig(aSection, KFldMessageElements, wrapperName))
                {
                CT_DataSIPMessageElements* msgElemsWrapper = static_cast<CT_DataSIPMessageElements*>(GetDataWrapperL(wrapperName));
                msgElemsWrapper->SetIsOwner(EFalse);
                }
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldTransaction());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdDeregisterL(
        const TTEFSectionName& aSection)
    {
    CSIPMessageElements* msgElems = NULL;
    CSIPClientTransaction* transaction = NULL;
    TPtrC wrapperName;
    
    if (GetStringFromConfig(aSection, KFldTransaction, wrapperName))
        {
        // Ignore return value 'cause the object is optional.
        (void) CT_SIPUtil::GetSIPMessageElements(*this, aSection, KFldMessageElements, msgElems);
        INFO_PRINTF1(_L("execute CSIPRegistrationBinding::DeregisterL(CSIPMessageElements*)"));
        TRAPD(err, transaction = iRegBinding->DeregisterL(msgElems));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            // Transfer ownerships.
            CT_DataSIPClientTransaction* transactionWrapper = static_cast<CT_DataSIPClientTransaction*>(GetDataWrapperL(wrapperName));
            transactionWrapper->SetIsOwner(ETrue);
            SetDataObjectL(wrapperName, transaction);
            
            if (GetStringFromConfig(aSection, KFldMessageElements, wrapperName))
                {
                CT_DataSIPMessageElements* msgElemsWrapper = static_cast<CT_DataSIPMessageElements*>(GetDataWrapperL(wrapperName));
                msgElemsWrapper->SetIsOwner(EFalse);
                }
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldTransaction());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdUpdateL(
        const TTEFSectionName& aSection)
    {
    CSIPMessageElements* msgElems = NULL;
    CSIPClientTransaction* transaction = NULL;
    TPtrC wrapperName;
    TUint expiration;
    TInt err = KErrNone;
    
    if (GetStringFromConfig(aSection, KFldTransaction, wrapperName))
        {
        if (CT_SIPUtil::GetSIPMessageElements(*this, aSection, KFldMessageElements, msgElems))
            {
            if (!GetTUintFromConfig(aSection, KFldExpiration, expiration))
                {
                INFO_PRINTF1(_L("execute CSIPRegistrationBinding::UpdateL(CSIPMessageElements*)"));
                TRAP(err, transaction = iRegBinding->UpdateL(msgElems));
                }
            else
                {
                INFO_PRINTF1(_L("execute CSIPRegistrationBinding::UpdateL(TUint, CSIPMessageElements*)"));
                TRAP(err, transaction = iRegBinding->UpdateL(expiration, msgElems));
                }
            
            if (err != KErrNone)
                {
                ERR_PRINTF2(KLogError, err);
                SetError(err);
                }
            else
                {
                // Transfer ownerships.
                CT_DataSIPClientTransaction* transactionWrapper = static_cast<CT_DataSIPClientTransaction*>(GetDataWrapperL(wrapperName));
                transactionWrapper->SetIsOwner(ETrue);
                SetDataObjectL(wrapperName, transaction);
                
                if (GetStringFromConfig(aSection, KFldMessageElements, wrapperName))
                    {
                    CT_DataSIPMessageElements* msgElemsWrapper = static_cast<CT_DataSIPMessageElements*>(GetDataWrapperL(wrapperName));
                    msgElemsWrapper->SetIsOwner(EFalse);
                    }
                }
            }
        else
            {
            ERR_PRINTF2(KMissingParameter, &KFldMessageElements());
            SetBlockResult(EFail);
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldTransaction());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdConnectionL(
        const TTEFSectionName& aSection)
    {
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldConnection, name))
        {
        INFO_PRINTF1(_L("execute CSIPRegistrationBinding::Connection()"));
        TBool modifiable = EFalse;
        const CSIPConnection* pRegConnection;
        (void) GetBoolFromConfig(aSection, KFldModifiable, modifiable);
        if (modifiable)
            {
            pRegConnection = iRegBinding->Connection();
            }
        else
            {
            pRegConnection = ((const CSIPRegistrationBinding*) iRegBinding)->Connection();
            }
        SetDataObjectL(name, (void*)pRegConnection);
        CT_DataSIPConnection* wrapper = static_cast<CT_DataSIPConnection*> (GetDataWrapperL(name));
        wrapper->SetIsOwner(EFalse);
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldConnection());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdSetOutboundProxyL(const TTEFSectionName& aSection)
    {
    TPtrC name;
    CSIPRouteHeader *routeHeader = NULL;
    if (GetStringFromConfig(aSection, KFldRouteHeader, name))
        {
        routeHeader = static_cast<CSIPRouteHeader*> (GetDataObjectL(name));
        INFO_PRINTF1(_L("execute CSIPRegistrationBinding::SetOutboundProxyL(CSIPRouteHeader*)"));
        TRAPD(err,iRegBinding->SetOutboundProxyL(routeHeader));
        if (err != KErrNone)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        else
            {
            CT_DataSIPRouteHeader* wrapper = static_cast<CT_DataSIPRouteHeader*> (GetDataWrapperL(name));
            wrapper->SetIsOwner(EFalse);
            }
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldRouteHeader());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdAor(const TTEFSectionName& aSection)
    {
    TPtrC name;
    if (GetStringFromConfig(aSection, KFldToHeader, name))
        {
        INFO_PRINTF1(_L("execute CSIPRegistrationBinding::Aor()"));
        const CSIPToHeader* pToHeader;
        pToHeader = &(((const CSIPRegistrationBinding*) iRegBinding)->Aor());
        SetDataObjectL(name, (void*)pToHeader);
        CT_DataSIPToHeader* wrapper = static_cast<CT_DataSIPToHeader*> (GetDataWrapperL(name));
        wrapper->SetIsOwner(EFalse);
        }
    else
        {
        ERR_PRINTF2(KMissingParameter, &KFldToHeader());
        SetBlockResult(EFail);
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdContactHeaderL(const TTEFSectionName& aSection)
    {
    TPtrC wrapperName;
    if( !GetStringFromConfig(aSection, KFldContactHeader, wrapperName) )
        {
        ERR_PRINTF2(KMissingParameter, KFldContactHeader);
        SetBlockResult(EFail);
        }
    else
        {
        TBool modifiable = EFalse;
        (void) GetBoolFromConfig(aSection, KFldModifiable, modifiable);
        if(modifiable)
            {
            INFO_PRINTF1(_L("execute CSIPRegistrationBinding::ContactHeader()"));
            CSIPContactHeader& header = iRegBinding->ContactHeader();
            SetDataObjectL(wrapperName, &header);
            }
        else
            {
            INFO_PRINTF1(_L("execute CSIPRegistrationBinding::ContactHeader()"));
            const CSIPContactHeader& header = ((const CSIPRegistrationBinding*)iRegBinding)->ContactHeader();
            SetDataObjectL(wrapperName, (void*)&header);
            }
        
        CT_DataSIPContactHeader* wrapper = static_cast<CT_DataSIPContactHeader*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdOutboundProxy(const TTEFSectionName& aSection)
    {
    TPtrC wrapperName;
    if( !GetStringFromConfig(aSection, KFldRouteHeader, wrapperName) )
        {
        ERR_PRINTF2(KMissingParameter, KFldRouteHeader);
        SetBlockResult(EFail);
        }
    else
        {
        INFO_PRINTF1(_L("execute CSIPRegistrationBinding::OutboundProxy()"));
        const CSIPRouteHeader* header = iRegBinding->OutboundProxy();
        
        CT_DataSIPRouteHeader* wrapper = static_cast<CT_DataSIPRouteHeader*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, (void*)header);
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdSIPRefreshL(const TTEFSectionName& aSection)
    {
    TPtrC wrapperName;
    if( !GetStringFromConfig(aSection, KFldRefresh, wrapperName) )
        {
        ERR_PRINTF2(KMissingParameter, KFldRefresh);
        SetBlockResult(EFail);
        }
    else
        {
        TBool modifiable = EFalse;
        (void) GetBoolFromConfig(aSection, KFldModifiable, modifiable);
        if(modifiable)
            {
            INFO_PRINTF1(_L("execute CSIPRegistrationBinding::SIPRefresh()"));
            CSIPRefresh* refresh = iRegBinding->SIPRefresh();
            SetDataObjectL(wrapperName, (void*)refresh);
            }
        else
            {
            INFO_PRINTF1(_L("execute CSIPRegistrationBinding::SIPRefresh()"));
            const CSIPRefresh* refresh = ((const CSIPRegistrationBinding*)iRegBinding)->SIPRefresh();
            SetDataObjectL(wrapperName, (void*)refresh);
            }
        
        CT_DataSIPRefresh* wrapper = static_cast<CT_DataSIPRefresh*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        }
    }

void CT_DataSIPRegistrationBinding::DoCmdOperatorEqualL(
        const TTEFSectionName& aSection)
    {
    TPtrC  datregstbinding;
    CSIPRegistrationBinding* regstbinding;
    if(!GetStringFromConfig(aSection, KFldSIPRegistrationBinding, datregstbinding) )
        {
        ERR_PRINTF2(KMissingParameter, &KFldSIPRegistrationBinding());
        SetBlockResult(EFail);
        return;
        }
    else
        {
        regstbinding = static_cast<CSIPRegistrationBinding*>(GetDataObjectL(datregstbinding));
        }
    INFO_PRINTF1(_L("execute CSIPRegistrationBinding::==(const CSIPRegistrationBinding&)")); 
    TBool ret = (*iRegBinding == *regstbinding);
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

void CT_DataSIPRegistrationBinding::DoCmdRegisteredContactL(
        const TTEFSectionName& aSection)
    {
    TPtrC datcontachd;
    if (!GetStringFromConfig(aSection, KFldContactHeader, datcontachd))
        {
        ERR_PRINTF2(KMissingParameter, &KFldContactHeader());
        SetBlockResult(EFail);
        return;
        }
    const CSIPContactHeader* retcontacthd = NULL;
    INFO_PRINTF1(_L("execute CSIPRegistrationBinding::RegisteredContact()")); 
    retcontacthd = iRegBinding->RegisteredContact();
    CT_DataSIPContactHeader* wrapper = static_cast<CT_DataSIPContactHeader*>(GetDataWrapperL(datcontachd));
    wrapper->SetIsOwner(EFalse);
    SetDataObjectL(datcontachd, (CSIPContactHeader*)retcontacthd);   
    }

void CT_DataSIPRegistrationBinding::SetIsOwner(TBool aOwner)
    {
    iIsOwner = aOwner;
    }
