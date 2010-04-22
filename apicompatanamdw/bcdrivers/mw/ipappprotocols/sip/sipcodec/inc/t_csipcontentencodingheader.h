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
 * This contains CT_DataContentEncodingHeader
 */


#ifndef __T_DATASIPCONTENTENCODINGHEADER_H__
#define __T_DATASIPCONTENTENCODINGHEADER_H__

#include "t_csiptokenheaderbase.h"
#include <testexecutestepbase.h>
#include <sipcontentencodingheader.h> 

class CT_DataContentEncodingHeader : public CT_DataSIPTokenHeaderBase 
    {
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	~CT_DataContentEncodingHeader();
	static CT_DataContentEncodingHeader* NewL();
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObjectL();

	CSIPHeaderBase* GetSIPHeaderBase() const;
	CSIPTokenHeaderBase* GetSIPTokenHeaderBase()const;
	void SetIsOwner(TBool aIsOwner);
	
protected:
    CT_DataContentEncodingHeader();
	void ConstructL();
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdDecodeL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
	void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
	void DestroyData();
	
private:
    CSIPContentEncodingHeader* iSIPContentEncodingHeader;
    TBool iIsOwner;
    };

#endif /*__T_DATASIPCONTENTENCODINGHEADER_H__*/

