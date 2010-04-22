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


#ifndef T_CSIPPASSOCIATEDURIHEADER_H_
#define T_CSIPPASSOCIATEDURIHEADER_H_
#include <testexecutestepbase.h>
#include <sippassociateduriheader.h> 
#include "t_csipaddressheaderbase.h"

class CT_DataSIPPAssociatedURIHeader : public CT_DataSIPAddressHeaderBase
{
public:
    static CT_DataSIPPAssociatedURIHeader* NewL();
    ~CT_DataSIPPAssociatedURIHeader();
    virtual TBool  DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*  GetObject();
    virtual void   SetObjectL(TAny* aAny);
    virtual void   DisownObjectL();
    virtual CSIPHeaderBase* GetSIPHeaderBase() const;
    virtual void   SetIsOwner(TBool aOwner);
    
protected:
    CT_DataSIPPAssociatedURIHeader();
    void ConstructL();
    
private:
    void DoCmdDestructor();
    void DoCmdDecodeL(const TTEFSectionName& aSection);
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
    
private:
    void  DestroyData();
    
private:
    CSIPPAssociatedURIHeader*           iURIHeader ;
    TBool                               iIsOwner;
};

#endif /* T_CSIPPASSOCIATEDURIHEADER_H_ */
