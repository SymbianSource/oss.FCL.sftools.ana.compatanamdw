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


// This contains CT_DataSIPRouteHeader

#ifndef __T_DATASIPROUTEHEADER_H__
#define __T_DATASIPROUTEHEADER_H__

#include "t_csiprouteheaderbase.h"
#include <siprouteheader.h>

class CT_DataSIPRouteHeader : public CT_DataSIPRouteHeaderBase
	{
public:
    static CT_DataSIPRouteHeader* NewL();
    ~CT_DataSIPRouteHeader();
    
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    void            SetIsOwner(TBool aIsOwner);
    
protected:
    CT_DataSIPRouteHeader();
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
    CSIPRouteHeader* iSIPRouteHeader;
    TBool iIsOwner;
	};

#endif /* __T_DATASIPROUTEHEADER_H__ */

