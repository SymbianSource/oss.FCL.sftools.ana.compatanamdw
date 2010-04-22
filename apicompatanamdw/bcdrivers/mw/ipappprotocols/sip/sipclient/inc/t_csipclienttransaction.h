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


// This contains CT_DataSIPClientTransaction

#ifndef __T_SIPCLIENTTRANSACTION__
#define __T_SIPCLIENTTRANSACTION__

//  User includes
#include "t_csiptransactionbase.h" 
#include <sipclienttransaction.h>

class CT_DataSIPClientTransaction : public CT_DataSIPTransactionBase
	{
public:
    static CT_DataSIPClientTransaction* NewL();
    ~CT_DataSIPClientTransaction();
    
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    void            SetIsOwner(TBool aIsOwner);
    
protected:
    CT_DataSIPClientTransaction();
    void ConstructL();
    virtual CSIPTransactionBase* GetSIPTransactionBaseObject() const; 
    
private:
	void DoCmdCancelAllowed(const TTEFSectionName& aSection);
	void DoCmdCancelL(const TTEFSectionName& aSection);
	void DoCmdRefreshL(const TTEFSectionName& aSection);
	void DoCmdResponseElementsL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();

private:
    CSIPClientTransaction* iSIPClientTransaction;
    TBool                  iIsOwner;
	};

#endif /* __T_SIPCLIENTTRANSACTION__ */

