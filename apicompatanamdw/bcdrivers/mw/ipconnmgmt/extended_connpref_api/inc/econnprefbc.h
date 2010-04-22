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
* Description:
* STIF hardcoded module declaration.
*
*/


#ifndef ECONNPREFBC_H
#define ECONNPREFBC_H

#include <StifLogger.h>
#include <StifTestModule.h>

_LIT( KLogEmptyLine, "" );

#define TEST_MODULE_VERSION_MAJOR 52
#define TEST_MODULE_VERSION_MINOR 9
#define TEST_MODULE_VERSION_BUILD 50

// Logging path
_LIT( KEConnPrefBcLogPath, "\\logs\\testframework\\econnprefbc\\" );
// Log file
_LIT( KEConnPrefBcLogFile, "econnprefbc.txt" );
_LIT( KEConnPrefBcLogFileWithTitle, "econnprefbc_[%S].txt" );

#define GETPTR &
#define ENTRY(str,func) {_S(str), GETPTR func,0,0,0}
#define FUNCENTRY(func) {_S(#func), GETPTR func,0,0,0}


class CEConnPrefBc;

// A typedef for function that does the actual testing, function is a type.
typedef TInt (CEConnPrefBc::* TestFunction)(TTestResult&);


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
* The CEConnPrefBc class.
*/
NONSHARABLE_CLASS( CEConnPrefBc ) : public CTestModuleBase
    {
public: // Constructors and destructor
    /**
     * Two-phased constructor.
     */
    static CEConnPrefBc* NewL();

    /**
     * Destructor.
     */
    virtual ~CEConnPrefBc();

public: // Functions from base classes
    /**
     * From CTestModuleBase InitL is used to initialize the CEConnPrefBc. It is
     * called once for every instance of TestModuleEConnPrefBc after its creation.
     * @param aIniFile Initialization file for the test module (optional)
     * @param aFirstTime Flag is true when InitL is executed for first created
     * instance of EConnPrefBc.
     * @return Symbian OS error code
     */
    TInt InitL( TFileName& aIniFile, TBool aFirstTime );

    /**
     * From CTestModuleBase GetTestCasesL is used to inquire test cases from
     * EConnPrefBc.
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
    CEConnPrefBc();

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


    TInt TEcpbcConstuction( TTestResult& aResult );
    TInt TEcpbcSnapPurpose( TTestResult& aResult );
    TInt TEcpbcSnapId( TTestResult& aResult );
    TInt TEcpbcIapId( TTestResult& aResult );
    TInt TEcpbcBearerSet( TTestResult& aResult );
    TInt TEcpbcNoteBehaviour( TTestResult& aResult );
    TInt TEcpbcDisconnectDialog( TTestResult& aResult );
    TInt TEcpbcConnSelectionDialog( TTestResult& aResult );
    TInt TEcpbcForcedRoaming( TTestResult& aResult );

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

#endif // ECONNPREFBC_H

// End of file
