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


#ifndef CLBSSATELLITE_H
#define CLBSSATELLITE_H

// System Includes
#include <StifLogger.h>
#include <StifParser.h>
#include <lbs.h>
#include <LbsPositionInfo.h>
#include <LbsCommon.h>
#include <LbsRequestor.h>
#include <lbssatellite.h>
#include <lbsclasstypes.h>
#include <LbsPosition.h>

// Constants


// CLASS DECLARATION
/**
 *  
 *
 *  This class is a helper class used to handle the functions of TSatelliteData 
 *  & TPositionSatelliteInfo
 *  class. 
 *
 *  @lib tlbslocacquisition.lib
 *  @since S60 v3.2
 */

class TTestSatellite
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
        TTestSatellite(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~TTestSatellite();

    public:         
        
                   
		  
        // New functions  
	    /**
	    * Test case for Default Constructor of TSatelliteData
	    */
	    TInt DefaultSatelliteData();
	    /**
	    * Test case for setting & getting SatelliteId
	    */
	    TInt SetGetSatelliteId(CStifItemParser& aItem);
	    /**
	    * Test case for setting & getting Azimuth
	    */
	    TInt SetGetAzimuth(CStifItemParser& aItem);
	    /**
	    * Test case for setting & getting Elevation
	    */
	    TInt SetGetElevation(CStifItemParser& aItem);
	    /**
	    * Test case for checking if Used
	    */
	    TInt SetGetIsUsed(CStifItemParser& aItem);
	    /**
	    * Test case for setting & getting the signal strength
	    */
	    TInt SetGetSignalStrength(CStifItemParser& aItem);
	    /**
	    * Test case for Default Constructor of TPositionSatelliteInfo
	    */
	    TInt DefaultPositionSatelliteInfo();
	    /**
	    * Test case for setting & getting the satellite time
	    */
	    TInt SetGetSatelliteTime(CStifItemParser& aItem);
	    /**
	    * Test case for setting & getting the HorizontalDoP
	    */
	    TInt SetGetHorizontalDoP(CStifItemParser& aItem);
		/**
	    * Test case for setting & getting the VerticalDoP
	    */
	    TInt SetGetVerticalDoP(CStifItemParser& aItem);
	  	/**
	    * Test case for setting & getting the TimeDoP
	    */
	    TInt SetGetTimeDoP(CStifItemParser& aItem);
	    /**
	    * Test case to check the NumSatellitesInView
	    */
		TInt GetNumSatellitesInView(); 
		/**  
	    * Test case for ClearSatellitesInView
	    */
		TInt DoClearSatellitesInView();
		/**
	    * Test case to check the NumSatellitesUsed
	    */
		TInt GetNumSatellitesUsed();  
		/**
	    * Test case for AppendSatelliteData
	    */
		TInt DoAppendSatelliteData();  
		/**
	    * Test case for GetSatelliteData
	    */
		TInt ToGetSatelliteData(); 
		
		  
	private:
	    
	   
	   
	    
    private:  //data
	   
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
        
     };     

#endif      //  CLBSSATELLITE_H

// End of File
