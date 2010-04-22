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
* Description:  Test Class For TPositionCourseInfo
*
*/


// System Includes


// User Includes
#include "testpositioncourseinfo.h"


// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
CTestPositionCourseInfo::CTestPositionCourseInfo(CStifLogger* aLog)
    : iLog(aLog)
    {

    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
CTestPositionCourseInfo::~CTestPositionCourseInfo()
    {

    }

// ---------------------------------------------------------
// CTestPositionCourseInfo::CheckCourse
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CTestPositionCourseInfo::CheckCourse( )
    {
	TCourse iCourse1;
	TCourse iCourse2;
	iPositionCourseInfo.SetCourse(iCourse1);
	iPositionCourseInfo.GetCourse(iCourse2);
	if( Math::IsNaN(iCourse2.Speed()) && 
			Math::IsNaN(iCourse2.Heading()) && 
			Math::IsNaN(iCourse2.SpeedAccuracy()) && 
			Math::IsNaN(iCourse2.HeadingAccuracy()) )
		{
		iLog->Log(_L("CheckCourse - Passed"));
	 	return KErrNone;
		}
	else
		{
		iLog->Log(_L("CheckCourse - Failed"));
	 	return KErrGeneral;
		}
    }




