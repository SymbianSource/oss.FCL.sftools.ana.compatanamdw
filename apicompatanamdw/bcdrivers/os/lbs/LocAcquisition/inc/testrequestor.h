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
* Description:  Helper class for CRequestorBase class
*
*/


#ifndef CLBSTESTREQUESTOR_H
#define CLBSTESTREQUESTOR_H

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
 *  This class is a helper class used to handle the functions of CRequestorBase
 *  class. 
 *
 *  @lib tlbslocacquisition.lib
 *  @since S60 v3.2
 */
class CTestRequestorBase: public CRequestorBase
    {
    public:
		CTestRequestorBase(){};
		~CTestRequestorBase(){};
	
	    /**
	    * Test case for setting & getting requestor
	    */
		TInt TestExtendedInterface();
	
    };

// CLASS DECLARATION
/**
 *  
 *
 *  This class is a helper class used to handle the functions of CRequestor
 *  class. 
 *
 *  @lib tlbslocacquisition.lib
 *  @since S60 v3.2
 */

class TTestRequestor
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
        TTestRequestor(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~TTestRequestor();

    public:         
        
                   
		  
        // New functions  
	    /**
	    * Test case for setting & getting requestor
	    */
	    TInt SetGetRequestorL(CStifItemParser& aItem);
	    /**
	    * Test case for  getting requestor data
	    */
	    TInt GetRequestorDataL(CStifItemParser& aItem);
	    /**
	    * Test case for  getting requestor type
	    */
	    TInt GetRequestorTypeL(CStifItemParser& aItem);
	    /**
	    * Test case for  getting requestor format
	    */
	    TInt GetRequestorFormatL(CStifItemParser& aItem);
	    /**
	    * Test case for  CRequestor::New
	    */
	    TInt TestRequestorNew(CStifItemParser& aItem);
	    /**
	    * Test case for  CRequestor::NewL
	    */
	    TInt TestRequestorNewL(CStifItemParser& aItem);
	     /**
	    * Test case for  CRequestor::NewLC
	    */
	    TInt TestRequestorNewLC(CStifItemParser& aItem);
	    /**
	    * Test case for  CRequestor::NewL with RReadStream instance
	    */
	    TInt TestRequestorNewL1(CStifItemParser& aItem);
	    /**
	    * Test case for  CRequestor::ExtendedInterface
	    */
		TInt TestExtendedInterface();
		  
	private:
	    
	   
	   
	    
    private:  //data
	   
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
        
     };     

#endif      //  CLBSTESTREQUESTOR_H

// End of File
