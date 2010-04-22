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

This contains CT_DataGraphicsDevice
*/

#include "T_DataBitmapDevice.h"
#include "T_GraphicsUtil.h"

/*@{*/
///	Commands
_LIT(KCmdAddFile,									"AddFile");
_LIT(KCmdCreateBitmapContext,						"CreateBitmapContext");
_LIT(KCmdFontHeightInPixels,						"FontHeightInPixels");
_LIT(KCmdGetNearestFontInPixels,					"GetNearestFontInPixels");
_LIT(KCmdGetNearestFontToDesignHeightInPixels,		"GetNearestFontToDesignHeightInPixels");
_LIT(KCmdGetNearestFontToMaxHeightInPixels,			"GetNearestFontToMaxHeightInPixels");
_LIT(KCmdGetPixel,									"GetPixel");
_LIT(KCmdGetScanLine,								"GetScanLine");
_LIT(KCmdRemoveFile,								"RemoveFile");

///	Fields
_LIT(KFldBitmapContext,								"bitmap_context");
_LIT(KFldBuffLength,								"buff_length");
_LIT(KFldCheckScanLine,								"checkScanLine");
_LIT(KFldDisplayMode,								"displaymode");
_LIT(KFldExpected,									"expected");
_LIT(KFldFile,										"file");
_LIT(KFldFont,										"font");
_LIT(KFldHeightIndex,								"height_index");
_LIT(KFldId,										"id");
_LIT(KFldLength,									"length");
_LIT(KFldMaxHeight,									"maxheight");
_LIT(KFldPoint,										"point");
_LIT(KFldSize,										"size");
_LIT(KFldTypefaceIndex,								"typeface_index");


///	Logging
_LIT(KLogColor,										"Color Red=%d Green=%d Blue=%d Alpha=%d");
_LIT(KLogError,										"Error=%d");
_LIT(KLogHeight,									"Height=%d");
_LIT(KLogMissingFilename,							"File '%S' not found in array");
_LIT(KLogMissingParameter,							"Missing parameter '%S'");
_LIT(KLogMissingWrapper,							"Missing wrapper for '%S'");
_LIT(KLogNotExpectedValue,							"Not expected value");
_LIT(KLogDoNotCheckScanLine,						"Will not check scanline.");
_LIT(KLogDoCheckScanLine,							"Will check scanline is correct.");
/*@}*/


/**
* Constructor. First phase construction
*/
CT_DataBitmapDevice::CT_DataBitmapDevice()
:	CT_DataGraphicsDevice()
	{
	}

CT_DataBitmapDevice::~CT_DataBitmapDevice()
	{
	iFile.Reset();
	iFile.Close();
	iId.Reset();
	iId.Close();
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
TBool CT_DataBitmapDevice::DoCommandL(const TTEFFunction& aCommand, const TTEFSectionName& aSection, const TInt aAsyncErrorIndex)
	{
	TBool	ret=ETrue;
	if ( aCommand==KCmdAddFile )
		{
		DoCmdAddFileL(aSection);
		}
	else if ( aCommand==KCmdCreateBitmapContext )
		{
		DoCmdCreateBitmapContextL(aSection);
		}
	else if ( aCommand==KCmdFontHeightInPixels )
		{
		DoCmdFontHeightInPixels(aSection);
		}
	else if ( aCommand==KCmdGetNearestFontInPixels )
		{
		DoCmdGetNearestFontInPixelsL(aSection);
		}
	else if ( aCommand==KCmdGetNearestFontToDesignHeightInPixels )
		{
		DoCmdGetNearestFontToDesignHeightInPixelsL(aSection);
		}
	else if ( aCommand==KCmdGetNearestFontToMaxHeightInPixels )
		{
		DoCmdGetNearestFontToMaxHeightInPixelsL(aSection);
		}
	else if ( aCommand==KCmdGetPixel )
		{
		DoCmdGetPixel(aSection);
		}
	else if ( aCommand==KCmdGetScanLine )
		{
		DoCmdGetScanLineL(aSection);
		}
	else if ( aCommand==KCmdRemoveFile )
		{
		DoCmdRemoveFile(aSection);
		}
	else
		{
		ret=CT_DataGraphicsDevice::DoCommandL(aCommand, aSection, aAsyncErrorIndex);
		}

	/* Another work package will implement this */
	return ret;
	}

void CT_DataBitmapDevice::DoCmdAddFileL(const TDesC& aSection)
	{
	// get typeface index from parameters
	TPtrC	file;
	if ( !GetStringFromConfig(aSection, KFldFile(), file) )
		{
		ERR_PRINTF2(KLogMissingParameter, &KFldFile());
		SetBlockResult(EFail);
		}
	else
		{
		TInt	id;
		INFO_PRINTF1(_L("execute AddFile(const TDesC&, TInt&)"));
		TInt	err=GetBitmapDevice()->AddFile(file, id);
		if ( err!=KErrNone )
			{
			ERR_PRINTF2(KLogError, err);
			SetError(err);
			}
		else
			{
			// Append filename and id
			iFile.AppendL(file);
			iId.AppendL(id);
			}
		}
	}

void CT_DataBitmapDevice::DoCmdCreateBitmapContextL(const TDesC& aSection)
	{
	TPtrC	wrapperName;
	if ( !GetStringFromConfig(aSection, KFldBitmapContext, wrapperName) )
		{
		ERR_PRINTF2(KLogMissingParameter, &KFldBitmapContext());
		SetBlockResult(EFail);
		}
	else
		{
		CDataWrapper*	wrapper=GetDataWrapperL(wrapperName);
		if ( wrapper==NULL )
			{
			ERR_PRINTF2(KLogMissingWrapper, &wrapperName);
			SetBlockResult(EFail);
			}
		else
			{
			CBitmapContext*	bitmapContext=NULL;
			INFO_PRINTF1(_L("execute CreateBitmapContext(CBitmapContext*&)"));
			TInt	err=GetBitmapDevice()->CreateBitmapContext(bitmapContext);
			if ( err!=KErrNone )
				{
				ERR_PRINTF2(KLogError, err);
				SetError(err);
				}
			else
				{
				wrapper->SetObjectL(bitmapContext);
				}
			}
		}
	}

void CT_DataBitmapDevice::DoCmdFontHeightInPixels(const TDesC& aSection)
	{
	TBool	dataOk=ETrue;

	// get typeface index from parameters
	TInt	typefaceIndex;
	if ( !GetIntFromConfig(aSection, KFldTypefaceIndex(), typefaceIndex) )
		{
		dataOk=EFalse;
		ERR_PRINTF2(KLogMissingParameter, &KFldTypefaceIndex());
		SetBlockResult(EFail);
		}

	// get height index from parameters
	TInt	heightIndex;
	if ( !GetIntFromConfig(aSection, KFldHeightIndex(), heightIndex) )
		{
		dataOk=EFalse;
		ERR_PRINTF2(KLogMissingParameter, &KFldHeightIndex());
		SetBlockResult(EFail);
		}

	if ( dataOk )
		{
		INFO_PRINTF1(_L("execute FontHeightInPixels(TInt, TInt)"));
		TInt	height=GetBitmapDevice()->FontHeightInPixels(typefaceIndex, heightIndex);
		INFO_PRINTF2(KLogHeight, height);
	
		TInt	expected;
		if ( GetIntFromConfig(aSection, KFldExpected, expected) )
			{
			if ( expected!=height )
				{
				ERR_PRINTF1(KLogNotExpectedValue);
				SetBlockResult(EFail);
				}
			}
		}
	}

void CT_DataBitmapDevice::DoCmdGetNearestFontInPixelsL(const TDesC& aSection)
	{
	TBool	dataOk=ETrue;

	TFontSpec	fontSpec;
	if ( !GetFontSpecFromConfig(aSection, KFldFont, fontSpec) )
		{
		dataOk=EFalse;
		ERR_PRINTF2(KLogMissingParameter, &KFldFont());
		SetBlockResult(EFail);
		}

	TPtrC	wrapperName;
	if ( !GetStringFromConfig(aSection, KFldFont, wrapperName) )
		{
		dataOk=EFalse;
		ERR_PRINTF2(KLogMissingParameter, &KFldFont());
		SetBlockResult(EFail);
		}

	if ( dataOk )
		{
		CDataWrapper*	wrapper=GetDataWrapperL(wrapperName);
		if ( wrapper==NULL )
			{
			ERR_PRINTF2(KLogMissingWrapper, &wrapperName);
			SetBlockResult(EFail);
			}
		else
			{
			CFont*	font=NULL;
			INFO_PRINTF1(_L("execute GetNearestFontInPixels(CFont*&, TFontSpec)"));
			TInt	err=GetBitmapDevice()->GetNearestFontInPixels(font, fontSpec);
			if ( err!=KErrNone )
				{
				ERR_PRINTF2(KLogError, err);
				SetError(err);
				}
			else
				{
				wrapper->SetObjectL(font);
				}
			}
		}
	}

void CT_DataBitmapDevice::DoCmdGetNearestFontToDesignHeightInPixelsL(const TDesC& aSection)
	{
	TBool	dataOk=ETrue;

	TFontSpec	fontSpec;
	if ( !GetFontSpecFromConfig(aSection, KFldFont, fontSpec) )
		{
		dataOk=EFalse;
		ERR_PRINTF2(KLogMissingParameter, &KFldFont());
		SetBlockResult(EFail);
		}

	TPtrC		wrapperName;
	// get BitmapUtilData object from parameters
	if ( !GetStringFromConfig(aSection, KFldFont, wrapperName) )
		{
		dataOk=EFalse;
		ERR_PRINTF2(KLogMissingParameter, &KFldFont());
		SetBlockResult(EFail);
		}

	if ( dataOk )
		{
		CDataWrapper*	wrapper=GetDataWrapperL(wrapperName);
		if ( wrapper==NULL )
			{
			ERR_PRINTF2(KLogMissingWrapper, &wrapperName);
			SetBlockResult(EFail);
			}
		else
			{
			CFont*	font=NULL;
			INFO_PRINTF1(_L("execute GetNearestFontToDesignHeightInPixels(CFont*&, TFontSpec)"));
			TInt	err=GetBitmapDevice()->GetNearestFontToDesignHeightInPixels(font, fontSpec);
			if ( err!=KErrNone )
				{
				ERR_PRINTF2(KLogError, err);
				SetError(err);
				}
			else
				{
				wrapper->SetObjectL(font);
				}
			}
		}
	}

void CT_DataBitmapDevice::DoCmdGetNearestFontToMaxHeightInPixelsL(const TDesC& aSection)
	{
	TBool	dataOk=ETrue;

	TFontSpec	fontSpec;
	if ( !GetFontSpecFromConfig(aSection, KFldFont, fontSpec) )
		{
		dataOk=EFalse;
		ERR_PRINTF2(KLogMissingParameter, &KFldFont());
		SetBlockResult(EFail);
		}

	TInt	maxHeight;
	if ( !GetIntFromConfig(aSection, KFldMaxHeight, maxHeight) )
		{
		dataOk=EFalse;
		ERR_PRINTF2(KLogMissingParameter, &KFldMaxHeight());
		SetBlockResult(EFail);
		}

	TPtrC		wrapperName;
	// get BitmapUtilData object from parameters
	if ( !GetStringFromConfig(aSection, KFldFont, wrapperName) )
		{
		dataOk=EFalse;
		ERR_PRINTF2(KLogMissingParameter, &KFldFont());
		SetBlockResult(EFail);
		}

	if ( dataOk )
		{
		CDataWrapper*	wrapper=GetDataWrapperL(wrapperName);
		if ( wrapper==NULL )
			{
			ERR_PRINTF2(KLogMissingWrapper, &wrapperName);
			SetBlockResult(EFail);
			}
		else
			{
			CFont*	font=NULL;
			INFO_PRINTF1(_L("execute GetNearestFontToMaxHeightInPixels(CFont*&, TFontSpec, TInt)"));
			TInt	err=GetBitmapDevice()->GetNearestFontToMaxHeightInPixels(font, fontSpec, maxHeight);
			if ( err!=KErrNone )
				{
				ERR_PRINTF2(KLogError, err);
				SetError(err);
				}
			else
				{
				wrapper->SetObjectL(font);
				}
			}
		}
	}

void CT_DataBitmapDevice::DoCmdGetPixel(const TDesC& aSection)
	{
	// get typeface index from parameters
	TPoint	point;
	if ( !GetPointFromConfig(aSection, KFldPoint(), point) )
		{
		ERR_PRINTF2(KLogMissingParameter, &KFldPoint());
		SetBlockResult(EFail);
		}
	else
		{
		TRgb	color;
		INFO_PRINTF1(_L("execute GetPixel(TRgb&, const TPoint&)"));
		GetBitmapDevice()->GetPixel(color, point);
		INFO_PRINTF5(KLogColor, color.Red(), color.Green(), color.Blue(), color.Alpha());

		TRgb	expected;
		if ( GetRgbFromConfig(aSection, KFldExpected, expected) )
			{
			if ( expected!=color )
				{
				ERR_PRINTF1(KLogNotExpectedValue);
				SetBlockResult(EFail);
				}
			}
		}
	}

void CT_DataBitmapDevice::DoCmdGetScanLineL(const TDesC& aSection)
	{
	TBool	dataOk=ETrue;

	// get point x coordinate from parameters
	TPoint	point;
	if ( !GetPointFromConfig(aSection, KFldPoint(), point) )
		{
		dataOk=EFalse;
		ERR_PRINTF2(KLogMissingParameter, &KFldPoint());
		SetBlockResult(EFail);
		}

	// get length from parameters
	TInt	length = 0;
	if ( !GetIntFromConfig(aSection, KFldLength(), length) )
		{
		dataOk=EFalse;
		ERR_PRINTF2(KLogMissingParameter, &KFldLength());
		SetBlockResult(EFail);
		}

	// get buffer length from parameters
	TInt	buffLength = 0;
	if ( !GetIntFromConfig(aSection, KFldBuffLength(), buffLength) )
		{
		dataOk=EFalse;
		ERR_PRINTF2(KLogMissingParameter, &KFldBuffLength());
		SetBlockResult(EFail);
		}

	// get display mode from parameters
	TDisplayMode	displayMode;
	if ( !CT_GraphicsUtil::ReadDisplayMode(*this, aSection, KFldDisplayMode(), displayMode) )
		{
		ERR_PRINTF2(KLogMissingParameter, &KFldDisplayMode());
		SetBlockResult(EFail);
		dataOk=EFalse;
		}

	if ( dataOk )
		{
		// call GetScanLine()
		TUint8*	buffer = new (ELeave) TUint8[buffLength];
		TPtr8	scanline(buffer, buffLength, buffLength);

		INFO_PRINTF1(_L("execute GetScanLine(TDes8&, const TPoint&, TInt, TDisplayMode)"));
		GetBitmapDevice()->GetScanLine(scanline, point, length, displayMode);
		
		// Check ScanLine.
		TBool checkScanLine = EFalse;
		if ( !GetBoolFromConfig(aSection, KFldCheckScanLine(), checkScanLine)  )
			{
			INFO_PRINTF1(KLogDoNotCheckScanLine);	
			}
		else 
			{
			if(!checkScanLine)
				{
				INFO_PRINTF1(KLogDoNotCheckScanLine);
				}
			else
				{
				INFO_PRINTF1(KLogDoCheckScanLine);
				CheckScanLineL(aSection,scanline);
				}
			}
		delete [] buffer;
		}
	}

void CT_DataBitmapDevice::DoCmdRemoveFile(const TDesC& aSection)
	{
	TBool	dataOk = ETrue;
	TInt	id;
	if ( !GetIntFromConfig(aSection, KFldId(), id) )
		{
		TPtrC	file;
		if ( !GetStringFromConfig(aSection, KFldFile(), file) )
			{
			dataOk=EFalse;
			ERR_PRINTF2(KLogMissingParameter, &KFldId());
			ERR_PRINTF2(KLogMissingParameter, &KFldFile());
			SetBlockResult(EFail);
			}
		else
			{
			TBool	found=EFalse;	//	Filename found in array
			for ( TInt index=iFile.Count(); (index>0) && (!found);  )
				{
				if ( iFile[--index]==file )
					{
					id=iId[index];
					iFile.Remove(index);
					iId.Remove(index);
					found=ETrue;
					}
				}
			if ( !found )
				{
				dataOk=EFalse;
				ERR_PRINTF2(KLogMissingFilename, &file);
				SetBlockResult(EFail);
				}
			}
		}

	if ( dataOk )
		{
		INFO_PRINTF1(_L("execute RemoveFile(TInt)"));
		GetBitmapDevice()->RemoveFile(id);
		}
	}

void CT_DataBitmapDevice::CheckScanLineL(const TDesC& aSection,TDes8 &aBuf)
	{
	INFO_PRINTF1(KLogDoCheckScanLine);	
	
	TBool appendCheckDataOK = ETrue;
	TSize	bitmapSize;
	if ( !GetSizeFromConfig(aSection, KFldSize, bitmapSize) )
		{
		ERR_PRINTF2(KLogMissingParameter, &KFldSize);
		SetBlockResult(EFail);
		appendCheckDataOK = EFalse;
		}
	
	TDisplayMode displayMode;
	if ( !CT_GraphicsUtil::ReadDisplayMode(*this, aSection, KFldDisplayMode(), displayMode) )
		{
		ERR_PRINTF1(_L("No display mode"));
		SetBlockResult(EFail);
		appendCheckDataOK = EFalse;
		}
	
	if (appendCheckDataOK)
		{
		CFbsBitmap* fbsbitmap = new(ELeave) CFbsBitmap();
		fbsbitmap->Create(bitmapSize,displayMode);
		fbsbitmap->SetScanLine(aBuf,1);
		
		TPoint pixelPoint;
		if ( !GetPointFromConfig(aSection, KFldPoint(), pixelPoint) )
			{
			ERR_PRINTF2(KLogMissingParameter, &KFldPoint());
			SetBlockResult(EFail);
			appendCheckDataOK=EFalse;
			}	
		TRgb expected;
		if ( !GetRgbFromConfig(aSection, KFldExpected, expected) )
			{
			ERR_PRINTF2(KLogMissingParameter, &KFldExpected());
			SetBlockResult(EFail);
			appendCheckDataOK=EFalse;
			}
		if(appendCheckDataOK)
			{
			TRgb actual;
			fbsbitmap->GetPixel(actual,pixelPoint);
			if(actual != expected)
				{
				ERR_PRINTF5(KLogColor, actual.Red(), actual.Green(), actual.Blue(), actual.Alpha());
				ERR_PRINTF5(KLogColor, expected.Red(), expected.Green(), expected.Blue(), expected.Alpha());
				SetBlockResult(EFail);
				}
			}

		delete fbsbitmap;
		}
	}
