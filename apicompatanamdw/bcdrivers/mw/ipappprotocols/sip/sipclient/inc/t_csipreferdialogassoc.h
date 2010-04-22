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


// This contains CT_DataSIPReferDialogAssoc

#ifndef __T_DATASIPREFERDIALOGASSOC_H__
#define __T_DATASIPREFERDIALOGASSOC_H__

//  User includes
#include "t_csipdialogassocbase.h" 
#include <sipreferdialogassoc.h>

class CT_DataSIPReferDialogAssoc : public CT_DataSIPDialogAssocBase
	{
public:
    static CT_DataSIPReferDialogAssoc* NewL();
    ~CT_DataSIPReferDialogAssoc();
    
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    void            SetIsOwner(TBool aIsOwner);
    
protected:
    CT_DataSIPReferDialogAssoc();
    void ConstructL();    
    virtual CSIPDialogAssocBase* GetSIPDialogAssocBase() const;  
    
private:
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdSendReferL(const TTEFSectionName& aSection);
    void DoCmdReferToL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();

private:
    CSIPReferDialogAssoc* iSIPReferDialogAssoc;
    TBool                 iIsOwner;
	};

#endif /* __T_DATASIPREFERDIALOGASSOC_H__ */

