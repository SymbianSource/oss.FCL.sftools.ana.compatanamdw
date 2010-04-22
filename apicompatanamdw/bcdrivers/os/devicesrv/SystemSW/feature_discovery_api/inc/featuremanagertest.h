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
* Description:  Header file for featuremanagertest.
*
*/


#ifndef FEATUREMANAGERTEST_H
#define FEATUREMANAGERTEST_H

// INCLUDES
#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#include "StifTestModule.h"

// CONSTANTS
// None

// MACROS
//#define ?macro ?macro_def
#define TEST_MODULE_VERSION_MAJOR 30
#define TEST_MODULE_VERSION_MINOR 9
#define TEST_MODULE_VERSION_BUILD 40

// DATA TYPES
// None

// FUNCTION PROTOTYPES
// None

// FORWARD DECLARATIONS
class Cfeaturemanagertest;
class CFeatureDiscovery;
class TCaseInfo;

// CLASS DECLARATION


// DESCRIPTION
/**
*  Test class for featuremanager.
*  Checks what features are supported.
*
*/
typedef TInt (Cfeaturemanagertest::* TestFunction)(TTestResult&);    

NONSHARABLE_CLASS(Cfeaturemanagertest) 
        :public CTestModuleBase
    {
    public: // Enumerations
       
    private: // Enumerations
       
    public: // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        static Cfeaturemanagertest* NewL();

        /**
        * Destructor.
        */
        ~Cfeaturemanagertest();

    public: // New functions
       
    public: // Functions from base classes
        
        /**
        * InitL is used to initialize the Test Module. The Test Modules 
        * can use the configure file to read parameters for Test Module 
        * initialization but they can also have their own configure file 
        * or some other routine to initialize themselves.
		*
		* @param TName& aIniFile: in: Filename:
                    Configuration file for the test module
        * @return KErrNone: No error
        */
        TInt InitL( TFileName& aIniFile, TBool aFirstTime );

        /**
        * Test cases are inquired from the Test Module by calling GetTestCasesL. 
        * Test cases are read from the config file specified by aConfigFile. 
        * If the Test Module does not use config files for test case definition 
        * it does not use aConfigFile parameter. Test cases are appended 
        * to CArrayPtrFlat<RTestEngine::TTestCaseInfo> that is a list 
        * consisting of several TTestCaseInfo objects.
        * TTestCaseInfo class defines individual test cases and, if needed, 
        * a test set where the test case belongs to. TTestCaseInfo is 
        * defined in Table 9.
        * The Test Framework will be the owner of the data in the 
        * RPointerArray and it does the memory deallocation.
		*
		* @param TFileName& aConfig Test case file (optional)
                 RPointerArray<RTestEngine::TTestCaseInfo>& aTestCases Array of TestCases 
        * @return KErrNone: No error
        */
        TInt GetTestCasesL( const TFileName& aConfigFile, 
                            RPointerArray<TTestCaseInfo>& aTestCases );

        /**
        * RunTestCaseL is used to run an individual test case specified 
        * by aTestCase. Test cases that can be run may be requested from 
        * Test Module by GetTestCasesL method before calling RunTestCaseL.
        * This method is synchronous and test case result is returned as 
        * reference parameter aResult value. The function shall return 
        * KErrNone if case is succesfully started.
        * If test case is not available (i.e invalid configuration file or
        * or case number), then function shall return the error code (i.e
        * (KErrNotFound)
		*
		* @param  const TInt aCaseNumber    Case number
                  const TFileName& aConfig  Test case file (optional)
                  TTestResult& aResult      Test case result
        * @return System wide error code
        */
        TInt RunTestCaseL( const TInt aCaseNumber, 
                            const TFileName& aConfig,
                            TTestResult& aResult );
       /**
         * Method used to log version of test module
         */
        void SendTestModuleVersion();
 
    protected: // New functions
		/**
        * Returns test value according to given boolean value.
        * If aValue is true, returns KErrNone, else returns KErrGeneral
        *
        * @param  TBool aValue  Value to be tested
        * @return System wide error code 
        */
		TBool test( TBool aValue ) const;
		
    protected: // Functions from base classes
        	
    private:

		
        /**
        * C++ default constructor.
        */
        Cfeaturemanagertest();

        /**
        * By default Symbian OS constructor is private.
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



/******* TEST CASES	**********************************************************************
	
		/**
        * FeatureSupportedStaticTest
        * This test case fetches information about whether features are supported
        * by using the static feature of CFeatureDiscovery::IsFeatureSupportedL.
        * Case returns:
        *       KErrNone if test case passed
        *       KErrNotSupported if either of the queries returns unexpected result   
		*       KErrGeneral if any of the queries leaves  
		*
        * @param  TTestResult& aResult  Test case result
        * @return System wide error code
        */
		TInt FeaturesSupportedStatic( TTestResult& aResult );

		/**
        * FeaturesSupportedNewLTest
        * This test case fetches information about whether features are supported
        * by using an object of CFeatureDiscovery::NewL
        * Case returns:
        *       KErrNone if test case passed
        *       KErrNotSupported if any of the queries returns unexpected result 
        *
        * @param  TTestResult& aResult  Test case result
        * @return System wide error code 
        */
		TInt FeaturesSupportedNewL( TTestResult& aResult );

		/**
        * FeaturesSupportedNewLCTest
        * This test case fetches information about whether features are supported
        * by using an object of CFeatureDiscovery::NewLC
        * Case returns:
        *       KErrNone if test case passed
        *       KErrNotSupported if any of the queries returns unexpected result 
        *
        * @param  TTestResult& aResult  Test case result
        * @return System wide error code 
        */
		TInt FeaturesSupportedNewLC( TTestResult& aResult );


    public: // Data
        
    protected: // Data
        
    private: // Data
		
        // Pointer to test (function) to be executed
        TestFunction iMethod;
        
    public: // Friend classes
        
    protected: // Friend classes
        
    private: // Friend classes
      
    };


// Function pointer related internal definitions

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


#endif // FEATUREMANAGERTEST_H
// End of File
