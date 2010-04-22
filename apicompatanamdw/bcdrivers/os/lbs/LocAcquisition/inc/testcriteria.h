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
* Description:  Helper class for TPositionSelectionOrder,TPositionCriteriaBase
*                & TPositionCriteria class
*
*/


#ifndef CLBSTESTCRITERIA_H
#define CLBSTESTCRITERIA_H

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
 *  This class is a helper class used to handle the functions of TPositionSelectionOrder,
 *  TPositionCriteriaBase   & TPositionCriteria class
 *  class. 
 *
 *  @lib tlbslocacquisition.lib
 *  @since S60 v3.2
 */

class TTestCriteria
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
        TTestCriteria(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~TTestCriteria();

    public:         
        
                   
		  
        // New functions  
	    /**
	     * Test case for Default Constructor of TPositionSelectionOrder
	     * Returns KErrNone if successful
	     */
	    TInt DefaultPositionSelectionOrder(); 
	    /**
	    * Test case for SetOrderTimeToFirstFix
	    */
	    TInt DoSetOrderTimeToFirstFix(CStifItemParser& aItem);
	    /**
	    * Test case for SetOrderTimeToNextFix
	    */
	    TInt DoSetOrderTimeToNextFix(CStifItemParser& aItem);
	    /**
	    * Test case for SetOrderHorizontalAccuracy
	    */
	    TInt DoSetOrderHorizontalAccuracy(CStifItemParser& aItem);
	    /**
	    * Test case for SetOrderVerticalAccuracy
	    */
	    TInt DoSetOrderVerticalAccuracy(CStifItemParser& aItem);
	    /**
	    * Test case for SetOrderCostIndicator
	    */
	    TInt DoSetOrderCostIndicator(CStifItemParser& aItem);
	    /**
	    * Test case for SetOrderPowerConsumption
	    */
	    TInt DoSetOrderPowerConsumption(CStifItemParser& aItem);
	    /**
	    * Test case to check ResetSelectionOrder
	    */
	    TInt DoResetSelectionOrder();
	    /**
	    * Test case to check ClearSelectionOrder
	    */
	    TInt DoClearSelectionOrder();
	    /**
	    * Test case for NumSelectionItems
	    */
	    TInt GetNumSelectionItems();
	    /**
	    * Test case for GetSelectionItem
	    */
	    TInt DoGetSelectionItem();
	    /**
	    * Test case for setting & getting RequiredCapabilities
	    */
	    TInt SetGetRequiredCapabilities(CStifItemParser& aItem);
	    /**
	    * Test case for ClearRequiredCapabilities
	    */
	    TInt DoClearRequiredCapabilities();
	    /**
	    * Test case for setting & getting RequiredQuality
	    */
	    TInt SetGetRequiredQuality();
	    /**
	    * Test case for setting & getting SelectionOrder
	    */
	    TInt SetGetSelectionOrder();
	    /**
	    * Test case for ResetCriteria
	    */
	    TInt DoResetCriteria();
	    /**
	    * Test case for ClearCriteria
	    */
	    TInt DoClearCriteria();
		/**
		* Test Case for default constructor of TPositionCriteria
		*/
		TInt DefaultPositionCriteria(); 
		/**
		* Test Case for  constructor of TPositionCriteria with required capabilities
		* as parameter
		*/
		TInt PositionCriteriaCons(CStifItemParser& aItem); 
		 
		 
		 
		  
	private:
	    
	   
	   
	    
    private:  //data
	   
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
        
     };     

#endif      //  CLBSTESTCRITERIA_H

// End of File
