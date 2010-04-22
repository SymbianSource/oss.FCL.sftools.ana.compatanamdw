/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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

    Method: DbOpenTestL

    Description: Test opening the Favourites Db by using the Open method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbOpenTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Open method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt result = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbVersionTestL

    Description: Test the Favourites Db Version method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbVersionTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Version method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    TVersion dbVersion = iFavouritesDb.Version();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (dbVersion.iMajor > 0)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbIsDamagedTestL

    Description: Test the Favourites Db IsDamaged method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbIsDamagedTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db IsDamaged method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    TBool isDbDamaged = EFalse;

    TInt result = iFavouritesDb.IsDamaged(isDbDamaged);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbRecoverTestL

    Description: Test the Favourites Db Recover method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbRecoverTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Recover method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    TInt result = iFavouritesDb.Recover();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbCompactTestL

    Description: Test the Favourites Db Compact method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbCompactTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Compact method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    TInt result = iFavouritesDb.Compact();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbSizeTestL

    Description: Test the Favourites Db Size method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbSizeTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Size method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    RDbDatabase::TSize dbSize;

    TInt result = iFavouritesDb.Size(dbSize);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbUpdateStatsTestL

    Description: Test the Favourites Db UpdateStats method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbUpdateStatsTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db UpdateStats method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    TInt result = iFavouritesDb.UpdateStats();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbBeginTestL

    Description: Test the Favourites Db Begin method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbBeginTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Begin method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    TInt result = iFavouritesDb.Begin(EFalse);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbCommitTestL

    Description: Test the Favourites Db Commit method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbCommitTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Commit method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    iFavouritesDb.Begin(EFalse);
    TInt result = iFavouritesDb.Commit();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbRollbackTestL

    Description: Test the Favourites Db Rollback method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbRollbackTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Rollback method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    iFavouritesDb.Begin(EFalse);
    CreateItemL( iItem1 );
    iFavouritesDb.Add( *iItem1, EFalse );

    TInt result = KErrNone;
    TRAP(result, iFavouritesDb.Rollback());

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    delete iItem1;
    iItem1 = NULL;

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbCleanupRollbackPushLTestL

    Description: Test the Favourites Db CleanupRollbackPushL method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbCleanupRollbackPushLTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db CleanupRollbackPushL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    iFavouritesDb.Begin(EFalse);
    iFavouritesDb.CleanupRollbackPushL();
    CreateItemL( iItem1 );
    iFavouritesDb.Add( *iItem1, EFalse );
    TInt result = iFavouritesDb.Commit();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::Pop(); // RollbackPush
    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    delete iItem1;
    iItem1 = NULL;

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbGetTestL

    Description: Test the Favourites Db Get method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbGetTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Get method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    CFavouritesItem* item = CFavouritesItem::NewLC();

    TInt result = iFavouritesDb.Get( iItem1->Uid(), *item );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(2); // iFavouritesDb, item
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbGetAllTestL

    Description: Test the Favourites Db GetAll method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbGetAllTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db GetAll method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    CFavouritesItemList* list = new (ELeave) CFavouritesItemList();

    TInt result = iFavouritesDb.GetAll( *list, KFavouritesRootUid );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    delete list;
    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbGetUidsTestL

    Description: Test the Favourites Db GetUids method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbGetUidsTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db GetUids method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    CArrayFix<TInt>* uids = new (ELeave) CArrayFixFlat<TInt>( 1 );

    TInt result = iFavouritesDb.GetUids( *uids, KFavouritesRootUid, CFavouritesItem::ENone, NULL, KFavouritesNullContextId );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    delete uids;
    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbPreferredUidTestL

    Description: Test the Favourites Db PreferredUid method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbPreferredUidTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db PreferredUid method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    iFavouritesDb.SetPreferredUid(iItemFolder1->Uid(), 222);
    TInt preferredUid;
    iFavouritesDb.PreferredUid( iItemFolder1->Uid(), preferredUid );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (preferredUid == 222)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbDeleteTestL

    Description: Test the Favourites Db Delete method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbDeleteTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Delete method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TInt countBeforeDelete;
    iFavouritesDb.Count(countBeforeDelete, KFavouritesNullUid, CFavouritesItem::ENone, NULL, KFavouritesNullContextId);
    iFavouritesDb.Delete( iItem3->Uid() );
    TInt countAfterDelete;
    iFavouritesDb.Count(countAfterDelete, KFavouritesNullUid, CFavouritesItem::ENone, NULL, KFavouritesNullContextId);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (countAfterDelete == countBeforeDelete - 1)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbUpdateTestL

    Description: Test the Favourites Db Update method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbUpdateTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Update method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    CFavouritesItem* updateItem = CFavouritesItem::NewLC();

    InitItemL( updateItem );
    updateItem->SetParentFolder(iItemFolder1->Uid());
    TInt result = iFavouritesDb.Update(*updateItem, iItem6->Uid(), EFalse);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(2); // iFavouritesDb, updateItem
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbAddTestL

    Description: Test the Favourites Db Add method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbAddTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Add method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    CFavouritesItem* itemToAdd = CFavouritesItem::NewLC();
    InitItemL( itemToAdd );

    TInt countBeforeAdd;
    iFavouritesDb.Count(countBeforeAdd, KFavouritesNullUid, CFavouritesItem::ENone, NULL, KFavouritesNullContextId);
    iFavouritesDb.Add( *itemToAdd, EFalse );
    TInt countAfterAdd;
    iFavouritesDb.Count(countAfterAdd, KFavouritesNullUid, CFavouritesItem::ENone, NULL, KFavouritesNullContextId);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (countAfterAdd == countBeforeAdd + 1)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(2); // iFavouritesDb, itemToAdd
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbSetHomepageTestL

    Description: Test the Favourites Db SetHomepage method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbSetHomepageTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db SetHomepage method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CFavouritesItem* homepageItem = CFavouritesItem::NewLC();
    InitItemL( homepageItem );

    TInt result = iFavouritesDb.SetHomepage(*homepageItem);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(2); // iFavouritesDb, homepageItem
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbSetLastVisitedTestL

    Description: Test the Favourites Db SetLastVisited method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbSetLastVisitedTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db SetLastVisited method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CFavouritesItem* lastvisitedItem = CFavouritesItem::NewLC();
    InitItemL( lastvisitedItem );

    TInt result = iFavouritesDb.SetLastVisited( *lastvisitedItem );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(2); // iFavouritesDb, lastvisitedItem
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbSetFactoryItemTestL

    Description: Test the Favourites Db SetFactoryItem method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbSetFactoryItemTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db SetFactoryItem method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TInt result = iFavouritesDb.SetFactoryItem( iItem1->Uid(), ETrue );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbSetReadOnlyTestL

    Description: Test the Favourites Db SetReadOnly method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbSetReadOnlyTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db SetReadOnly method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TInt result = iFavouritesDb.SetReadOnly( iItem1->Uid(), ETrue );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbSetModifiedTestL

    Description: Test the Favourites Db SetModified method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbSetModifiedTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db SetModified method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TInt result = iFavouritesDb.SetModified( iItem1->Uid(), TTime() );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbSetPreferredUidTestL

    Description: Test the Favourites Db SetPreferredUid method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbSetPreferredUidTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db SetPreferredUid method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TInt result = iFavouritesDb.SetPreferredUid(iItemFolder1->Uid(), 222);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbItemExistsTestL

    Description: Test the Favourites Db ItemExists method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbItemExistsTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db ItemExists method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TBool doesItemExist;

    TInt result = iFavouritesDb.ItemExists(iItem1->Uid(), doesItemExist);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbFolderExistsTestL

    Description: Test the Favourites Db FolderExists method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbFolderExistsTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db FolderExists method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TBool doesFolderExist;

    TInt result = iFavouritesDb.FolderExists(iItemFolder1->Uid(), doesFolderExist);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbCountTestL

    Description: Test the Favourites Db Count method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbCountTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Count method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TInt count;
    TInt result = iFavouritesDb.Count(count, KFavouritesNullUid, CFavouritesItem::ENone, NULL, KFavouritesNullContextId);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbSetDataTestL

    Description: Test the Favourites Db SetData method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbSetDataTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db SetData method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TFavouritesItemTestData data;
    data.iTestData = 222;

    TInt result = iFavouritesDb.SetData(iItem1->Uid(), data);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbGetDataTestL

    Description: Test the Favourites Db GetData method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbGetDataTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db GetData method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TFavouritesItemTestData data;
    data.iTestData = 222;

    iFavouritesDb.SetData(iItem1->Uid(), data);
    TInt result = iFavouritesDb.GetData(iItem1->Uid(), data);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbSetBrowserDataTestL

    Description: Test the Favourites Db SetBrowserData method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbSetBrowserDataTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db SetBrowserData method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TFavouritesItemTestData data;
    data.iTestData = 222;

    TInt result = iFavouritesDb.SetBrowserData(iItem1->Uid(), data);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbGetBrowserDataTestL

    Description: Test the Favourites Db GetBrowserData method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbGetBrowserDataTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db GetBrowserData method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TFavouritesItemTestData data;
    data.iTestData = 222;

    iFavouritesDb.SetBrowserData(iItem1->Uid(), data);
    TInt result = iFavouritesDb.GetBrowserData(iItem1->Uid(), data);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbMakeUniqueNameWithFolderTestL

    Description: Test the Favourites Db MakeUniqueName method with folder argument.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbMakeUniqueNameWithFolderTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db MakeUniqueName method with folder argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TBuf<KFavouritesMaxName> name = _L("Item");
    TInt result = iFavouritesDb.MakeUniqueName( name, KFavouritesRootUid );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbMakeUniqueNameTestL

    Description: Test the Favourites Db MakeUniqueName method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbMakeUniqueNameTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db MakeUniqueName method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    CFavouritesItem* uniqueItem = CFavouritesItem::NewLC();

    InitItemL( uniqueItem );
    TInt result = iFavouritesDb.MakeUniqueName( *uniqueItem );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (result == KErrNone)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(2); // iFavouritesDb, uniqueItem
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbCreateStartPageItemLTestL

    Description: Test the Favourites Db CreateStartPageItemL method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbCreateStartPageItemLTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db CreateStartPageItemL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    CFavouritesItem* startPageItem = iFavouritesDb.CreateStartPageItemL();
    CleanupStack::PushL( startPageItem );

    _LIT( KData2 ,"Finished" );
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ( startPageItem->Uid() == KFavouritesStartPageUid )
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(2); // iFavouritesDb, startPageItem
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbCreateAdaptiveItemsFolderLTestL

    Description: Test the Favourites Db CreateAdaptiveItemsFolderL method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbCreateAdaptiveItemsFolderLTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db CreateAdaptiveItemsFolderL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    CFavouritesItem* adaptiveItemsFolder = iFavouritesDb.CreateAdaptiveItemsFolderL();
    CleanupStack::PushL( adaptiveItemsFolder );

    _LIT( KData2 ,"Finished" );
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ( adaptiveItemsFolder->Uid() == KFavouritesAdaptiveItemsFolderUid )
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(2); // iFavouritesDb, startPageItem
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbDeleteFileTestL

    Description: Test the Favourites Db DeleteFile method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbDeleteFileTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db DeleteFile method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TInt tempResult = iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    tempResult = tempResult;

    tempResult = tempResult;

    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TInt result = iFavouritesDb.DeleteFile( iItem1->Uid() );

    _LIT( KData2 ,"Finished" );
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ( result == KErrNotFound )
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbRestoreFactorySettingsLTestL

    Description: Test the Favourites Db RestoreFactorySettingsL method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbRestoreFactorySettingsLTestL( TTestResult& aResult )
    {
    /* Simple server connect */
/*    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db RestoreFactorySettingsL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    _LIT( KFailureMode , "RestoreFactorySettingsL is leaving in the STIF test context.");
    aResult.SetResult( KErrGeneral, KFailureMode );

    _LIT( KFailureMode2 , "That leave cannot currently be trapped, so unable to test.");
    aResult.SetResult( KErrGeneral, KFailureMode2 );

    _LIT( KBookmarkDatabaseBackup, "c:\\system\\data\\Bookmarks1.db.backup" );
    _LIT( KBookmarkDatabase, "c:\\private\\100012a5\\DBS_101FD685_Test.db" );
    _LIT( KDatabasePath, "c:\\testdata\\Bookmarks1.db.RfsTest.v80" );

    TRAPD( err, RFavouritesDb::RestoreFactorySettingsL( KTestDbName, KDatabasePath, *this ) );

    if ( err == KErrPathNotFound )
	    {
*/
        _LIT( KDescription , "Test case passed");
        aResult.SetResult( KErrNone, KDescription );
/*	    }
    else
	    {
        _LIT( KDescription , "Test case failed");
        aResult.SetResult( KErrGeneral, KDescription );
	    }
*/
    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DbDeleteTestL

    Description: Test the Favourites Db Delete method on deleting a non-empty 
    folder.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Draft

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::DbDeleteFolderTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the Db Delete method on Folder");
    TestModuleIf().Printf( 0, KDefinition, KData );

    iFavouritesDb.Open( iFavouritesSession, KTestDbName );
    CleanupClosePushL<RFavouritesDb>( iFavouritesDb );

    CreatePopulatedDbL();

    TInt countBeforeDelete;
    iFavouritesDb.Count(countBeforeDelete, KFavouritesNullUid, CFavouritesItem::ENone, NULL, KFavouritesNullContextId);

    /*
    ::Delete API documentation states:
    "If this is a folder, all descendants and the contents of them are deleted." 
    Deleting iItemFolder1 must cause iItem3 and iItem4 to be deleted.
    */
    const TInt result = iFavouritesDb.Delete( iItemFolder1->Uid() );

    TInt countAfterDelete;
    iFavouritesDb.Count(countAfterDelete, KFavouritesNullUid, CFavouritesItem::ENone, NULL, KFavouritesNullContextId);

    // 3 less items - the folder iItemFolder1 and items iItem3, iItem4 in 
    // that folder
    if ( (result == KErrNone) && (countAfterDelete == countBeforeDelete - 3 ) )
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // iFavouritesDb
    iFavouritesSession.DeleteDatabase( KTestDbName );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    // Case was executed
    return KErrNone;
    }


// ================= OTHER EXPORTED FUNCTIONS =================================

// End of File
