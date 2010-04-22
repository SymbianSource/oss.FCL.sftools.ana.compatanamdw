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


#ifndef CLBSPOSITION_H
#define CLBSPOSITION_H

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
 *  This class is a helper class used to handle the functions of TPosition
 *  class. 
 *
 *  @lib tlbslocacquisition.lib
 *  @since S60 v3.2
 */

class TTestPosition
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
        TTestPosition(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~TTestPosition();

    public:         
        
                   
		  
        // New functions  
	    /**
	     * Test Case for constructors of TPosition class
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */        
		  TInt CreatePosition(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting the time
		  * Returns KErrNone if successful. 
		  */
		  TInt SetGetTime(CStifItemParser& aItem);
		  /**
		  * Test case for setting current time
		  * Returns KErrNone if successful. 
		  */
		  TInt SettingTime();
		  /**
		  * Test case for checking Speed method
		  * Returns KErrNone if successful. 
		  */
		  TInt GetSpeed(CStifItemParser& aItem);
		  /**
		  * Test case for checking Speed method with accuracy
		  * Returns KErrNone if successful. 
		  */
		  TInt GetSpeed1(CStifItemParser& aItem);
		  
		 
		  
	private:
	    /**
	     * Test case for Default Constructor of TPosition
	     * Returns KErrNone if successful
	     */
	    TInt DefaultConstructor();
	    /**
	    * Test case for constructor of TPosition with locality object 
	    * & time as parameters
	    * Returns KErrNone if successful
	    */
	    TInt Position1(TLocality& locality,TTime time);
	    
	   
	    
    private:  //data
	   
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
        
     };     

#endif      //  CLBSPOSITION_H

// End of File
