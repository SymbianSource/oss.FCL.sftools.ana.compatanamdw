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
 * This contains CT_DataSupportedHeader
 */


#ifndef __T_DATASIPSUPPORTEDHEADER_H__
#define __T_DATASIPSUPPORTEDHEADER_H__

#include "t_csiptokenheaderbase.h"
#include <testexecutestepbase.h>
#include <sipsupportedheader.h> 

class CT_DataSupportedHeader : public CT_DataSIPTokenHeaderBase 
    {
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	~CT_DataSupportedHeader();
	static CT_DataSupportedHeader* NewL();
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObjectL();

	CSIPHeaderBase* GetSIPHeaderBase() const;
	CSIPTokenHeaderBase* GetSIPTokenHeaderBase()const;
	void SetIsOwner(TBool aIsOwner);
	
protected:
    CT_DataSupportedHeader();
	void ConstructL();
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdDecodeL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
	void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
	void DestroyData();
	
private:
    CSIPSupportedHeader* iSIPSupportedHeader;
    TBool iIsOwner;
    };

#endif /*__T_DATASIPSUPPORTHEADER_H__*/

