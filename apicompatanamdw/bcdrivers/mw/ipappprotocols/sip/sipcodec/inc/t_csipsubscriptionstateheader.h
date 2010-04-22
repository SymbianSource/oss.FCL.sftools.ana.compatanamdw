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


#ifndef T_CSIPSUBSCRIPTIONHEADER_H_
#define T_CSIPSUBSCRIPTIONHEADER_H_
#include "t_csipparameterheaderbase.h"

#include <sipsubscriptionstateheader.h> 
class CT_DataSIPSubscriptionStateHeader : public CT_DataSIPParameterHeaderBase
    {
public:
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    ~CT_DataSIPSubscriptionStateHeader();
    static CT_DataSIPSubscriptionStateHeader* NewL();
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    virtual CSIPHeaderBase* GetSIPHeaderBase() const;
    virtual void   SetIsOwner(TBool aOwner);
    
protected:
    CT_DataSIPSubscriptionStateHeader();
    void ConstructL();
    void DoCmdDecodeL(const TTEFSectionName& aSection);
    void DoCmdExpiresParameter(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdRetryAfterParameter(const TTEFSectionName& aSection);
    void DoCmdSetExpiresParameterL(const TTEFSectionName& aSection);
    void DoCmdSetRetryAfterParameterL(const TTEFSectionName& aSection);
    void DoCmdSetSubStateValueL(const TTEFSectionName& aSection);
    void DoCmdSubStateValue(const TTEFSectionName& aSection);
    void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();
    
private:
    CSIPSubscriptionStateHeader* iSIPSubscriptionStateHeader;
    TBool         iIsOwner;
    };

#endif /* T_CSIPSUBSCRIPTIONHEADER_H_ */
