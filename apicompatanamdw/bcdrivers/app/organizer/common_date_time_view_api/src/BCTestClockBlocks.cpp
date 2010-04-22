/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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



// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "BCTestClock.h"

#include <ClkDateTimeView.h>


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
// CBCTestClock::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CBCTestClock::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CBCTestClock::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CBCTestClock::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "Example", CBCTestClock::ExampleL ),
        ENTRY( "TestNewLCFalse", CBCTestClock::TestNewLCFalseL ),
        ENTRY( "TestNewLCTrue", CBCTestClock::TestNewLCTrueL ),
        ENTRY( "TestInitCurItem", CBCTestClock::TestInitCurItemL ),
        ENTRY( "TestHandleUpdate", CBCTestClock::TestHandleUpdateL ),
        
        
                
        
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CBCTestClock::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CBCTestClock::ExampleL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KBCTestClock, "BCTestClock" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KBCTestClock, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KBCTestClock, 
                                KParam, i, &string );
        i++;
        }
		
    return KErrNone;

    }

TInt CBCTestClock::TestNewLCFalseL( CStifItemParser& aItem )
{
	const TUid aViewId = {1};
	CClkDateTimeView* dateTimeView;
	TRAPD(err, 
						{
							dateTimeView = CClkDateTimeView::NewLC(aViewId, EFalse);
							CleanupStack::Pop(dateTimeView);
	
  						if(dateTimeView)
							  {
							  	delete dateTimeView ;	
							    dateTimeView = 0;
							  }
						});	  

	if(err != KErrNone)
		User::LeaveIfError(err);
	else	
	return KErrNone;
}

TInt CBCTestClock::TestNewLCTrueL( CStifItemParser& aItem )
{
	const TUid aViewId = {1};
	CClkDateTimeView* dateTimeView;
	TRAPD(err, 
						{
							dateTimeView = CClkDateTimeView::NewLC(aViewId, ETrue);
							CleanupStack::Pop(dateTimeView);
	
  						if(dateTimeView)
							  {
							  	delete dateTimeView ;	
							    dateTimeView = 0;
							  }
						});	  

	if(err != KErrNone)
		User::LeaveIfError(err);
	else	
	return KErrNone;
}


TInt CBCTestClock::TestInitCurItemL( CStifItemParser& aItem )
{
	const TUid aViewId = {1};
	CClkDateTimeView* dateTimeView;
	dateTimeView = CClkDateTimeView::NewLC(aViewId, ETrue);
	CleanupStack::Pop(dateTimeView);
	TRAPD(err,dateTimeView->InitCurrentItem());

	if(dateTimeView)
  {
  	delete dateTimeView ;	
    dateTimeView = 0;
  }
  
	if(err != KErrNone)
		User::LeaveIfError(err);
	else
	return KErrNone;
}

TInt CBCTestClock::TestHandleUpdateL( CStifItemParser& aItem )
{
	const TUid aViewId = {1};
	CClkDateTimeView* dateTimeView;
	dateTimeView = CClkDateTimeView::NewLC(aViewId, ETrue);
	CleanupStack::Pop(dateTimeView);
	TRAPD(err,dateTimeView->HandleUpdateL(1));

	if(dateTimeView)
  {
  	delete dateTimeView ;	
    dateTimeView = 0;
  }
  
	if(err != KErrNone)
		User::LeaveIfError(err);
	else
	return KErrNone;
}





// -----------------------------------------------------------------------------
// CBCTestClock::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt CBCTestClock::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  [End of File] - Do not remove
