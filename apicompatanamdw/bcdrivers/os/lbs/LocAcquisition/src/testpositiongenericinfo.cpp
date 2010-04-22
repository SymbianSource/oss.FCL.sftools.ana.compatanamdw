/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test Class For HPositionGenericInfo
*
*/


// System Includes


// User Includes
#include "testpositiongenericinfo.h"


// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
CTestPositionGenericInfo::CTestPositionGenericInfo(CStifLogger* aLog)
    : iPositionGenericInfo(NULL),iLog(aLog)
    {

    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
CTestPositionGenericInfo::~CTestPositionGenericInfo()
    {
	if(iPositionGenericInfo)
		{
		delete iPositionGenericInfo;
		iPositionGenericInfo = NULL;
		}
    }

// ---------------------------------------------------------
// CTestPositionGenericInfo::CheckNewL
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionGenericInfo::CheckNewL( CStifItemParser& aItem )
	{
	TInt bufferSize;
	TInt maxFields;
	TInt ret;
	if( aItem.GetNextInt(bufferSize) != KErrNotFound && 
		aItem.GetNextInt(maxFields) != KErrNotFound )
		{
		ret = CreateLC( bufferSize, maxFields );
		}
	else if ( aItem.GetNextInt(bufferSize) != KErrNotFound )
		{
		ret = CreateLC( bufferSize );
		}	
	else
		{
		ret = CreateLC( );
		}
	return ret;
	}

// ---------------------------------------------------------
// CTestPositionGenericInfo::CreateLC
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionGenericInfo::CreateLC( TInt aBufferSize, TInt aMaxFields )
	{
	HPositionGenericInfo* PositionGenericInfo = HPositionGenericInfo::NewLC( aBufferSize, aMaxFields );
	if( aBufferSize == PositionGenericInfo->BufferSize() && 
		aMaxFields == PositionGenericInfo->MaxFields() )
		{
		CleanupStack::PopAndDestroy(PositionGenericInfo);
		iLog->Log(_L("CheckNewLC - Passed"));
		return KErrNone;
		}
	else
		{
		CleanupStack::PopAndDestroy(PositionGenericInfo);
		iLog->Log(_L("CheckNewLC - Failed"));	
		return KErrGeneral;
		}
	}

// ---------------------------------------------------------
// CTestPositionGenericInfo::CreateLC
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionGenericInfo::CreateLC( TInt aBufferSize )
	{
	HPositionGenericInfo* PositionGenericInfo = HPositionGenericInfo::NewLC( aBufferSize );
	if(aBufferSize == PositionGenericInfo->BufferSize() && 
		KPositionGenericInfoDefaultMaxFields == PositionGenericInfo->MaxFields() )
		{
		CleanupStack::PopAndDestroy(PositionGenericInfo);
		iLog->Log(_L("CheckNewLC - Passed"));
		return KErrNone;
		}
	else
		{
		CleanupStack::PopAndDestroy(PositionGenericInfo);
		iLog->Log(_L("CheckNewLC - Failed"));	
		return KErrGeneral;
		}
	}

// ---------------------------------------------------------
// CTestPositionGenericInfo::CreateLC
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionGenericInfo::CreateLC()
	{
	HPositionGenericInfo* PositionGenericInfo = HPositionGenericInfo::NewLC( );
	if(KPositionGenericInfoDefaultBufferSize == PositionGenericInfo->BufferSize() && 
		KPositionGenericInfoDefaultMaxFields == PositionGenericInfo->MaxFields() )
		{
		CleanupStack::PopAndDestroy(PositionGenericInfo);
		iLog->Log(_L("CheckNewLC - Passed"));
		return KErrNone;
		}
	else
		{
		CleanupStack::PopAndDestroy(PositionGenericInfo);
		iLog->Log(_L("CheckNewLC - Failed"));	
		return KErrGeneral;
		}
	}
	
// ---------------------------------------------------------
// CTestPositionGenericInfo::CreateL
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionGenericInfo::CreateL()
	{
	iPositionGenericInfo = HPositionGenericInfo::NewL( );
	if(KPositionGenericInfoDefaultBufferSize == iPositionGenericInfo->BufferSize() && 
		KPositionGenericInfoDefaultMaxFields == iPositionGenericInfo->MaxFields() )
		{
		iLog->Log(_L("CheckNewL - Passed"));
		return KErrNone;
		}
	else
		{
		iLog->Log(_L("CheckNewL - Failed"));	
		return KErrGeneral;
		}
	}
	
// ---------------------------------------------------------
// CTestPositionGenericInfo::Delete
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionGenericInfo::Delete()
	{
	if(iPositionGenericInfo)
		{
		delete iPositionGenericInfo;
		iPositionGenericInfo = NULL;
		}	
	return KErrNone;
	}

// ---------------------------------------------------------
// CTestPositionGenericInfo::CheckRequestedFieldsL
//
// (other items were commented in a header).
// ---------------------------------------------------------
// 		  
TInt CTestPositionGenericInfo::CheckRequestedFieldsL( )
	{
	TInt err = CreateL();
	TPositionFieldId aPositionFieldIdList[3];
	aPositionFieldIdList[0] = EPositionFieldHorizontalSpeed;
	aPositionFieldIdList[1] = EPositionFieldVerticalSpeed;
	aPositionFieldIdList[2] = EPositionFieldTrueCourse;
	
	iPositionGenericInfo->SetRequestedFields(aPositionFieldIdList);
	
	if(iPositionGenericInfo->IsRequestedField(aPositionFieldIdList[0]) && 
		iPositionGenericInfo->IsRequestedField(aPositionFieldIdList[1]) && 
		iPositionGenericInfo->IsRequestedField(aPositionFieldIdList[2]) )
		{
		iLog->Log(_L("CheckRequestedField - Passed"));
		err = KErrNone;
		}
	else
		{
		iLog->Log(_L("CheckRequestedField - Failed"));
		err = KErrGeneral;
		}
	Delete();	
	return err;
	}

// ---------------------------------------------------------
// CTestPositionGenericInfo::CheckOrderOfRequestedFieldL
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionGenericInfo::CheckOrderOfRequestedFieldL( )
	{
	TInt err = CreateL();
	TPositionFieldId aPositionFieldIdList[3];
	aPositionFieldIdList[0] = EPositionFieldHorizontalSpeed;
	aPositionFieldIdList[1] = EPositionFieldVerticalSpeed;
	aPositionFieldIdList[2] = EPositionFieldTrueCourse;
	
	iPositionGenericInfo->SetRequestedFields(aPositionFieldIdList);
	
	TInt some = iPositionGenericInfo->FirstRequestedFieldId();
	TInt some1 = iPositionGenericInfo->NextRequestedFieldId(aPositionFieldIdList[0]);
	TBool some3 = iPositionGenericInfo->IsFieldAvailable( EPositionFieldHorizontalSpeed );
	
	if( aPositionFieldIdList[1] == iPositionGenericInfo->NextRequestedFieldId(aPositionFieldIdList[0]) && 
		!iPositionGenericInfo->IsFieldAvailable( EPositionFieldVerticalSpeed ) )
		{
		iLog->Log(_L("CheckOrderOfRequestedField - Passed"));
		err = KErrNone;
		}
	else
		{
		iLog->Log(_L("CheckOrderOfRequestedField - Failed"));
		err = KErrGeneral;
		}
	Delete();	
	return err;
	}

// ---------------------------------------------------------
// CTestPositionGenericInfo::CheckClearPositionDataL
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionGenericInfo::CheckClearPositionDataL()
	{
	TInt err = CreateL();
	iPositionGenericInfo->ClearPositionData();
	Delete();	
	return KErrNone;
	}

// ---------------------------------------------------------
// CTestPositionGenericInfo::CheckClearRequestedFieldsL
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionGenericInfo::CheckClearRequestedFieldsL()
	{
	TInt err = CreateL();
	iPositionGenericInfo->SetRequestedField(EPositionFieldHorizontalSpeed);
	iPositionGenericInfo->ClearRequestedFields();
	if(EPositionFieldNone == iPositionGenericInfo->FirstRequestedFieldId())
		{
		iLog->Log(_L("CheckClearRequestedFieldsL - Passed"));
		err = KErrNone;
		}
	else
		{
		iLog->Log(_L("CheckClearRequestedFieldsL - Failed"));
		err = KErrGeneral;
		}
	Delete();	
	return err;
	}

// ---------------------------------------------------------
// CTestPositionGenericInfo::CheckSetGetValueL
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionGenericInfo::CheckSetGetValueL( CStifItemParser& aItem )
	{
    TInt choice;
    User::LeaveIfError(aItem.GetNextInt(choice));
	TPositionFieldId positionFieldId = EPositionFieldHorizontalSpeed;
	TInt err = CreateL();
	
	switch(choice)
		{
		case EInt8:
			TInt value11;
			TInt8 value12;
			User::LeaveIfError(aItem.GetNextInt(value11));
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, static_cast<TInt8>(value11))) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value12)) &&
				value11 == static_cast<TInt>(value12) )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;	
		case EInt16:
			TInt value21;
			TInt16 value22;
			User::LeaveIfError(aItem.GetNextInt(value21));
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, static_cast<TInt16>(value21))) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value22)) &&
				value21 == value22 )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;	
		case EInt32:
			TInt value31;
			TInt32 value32;
			User::LeaveIfError(aItem.GetNextInt(value31));
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, static_cast<TInt32>(value31))) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value32)) &&
				value31 == value32 )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;
		case EInt64:
			TInt value41;
			TInt64 value42;
			User::LeaveIfError(aItem.GetNextInt(value41));
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, static_cast<TInt64>(value41))) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value42)) &&
				value41 == value42 )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;
		case EUint8:
			TInt value51;
			TUint8 value52;
			User::LeaveIfError(aItem.GetNextInt(value51));
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, static_cast<TUint8>(value51))) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value52)) &&
				value51 == value52 )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;	
		case EUint16:
			TInt value61;
			TUint16 value62;
			User::LeaveIfError(aItem.GetNextInt(value61));
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, static_cast<TUint16>(value61))) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value62)) &&
				value61 == value62 )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;	
		case EUint32:
			TInt value71;
			TUint32 value72;
			User::LeaveIfError(aItem.GetNextInt(value71));
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, static_cast<TUint32>(value71))) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value72)) &&
				value71 == value72 )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;		
		case EReal32:
			TInt value81;
			TReal32 value82;
			User::LeaveIfError(aItem.GetNextInt(value81));
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, static_cast<TReal32>(value81))) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value82)) &&
				value81 == value82 )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;		
		case EReal64:
			TInt value91;
			TReal64 value92;
			User::LeaveIfError(aItem.GetNextInt(value91));
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, static_cast<TReal64>(value91))) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value92)) &&
				value91 == value92 )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;		
		case EDesC8:
			TPtrC value101;
			User::LeaveIfError(aItem.GetNextString(value101));
			TBuf8<100> value102;
			value102.Copy(value101);
			TBuf8<100> value103;

			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, value102)) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value103)) &&
				(0 == value102.Compare(value103)) )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;		
		case EDesC16:
			TPtrC value111;
			TBuf16<100> value112;
			User::LeaveIfError(aItem.GetNextString(value111));
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, value111)) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value112)) &&
				(0 == value111.Compare(value112)) )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;			
		case EPtrC8:
			TPtrC value121;
			User::LeaveIfError(aItem.GetNextString(value121));
			TBuf8<100> value122;
			value122.Copy(value121);
			
			TPtrC8 value123 = value122.Ptr();
			value122.Copy(value121);
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, value122)) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value123)) &&
				(0 == value123.Compare(value122)) )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;		
		case EPtrC16:
			TPtrC value131;
			TPtrC16 value132;
			User::LeaveIfError(aItem.GetNextString(value131));
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, static_cast<TPtrC16>(value131))) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value132)) &&
				(0 == value131.Compare(value132)) )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;	
		case ETime:
			TInt value141;
			User::LeaveIfError(aItem.GetNextInt(value141));
			TTime value142(value141);
			TTime value143;
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, value142)) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value143)) &&
				value142==value143 )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;
		case ETimeIntervalMicroSeconds:
			TInt value151;
			User::LeaveIfError(aItem.GetNextInt(value151));
			TTimeIntervalMicroSeconds value152(value151);
			TTimeIntervalMicroSeconds value153;
			if((KErrNone == iPositionGenericInfo->SetValue(positionFieldId, value152)) &&
				(KErrNone == iPositionGenericInfo->GetValue(positionFieldId, value153)) &&
				value152 == value153 )
				{
				iLog->Log(_L("CheckSetGetValueL - Passed"));
				err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckSetGetValueL - Failed"));
				err = KErrGeneral;	
				}
			break;
		default:
				iLog->Log(_L("CheckSetGetValueL - Wrong Value"));
				err = KErrGeneral;	
		}

	Delete();	
	return err;
	}
