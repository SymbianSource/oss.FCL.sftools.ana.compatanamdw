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


// This contains CT_DataSIPContentTypeHeader

#ifndef __T_DATASIPCONTENTTYPEHEADER_H__
#define __T_DATASIPCONTENTTYPEHEADER_H__

//  User includes
#include "t_csipparameterheaderbase.h"
#include <sipcontenttypeheader.h>

class CT_DataSIPContentTypeHeader : public CT_DataSIPParameterHeaderBase
	{
public:
    static CT_DataSIPContentTypeHeader* NewL();
    ~CT_DataSIPContentTypeHeader();
    
    virtual TBool   DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
    virtual TAny*   GetObject();
    virtual void    SetObjectL(TAny* aAny);
    virtual void    DisownObjectL();
    void            SetIsOwner(TBool aOwner);

protected:
    CT_DataSIPContentTypeHeader();
    void ConstructL();
    virtual CSIPHeaderBase* GetSIPHeaderBase() const;
    
private:
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
	void DoCmdDecodeL(const TTEFSectionName& aSection);
	void DoCmdMediaType(const TTEFSectionName& aSection);
	void DoCmdSetMediaTypeL(const TTEFSectionName& aSection);
	void DoCmdMediaSubtype(const TTEFSectionName& aSection);
    void DoCmdSetMediaSubtypeL(const TTEFSectionName& aSection);
    void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
    void DestroyData();

private:
    CSIPContentTypeHeader* iSIPContentTypeHeader;
    TBool                   iIsOwner;
	};

#endif /* __T_DATASIPCONTENTTYPEHEADER_H__ */

