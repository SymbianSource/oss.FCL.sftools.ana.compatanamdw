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
* Description:  Test Class For TPositionInfo
*
*/


#ifndef CTESTPOSITIONINFO_H
#define CTESTPOSITIONINFO_H

// System Includes
#include <StifLogger.h>
#include <StifParser.h>
#include <StifTestModule.h>
#include <e32base.h>
#include <e32std.h>
#include <bautils.h>
#include <f32file.h>

#include <lbs.h>
#include <LbsPositionInfo.h>
#include <LbsCommon.h>
#include <LbsRequestor.h>
#include <lbssatellite.h>
#include <lbsclasstypes.h>


// Constants


// CLASS DECLARATION
/**
 *  Test Class For TPositionInfo
 *
 *  This has TPositionInfo object which invokes TPositionInfo methods 
 *
 *  @lib testlbslocacquisition.lib
 *  @since S60 v3.2
 */

class CTestPositionInfo : public CBase
    {
    public:  
    
    	// Constructors and destructor
        /**
        * C++ default constructor.
        */
        CTestPositionInfo(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~CTestPositionInfo();

    public:         

        // New functions  
	    /**
	     * Method to Check the Module Id information 
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */        
		  TInt CheckModuleIdL( CStifItemParser& aItem );
		  
	    /**
	     * Method to Check the Update Type
	     *
	     * @since S60 v3.2
	     *
	     */   		  
		  TInt CheckUpdateTypeL( CStifItemParser& aItem );
		  		  
	    /**
	     * Test Case for Disconnect to Position Sever 
	     * This will test for Successful Disconnect
	     *
	     * @since S60 v3.2
	     *
	     */   	
		  TInt CheckPosition( );	    
		  		  	   
    private:  //data
	    /**
	     * TPositionInfo Instance
	     */     		 
    	TPositionInfo         iPositionInfo;
    	  
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
	        
     };     

#endif      // CTESTPOSITIONINFO_H

// End of File
