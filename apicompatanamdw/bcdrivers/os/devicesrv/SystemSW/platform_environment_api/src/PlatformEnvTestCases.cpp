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
#include "PlatformEnvTest.h"

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
// CPlatformEnvTest::Case
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
const TCaseInfo CPlatformEnvTest::Case ( 
    const TInt aCaseNumber ) const 
     {

    /**
    * To add new test cases, implement new test case function and add new 
    * line to KCases array specify the name of the case and the function 
    * doing the test case
    * In practice, do following
    * 1) Make copy of existing test case function and change its name
    *    and functionality. Note that the function must be added to 
    *    PlatformEnvTest.cpp file and to PlatformEnvTest.h 
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
        ENTRY( "[Platformenv] PathTest", PathTest ),
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
// CPlatformEnvTest::PathTest
//
// -----------------------------------------------------------------------------
//
TInt CPlatformEnvTest::PathTest( TTestResult& aResult )
    {

	TBuf<50> iRomBootPath,
	iPhoneMemoryRootPath,
	iMemoryCardRootPath,
	iGamesPath,
	iInstallsPath,
	iOthersPath,
	iVideosPath,
	iImagesPath,
	iPicturesPath,
	iGmsPicturesPath,
	iMmsBackgroundImagesPath,
	iPresenceLogosPath,
	iSoundsPath,
	iDigitalSoundsPath,
	iSimpleSoundsPath,
	iImagesThumbnailPath,
	iMemoryCardContactsPath = _L("");
		
	iRomBootPath = PathInfo::RomRootPath();
	iPhoneMemoryRootPath = PathInfo::PhoneMemoryRootPath();
	iMemoryCardRootPath = PathInfo::MemoryCardRootPath();
	iGamesPath = PathInfo::GamesPath();
	iInstallsPath = PathInfo::InstallsPath();
	iOthersPath = PathInfo::OthersPath();
	iVideosPath = PathInfo::VideosPath();
	iImagesPath = PathInfo::ImagesPath();
	iPicturesPath = PathInfo::PicturesPath();
	iGmsPicturesPath = PathInfo::GmsPicturesPath();
	iMmsBackgroundImagesPath = PathInfo::MmsBackgroundImagesPath();
	iPresenceLogosPath = PathInfo::PresenceLogosPath();
	iSoundsPath = PathInfo::SoundsPath();
	iDigitalSoundsPath = PathInfo::DigitalSoundsPath();
	iSimpleSoundsPath = PathInfo::SimpleSoundsPath();
	iImagesThumbnailPath = PathInfo::ImagesThumbnailPath();
	iMemoryCardContactsPath = PathInfo::MemoryCardContactsPath();
	
	iLog->Log( _L( "PlatformEnvTest Paths:" ));
	iLog->Log( iRomBootPath );
	iLog->Log( iPhoneMemoryRootPath );
	iLog->Log( iMemoryCardRootPath );
	iLog->Log( iGamesPath );
	iLog->Log( iInstallsPath );
	iLog->Log( iOthersPath );
	iLog->Log( iVideosPath );
	iLog->Log( iImagesPath );
	iLog->Log( iPicturesPath );
	iLog->Log( iGmsPicturesPath );
	iLog->Log( iMmsBackgroundImagesPath );
	iLog->Log( iPresenceLogosPath );
	iLog->Log( iSoundsPath );
	iLog->Log( iDigitalSoundsPath );
	iLog->Log( iSimpleSoundsPath );
	iLog->Log( iImagesThumbnailPath );
	iLog->Log( iMemoryCardContactsPath );
		
    // Sets test case result and description(Maximum size is KStifMaxResultDes)
    _LIT( KDescription, "Path Test passed" );
    aResult.SetResult( KErrNone, KDescription );

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
