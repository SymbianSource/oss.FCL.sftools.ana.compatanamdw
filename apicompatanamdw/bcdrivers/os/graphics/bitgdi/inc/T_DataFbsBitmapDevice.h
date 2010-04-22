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

This contains CT_DataFbsBitmapDevice
*/

#if (!defined __T_DATA_FBS_BITMAP_DEVICE_H__)
#define __T_DATA_FBS_BITMAP_DEVICE_H__

//	User includes
#include "DataWrapperBase.h"
#include "T_DataBitmapDevice.h"

class CT_DataFbsBitmapDevice : public CT_DataBitmapDevice
	{
public:
	static CT_DataFbsBitmapDevice*	NewL();
	
	~CT_DataFbsBitmapDevice();

	//	CTPData implementation
	virtual TBool	DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex);

	virtual TAny*	GetObject();
	virtual void	SetObjectL(TAny* aObject);
	virtual void	DisownObjectL();
	void			DestroyData();

protected:
	CT_DataFbsBitmapDevice();
	void	ConstructL();

	//	CT_DataGraphicsDeviceMap implementation
	virtual MGraphicsDeviceMap*	GetGraphicsDeviceMap() const;

	//	CT_DataGraphicsDevice implementation
	virtual CGraphicsDevice*	GetGraphicsDevice() const;

	//	CT_DataBitmapDevice implementation
	virtual CBitmapDevice*		GetBitmapDevice() const;

private:
	void	DoCmdNewL(const TDesC& aSection);
	void	DoCmdDestructor();

protected:
	/** test step reference*/
	CFbsBitmapDevice*	iFbsBitmapDevice;
	};

#endif /* __T_DATA_FBS_BITMAP_DEVICE_H__ */
