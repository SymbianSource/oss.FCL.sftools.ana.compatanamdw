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


#ifndef T_CSIPRESPONSEELEMENTS_H_
#define T_CSIPRESPONSEELEMENTS_H_

#include <testexecutestepbase.h>
#include "DataWrapperBase.h"

class CSIPResponseElements;

class CT_DataSIPResponseElements: public CDataWrapperBase
    {
public:
    static CT_DataSIPResponseElements* NewL();
    ~CT_DataSIPResponseElements();
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny* GetObject();
    virtual void SetObjectL(TAny* aAny);
    virtual void DisownObjectL();
    
    void SetIsOwner(TBool aIsOwner);
    
protected:
    CT_DataSIPResponseElements();
    void ConstructL();
    
private:
    // Wrapper functions.
    void DoCmdCSeqHeaderL(const TTEFSectionName& aSection);
    void DoCmdFromHeaderL(const TTEFSectionName& aSection);
    void DoCmdMessageElements(const TTEFSectionName& aSection);
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdReasonPhrase(const TTEFSectionName& aSection);
    void DoCmdSetReasonPhraseL(const TTEFSectionName& aSection);
    void DoCmdSetStatusCodeL(const TTEFSectionName& aSection);
    void DoCmdStatusCode(const TTEFSectionName& aSection);
    void DoCmdToHeader(const TTEFSectionName& aSection);
    void DoCmdDestructor();
    
private:
    void DestroyData();
   
private:
    // Wrapped class.
    CSIPResponseElements* iRespElems;
    TBool iIsOwner;
    };

#endif /* T_CSIPRESPONSEELEMENTS_H_ */
