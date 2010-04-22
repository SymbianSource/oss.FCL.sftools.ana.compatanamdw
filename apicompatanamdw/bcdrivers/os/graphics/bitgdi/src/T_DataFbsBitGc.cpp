/*
* Copyright (c) 2007-2008 Nokia Corporation and/or its subsidiary(-ies).
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

This contains CT_DataFbsBitGc
*/

//	User includes
#include "T_DataFbsBitGc.h"
#include "T_GraphicsUtil.h"

/*@{*/
///	Commands
_LIT(KCmdNewL,						"NewL");
_LIT(KCmdDestructor,				"~");
_LIT(KCmdActivate,					"Activate");
_LIT(KCmdActivateNoJustAutoUpdate,	"ActivateNoJustAutoUpdate");
_LIT(KCmdAlphaBlendBitmaps,			"AlphaBlendBitmaps");

///	Fields
_LIT(KFldAlphaBmp,					"alphabmp");
_LIT(KFldAlphaPt,					"alphapt");
_LIT(KFldDestPt,					"destpt");
_LIT(KFldDevice,					"device");
_LIT(KFldSrcBmp1,					"srcbmp1");
_LIT(KFldSrcBmp2,					"srcbmp2");
_LIT(KFldSrcPt,						"srcpt");
_LIT(KFldSrcRect,					"srcrect");

///	Logging
_LIT(KLogError,						"Error=%d");
_LIT(KLogMissingParameter,			"Missing parameter '%S'");
/*@}*/


/**
* Two phase constructor
*/
CT_DataFbsBitGc* CT_DataFbsBitGc::NewL()
	{
	CT_DataFbsBitGc*	ret = new (ELeave) CT_DataFbsBitGc();
	CleanupStack::PushL(ret);
	ret->ConstructL();
	CleanupStack::Pop(ret);
	return ret;
	}

/**
* Protected constructor. First phase construction
*/
CT_DataFbsBitGc::CT_DataFbsBitGc()
:	CT_DataBitmapContext()
,	iFbsBitGc(NULL)
	{
	}

/**
* Protected second phase construction
*/
void CT_DataFbsBitGc::ConstructL()
	{
	}

/**
* Destructor.
*/
CT_DataFbsBitGc::~CT_DataFbsBitGc()
	{
	DestroyData();
	}

void CT_DataFbsBitGc::DestroyData()
	{
	delete iFbsBitGc;
	iFbsBitGc=NULL;
	}

/**
* Return a pointer to the object that the data wraps
*
* @return pointer to the object that the data wraps
*/
TAny* CT_DataFbsBitGc::GetObject()
	{
	return iFbsBitGc;
	}

void CT_DataFbsBitGc::SetObjectL(TAny* aObject)
	{
	DestroyData();
	iFbsBitGc	= static_cast<CFbsBitGc*> (aObject);
	}

void CT_DataFbsBitGc::DisownObjectL() 
	{
	iFbsBitGc = NULL;
	}


//	CT_DataGraphicsContext implementation
CGraphicsContext* CT_DataFbsBitGc::GetGraphicsContext() const
	{
	return iFbsBitGc;
	}

//	CT_DataBitmapContext implementation
CBitmapContext* CT_DataFbsBitGc::GetBitmapContext() const
	{
	return iFbsBitGc;
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
TBool CT_DataFbsBitGc::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	/* Another work package will complete the implement of this */
	TBool	retVal = ETrue;

	if ( aCommand == KCmdNewL )
		{
		DoCmdNewL();
		}
	else if (aCommand == KCmdDestructor)
		{
		DoCmdDestructor();
		}
	else if (aCommand == KCmdActivate)
		{
		DoCmdActivateL(aSection);
		}
	else if (aCommand == KCmdActivateNoJustAutoUpdate)
		{
		DoCmdActivateNoJustAutoUpdateL(aSection);
		}
	else if (aCommand == KCmdAlphaBlendBitmaps)
		{
		if ( !DoCmdAlphaBlendBitmapsL(aSection) )
			{
			retVal=CT_DataBitmapContext::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
			}
		}
	else
		{
		retVal=CT_DataBitmapContext::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
		}

	return retVal;
	}

void CT_DataFbsBitGc::DoCmdNewL()
	{
	DestroyData();

	TRAPD(err, iFbsBitGc=CFbsBitGc::NewL());
	if ( err!=KErrNone )
		{
		ERR_PRINTF2(_L("NewL failed with error %d"), err);
		SetError(err);
		}
	}

void CT_DataFbsBitGc::DoCmdDestructor()
	{
	DestroyData();
	}

void CT_DataFbsBitGc::DoCmdActivateL(const TDesC& aSection)
	{
	CFbsDevice*	device=NULL;
	if ( !CT_GraphicsUtil::GetFbsDeviceL(*this, aSection, KFldDevice, device) )
		{
		ERR_PRINTF2(KLogMissingParameter, &KFldDevice());
		SetBlockResult(EFail);
		}
	else
		{
		// Execute command and log parameters
		INFO_PRINTF1(_L("execute Activate(CFbsDevice*)"));
		iFbsBitGc->Activate(device);
		}
	}

void CT_DataFbsBitGc::DoCmdActivateNoJustAutoUpdateL(const TDesC& aSection)
	{
	CFbsDevice*	device=NULL;
	if ( !CT_GraphicsUtil::GetFbsDeviceL(*this, aSection, KFldDevice, device) )
		{
		ERR_PRINTF2(KLogMissingParameter, &KFldDevice());
		SetBlockResult(EFail);
		}
	else
		{
		// Execute command and log parameters
		INFO_PRINTF1(_L("execute ActivateNoJustAutoUpdate(CFbsDevice*)"));
		iFbsBitGc->ActivateNoJustAutoUpdate(device);
		}
	}

TBool CT_DataFbsBitGc::DoCmdAlphaBlendBitmapsL(const TDesC& aSection)
	{
	CFbsBitmap*	fbsBitmap1=NULL;
	TBool		ret=CT_GraphicsUtil::GetFbsBitmapL(*this, aSection, KFldSrcBmp1, fbsBitmap1);
	if ( CT_GraphicsUtil::GetFbsBitmapL(*this, aSection, KFldSrcBmp1, fbsBitmap1) )
		{
		TBool		dataOk=ETrue;

		CFbsBitmap*	fbsBitmap2=NULL;
		if ( !CT_GraphicsUtil::GetFbsBitmapL(*this, aSection, KFldSrcBmp2, fbsBitmap2) )
			{
			dataOk=EFalse;
			ERR_PRINTF2(KLogMissingParameter, &KFldSrcBmp2());
			SetBlockResult(EFail);
			}

		CFbsBitmap*	alphaBitmap=NULL;
		if ( !CT_GraphicsUtil::GetFbsBitmapL(*this, aSection, KFldAlphaBmp, alphaBitmap) )
			{
			dataOk=EFalse;
			ERR_PRINTF2(KLogMissingParameter, &KFldAlphaBmp());
			SetBlockResult(EFail);
			}

		TPoint	destinationPoint;
		if ( !GetPointFromConfig(aSection, KFldDestPt, destinationPoint) )
			{
			dataOk=EFalse;
			ERR_PRINTF2(KLogMissingParameter, &KFldDestPt());
			SetBlockResult(EFail);
			}

		TRect	sourceRect;
		if ( !GetRectFromConfig(aSection, KFldSrcRect, sourceRect) )
			{
			dataOk=EFalse;
			ERR_PRINTF2(KLogMissingParameter, &KFldSrcRect());
			SetBlockResult(EFail);
			}

		TPoint	sourcePoint;
		if ( !GetPointFromConfig(aSection, KFldSrcPt, sourcePoint) )
			{
			dataOk=EFalse;
			ERR_PRINTF2(KLogMissingParameter, &KFldSrcPt());
			SetBlockResult(EFail);
			}

		TPoint	alphaPoint;
		if ( !GetPointFromConfig(aSection, KFldAlphaPt, alphaPoint) )
			{
			dataOk=EFalse;
			ERR_PRINTF2(KLogMissingParameter, &KFldAlphaPt());
			SetBlockResult(EFail);
			}

		if ( dataOk )
			{
			INFO_PRINTF1(_L("execute AlphaBlendBitmaps(TPoint, CFbsBitmap*, TRect, CFbsBitmap*, TPoint)"));
			TInt	err=iFbsBitGc->AlphaBlendBitmaps(destinationPoint, fbsBitmap1, fbsBitmap2, sourceRect, sourcePoint, alphaBitmap, alphaPoint);
			if ( err!=KErrNone )
				{
				ERR_PRINTF2(KLogError, err);
				SetError(err);
				}
			}
		}

	return ret;
	}
