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


// This contains CT_DataSIPManagedProfileRegistry

#ifndef T_CSIPMANAGEDPROFILEREGISTRY_H__
#define T_CSIPMANAGEDPROFILEREGISTRY_H__

#include <sipmanagedprofileregistry.h> 
#include <testexecutestepbase.h>
#include "t_csipprofileregistrybase.h"

class CT_DataSIPManagedProfileRegistry : public CT_DataSIPProfileRegistryBase
    {
public:
	static CT_DataSIPManagedProfileRegistry*	NewL();
	~CT_DataSIPManagedProfileRegistry();
	
	virtual TBool	DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObjectL();
	void			DestroyData();	
	
protected:	
	CT_DataSIPManagedProfileRegistry();
	virtual CSIPProfileRegistryBase*	GetSIPProfileRegistryBase() const;
	void           ConstructL();
	
private:
	
	void           DoCmdCreateL(const TTEFSectionName& aSection);
	void           DoCmdDestroyL(const TTEFSectionName& aSection);
	void           DoCmdIsInUseL(const TTEFSectionName& aSection);
	void           DoCmdNewL();
	void           DoCmdNewLC();
	void           DoCmdSaveL(const TTEFSectionName& aSection);
	void           DoCmdDestructor();	

private:
	CSIPManagedProfileRegistry* iSIPManagedProfileRegistry;
    };

#endif /*T_CSIPMANAGEDPROFILEREGISTRY_H__*/
