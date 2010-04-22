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
#include "BCTestContentManagement.h"
#include <MGFetch.h>
#include <mediafiletypes.hrh>

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;
_LIT(KAppName, "BCAppContentManagement");
_LIT( KSelection, "Selection" );
_LIT( KHeading, "Heading" );

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
// CBCAppContentManagement::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CBCAppContentManagement::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CBCAppContentManagement::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CBCAppContentManagement::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "Example", CBCAppContentManagement::ExampleL ),
        ENTRY( "TestRun1L", CBCAppContentManagement::TestRun1L ),
        ENTRY( "TestRun2L", CBCAppContentManagement::TestRun2L ),
        ENTRY( "TestRun3L", CBCAppContentManagement::TestRun3L ),
        ENTRY( "TestRun4L", CBCAppContentManagement::TestRun4L ),
        ENTRY( "TestRun5L", CBCAppContentManagement::TestRun5L ),
        ENTRY( "TestRun6L", CBCAppContentManagement::TestRun6L ),
        ENTRY( "TestRun7L", CBCAppContentManagement::TestRun7L ),
        ENTRY( "TestRun8L", CBCAppContentManagement::TestRun8L ),
        ENTRY( "TestRun9L", CBCAppContentManagement::TestRun9L ),
        ENTRY( "TestRun10L", CBCAppContentManagement::TestRun10L ),
        ENTRY( "TestRun11L", CBCAppContentManagement::TestRun11L ),
        ENTRY( "TestRun12L", CBCAppContentManagement::TestRun12L ),
        ENTRY( "TestRun13L", CBCAppContentManagement::TestRun13L ),
        
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CBCAppContentManagement::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CBCAppContentManagement::ExampleL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KBCAppContentManagement, "BCAppContentManagement" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KBCAppContentManagement, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KBCAppContentManagement, 
                                KParam, i, &string );
        i++;
        }

    return KErrNone;

    }

TInt CBCAppContentManagement::TestRun1L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err, result = MGFetch::RunL( *testArray, EImageFile, EFalse ));
    	if(testArray) { delete testArray; testArray=NULL; }
    	if(err == KErrNotSupported)
				return KErrNone;
    	return result;
    }

TInt CBCAppContentManagement::TestRun2L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err, result = MGFetch::RunL( *testArray, EVideoFile, EFalse ));
    	if(testArray) { delete testArray; testArray=NULL; }
    	if(err == KErrNotSupported)
				return KErrNone;
    	return result;
    }
    
 TInt CBCAppContentManagement::TestRun3L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err, result = MGFetch::RunL( *testArray, EAudioFile, EFalse ));
    	if(testArray) { delete testArray; testArray=NULL; }
    	if(err == KErrNotSupported)
				return KErrNone;
    	return result;
    }
    
 TInt CBCAppContentManagement::TestRun4L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err, result = MGFetch::RunL( *testArray, EPlaylistFile, EFalse ));
    	if(err!= KErrNotSupported)
				User::Leave(err);
    	if(testArray) { delete testArray; testArray=NULL; }
    	if(err == KErrNotSupported)
				return KErrNone;
    	return result;
    }
    
 TInt CBCAppContentManagement::TestRun5L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err, result = MGFetch::RunL( *testArray, EGMSFile, EFalse ));
    	if(err!= KErrNotSupported)
				User::Leave(err);
    	if(testArray) { delete testArray; testArray=NULL; }
    	if(err == KErrNotSupported)
				return KErrNone;
    	return result;
    }
    
 TInt CBCAppContentManagement::TestRun6L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err, result = MGFetch::RunL( *testArray, EMusicFile, EFalse ));
    	if(testArray) { delete testArray; testArray=NULL; }
    	if(err == KErrNotSupported)
				return KErrNone;
    	return result;
    }
    
  TInt CBCAppContentManagement::TestRun7L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err, result = MGFetch::RunL( *testArray, EPresentationsFile, EFalse ));
    	if(testArray) { delete testArray; testArray=NULL; }
    	if(err == KErrNotSupported)
				return KErrNone;
    	return result;
    }
    
  TInt CBCAppContentManagement::TestRun8L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err, result = MGFetch::RunL( *testArray, EAnyMediaFile, EFalse ));
    	if(testArray) { delete testArray; testArray=NULL; }
    	if(err == KErrNotSupported)
				return KErrNone;
    	return result;
    }
    
  TInt CBCAppContentManagement::TestRun9L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err, result = MGFetch::RunL( *testArray, (TMediaFileType) 0x12345678, EFalse ));
    	if(err != KErrNotSupported)
				User::Leave(err);
    	if(testArray) { delete testArray; testArray=NULL; }
    	return KErrNone;
    }
    
    TInt CBCAppContentManagement::TestRun10L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err,result = MGFetch::RunL( *testArray, EImageFile, EFalse, (KSelection), (KHeading) ));
    	if(testArray) { delete testArray; testArray=NULL; }
    	if(err == KErrNotSupported)
				return KErrNone;
    	return result;
    }
    
    TInt CBCAppContentManagement::TestRun11L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	CDesCArrayFlat*	mimeTypeArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err, result = MGFetch::RunL( *testArray, EImageFile, EFalse, (KSelection), (KHeading), mimeTypeArray ));
    	if(testArray) { delete testArray; testArray=NULL; }
    	if(mimeTypeArray) { delete mimeTypeArray; mimeTypeArray=NULL; }
    	if(err == KErrNotSupported)
				return KErrNone;
    	return result;
    }
    
    TInt CBCAppContentManagement::TestRun12L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	CDesCArrayFlat*	mimeTypeArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err, result = MGFetch::RunL( *testArray, EImageFile, EFalse, (KSelection), (KHeading), mimeTypeArray, NULL ));
    	if(testArray) { delete testArray; testArray=NULL; }
    	if(mimeTypeArray) { delete mimeTypeArray; mimeTypeArray=NULL; }
    	if(err == KErrNotSupported)
				return KErrNone;
    	return result;
    }
    
    TInt CBCAppContentManagement::TestRun13L( CStifItemParser& aItem )
    {
    	TBool result=0;
    	CDesCArrayFlat* testArray = new (ELeave) CDesCArrayFlat( 5 );
    	CDesCArrayFlat*	mimeTypeArray = new (ELeave) CDesCArrayFlat( 5 );
    	TRAPD(err, result = MGFetch::RunL( *testArray, ERAMFile, EFalse ));
    	if(testArray) { delete testArray; testArray=NULL; }
    	if(mimeTypeArray) { delete mimeTypeArray; mimeTypeArray=NULL; }
    	if(err == KErrNotSupported)
				return KErrNone;
    	return result;
    }
    
// -----------------------------------------------------------------------------
// CBCAppContentManagement::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt CBCAppContentManagement::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  [End of File] - Do not remove
