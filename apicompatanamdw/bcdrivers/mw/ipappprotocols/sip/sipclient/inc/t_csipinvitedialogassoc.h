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


#ifndef T_CSIPINVITEDIALOGASSOC_H_
#define T_CSIPINVITEDIALOGASSOC_H_

#include <testexecutestepbase.h>
#include "t_csipdialogassocbase.h"

class CSIPInviteDialogAssoc;

class CT_DataSIPInviteDialogAssoc: public CT_DataSIPDialogAssocBase
    {
public:
    static CT_DataSIPInviteDialogAssoc* NewL();
    ~CT_DataSIPInviteDialogAssoc();
    TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    TAny* GetObject();
    void SetObjectL(TAny* aAny);
    void DisownObjectL();
    CSIPDialogAssocBase* GetSIPDialogAssocBase() const;
    void  SetIsOwner(TBool aOwner);
    
protected:
    CT_DataSIPInviteDialogAssoc();
    void ConstructL();
    
private:
    // Wrapper functions.
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdSendAckL(const TTEFSectionName& aSection);
    void DoCmdSendByeL(const TTEFSectionName& aSection);
    void DoCmdSendInviteL(const TTEFSectionName& aSection);
    void DoCmdSendPrackL(const TTEFSectionName& aSection);
    void DoCmdSendUpdateL(const TTEFSectionName& aSection);
    void DoCmdDestructor();
    
private:
    void DestroyData();
   
private:
    // Wrapped class.
    CSIPInviteDialogAssoc* iInviteDlgAssoc;
    TBool iIsOwner;
    };

#endif /* T_CSIPINVITEDIALOGASSOC_H_ */
