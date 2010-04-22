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


#ifndef __T_DATASIPRACKHEADER_H__
#define __T_DATASIPRACKHEADER_H__

#include "t_csipheaderbase.h"
#include <testexecutestepbase.h>
#include <siprackheader.h> 

class CT_DataSIPRAckHeader : public CT_DataSIPHeaderBase 
    {
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	~CT_DataSIPRAckHeader();
	static CT_DataSIPRAckHeader* NewL();
	virtual TAny*	GetObject();
	virtual void    SetObjectL(TAny* aAny);
	virtual void	DisownObjectL();

	CSIPHeaderBase* GetSIPHeaderBase() const;
	void SetIsOwner(TBool aIsOwner);
	
protected:
	CT_DataSIPRAckHeader();
	void ConstructL();
	void DoCmdNewL(const TTEFSectionName& aSection);
	void DoCmdNewLC(const TTEFSectionName& aSection);
	void DoCmdDecodeL(const TTEFSectionName& aSection);
	void DoCmdMethod(const TTEFSectionName& aSection);
	void DoCmdSetMethodL(const TTEFSectionName& aSection);	
	void DoCmdSeq(const TTEFSectionName& aSection);
	void DoCmdSetSeq(const TTEFSectionName& aSection);
    void DoCmdCSeqNum(const TTEFSectionName& aSection);
    void DoCmdSetCSeqNumL(const TTEFSectionName& aSection);	
	void DoCmdInternalizeValueL(const TTEFSectionName& aSection);
	void DoCmdDestructor(const TTEFSectionName& aSection);
	void DestroyData();
	
private:
    CSIPRAckHeader* iSIPRAckHeader;
    TBool iIsOwner;
    };

#endif /*__T_DATASIPRACKHEADER_H__*/

