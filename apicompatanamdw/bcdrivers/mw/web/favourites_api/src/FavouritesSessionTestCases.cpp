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
* Description: 
*
*
*/



// INCLUDE FILES
#include <e32math.h>
#include "FavouritesBCTest.h"

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


// ============================ MEMBER FUNCTIONS ===============================

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: SessionVersionTest

    Description: Test the RFavouritesSession Version method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::SessionVersionTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State" );
    _LIT( KData ,"Test the RFavouritesSession Version method" );
    TestModuleIf().Printf( 0, KDefinition, KData );

    TVersion sessionVersion = iFavouritesSession.Version();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (sessionVersion.iMajor > 0)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: SessionConnectTest

    Description: Test the RFavouritesSession Connect method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::SessionConnectTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State" );
    _LIT( KData ,"Test the RFavouritesSession Connect method" );
    TestModuleIf().Printf( 0, KDefinition, KData );

    RFavouritesSession session;

    TInt result = session.Connect();

    _LIT( KData2 ,"Finished" );
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    session.Close();

    if( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: SessionResourceMarkTest

    Description: Test the RFavouritesSession ResourceMark method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::SessionResourceMarkTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State" );
    _LIT( KData ,"Test the RFavouritesSession ResourceMark method" );
    TestModuleIf().Printf( 0, KDefinition, KData );

    iFavouritesSession.ResourceMark();

    _LIT( KData2 ,"Finished" );
    TestModuleIf().Printf( 0, KDefinition, KData2 );

	// ResourceMark provides no results, so if we've gotten this far assume success
    _LIT( KDescription , "Test case passed" );
    aResult.SetResult( KErrNone, KDescription );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: SessionResourceCheckTest

    Description: Test the RFavouritesSession ResourceCheck method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::SessionResourceCheckTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State" );
    _LIT( KData ,"Test the RFavouritesSession ResourceCheck method" );
    TestModuleIf().Printf( 0, KDefinition, KData );

    iFavouritesSession.ResourceCheck();

    _LIT( KData2 ,"Finished" );
    TestModuleIf().Printf( 0, KDefinition, KData2 );

	// ResourceCheck provides no results, so if we've gotten this far assume success
    _LIT( KDescription , "Test case passed" );
    aResult.SetResult( KErrNone, KDescription );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: SessionResourceCountTest

    Description: Test the RFavouritesSession ResourceCount method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::SessionResourceCountTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State" );
    _LIT( KData ,"Test the RFavouritesSession ResourceCount method" );
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt count = iFavouritesSession.ResourceCount();

    _LIT( KData2 ,"Finished" );
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if( count == 0 )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: SessionDeleteDatabaseTestL

    Description: Test the RFavouritesSession DeleteDatabase method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::SessionDeleteDatabaseTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State" );
    _LIT( KData ,"Test the RFavouritesSession DeleteDatabase method" );
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    TInt result = iFavouritesSession.DeleteDatabase( KTestDbName );

    _LIT( KData2 ,"Finished" );
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: SessionDbgSetAllocFailTest

    Description: Test the RFavouritesSession __DbgSetAllocFail method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::SessionDbgSetAllocFailTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State" );
    _LIT( KData ,"Test the RFavouritesSession __DbgSetAllocFail method" );
    TestModuleIf().Printf( 0, KDefinition, KData );

    iFavouritesSession.__DbgSetAllocFail( RHeap::ENone, 1 );

    _LIT( KData2 ,"Finished" );
    TestModuleIf().Printf( 0, KDefinition, KData2 );

	// __DbgSetAllocFail provides no results, so if we've gotten this far assume success
    _LIT( KDescription , "Test case passed" );
    aResult.SetResult( KErrNone, KDescription );

    // Case was executed
    return KErrNone;
    }

// ================= OTHER EXPORTED FUNCTIONS =================================

// End of File
