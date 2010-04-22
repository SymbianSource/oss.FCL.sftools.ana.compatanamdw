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


#ifndef __T_CSIPPROFILEREGISTRY_H_
#define __T_CSIPPROFILEREGISTRY_H_

#include "t_csipprofileregistrybase.h"
#include <testexecutestepbase.h>
#include <sipprofileregistry.h> 
#include <sipconnectionobserver.h>

class CT_DataSIPProfileRegistry : public CT_DataSIPProfileRegistryBase, public MSIPConnectionObserver
    {
public:
	static CT_DataSIPProfileRegistry* NewL();
	~CT_DataSIPProfileRegistry();
	
	virtual TBool	DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObjectL();

public: // from MSIPConnectionObserver
	void IncomingRequest (CSIPServerTransaction* aTransaction);
	void IncomingRequest (CSIPServerTransaction* aTransaction, CSIPDialog& aDialog);
	void IncomingResponse (CSIPClientTransaction& aTransaction);
	void IncomingResponse (CSIPClientTransaction& aTransaction, CSIPDialogAssocBase& aDialogAssoc);
	void IncomingResponse (CSIPClientTransaction& aTransaction, CSIPInviteDialogAssoc* aDialogAssoc);
	void IncomingResponse (CSIPClientTransaction& aTransaction, CSIPRegistrationBinding& aRegistration);
	void ErrorOccured (TInt aError, CSIPTransactionBase& aTransaction);
	void ErrorOccured (TInt aError, CSIPClientTransaction& aTransaction, CSIPRegistrationBinding& aRegistration);
	void ErrorOccured (TInt aError, CSIPTransactionBase& aTransaction, CSIPDialogAssocBase& aDialogAssoc);
	void ErrorOccured (TInt aError, CSIPRefresh& aSIPRefresh);
	void ErrorOccured (TInt aError, CSIPRegistrationBinding& aRegistration);
	void ErrorOccured (TInt aError,	CSIPDialogAssocBase& aDialogAssoc);
    void InviteCompleted (CSIPClientTransaction& aTransaction);
    void InviteCanceled (CSIPServerTransaction& aTransaction);
	void ConnectionStateChanged (CSIPConnection::TState aState);
	
protected:
	CT_DataSIPProfileRegistry();
	void ConstructL();
	
	virtual CSIPProfileRegistryBase* GetSIPProfileRegistryBase() const;
	
private:
	void DoCmdConnectionL(const TTEFSectionName& aSection);
	void DoCmdDisableL(const TTEFSectionName& aSection);
	void DoCmdEnableL(const TTEFSectionName& aSection);
	void DoCmdIsEnabledL(const TTEFSectionName& aSection);
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
	void DoCmdSIPL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
	void DestroyData();
	
private:
	CSIPProfileRegistry* iSIPProfileRegistry;
    };

#endif /*__T_CSIPPROFILEREGISTRY_H_*/
