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


// This contains CT_DataSIPAllowHeader

#ifndef __T_DATASIPALLOWHEADER_H__
#define __T_DATASIPALLOWHEADER_H__

//  User includes
#include "t_csiptokenheaderbase.h"
#include <sipallowheader.h>

class CT_DataSIPAllowHeader : public CT_DataSIPTokenHeaderBase
	{
public:
    static CT_DataSIPAllowHeader* NewL();
    ~CT_DataSIPAllowHeader();
    
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();    
    void            SetIsOwner(TBool aOwner);

protected:
    CT_DataSIPAllowHeader();
    void ConstructL();
    virtual CSIPHeaderBase* GetSIPHeaderBase() const;
    virtual CSIPTokenHeaderBase* GetSIPTokenHeaderBase()const;
    
private:
    void DoCmdDecodeL(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
    void DoCmdNewL(const TTEFSectionName& aSection);
    void DoCmdNewLC(const TTEFSectionName& aSection);
    void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();

private:
    CSIPAllowHeader*        iSIPAllowHeader;
    TBool                   iIsOwner;
	};

#endif /* __T_DATASIPALLOWHEADER_H__ */

