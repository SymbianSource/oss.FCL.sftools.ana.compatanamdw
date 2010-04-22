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


#ifndef T_CSIPTOHEADER_H_
#define T_CSIPTOHEADER_H_

#include "DataWrapperBase.h"
#include "t_csipheaderbase.h"
#include <testexecutestepbase.h>
#include <siptoheader.h> 
#include "t_csipfromtoheaderbase.h"

class CSIPServerTransaction;

class CT_DataSIPToHeader : public CT_DataSIPFromToHeaderBase 
    {
public:
    virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    ~CT_DataSIPToHeader();
    static CT_DataSIPToHeader* NewL();
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    virtual CSIPHeaderBase* GetSIPHeaderBase() const;
    virtual void   SetIsOwner(TBool aOwner);
    
protected:
    CT_DataSIPToHeader();
    void ConstructL();
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdDecodeL(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
    void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();
    
private:
    CSIPToHeader* iSIPToHeader;
    TBool         iIsOwner;
    };


#endif /* T_CSIPTOHEADER_H_ */
