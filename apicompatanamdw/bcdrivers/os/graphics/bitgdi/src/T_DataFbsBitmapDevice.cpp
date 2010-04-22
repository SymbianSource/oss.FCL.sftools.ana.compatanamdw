/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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

//	User includes
#include "T_DataFbsBitmapDevice.h"
#include "T_GraphicsUtil.h"

/*@{*/
///	Commands
_LIT(KCmdNewL,			"NewL");
_LIT(KCmdDestructor,	"~");

///	Parameters
_LIT(KBitmap,			"bitmap");
_LIT(KLibName,			"libname");
/*@}*/


/**
* Two phase constructor
*/
CT_DataFbsBitmapDevice* CT_DataFbsBitmapDevice::NewL()
	{
	CT_DataFbsBitmapDevice*	ret = new (ELeave) CT_DataFbsBitmapDevice();
	CleanupStack::PushL(ret);
	ret->ConstructL();
	CleanupStack::Pop(ret);
	return ret;
	}

/**
* Protected constructor. First phase construction
*/
CT_DataFbsBitmapDevice::CT_DataFbsBitmapDevice()
:	CT_DataBitmapDevice()
,	iFbsBitmapDevice(NULL)
	{
	}

/**
* Protected second phase construction
*/
void CT_DataFbsBitmapDevice::ConstructL()
	{
	}

/**
* Destructor.
*/
CT_DataFbsBitmapDevice::~CT_DataFbsBitmapDevice()
	{
	DestroyData();
	}

void CT_DataFbsBitmapDevice::DestroyData()
	{
	delete iFbsBitmapDevice;
	iFbsBitmapDevice=NULL;
	}

MGraphicsDeviceMap* CT_DataFbsBitmapDevice::GetGraphicsDeviceMap() const
	{
	return iFbsBitmapDevice;
	}

CGraphicsDevice* CT_DataFbsBitmapDevice::GetGraphicsDevice() const
	{
	return iFbsBitmapDevice;
	}

CBitmapDevice* CT_DataFbsBitmapDevice::GetBitmapDevice() const
	{
	return iFbsBitmapDevice;
	}

/**
* Return a pointer to the object that the data wraps
*
* @return pointer to the object that the data wraps
*/
TAny* CT_DataFbsBitmapDevice::GetObject()
	{
	return iFbsBitmapDevice;
	}

void CT_DataFbsBitmapDevice::SetObjectL(TAny* aObject)
	{
	DestroyData();
	iFbsBitmapDevice	= static_cast<CFbsBitmapDevice*> (aObject);
	}

void CT_DataFbsBitmapDevice::DisownObjectL() 
	{
	iFbsBitmapDevice = NULL;
	}

/**
* Process a command read from the ini file
*
* @param aDataWrapper	test step requiring command to be processed
* @param aCommand	the command to process
* @param aSection		the entry in the ini file requiring the command to be processed
*
* @return ETrue if the command is processed
*/
TBool CT_DataFbsBitmapDevice::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	/* Another work package will complete the implement of this */
	TBool	retVal = ETrue;

	if ( aCommand == KCmdNewL )
		{
		DoCmdNewL(aSection);
		}
	else if (aCommand == KCmdDestructor)
		{
		DoCmdDestructor();
		}
	else
		{
		retVal=CT_DataBitmapDevice::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
		}

	return retVal;
	}

void CT_DataFbsBitmapDevice::DoCmdNewL(const TDesC& aSection)
	{
	DestroyData();

	CFbsBitmap*	bitmap;

	if ( !CT_GraphicsUtil::GetFbsBitmapL(*this, aSection, KBitmap, bitmap) )
		{
		ERR_PRINTF1(_L("No bitmap specified"));
		SetBlockResult(EFail);
		}
	else
		{
		TInt	err=KErrNone;
		TPtrC	libName;
		if ( GetStringFromConfig(aSection, KLibName(), libName) )
			{
			TRAP(err, iFbsBitmapDevice=CFbsBitmapDevice::NewL(bitmap, libName));
			}
		else
			{
			TRAP(err, iFbsBitmapDevice=CFbsBitmapDevice::NewL(bitmap));
			}

		if ( err!=KErrNone )
			{
			ERR_PRINTF2(_L("NewL failed with error %d"), err);
			SetError(err);
			}
		}
	}

void CT_DataFbsBitmapDevice::DoCmdDestructor()
	{
	DestroyData();
	}
