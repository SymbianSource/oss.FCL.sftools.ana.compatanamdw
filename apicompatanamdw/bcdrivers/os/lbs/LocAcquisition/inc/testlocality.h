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
* Description:  Helper class for TLocality class
*
*/


#ifndef CLBSLOCALITY_H
#define CLBSLOCALITY_H

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
 *  This class is a helper class used to handle the functions of TLocality
 *  class. 
 *
 *  @lib tlbslocacquisition.lib
 *  @since S60 v3.2
 */

class TTestLocality 
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
        TTestLocality(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~TTestLocality();

    public:         
        
                   
		  
        // New functions  
	    /**
	     * Test Case for constructors of TLocality class
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */        
		  TInt CreateLocality(CStifItemParser& aItem);
		 /**
         * Test case for setting horizontal accuracy
         * Returns KErrNone if successful
         */
          TInt SetGetHorAccuracy(CStifItemParser& aItem);
		 /**
         * Test case for setting vertical accuracy
         * Returns KErrNone if successful
         */
          TInt SetGetVerAccuracy(CStifItemParser& aItem);
		  /**
         * Test case for setting horizontal & vertical accuracy
         * Returns KErrNone if successful
         */ 
          TInt SetGetAccuracy(CStifItemParser& aItem);
          /**
          * Test case for obtaining the distance between 2 coordinates
          */
          TInt GetDistance(CStifItemParser& aItem);
          /**
          * Test case for obtaining the distance between 2 localities
          */
          TInt GetDistance1(CStifItemParser& aItem);
          /**
          * Test case for obtaining the distance between 2 coordinates
          */
          TInt GetBearing(CStifItemParser& aItem);
           /**
          * Test case for obtaining the distance between 2 localities
          */
          TInt GetBearing1(CStifItemParser& aItem);
		  
	private:
	    /**
	     * Test case for Default Constructor of TLocality
	     * Returns KErrNone if successful
	     */
	    TInt DefaultConstructor();
	    /**
	    * Test case for Constructor of TLocality with horizontal accuracy
	    * Returns KErrNone if successful
	    */
	    TInt Locality1(TCoordinate& aCoordinate,TReal32 aHorizontalAccuracy);
        /**
        * Test case for Constructor of TLocality with horizontal accuracy & vertical accuracy
        * Returns KErrNone if successful
        */
        TInt Locality2(TCoordinate& aCoordinate,TReal32 aHorizontalAccuracy,TReal32 aVerticalAccuracy);
        
        
	    
    private:  //data
	   
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
        
     };     

#endif      //  CLBSLOCALITY_H

// End of File
