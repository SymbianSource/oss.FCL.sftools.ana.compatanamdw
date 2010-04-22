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
* Description:  CenRepNotifyHandlerTest test module.
*
*/



#ifndef CENREPNOTIFYHANDLERTEST_H
#define CENREPNOTIFYHANDLERTEST_H

// INCLUDES

#include "StifTestModule.h"
#include <StifLogger.h>
#include <CentralRepository.h>
#include <cenrepnotifyhandler.h>
#include "TestScheduler.h"

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
#define TEST_MODULE_VERSION_MAJOR 31
#define TEST_MODULE_VERSION_MINOR 9
#define TEST_MODULE_VERSION_BUILD 40

// Logging path
_LIT( KCenRepNotifyHandlerTestLogPath, "\\logs\\testframework\\CenRepNotifyHandlerTest\\" ); 
// Log file
_LIT( KCenRepNotifyHandlerTestLogFile, "CenRepNotifyHandlerTest.txt" ); 

// Function pointer related internal definitions
// Rounding known bug in GCC
#ifndef __GCC32__
#define GETPTR
#else
#define GETPTR &
#endif  
#define ENTRY(str,func) {_S(str), GETPTR func}
#define FUNCENTRY(func) {_S(#func), GETPTR func}

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CCenRepNotifyHandlerTest;
//class CTestScheduler;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;
// A typedef for function that does the actual testing,
// function is a type 
// TInt CCenRepNotifyHandlerTest::<NameOfFunction> ( TTestResult& aResult )
typedef TInt (CCenRepNotifyHandlerTest::* TestFunction)(TTestResult&);    

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
        const TText* iCaseName;
        TestFunction iMethod;
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

    TCaseInfo( const TText* a ) : iCaseName( (TText*) a )
        {        
        };

    };



// CLASS DECLARATION

/**
*  This a CenRepNotifyHandlerTest class.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CCenRepNotifyHandlerTest) : public CTestModuleBase, MCenRepNotifyHandlerCallback 
    {
    
    public:  // Constructors and destructor
        
        
        /**
        * Two-phased constructor.
        */
        static CCenRepNotifyHandlerTest* NewL();
        
        /**
        * Destructor.
        */
        virtual ~CCenRepNotifyHandlerTest();
        
    public: // New functions
        
        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );
        
        void HandleNotifyInt(TUint32 aId, TInt aNewValue);
        void HandleNotifyReal(TUint32 aId, TReal aNewValue);
        void HandleNotifyString(TUint32 aId, const TDesC16& aNewValue);
        void HandleNotifyBinary(TUint32 aId, const TDesC8& aNewValue);
        void HandleNotifyGeneric(TUint32 aId);
        void HandleNotifyError(TUint32 aId, TInt error, CCenRepNotifyHandler* aHandler);

    public: // Functions from base classes

        /**
        * From CTestModuleBase InitL is used to initialize the 
        *       CenRepNotifyHandlerTest. It is called once for every instance of 
        *       TestModuleCenRepNotifyHandlerTest after its creation.
        * @since ?Series60_version
        * @param aIniFile Initialization file for the test module (optional)
        * @param aFirstTime Flag is true when InitL is executed for first 
        *               created instance of CenRepNotifyHandlerTest.
        * @return Symbian OS error code
        */
        TInt InitL( TFileName& aIniFile, TBool aFirstTime );

        /**
        * From CTestModuleBase GetTestCasesL is used to inquiry test cases 
        *   from CenRepNotifyHandlerTest. 
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
         * Method used to log version of test module
         */
        void SendTestModuleVersion();

        
        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );

    protected:  // Functions from base classes
        
        /**
        * From ?base_class ?member_description
        */
        //?type ?member_function();

    private:

        /**
        * C++ default constructor.
        */
        CCenRepNotifyHandlerTest();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        // Prohibit copy constructor if not deriving from CBase.
        // ?classname( const ?classname& );
        // Prohibit assigment operator if not deriving from CBase.
        // ?classname& operator=( const ?classname& );
        
        /**
        * Function returning test case name and pointer to test case function.
        * @since ?Series60_version
        * @param aCaseNumber test case number
        * @return TCaseInfo 
        */
        const TCaseInfo Case ( const TInt aCaseNumber ) const;
        
        
        /**
        * Function returning test case name and pointer to test case function.
        * @since ?Series60_version
        * @param aCaseNumber test case number
        * @return TCaseInfo 
        */
        void InitializeNotifyData();
        
        /**
        * Actual Hardcoded test case functions are listed below.
        */
        
        /**
        * Printing test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ListeningToSingleIntKey( TTestResult& aResult );
 
        /**
        * Printing loop test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ListeningToSingleRealKey( TTestResult& aResult );

         /**
        * Printing loop test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ListeningToSingleStringKey( TTestResult& aResult );

        /**
        * Printing loop test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ListeningToSingleBinaryKey( TTestResult& aResult );

        /**
        * Printing loop test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */

		TInt ListeningToAllKeys (TTestResult& aResult);
        
        /**
        * Printing loop test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
		TInt NoMultipleNotifiesOnSameValueChange (TTestResult& aResult);
		        
        /**
        * Printing loop test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
		TInt NoNotificationAfterStopListening( TTestResult& aResult );
        
        /**
        * Printing loop test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
	
		TInt NotificationAfterWholeRepositoryReset ( TTestResult& aResult );
		
		/**
        * Printing loop test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
	
		TInt NotificationAfterRepositoryKeyReset ( TTestResult& aResult );
		
		/**
        * Printing loop test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
		TInt ListeningForTwoNotificationHandler (TTestResult& aResult );
		
    public:     // Data
        // ?one_line_short_description_of_data
        //?data_declaration;
        
    
    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        // Pointer to test (function) to be executed
        TestFunction iMethod;

		// Pointer to logger
		CStifLogger * iLog;  
		
		//Pointer to cenrep notify handler
		CCenRepNotifyHandler* iNotifyHandler;
		
		//Pointer to cenrep notify handler (needed in test case ListeningForTwoNotificationHandler)
		CCenRepNotifyHandler* iSecondHandler;
		
		//Pointer to central repository session
		CRepository* iSession;
		CActiveScheduler* myScheduler;
		
		TInt iNotifyInt;
		TReal iNotifyReal;
		TBuf16<NCentralRepositoryConstants::KMaxUnicodeStringLength> iNotifyString;
		TBuf8<NCentralRepositoryConstants::KMaxBinaryLength> iNotifyBinary;
		TBuf8<NCentralRepositoryConstants::KMaxBinaryLength> iSecondBinary;
		TUint32 iNotificationId;
		TUint32 iSecondNotificationId;
		
		
		TInt iNotifyError;
		
        // Reserved pointer for future extension
        //TAny* iReserved;
        
    public:     // Friend classes
        //?friend_class_declaration;
    protected:  // Friend classes
        //?friend_class_declaration;
    private:    // Friend classes
        //?friend_class_declaration;

    };

#endif      // CENREPNOTIFYHANDLERTEST_H
            
// End of File