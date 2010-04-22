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
 * This contains CT_DataSdpCodecStringPool
 */


#ifndef __T_DATASDPCODECSTRINGPOOL_H__
#define __T_DATASDPCODECSTRINGPOOL_H__

#include "DataWrapperBase.h"

#include <sdpcodecstringpool.h>
class CT_DataSdpCodecStringPool : public CDataWrapperBase 
    {
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	~CT_DataSdpCodecStringPool();
	static CT_DataSdpCodecStringPool* NewL();
	virtual TAny*	GetObject();

protected:
    void ConstructL();
	CT_DataSdpCodecStringPool();
	void DoCmdOpenL();
	void DoCmdClose();
    };

#endif /*__T_DATASDPCODECSTRINGPOOL_H__*/

