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
* Description:  This module contains the implementation of Stiftextresolvertest class 
*				 member functions
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include "Stiftextresolvertest.h"

// EXTERNAL DATA STRUCTURES
// None

// EXTERNAL FUNCTION PROTOTYPES  
// None

// CONSTANTS
// None

// MACROS
// None

// LOCAL CONSTANTS AND MACROS
// None

// MODULE DATA STRUCTURES
// None

// LOCAL FUNCTION PROTOTYPES
// None

// FORWARD DECLARATIONS
// None

// ==================== LOCAL FUNCTIONS =======================================
// None


// ================= MEMBER FUNCTIONS =========================================

// -----------------------------------------------------------------------------
// CStiftextresolvertest::CStiftextresolvertest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CStiftextresolvertest::CStiftextresolvertest()
    {

    }

// -----------------------------------------------------------------------------
// CStiftextresolvertest::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CStiftextresolvertest::ConstructL()
    {
	
	TInt erro( iFs.Connect() );
		if ( erro < 0 )
	    	{
			User::LeaveIfError( erro );
	    	}
	
		User::LeaveIfError(iFs.ShareProtected());
		
    }
//-----------------------------------------------------------------------------
// CStiftextresolvertest::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CStiftextresolvertest::SendTestModuleVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_MODULE_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_MODULE_VERSION_MINOR;
	moduleVersion.iBuild = TEST_MODULE_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("stiftextresolvertest.dll");
	

	TBool newVersionOfMethod = ETrue;
	CTestModuleIf &test=TestModuleIf();
	test.SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
	test.SetBehavior(CTestModuleIf::ETestLeaksHandles);
	}

// -----------------------------------------------------------------------------
// CStiftextresolvertest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
CStiftextresolvertest* CStiftextresolvertest::NewL()
    {
    CStiftextresolvertest* self = new (ELeave) CStiftextresolvertest;
    
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

	//TInt err = iFsSession.Connect();

    return self;
    
    }

// Destructor    
CStiftextresolvertest::~CStiftextresolvertest()
    { 
    iFs.Close();   
    }

// -----------------------------------------------------------------------------
// CStiftextresolvertest::InitL
// Initialization function.
// -----------------------------------------------------------------------------
TInt CStiftextresolvertest::InitL( 
		TFileName& /*aIniFile*/, 
		TBool /*aFirstTime*/ )
    {
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CStiftextresolvertest::GetTestCasesL
// GetTestCases is used to inquire test cases from the Test Module
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt CStiftextresolvertest::GetTestCasesL( 
		const TFileName& /*aConfigFile*/, //Test case file
        RPointerArray<TTestCaseInfo>& aTestCases ) //Array of test cases
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
// Cfinditemenginetest::RunTestCaseL
// Runs a specified testcase
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt CStiftextresolvertest::RunTestCaseL( 
		const TInt aCaseNumber, //Test case number 
        const TFileName& /*aConfig*/, //Test case file
        TTestResult& aResult ) //Test case result
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
    return execStatus;
      
    }

// -----------------------------------------------------------------------------
// CStiftextresolvertest::test
// Gives a return value.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
/*const*/ TInt CStiftextresolvertest::test(TBool val) const
{
	TInt retVal(KErrNone);
	if (!val) retVal = KErrGeneral;
	return retVal;
}

// ================= OTHER EXPORTED FUNCTIONS =================================

// -----------------------------------------------------------------------------
// LibEntryL
// Polymorphic Dll Entry Point
// Returns: CTestModuleBase*: Pointer to Test Module object
// -----------------------------------------------------------------------------
EXPORT_C CStiftextresolvertest* LibEntryL()
    {
    return CStiftextresolvertest::NewL();
    
    }

//  End of File
