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


#ifndef T_CSIPMESSAGEELEMENTS_H_
#define T_CSIPMESSAGEELEMENTS_H_

#include <testexecutestepbase.h>
#include "DataWrapperBase.h"

class CSIPMessageElements;
class CSIPContentTypeHeader;

class CT_DataSIPMessageElements: public CDataWrapperBase
    {
public:
    static CT_DataSIPMessageElements* NewL();
    ~CT_DataSIPMessageElements();
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny* GetObject();
    virtual void SetObjectL(TAny* aAny);
    virtual void DisownObjectL();
    void         SetIsOwner(TBool aOwner);
    
protected:
    CT_DataSIPMessageElements();
    void ConstructL();
    
private:
    // Wrapper functions.
    void DoCmdContent(const TTEFSectionName& aSection);
    void DoCmdContentTypeL(const TTEFSectionName& aSection);
    void DoCmdExtractContent(const TTEFSectionName& aSection);
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdSetContentL(const TTEFSectionName& aSection);
    void DoCmdSetUserHeadersL(const TTEFSectionName& aSection);
    void DoCmdUserHeaders(const TTEFSectionName& aSection);
    void DoCmdDestructor();
    
private:
    void DestroyData();
    // Helper
//    TBool CompareSIPContentTypeHeader(const CSIPContentTypeHeader& aHdr1, const CSIPContentTypeHeader& aHdr2);
    
private:
    // Wrapped class.
    CSIPMessageElements* iMsgElems;
    TBool                iIsOwner;
    };

#endif /* T_CSIPMESSAGEELEMENTS_H_ */
