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
* Description:  Helper class for TSatelliteData & TPositionSatelliteInfo  class
*
*/


// System Includes


// User Includes
#include "testsatellite.h"
#include <e32std.h>

// Constant Declarations

    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ Default Constructor
// ---------------------------------------------------------------------------
//
TTestSatellite ::TTestSatellite (CStifLogger* aLog):iLog(aLog)
    {
        
    }

// ---------------------------------------------------------------------------
// C++ Destructor
// ---------------------------------------------------------------------------
//
TTestSatellite ::~TTestSatellite ()
    {
        
    }


// ---------------------------------------------------------
//  Test case for Default Constructor of TSatelliteData
// ---------------------------------------------------------
//	
TInt TTestSatellite :: DefaultSatelliteData()
    {
	    TSatelliteData satData;
	
        return KErrNone;
    }

// ---------------------------------------------------------
//  Test case for setting & getting SatelliteId
// ---------------------------------------------------------
TInt TTestSatellite :: SetGetSatelliteId(CStifItemParser& aItem)
    {
        TInt satId1 = 0;
        TInt error = aItem.GetNextInt(satId1);
        TSatelliteData satData;
        if(!error)
            {
                satData.SetSatelliteId(satId1);
                TInt satId2 = satData.SatelliteId();
                if(satId2==satId1)
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
//  Test case for setting & getting Azimuth
// ---------------------------------------------------------
TInt TTestSatellite :: SetGetAzimuth(CStifItemParser& aItem)
    {
        TInt azimuth1 = 0;
        TInt error = aItem.GetNextInt(azimuth1);
        TReal32 azimuth2 = static_cast<TReal32>(azimuth1);
        TSatelliteData satData;
        if(!error)
            {
                satData.SetAzimuth(azimuth2);
                TReal32  azimuth3 = satData.Azimuth();
                if(azimuth3==azimuth2)
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
//  Test case for setting & getting Elevation
// ---------------------------------------------------------
TInt TTestSatellite :: SetGetElevation(CStifItemParser& aItem)
    {
        TInt elevation1 = 0;
        TInt error = aItem.GetNextInt(elevation1);
        TReal32 elevation2 = static_cast<TReal32>(elevation1);
        TSatelliteData satData;
        if(!error)
            {
                satData.SetElevation(elevation2);
                TReal32  elevation3 = satData.Elevation();
                if(elevation3==elevation2)
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
//  Test case for checking if Used
// ---------------------------------------------------------
TInt TTestSatellite :: SetGetIsUsed(CStifItemParser& aItem)
    {
        TInt used = 0;
        TInt error = aItem.GetNextInt(used);
        TSatelliteData satData;
        if(!error)
            {
                satData.SetIsUsed(used);
                TBool check = satData.IsUsed();
                if(check==used)
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
// Test case for setting & getting the signal strength
// ---------------------------------------------------------
TInt TTestSatellite :: SetGetSignalStrength(CStifItemParser& aItem)
    {
        TInt sigStrength1 = 0;
        TInt error = aItem.GetNextInt(sigStrength1);
        TSatelliteData satData;
        if(!error)
            {
                satData.SetSignalStrength(sigStrength1);
                TInt sigStrength2 = satData.SignalStrength();
                if(sigStrength2==sigStrength1)
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
//  Test case for Default Constructor of TPositionSatelliteInfo
// ---------------------------------------------------------
//	
TInt TTestSatellite :: DefaultPositionSatelliteInfo()
    {
	    TPositionSatelliteInfo satData;
	
        return KErrNone;
    }
    
// ---------------------------------------------------------
//  Test case for setting & getting the satellite time
// ---------------------------------------------------------
//	
TInt TTestSatellite :: SetGetSatelliteTime(CStifItemParser& aItem)
    {
        TInt satTime = 0;
        TInt error = aItem.GetNextInt(satTime);
        TTime time(satTime);
        TPositionSatelliteInfo satData;
        if(!error)
            {
                satData.SetSatelliteTime(time);
                TTime satelliteTime = satData.SatelliteTime();
                if(satelliteTime==time)
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
//  Test case for setting & getting the HorizontalDoP
// ---------------------------------------------------------
TInt TTestSatellite :: SetGetHorizontalDoP(CStifItemParser& aItem)
    {
        TInt horDoP1 = 0;
        TInt error = aItem.GetNextInt(horDoP1);
        TReal32 horDoP2 = static_cast<TReal32>(horDoP1);
        TPositionSatelliteInfo satData;
        if(!error)
            {
                satData.SetHorizontalDoP(horDoP2);
                TReal32  horDoP3 = satData.HorizontalDoP();
                if(horDoP3==horDoP2)
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
//  Test case for setting & getting the VerticalDoP
// ---------------------------------------------------------
TInt TTestSatellite :: SetGetVerticalDoP(CStifItemParser& aItem)
    {
        TInt verDoP1 = 0;
        TInt error = aItem.GetNextInt(verDoP1);
        TReal32 verDoP2 = static_cast<TReal32>(verDoP1);
        TPositionSatelliteInfo satData;
        if(!error)
            {
                satData.SetVerticalDoP(verDoP2);
                TReal32  verDoP3 = satData.VerticalDoP();
                if(verDoP3==verDoP2)
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
//  Test case for setting & getting the TimeDoP
// ---------------------------------------------------------
TInt TTestSatellite :: SetGetTimeDoP(CStifItemParser& aItem)
    {
        TInt timeDoP1 = 0;
        TInt error = aItem.GetNextInt(timeDoP1);
        TReal32 timeDoP2 = static_cast<TReal32>(timeDoP1);
        TPositionSatelliteInfo satData;
        if(!error)
            {
                satData.SetTimeDoP(timeDoP2);
                TReal32  timeDoP3 = satData.TimeDoP();
                if(timeDoP3==timeDoP2)
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
//  Test case to check the NumSatellitesInView
// ---------------------------------------------------------
TInt TTestSatellite :: GetNumSatellitesInView()
    {
        TPositionSatelliteInfo satData;
        TInt numOfSat = satData.NumSatellitesInView();
        if(numOfSat==0)
            {
                return KErrNone;
            }
        else
            return KErrGeneral;
    }
    
// ---------------------------------------------------------
//  Test case for ClearSatellitesInView
// ---------------------------------------------------------
TInt TTestSatellite :: DoClearSatellitesInView()
    {
        
        TPositionSatelliteInfo satInfo;
        satInfo.ClearSatellitesInView();
        return KErrNone;
           
    }

// ---------------------------------------------------------
//  Test case to check the NumSatellitesUsed
// ---------------------------------------------------------
TInt TTestSatellite :: GetNumSatellitesUsed()
    {
        TPositionSatelliteInfo satData;
        TInt numOfSat = satData.NumSatellitesUsed();
        if(numOfSat==0)
            {
                return KErrNone;
            }
        else
            return KErrGeneral;
    }

// ---------------------------------------------------------
//  Test case for AppendSatelliteData
// ---------------------------------------------------------
TInt TTestSatellite :: DoAppendSatelliteData()
    {
        // AppendSatelliteData() returns KErrOverflow if an attempt is made to store 
    	// details of more than KMaxSatellitesInView
    	TPositionSatelliteInfo satInfo;
    	TSatelliteData satData,satData1;	
    	TInt counter = 0;
    	while(counter<20)
        	{
        	satInfo.AppendSatelliteData(satData);
        	counter++;	
        	}
    	satInfo.AppendSatelliteData(satData);
    	TInt err = satInfo.AppendSatelliteData(satData1);
    	return err;
    }

// ---------------------------------------------------------
//  Test case for GetSatelliteData
// ---------------------------------------------------------
TInt TTestSatellite :: ToGetSatelliteData()
    {
        
    	//GetSatelliteData() returns KErrNotFound if aIndex is outside the range of 0 to 
    	//{NumSatellitesInView() - 1}.	
    	TSatelliteData satData,satData1,satData2;
    	TPositionSatelliteInfo satInfo;
    	TInt numOfSat = satInfo.NumSatellitesInView();
    	TInt err = satInfo.GetSatelliteData(numOfSat+1,satData);
    	return err;
    }
