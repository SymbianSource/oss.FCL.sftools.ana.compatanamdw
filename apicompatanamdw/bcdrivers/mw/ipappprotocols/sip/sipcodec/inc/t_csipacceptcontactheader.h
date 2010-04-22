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
 * This contains CT_DataSIPAcceptContactHeader
 */


#ifndef __T_DATASIPACCEPTCONTACTHEADER_H__
#define __T_DATASIPACCEPTCONTACTHEADER_H__

#include "t_csipparameterheaderbase.h"
#include <testexecutestepbase.h>
#include <sipacceptcontactheader.h> 

class CT_DataSIPAcceptContactHeader : public CT_DataSIPParameterHeaderBase 
    {
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	~CT_DataSIPAcceptContactHeader();
	static CT_DataSIPAcceptContactHeader* NewL();
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObjectL();

	CSIPHeaderBase* GetSIPHeaderBase() const;
	void SetIsOwner(TBool aIsOwner);
	
protected:
	CT_DataSIPAcceptContactHeader();
	void ConstructL();
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdDecodeL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
	void DoCmdCompare(const TTEFSectionName& aSection);
	void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
	void DestroyData();
	
private:
    CSIPAcceptContactHeader* iSIPAcceptContactHeader;
    TBool iIsOwner;
    };

#endif /*CT_DataSIPAcceptContactHeader*/

