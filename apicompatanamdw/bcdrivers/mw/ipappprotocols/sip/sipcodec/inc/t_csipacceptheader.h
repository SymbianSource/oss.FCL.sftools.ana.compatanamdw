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


#ifndef T_CSIPACCEPTHEADER_H_
#define T_CSIPACCEPTHEADER_H_

#include "t_csipparameterheaderbase.h"
#include <sipacceptheader.h>

class CT_DataSIPAcceptHeader : public CT_DataSIPParameterHeaderBase
    {
public:
    ~CT_DataSIPAcceptHeader();
    static CT_DataSIPAcceptHeader* NewL();
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    void            SetIsOwner(TBool aOwner);
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);

    
protected:
    CT_DataSIPAcceptHeader();
    void ConstructL();
    virtual CSIPHeaderBase* GetSIPHeaderBase() const;  
    
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);  
    void DoCmdDecodeL(const TTEFSectionName& aSection);
    void DoCmdIsEmpty(const TTEFSectionName& aSection);
	void DoCmdMediaType(const TTEFSectionName& aSection);
	void DoCmdSetMediaTypeL(const TTEFSectionName& aSection);
	void DoCmdMediaSubtype(const TTEFSectionName& aSection);
    void DoCmdSetMediaSubtypeL(const TTEFSectionName& aSection);    
    void DoCmdQParameter(const TTEFSectionName& aSection);
    void DoCmdSetQParameterL(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
    void DoCmdDestructor(const TTEFSectionName& aSection);  
    void DestroyData();

private:
    CSIPAcceptHeader* iSIPAcceptHeader;
    TBool           iIsOwner;
    
    };

#endif /* T_CSIPACCEPTHEADER_H_ */
