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
* This contains CT_DataSIPConnection
*/


#include <sipregistrationbinding.h>
#include <sipstrconsts.h>
#include <sipstrings.h>
#include <sipservertransaction.h>
#include <sipclienttransaction.h>
#include <sipresponseelements.h>
#include <sipinvitedialogassoc.h>
#include <utf.h>
#include "T_SIPUtil.h"
#include "t_csipconnection.h"
#include "t_csip.h"
#include "t_csiprequestelements.h"
#include "t_csipclienttransaction.h"
#include "t_csipregistrationbinding.h"
#include "t_csipinvitedialogassoc.h"
#include "t_csipdialog.h"

/*@{*/
_LIT(KCmdDestroy,               "~");
_LIT(KCmdNewL,                  "NewL");
_LIT(KCmdNewLC,                 "NewLC");
_LIT(KCmdDisown,                "disown");
_LIT(KCmdState,                 "State");
_LIT(KCmdSendRequestL,          "SendRequestL");
_LIT(KCmdFetchRegistrationsL,   "FetchRegistrationsL");
_LIT(KCmdIapId,                 "IapId");
_LIT(KCmdSIP,                   "SIP");
_LIT(KCmdSetOptL,               "SetOptL");
_LIT(KCmdGetLocalAddrL,         "GetLocalAddrL");
_LIT(KCmdWaitForIncomingRequest,    "WaitForIncomingRequest");
_LIT(KCmdWaitForIncomingResponse,   "WaitForIncomingResponse");
_LIT(KCmdWaitForInviteCompleted,    "WaitForInviteCompleted");
_LIT(KCmdWaitForInviteCanceled,     "WaitForInviteCanceled");
_LIT(KCmdWaitForErrorOccured,       "WaitForErrorOccured");

//Fields 
_LIT(KFldIAPID,                 "iapID");
_LIT(KFldSIP,                   "sip");
_LIT(KFldExpectedState,         "ExpectedState");
_LIT(KFldConstFlag,             "ConstFlag");
_LIT(KFldRequestElement,        "RequestElement");
_LIT(KFldClientTransaction,     "ClientTransaction");
_LIT(KFldRegistrationBinding,   "RegistrationBinding");
_LIT(KFldRefresh,               "Refresh");
_LIT(KFldOptionName,            "OptionName");
_LIT(KFldOptionLevel,           "OptionLevel");
_LIT(KFldOptionValue,           "OptionValue");
_LIT(KFldOptionValueType,       "OptionValueType");
_LIT(KFldLocalAddr,             "LocalAddr");
_LIT(KFldServTransaction,       "ServTransaction");
_LIT(KFldDialogAssocBase,       "dialogassocbase");
_LIT(KFldSIPDialog,             "sipdialog");
_LIT(KFldErrorCode,             "errorcode");

//Error
_LIT(KLogError,                 "Error = %d");
_LIT(KLogMissingParameter,      "Missing parameter '%S'");
_LIT(KLogNotExpectedValue,      "Not expected value, actual = %d, expect = %d");

CT_DataSIPConnection::CT_DataSIPConnection() 
: iSIPConnection(NULL), iIsOwner(ETrue), iCheckState(EFalse), iCount(0)
    {
    }

CT_DataSIPConnection::~CT_DataSIPConnection()
    {
    DestroyData();
    }

CT_DataSIPConnection* CT_DataSIPConnection::NewL()
    {
    CT_DataSIPConnection* self=new (ELeave)CT_DataSIPConnection();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

void CT_DataSIPConnection::ConstructL()
    {
    }

TAny* CT_DataSIPConnection::GetObject()
    {
    return iSIPConnection;
    }

void CT_DataSIPConnection::SetObjectL(TAny* aAny)
    {
    iSIPConnection = static_cast<CSIPConnection*>(aAny);
    }

TBool CT_DataSIPConnection::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt /*aAsyncErrorIndex*/)
    {
    TBool   ret=ETrue;
        
    if ( aCommand==KCmdDestroy )
        {
        DoCmdDestructor(aSection);
        }
    else if ( aCommand==KCmdNewL )
        {
        DoCmdNewL(aSection);
        }
    else if ( aCommand==KCmdNewLC )
        {
        DoCmdNewLC(aSection);
        }
    else if ( aCommand==KCmdDisown )
        {
        DoCmdDisown();
        }
    else if ( aCommand==KCmdState )
        {
        DoCmdState(aSection);
        }
    else if ( aCommand==KCmdSendRequestL )
        {
        DoCmdSendRequestL(aSection);
        }
    else if ( aCommand==KCmdFetchRegistrationsL )
        {
        DoCmdFetchRegistrationsL(aSection);
        }
    else if ( aCommand==KCmdIapId )
        {
        DoCmdIapId(aSection);
        }
    else if ( aCommand==KCmdSIP )
        {
        DoCmdSIP(aSection);
        }
    else if ( aCommand==KCmdSetOptL )
        {
        DoCmdSetOptL(aSection);
        }
    else if ( aCommand==KCmdGetLocalAddrL )
        {
        DoCmdGetLocalAddrL(aSection);
        }
    else if ( aCommand==KCmdWaitForIncomingRequest )
        {
        DoCmdWaitForIncomingRequest(aSection);
        }
    else if ( aCommand==KCmdWaitForIncomingResponse )
        {
        DoCmdWaitForIncomingResponse(aSection);
        }
    else if ( aCommand==KCmdWaitForInviteCompleted )
        {
        DoCmdWaitForInviteCompleted(aSection);
        }     
    else if ( aCommand==KCmdWaitForInviteCanceled )
        {
        DoCmdWaitForInviteCanceled(aSection);
        }     
    else if ( aCommand==KCmdWaitForErrorOccured )
        {
        DoCmdWaitForErrorOccured(aSection);
        }    
    else
        {
        ret=EFalse;
        }
    return ret;
    }

void CT_DataSIPConnection::DisownObjectL()
    {
    iSIPConnection = NULL;
    iIsOwner = EFalse;
    }

void CT_DataSIPConnection::DoCmdNewL(const TTEFSectionName& aSection)
    {
    TPtrC datIapName;
    TPtrC datSipProfile;
    if (!GetStringFromConfig(aSection, KFldIAPID, datIapName))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldIAPID);
        SetBlockResult(EFail);
        return;
        }
       
    if (!GetStringFromConfig(aSection, KFldSIP, datSipProfile))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIP);
        SetBlockResult(EFail);
        return;
        }
    
    CSIP* sip = static_cast<CSIP*>(GetDataObjectL(datSipProfile));
    INFO_PRINTF1(_L("call CSIPConnection::NewL()"));
    TRAPD(err, iSIPConnection = CSIPConnection::NewL(*sip, ConvertIAPNameToID(datIapName), *this));
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = ETrue;
    
    TPtrC datExpectedState;
    if (GetStringFromConfig(aSection, KFldExpectedState, datExpectedState))
        {
        iCheckState = ETrue;
        CT_SIPUtil::ConvertStringToEnumState(datExpectedState, iExpectedState);
        IncOutstanding();
        }
    }

TUint32 CT_DataSIPConnection::ConvertIAPNameToID(TDesC& iapName)
    {
    TUint32 apId = CT_SIPUtil::GetIAPIDL(iapName);
    if(apId == 0)
        {
        apId = CT_SIPUtil::AddAccessPointL(iapName);
        INFO_PRINTF3(_L("Add a new IAP (name = %S and ID = [%d])"), &iapName, apId );
        }
    else
        {
        INFO_PRINTF3(_L("IAP (name = %S) found with IAP (ID = [%d])"), &iapName, apId );
        }
    
    if(apId == 0)
        {
        ERR_PRINTF1(_L("Failed to add a IAP."));
        SetBlockResult(EFail);
        return 0;
        }
    
    return apId;
    }

void CT_DataSIPConnection::DoCmdNewLC(const TTEFSectionName& aSection)
    {
    TPtrC datIapName;
    TPtrC datSipProfile;
    if (!GetStringFromConfig(aSection, KFldIAPID, datIapName))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldIAPID);
        SetBlockResult(EFail);
        return;
        }
            
    if (!GetStringFromConfig(aSection, KFldSIP, datSipProfile))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIP);
        SetBlockResult(EFail);
        return;
        }
        
    CSIP* sip = static_cast<CSIP*>(GetDataObjectL(datSipProfile));
    INFO_PRINTF1(_L("call CSIPConnection::NewLC()"));
    TRAPD(err, iSIPConnection = CSIPConnection::NewLC(*sip, ConvertIAPNameToID(datIapName), *this); CleanupStack::Pop());
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    iIsOwner = ETrue;
    
    TPtrC datExpectedState;
    if (GetStringFromConfig(aSection, KFldExpectedState, datExpectedState))
        {
        iCheckState = ETrue;
        CT_SIPUtil::ConvertStringToEnumState(datExpectedState, iExpectedState);
        IncOutstanding();
        }
    }

void CT_DataSIPConnection::DoCmdDestructor(const TTEFSectionName& /*aSection*/)
    {
    INFO_PRINTF1(_L("call CSIPConnection::~CSIPConnection()"));
    DestroyData();
    }

void CT_DataSIPConnection::DoCmdDisown()
    {
    iIsOwner = EFalse;
    }

void CT_DataSIPConnection::DoCmdState(const TTEFSectionName& aSection)
    {
    TPtrC datExpectedState;
    CSIPConnection::TState state;
    INFO_PRINTF1(_L("call CSIPConnection::State()"));
    state = iSIPConnection->State();
        
    if (GetStringFromConfig(aSection, KFldExpectedState, datExpectedState))
        {
        CSIPConnection::TState expectedState;
        if (!CT_SIPUtil::ConvertStringToEnumState(datExpectedState, expectedState))
            {
            ERR_PRINTF1(_L("Invalid ExpectedState string value in test data file!"));
            ERR_PRINTF1(datExpectedState);
            SetBlockResult(EFail);
            }
        
        if (state != expectedState)
            {
            ERR_PRINTF3(KLogNotExpectedValue, (TInt)state, (TInt)expectedState);
            SetBlockResult(EFail);
            }
        }
    else
        {
        INFO_PRINTF2(_L("State: %d"), state);
        }
    }

void CT_DataSIPConnection::DoCmdSendRequestL(const TTEFSectionName& aSection)
    {
    TPtrC datRequestElement;
    TPtrC datRegistrationBinding;
    TPtrC datRefresh;
    if (!GetStringFromConfig(aSection, KFldRequestElement, datRequestElement)) 
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldRequestElement);
        SetBlockResult(EFail);
        return;
        }
    
    CSIPRequestElements* requestElement = static_cast<CSIPRequestElements*>(GetDataObjectL(datRequestElement));
    CSIPClientTransaction* clientTransaction = NULL;
    TBool bRegistrationBinding = GetStringFromConfig(aSection, KFldRegistrationBinding, datRegistrationBinding);
    TBool bRefresh = GetStringFromConfig(aSection, KFldRefresh, datRefresh);
    INFO_PRINTF3(_L("RegistrationBinding exist: %d, Refresh exist: %d"), bRegistrationBinding, bRefresh);
    
    TInt err = KErrNone;
    // No KFldRegContext && No KFldRefresh
    if (!bRegistrationBinding && !bRefresh)
        {
        INFO_PRINTF1(_L("call CSIPConnection::SendRequestL(CSIPRequestElements*)"));
        TRAP(err, clientTransaction = iSIPConnection->SendRequestL(requestElement));
        }
    // Has KFldRegContext && No KFldRefresh
    else if (bRegistrationBinding && !bRefresh)
        {
        INFO_PRINTF1(_L("call CSIPConnection::SendRequestL(CSIPRequestElements*, const MSIPRegistrationContext&)"));
        CSIPRegistrationBinding* regBinding = static_cast<CSIPRegistrationBinding*>(GetDataObjectL(datRegistrationBinding));
        TRAP(err, clientTransaction = iSIPConnection->SendRequestL(requestElement, *regBinding));
        }
    // No KFldRegContext && Has KFldRefresh
    else if (!bRegistrationBinding && bRefresh)
        {
        INFO_PRINTF1(_L("call CSIPConnection::SendRequestL(CSIPRequestElements*, CSIPRefresh&)"));
        CSIPRefresh* refresh = static_cast<CSIPRefresh*>(GetDataObjectL(datRefresh));
        TRAP(err, clientTransaction = iSIPConnection->SendRequestL(requestElement, *refresh));
        }
    // Has KFldRegContext && Has KFldRefresh
    else if (bRegistrationBinding && bRefresh)
        {
        INFO_PRINTF1(_L("call CSIPConnection::SendRequestL(CSIPRequestElements*, const MSIPRegistrationContext&, CSIPRefresh&)"));
        CSIPRegistrationBinding* regBinding = static_cast<CSIPRegistrationBinding*>(GetDataObjectL(datRegistrationBinding));
        CSIPRefresh* refresh = static_cast<CSIPRefresh*>(GetDataObjectL(datRefresh));
        INFO_PRINTF2(_L("IsContextActive: %d"), regBinding->IsContextActive());
        TRAP(err, clientTransaction = iSIPConnection->SendRequestL(requestElement, *regBinding, *refresh));
        }
  
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    else
        {
        CT_DataSIPRequestElements* wrapper = static_cast<CT_DataSIPRequestElements*>(GetDataWrapperL(datRequestElement));
        wrapper->SetIsOwner(EFalse);
        
        TPtrC datClientTransaction;
        if (GetStringFromConfig(aSection, KFldClientTransaction, datClientTransaction))
            {
            SetDataObjectL(datClientTransaction, clientTransaction);
            }
        }
    }

void CT_DataSIPConnection::DoCmdFetchRegistrationsL(const TTEFSectionName& aSection)
    {
    TPtrC datReqElement;
    if (!GetStringFromConfig(aSection, KFldRequestElement, datReqElement)) 
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldRequestElement);
        SetBlockResult(EFail);
        return;
        }
    
    CSIPRequestElements* reqElement = static_cast<CSIPRequestElements*>(GetDataObjectL(datReqElement));
    CT_DataSIPRequestElements* wrapper = static_cast<CT_DataSIPRequestElements*>(GetDataWrapperL(datReqElement));
    wrapper->SetIsOwner(EFalse);
    CSIPClientTransaction* clientTransaction = NULL;

    INFO_PRINTF1(_L("call CSIPConnection::DoCmdFetchRegistrationsL(CSIPRequestElements*)"));
    TRAPD(err, clientTransaction = iSIPConnection->FetchRegistrationsL(reqElement));
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        return;
        }
    
    TPtrC datClientTransaction;
    if (GetStringFromConfig(aSection, KFldClientTransaction, datClientTransaction))
        {
        SetDataObjectL(datClientTransaction, clientTransaction);
        }
    }

void CT_DataSIPConnection::DoCmdIapId(const TTEFSectionName& aSection)
    {
    TPtrC datIapName;
    INFO_PRINTF1(_L("call CSIPConnection::IapId()"));
    TUint32 iapID = iSIPConnection->IapId();
    if (!GetStringFromConfig(aSection, KFldIAPID, datIapName))
        {
        TUint32 expectedIapID = ConvertIAPNameToID(datIapName);
        if (iapID != expectedIapID)
            {
            ERR_PRINTF3(KLogNotExpectedValue, (TInt)iapID, (TInt)expectedIapID);
            SetBlockResult(EFail);
            }
        }
    else
        {
        INFO_PRINTF2(_L("IAP ID: %d"), iapID);
        }
    }

void CT_DataSIPConnection::DoCmdSIP(const TTEFSectionName& aSection)
    {
    TBool datConstFlag;
    if (!GetBoolFromConfig(aSection, KFldConstFlag, datConstFlag))
        {
        ERR_PRINTF2(KLogMissingParameter, KFldExpectedState);
        SetBlockResult(EFail);
        return;
        }

    TPtrC datSip;
    GetStringFromConfig(aSection, KFldSIP, datSip);
    CT_DataSIP* wrapper = static_cast<CT_DataSIP*>(GetDataWrapperL(datSip));
    wrapper->SetIsOwner(EFalse);
    if (datConstFlag)
        {
        INFO_PRINTF1(_L("call const CSIPConnection::SIP() const"));
        const CSIP* constSip = ((const CSIPConnection*)iSIPConnection)->SIP();
        if (datSip.Length() != 0)
            {
            SetDataObjectL(datSip, const_cast<CSIP*>(constSip));
            }
        }
    else
        {
        INFO_PRINTF1(_L("call CSIPConnection::SIP()"));
        CSIP* sip = iSIPConnection->SIP();
        if (datSip.Length() != 0)
            {
            SetDataObjectL(datSip, sip);
            }
        }
    }
    
void CT_DataSIPConnection::DoCmdSetOptL(const TTEFSectionName& aSection)
    {
    TPtrC datOptName;
    if (!GetStringFromConfig(aSection, KFldOptionName, datOptName))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldOptionName);
        SetBlockResult(EFail);
        return;
        }
    
    TUint optName;
    if (!GetOptNameIntValue(datOptName, optName))
        {
        ERR_PRINTF1(_L("Invalid string option name value!"));
        ERR_PRINTF1(datOptName);
        SetBlockResult(EFail);
        return;
        }
    
    TPtrC datOptLevel;
    if (!GetStringFromConfig(aSection, KFldOptionLevel, datOptLevel))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldOptionLevel);
        SetBlockResult(EFail);
        return;
        }
    
    TUint optLevel;
    if (datOptLevel == _L("KSOLSocket"))
        {
        optLevel = KSOLSocket;
        }
    else
        {
        optLevel = KLevelUnspecified;
        }

    TPtrC datOptValueType;
    if (!GetStringFromConfig(aSection, KFldOptionValueType, datOptValueType))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldOptionValueType);
        SetBlockResult(EFail);
        return;
        }
    
    if (datOptValueType == _L("Integer"))
        {
        TInt datOptIntValue;
        if (!GetIntFromConfig(aSection, KFldOptionValue, datOptIntValue))
            {
            ERR_PRINTF2(KLogMissingParameter, &KFldOptionValue);
            SetBlockResult(EFail);
            return;
            }
        
        INFO_PRINTF1(_L("call CSIPConnection::SetOptL(TUint, TUint, TInt)"));
        TRAPD(err, iSIPConnection->SetOptL(optName, optLevel, datOptIntValue));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else if (datOptValueType == _L("String"))
        {
        TPtrC datOptStringValue;
        if (!GetStringFromConfig(aSection, KFldOptionValue, datOptStringValue))
            {
            ERR_PRINTF2(KLogMissingParameter, &KFldOptionValue);
            SetBlockResult(EFail);
            return;
            }
        
        TBuf8<128> optValue;
        CT_SIPUtil::ConvertToUtf8(datOptStringValue, optValue);
        INFO_PRINTF1(_L("call CSIPConnection::SetOptL(TUint, TUint, const TDesC8&)"));
        TRAPD(err, iSIPConnection->SetOptL(optName, optLevel, optValue));
        if(KErrNone != err)
            {
            ERR_PRINTF2(KLogError, err);
            SetError(err);
            }
        }
    else
        {
        ERR_PRINTF1(_L("Invalid option value type!"));
        ERR_PRINTF1(datOptValueType);
        SetBlockResult(EFail);
        }
    }

TBool CT_DataSIPConnection::GetOptNameIntValue(TPtrC& aStrOptName, TUint& aName)
    {
    TBool ret = ETrue;
    if (aStrOptName == _L("KSODebug"))
        {
        aName = KSODebug;
        }
    else if (aStrOptName == _L("KSORecvBuf"))
        {
        aName = KSORecvBuf;
        }
    else if (aStrOptName == _L("KSOSendBuf"))
        {
        aName = KSOSendBuf;
        }
    else if (aStrOptName == _L("KSONonBlockingIO"))
        {
        aName = KSONonBlockingIO;
        }
    else if (aStrOptName == _L("KSOBlockingIO"))
        {
        aName = KSOBlockingIO;
        }
    else if (aStrOptName == _L("KSOSelectPoll"))
        {
        aName = KSOSelectPoll;
        }
    else if (aStrOptName == _L("KSOReadBytesPending"))
        {
        aName = KSOReadBytesPending;
        }
    else if (aStrOptName == _L("KSOUrgentDataOffset"))
        {
        aName = KSOUrgentDataOffset;
        }
    else if (aStrOptName == _L("KSOSelectLastError"))
        {
        aName = KSOSelectLastError;
        }
    else if (aStrOptName == _L("KSOEnableTransfer"))
        {
        aName = KSOEnableTransfer;
        }
    else if (aStrOptName == _L("KSODisableTransfer"))
        {
        aName = KSODisableTransfer;
        }
    else
        {
        ret = EFalse;
        }
    return ret;
    }

void CT_DataSIPConnection::DoCmdGetLocalAddrL(const TTEFSectionName& aSection)
    {
    TInetAddr addr;
    INFO_PRINTF1(_L("call CSIPConnection::GetLocalAddrL()"));
    TRAPD(err, iSIPConnection->GetLocalAddrL(addr));
    if(KErrNone != err)
        {
        ERR_PRINTF2(KLogError, err);
        SetError(err);
        }
    TBuf<20> strAddr;
    addr.Output(strAddr);
    
    TPtrC datAddr;
    if (!GetStringFromConfig(aSection, KFldLocalAddr, datAddr))
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldLocalAddr);
        SetBlockResult(EFail);
        return;
        }
    
    if (datAddr.Length() != 0)
        {
        TInetAddr expectedAddr;
        expectedAddr.Input(datAddr);
        if (!expectedAddr.CmpAddr(addr))
            {
            TBuf<20> strAddr;
            TBuf<20> strExpectedAddr;
            expectedAddr.Output(strExpectedAddr);
            addr.Output(strAddr);
            ERR_PRINTF1(_L("Local address does not match!"));
            ERR_PRINTF2(_L("Local address: %S"), &strAddr);
            ERR_PRINTF2(_L("Expected address: %S"), &strExpectedAddr);
            SetBlockResult(EFail);
            return;
            }
        }
    
    INFO_PRINTF2(_L("Local address: %S"), &strAddr);
    }
    
void CT_DataSIPConnection::DoCmdWaitForIncomingRequest(const TTEFSectionName& aSection)
    {
    iTEFSectionName = aSection;
    IncOutstanding();
    }

void CT_DataSIPConnection::DoCmdWaitForIncomingResponse(const TTEFSectionName& aSection)
    {
    iTEFSectionName = aSection;
    IncOutstanding();
    iCount++;
    }

void CT_DataSIPConnection::DoCmdWaitForInviteCompleted(const TTEFSectionName& aSection)
    {
    iTEFSectionName = aSection;
    IncOutstanding();
    }
    
void CT_DataSIPConnection::DoCmdWaitForInviteCanceled(const TTEFSectionName& aSection)
    {
    iTEFSectionName = aSection;
    IncOutstanding();
    }   

void CT_DataSIPConnection::DoCmdWaitForErrorOccured(const TTEFSectionName& aSection)
    {
    iTEFSectionName = aSection;
    IncOutstanding();
    }

void CT_DataSIPConnection::DestroyData()
    {
    if(iIsOwner && iSIPConnection)
        {
        delete iSIPConnection;
        iSIPConnection = NULL;
        iIsOwner = EFalse;
        }
    }

void CT_DataSIPConnection::SetIsOwner(TBool aIsOwner)
    {
    iIsOwner = aIsOwner;
    }

void CT_DataSIPConnection::IncomingRequest (CSIPServerTransaction* aTransaction)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::IncomingRequest(CSIPServerTransaction*)"));

    TBuf<50> val;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, aTransaction->Type().DesC());
    INFO_PRINTF2(_L("Incoming Request: %S"), &val);
    
    TPtrC wrapperName;
    if( !GetStringFromConfig(iTEFSectionName, KFldServTransaction, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldServTransaction);
        SetBlockResult(EFail);
        }
    else
        {
        SetDataObjectL(wrapperName, aTransaction);
        }
    
    DecOutstanding();
    }

void CT_DataSIPConnection::IncomingRequest (CSIPServerTransaction* aTransaction, CSIPDialog& aDialog)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::IncomingRequest(CSIPServerTransaction*, CSIPDialog&)"));
    
    TBuf<50> val;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, aTransaction->Type().DesC());
    INFO_PRINTF2(_L("Incoming Request: %S"), &val);
    
    TPtrC wrapperName;
    if( !GetStringFromConfig(iTEFSectionName, KFldServTransaction, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldServTransaction);
        SetBlockResult(EFail);
        }
    else
        {
        SetDataObjectL(wrapperName, aTransaction);
        }    
    
    if( !GetStringFromConfig(iTEFSectionName, KFldSIPDialog, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldSIPDialog);
        SetBlockResult(EFail);
        }
    else
        {
        CT_DataSIPDialog* wrapper = static_cast<CT_DataSIPDialog*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, &aDialog);
        }
    
    DecOutstanding();
    }

void CT_DataSIPConnection::IncomingResponse (CSIPClientTransaction& aTransaction)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::IncomingResponse(CSIPClientTransaction&)"));
    
    TBuf<50> val;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, aTransaction.Type().DesC());
    INFO_PRINTF2(_L("Incoming Response Type: %S"), &val);
    
    const CSIPResponseElements* response = aTransaction.ResponseElements();
    INFO_PRINTF2(_L("Incoming Response Status Code: %d"), response->StatusCode());
    
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, response->ReasonPhrase().DesC());
    INFO_PRINTF2(_L("Incoming Response Reason Phrase: %S"), &val);

    TPtrC wrapperName;
    if( GetStringFromConfig(iTEFSectionName, KFldClientTransaction, wrapperName) )
        {
        CT_DataSIPClientTransaction* wrapper = static_cast<CT_DataSIPClientTransaction*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, &aTransaction);
        }
    
    DecOutstanding();
    }

void CT_DataSIPConnection::IncomingResponse (CSIPClientTransaction& aTransaction, CSIPDialogAssocBase& aDialogAssoc)
    {
    if(iCount == 0)
        {
        return;
        }
    else
        {
        iCount--;
        }
        
    INFO_PRINTF1(_L("call MSIPConnectionObserver::IncomingResponse(CSIPClientTransaction&, CSIPDialogAssocBase&)"));
    
    TBuf<50> val;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, aTransaction.Type().DesC());
    INFO_PRINTF2(_L("Incoming Response Type: %S"), &val);
    
    const CSIPResponseElements* response = aTransaction.ResponseElements();
    INFO_PRINTF2(_L("Incoming Response Status Code: %d"), response->StatusCode());
    
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, response->ReasonPhrase().DesC());
    INFO_PRINTF2(_L("Incoming Response Reason Phrase: %S"), &val);

    TPtrC wrapperName;
    if( GetStringFromConfig(iTEFSectionName, KFldClientTransaction, wrapperName) )
        {
        CT_DataSIPClientTransaction* wrapper = static_cast<CT_DataSIPClientTransaction*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, &aTransaction);
        }
    
    if( !GetStringFromConfig(iTEFSectionName, KFldDialogAssocBase, wrapperName) )
        {
        if ( aDialogAssoc.Type() == SIPStrings::StringF( SipStrConsts::EInvite )  )
            {
            CSIPInviteDialogAssoc* invite = dynamic_cast<CSIPInviteDialogAssoc*>( &aDialogAssoc );
            CT_DataSIPInviteDialogAssoc* wrapper = static_cast<CT_DataSIPInviteDialogAssoc*>(GetDataWrapperL(wrapperName));
            wrapper->SetIsOwner(EFalse);
            SetDataObjectL(wrapperName, invite);
            }
        }
    
    DecOutstanding();
    }

void CT_DataSIPConnection::IncomingResponse (CSIPClientTransaction& aTransaction, CSIPInviteDialogAssoc* aDialogAssoc)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::IncomingResponse(CSIPClientTransaction&, CSIPInviteDialogAssoc*)"));
    
    TBuf<50> val;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, aTransaction.Type().DesC());
    INFO_PRINTF2(_L("Incoming Response Type: %S"), &val);
    
    const CSIPResponseElements* response = aTransaction.ResponseElements();
    INFO_PRINTF2(_L("Incoming Response Status Code: %d"), response->StatusCode());
    
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, response->ReasonPhrase().DesC());
    INFO_PRINTF2(_L("Incoming Response Reason Phrase: %S"), &val);

    TPtrC wrapperName;
    if( GetStringFromConfig(iTEFSectionName, KFldClientTransaction, wrapperName) )
        {
        CT_DataSIPClientTransaction* wrapper = static_cast<CT_DataSIPClientTransaction*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, &aTransaction);
        }
    
    if( !GetStringFromConfig(iTEFSectionName, KFldDialogAssocBase, wrapperName) )
        {
        ERR_PRINTF2(KLogMissingParameter, &KFldDialogAssocBase);
        SetBlockResult(EFail);
        }
    else
        {
        if ( aDialogAssoc->Type() == SIPStrings::StringF( SipStrConsts::EInvite )  )
            {
            CSIPInviteDialogAssoc* invite = dynamic_cast<CSIPInviteDialogAssoc*>( aDialogAssoc );
            SetDataObjectL(wrapperName, invite);
            }
        }
    
    DecOutstanding();
    }

void CT_DataSIPConnection::IncomingResponse (CSIPClientTransaction& aTransaction, CSIPRegistrationBinding& aRegistration)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::IncomingResponse(CSIPClientTransaction&, CSIPRegistrationBinding&)"));

    TBuf<50> val;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, aTransaction.Type().DesC());
    INFO_PRINTF2(_L("Incoming Response Type: %S"), &val);
    
    const CSIPResponseElements* response = aTransaction.ResponseElements();
    INFO_PRINTF2(_L("Incoming Response Status Code: %d"), response->StatusCode());
    
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, response->ReasonPhrase().DesC());
    INFO_PRINTF2(_L("Incoming Response Reason Phrase: %S"), &val);
    
    TPtrC wrapperName;
    if( GetStringFromConfig(iTEFSectionName, KFldClientTransaction, wrapperName) )
        {
        CT_DataSIPClientTransaction* wrapper = static_cast<CT_DataSIPClientTransaction*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, &aTransaction);
        }
    
    if( GetStringFromConfig(iTEFSectionName, KFldRegistrationBinding, wrapperName) )
        {
        CT_DataSIPRegistrationBinding* wrapper = static_cast<CT_DataSIPRegistrationBinding*>(GetDataWrapperL(wrapperName));
        wrapper->SetIsOwner(EFalse);
        SetDataObjectL(wrapperName, &aRegistration);
        }

    DecOutstanding();
    }

void CT_DataSIPConnection::ErrorOccured (TInt aError, CSIPTransactionBase& /*aTransaction*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ErrorOccured(TInt, CSIPTransactionBase&)"));
    INFO_PRINTF2(KLogError, aError);
    }

void CT_DataSIPConnection::ErrorOccured (TInt aError, CSIPClientTransaction& /*aTransaction*/, CSIPRegistrationBinding& /*aRegistration*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ErrorOccured(TInt, CSIPClientTransaction&, CSIPRegistrationBinding&)"));
    TInt errorcode;
    if( GetIntFromConfig(iTEFSectionName, KFldErrorCode, errorcode) )
        {
        if(errorcode==aError)
            {
            INFO_PRINTF3(_L("The actual error code matched the expected,actual = %d,expected = %d"),aError,errorcode);
            }
        else
            {
            ERR_PRINTF3(KLogNotExpectedValue, aError,errorcode);
            SetBlockResult(EFail);
            }
        }
    DecOutstanding();
    }

void CT_DataSIPConnection::ErrorOccured (TInt aError, CSIPTransactionBase& /*aTransaction*/, CSIPDialogAssocBase& /*aDialogAssoc*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ErrorOccured(TInt, CSIPTransactionBase&, CSIPDialogAssocBase)"));
    INFO_PRINTF2(KLogError, aError);
    }

void CT_DataSIPConnection::ErrorOccured (TInt aError, CSIPRefresh& /*aSIPRefresh*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ErrorOccured(TInt, CSIPRefresh&)"));
    INFO_PRINTF2(KLogError, aError);
    }

void CT_DataSIPConnection::ErrorOccured (TInt aError, CSIPRegistrationBinding& /*aRegistration*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ErrorOccured(TInt, CSIPRegistrationBinding&)"));
    INFO_PRINTF2(KLogError, aError);
    }

void CT_DataSIPConnection::ErrorOccured (TInt aError,   CSIPDialogAssocBase& /*aDialogAssoc*/)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ErrorOccured(TInt, CSIPDialogAssocBase&)"));
    INFO_PRINTF2(KLogError, aError);
    }

void CT_DataSIPConnection::InviteCompleted (CSIPClientTransaction& aTransaction)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::InviteCompleted(CSIPClientTransaction&)"));
    
    TBuf<50> val;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, aTransaction.Type().DesC());
    INFO_PRINTF2(_L("Incoming Response Type: %S"), &val);
    
    const CSIPResponseElements* response = aTransaction.ResponseElements();
    INFO_PRINTF2(_L("Incoming Response Status Code: %d"), response->StatusCode());
    
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, response->ReasonPhrase().DesC());
    INFO_PRINTF2(_L("Incoming Response Reason Phrase: %S"), &val);
    
    DecOutstanding();
    }

void CT_DataSIPConnection::InviteCanceled (CSIPServerTransaction& aTransaction)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::InviteCanceled(CSIPServerTransaction&)"));
    
    TBuf<50> val;
    CnvUtfConverter::ConvertToUnicodeFromUtf8(val, aTransaction.Type().DesC());
    INFO_PRINTF2(_L("Incoming Request: %S"), &val);
    
    DecOutstanding();
    }

void CT_DataSIPConnection::ConnectionStateChanged (CSIPConnection::TState aState)
    {
    INFO_PRINTF1(_L("call MSIPConnectionObserver::ConnectionStateChanged(CSIPConnection::TState)"));
    INFO_PRINTF2(_L("Connection state: %d"), aState);
    if (iCheckState)
        {
        if (iExpectedState != aState)
            {
            ERR_PRINTF3(KLogNotExpectedValue, aState, iExpectedState);
            SetBlockResult(EFail);
            }
        DecOutstanding();
        }
    }
