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
* Description:  This module contains the implementation of finditemenginetest class 
*				 member functions
*
*/






// INCLUDE FILES
#include <testinterface.h>
#include "finditemenginetest.h"

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
// Cfinditemenginetest::Cfinditemenginetest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
Cfinditemenginetest::Cfinditemenginetest()
    {

    }

// -----------------------------------------------------------------------------
// Cfinditemenginetest::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void Cfinditemenginetest::ConstructL()
    {

    }

// -----------------------------------------------------------------------------
// Cfinditemenginetest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
Cfinditemenginetest* Cfinditemenginetest::NewL()
    {
    Cfinditemenginetest* self = new (ELeave) Cfinditemenginetest;
    
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    
    }

// Destructor   
Cfinditemenginetest::~Cfinditemenginetest()
    { 
       
    }


// -----------------------------------------------------------------------------
// Cfinditemenginetest::InitL
// Initialization function.
// -----------------------------------------------------------------------------
TInt Cfinditemenginetest::InitL( 
		TFileName& /*aIniFile*/, 
		TBool /*aFirstTime*/ )
    {
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// Cfinditemenginetest::GetTestCasesL
// GetTestCases is used to inquire test cases from the Test Module
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cfinditemenginetest::GetTestCasesL( 
		const TFileName& /*aConfig*/, 
        RPointerArray<TTestCaseInfo>& aTestCases )
    {
    
    /**
    * A sample code for testcase description allocation, filling and adding 
    * to test case array. This is probably done somehow in a loop for 
    * every testcase and information may be fetched from file 
    * given as parameter or it can be hardcoded to the testmodule. 
    * Another example can be found from DemoModule included 
    * also in STIF Test Framework release. 
	**/
    
    for( TInt i = 0; Case(i).iMethod != NULL; i++ )
    {
			// Allocate new TTestCaseInfo from heap.
		    // It MUST be allocated from heap.
		   TTestCaseInfo* testCase = new ( ELeave ) TTestCaseInfo();
    
			// PushL TTestCaseInfo to CleanupStack.    
			CleanupStack::PushL( testCase );
    
			// Set number for the testcase.
			// When the testcase is run, this comes as a parameter to RunTestCaseL.
			testCase->iCaseNumber = 1;
    
			// Set title for the test case. This is shown in UI to the user.
			testCase->iTitle.Copy( _L("Test one") );
    
			// Append TTestCaseInfo to the testcase array. After appended succesfully 
			// the TTestCaseInfo object is owned (and freed) by the TestServer. 
			User::LeaveIfError( aTestCases.Append( testCase ) );
    
			// Pop TTestCaseInfo from the CleanupStack.
			CleanupStack::Pop( testCase );
	}
    
    
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// Cfinditemenginetest::RunTestCaseL
// Runs a specified testcase
// (other items were commented in a header).
// -----------------------------------------------------------------------------
TInt Cfinditemenginetest::RunTestCaseL( 
		const TInt aCaseNumber, 
        const TFileName& /*aConfig*/,
        TTestResult& aResult )
    {
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
    /*aResult.iResultDes.Copy( _L("Test passed") );
    aResult.iResult = KErrNone;
    return KErrNone;*/
    
    }

// -----------------------------------------------------------------------------
// Cfinditemenginetest::test
// Gives a return value.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
const TInt Cfinditemenginetest::test(
		TBool val) const
{
	TInt retVal(KErrNone);
	if (!val) retVal = KErrGeneral;
	return retVal;
}


// ================= OTHER EXPORTED FUNCTIONS =================================

/*
-------------------------------------------------------------------------------
   
    Function: LibEntryL

    Description: Polymorphic Dll Entry Point

    Parameters:	None

    Return Values: CTestModuleBase*: Pointer to Test Module object

    Errors/Exceptions: Leaves if NewL leaves.

    Status: Draft

-------------------------------------------------------------------------------
*/
EXPORT_C CTestModuleBase* LibEntryL()
    {
    return Cfinditemenginetest::NewL();
    
    }

//  End of File
