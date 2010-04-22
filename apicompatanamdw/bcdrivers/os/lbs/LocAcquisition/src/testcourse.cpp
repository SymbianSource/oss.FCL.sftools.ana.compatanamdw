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
* Description:  Helper class for TCourse class
*
*/


// System Includes


// User Includes
#include "testcourse.h"
#include <e32std.h>

// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
TTestCourse ::TTestCourse (CStifLogger* aLog):iLog(aLog)
    {
        
    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
TTestCourse ::~TTestCourse ()
    {
        
    }


// ---------------------------------------------------------
//  Test case for Default Constructor of TCourse
// ---------------------------------------------------------
//	
TInt TTestCourse :: DefaultConstructor()
    {
	TCourse course;
	
    return KErrNone;
    }

// ---------------------------------------------------------
//  Test case for setting & getting the speed
// ---------------------------------------------------------   
 TInt TTestCourse ::SetGetSpeed(CStifItemParser& aItem)
    {
        TCourse course;
        TInt speed = 0;
        TInt error = aItem.GetNextInt(speed);
        TReal32 speed1 = static_cast<TReal32>(speed);
        if(!error)
            {
                course.SetSpeed(speed1);
                if(course.Speed()==speed1)
                    {
                        return KErrNone;
                        
                    }
                else
                    return KErrGeneral;
                
            }
         else
            return KErrGeneral;
    }
// ---------------------------------------------------------
//  Test case for setting & getting the heading
// ---------------------------------------------------------   


TInt TTestCourse :: SetGetHeading(CStifItemParser& aItem)
    {
        TCourse course;
        TInt heading = 0;
        TInt error = aItem.GetNextInt(heading);
        TReal32 heading1 = static_cast<TReal32>(heading);
        if(!error)
            {
                course.SetHeading(heading1);
                if(course.Heading()==heading1)
                    {
                        return KErrNone;
                        
                    }
                else
                    return KErrGeneral;
                
            }
         else
            return KErrGeneral;
    }
    
// ---------------------------------------------------------
//  Test case for setting & getting the course
// ---------------------------------------------------------   


TInt TTestCourse :: SetGetCourse(CStifItemParser& aItem)
    {
        TCourse course_obj;
        TInt course = 0;
        TInt error = aItem.GetNextInt(course);
        TReal32 course1 = static_cast<TReal32>(course);
        if(!error)
            {
                course_obj.SetCourse(course1);
                if(course_obj.Course()==course1)
                    {
                        return KErrNone;
                        
                    }
                else
                    return KErrGeneral;
                
            }
         else
            return KErrGeneral;
    }
    
    
// ---------------------------------------------------------
//  Test case for setting & getting the speed accuracy
// ---------------------------------------------------------   


TInt TTestCourse :: SetGetSpeedAcc(CStifItemParser& aItem)
    {
        TCourse course_obj;
        TInt speed_acc = 0;
        TInt error = aItem.GetNextInt(speed_acc);
        TReal32 speed_acc1 = static_cast<TReal32>(speed_acc);
        if(!error)
            {
                course_obj.SetSpeedAccuracy(speed_acc1);
                if(course_obj.SpeedAccuracy()==speed_acc1)
                    {
                        return KErrNone;
                        
                    }
                else
                    return KErrGeneral;
                
            }
         else
            return KErrGeneral;
    }
    
// ---------------------------------------------------------
//  Test case for setting & getting the heading accuracy
// ---------------------------------------------------------   


TInt TTestCourse :: SetGetHeadingAcc(CStifItemParser& aItem)
    {
        TCourse course_obj;
        TInt heading_acc = 0;
        TInt error = aItem.GetNextInt(heading_acc);
        TReal32 heading_acc1 = static_cast<TReal32>(heading_acc);
        if(!error)
            {
                course_obj.SetHeadingAccuracy(heading_acc1);
                if(course_obj.HeadingAccuracy()==heading_acc1)
                    {
                        return KErrNone;
                        
                    }
                else
                    return KErrGeneral;
                
            }
         else
            return KErrGeneral;
    }
    
    
// ---------------------------------------------------------
//  Test case for setting & getting the course accuracy
// ---------------------------------------------------------   


TInt TTestCourse :: SetGetCourseAcc(CStifItemParser& aItem)
    {
        TCourse course_obj;
        TInt course_acc = 0;
        TInt error = aItem.GetNextInt(course_acc);
        TReal32 course_acc1 = static_cast<TReal32>(course_acc);
        if(!error)
            {
                course_obj.SetCourseAccuracy(course_acc1);
                if(course_obj.CourseAccuracy()==course_acc1)
                    {
                        return KErrNone;
                        
                    }
                else
                    return KErrGeneral;
                
            }
         else
            return KErrGeneral;
    }
