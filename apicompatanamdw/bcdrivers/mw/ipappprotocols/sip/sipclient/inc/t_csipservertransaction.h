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


// This contains CT_DataSIPServerTransaction

#ifndef __T_SIPSERVERTRANSACTION__
#define __T_SIPSERVERTRANSACTION__

//  User includes
#include "t_csiptransactionbase.h" 
#include <sipservertransaction.h>

class CT_DataSIPServerTransaction : public CT_DataSIPTransactionBase
	{
public:
    static CT_DataSIPServerTransaction* NewL();
    ~CT_DataSIPServerTransaction();
    
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();

protected:
    CT_DataSIPServerTransaction();
    void ConstructL();
    virtual CSIPTransactionBase* GetSIPTransactionBaseObject() const; 
    
private:
	void DoCmdRequestElementsL(const TTEFSectionName& aSection);
	void DoCmdResponseAllowed(const TTEFSectionName& aSection);
	void DoCmdSendResponseL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();

private:
    CSIPServerTransaction* iSIPServerTransaction;
	};

#endif /* __T_SIPSERVERTRANSACTION__ */

