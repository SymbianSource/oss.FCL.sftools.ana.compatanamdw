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
 * This contains CT_DataSdpConnectionField
 */


#ifndef __T_DATASDPCONNECTIONFIELD_H__
#define __T_DATASDPCONNECTIONFIELD_H__

#include "DataWrapperBase.h"
#include <testexecutestepbase.h>
#include <sdpconnectionfield.h> 

class CT_DataSdpConnectionField : public CDataWrapperBase 
    {
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	~CT_DataSdpConnectionField();
	static CT_DataSdpConnectionField* NewL();
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObjectL();

	void SetIsOwner(TBool aIsOwner);
	
protected:
	CT_DataSdpConnectionField();
	void ConstructL();
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
	void DestroyData();
	
private:
    CSdpConnectionField* iSdpConnectionField;
    TBool iIsOwner;
    };

#endif /*__T_DATASDPCONNECTIONFIELD_H__*/

