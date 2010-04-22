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
 * This contains CT_DataSdpMediaField
 */


#ifndef __T_DATASDPMEDIAFIELD_H__
#define __T_DATASDPMEDIAFIELD_H__

#include "DataWrapperBase.h"
#include <sdpmediafield.h> 

class CT_DataSdpMediaField : public CDataWrapperBase 
    {
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	~CT_DataSdpMediaField();
	static CT_DataSdpMediaField* NewL();
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObjectL();

	void SetIsOwner(TBool aIsOwner);
	
protected:
	CT_DataSdpMediaField();
	void ConstructL();
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
	void DestroyData();
	
private:
    CSdpMediaField* iSdpMediaField;
    TBool iIsOwner;
    };

#endif /*__T_DATASDPMEDIAFIELD_H__*/

