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
* Description:  vibractrltest test module.
*
*/

/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */


#ifndef VIBRACTRLTEST_H
#define VIBRACTRLTEST_H

// INCLUDES
#include "StifTestModule.h"
#include "Vibrawrapper.h"
#include <StifLogger.h>

// For handling vibra mode in profiles.
//#include <TProfileToneSettings.h>

// CONSTANTS

// MACROS
//#define ?macro ?macro_def
#define TEST_MODULE_VERSION_MAJOR 30
#define TEST_MODULE_VERSION_MINOR 9
#define TEST_MODULE_VERSION_BUILD 40

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class Cvibractrltest;
class TCaseInfo;


// Logging path
_LIT( KBCVibraCtrlPath, "\\logs\\testframework\\BCibraCtrlTest\\" ); 
// Log file
_LIT( KBCibraCtrlTestLogFile, "BCibraCtrlTest.txt" ); 

// CLASS DECLARATION

/**
*  This a vibractrltest class.
*
*  @lib ?library
*  @since ?Series60_version
*/
typedef TInt (Cvibractrltest::* TestFunction)(TTestResult&);

NONSHARABLE_CLASS(Cvibractrltest) : public CTestModuleBase
{
public:  // Constructors and destructor
        
        
	/**
    * Two-phased constructor.
    */
    static Cvibractrltest* NewL();
      
    /**
    * Destructor.
    */
    virtual ~Cvibractrltest();
        
public: // New functions
       

public: // Functions from base classes

	/**
    * From CTestModuleBase InitL is used to initialize the vibractrltest. 
    *       It is called once for every instance of vibractrltest after
    *       its creation.
    * @since ?Series60_version
    * @param aIniFile Initialization file for the test module (optional)
    * @param aFirstTime Flag is true when InitL is executed for first 
    *               created instance of vibractrltest.
    * @return Symbian OS error code
    */
    TInt InitL( TFileName& aIniFile, TBool aFirstTime );

    /**
    * From CTestModuleBase GetTestCasesL is used to inquiry test cases 
    *   from vibractrltest. 
    * @since ?Series60_version
    * @param aTestCaseFile Test case file (optional)
    * @param aTestCases  Array of TestCases returned to test framework
    * @return Symbian OS error code
    */
    TInt GetTestCasesL( const TFileName& aTestCaseFile, 
                            RPointerArray<TTestCaseInfo>& aTestCases );
    
    /**
    * From CTestModuleBase RunTestCaseL is used to run an individual 
    * test case. 
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


protected:  // Functions from base classes


private:

    /**
    * C++ default constructor.
    */
    Cvibractrltest();

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

	/**
    * This function contains an array of all available test cases 
	* i.e pair of case name and test function. If case specified by parameter
	* aCaseNumber is found from array, then that item is returned.
	*
	* The reason for this rather complicated function is to specify all the
	* test cases only in one place. It is not necessary to understand how
	* function pointers to class member functions works when adding new test
	* cases. See function body for instructions how to add new test case.
    * 
    * @param  const TInt aCaseNumber :in:      Test case number
    * @return const TCaseInfo Struct containing case name & function
    */
	const TCaseInfo Case ( const TInt aCaseNumber ) const;

	/**
    * Creates vibra with notify-option and starts and stops it. 
	* Test passes when both starting and stopping are notified.
    * 
    * @param  TTestResult& aResult: out: Test case result
    * @return KErrNone: Test case implemented
	*         KErrGeneral: Test case not implemented
    */
	TInt CheckRequestStatus( TTestResult& aResult );

	/**
    * Creates vibra without notify-option and starts and stops it. 
	* Test passes whenno notifies are received.
    * 
    * @param  TTestResult& aResult: out: Test case result
    * @return KErrNone: Test case implemented
	*         KErrGeneral: Test case not implemented
    */
	TInt CheckRequestStatusWithNoNotif( TTestResult& aResult );
			
	/**
    * Runs vibra for 10 ms and stops it.
	* Test passes when starting and stopping are successfull.
    * 
    * @param  TTestResult& aResult: out: Test case result
    * @return KErrNone: Test case implemented
	*         KErrGeneral: Test case not implemented
    */
	TInt RunVibra10Ms(TTestResult& aResult);

	/**
    * Runs vibra for 1 second without stopping.
	* Vibra shoudl stop automatically after set time.
	* Test passes when starting and stopping are successfull.
    * 
    * @param  TTestResult& aResult: out: Test case result
    * @return KErrNone: Test case implemented
	*         KErrGeneral: Test case not implemented
    */
	TInt RunVibra1Second(TTestResult& aResult);

	/**
    * Vibra is set to run indefinetly.
	* After running scheduler for 1 second it is stopped.
	* Test passes when starting and stopping are successfull.
    * 
    * @param  TTestResult& aResult: out: Test case result
    * @return KErrNone: Test case implemented
	*         KErrGeneral: Test case not implemented
    */
	TInt RunVibraWithoutDuration1Second(TTestResult& aResult);

	/**
    * Vibra is run 2 times for 10 ms and 2 times for 100 ms.
	* After last time vibra is stopped.
	* Test passes when starting and stopping are successfull.
    * 
    * @param  TTestResult& aResult: out: Test case result
    * @return KErrNone: Test case implemented
	*         KErrGeneral: Test case not implemented
    */
	TInt RunVibraSeveralTimes(TTestResult& aResult);

	/**
    * Vibra set to run for 1 second and it is deleted after 100 ms.
	* Test passes when starting is successfull.
    * 
    * @param  TTestResult& aResult: out: Test case result
    * @return KErrNone: Test case implemented
	*         KErrGeneral: Test case not implemented
    */
	//TInt DeleteVibraWhenRunning(TTestResult& aResult);

	/**
    * Gets current vibra mode.
	* Test passes when vibra mode is on.
    * 
    * @param  TTestResult& aResult: out: Test case result
    * @return KErrNone: Test case implemented
	*         KErrGeneral: Test case not implemented
    */
	TInt GetVibraMode(TTestResult& aResult);

	/**
    * Vibra is set to run with a negative value.
	* Test passes when starting is successfull.
    * 
    * @param  TTestResult& aResult: out: Test case result
    * @return KErrNone: Test case implemented
	*         KErrGeneral: Test case not implemented
    */
	TInt RunVibraWithNegativeValue(TTestResult& aResult);

	/**
    * Vibra set to run indefinetly.
	* After 15 seconds it is stopped.
	* Test passes when starting and stopping are successfull.
    * 
    * @param  TTestResult& aResult: out: Test case result
    * @return KErrNone: Test case implemented
	*         KErrGeneral: Test case not implemented
    */
	TInt RunVibraWithoutDuration15Seconds(TTestResult& aResult);

	/**
    * Vibra set to run for 30 seconds.
	* After 15 seconds it is stopped.
	* Test passes when starting and stopping are successfull.
    * 
    * @param  TTestResult& aResult: out: Test case result
    * @return KErrNone: Test case implemented
	*         KErrGeneral: Test case not implemented
    */
	TInt StopVibraWhileRunning(TTestResult& aResult);

	/**
    * Sets the vibra on with duration and intensity.
	* Test passes when starting and stopping are successfull.
    * 
    * @param  TTestResult& aResult: out: Test case result
    * @return KErrNone: Test case implemented
	*         KErrGeneral: Test case not implemented
    */
	
	//Just start the vibra dur 0, verify it's on. Check shutdown after 15s
	TInt StartVibraIndef(TTestResult& aResult);
	//Just start the vibra dur 0 int 70, verify it's on. Check shutdown after 15s
	TInt StartVibraIndefI(TTestResult& aResult);

	//Just start the vibra dur 5, verify it's on. Check shutdown after 5s
	TInt StartVibra5s(TTestResult& aResult);
	//Just start the vibra dur 5 int 70 verify it's on. Check shutdown after 5s
	TInt StartVibra5sI(TTestResult& aResult);
	//Just start the vibra dur 5 int -70 verify it's on. Check shutdown after 5s
	TInt StartVibra5sNI(TTestResult& aResult);

	//Just start the vibra dur 5 int 110 verify it's on. Check shutdown after 5s
	TInt StartVibra5sOI(TTestResult& aResult);
	//Just start the vibra dur 5 int -110 verify it's on. Check shutdown after 5s
	TInt StartVibra5sNOI(TTestResult& aResult);

	//Just start the vibra dur 5 int 0 verify it's off.
	TInt StartVibra5sZI(TTestResult& aResult);

	//Just start the vibra dur 5 verify it's on. Stop vibra and verify it's off.
	TInt StopVibra(TTestResult& aResult);
	//Just start the vibra dur 5 int 70 verify it's on. Stop vibra and verify it's off.
	TInt StopVibraI(TTestResult& aResult);

	//Just start the vibra dur 10. verify it's on restart dur 1. verify it's on. verify it's off after 1s
	TInt ReStartVibra(TTestResult& aResult);
	TInt ReStartVibraI(TTestResult& aResult);
	TInt ReStartVibraIonL(TTestResult& aResult);
	TInt ReStartVibraIonF(TTestResult& aResult);

	TInt ReStopVibra(TTestResult& aResult);
	TInt ReStopVibra2(TTestResult& aResult);

	TInt VibraSettingOn(TTestResult& aResult);
	TInt VibraSettingOff(TTestResult& aResult);

	TInt PendingOn(TTestResult& aResult);
	TInt PendingOff(TTestResult& aResult);

//	TInt DeleteVibraWhenRunning(TTestResult& aResult);

	/**
    * Prints information about the received request status.
    * 
    * @param  CVibraControl::TVibraRequestStatus Status: in: received status
	*		  TTestResult& aResult: out: Test case result
    * @return none
    */
	void CheckRequest(CVibraControl::TVibraRequestStatus Status, TTestResult& aResult);
	TInt LogStatus(CVibraControl::TVibraRequestStatus Status, CVibraControl::TVibraRequestStatus okStatus);
public:     // Data

protected:  // Data

private:    // Data

	//	To get/set information about the Vibra settings in the device
    CRepository*            iRepository;

	// file containing loggin information
	CStifLogger* iLogger ;

	// Pointer to test (function) to be executed
    TestFunction iMethod;
         
	// Variable to store TRAP result
	TInt error;
public:     // Friend classes
      
protected:  // Friend classes
        
private:    // Friend classes
        

};

// Hack around known GCC bug.
#ifndef __GCC32__
    #define GETPTR
#else
    #define GETPTR &
#endif 

// An internal structure containing a test case name and
// the pointer to function doing the test
class TCaseInfoInternal
    {
    public:
		// Pointer to test name
        const TText* iCaseName;
		// Pointer to test (function) to be executed
        TestFunction iMethod;
    };

// An internal structure containing a test case name and
// the pointer to function doing the test
class TCaseInfo
{
public:
	//Test case name
    TPtrC iCaseName;  

	// Pointer to test (function) to be executed
    TestFunction iMethod;

    TCaseInfo( const TText* a ) : iCaseName( (TText*) a )
        {        
        };
};

#endif      // VIBRACTRLTEST_H
            
// End of File
