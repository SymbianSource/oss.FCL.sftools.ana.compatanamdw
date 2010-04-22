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


// This contains CT_DataSIPConnection
#ifndef T_DATASIPCONNECTION_H_
#define T_DATASIPCONNECTION_H_
#include <testexecutestepbase.h>
#include <sipprofileregistryobserver.h>
#include <sipobserver.h>
#include <sipconnectionobserver.h>
#include <sipmanagedprofileregistry.h>
#include <sipmanagedprofile.h>
#include <es_sock.h>
#include <sip.h> 
//#include <sipprofilealrobserver.h> 
//#include <sipprofilealrcontroller.h>
#include <f32file.h>
#include "DataWrapperBase.h"

class CT_DataSIPConnection : public CDataWrapperBase, public MSIPConnectionObserver   
    {
public:
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    ~CT_DataSIPConnection();
    static CT_DataSIPConnection* NewL();
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    
    void SetIsOwner(TBool aIsOwner);
    
public:
    // Function implementation of MSIPConnectionObserver
    virtual void IncomingRequest (CSIPServerTransaction* aTransaction);
    virtual void IncomingRequest (CSIPServerTransaction* aTransaction, CSIPDialog& aDialog);
    virtual void IncomingResponse (CSIPClientTransaction& aTransaction);
    virtual void IncomingResponse (CSIPClientTransaction& aTransaction, CSIPDialogAssocBase& aDialogAssoc);
    virtual void IncomingResponse (CSIPClientTransaction& aTransaction, CSIPInviteDialogAssoc* aDialogAssoc);
    virtual void IncomingResponse (CSIPClientTransaction& aTransaction, CSIPRegistrationBinding& aRegistration);
    virtual void ErrorOccured (TInt aError, CSIPTransactionBase& aTransaction);
    virtual void ErrorOccured (TInt aError, CSIPClientTransaction& aTransaction, CSIPRegistrationBinding& aRegistration);
    virtual void ErrorOccured (TInt aError, CSIPTransactionBase& aTransaction, CSIPDialogAssocBase& aDialogAssoc);
    virtual void ErrorOccured (TInt aError, CSIPRefresh& aSIPRefresh);
    virtual void ErrorOccured (TInt aError, CSIPRegistrationBinding& aRegistration);
    virtual void ErrorOccured (TInt aError, CSIPDialogAssocBase& aDialogAssoc);
    virtual void InviteCompleted (CSIPClientTransaction& aTransaction);
    virtual void InviteCanceled (CSIPServerTransaction& aTransaction);
    virtual void ConnectionStateChanged (CSIPConnection::TState aState);
            
protected:
    CT_DataSIPConnection();
    void ConstructL();
    
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdDestructor(const TTEFSectionName& aSection);
    void DoCmdDisown();
    void DoCmdState(const TTEFSectionName& aSection);
    void DoCmdSendRequestL(const TTEFSectionName& aSection);
    void DoCmdFetchRegistrationsL(const TTEFSectionName& aSection);
    void DoCmdIapId(const TTEFSectionName& aSection);
    void DoCmdSIP(const TTEFSectionName& aSection);
    void DoCmdSetOptL(const TTEFSectionName& aSection);
    void DoCmdGetLocalAddrL(const TTEFSectionName& aSection);
    void DoCmdWaitForIncomingRequest(const TTEFSectionName& aSection);
    void DoCmdWaitForIncomingResponse(const TTEFSectionName& aSection);
    void DoCmdWaitForInviteCompleted(const TTEFSectionName& aSection);
    void DoCmdWaitForInviteCanceled(const TTEFSectionName& aSection);
    void DoCmdWaitForErrorOccured(const TTEFSectionName& aSection);
    
    void DestroyData();
    TBool ConvertStringToEnumState(TPtrC& aStrState, CSIPConnection::TState& aState);
    TBool GetOptNameIntValue(TPtrC& aStrOptName, TUint& aName);
    TUint32 ConvertIAPNameToID(TDesC& iapName);
    
private:
    CSIPConnection* iSIPConnection;
    TBool iIsOwner;
    TTEFSectionName iTEFSectionName;
    TBool iCheckState;
    CSIPConnection::TState iExpectedState;
    TInt iCount;
    };

#endif /*T_DATASIPCONNECTION_H_*/

