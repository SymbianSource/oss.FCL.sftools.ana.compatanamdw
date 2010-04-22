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
 * This contains CT_DataSIPAddress
 */


#ifndef __T_DATASIPADDRESS_H__
#define __T_DATASIPADDRESS_H__

#include "DataWrapperBase.h"
#include <testexecutestepbase.h>
#include <sipaddress.h> 

class CT_DataSIPAddress : public CDataWrapperBase 
    {
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	~CT_DataSIPAddress();
	static CT_DataSIPAddress* NewL();
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObjectL();

	void SetIsOwner(TBool aIsOwner);
	
protected:
	CT_DataSIPAddress();
	void ConstructL();
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
	void DoCmdDecodeL(const TTEFSectionName& aSection);
	void DoCmdDisplayName(const TTEFSectionName& aSection);
	void DoCmdSetDisplayNameL(const TTEFSectionName& aSection);	
	void DoCmdUri8(const TTEFSectionName& aSection);
	void DoCmdSetUri8L(const TTEFSectionName& aSection);
	void DoCmdToTextLC(const TTEFSectionName& aSection);
	void DoCmdInternalizeL(const TTEFSectionName& aSection);
	void DoCmdExternalizeL(const TTEFSectionName& aSection);
	void DoCmdURI(const TTEFSectionName& aSection);	
	void DoCmdCompare(const TTEFSectionName& aSection); // operator==() 
	void DoCmdDestructor(const TTEFSectionName& aSection);
	void DestroyData();
	
private:
    CSIPAddress* iSIPAddress;
    TBool iIsOwner;
    };

#endif /*__T_DATASIPADDRESS_H__*/

