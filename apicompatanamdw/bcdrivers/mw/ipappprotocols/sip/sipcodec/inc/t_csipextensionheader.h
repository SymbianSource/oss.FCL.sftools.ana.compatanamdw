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


#ifndef T_CSIPEXTENSIONHEADER_H_
#define T_CSIPEXTENSIONHEADER_H_

#include <testexecutestepbase.h>
#include <sipextensionheader.h> 
#include "t_csipheaderbase.h"


class CT_DataSIPExtensionHeader : public CT_DataSIPHeaderBase
{
public:
    static CT_DataSIPExtensionHeader* NewL();
    ~CT_DataSIPExtensionHeader();
    virtual TBool  DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*  GetObject();
    virtual void   SetObjectL(TAny* aAny);
    virtual void   DisownObjectL();
    virtual CSIPHeaderBase* GetSIPHeaderBase() const;
    virtual void   SetIsOwner(TBool aOwner);
    
protected:
    CT_DataSIPExtensionHeader();
    void ConstructL();
    
private:
    void DoCmdDestructor();
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdSetValueL(const TTEFSectionName& aSection);
    void DoCmdValue(const TTEFSectionName& aSection);
    
private:
    void  DestroyData();
    
private:
    CSIPExtensionHeader*                 iSIPExtensionHeader ;
    TBool                            iIsOwner;
};

#endif /* T_CSIPEXTENSIONHEADER_H_ */
