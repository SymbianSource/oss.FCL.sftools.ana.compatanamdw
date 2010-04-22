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
* Description:  BCLogEngineTest test module.
*
*/


/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */

#ifndef BCLOGENGINETEST_H
#define BCLOGENGINETEST_H

// INCLUDES
#include "StifTestModule.h"
#include <StifLogger.h>
#include <LogCli.h>
#include <LogWrap.h>
#include <LogView.h>
#include <LogClientChangeObserver.h>
#include <f32file.h>
#include <e32base.h>

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
#define TEST_MODULE_VERSION_MAJOR 52
#define TEST_MODULE_VERSION_MINOR 9
#define TEST_MODULE_VERSION_BUILD 50

#define KTestEventId1 0x10005394
#define KTestEventId2 0x10005395
#define TEST(aValue, aExpected) ::Check(aValue, aExpected)

// Logging path
_LIT( KBCLogEngineTestLogPath, "\\logs\\testframework\\BCLogEngineTest\\" ); 
// Log file
_LIT( KBCLogEngineTestLogFile, "BCLogEngineTest.txt" ); 

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

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CBCLogEngineTest;
class CActiveLogEngine;
class CMyLogActive;
// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;
// A typedef for function that does the actual testing,
// function is a type 
// TInt CBCLogEngineTest::<NameOfFunction> ( TTestResult& aResult )
typedef TInt (CBCLogEngineTest::* TestFunction)(TTestResult&);

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
*  This a BCLogEngineTest class.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CBCLogEngineTest) : public CTestModuleBase
    {
    public:  // Constructors and destructor


        /**
        * Two-phased constructor.
        */
        static CBCLogEngineTest* NewL();

        /**
        * Destructor.
        */
        virtual ~CBCLogEngineTest();

    public: // New functions

        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
       
    public: // Functions from base classes

        /**
        * From CTestModuleBase InitL is used to initialize the 
        *       BCLogEngineTest. It is called once for every instance of 
        *       TestModuleBCLogEngineTest after its creation.
        * @since ?Series60_version
        * @param aIniFile Initialization file for the test module (optional)
        * @param aFirstTime Flag is true when InitL is executed for first 
        *               created instance of BCLogEngineTest.
        * @return Symbian OS error code
        */
        TInt InitL( TFileName& aIniFile, TBool aFirstTime );

        /**
        * From CTestModuleBase GetTestCasesL is used to inquiry test cases 
        *   from BCLogEngineTest. 
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
        CBCLogEngineTest();

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
        TInt TestNotifyChangeL( TTestResult& aResult );
        
        TInt TestNotifyChangeCancelL( TTestResult& aResult );
        
        TInt TestLogClientL( TTestResult& aResult );
		
 		TInt TestLogBaseL( TTestResult& aResult );
 		
 		TInt TestLogEventL( TTestResult& aResult );
 		
 		TInt TestLogEventTypeL( TTestResult& aResult );
 		
 		TInt TestLogFilterL( TTestResult& aResult );
 		
 		TInt TestLogWrapperL( TTestResult& aResult );
 		
 		TInt TestLogViewRecentL( TTestResult& aResult );
 		
 		TInt TestLogViewEventL( TTestResult& aResult );
 		
 		TInt TestLogFilterListL( TTestResult& aResult );
 		
		TInt TestLogViewDuplicateL( TTestResult& aResult );
 		
 		TInt TestLogActiveL( TTestResult& aResult );

	public:     // Data
		CActiveScheduler* myActiveScheduler;
		
    private:    // Data
        // Pointer to test (function) to be executed
        TestFunction iMethod;

        // Pointer to logger
        CStifLogger* iLog; 
		CActiveScheduler* iActiveScheduler;
		// needed for using CLogClient
        RFs iSession;
        CLogClient* iLogClient; 
        CLogEvent* iLogEvent;
        CLogEventType* iLogType;
        CLogFilter* iLogFilter;
    	CLogWrapper* iLogWrapper;
    	CLogViewRecent* iLogViewRecent;
    	CLogViewEvent* iLogViewEvent;
    	CLogFilterList* iLogFilterList;
    	CLogViewDuplicate* iLogViewDuplicate;
    };

class CActiveLogEngine : public CActive
	{
	public:          
		/**
        * C++ default constructor.
        */
        CActiveLogEngine( TInt aPriority = EPriorityIdle-100 );

        /**
        * Destructor.
        */
        virtual ~CActiveLogEngine();

    public:
        /**
        * Sends asynchronous request to log server to return
        * last dialled number.
        * @since 2.5
        * @param None
        * @return None
        */
        void StartL();
    		
    private:
        /**
        * From CActive. Called when asynchronous request completes.
        * @since 2.5
        * @param None
        * @return None
        */
        void RunL();

        /**
        * From CActive. Cancels asynchronous request.
        * @since 2.5
        * @param None
        * @return None
        */
        void DoCancel();

    private:
	   	TRequestStatus iStoredStatus;
	};

class CMyLogActive : public CLogActive
	{
public:
	CMyLogActive();
	~CMyLogActive();
	
	void StartL();
	
	void Queue(TRequestStatus& aStatus)
		{
		CLogActive::Queue(aStatus);
		}
		
	void Complete(TInt aStatus) 
		{
		CLogActive::Complete(aStatus);
		}
	
private:
	void RunL();
	void DoCancel();
	void DoRunL() {	};
	};	

class CMyLogClient : public CLogBase
	{
	public:
	CMyLogClient();
	~CMyLogClient();
	
	public:
	void LoadResourcesL( RFs& aFs)
		{
		CLogBase::LoadResourcesL( aFs );
		}
		
	inline const CResourceFile *ResourceFile() const
		{
		return CLogBase::ResourceFile();
		}
		
	private:
		void DoRunL();	
	};

class TClientObserverTestReceiver : public MLogClientChangeObserver
	{
public:
	TClientObserverTestReceiver(TBool& aFlag) : iCallCount(0), iFlag(aFlag) { }

public:
	void HandleLogClientChangeEventL(TUid aChangeType, TInt /*aChangeParam1*/, TInt /*aChangeParam2*/, TInt /*aChangeParam3*/)
		{
		++iCallCount;
		iFlag = (aChangeType == KLogClientChangeEventLogCleared);
		}
	inline TInt CallCount() const { return iCallCount; }
	inline void Reset() { iCallCount = 0; iFlag = EFalse; }

private:
	TInt iCallCount;
	TBool& iFlag;
	};

#endif      // BCLOGENGINETEST_H

// End of File