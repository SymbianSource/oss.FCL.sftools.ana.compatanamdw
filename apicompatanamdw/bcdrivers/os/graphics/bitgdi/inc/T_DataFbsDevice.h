/*
* Copyright (c) 2006-2008 Nokia Corporation and/or its subsidiary(-ies).
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

/**
@test
@internalComponent

This contains CT_DataFbsDevice
*/

#if (!defined __T_DATA_FBS_DEVICE_H__)
#define __T_DATA_FBS_DEVICE_H__

//	User includes
#include "DataWrapperBase.h"
#include "T_DataBitmapDevice.h"

class CT_DataFbsDevice : public CT_DataBitmapDevice
	{
public:
	virtual TBool DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);
	CT_DataFbsDevice();

protected:

	virtual CFbsDevice*	GetFbsDevice() const = 0;
	};

#endif /* __T_DATA_FBS_DEVICE_H__ */
