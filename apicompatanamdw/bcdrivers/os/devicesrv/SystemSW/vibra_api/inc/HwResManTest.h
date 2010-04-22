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
* Description:  HwResManTest test module.
*
*/



#ifndef HWRESMANTEST_H
#define HWRESMANTEST_H

// INCLUDES
#include "StifTestModule.h"
#include <StifLogger.h>

#include "HWRMVibra.h"
#include "TestScheduler.h"
#include <centralrepository.h>
#include "HWRMVibraSDKCRKeys.h"

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
#define TEST_MODULE_VERSION_MAJOR 30
#define TEST_MODULE_VERSION_MINOR 9
#define TEST_MODULE_VERSION_BUILD 40
// Logging path
_LIT( KHwResManTestLogPath, "c:\\logs\\testframework\\HwResManTest\\" ); 
// Log file
_LIT( KHwResManTestLogFile, "HwResManTest.txt" ); 

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
class CHwResManTest;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;
// A typedef for function that does the actual testing,
// function is a type 
// TInt CHwResManTest::<NameOfFunction> ( TTestResult& aResult )
typedef TInt (CHwResManTest::* TestFunction)(TTestResult&);    

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
*  This a HwResManTest class.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CHwResManTest) : public CTestModuleBase, MHWRMVibraObserver
    {
    public:  // Constructors and destructor
        
        
        /**
        * Two-phased constructor.
        */
        static CHwResManTest* NewL();
        
        /**
        * Destructor.
        */
        virtual ~CHwResManTest();
        
    public: // New functions
        
        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );

		void VibraModeChanged(CHWRMVibra::TVibraModeState aStatus);
		void VibraStatusChanged(CHWRMVibra::TVibraStatus aStatus);
		void InitTestVariables();

    public: // Functions from base classes

        /**
        * From CTestModuleBase InitL is used to initialize the 
        *       HwResManTest. It is called once for every instance of 
        *       TestModuleHwResManTest after its creation.
        * @since ?Series60_version
        * @param aIniFile Initialization file for the test module (optional)
        * @param aFirstTime Flag is true when InitL is executed for first 
        *               created instance of HwResManTest.
        * @return Symbian OS error code
        */
        TInt InitL( TFileName& aIniFile, TBool aFirstTime );

        /**
        * From CTestModuleBase GetTestCasesL is used to inquiry test cases 
        *   from HwResManTest. 
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
        
		  
    protected:  // New functions
        
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
        CHwResManTest();

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
        * Actual Hardcoded test case functions are listed below.
        */
        
        /**
        * Printing test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt PrintTest( TTestResult& aResult );

        /**
        * Printing loop test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt LoopTest( TTestResult& aResult );
		
		TBool statusUpdated;
		CHWRMVibra::TVibraModeState myMode;
		TBool modeUpdated;
		CHWRMVibra::TVibraStatus myStatus;
		
		TInt RunTestVibra( CHWRMVibra* iVibra, TInt howLong, TInt whatIntensity);
		TInt RunTestVibra( CHWRMVibra* iVibra, TInt howLong);
		TInt StopTestVibra( CHWRMVibra* iVibra);
		
		TInt Check_status( TTestResult& aResult );
		TInt StartVibra_5s( TTestResult& aResult );
		TInt StartVibra_infinite( TTestResult& aResult );
		TInt StartVibra_KVibraCtrlMaxTime( TTestResult& aResult );
		TInt StartVibra_loop( TTestResult& aResult );
		TInt StartVibra_loop2( TTestResult& aResult );		
		TInt StartVibra_loop3( TTestResult& aResult );				
		TInt StartVibra_notallowed( TTestResult& aResult );
		TInt unsupported_Vibra_Intensity(TTestResult& aResult);
		TInt unsupported_Vibra_Duration(TTestResult& aResult);
			
    public:     // Data
        // ?one_line_short_description_of_data
        //?data_declaration;
        
        CActiveScheduler* myActiveScheduler;
        CRepository* iSession;
    
    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        // Pointer to test (function) to be executed
        TestFunction iMethod;

	// Pointer to logger
	CStifLogger * iLog;  
		
        // ?one_line_short_description_of_data
        //?data_declaration;
         
        // Reserved pointer for future extension
        //TAny* iReserved;
        
    public:     // Friend classes
        //?friend_class_declaration;
    protected:  // Friend classes
        //?friend_class_declaration;
    private:    // Friend classes
        //?friend_class_declaration;

    };

#endif      // HWRESMANTEST_H
            
// End of File