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
 * This contains CT_DataSIPAcceptLanguageHeader
 */


#ifndef __T_DATASIPACCEPTLANGUAGEHEADER_H__
#define __T_DATASIPACCEPTLANGUAGEHEADER_H__

#include "t_csipparameterheaderbase.h"
#include <testexecutestepbase.h>
#include <sipacceptlanguageheader.h> 

class CT_DataSIPAcceptLanguageHeader : public CT_DataSIPParameterHeaderBase 
    {
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	~CT_DataSIPAcceptLanguageHeader();
	static CT_DataSIPAcceptLanguageHeader* NewL();
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObjectL();

	CSIPHeaderBase* GetSIPHeaderBase() const;
	void SetIsOwner(TBool aIsOwner);
	
protected:
    CT_DataSIPAcceptLanguageHeader();
	void ConstructL();
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdDecodeL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
	void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
	void DoCmdLanguageRange(const TTEFSectionName& aSection);
	void DoCmdSetLanguageRangeL(const TTEFSectionName& aSection);
	void DoCmdQParameter(const TTEFSectionName& aSection);
	void DoCmdSetQParameterL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
	void DestroyData();
	
private:
    CSIPAcceptLanguageHeader* iSIPAcceptLanguageHeader;
    TBool iIsOwner;
    };

#endif /*__T_DATASIPACCEPTLANGUAGEHEADER_H__*/

