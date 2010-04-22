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
* Description:  ?Description
*
*/

/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */


// INCLUDE FILES
#include <e32math.h>
#include "PhoneParserTest.h"

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
// CPhoneParserTest::Case
// Returns a test case by number.
//
// This function contains an array of all available test cases 
// i.e pair of case name and test function. If case specified by parameter
// aCaseNumber is found from array, then that item is returned.
// 
// The reason for this rather complicated function is to specify all the
// test cases only in one place. It is not necessary to understand how
// function pointers to class member functions works when adding new test
// cases. See function body for instructions how to add new test case.
// -----------------------------------------------------------------------------
//
const TCaseInfo CPhoneParserTest::Case ( 
    const TInt aCaseNumber ) const 
     {

    /**
    * To add new test cases, implement new test case function and add new 
    * line to KCases array specify the name of the case and the function 
    * doing the test case
    * In practice, do following
    * 1) Make copy of existing test case function and change its name
    *    and functionality. Note that the function must be added to 
    *    PhoneParserTest.cpp file and to PhoneParserTest.h 
    *    header file.
    *
    * 2) Add entry to following KCases array either by using:
    *
    * 2.1: FUNCENTRY or ENTRY macro
    * ENTRY macro takes two parameters: test case name and test case 
    * function name.
    *
    * FUNCENTRY macro takes only test case function name as a parameter and
    * uses that as a test case name and test case function name.
    *
    * Or
    *
    * 2.2: OOM_FUNCENTRY or OOM_ENTRY macro. Note that these macros are used
    * only with OOM (Out-Of-Memory) testing!
    *
    * OOM_ENTRY macro takes five parameters: test case name, test case 
    * function name, TBool which specifies is method supposed to be run using
    * OOM conditions, TInt value for first heap memory allocation failure and 
    * TInt value for last heap memory allocation failure.
    * 
    * OOM_FUNCENTRY macro takes test case function name as a parameter and uses
    * that as a test case name, TBool which specifies is method supposed to be
    * run using OOM conditions, TInt value for first heap memory allocation 
    * failure and TInt value for last heap memory allocation failure. 
    */ 

    static TCaseInfoInternal const KCases[] =
        {
        // To add new test cases, add new items to this array
        //FUNCENTRY( PrintTest ),
        
        //PPN == EPlainPhoneNumber
        //CCN == EContactCardNumber
        //PCN == EPhoneClientNumber
        //SMS == ESMSNumber
        
        ENTRY( "[PhoneParser] ParsePhoneNumberWithValidPPN1", ParsePhoneNumberTest1 ),
        ENTRY( "[PhoneParser] ParsePhoneNumberWithValidPPN2", ParsePhoneNumberTest2 ),
        ENTRY( "[PhoneParser] ParsePhoneNumberWithNotValidPPN", ParsePhoneNumberTest3 ),
        ENTRY( "[PhoneParser] ParsePhoneNumberWithValidCCN", ParsePhoneNumberTest4 ),
        ENTRY( "[PhoneParser] ParsePhoneNumberWithNotValidCCN", ParsePhoneNumberTest5 ),
        ENTRY( "[PhoneParser] IsValidPhoneNumberWithValidPPN", IsValidPhoneNumberTest1 ),
        ENTRY( "[PhoneParser] IsValidPhoneNumberWithNotValidPPN", IsValidPhoneNumberTest2 ),
        ENTRY( "[PhoneParser] IsValidPhoneNumberWithValidCCN", IsValidPhoneNumberTest3 ),
        ENTRY( "[PhoneParser] IsValidPhoneNumberWithNotValidCCN", IsValidPhoneNumberTest4 ),
                
        // Example how to use OOM functionality
        //OOM_ENTRY( "Loop test with OOM", LoopTest, ETrue, 2, 3),
        //OOM_FUNCENTRY( PrintTest, ETrue, 1, 3 ),
        };

    // Verify that case number is valid
    if( (TUint) aCaseNumber >= sizeof( KCases ) / 
                               sizeof( TCaseInfoInternal ) )
        {
        // Invalid case, construct empty object
        TCaseInfo null( (const TText*) L"" );
        null.iMethod = NULL;
        null.iIsOOMTest = EFalse;
        null.iFirstMemoryAllocation = 0;
        null.iLastMemoryAllocation = 0;
        return null;
        } 

    // Construct TCaseInfo object and return it
    TCaseInfo tmp ( KCases[ aCaseNumber ].iCaseName );
    tmp.iMethod = KCases[ aCaseNumber ].iMethod;
    tmp.iIsOOMTest = KCases[ aCaseNumber ].iIsOOMTest;
    tmp.iFirstMemoryAllocation = KCases[ aCaseNumber ].iFirstMemoryAllocation;
    tmp.iLastMemoryAllocation = KCases[ aCaseNumber ].iLastMemoryAllocation;
    return tmp;

    }

// -----------------------------------------------------------------------------
// CPhoneParserTest::ParsePhoneNumberTest
// Test checks if CommonPhoneParser::ParsePhoneNumber method returns correct value
// -----------------------------------------------------------------------------
//

// Tests with EPlainPhoneNumber
TInt CPhoneParserTest::ParsePhoneNumberTest1( TTestResult& aResult )
    {

    TBuf<50> number = _L("+46 345 34(34347) 42443 42"); // This should be a parseable plain phone number
	
	if( CommonPhoneParser::ParsePhoneNumber(number, CommonPhoneParser::EPlainPhoneNumber) )
	{
    	// Test case passed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "ParsePhoneNumberTest1 passed" );
	    aResult.SetResult( KErrNone, KDescription );
	}
    else
    {
    	// Test case failed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "ParsePhoneNumberTest1 failed" );
	    aResult.SetResult( KErrGeneral, KDescription );    	
    }
    
    // Case was executed
    return KErrNone;

    }

TInt CPhoneParserTest::ParsePhoneNumberTest2( TTestResult& aResult )
    {

    TBuf<50> number = _L("0500 -499000"); // This should be a parseable plain phone number
	
	if( CommonPhoneParser::ParsePhoneNumber(number, CommonPhoneParser::EPlainPhoneNumber) )
	{
    	// Test case passed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "ParsePhoneNumberTest2 passed" );
	    aResult.SetResult( KErrNone, KDescription );
	}
    else
    {
    	// Test case failed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "ParsePhoneNumberTest2 failed" );
	    aResult.SetResult( KErrGeneral, KDescription );    	
    }
    
    // Case was executed
    return KErrNone;

    }

TInt CPhoneParserTest::ParsePhoneNumberTest3( TTestResult& aResult )
    {

    TBuf<50> number = _L("p050-4872485"); // This should NOT be a parseable plain phone number
	
	if(! (CommonPhoneParser::ParsePhoneNumber(number, CommonPhoneParser::EPlainPhoneNumber) ))
	{
    	// Test case passed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "ParsePhoneNumberTest3 passed" );
	    aResult.SetResult( KErrNone, KDescription );
	}
    else
    {
    	// Test case failed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "ParsePhoneNumberTest3 failed" );
	    aResult.SetResult( KErrGeneral, KDescription );    	
    }
    
    // Case was executed
    return KErrNone;

    }
 
 //Tests with EContactCardNumber  
 TInt CPhoneParserTest::ParsePhoneNumberTest4( TTestResult& aResult )
    {

    TBuf<50> number = _L("*31*6(0)35/6546"); // This should be a parseable contact card number
	
	if( CommonPhoneParser::ParsePhoneNumber(number, CommonPhoneParser::EContactCardNumber) )
	{
    	// Test case passed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "ParsePhoneNumberTest1 passed" );
	    aResult.SetResult( KErrNone, KDescription );
	}
    else
    {
    	// Test case failed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "ParsePhoneNumberTest1 failed" );
	    aResult.SetResult( KErrGeneral, KDescription );    	
    }
    
    // Case was executed
    return KErrNone;

    }
    
 TInt CPhoneParserTest::ParsePhoneNumberTest5( TTestResult& aResult )
    {

    TBuf<50> number = _L("*31*p#+46a35656546"); // This should NOT be a parseable contact card number
	
	if(!( CommonPhoneParser::ParsePhoneNumber(number, CommonPhoneParser::EContactCardNumber) ))
	{
    	// Test case passed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "ParsePhoneNumberTest5 passed" );
	    aResult.SetResult( KErrNone, KDescription );
	}
    else
    {
    	// Test case failed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "ParsePhoneNumberTest5 failed" );
	    aResult.SetResult( KErrGeneral, KDescription );    	
    }
    
    // Case was executed
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CPhoneParserTest::IsValidPhoneNumberTest
// Test checks if CommonPhoneParser::IsValidPhoneNumber method returns correct value.
// -----------------------------------------------------------------------------
//

// Tests with EPlainPhoneNumber
TInt CPhoneParserTest::IsValidPhoneNumberTest1( TTestResult& aResult )
   {
    TBuf<50> number = _L("+46 40 45656546"); // This should be valid plain phone number
	
	if(CommonPhoneParser::IsValidPhoneNumber(number, CommonPhoneParser::EPlainPhoneNumber) )
	{
    	// Test case passed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "IsValidPhoneNumberTest1 passed" );
	    aResult.SetResult( KErrNone, KDescription );
	}
    else
    {
    	// Test case failed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "IsValidPhoneNumberTest1 failed" );
	    aResult.SetResult( KErrGeneral, KDescription );    	
    }
    // Case was executed
    return KErrNone;
   }

TInt CPhoneParserTest::IsValidPhoneNumberTest2( TTestResult& aResult )
   {
    TBuf<50> number = _L("p +46 40 45656546"); // This should NOT be a valid plain phone number
	
	if(!(CommonPhoneParser::IsValidPhoneNumber(number, CommonPhoneParser::EPlainPhoneNumber) ))
	{
    	// Test case passed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "IsValidPhoneNumberTest2 passed" );
	    aResult.SetResult( KErrNone, KDescription );
	}
    else
    {
    	// Test case failed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "IsValidPhoneNumberTest2 failed" );
	    aResult.SetResult( KErrGeneral, KDescription );    	
    }
    // Case was executed
    return KErrNone;
   }

// Tests with EContactCardNumber

TInt CPhoneParserTest::IsValidPhoneNumberTest3( TTestResult& aResult )
   {
    TBuf<50> number = _L("*31#0w(08)3111113"); // This should  be a valid contact card number
	
	if(CommonPhoneParser::IsValidPhoneNumber(number, CommonPhoneParser::EContactCardNumber) )
	{
    	// Test case passed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "IsValidPhoneNumberTest3 passed" );
	    aResult.SetResult( KErrNone, KDescription );
	}
    else
    {
    	// Test case failed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "IsValidPhoneNumberTest3 failed" );
	    aResult.SetResult( KErrGeneral, KDescription );    	
    }
    // Case was executed
    return KErrNone;
   }

TInt CPhoneParserTest::IsValidPhoneNumberTest4( TTestResult& aResult )
   {
    TBuf<50> number = _L("a(08)3111113"); // This should NOT be a valid contact card number
	
	if(!(CommonPhoneParser::IsValidPhoneNumber(number, CommonPhoneParser::EContactCardNumber) ))
	{
    	// Test case passed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "IsValidPhoneNumberTest4 passed" );
	    aResult.SetResult( KErrNone, KDescription );
	}
    else
    {
    	// Test case failed
   	 	// Sets test case result and description(Maximum size is KStifMaxResultDes)
   	 	_LIT( KDescription, "IsValidPhoneNumberTest4 failed" );
	    aResult.SetResult( KErrGeneral, KDescription );    	
    }
    // Case was executed
    return KErrNone;
   }
   
// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// ?function_name implements...
// ?implementation_description.
// Returns: ?value_1: ?description
//          ?value_n: ?description
//                    ?description
// -----------------------------------------------------------------------------
//
/*
?type  ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg )  // ?description
    {

    ?code

    }
*/
//  End of File
