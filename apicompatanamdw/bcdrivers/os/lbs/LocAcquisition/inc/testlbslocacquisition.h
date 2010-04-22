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
* Description:  Test Class which has the list of test cases
*
*/



#ifndef TESTLBSLOCACQUISITION_H
#define TESTLBSLOCACQUISITION_H

//  System Includes
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>

// MACROS
//#define ?macro ?macro_def
#define TEST_MODULE_VERSION_MAJOR 30
#define TEST_MODULE_VERSION_MINOR 9
#define TEST_MODULE_VERSION_BUILD 38

// CONSTANTS
_LIT( KtlbslocacquisitionLogPath, "\\logs\\testframework\\testlbslocacquisition\\" ); 
_LIT( KtlbslocacquisitionLogFile, "testlbslocacquisition.txt" ); 

// FORWARD DECLARATIONS
class CTestLbsLocAcquisition;
class CTestPositionServer;
class CTestPositioner;
class CTestPositionInfo;
class CTestPositionCourseInfo;
class CTestPositionGenericInfo;

// CLASS DECLARATION

/**
*  CTestLbsLocAcquisition test class for STIF Test Framework TestScripter.
*  This is the testclass for Location Acquisition API
*
*  @lib testlbslocacquisition.lib
*  @since S60 v3.2
*/

NONSHARABLE_CLASS(CTestLbsLocAcquisition) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTestLbsLocAcquisition* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTestLbsLocAcquisition();

    public: // New functions

    public: // Functions from base classes

        /**
        * From CScriptBase Runs a script line.
        * @since S60 v3.2
        * @param aItem Script line containing method name and parameters
        * @return Symbian OS error code
        */
        virtual TInt RunMethodL( CStifItemParser& aItem );
        /**
         * Method used to log version of test module
         */
        void SendTestModuleVersion();

    private:

        /**
        * C++ default constructor.
        */
          CTestLbsLocAcquisition( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
          void ConstructL();

        /**
        * Frees all resources allocated from test methods.
        * @since S60 v3.2
        */
          void Delete();
          
	    /**
	     * Test Case for Connect of Position Sever 
	     * This will test for Successful Connect
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */
          TInt Connect( CStifItemParser& aItem );   

	    /**
	     * Test Case for Connect of Position Sever with allowed Panic.
	     * This will test for EPositionServerHandleNotClosed Panic
	     * on Connect
	     *
	     * @since S60 v3.2
	     *
	     */
          TInt ConnectPanic( CStifItemParser& aItem );  
          
	    /**
	     * Test Case for Version Check of Position Sever 
	     * This will test for Version of Server.
	     *
	     * @since S60 v3.2
	     *
	     */
		  TInt VersionCheck( CStifItemParser& aItem );
		  
	    /**
	     * Test Case for Disconnect of Position Sever 
	     * This will test for Successful Disconnect
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */   		  
		  TInt Disconnect( CStifItemParser& aItem );
		  
	    /**
	     * Test Case for Disconnect of Position Sever 
	     * This will test for EPositionRequestsNotCancelled Panic
	     * on Disconnect
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */ 
		  TInt DisconnectPanicOutstandingL( CStifItemParser& aItem );
		  		  
	    /**
	     * Test Case for Opening a Positioning Module 
	     * This will test for Successful Open
	     *
	     * @since S60 v3.2
	     * Returns KErrNone if successful. 
	     *
	     */ 		  
		  TInt OpenPositioner( CStifItemParser& aItem );

	    /**
	     * Test Case for Opening a Positioning Module 
	     * This will test for EPositionServerHandleNotClosed Panic 
	     * on Open Postioning Module
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  TInt OpenPositionerPanicNotClosed( CStifItemParser& aItem ); 
		  
	    /**
	     * Test Case for Opening a Positioning Module 
	     * This will test for EPositionServerBadHandle Panic 
	     * on Open Postioning Module
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  TInt OpenPositionerPanicBadHandle( CStifItemParser& aItem ); 
		  	  
	    /**
	     * Test Case for Opening a Positioning Module by Criteria
	     * This will test for Successfull on Open Postioning Module
	     *
	     * @since S60 v3.2
	     *
	     */		  
		  TInt OpenPositionerByCriteria( CStifItemParser& aItem ); 
		  
	    /**
	     * Test Case for Closing a Positioning Module 
	     * This will test for Successful Close.
	     *
	     * @since S60 v3.2
	     *
	     */   		  
		  TInt ClosePositioner( CStifItemParser& aItem );
		  
	    /**
	     * Test Case for Closing Position Sever/Positioning Module 
	     * This will test for EPositionRequestsNotCancelled Panic 
	     * on Closing Position Sever/Positioning Module
	     *
	     * @since S60 v3.2
	     *
	     */   		  
		  TInt ClosePositionerPanicNotCancelled( CStifItemParser& aItem );		  
		  
	    /**
	     * Test Case for Getting Default Module Id 
	     * This will test for Successful Get
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetDefaultModule( CStifItemParser& aItem );
		  		  
	    /**
	     * Test Case for Getting Default Module Id 
	     * This will test for EPositionServerBadHandle Panic
	     * on Get
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetDefaultModulePanicNoServer( CStifItemParser& aItem );
		  		  
	    /**
	     * Test Case for Getting number of Modules 
	     * This will test for Successful Get
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetModuleNum( CStifItemParser& aItem );
		  		  
	    /**
	     * Test Case for Getting number of Modules  
	     * This will test for EPositionServerBadHandle Panic
	     * on Get.
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetModuleNumPanicNoServer( CStifItemParser& aItem );
		  		  		  
	    /**
	     * Test Case for Getting the Module Info based on Index 
	     * This will test for Successful Get
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetModuleInfoIndexL(CStifItemParser& aItem);
		  		  
	    /**
	     * Test Case for Getting the Module Info based on Index
	     * This will test for Successful Set
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetModuleInfoIndexPanicNoServerL(CStifItemParser& aItem);
		  		  
	    /**
	     * Test Case for setting the Requestor 
	     * This will test for Successful Set
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetModuleInfoIdL(CStifItemParser& aItem);
		  		  
	    /**
	     * Test Case for setting the Requestor 
	     * This will test for EPositionServerBadHandle Panic
	     * on Get.
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetModuleInfoIdPanicNoServerL(CStifItemParser& aItem);
		  		  
	    /**
	     * Test Case for Getting the Status of the Module 
	     * This will test for Successful Get
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetModuleStatusL(CStifItemParser& aItem);	
		  	  		  		  
	    /**
	     * Test Case for Getting Module Status Change Notification 
	     * This will test for Successful Get
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetModuleChangeNotificationL(CStifItemParser& aItem);		
		  		  		  	  		  		  
	    /**
	     * Test Case for Getting Module Status Change Notification 
	     * This will test for Successfull Cancel of 
	     * Get Module Status Notification
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetModuleChangeNotificationCancelL(CStifItemParser& aItem);
		  		  		  
	    /**
	     * Test Case for Getting Module Status Change Notification 
	     * This will test for EPositionServerBadHandle Panic
	     * on Get Module Status Notification
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetModuleChangeNotificationPanicNoServerL(CStifItemParser& aItem);	
		  		  		  
	    /**
	     * Test Case for Getting Module Status Change Notification 
	     * This will test for EPositionDuplicateRequest Panic
	     * on Get Module Status Notification
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt GetModuleChangeNotificationPanicDuplicateL(CStifItemParser& aItem);
		  		  		  
	    /**
	     * Test Case for Cancelling Module status Request
	     * This will test for return of Error Code 
	     * on CancelRequest
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt CancelModuleStatusRequest( CStifItemParser& aItem );
		  		  		  
		 /**
		  * Test Case for Cancelling Module status Request
		  * This will test for EPositionServerBadHandle Panic
		  * on CancelRequest
		  *
		  * @since S60 v3.2
		  *
		  */	   		  
		  TInt CancelModuleStatusRequestPanicNoConnect( CStifItemParser& aItem );		  		  	

	    /**
	     * Test Case for setting the Requestor 
	     * This will test for Successful Set
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt SetRequestorL(CStifItemParser& aItem);
		  
	    /**
	     * Test Case for setting the Requestor 
	     * This will test for EPositionServerBadHandle Panic
	     * on Set
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt SetRequestorPanicNoOpenL(CStifItemParser& aItem);
	  
	    /**
	     * Test Case for setting the Requestor Stack to Positioner
	     * This will test for Successful Set
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt SetRequestorStackL(CStifItemParser& aItem);
		  
	    /**
	     * Test Case for setting the Requestor Stack to Positioner
	     * This will test for EPositionServerBadHandle Panic
	     * on Set
	     *
	     * @since S60 v3.2
	     *
	     */	   		  
		  TInt SetRequestorStackPanicNoOpenL(CStifItemParser& aItem);
		  
	    /**
	     * Test Case for Setting Update Options 
	     * This will test for Successful Setting of Update Options
	     *
	     * @since S60 v3.2
	     *
	     */  		  
		  TInt SetUpdateOpL(CStifItemParser& aItem);		  
		  
	    /**
	     * Test Case for Setting Update Options 
	     * This will test for EPositionServerBadHandle Panic 
	     * on Setting Update Options
	     *
	     * @since S60 v3.2
	     *
	     */  		  
		  TInt SetUpdateOpPanicNoOpenL(CStifItemParser& aItem);
		  
	    /**
	     * Test Case for Getting Update Options 
	     * This will test for Successful Getting of Update Options
	     *
	     * @since S60 v3.2
	     *
	     */  		  
		  TInt GetUpdateOpL(CStifItemParser& aItem);		  
		  
	    /**
	     * Test Case for Getting Update Options 
	     * This will test for EPositionServerBadHandle Panic 
	     * on Getting Update Options
	     *
	     * @since S60 v3.2
	     *
	     */  		  
		  TInt GetUpdateOpPanicNoOpenL(CStifItemParser& aItem);
		  
	    /**
	     * Test Case for Getting Last Known Position 
	     * This will test for Successfull Get
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt GetLastKnownPostionL(CStifItemParser& aItem);

	    /**
	     * Test Case for Getting Last Known Position 
	     * This will test for Cancelling the Get Last Known Position
	     * Request
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt GetLastKnownPostionCancelL(CStifItemParser& aItem);

	    /**
	     * Test Case for Getting Last Known Position 
	     * This will test for EPositionServerBadHandle Panic
	     * on Get Last Known Position
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt GetLastKnownPostionPanicNoOpenL(CStifItemParser& aItem);

	    /**
	     * Test Case for Cancelling Request for Get Last Known Position 
	     * This will test for Successfull Cancel
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt CancelGetLastKnownPostionL(CStifItemParser& aItem);

	    /**
	     * Test Case for Cancelling Request for Get Last Known Position
	     * This will test for EPositionServerBadHandle Panic 
	     * on Cancelling Request
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt CancelGetLastKnownPostionPanicNoConnectL(CStifItemParser& aItem);

	    /**
	     * Test Case for Getting Position Info(Notify) 
	     * This will test for Successfull Get.
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt GetPositionInfoL(CStifItemParser& aItem);

	    /**
	     * Test Case for Cancelling request for Getting Position Info
	     * This will test for Successfull Cancel.
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt GetPositionInfoCancelL(CStifItemParser& aItem);


	    /**
	     * Test Case for Getting Position Info(Notify) 
	     * This will test for EPositionServerBadHandle Panic 
	     * on Get Position Info Notification
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt GetPositionInfoPanicNoOpenL(CStifItemParser& aItem);
		  
	    /**
	     * Test Case for Getting Position Info(Notify) 
	     * This will test for EPositionDuplicateRequest Panic 
	     * on Get Position Info Notification
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt GetPositionInfoPanicDuplicateL(CStifItemParser& aItem);

	    /**
	     * Test Case for Cancelling an Outstanding 
	     * Get Position Info Notification 
	     * This will test for Error Code on Cancel
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt CancelGetPositionInfoL(CStifItemParser& aItem);

	    /**
	     * Test Case for Cancelling an Outstanding 
	     * Get Position Info Notification 
	     * This will test for EPositionServerBadHandle Panic
	     * on Cancel
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt CancelGetPositionInfoPanicNoConnectL(CStifItemParser& aItem);

	    /**
	     * Method for Testing ExtendedInterface of RPositioner
	     *
	     * @since S60 v3.2
	     *
	     */	   
		  TInt PositionerExtendedInterfaceL( CStifItemParser& aItem );

	    /**
	     * Utility Function for Deleting the Cached Position Info
	     * Used to Fail Get Last Known Position
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt DeleteLastKnownPostionCacheL( CStifItemParser& aItem );
		  
//TPositionInfo		  

		/**
		 * Test Case for Checking Module Id in TPositionInfo
		 * This will test for Set/Get ModuleId Methods of
		 * TPositionInfo
		 *
		 * @since S60 v3.2
		 *
		 */ 
		  TInt CheckModuleIdL( CStifItemParser& aItem );
		  
		 /**
		  * Test Case for Checking Update Type in TPositionInfo
		  * This will test for Set/Get UpdateType Methods of
		  * TPositionInfo
		  *
		  * @since S60 v3.2
		  *
		  */ 
		   TInt CheckUpdateTypeL( CStifItemParser& aItem );
		  
		 /**
		  * Test Case for Checking Position in TPositionInfo
		  * This will test for Set/Get Position Methods of
		  * TPositionInfo
		  *
		  * @since S60 v3.2
		  *
		  */ 
		   TInt CheckPosition( CStifItemParser& aItem );
		  
//TPositionCourseInfo

		/**
		 * Test Case for Checking Course info in TPositionCourseInfo
		 * This will test for Panic on Setting Update Options
		 *
		 * @since S60 v3.2
		 *
		 */ 
		  TInt CheckCourse( CStifItemParser& aItem );
		  
//TPositionGenericInfo

	    /**
	     * Test Case for NewL of TPositionGenericInfo 
	     * This will test for all possible instance creation.
	     *
	     * @since S60 v3.2
	     *
	     */ 
		  TInt CheckNewL( CStifItemParser& aItem );

	    /**
	     * Test Case for Get/Set Request Fields in TPositionGenericInfo 
	     * This will test for Successfull Set/Get.
	     *
	     * @since S60 v3.2
	     *
	     */ 
   	 	  TInt CheckRequestedFieldsL( CStifItemParser& aItem );

  	    /**
  	     * Test Case for First Requested Field and Next Requested Field
  	     * This will test for successfull Checks
  	     *
  	     * @since S60 v3.2
  	     *
  	     */ 
   	 	  TInt CheckOrderOfRequestedFieldL( CStifItemParser& aItem );

  	    /**
  	     * Test Case for Clearing Position Data 
  	     * This will test for Successfull clear.
  	     *
  	     * @since S60 v3.2
  	     *
  	     */ 
		  TInt CheckClearPositionDataL( CStifItemParser& aItem );

	    /**
  	     * Test Case for Clearing Request Fields 
  	     * This will test for Successfull clear.
	     *
	     * @since S60 v3.2
	     *
	     */  
		  TInt CheckClearRequestedFieldsL( CStifItemParser& aItem );

	    /**
  	     * Test Case for Clearing Request Fields 
  	     * This will test for Successfull clear.
	     *
	     * @since S60 v3.2
	     *
	     */ 
	  	  TInt CheckSetGetValueL( CStifItemParser& aItem );

//TClasses

		  TInt Coordinate(CStifItemParser& aItem);
		  /**
		  * Test case for setting the coordinate values
		  */
		  TInt SettingCoordinate(CStifItemParser& aItem);
		  /**
		  * Test case for setting the datum
		  */
		  TInt SettingDatum(CStifItemParser& aItem);
		  /**
		  * Test case for obtaining the distance between two coordinates
		  */
		  TInt GettingDistance(CStifItemParser& aItem);
		  /**
		  * Test case for obtaining the bearing between two coordinates
		  */
		  TInt GetBearingTo(CStifItemParser& aItem);
		  /**
		  *  Test case for moving the coordinate object
		  */
		  TInt MoveCoordinate(CStifItemParser& aItem);
		  /**
		  * Test case for the constructors of TLocality class
		  */
		  TInt Locality(CStifItemParser& aItem);
		  /**
		  * Test case for setting the horizontal accuracy
		  */
		  TInt SetGetHorizontalAcc(CStifItemParser& aItem);
		  /**
		  * Test case for setting the vertical accuracy
		  */
		  TInt SetGetVerticalAcc(CStifItemParser& aItem);
		  /**
		  * Test case for setting the horizontal & vertical accuracy
		  */
		  TInt SetGetAcc(CStifItemParser& aItem);
		  /**
		  * Test case for obtaining distance between coordinates
		  */
		  TInt GetDistLocality1(CStifItemParser& aItem);
		  /**
		  * Test case for obtaining distance between localities
		  */
		   TInt GetDistLocality2(CStifItemParser& aItem);
		   /**
		  * Test case for obtaining bearing between coordinates
		  */
		  TInt GetBearingLocality1(CStifItemParser& aItem);
		  /**
		  * Test case for obtaining bearing between localities
		  */
		  TInt GetBearingLocality2(CStifItemParser& aItem);
		  /**
		  * Test case for the constructors of TPosition class
		  */
		  TInt Position(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting the time
		  */
		  TInt PositionSetTime(CStifItemParser& aItem);
		  /**
		  * Test case for setting current time
		  */
		  TInt SettingCurrentTime(CStifItemParser& aItem);
		  /**
		  * Test case for checking Speed method
		  */
		  TInt CheckSpeed(CStifItemParser& aItem);
		  /**
		  * Test case for checking Speed method with accuracy
		  */
		  TInt CheckSpeed1(CStifItemParser& aItem);
		  /**
		  * Test case for Default Constructor of TCourse
		  */
		  TInt Course(CStifItemParser& aItem);
		  /**
		  *  Test case for setting & getting the speed
		  */
		  TInt SettingSpeed(CStifItemParser& aItem);
		  /**
		  *  Test case for setting & getting the heading
		  */
		  TInt SettingHeading(CStifItemParser& aItem);
		  /**
		  *  Test case for setting & getting the course
		  */
		  TInt SettingCourse(CStifItemParser& aItem);
		   /**
		  *  Test case for setting & getting the speed accuracy
		  */
		  TInt SetGetSpeedAccuracy(CStifItemParser& aItem);
		  /**
		  *  Test case for setting & getting the heading accuracy
		  */
		  TInt SetGetHeadingAccuracy(CStifItemParser& aItem);
		  /**
		  *  Test case for setting & getting the course accuracy
		  */
		  TInt SetGetCourseAccuracy(CStifItemParser& aItem);
		  /**
		  * Test case for PositionClassType
		  */
		  TInt CheckPositionClassType(CStifItemParser& aItem);
		  /**
		  * Test case for PositionClassSize
		  */
		  TInt CheckPositionClassSize(CStifItemParser& aItem);
		  /**
		  * Test case for Compare
		  */
		  TInt CheckCompare(CStifItemParser& aItem);
		  /**
		  * Test case for IsDefined
		  */
		  TInt CheckIsDefined(CStifItemParser& aItem);
		  /**
		  * Test case for getting the HighWaterMark
		  */
		  TInt GettingHighWaterMark(CStifItemParser& aItem);
		  /**
		  * Test case for default constructor of TPositionQuality class
		  */
		  TInt PositionQualityConstructor(CStifItemParser& aItem);
		  /**
		  * Test case for setting & gettting the time to first fix
		  */
		  TInt SettingTimeToFirstFix(CStifItemParser& aItem);
		 /**
		  * Test case for setting & gettting the time to next fix
		  */
		  TInt SettingTimeToNextFix(CStifItemParser& aItem);
		  /**
		  * Test case for setting & gettting the horizontal accuracy
		  */
		  TInt SettingHorizontalAccuracy(CStifItemParser& aItem);
		  /**
		  * Test case for setting & gettting the vertical accuracy
		  */
		  TInt SettingVerticalAccuracy(CStifItemParser& aItem);
		  /**
		  * Test case for setting & gettting the cost indicator
		  */
		  TInt SettingCostIndicator(CStifItemParser& aItem);
		  /**
		  * Test case for setting & gettting the power consumption
		  */
		  TInt SettingPowerConsumption(CStifItemParser& aItem);
		  /**
		  * Test case for constructor of TPositionModuleInfoBase
		  */
		  TInt PositionModuleInfo(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting ModuleId
		  */
		  TInt SettingModuleId(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting ModuleName
		  */
		  TInt SettingModuleName(CStifItemParser& aItem);
		  /**
		  * Test case for checking if module is available
		  */
		  TInt SettingAvailable(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting Technologytype
		  */
		  TInt SettingTechnologyType(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting DeviceLocation
		  */
		  TInt SettingDeviceLocation(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting Capabilties
		  */
		  TInt SettingCapabilities(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting Classes supported
		  */
		  TInt SettingClassesSupported(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting Version
		  */
		  TInt SettingVersion(CStifItemParser& aItem);
		  /**
		  * Test case for default constructor of TPositionModuleStatusBase
		  */
		  TInt PositionModuleStatus(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting Device Status
		  */
		  TInt SettingDeviceStatus(CStifItemParser& aItem);
		   /**
		  * Test case for setting & getting DataQuality Status
		  */
		  TInt SettingDataQualityStatus(CStifItemParser& aItem);
		   /**
		  * Test case for setting & getting Requested events
		  */
		  TInt SettingRequestedEvents(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting ModuleId
		  */
		 TInt SetModStatusEventBaseModuleId(CStifItemParser& aItem);
		 /**
		  * Test case for setting & getting Occurred events
		  */
		  TInt SettingOccurredEvents(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting SystemModule events
		  */
		  TInt SettingSystemModuleEvents(CStifItemParser& aItem);
		  /**
		  * Test case for default constructor of TPositionModuleStatusEvent
		  */
		  TInt PositionModuleStatusEvent(CStifItemParser& aItem);
		  /**
		  * Test case for constructor with events as arguments
		  */
		  TInt PositionModuleStatusEventCons(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting ModuleStatus
		  */
		  TInt SettingModuleStatus(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting UpdateInterval
		  */
		  TInt SettingUpdateInterval(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting UpdateTimeOut
		  */
		  TInt SettingUpdateTimeOut(CStifItemParser& aItem);
		 /**
		  * Test case for setting & getting MaxUpdateAge
		  */
		  TInt SettingMaxUpdateAge(CStifItemParser& aItem);
		  /**
		  * Test case for default constructor of TPositionUpdateOptions
		  */
		  TInt PositionUpdateOptions(CStifItemParser& aItem);
		  /**
		  * Test case for constructor of TPositionUpdateOptions with arguments
		  */
		  TInt PositionUpdateOptionsCons(CStifItemParser& aItem);
		  /**
		  * Test case for checking if partial updates are allowed
		  */
		  TInt PartialUpdates(CStifItemParser& aItem);
		  /**
		  * Test case for Default Constructor of TSatelliteData
		  */
		  TInt SatelliteData(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting SatelliteId
		  */
		  TInt SettingSatelliteId(CStifItemParser& aItem);
		   /**
		  * Test case for setting & getting Azimuth
		  */
		  TInt SettingAzimuth(CStifItemParser& aItem);
		   /**
		  * Test case for setting & getting Elevation
		  */
		  TInt SettingElevation(CStifItemParser& aItem);
		  /**
		  * Test case for checking if Used
		  */
		  TInt SettingIsUsed(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting the signal strength
		  */
		  TInt SettingSignalStrength(CStifItemParser& aItem);
		  /**
		  * Test case for Default Constructor of TPositionSatelliteInfo
		  */
		  TInt PositionSatelliteInfo(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting the satellite time
		  */
		  TInt SettingSatelliteTime(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting the HorizontalDoP
		  */
		  TInt SettingHorizontalDoP(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting the VerticalDoP
		  */
		  TInt SettingVerticalDoP(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting the TimeDoP
		  */
		  TInt SettingTimeDoP(CStifItemParser& aItem);
		  /**
		  * Test case to check the NumSatellitesInView
		  */
		  TInt CheckNumSatellitesInView(CStifItemParser& aItem);
		  /**
		  * Test case for ClearSatellitesInView
		  */
		  TInt CheckClearSatellitesInView(CStifItemParser& aItem);
		  /**
		  * Test case to check the NumSatellitesUsed
		  */
		  TInt CheckNumSatellitesUsed(CStifItemParser& aItem);
		  /**
		  * Test case for AppendSatelliteData
		  */
		  TInt CheckAppendSatelliteData(CStifItemParser& aItem);
		  /**
		  * Test case for GetSatelliteData
		  */
		  TInt CheckGetSatelliteData(CStifItemParser& aItem);
		  /**
		  * Test case for Default Constructor of TPositionSelectionOrder
		  */
		  TInt PositionSelectionOrder(CStifItemParser& aItem);
		  /**
		  * Test case for SetOrderTimeToFirstFix
		  */
		  TInt SettingOrderTimeToFirstFix(CStifItemParser& aItem);
		  /**
		  * Test case for SetOrderTimeToNextFix
		  */
		  TInt SettingOrderTimeToNextFix(CStifItemParser& aItem);
		  /**
		  * Test case for SetOrderHorizontalAccuracy
		  */
		  TInt SettingOrderHorizontalAccuracy(CStifItemParser& aItem);
		 /**
		  * Test case for SetOrderVerticalAccuracy
		  */
		  TInt SettingOrderVerticalAccuracy(CStifItemParser& aItem);
		   /**
		  * Test case for SetOrderCostIndicator
		  */
		  TInt SettingOrderCostIndicator(CStifItemParser& aItem);
		 /**
		  * Test case for SetOrderPowerConsumption
		  */
		  TInt SettingOrderPowerConsumption(CStifItemParser& aItem);
		  /**
		  * Test case to check ResetSelectionOrder
		  */
		  TInt CheckResetSelectionOrder(CStifItemParser& aItem);
		  /**
		  * Test case to check ClearSelectionOrder
		  */
		  TInt CheckClearSelectionOrder(CStifItemParser& aItem);
		  /**
		  * Test case for NumSelectionItems
		  */
		  TInt CheckNumSelectionItems(CStifItemParser& aItem);
		  /**
		  * Test case for GetSelectionItem
		  */
		  TInt CheckGetSelectionItem(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting RequiredCapabilities
		  */
		  TInt SettingRequiredCapabilities(CStifItemParser& aItem);
		  /**
		  * Test case for ClearRequiredCapabilities
		  */
		  TInt CheckClearRequiredCapabilities(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting RequiredQuality
		  */
		  TInt SettingRequiredQuality(CStifItemParser& aItem);
		  /**
		  * Test case for setting & getting SelectionOrder
		  */
		  TInt SettingSelectionOrder(CStifItemParser& aItem);
		  /**
		  * Test case for ResetCriteria
		  */
		  TInt CheckResetCriteria(CStifItemParser& aItem);
		   /**
		  * Test case for ClearCriteria
		  */
		  TInt CheckClearCriteria(CStifItemParser& aItem);
		  /**
		  * Test Case for default constructor of TPositionCriteria
		  */
		  TInt PositionCriteria(CStifItemParser& aItem);
		  /**
		  * Test Case for  constructor of TPositionCriteria with required capabilities
		  * as parameter
		  */
		  TInt PositionCriteria1(CStifItemParser& aItem);
		 /**
		  * Test case for setting & getting requestor
		  */
		  TInt SettingRequestorL(CStifItemParser& aItem);
		  /**
		  * Test case for  getting requestor data
		  */
		  TInt GettingRequestorDataL(CStifItemParser& aItem);
		  /**
		  * Test case for  getting requestor type
		  */
		  TInt GettingRequestorTypeL(CStifItemParser& aItem);
		  /**
		  * Test case for  getting requestor format
		  */
		  TInt GettingRequestorFormatL(CStifItemParser& aItem);
		   /**
		  * Test case for  CRequestor::New
		  */
		  TInt RequestorNew(CStifItemParser& aItem);
		   /**
		  * Test case for  CRequestor::NewL
		  */
		  TInt RequestorNewL(CStifItemParser& aItem);
		   /**
		  * Test case for  CRequestor::NewLC
		  */
		  TInt RequestorNewLC(CStifItemParser& aItem);
		   /**
		  * Test case for  CRequestor::NewL with RReadStream instance
		  */
		  TInt RequestorNewL1(CStifItemParser& aItem);
		   /**
		  * Test case for  CRequestor::ExtendedInterface
		  */
		  TInt RequestorExtendedInterfaceL( CStifItemParser& aItem );



    private:    // Data
        CTestPositionServer* iPosServer;
		CTestPositioner* iPositioner;
        CTestPositionInfo* iPositionInfo;
		CTestPositionCourseInfo* iPositionCourseInfo;
		CTestPositionGenericInfo* iPositionGenericInfo; 
    };

#endif      // TESTLBSLOCACQUISITION_H

// End of File
