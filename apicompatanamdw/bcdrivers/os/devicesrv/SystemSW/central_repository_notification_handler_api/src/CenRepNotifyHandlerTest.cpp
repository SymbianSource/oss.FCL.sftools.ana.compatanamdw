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
* Description:  CenRepNotifyHandlerTest class member functions
*
*/



// INCLUDE FILES
#include <Stiftestinterface.h>
#include "CenRepNotifyHandlerTest.h"
#include "CenRepNotifyHandlerTestKeys.h"



// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::CCenRepNotifyHandlerTest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CCenRepNotifyHandlerTest::CCenRepNotifyHandlerTest()
    {
	
	myScheduler = new CActiveScheduler;
	CActiveScheduler::Install(myScheduler);

    }

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CCenRepNotifyHandlerTest::ConstructL()
    {
    iLog = CStifLogger::NewL( KCenRepNotifyHandlerTestLogPath, 
                          KCenRepNotifyHandlerTestLogFile);
                          
	                      
    }
//-----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CCenRepNotifyHandlerTest::SendTestModuleVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_MODULE_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_MODULE_VERSION_MINOR;
	moduleVersion.iBuild = TEST_MODULE_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("CenRepNotifyHandlerTest.dll");
	

	TBool newVersionOfMethod = ETrue;
	CTestModuleIf &test=TestModuleIf();
	test.SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
	test.SetBehavior(CTestModuleIf::ETestLeaksHandles);
	}

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CCenRepNotifyHandlerTest* CCenRepNotifyHandlerTest::NewL()
    {
    CCenRepNotifyHandlerTest* self = new (ELeave) CCenRepNotifyHandlerTest;
    
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    
    }

// Destructor
CCenRepNotifyHandlerTest::~CCenRepNotifyHandlerTest()
    { 
     
    if (iLog) delete iLog;


    if(myScheduler) 
    	{
    		CActiveScheduler::Install(NULL);
    		delete myScheduler;	
    	}
    	
      
    }

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::InitL
// InitL is used to initialize the Test Module.
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::InitL( 
    TFileName& /*aIniFile*/, 
    TBool /*aFirstTime*/ )
    {
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::GetTestCasesL
// GetTestCases is used to inquire test cases from the Test Module. Test
// cases are stored to array of test cases. The Test Framework will be 
// the owner of the data in the RPointerArray after GetTestCases return
// and it does the memory deallocation. 
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::GetTestCasesL( 
    const TFileName& /*aConfig*/, 
    RPointerArray<TTestCaseInfo>& aTestCases )
    {
    
    // Loop through all test cases and create new
    // TTestCaseInfo items and append items to aTestCase array    
    for( TInt i = 0; Case(i).iMethod != NULL; i++ )
        {
 
	    // Allocate new TTestCaseInfo from heap for a testcase definition.
        TTestCaseInfo* newCase = new( ELeave ) TTestCaseInfo();
    
	    // PushL TTestCaseInfo to CleanupStack.    
        CleanupStack::PushL( newCase );

	    // Set number for the testcase.
	    // When the testcase is run, this comes as a parameter to RunTestCaseL.
        newCase->iCaseNumber = i;

	    // Set title for the test case. This is shown in UI to user.
        newCase->iTitle.Copy( Case(i).iCaseName );

	    // Append TTestCaseInfo to the testcase array. After appended 
	    // successfully the TTestCaseInfo object is owned (and freed) 
	    // by the TestServer. 
        User::LeaveIfError(aTestCases.Append ( newCase ) );
        
	    // Pop TTestCaseInfo from the CleanupStack.
        CleanupStack::Pop( newCase );

        }
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::RunTestCaseL
// RunTestCaseL is used to run an individual test case specified 
// by aTestCase. Test cases that can be run may be requested from 
// Test Module by GetTestCases method before calling RunTestCase.
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::RunTestCaseL( 
    const TInt aCaseNumber,   
    const TFileName& /*aConfig*/,                 
    TTestResult& aResult )
    {
    SendTestModuleVersion();
    // Sample how to use logging
    //iLog->Log(_L("Logging starts!"));

    // Return value
    TInt execStatus = KErrNone;

    // Get the pointer to test case function
    TCaseInfo tmp = Case ( aCaseNumber );

    // Check that case number was valid
    if ( tmp.iMethod != NULL )
        {
        // Valid case was found, call it via function pointer
        iMethod = tmp.iMethod;        
        execStatus  = ( this->*iMethod )( aResult );                  
        }
    else
        {        
        // Valid case was not found, return error.
        execStatus = KErrNotFound;
        }

    // Return case execution status (not the result of the case execution)
    return execStatus;
    
    }


// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// LibEntryL is a polymorphic Dll entry point
// Returns: CTestModuleBase*: Pointer to Test Module object
// -----------------------------------------------------------------------------
//
EXPORT_C CTestModuleBase* LibEntryL()
    {
    return CCenRepNotifyHandlerTest::NewL();
    
    }

//  End of File

