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
* Description:  Test Class For RPositionServer
*
*/


#ifndef CTESTPOSITIONSERVER_H
#define CTESTPOSITIONSERVER_H

// System Includes
#include <StifLogger.h>
#include <StifTestModule.h>
#include <e32base.h>
#include <e32std.h>

#include <lbs.h>
#include <LbsPositionInfo.h>
#include <LbsCommon.h>
#include <LbsRequestor.h>
#include <lbssatellite.h>
#include <lbsclasstypes.h>

// Constants

// CLASS DECLARATION
/**
 *  Test Class to invoke the RPositionServer methods
 *
 *  This class is a helper class. The status variable of this active obect is 
 *  used to provide the asynchronous method Calls.
 *
 *  @lib testlbslocacquisition.lib
 *  @since S60 v3.2
 */

class CTestPositionServer :public CActive
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
        CTestPositionServer(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~CTestPositionServer();

    public:         
        
        //From CActive
          void RunL();
          void DoCancel();
		  TInt RunError(TInt aError);   
		         
		TInt CancelRequest();
		
		//
		RPositionServer& CTestPositionServer::PositionServer();		  

        // New functions  
        
	    /**
	     * Test Case for Connect to Position Sever 
	     * This will test for Successful Connect
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */        
		  TInt Connect();
		  
	    /**
	     * Test Case for Disconnect to Position Sever 
	     * This will test for Successful Disconnect
	     *
	     * @since S60 v3.2
	     *
	     */   		  
		  TInt Disconnect();

	    /**
	     * Method for Checking the Version of Position Server 
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */        
		  TInt VersionCheck();

	    /**
	     * Test Case for Getting Default Modu;e Id 
	     *
	     * @since S60 v3.2
	     *
	     */  	  
		  TInt GetDefaultModule();		  	  
		  
	    /**
	     * Test Case for Getting the number of Positioning Modules
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  TInt GetModuleNum();		  	  
		  
	    /**
	     * Test Case for Getting Module Info by Index
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  TInt GetModuleInfoIndex(TInt aIndex);		  	  
		  
	    /**
	     * Test Case for Getting Module Info by Id
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  TInt GetModuleInfoId(TPositionModuleId aUid);		  	  
		  
	    /**
	     * Test Case for Getting Module Status
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  TInt GetModuleStatus(TPositionModuleId aUid);		  	  
		  		  
	    /**
	     * Test Case for Getting Notification on change of 
	     * Module Status
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  TInt GetModuleChangeNotification(TInt aEvent, TPositionModuleId aUid);		  	  
		  		  
	    /**
	     * Test Case for Cancelling the request to 
	     * Module Change Notification
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  TInt GetModuleChangeNotificationCancel(TInt aEvent, TPositionModuleId aUid);		  	  
		  		  
	    /**
	     * Test Case for Checking the Duplicate Panic on
	     * Module Change Notification
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  void GetModuleChangeNotificationPanicDuplicate(TInt aEvent, TPositionModuleId aUid);		  	  
		  
		/**
	     * Test Case for Cheacking the Outstanding Panic on
	     * Module Change Notification
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  void DisconnectPanicOutstanding(TInt aEvent, TPositionModuleId aUid);	  	  
		  		  	   
    private:  //data
	    /**
	     * Session for Postion Server
	     */     		 
    	RPositionServer         iPosServer;
	    /**
	     * Sub Session for Postion Server
	     */      	
        RPositioner             iPositioner;  
	    /**
	     * Pointer to Stif Logger - Does not Own
	     */           
        CStifLogger* 			iLog;
	    /**
	     * ModuleEvent with Event on Request Complete
	     */           
		TPositionModuleStatusEvent iModuleEvent;
	        
     };     

#endif      // CTESTPOSITIONSERVER_H

// End of File
