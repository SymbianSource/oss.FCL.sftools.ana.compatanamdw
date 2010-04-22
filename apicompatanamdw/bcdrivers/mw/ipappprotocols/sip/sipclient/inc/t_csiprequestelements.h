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


#ifndef T_CSIPREQUESTELEMENTS_H_
#define T_CSIPREQUESTELEMENTS_H_

#include <testexecutestepbase.h>
#include <sipstrings.h>
#include "DataWrapperBase.h"

class CSIPRequestElements;

class CT_DataSIPRequestElements: public CDataWrapperBase
    {
public:
    static CT_DataSIPRequestElements* NewL();
    ~CT_DataSIPRequestElements();
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny* GetObject();
    virtual void SetObjectL(TAny* aAny);
    virtual void DisownObjectL();
    
    void SetIsOwner(TBool aIsOwner);
    
protected:
    CT_DataSIPRequestElements();
    void ConstructL();
    
private:
    // Wrapper functions.
    void DoCmdCSeqHeaderL(const TTEFSectionName& aSection);
    void DoCmdFromHeaderL(const TTEFSectionName& aSection);
    void DoCmdMessageElements(const TTEFSectionName& aSection);
    void DoCmdMethod(const TTEFSectionName& aSection);
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdRemoteUri(const TTEFSectionName& aSection);
    void DoCmdSetFromHeaderL(const TTEFSectionName& aSection);
    void DoCmdSetMethodL(const TTEFSectionName& aSection);
    void DoCmdSetRemoteUriL(const TTEFSectionName& aSection);
    void DoCmdSetToHeaderL(const TTEFSectionName& aSection);
    void DoCmdToHeaderL(const TTEFSectionName& aSection);
    void DoCmdDestructor();
    
private:
    void DestroyData();
   
private:
    // Wrapped class.
    CSIPRequestElements* iReqElems;
    TBool iIsOwner;
    RStringPool iPool;
    };

#endif /* T_CSIPREQUESTELEMENTS_H_ */
