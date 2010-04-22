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

This contains CT_DataFbsScreenDevice
*/

//	User includes
#include "T_DataFbsScreenDevice.h"
#include "T_GraphicsUtil.h"

/*@{*/
//Commands
_LIT(KCmdNewL,				"NewL");
_LIT(KCmdDestructor,		"~");

//Parameters
_LIT(KLibName,				"libname");
_LIT(KScreenNumber,			"screen_number");
_LIT(KRgbColorRed,			"rgb_red");
_LIT(KRgbColorGreen,		"rgb_green");
_LIT(KRgbColorBlue,			"rgb_blue");
_LIT(KDisplayMode,			"displaymode");
/*@}*/


/**
* Two phase constructor
*/
CT_DataFbsScreenDevice* CT_DataFbsScreenDevice::NewL()
	{
	CT_DataFbsScreenDevice*	ret = new (ELeave) CT_DataFbsScreenDevice();
	CleanupStack::PushL(ret);
	ret->ConstructL();
	CleanupStack::Pop(ret);
	return ret;
	}

/**
* Protected constructor. First phase construction
*/
CT_DataFbsScreenDevice::CT_DataFbsScreenDevice()
:	CT_DataFbsDevice()
,	iFbsScreenDevice(NULL)
	{
	}

/**
* Protected second phase construction
*/
void CT_DataFbsScreenDevice::ConstructL()
	{
	}

/**
* Destructor. 
*/
CT_DataFbsScreenDevice::~CT_DataFbsScreenDevice()
	{
	DestroyData();
	}

void CT_DataFbsScreenDevice::DestroyData()
	{
	delete iFbsScreenDevice;
	iFbsScreenDevice=NULL;
	}

MGraphicsDeviceMap* CT_DataFbsScreenDevice::GetGraphicsDeviceMap() const
	{
	return iFbsScreenDevice;
	}

CGraphicsDevice* CT_DataFbsScreenDevice::GetGraphicsDevice() const
	{
	return iFbsScreenDevice;
	}

CBitmapDevice* CT_DataFbsScreenDevice::GetBitmapDevice() const
	{
	return iFbsScreenDevice;
	}

CFbsDevice* CT_DataFbsScreenDevice::GetFbsDevice() const
	{
	return iFbsScreenDevice;
	}

/**
* Return a pointer to the object that the data wraps
*
* @return pointer to the object that the data wraps
*/
TAny* CT_DataFbsScreenDevice::GetObject()
	{
	return iFbsScreenDevice;
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
TBool CT_DataFbsScreenDevice::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	/* Another work package will complete the implement of this */
	TBool	retVal = ETrue;

	if ( aCommand == KCmdNewL )
		{
		DoCmdNew(aSection);
		}
	else if (aCommand == KCmdDestructor)
		{
		DoCmdDestructor();
		}
	else
		{
		retVal=CT_DataFbsDevice::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
		}

	return retVal;
	}

void CT_DataFbsScreenDevice::DoCmdNew(const TDesC& aSection)
	{
	DestroyData();

	// get display mode from parameters
	TDisplayMode	displayMode=ENone;
	TBool			hasDisplayMode=CT_GraphicsUtil::ReadDisplayMode(*this, aSection, KDisplayMode(), displayMode);

	// get lib name from parameters

	TPtrC	libName;
	TBool	hasLibName=GetStringFromConfig(aSection, KLibName(), libName);

	TBool	useRgb = EFalse;

	TInt	red = 0;
	if(GetIntFromConfig(aSection, KRgbColorRed(), red))
		{
		useRgb=ETrue;
		}

	TInt	green = 0;
	if(GetIntFromConfig(aSection, KRgbColorGreen(), green))
		{
		useRgb=ETrue;
		}

	TInt	blue = 0;
	if(GetIntFromConfig(aSection, KRgbColorBlue(), blue))
		{
		useRgb = ETrue;
		}

	// get screen number from parameters
	TInt	screenNumber = 0;
	GetIntFromConfig(aSection, KScreenNumber(), screenNumber);

	TInt	err=KErrNone;
	if ( !hasDisplayMode )
		{
		//	Find the best display mode
		for ( TDisplayMode testMode=TDisplayMode(ENone+1); testMode<EColorLast; testMode=TDisplayMode(testMode+1) )
			{
			if ( hasLibName ) // if lib name is given
				{		
				if ( useRgb )
					{
					TRAP(err, iFbsScreenDevice=CFbsScreenDevice::NewL(libName, testMode, TRgb(red, green, blue)));
					}
				else
					{
					TRAP(err, iFbsScreenDevice=CFbsScreenDevice::NewL(libName, testMode));
					}
				}
			else // if lib name is not given
				{		
				TRAP(err, iFbsScreenDevice=CFbsScreenDevice::NewL(screenNumber, testMode));
				}

			//	Test if Mode OK
			if ( err==KErrNone )
				{
				displayMode=testMode;
				hasDisplayMode=ETrue;
				delete iFbsScreenDevice;
				iFbsScreenDevice=NULL;
				INFO_PRINTF2(_L("Mode %d supported"), testMode);
				}
			}
		}

	if ( hasDisplayMode )
		{
		if ( hasLibName ) // if lib name is given
			{		
			if ( useRgb )
				{
				TRAP(err, iFbsScreenDevice=CFbsScreenDevice::NewL(libName, displayMode, TRgb(red, green, blue)));
				}
			else
				{
				TRAP(err, iFbsScreenDevice=CFbsScreenDevice::NewL(libName, displayMode));
				}
			}
		else // if lib name is not given
			{		
			TRAP(err, iFbsScreenDevice=CFbsScreenDevice::NewL(screenNumber, displayMode));
			}

		if ( err!=KErrNone )
			{
			ERR_PRINTF2(_L("NewL failed with error %d"), err);
			SetError(err);
			}
		}
	else
		{
		ERR_PRINTF1(_L("No Display Mode"));
		SetBlockResult(EFail);
		}
	}

void CT_DataFbsScreenDevice::DoCmdDestructor()
	{
	DestroyData();
	}
