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
* Description:  Test Class For RPositioner
*
*/


#ifndef CTESTPOSITIONER_H
#define CTESTPOSITIONER_H

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
#include <LbsCriteria.h>

// Constants

// CLASS DECLARATION
/**
 *  Test Class to invoke the RPositioner methods
 *
 *  This class is a helper class. The status variable of this active obect is 
 *  used to provide the asynchronous method Calls.
 *
 *  @lib testlbslocacquisition.lib
 *  @since S60 v3.2
 */

class CTestPositioner :public CActive,public RPositioner
    {
    public:  
    	//Enumerators
		enum TRequsted
			{
			/** GetLastKnownPosition Requested */
			EGetLastKnownPosition		= 0,
			/** GetPositionInfo Requested */
			EPositionInfo	= 1,
			/** No Requests */
			ENone	= 2
			};
    
    	// Constructors and destructor
        /**
        * C++ default constructor.
        */
        CTestPositioner(CStifLogger* aLog);

        /**
        * Destructor. 
        */
        ~CTestPositioner();

    public:         
        
        //From CActive
          void RunL();
          void DoCancel();
		  TInt RunError(TInt aError);          

		  TInt CancelRequest();

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
		  void Disconnect();
		  		  
	    /**
	     * Test Case for Resolving Which Open has to be called
	     * for Opening Position Module 
	     * This will redirect the call to Open Positioner method.
	     *
	     * @since S60 v3.2
	     *
	     */   	
		  TInt OpenPositionerResolver(RPositionServer& aPosServer, CStifItemParser& aItem );
	    
	    /**
	     * Test Case for Opening a Positioning Module 
	     * This will test for Successful Open
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */ 		  
		  TInt OpenPositioner(RPositionServer& aPosServer);

	    /**
	     * Test Case for Opening a Positioning Module by Id
	     * This will test for Successful Open
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */		  
		  TInt OpenPositionerById(RPositionServer& aPosServer, const TUid aPsyUid);

	    /**
	     * Test Case for Opening a Positioning Module by Id
	     * This will test for Successful Open
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */	
		  TInt OpenPositionerByCriteria(RPositionServer& aPosServer);

	    /**
	     * Test Case for Closing a Positioning Module 
	     * This will test for Successful Disconnect
	     *
	     * @since S60 v3.2
	     *
	     */   		  
		  void ClosePositioner();

	    /**
	     * Method to set the Request State(GetLastKnown/GetPositionInfo)
	     * Helper method
	     *
	     * @since S60 v3.2
	     *
	     */  	  
		  void SetRequestStateL( CStifItemParser& aItem );

	    /**
	     * Method for Closing Position Sever/Positioning Module 
	     * This will test for Panic on Closing Position Sever/Positioning Module
	     * while the request in Pending(Not Cancelled)
	     *
	     * @since S60 v3.2
	     *
	     */  	  
		  void ClosePosServerPanic(TPositionInfoBase *aPosInfo);

	    /**
	     * Test Case for setting the Requestor 
	     * This will test for Successful Set
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  TInt SetRequestor( TInt aType,
		  	TInt aFormat,const TDesC &  aData );  
		  	
	    /**
	     * Test Case for setting the Requestor Stack
	     * This will test for Successful Set
	     *
	     * @since S60 v3.2
	     *
	     */	   
		  TInt SetRequestorStackL( CStifItemParser& aItem );

	    /**
	     * Test Case for Setting Update Options 
	     * This will test for Successful Setting of Update Options
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  TInt SetUpdateOp(TInt aInterval,TInt aTimeOut,TInt aAge);	
		  
	    /**
	     * Test Case for Getting Update Options 
	     * This will test for Successful Getting of Update Options
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  TInt GetUpdateOp(TInt aInterval,TInt aTimeOut,TInt aAge);	
		  
	    /**
	     * Method for Resolving the call to Get Last Known Position 
	     * This will redirect to correct Get Last Known Position method
	     *
	     * @since S60 v3.2
	     *
	     */	
		  TInt GetLastKnownPostionResolverL( CStifItemParser& aItem );
	    
	    /**
	     * Method for Getting the Last Known Position
	     * This will fetch the Position Info from Cache
	     *
	     * @since S60 v3.2
	     *
	     */		  	  
		  TInt GetLastKnownPostionL(TPositionInfoBase *aPosInfo);	   
		  
	    /**
	     * Method for Resolving the call to Cancel 
	     * Get Last Known Position 
	     * This will redirect to correct Cancel method
	     *
	     * @since S60 v3.2
	     *
	     */	
		  TInt GetLastKnownPostionCancelResolverL( CStifItemParser& aItem );
	    
	    /**
	     *  
	     * Method to Cancel the Get Last Known Position
	     *
	     * @since S60 v3.2
	     *
	     */		  	  
		  TInt GetLastKnownPostionCancel(TPositionInfoBase *aPosInfo);
		  
	    /**
	     * Method for Resolving the call to Get Position Info
	     * This will redirect to correct Get Position Info method
	     *
	     * @since S60 v3.2
	     *
	     */	
		  TInt GetPositionInfoResolverL( CStifItemParser& aItem );
	    
	    /**
	     * Method to Get the Position Info from Positioning Module 
	     * Gets the Notification on Successfull.
	     *
	     * @since S60 v3.2
	     *
	     */		  	  
		  TInt GetPositionInfoL(TPositionInfoBase *aPosInfo);
		 
	    /**
	     * Method to Handle Duplicate Panic 
	     * on Get Position Info from Positioning Module 
	     *
	     * @since S60 v3.2
	     *
	     */		  	  
		  void GetPositionInfoPanicDuplicate(TPositionInfoBase *aPosInfo); 	  
		  	    
	    /**
	     * Method for Resolving the call to Cancel Get Position Info
	     * This will redirect to correct Cancel method
	     *
	     * @since S60 v3.2
	     *
	     */	
		  TInt GetPositionInfoCancelResolverL( CStifItemParser& aItem );
	    
	    /**
	     * Method for Cancelling the Get Position Info Request
	     *
	     * @since S60 v3.2
	     *
	     */		  	  
		  TInt GetPositionInfoCancelL(TPositionInfoBase *aPosInfo);
		  
	    /**
	     * Method for Testing ExtendedInterface
	     *
	     * @since S60 v3.2
	     *
	     */	   
		  TInt TestExtendedInterface();
	
	    /**
	     * Utility Method to Delete the Cache
	     *
	     * @since S60 v3.2
	     *
	     */	
		  TInt DeleteLastKnownPostionCacheL();
		  		  	   
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
		
	    /**
	     *  Requested Service
	     */  
		TRequsted iState;
	        
     };     

#endif      // CTESTPOSITIONER_H

// End of File
