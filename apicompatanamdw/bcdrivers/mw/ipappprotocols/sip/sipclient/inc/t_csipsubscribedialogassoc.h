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


// This contains CT_DataSIPSubscribeDialogAssoc

#ifndef T_CSIPSUBSCRIBLEDIALOGASSOC_H_
#define T_CSIPSUBSCRIBLEDIALOGASSOC_H_

#include "DataWrapperBase.h"
#include "t_csipdialogassocbase.h" 

#include <sipsubscribedialogassoc.h>

class CT_DataSIPSubscribeDialogAssoc : public CT_DataSIPDialogAssocBase
    {
public:
    static CT_DataSIPSubscribeDialogAssoc* NewL();
    ~CT_DataSIPSubscribeDialogAssoc();
    
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    void            SetIsOwner(TBool aIsOwner);
    
protected:
    CT_DataSIPSubscribeDialogAssoc();
    void ConstructL();
    virtual CSIPDialogAssocBase* GetSIPDialogAssocBase() const; 
    
private:
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdEvent(const TTEFSectionName& aSection);
    void DoCmdSIPRefresh(const TTEFSectionName& aSection);
    void DoCmdSendSubscribeL(const TTEFSectionName& aSection);
    void DoCmdSendUnsubscribeL(const TTEFSectionName& aSection);
    void DoCmdUpdateL(const TTEFSectionName& aSection);
    void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();

private:
    CSIPSubscribeDialogAssoc* iSIPSubscribeDialogAssoc;
    TBool                  iIsOwner;
    };

#endif /* T_CSIPSUBSCRIBLEDIALOGASSOC_H_ */
