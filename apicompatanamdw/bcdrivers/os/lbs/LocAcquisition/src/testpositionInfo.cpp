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
* Description:  Test Class For TPositionInfo
*
*/


// System Includes


// User Includes
#include "testpositionInfo.h"


// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
CTestPositionInfo::CTestPositionInfo(CStifLogger* aLog)
    :iLog(aLog)
    {

    }
    
// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
CTestPositionInfo::~CTestPositionInfo()
    {

    }

// ---------------------------------------------------------
// CTestPositionInfo::CheckModuleId
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionInfo::CheckModuleIdL( CStifItemParser& aItem )
	{
	 TUint PsyUidInInt;
	 TUid PsyUid;
	 TPositionModuleId retrieveId;

	 //Get the PSYUid from the Stif framework
	 User::LeaveIfError(aItem.GetNextInt(PsyUidInInt, EHex));

	 //lex.Val(PsyUidInInt,EHex);	 
	 PsyUid.iUid = PsyUidInInt;
	 
	 iPositionInfo.SetModuleId(PsyUid);
	 retrieveId=iPositionInfo.ModuleId();

	 if( PsyUid == retrieveId )
	 	{
	 	iLog->Log(_L("CheckModuleId - Passed"));
	 	return KErrNone;
	 	}
	 else
	 	{
	 	iLog->Log(_L("CheckModuleId - Failed"));
	 	return KErrGeneral;
	 	}
		
	}

// ---------------------------------------------------------
// CTestPositionInfo::CheckUpdateType
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionInfo::CheckUpdateTypeL( CStifItemParser& aItem )
	{
	TInt aUpdateType;
	User::LeaveIfError(aItem.GetNextInt(aUpdateType));
	TInt err; 
	 
	switch(aUpdateType)
		{
		case 0:
			iPositionInfo.SetUpdateType(EPositionUpdateUnknown);
			if( EPositionUpdateUnknown == iPositionInfo.UpdateType() )
				{
				iLog->Log(_L("CheckModuleId - Passed"));
	 			err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckModuleId - Failed"));
	 			err = KErrGeneral;
				}
			break;	
		default:
			iPositionInfo.SetUpdateType(EPositionUpdateGeneral);
			if( EPositionUpdateGeneral == iPositionInfo.UpdateType() )
				{
				iLog->Log(_L("CheckModuleId - Passed"));
	 			err = KErrNone;
				}
			else
				{
				iLog->Log(_L("CheckModuleId - Failed"));
	 			err = KErrGeneral;
				}
		}
	return err;
	}

// ---------------------------------------------------------
// CTestPositionInfo::CheckPosition
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionInfo::CheckPosition( )
	{
	TPosition iPosition1;
	TPosition iPosition2;
	iPositionInfo.SetPosition(iPosition1);
	iPositionInfo.GetPosition(iPosition2);
	
	TInt some1 = iPosition1.Latitude();
	TInt some2 = iPosition2.Latitude();
	
	some1 = iPosition1.Longitude();
	some2 = iPosition2.Longitude();
	
	some1 = iPosition1.Altitude();
	some2 = iPosition2.Altitude();
	
	TBool some3 = (iPosition1.Time() == iPosition2.Time());
	
	
	if( Math::IsNaN(iPosition2.Latitude()) && 
		Math::IsNaN(iPosition2.Longitude()) && 
		Math::IsNaN(iPosition2.Altitude()) && 
		iPosition1.Time() == iPosition2.Time() )
		{
		iLog->Log(_L("CheckPosition - Passed"));
	 	return KErrNone;
		}
	else
		{
		iLog->Log(_L("CheckPosition - Failed"));
	 	return KErrGeneral;
		}
	}
