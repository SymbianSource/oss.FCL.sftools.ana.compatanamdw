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
* Description:  Helper class for TPositionClassTypeBase, TPositionQualityBase 
*                TPositionQuality TPositionUpdateOptionsBase &
*                TPositionUpdateOptions classes
*
*/


#ifndef CLBPOSITIONQUALITY_H
#define CLBPOSITIONQUALITY_H

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
#include <StifTestModule.h>
// Constants


// CLASS DECLARATION
/**
 *  
 *
 *  This class is a helper class used to handle the functions of TPositionClassTypeBase,
 *  TPositionQualityBase & TPositionQuality classes
 *  class. 
 *
 *  @lib tlbslocacquisition.lib
 *  @since S60 v3.2
 */

class TTestPositionQuality
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
        TTestPositionQuality(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~TTestPositionQuality();

    public:         
        
                   
		  
        // New functions 
        /**
	    * Test case for PositionClassType
	    */ 
	    TInt GetPositionClassType();
	    /**
	    * Test case for PositionClassSize
	    */ 
	    TInt GetPositionClassSize();
	    /**
	    * Test Case for Compare
	    */
	    TInt DoCompare();
	    /**
	    * Test Case for IsDefined
	    */
	    TInt GetIsDefined();
	    
        /**
	    * Test case for getting the HighWaterMark
	    */
	    TInt GetHighWaterMark();
	    /**
	    * Test case for default constructor of TPositionQuality class
	    */
	    TInt DefaultPositionQuality();
	    /**
	    * Test case for setting & gettting the time to first fix
	    */
	    TInt SetGetTimeToFirstFix(TTimeIntervalMicroSeconds time);
	     /**
	    * Test case for setting & gettting the time to next fix
	    */
	    TInt SetGetTimeToNextFix(TTimeIntervalMicroSeconds time);
	     /**
	    * Test case for setting & gettting the horizontal accuracy
	    */
	    TInt SetGetHorizontalAccuracy(TReal32 haccuracy);
	     /**
	    * Test case for setting & gettting the vertical accuracy
	    */
	    TInt SetGetVerticalAccuracy(TReal32 vaccuracy);
		   /**
	    * Test case for setting & gettting the cost indicator
	    */
	    TInt SetGetCostIndicator(CStifItemParser& aItem);
	      /**
	    * Test case for setting & gettting the power consumption
	    */
	    TInt SetGetPowerConsumption(CStifItemParser& aItem);
	    /**
	    * Test case for constructor of TPositionModuleInfo
	    */
	    TInt PositionModuleInfoConst();
	    /**
	    * Test case for setting & getting ModuleId
	    */
	    TInt SetGetModuleId();
	    /**
        * Test case for setting & getting ModuleName
        */
        TInt SetGetModuleName(CStifItemParser& aItem);
        /**
        * Test case for checking if module is available
        */
        TInt SetGetIsAvailable(CStifItemParser& aItem);
	     /**
	    * Test case for setting & getting TechnologyType
	    */
	    TInt SetGetTechnologyType(CStifItemParser& aItem);
	      /**
	    * Test case for setting & getting DeviceLocation
	    */
	    TInt SetGetDeviceLocation(CStifItemParser& aItem);
	     /**
	    * Test case for setting & getting Capabilities
	    */
	    TInt SetGetCapabilities(CStifItemParser& aItem);
	    /**
	    * Test case for setting & getting Classes supported
	    */
	    TInt SetGetClassesSupported(TPositionClassFamily posClassType,TUint32 posInfoClasstype);
	    /**
	    * Test case for setting & getting Version
	    */
	    TInt SetGetVersion(CStifItemParser& aItem);
	    /**
	    * Test case for setting & getting UpdateInterval
	    */
	    TInt SetGetUpdateInterval(TTimeIntervalMicroSeconds aInterval);
	    
	    
		  
	private:
	    
	   
	   
	    
    private:  //data
	   
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
        
     };     

#endif      //  CLBPOSITIONQUALITY_H

// End of File
