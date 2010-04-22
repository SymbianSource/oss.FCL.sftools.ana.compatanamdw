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
* Description:  Helper class for TCoordinate class
*
*/


#ifndef CLBSCOORDINATE_H
#define CLBSCOORDINATE_H

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
 *  This class is a helper class used to handle the functions of TCoordinate
 *  class. 
 *
 *  @lib tlbslocacquisition.lib
 *  @since S60 v3.2
 */

class TTestCoordinate 
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
        TTestCoordinate (CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~TTestCoordinate();

    public:         
        
                   
		  
        // New functions  
	    /**
	     * Test Case for constructors of TCoordinate class
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */        
		  TInt CreateCoordinate(CStifItemParser& aItem);
		 /**
	     * Test Case for setting the coordinate values
	     */
		  TInt SetCoordinate(CStifItemParser& aItem);
		  /**
		  * Test case for asssigning a new datum to the object
		  */
		  TInt SetGetDatum();
		  /**
		  * Test case for obtaining the distance between two coordinates
		  */
		  TInt GetDistance(CStifItemParser& aItem);
		  /**
		  * Test case for obtaining the bearing between two coordinates
		  */
		  TInt GetBearing(CStifItemParser& aItem);
		  /**
		  * Test case for moving the coordinate object 
		  */
		  TInt MoveTo(CStifItemParser& aItem); 
		  
		  
	private:
	    /**
	     * Default Constructor of TCoordinate
	     * Returns KErrNone if successful
	     */
	    TInt DefaultConstructor();
	    /**
	     * Constructor of TCoordinate with latitude & longtitude as parameters
	     * Returns KErrNone if successful
	     */
	    
	    TInt Constructor1(TReal64 aLatitude,TReal64 aLongitude);
	    /**
	     * Constructor of TCoordinate with latitude,longtitude & altitude
	     * as parametrs
	     * Returns KErrNone if successful
	     */
	    
	    TInt Constructor2(TReal64 aLatitude,TReal64 aLongitude,TReal64 aAltitude);        
    
        /**
        * Test case for setting latitude & longitude
        */
        TInt SetLatLon(TReal64 aLatitude,TReal64 aLongitude);
        /**
        * Test case for setting latitude longitude & altitude
        */
        TInt SetLatLonAlt(TReal64 aLatitude,TReal64 aLongitude,TReal64 aAltitude);
    private:  //data
	   
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
        
     };     

#endif      //  CLBSCOORDINATE_H

// End of File
