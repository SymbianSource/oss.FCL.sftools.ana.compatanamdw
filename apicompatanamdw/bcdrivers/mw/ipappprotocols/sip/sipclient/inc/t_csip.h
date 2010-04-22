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


// This contains CT_DataSIP
#ifndef T_DATASIP_H_
#define T_DATASIP_H_

#include "DataWrapperBase.h"
#include <testexecutestepbase.h>
#include <sip.h> 
#include <sipobserver.h> 

class CSIPServerTransaction;

class CT_DataSIP : public CDataWrapperBase, public MSIPObserver 
    {
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	~CT_DataSIP();
	static CT_DataSIP* NewL();
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObjectL();

	void SetIsOwner(TBool aIsOwner);
	
public:
	void IncomingRequest(TUint32,CSIPServerTransaction *);
	void TimedOut(CSIPServerTransaction &);
	
protected:
	CT_DataSIP();
	void ConstructL();
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
	void DoCmdConnection(const TTEFSectionName& aSection);
	void DoCmdIsSigCompSupportedL(const TTEFSectionName& aSection);
	void DoCmdNegotiatedSecurityMechanismL(const TTEFSectionName& aSection);
	void DoCmdSupportedSecurityMechanismsL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
	void DestroyData();
	
private:
	CSIP* iSIP;
	TBool iIsOwner;
    };

#endif /*T_DATASIP_H_*/

