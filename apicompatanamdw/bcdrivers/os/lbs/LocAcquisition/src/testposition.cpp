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
* Description:  Helper class for TPosition class
*
*/


// System Includes


// User Includes
#include "testposition.h"
#include <e32std.h>

// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
TTestPosition ::TTestPosition (CStifLogger* aLog):iLog(aLog)
    {
        
    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
TTestPosition ::~TTestPosition ()
    {
        
    }

// -----------------------------------------------------------------------------
// This method calls the respective constructor based on the number of arguments
// -----------------------------------------------------------------------------
//	
TInt TTestPosition ::CreatePosition(CStifItemParser& aItem)
    {
         TLocality locality;
         TInt time = 0;
         TInt error = aItem.GetNextInt(time);
         
         TTime time1(time);
         if(!error)
            {
               return Position1(locality,time1);
            }
         else
            return DefaultConstructor();
	    
    }

// ---------------------------------------------------------
//  Test case for Default Constructor of TPosition
// ---------------------------------------------------------
//	
TInt TTestPosition :: DefaultConstructor()
    {
	TPosition position;
	
    return KErrNone;
    }
// ---------------------------------------------------------
//  Test case for constructor of TPosition with locality object 
// ----------------------------------------------------------

TInt TTestPosition :: Position1(TLocality& locality,TTime time)
    {
       TPosition position(locality,time);
       if(position.Time()!=time)
        {
            return KErrGeneral;
        }
       else
            return KErrNone;
    }
// ---------------------------------------------------------
//  Test case for setting & getting the time
// ----------------------------------------------------------    
TInt TTestPosition :: SetGetTime(CStifItemParser& aItem)
    {
        
         TPosition position;
         TInt time = 0;
         TInt error = aItem.GetNextInt(time);
         
         TTime time1(time);
         if(!error)
            {
                position.SetTime(time1);
                if(position.Time()==time1)
                    {
                        return KErrNone;
                       
                    }
                else return KErrGeneral;
            }
         else
            return KErrGeneral;
    }
    
// ---------------------------------------------------------
//  Test case for setting current time
// ----------------------------------------------------------  

TInt TTestPosition :: SettingTime()
    {
        TPosition position;
        position.SetCurrentTime();
           
        TTime uniTime;
        uniTime.UniversalTime();

        TTimeIntervalSeconds last;
        uniTime.SecondsFrom(position.Time(), last);
        if(last <= TTimeIntervalSeconds(1))
            {
                return KErrNone;
            }
         else
          return KErrGeneral;
       
            
           
        
    }
    
    
    
    
// ---------------------------------------------------------
//  Test case for checking Speed method
// ----------------------------------------------------------  

TInt TTestPosition :: GetSpeed(CStifItemParser& aItem)
    {
            TInt lat1 = 0;
            TInt lon1 = 0;
            TInt lat2 = 0;
            TInt lon2 = 0;
            TInt haccuracy1 = 0;
            TInt haccuracy2 = 0; 
            TInt time1 = 0;
            TInt time2 = 0;
            TInt err1 = aItem.GetNextInt(lat1);
            TInt err2 = aItem.GetNextInt(lon1);
            TInt err3 = aItem.GetNextInt(lat2);
            TInt err4 = aItem.GetNextInt(lon2);
            TInt err5 = aItem.GetNextInt(haccuracy1);
            TInt err6 = aItem.GetNextInt(haccuracy2);
            TInt err7 = aItem.GetNextInt(time1);
            TInt err8 = aItem.GetNextInt(time2);
            TTime time3(time1);
            TTime time4(time2);
            TReal32 speed; 
            
             if(!err1 && !err2 && !err3 && !err4 && !err5 && !err6 && !err7 && !err8)
                {
                    
                    TCoordinate co_ord1(lat1,lon1);
                    TCoordinate co_ord2(lat2,lon2);
                    TLocality locality1(co_ord1,haccuracy1);
                    TLocality locality2(co_ord2,haccuracy2);
                    TPosition position1(locality1,time3);
                    TPosition position2(locality2,time4);
                    TInt error = position1.Speed(position2,speed);
                    if(!error)
                        {
                            return KErrNone;
                        }
                    else
                        return error;
                }
                else
                    return KErrArgument;
                    
                    
    }
    
    
// ---------------------------------------------------------
//  Test case for checking Speed method with accuracy
// ----------------------------------------------------------  

TInt TTestPosition :: GetSpeed1(CStifItemParser& aItem)
    {
            TInt lat1 = 0;
            TInt lon1 = 0;
            TInt lat2 = 0;
            TInt lon2 = 0;
            TInt haccuracy1 = 0;
            TInt haccuracy2 = 0; 
            TInt time1 = 0;
            TInt time2 = 0;
            TInt err1 = aItem.GetNextInt(lat1);
            TInt err2 = aItem.GetNextInt(lon1);
            TInt err3 = aItem.GetNextInt(lat2);
            TInt err4 = aItem.GetNextInt(lon2);
            TInt err5 = aItem.GetNextInt(haccuracy1);
            TInt err6 = aItem.GetNextInt(haccuracy2);
            TInt err7 = aItem.GetNextInt(time1);
            TInt err8 = aItem.GetNextInt(time2);
            TTime time3(time1);
            TTime time4(time2);
            TReal32 speed; 
            TReal32 delta;
            
             if(!err1 && !err2 && !err3 && !err4 && !err5 && !err6 && !err7 && !err8)
                {
                    
                    TCoordinate co_ord1(lat1,lon1);
                    TCoordinate co_ord2(lat2,lon2);
                    TLocality locality1(co_ord1,haccuracy1);
                    TLocality locality2(co_ord2,haccuracy2);
                    TPosition position1(locality1,time3);
                    TPosition position2(locality2,time4);
                    TInt error = position1.Speed(position2,speed,delta);
                    if(!error)
                        {
                            return KErrNone;
                        }
                    else
                        return error;
                }
                else
                    return KErrArgument;
                    
                    
    }
    

