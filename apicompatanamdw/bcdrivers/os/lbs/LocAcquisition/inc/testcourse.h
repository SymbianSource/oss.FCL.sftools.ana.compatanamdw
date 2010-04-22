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


#ifndef CLBSCOURSE_H
#define CLBSCOURSE_H

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
 *  This class is a helper class used to handle the functions of TCourse
 *  class. 
 *
 *  @lib tlbslocacquisition.lib
 *  @since S60 v3.2
 */

class TTestCourse
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
        TTestCourse(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~TTestCourse();

    public:         
        
                   
		  
        // New functions  
	    /**
	     * Test case for Default Constructor of TCourse
	     * Returns KErrNone if successful
	     */
	    TInt DefaultConstructor(); 
		 /**
		 * Test case for setting & getting the speed
		 */
		 TInt SetGetSpeed(CStifItemParser& aItem);
		 /**
		 * Test case for setting & getting the heading
		 */
		 TInt SetGetHeading(CStifItemParser& aItem);
		  /**
		 * Test case for setting & getting the course
		 */
		 TInt SetGetCourse(CStifItemParser& aItem);
		  /**
		 * Test case for setting & getting the speed accuracy
		 */
		 TInt SetGetSpeedAcc(CStifItemParser& aItem);
		  /**
		 * Test case for setting & getting the headingaccuracy
		 */
		 TInt SetGetHeadingAcc(CStifItemParser& aItem);
		  /**
		 * Test case for setting & getting the course accuracy
		 */
		 TInt SetGetCourseAcc(CStifItemParser& aItem);
		 
		 
		  
	private:
	    
	   
	   
	    
    private:  //data
	   
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
        
     };     

#endif      //  CLBSCOURSE_H

// End of File
