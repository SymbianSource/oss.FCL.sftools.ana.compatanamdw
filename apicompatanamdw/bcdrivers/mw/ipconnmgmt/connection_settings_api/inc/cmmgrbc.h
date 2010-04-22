/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: STIF hardcoded module declaration
*
*/

#ifndef CMMGRBC_H
#define CMMGRBC_H

// Configuration file to set build environment settings
#include "cmmgrbc.cfg"

#include <StifLogger.h>
#include <StifTestModule.h>


_LIT( KLogEmptyLine, "" );

#define TEST_MODULE_VERSION_MAJOR 1
#define TEST_MODULE_VERSION_MINOR 0
#define TEST_MODULE_VERSION_BUILD 0

// Logging path
_LIT( KCmmgrBcLogPath, "\\logs\\testframework\\cmmgrbc\\" );
// Log file
_LIT( KCmmgrBcLogFile, "cmmgrbc.txt" );
_LIT( KCmmgrBcLogFileWithTitle, "cmmgrbc_[%S].txt" );

#define GETPTR &
#define ENTRY(str,func) {_S(str), GETPTR func,0,0,0}
#define FUNCENTRY(func) {_S(#func), GETPTR func,0,0,0}

// If enabled, permits the use of small delays after commsdat writes. These may
// be needed to avoid possible commsdat locks caused by other (poorly designed)
// processes rushing to read commsdat after detecting a change.
#define CMMGRBC_ENABLE_DELAYS

const TInt KCmmgrbcMicroSecondsInMilliSecond = 1000;
const TInt KCmmgrbcDefaultDelayInMs = 500;
const TInt KCmmgrbcQuarterSecondInMs = 250;
const TInt KCmmgrbcHalfSecondInMs = 500;

class CCmmgrBc;

// A typedef for function that does the actual testing, function is a type.
typedef TInt (CCmmgrBc::* TestFunction)(TTestResult&);


/**
* An internal structure containing a test case name and the pointer to function
* doing the test.
*/
class TCaseInfoInternal
    {
public:
    const TText* iCaseName;
    TestFunction iMethod;
    TBool iIsOOMTest;
    TInt iFirstMemoryAllocation;
    TInt iLastMemoryAllocation;
    };


/**
* A structure containing a test case name and the pointer to function doing the
* test.
*/
class TCaseInfo
    {
public:
    TPtrC iCaseName;
    TestFunction iMethod;
    TBool iIsOOMTest;
    TInt iFirstMemoryAllocation;
    TInt iLastMemoryAllocation;

    TCaseInfo( const TText* a ) : iCaseName( (TText*)a )
        {
        };
    };


/**
* The CmmgrBc class.
*/
NONSHARABLE_CLASS( CCmmgrBc ) : public CTestModuleBase
    {
public: // Constructors and destructor
    /**
     * Two-phased constructor.
     */
    static CCmmgrBc* NewL();

    /**
     * Destructor.
     */
    virtual ~CCmmgrBc();

public: // Functions from base classes
    /**
     * From CTestModuleBase InitL is used to initialize the ConnMonBc. It is
     * called once for every instance of TestModuleConnMonBc after its creation.
     * @param aIniFile Initialization file for the test module (optional)
     * @param aFirstTime Flag is true when InitL is executed for first created
     * instance of ConnMonBc.
     * @return Symbian OS error code
     */
    TInt InitL( TFileName& aIniFile, TBool aFirstTime );

    /**
     * From CTestModuleBase GetTestCasesL is used to inquiry test cases from
     * ConnMonBc.
     * @param aTestCaseFile Test case file (optional)
     * @param aTestCases Array of TestCases returned to test framework
     * @return Symbian OS error code
     */
    TInt GetTestCasesL(
            const TFileName& aTestCaseFile,
            RPointerArray<TTestCaseInfo>& aTestCases );

    /**
     * From CTestModuleBase RunTestCaseL is used to run an individual test case.
     * @param aCaseNumber Test case number
     * @param aTestCaseFile Test case file (optional)
     * @param aResult Test case result returned to test framework (PASS/FAIL)
     * @return Symbian OS error code (test case execution error, which is not
     * reported in aResult parameter as test case failure).
     */
    TInt RunTestCaseL(
            const TInt aCaseNumber,
            const TFileName& aTestCaseFile,
            TTestResult& aResult );

    /**
     * From CTestModuleBase; OOMTestQueryL is used to specify is particular
     * test case going to be executed using OOM conditions.
     * @param aTestCaseFile Test case file (optional)
     * @param aCaseNumber Test case number (optional)
     * @param aFailureType OOM failure type (optional)
     * @param aFirstMemFailure The first heap memory allocation failure value (optional)
     * @param aLastMemFailure The last heap memory allocation failure value (optional)
     * @return TBool
     */
    virtual TBool OOMTestQueryL(
            const TFileName& /*aTestCaseFile*/,
            const TInt /*aCaseNumber*/,
            TOOMFailureType& aFailureType,
            TInt& /*aFirstMemFailure*/,
            TInt& /*aLastMemFailure*/ );

    /**
     * From CTestModuleBase; OOMTestInitializeL may be used to initialize OOM
     * test environment.
     * @param aTestCaseFile Test case file (optional)
     * @param aCaseNumber Test case number (optional)
     * @return None
     */
    virtual void OOMTestInitializeL(
            const TFileName& /*aTestCaseFile*/,
            const TInt /*aCaseNumber*/ );

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
    virtual void OOMHandleWarningL(
            const TFileName& /*aTestCaseFile*/,
            const TInt /*aCaseNumber*/,
            TInt& /*aFailNextValue*/ );

    /**
     * From CTestModuleBase; OOMTestFinalizeL may be used to finalize OOM test
     * environment.
     * @param aTestCaseFile Test case file (optional)
     * @param aCaseNumber Test case number (optional)
     * @return None
     */
    virtual void OOMTestFinalizeL(
            const TFileName& /*aTestCaseFile*/,
            const TInt /*aCaseNumber*/ );

    /**
     * Method used to log version of test module.
     */
    void SendTestModuleVersion();

private:
    /**
     * C++ default constructor.
     */
    CCmmgrBc();

    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();

    /**
     * Function returning test case name and pointer to test case function.
     * @param aCaseNumber test case number
     * @return TCaseInfo
     */
    const TCaseInfo Case( const TInt aCaseNumber ) const;

    /**
     * Helper method to set test case results according to the number of errors
     * during test case execution.
     * @param aResult Test case result (PASS/FAIL).
     * @param aErrorCount The number of errors encountered during test case
     * execution.
     * @return KErrNone to be passed forward as testcase execution result (not
     * testcase pass/fail result).
     */
    TInt SetTestCaseResult( TTestResult& aResult, const TInt aErrorCount );

    void MyDelay( const TInt aDelay = KCmmgrbcDefaultDelayInMs );

    TInt TCmManagerConstructionL( TTestResult& aResult );
    TInt TCmManagerCreateTablesAndOpenL( TTestResult& aResult );
    TInt TCmManagerBearerPriorityArrayL( TTestResult& aResult );
    TInt TCmManagerDefConnSettingsL( TTestResult& aResult );
#ifdef CMMGRBC_S60_092_SUPPORT
    TInt TCmManagerGenConnSettingsL( TTestResult& aResult );
#endif // CMMGRBC_S60_092_SUPPORT
    TInt TCmManagerEasyWlanIdL( TTestResult& aResult );
    TInt TCmManagerGetBearerInfoL( TTestResult& aResult );
    TInt TCmManagerGetConnMethodInfoL( TTestResult& aResult );
    TInt TCmManagerAllDestinationsL( TTestResult& aResult );
    TInt TCmManagerAllConnMethodsL( TTestResult& aResult );
    TInt TCmManagerSupportedBearersL( TTestResult& aResult );
    TInt TCmManagerCreateAndOpenDestinationsL( TTestResult& aResult );
    TInt TCmManagerCreateAndOpenConnMethodsL( TTestResult& aResult );
    TInt TCmManagerCopyAndRemoveAllConnMethodL( TTestResult& aResult );
    TInt TCmManagerMoveAndRemoveConnMethodL( TTestResult& aResult );
#ifndef CMMGRBC_S60_101_SUPPORT
    TInt TCmManagerUncategorizedIconL( TTestResult& aResult );
#endif

    // --------

    TInt TDestConstructionL( TTestResult& aResult );
    TInt TDestCopyConstructionL( TTestResult& aResult );
    TInt TDestBasicAttributesL( TTestResult& aResult );
    TInt TDestSetBasicAttributesL( TTestResult& aResult );
    TInt TDestCompareL( TTestResult& aResult );
    TInt TDestCreateAndOpenConnMethodsL( TTestResult& aResult );
    TInt TDestPriorityL( TTestResult& aResult );
    TInt TDestAddRemoveConnMethodsL( TTestResult& aResult );
#ifndef CMMGRBC_S60_101_SUPPORT
    TInt TDestIconL( TTestResult& aResult );
#endif
    // Temporary testcase for DeleteLD bug investigation
    TInt TDestTemp01L( TTestResult& aResult );

    // --------

    TInt TConnMethodConstructionL( TTestResult& aResult );
    TInt TConnMethodCopyConstructionL( TTestResult& aResult );
    TInt TConnMethodSetAttributesL( TTestResult& aResult );
    TInt TConnMethodGetAttributesL( TTestResult& aResult );
    TInt TConnMethodCompareL( TTestResult& aResult );
    TInt TConnMethodAsEmbeddedDestinationL( TTestResult& aResult );

private: // Data
    // Pointer to test (function) to be executed
    TestFunction iMethod;

    // Pointer to logger
    CStifLogger* iLog;

    // Normal logger
    CStifLogger* iStdLog;

    // Test case logger
    CStifLogger* iTCLog;

    // Flag saying if test case title should be added to log file name
    TBool iAddTestCaseTitleToLogName;

    // Flag saying if version of test module was already sent
    TBool iVersionLogged;
    };

#endif // CMMGRBC_H

// End of file
