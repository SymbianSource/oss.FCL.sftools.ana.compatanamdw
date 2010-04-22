/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Isv Telephony test module.
*
*/



#ifndef ISVTELEPHONYTEST_H
#define ISVTELEPHONYTEST_H

// INCLUDES
#include <e32base.h>
#include <f32file.h>
#include <StifTestModule.h>
#include <StifLogger.h>
#include "IsvTelephonyTestParser.h" 
#include "IsvTelephonyTestMessageHandler.h" 

// MACROS
//#define ?macro ?macro_def
#define TEST_MODULE_VERSION_MAJOR 30
#define TEST_MODULE_VERSION_MINOR 9
#define TEST_MODULE_VERSION_BUILD 38

// Logging path
_LIT( KIsvTelephonyTestLogPath, "\\logs\\testframework\\IsvTelephonyTest\\" ); 
// Log file
_LIT( KIsvTelephonyTestLogFile, "IsvTelephonyTest.txt" ); 

// Function pointer related internal definitions
// Rounding known bug in GCC
#ifndef __GCC32__
#define GETPTR
#else
#define GETPTR &
#endif  
#define ENTRY(str,func) {_S(str), GETPTR func,0,0,0}
#define FUNCENTRY(func) {_S(#func), GETPTR func,0,0,0}
#define OOM_ENTRY(str,func,a,b,c) {_S(str), GETPTR func,a,b,c}
#define OOM_FUNCENTRY(func,a,b,c) {_S(#func), GETPTR func,a,b,c}

// FORWARD DECLARATIONS
class CIsvTelephonyTest;
class CIsvTelephonyTestEngine; 
class CIsvTelephonyTestParser; 

// DATA TYPES
// TInt CIsvTelephonyTest::<NameOfFunction> ( TTestResult& aResult )
typedef TInt (CIsvTelephonyTest::* TestFunction)(TTestResult&);

// CLASS DECLARATION

/**
*  An internal structure containing a test case name and
*  the pointer to function doing the test
*
*  @lib ?library
*  @since ?Series60_version
*/
class TCaseInfoInternal
    {
    public:
        const TText*    iCaseName;
        TestFunction    iMethod;
        TBool           iIsOOMTest;
        TInt            iFirstMemoryAllocation;
        TInt            iLastMemoryAllocation;
    };

// CLASS DECLARATION

/**
*  A structure containing a test case name and
*  the pointer to function doing the test
*
*  @lib ?library
*  @since ?Series60_version
*/
class TCaseInfo
    {
    public:
        TPtrC iCaseName;
        TestFunction iMethod;
        TBool           iIsOOMTest;
        TInt            iFirstMemoryAllocation;
        TInt            iLastMemoryAllocation;

    TCaseInfo( const TText* a ) : iCaseName( (TText*) a )
        {
        };
    };

// CLASS DECLARATION

/**
*  This a IsvTelephonyTest class.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CIsvTelephonyTest) : 
	public CTestModuleBase,
	public MIsvTelephonyTestMessageHandler 	
    {	
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CIsvTelephonyTest* NewL();

        /**
        * Destructor.
        */
        virtual ~CIsvTelephonyTest();

    public: // Functions from base classes

        /**
        * From CTestModuleBase InitL is used to initialize the 
        *       IsvTelephonyTest. It is called once for every instance of 
        *       IsvTelephonyTest after its creation.
        * @since 
        * @param aIniFile Initialization file for the test module (optional)
        * @param aFirstTime Flag is true when InitL is executed for first 
        *               created instance of IsvTelephonyTest.
        * @return Symbian OS error code
        */
        TInt InitL( TFileName& aIniFile, TBool aFirstTime );

        /**
        * From CTestModuleBase GetTestCasesL is used to inquiry test cases 
        *   from IsvTelephonyTest. 
        * @since ?Series60_version
        * @param aTestCaseFile Test case file (optional)
        * @param aTestCases  Array of TestCases returned to test framework
        * @return Symbian OS error code
        */
        TInt GetTestCasesL( const TFileName& aTestCaseFile, 
                            RPointerArray<TTestCaseInfo>& aTestCases );

        /**
        * From CTestModuleBase RunTestCaseL is used to run an individual 
        *   test case. 
        * @since ?Series60_version
        * @param aCaseNumber Test case number
        * @param aTestCaseFile Test case file (optional)
        * @param aResult Test case result returned to test framework (PASS/FAIL)
        * @return Symbian OS error code (test case execution error, which is 
        *           not reported in aResult parameter as test case failure).
        */   
        TInt RunTestCaseL( const TInt aCaseNumber, 
                           const TFileName& aTestCaseFile,
                           TTestResult& aResult );

        /**
        * From CTestModuleBase; OOMTestQueryL is used to specify is particular
        * test case going to be executed using OOM conditions
        * @param aTestCaseFile Test case file (optional)
        * @param aCaseNumber Test case number (optional)
        * @param aFailureType OOM failure type (optional)
        * @param aFirstMemFailure The first heap memory allocation failure value (optional)
        * @param aLastMemFailure The last heap memory allocation failure value (optional)
        * @return TBool
        */
        virtual TBool OOMTestQueryL( const TFileName& /* aTestCaseFile */, 
                                     const TInt /* aCaseNumber */, 
                                     TOOMFailureType& aFailureType, 
                                     TInt& /* aFirstMemFailure */, 
                                     TInt& /* aLastMemFailure */ );

        /**
        * From CTestModuleBase; OOMTestInitializeL may be used to initialize OOM
        * test environment
        * @param aTestCaseFile Test case file (optional)
        * @param aCaseNumber Test case number (optional)
        * @return None
        */
        virtual void OOMTestInitializeL( const TFileName& /* aTestCaseFile */, 
                                    const TInt /* aCaseNumber */ ); 

        /**
        * From CTestModuleBase; OOMHandleWarningL
        * @param aTestCaseFile Test case file (optional)
        * @param aCaseNumber Test case number (optional)
        * @param aFailNextValue FailNextValue for OOM test execution (optional)
        * @return None
        *
        * User may add implementation for OOM test warning handling. Usually no
        * implementation is required.           
        */
        virtual void OOMHandleWarningL( const TFileName& /* aTestCaseFile */,
                                        const TInt /* aCaseNumber */, 
                                        TInt& /* aFailNextValue */); 

        /**
        * From CTestModuleBase; OOMTestFinalizeL may be used to finalize OOM
        * test environment
        * @param aTestCaseFile Test case file (optional)
        * @param aCaseNumber Test case number (optional)
        * @return None
        *
        */
        virtual void OOMTestFinalizeL( const TFileName& /* aTestCaseFile */, 
                                       const TInt /* aCaseNumber */ );
				/**
         * Method used to log version of test module
         */
        void SendTestModuleVersion();

	public:	// Functions from MIsvTelephonyTestMessageHandler

	   /** 
        * From MIsvTelephonyTestMessageHandler. 
        * Outputs messages to Stif UI or log
        * @param aMessage Contains the message
        */        
		virtual void PrintMessage( const TDesC& aMessage );

       /** 
        * From MIsvTelephonyTestMessageHandler. 
        * Outputs messages to Stif UI or log
        * @param aMessage Contains the message
        */        
		virtual void PrintMessage( TRefByValue<const TDesC> aMessage,... ); 
									    
    private:

        /**
        * C++ default constructor.
        */
        CIsvTelephonyTest();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        /**
        * Function returning test case name and pointer to test case function.
        * @since ?Series60_version
        * @param aCaseNumber test case number
        * @return TCaseInfo 
        */
        const TCaseInfo Case ( const TInt aCaseNumber ) const;

        /**
        * Actual Hardcoded test case functions are listed below.
        */ 
		/**
		* Sets cancellation of async. function tests. 
		* First call this setter case, and then execute test 
		* for async. function, e.g. GetCallBarringStatus
		*/ 
		TInt SetCancelAsyncs( TTestResult& aResult ); 

		/**
		* Clears cancellation of async. function tests. 
		*/ 
		TInt ClearCancelAsyncs( TTestResult& aResult ); 
		
		/**
		* Test CTelephony::GetVersion 
		*/ 
		TInt TestGetVersion( TTestResult& aResult );

		/**
		* Test CTelephony::GetPhoneId 
		*/ 
		TInt TestGetPhoneId( TTestResult& aResult );

		/**
		* Test CTelephony::GetSubscriber 
		*/ 
		TInt TestGetSubscriberId( TTestResult& aResult );

		/**
		* Test CTelephony::GetFlightMode 
		*/ 
		TInt TestGetFlightMode( TTestResult& aResult );

		/**
		* Test CTelephony::GetIndicator 
		*/ 
		TInt TestGetIndicator( TTestResult& aResult );
               
		/**
		* Test CTelephony::GetBatteryInfo
		*/ 
		TInt TestGetBatteryInfo( TTestResult& aResult );

		/**
		* Test CTelephony::GetSignalStrength
		*/ 
		TInt TestGetSignalStrength( TTestResult& aResult );

		/**
		* Test CTelephony::GetLockInfo
		*/ 
		TInt TestGetLockInfo( TTestResult& aResult );

		/**
		* Test CTelephony::SendDTMFTones
		*/ 
		TInt TestSendDTMFTones( TTestResult& aResult );		

		/**
		* Test CTelephony::GetLineStatus
		*/ 
		TInt TestGetLineStatus( TTestResult& aResult );

		/**
		* Test CTelephony::GetCallInfo
		*/ 
		TInt TestGetCallInfoL( TTestResult& aResult );

		/**
		* Test CTelephony::GetNetworkRegistrationStatus
		*/ 
		TInt TestGetNetworkRegistrationStatus( TTestResult& aResult );

		/**
		* Test CTelephony::GetCurrentNetworkInfo  
		*/ 
        TInt TestGetCurrentNetworkInfo( TTestResult& aResult );
        
		/**
		* Test CTelephony::GetCurrentNetworkName  
		*/ 
		TInt TestGetCurrentNetworkName( TTestResult& aResult );

		/**
		* Test CTelephony::GetOperatorName  
		*/ 
		TInt TestGetOperatorName( TTestResult& aResult );

		/**
		* Test CTelephony::GetCallForwardingStatus
		*/ 
		TInt TestGetCallForwardingStatus( TTestResult& aResult );

		/**
		* Test CTelephony::GetCallBarringStatus
		*/ 
		TInt TestGetCallBarringStatus( TTestResult& aResult );

		/**
		* Test CTelephony::GetCallWaitingStatus
		*/ 
		TInt TestGetCallWaitingStatus( TTestResult& aResult );
		
		/**
		* Test CTelephony::GetIdentityServiceStatus
		*/ 
		TInt TestGetIdentityServiceStatus( TTestResult& aResult );
		
		/**
		* Test CTelephony::DialNewCall
		*/ 
		TInt TestDialNewCall( TTestResult& aResult );
		
		/**
		* Test CTelephony::GetCallDynamicCaps
		*/ 
		TInt TestGetCallDynamicCaps( TTestResult& aResult );

		/**
		* Test CTelephony::GetCallStatus
		*/ 
		TInt TestGetCallStatus( TTestResult& aResult );		

		/**
		* Test CTelephony::Hold
		*/ 
		TInt TestHold( TTestResult& aResult );		

		/**
		* Test CTelephony::Resume
		*/ 
		TInt TestResume( TTestResult& aResult );		

		/**
		* Test CTelephony::Swap
		*/ 
		TInt TestSwap( TTestResult& aResult );		

		/**
		* Test CTelephony::Hangup
		*/ 
		TInt TestHangup( TTestResult& aResult );		
		
		/**
		* Test CTelephony::AnswerIncomingCall
		*/ 
		TInt TestAnswerIncomingCall( TTestResult& aResult );		

		/**
		* Test CTelephony::NotifyChange
		*/ 
		TInt TestNotifyChangeVoiceLineStatus ( TTestResult& aResult );		

		/**
		* Test CTelephony::FindDeviceStatus
		*/ 
		TInt TestFindDeviceStatus( TTestResult& aResult );		

		/**
		* Test CTelephony::EstablishDataCall
		*/ 
		TInt TestEstablishDataCall( TTestResult& aResult );		

		/**
		* Test CTelephony::EstablishDataCall
		*/ 
		TInt TestEstablishDataCallAsync( TTestResult& aResult );		

		/**
		* Test CTelephony::TerminateDataCall
		*/ 
		TInt TestTerminateDataCall( TTestResult& aResult );		

		/**
		* Test CTelephony::ReceiveDataCall
		*/ 
		TInt TestReceiveDataCall( TTestResult& aResult );		

		/**
		* Test CTelephony::ReceiveDataCall
		*/ 
		TInt TestReceiveDataCallAsync( TTestResult& aResult );		

		/**
		* Test CTelephony::CancelEstablishDataCall
		*/ 
		TInt TestCancelEstablishDataCall( TTestResult& aResult );		

		/**
		* Test CTelephony::CancelReceiveDataCall
		*/ 
		TInt TestCancelReceiveDataCall( TTestResult& aResult );		

    private:    // Data
        // Pointer to test (function) to be executed
        TestFunction iMethod;

		// Pointer to test result
		TTestResult* iTestResult;		

        // Pointer to logger
        CStifLogger* iLogger; 

		// Logging output selector (Stif UI output VS. file logging)
		TMessageOption iMessageOption; 
		
		// Counter for STIF UI line number
		TInt iStifUiLineCounter; 		
		
		// Pointer to active scheduler
		CActiveScheduler* iTestScheduler;
		
		// Pointer to test engine
		CIsvTelephonyTestEngine* iTestEngine; 	
		
		// Pointer to test parser
		CIsvTelephonyTestParser* iTestParser; 
		
		// For ISV Telephony call handling tests 
		CTelephony::TCallParamsV1 iCallParams; 		
		CTelephony::TCallId iCallId1; 
		CTelephony::TCallId iCallId2; 
		CTelephony::TCallStatusV1 iCallStatus; 		
		CTelephony::TCallSelectionV1 iCallSelection; 
		CTelephony::TCallInfoV1 iCallInfo; 
		CTelephony::TRemotePartyInfoV1 iRemotePartyInfo; 		
		CTelephony::TCallCapsV1 iCallCaps; 
		
		// Initialised from ini file
		// Telephone number 1
	 	CTelephony::TTelNumber iTelNumber1; 
	 	// Telephone number 2
	 	CTelephony::TTelNumber iTelNumber2; 
		// CLIR setting
		CTelephony::TCallerIdentityRestrict iIdRestrict; 
		// Phone Line
		CTelephony::TPhoneLine iPhoneLine; 
		// DTMF tones
		RBuf iDTMFTones;
		
    };

#endif      // ISVTELEPHONYTEST_H

// End of File