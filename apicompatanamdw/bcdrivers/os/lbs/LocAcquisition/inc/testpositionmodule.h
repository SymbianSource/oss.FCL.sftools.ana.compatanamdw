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
* Description:  Helper class for TPositionModuleStatus,TPositionModuleStatusEventBase
*                & TPositionModuleStatusEvent classes
*
*/


#ifndef CLBSPOSITIONMODULE_H
#define CLBSPOSITIONMODULE_H

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
 *  Helper class for TPositionModuleStatus,TPositionModuleStatusEventBase
 *  & TPositionModuleStatusEvent classes. 
 *
 *  @lib tlbslocacquisition.lib
 *  @since S60 v3.2
 */

class TTestPositionModule
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
        TTestPositionModule(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~TTestPositionModule();

    public:         
        
                   
		  
        // New functions  
        /**
        * Test case for default constructor of TPositionModuleStatus
        */
        TInt DefaultPositionModuleStatus();
        /**
        * Test case for setting & getting Device Status
        */
        TInt SetGetDeviceStatus(CStifItemParser& aItem);
        /**
        * Test case for setting & getting Device Quality Status
        */
        TInt SetGetDataQualityStatus(CStifItemParser& aItem);
        /**
        * Test case for setting & getting Requested Events
        */
        TInt SetGetRequestedEvents(CStifItemParser& aItem);
        /**
        * Test case for setting & getting ModuleId
        */
        TInt SetGetModuleId();
        
        /**
        * Test case for setting & getting Occurred Events
        */
        TInt SetGetOccurredEvents(CStifItemParser& aItem);
         /**
        * Test case for setting & getting SystemModule Events
        */
        TInt SetGetSystemModuleEvents(CStifItemParser& aItem);
        /**
        * Test case for default constructor of TPositionModuleStatusEvent 
        */
        TInt DefaultPositionModuleStatusEvent();
        /**
        * Test case for constructor with events as arguments
        */
        TInt PositionModuleStatusEvent1(CStifItemParser& aItem);
        /**
        * Test case for setting & getting ModuleStatus
        */
        TInt SetGetModuleStatus(CStifItemParser& aItem);
        /**
	    * Test case for setting & getting UpdateInterval
	    */
	    TInt SetGetUpdateInterval(TTimeIntervalMicroSeconds aInterval);
       /**
	    * Test case for setting & getting UpdateTimeOut
	    */
	    TInt SetGetUpdateTimeOut(TTimeIntervalMicroSeconds aTimeOut);
	    /**
	    * Test case for setting & getting MaxUpdateAge
	    */
	    TInt SetGetMaxUpdateAge(TTimeIntervalMicroSeconds aMaxAge);
	    /**
	    * Test case for default constructor of TPositionUpdateOptions
	    */
	    TInt DefaultPosUpdateOptions();
	    /**
	    * Test case for constructor of TPositionUpdateOptions with arguments
	    */
	    TInt PosUpdateOptions1();
	    /**
	    * Test case for checking if partial updates are allowed
	    */
	    TInt SetGetPartialUpdates(CStifItemParser& aItem);
       
       
       
       
	    
	    
		 
		  
	private:
	    
	   
	   
	    
    private:  //data
	   
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
        
     };     

#endif      //  CLBSPOSITIONMODULE_H

// End of File
