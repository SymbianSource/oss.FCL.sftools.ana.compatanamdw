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


// This contains CT_DataSIPReferToHeader

#ifndef __T_DATASIPREFERTOHEADER_H__
#define __T_DATASIPREFERTOHEADER_H__

#include "t_csipaddressheaderbase.h"
#include <siprefertoheader.h>

class CT_DataSIPReferToHeader : public CT_DataSIPAddressHeaderBase
	{
public:
    static CT_DataSIPReferToHeader* NewL();
    ~CT_DataSIPReferToHeader();
    
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    void            SetIsOwner(TBool aIsOwner);
    
protected:
    CT_DataSIPReferToHeader();
    void ConstructL();    
    virtual CSIPHeaderBase* GetSIPHeaderBase() const;  
    
private:
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdDecodeL(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();

private:
    CSIPReferToHeader* iSIPReferToHeader;
    TBool iIsOwner;
	};

#endif /* __T_DATASIPREFERTOHEADER_H__ */

