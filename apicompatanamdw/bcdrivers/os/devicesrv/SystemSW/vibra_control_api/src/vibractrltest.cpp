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
* Description:  vibractrltest class member functions
*
*/

/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */


// INCLUDE FILES
#include <stiftestinterface.h>
#include "vibractrltest.h"
//#include <vibraInternalCRKeys.h>


// EXTERNAL DATA STRUCTURES

// EXTERNAL FUNCTION PROTOTYPES  

// CONSTANTS

// MACROS

// LOCAL CONSTANTS AND MACROS

// MODULE DATA STRUCTURES

// LOCAL FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// ============================= LOCAL FUNCTIONS ===============================

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Cvibractrltest::Cvibractrltest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
Cvibractrltest::Cvibractrltest()
{
	
	/*
	CActiveScheduler myActiveScheduler;
	myActiveScheduler = new CActiveScheduler;
	CActiveScheduler::Install(myActiveScheduler);
*/	//CActiveScheduler *test = CActiveScheduler::NewL(); //::Install( /*CTestScheduler::NewL() */this);
}

// -----------------------------------------------------------------------------
// Cvibractrltest::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void Cvibractrltest::ConstructL()
{
    iRepository = CRepository::NewL(KCRUidVibraCtrl);

	#ifndef __WINS__


	iLogger = CStifLogger::NewL(KBCVibraCtrlPath,
						           KBCibraCtrlTestLogFile, 
								   CStifLogger::ETxt, 
								   CStifLogger::EFile, 
								   ETrue,
								   ETrue,
								   ETrue,
								   EFalse, 
								   EFalse);

	#else

	iLogger = CStifLogger::NewL(_L("C:\\"),
						           _L("VibraLoggerFile"), 
								   CStifLogger::ETxt, 
								   CStifLogger::EFile, 
								   ETrue,
								   ETrue,
								   ETrue,
								   EFalse, 
								   EFalse);
	#endif
	

}
//-----------------------------------------------------------------------------
// Cvibractrltest::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void Cvibractrltest::SendTestModuleVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_MODULE_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_MODULE_VERSION_MINOR;
	moduleVersion.iBuild = TEST_MODULE_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("vibractrltest.dll");
	

	TBool newVersionOfMethod = ETrue;
	CTestModuleIf &test=TestModuleIf();
	test.SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
	test.SetBehavior(CTestModuleIf::ETestLeaksHandles);
	}

// -----------------------------------------------------------------------------
// Cvibractrltest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
Cvibractrltest* Cvibractrltest::NewL()
{
    Cvibractrltest* self = new (ELeave) Cvibractrltest;
    
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    
}

// Destructor
Cvibractrltest::~Cvibractrltest()
{ 
    delete iRepository;
	//delete myTestScheduler;
      
}

// -----------------------------------------------------------------------------
// Cvibractrltest::InitL
// InitL is used to initialize the Test Module.
// -----------------------------------------------------------------------------
//
TInt Cvibractrltest::InitL( 
    TFileName& /*aIniFile*/, 
    TBool /*aFirstTime*/ )
{
    return KErrNone;
    
}

// -----------------------------------------------------------------------------
// Cvibractrltest::GetTestCasesL
// GetTestCases is used to inquire test cases from the Test Module. Test
// cases are stored to array of test cases. The Test Framework will be 
// the owner of the data in the RPointerArray after GetTestCases return
// and it does the memory deallocation. 
// -----------------------------------------------------------------------------
//
TInt Cvibractrltest::GetTestCasesL( 
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
// Cvibractrltest::RunTestCaseL
// RunTestCaseL is used to run an individual test case specified 
// by aTestCase. Test cases that can be run may be requested from 
// Test Module by GetTestCases method before calling RunTestCase.
// -----------------------------------------------------------------------------
//
TInt Cvibractrltest::RunTestCaseL( 
    const TInt aCaseNumber,   
    const TFileName& /*aConfig*/,                 
    TTestResult& aResult )
{
	SendTestModuleVersion();
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
	
    /*aResult.iResultDes.Copy( _L("Test passed") );
    aResult.iResult = KErrNone;
    return KErrNone;*/
    
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
    return Cvibractrltest::NewL();
    
}

//  End of File
