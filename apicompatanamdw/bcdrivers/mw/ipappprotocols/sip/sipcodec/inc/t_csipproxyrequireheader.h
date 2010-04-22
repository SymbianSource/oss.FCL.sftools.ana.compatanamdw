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


// This contains CT_DataSIPProxyRequireHeader

#ifndef __T_DATASIPPROXYREQUIREHEADER_H__
#define __T_DATASIPPROXYREQUIREHEADER_H__

#include "t_csiptokenheaderbase.h"
#include <sipproxyrequireheader.h>

class CT_DataSIPProxyRequireHeader : public CT_DataSIPTokenHeaderBase
	{
public:
    static CT_DataSIPProxyRequireHeader* NewL();
    ~CT_DataSIPProxyRequireHeader();
    
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    void            SetIsOwner(TBool aIsOwner);
    
protected:
    CT_DataSIPProxyRequireHeader();
    void ConstructL();    
    virtual CSIPHeaderBase* GetSIPHeaderBase()const;
    virtual CSIPTokenHeaderBase* GetSIPTokenHeaderBase() const;  
    
private:
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdDecodeL(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();

private:
    CSIPProxyRequireHeader* iSIPProxyRequireHeader;
    TBool iIsOwner;
	};

#endif /* __T_DATASIPPROXYREQUIREHEADER_H__ */

