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



// INCLUDE FILES
#include <e32math.h>
#include "PowerStateTest.h"

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
// CPowerStateTest::Case
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
const TCaseInfo CPowerStateTest::Case ( 
    const TInt aCaseNumber ) const 
     {

    /**
    * To add new test cases, implement new test case function and add new 
    * line to KCases array specify the name of the case and the function 
    * doing the test case
    * In practice, do following
    * 1) Make copy of existing test case function and change its name
    *    and functionality. Note that the function must be added to 
    *    PowerStateTest.cpp file and to PowerStateTest.h 
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
        ENTRY( "[PowerState] Battery level test", BatteryLevel ),
        ENTRY( "[PowerState] Battery status test", BatteryStatus ),
        ENTRY( "[PowerState] Charging status test", ChargingStatus ),
        ENTRY( "[PowerState] Test all keys in one", TestAllKeysInOne ),
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
// CPowerStateTest::BatteryLevel
// 
// -----------------------------------------------------------------------------
//
TInt CPowerStateTest::BatteryLevel( TTestResult& aResult )
    {

	CTestCasePropertyWatch* iBatteryLevelWatch;
	TInt iErr = KErrNone;

    _LIT( KFailNote, "BatteryLevel test failed" );
   	aResult.SetResult( KErrGeneral, KFailNote );
	
	TRAP(iErr, iBatteryLevelWatch = CTestCasePropertyWatch::NewL(EPSBatteryLevel));

	//Cannot expect battery level to be published in emulator
	//for(i=0;i<300;i++)
	//{	
	//   	CTestScheduler::StartAndStopL(1000);	    		
	//    
	//    if(iBatteryLevelWatch->iStatusReceived)
	//    {
    //		_LIT( KDescription, "BatteryLevel test passed" );
   	//		aResult.SetResult( KErrNone, KDescription );
	//    	break;
	//    }			    			    
	//}

	_LIT( KDescription, "BatteryLevel test executed" );
	aResult.SetResult( iErr, KDescription );

    // Case was executed
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CPowerStateTest::BatteryStatus
// 
// -----------------------------------------------------------------------------
//
TInt CPowerStateTest::BatteryStatus( TTestResult& aResult )
    {

	CTestCasePropertyWatch* iBatteryStatusWatch;
	TInt iErr = KErrNone;

    _LIT( KFailNote, "BatteryStatus test failed" );
   	aResult.SetResult( KErrGeneral, KFailNote );
   	
	TRAP(iErr, iBatteryStatusWatch = CTestCasePropertyWatch::NewL(EPSBatteryStatus));

	//Cannot expect battery status to be published in emulator
	//for(i=0;i<300;i++)
	//{	
	//   	CTestScheduler::StartAndStopL(1000);	    		
	//    
	//    if(iBatteryStatusWatch->iStatusReceived)
	//    {
    //		_LIT( KDescription, "BatteryStatus test passed" );
   	//		aResult.SetResult( KErrNone, KDescription );
	//    	break;
	//    }			    			    
	//}

	_LIT( KDescription, "BatteryStatus test executed" );
	aResult.SetResult( iErr, KDescription );

	
    // Case was executed
    return KErrNone;

    }
    
// -----------------------------------------------------------------------------
// CPowerStateTest::ChargingStatus
// 
// -----------------------------------------------------------------------------
//
TInt CPowerStateTest::ChargingStatus( TTestResult& aResult )
    {
    
	CTestCasePropertyWatch* iChargingStatusWatch;
	
	TInt iErr = KErrNone;

    _LIT( KFailNote, "ChargingStatus test failed" );
   	aResult.SetResult( KErrGeneral, KFailNote );
   	
	TRAP(iErr, iChargingStatusWatch = CTestCasePropertyWatch::NewL(EPSChargingStatus));

	//for(i=0;i<300;i++)
	//{	
	//   	CTestScheduler::StartAndStopL(1000);	    		
	//    
	//    if(iChargingStatusWatch->iStatusReceived)
	//    {
    //		_LIT( KDescription, "ChargingStatus test passed" );
   	//		aResult.SetResult( KErrNone, KDescription );
	//    	break;
	//    }			    			    
	//}


	_LIT( KDescription, "ChargingStatus test executed" );
	aResult.SetResult( iErr, KDescription );


    // Case was executed
    return KErrNone;

    }    

// -----------------------------------------------------------------------------
// CPowerStateTest::TestAllKeysInOne
// 
// -----------------------------------------------------------------------------
//
TInt CPowerStateTest::TestAllKeysInOne( TTestResult& aResult )
    {
    
	CTestCasePropertyWatch* iChargingStatusWatch;
	CTestCasePropertyWatch* iBatteryLevelWatch;
	CTestCasePropertyWatch* iBatteryStatusWatch;
		
	TInt iErr1 = KErrNone;
	TInt iErr2 = KErrNone;
	TInt iErr3 = KErrNone;
	
    _LIT( KFailNote, "TestAllKeysInOne test failed" );
   	aResult.SetResult( KErrGeneral, KFailNote );
   	
	TRAP(iErr1, iChargingStatusWatch = CTestCasePropertyWatch::NewL(EPSChargingStatus));
	TRAP(iErr2, iBatteryLevelWatch = CTestCasePropertyWatch::NewL(EPSBatteryLevel));
	TRAP(iErr3, iBatteryStatusWatch = CTestCasePropertyWatch::NewL(EPSBatteryStatus));
	
	//for(i=0;i<300;i++)
	//{	
	//   	CTestScheduler::StartAndStopL(1000);	    		
	//    
	//    if(iChargingStatusWatch->iStatusReceived && iBatteryLevelWatch->iStatusReceived && iBatteryStatusWatch->iStatusReceived)
	//    {
    // 		_LIT( KDescription, "TestAllKeysInOne test passed" );
   	//		aResult.SetResult( KErrNone, KDescription );
	//    	break;
	//    }			    			    
	//}

	if(iErr1 == KErrNone && iErr2 == KErrNone && iErr3 == KErrNone)
	{
		_LIT( KDescription, "Test executed" );
		aResult.SetResult( KErrNone, KDescription );		
	}

    // Case was executed
    return KErrNone;

    }    

// -----------------------------------------------------------------------------
// ?classname::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
?type ?classname::?member_function(
   ?arg_type arg,
   ?arg_type arg )
   {

   ?code

   }
*/

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
