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


#ifndef T_CSIPREGISTRATIONBINDING_H_
#define T_CSIPREGISTRATIONBINDING_H_

#include <testexecutestepbase.h>
#include "t_csipdialogassocbase.h"

class CSIPRegistrationBinding;

class CT_DataSIPRegistrationBinding: public CDataWrapperBase// TODO should inherit from MSIPDRegistrationContext or its wrapper.
    {
public:
    static CT_DataSIPRegistrationBinding* NewL();
    ~CT_DataSIPRegistrationBinding();
    TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    TAny* GetObject();
    void SetObjectL(TAny* aAny);
    void DisownObjectL();
    void  SetIsOwner(TBool aOwner);
    
protected:
    CT_DataSIPRegistrationBinding();
    void ConstructL();
    
private:
    // Wrapper functions.
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdIsContextActive(const TTEFSectionName& aSection);
    void DoCmdContextId(const TTEFSectionName& aSection);
    void DoCmdRegisterL(const TTEFSectionName& aSection);
    void DoCmdDeregisterL(const TTEFSectionName& aSection);
    void DoCmdUpdateL(const TTEFSectionName& aSection);
    void DoCmdConnectionL(const TTEFSectionName& aSection);
    void DoCmdSetOutboundProxyL(const TTEFSectionName& aSection);
    void DoCmdAor(const TTEFSectionName& aSection);
    void DoCmdContactHeaderL(const TTEFSectionName& aSection);
    void DoCmdOutboundProxy(const TTEFSectionName& aSection);
    void DoCmdSIPRefreshL(const TTEFSectionName& aSection);
    void DoCmdOperatorEqualL(const TTEFSectionName& aSection);
    void DoCmdRegisteredContactL(const TTEFSectionName& aSection);
    void DoCmdDestructor();
    
private:
    void DestroyData();
   
private:
    // Wrapped class.
    CSIPRegistrationBinding* iRegBinding;
    TBool iIsOwner;
    };

#endif /* T_CSIPREGISTRATIONBINDING_H_ */
