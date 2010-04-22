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


// This contains CT_DataSIPTransactionBase

#ifndef __T_SIPTRANSACTIONBASE__
#define __T_SIPTRANSACTIONBASE__

//	User includes
#include "DataWrapperBase.h"
#include <testexecutestepbase.h>

// Epoc includes
#include <siptransactionbase.h> 

class CT_DataSIPTransactionBase : public CDataWrapperBase
	{
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	
protected:
	CT_DataSIPTransactionBase();
    virtual CSIPTransactionBase* GetSIPTransactionBaseObject() const = 0; 
    
private:
	void DoCmdType(const TTEFSectionName& aSection);
	void DoCmdStateL(const TTEFSectionName& aSection);  
	void DoCmdIsSIPClientTransaction(const TTEFSectionName& aSection);  
	void DoCmdCompare(const TTEFSectionName& aSection);  // operator ==()
	};

#endif /* __T_SIPTRANSACTIONBASE__ */

