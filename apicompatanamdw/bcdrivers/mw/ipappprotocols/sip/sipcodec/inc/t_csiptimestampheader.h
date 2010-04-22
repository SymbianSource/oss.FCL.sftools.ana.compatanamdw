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
 * This contains CT_DataSIPAddress
 */


#ifndef __T_DATASIPTIMESTAMPHEADER_H__
#define __T_DATASIPTIMESTAMPHEADER_H__

#include "t_csipheaderbase.h"
#include <testexecutestepbase.h>
#include <siptimestampheader.h> 

class CT_DataSIPTimestampHeader : public CT_DataSIPHeaderBase 
    {
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	~CT_DataSIPTimestampHeader();
	static CT_DataSIPTimestampHeader* NewL();
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObjectL();

	CSIPHeaderBase* GetSIPHeaderBase() const;
	void SetIsOwner(TBool aIsOwner);
	
protected:
	CT_DataSIPTimestampHeader();
	void ConstructL();
	void DoCmdConstructorL(const TTEFSectionName& aSection);
	void DoCmdDecodeL(const TTEFSectionName& aSection);
	void DoCmdTimestamp(const TTEFSectionName& aSection);
	void DoCmdSetTimestamp(const TTEFSectionName& aSection);	
	void DoCmdHasDelay(const TTEFSectionName& aSection);
	void DoCmdSetDelay(const TTEFSectionName& aSection);
    void DoCmdDelay(const TTEFSectionName& aSection);	
	void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
	void DestroyData();
	
private:
    CSIPTimestampHeader* iSIPTimestampHeader;
    TBool iIsOwner;
    };

#endif /*__T_DATASIPTIMESTAMPHEADER_H__*/

