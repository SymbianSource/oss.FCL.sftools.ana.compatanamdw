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

/*
-------------------------------------------------------------------------------

    DESCRIPTION

    This module contains the implementation of CTestModuleDemo class 
    member functions that does the actual tests.

-------------------------------------------------------------------------------
*/

// ============================ MEMBER FUNCTIONS ===============================

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemNewLCTestL

    Description: Test creating a new favourites item with the NewLC method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemNewLCTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Creating item with NewLC method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (item)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemNewLTestL

    Description: Test creating a new favourites item with the NewL method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemNewLTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Creating item with NewL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewL();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (item)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    
	    delete item;
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

    Method: ItemDestructorTestL

    Description: Test destroying an item with the ~CFavouritesItem method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemDestructorTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Destroying item with ~CFavouritesItem method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewL();
    
//    item->~CFavouritesItem();
    
    delete item;

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    _LIT( KDescription , "Test case passed");
    aResult.SetResult( KErrNone, KDescription );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemAssignTestL

    Description: Assigning one item to another with the Assign(=) method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemAssignTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Assigning item with Assign(=) operator");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item1 = CFavouritesItem::NewLC();
    item1->SetNameL( _L("Item1") );
    CFavouritesItem* item2 = CFavouritesItem::NewLC();
    item2->SetNameL( _L("Item2") );

    *item1 = *item2;
    
    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (item1->Name() == item2->Name())
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( 2 );   // item1, item2

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemUidTestL

    Description: Test getting the item's Uid using the Uid method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemUidTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Getting item's Uid with Uid method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TInt itemUid = item->Uid();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (itemUid == 0)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemParentFolderTestL

    Description: Test getting the item's parent folder using the ParentFolder method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemParentFolderTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Getting item's parent folder with ParentFolder method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TInt itemParent = item->ParentFolder();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (itemParent == 0)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemTypeTestL

    Description: Test getting the item's type using the Type method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemTypeTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Getting item's type with Type method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TInt itemType = item->Type();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (itemType == 1)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemNameTestL

    Description: Test getting the item's name using the Name method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemNameTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Getting item's name with Name method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TPtrC itemName = item->Name();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    _LIT( KItemName ,"");
    if (itemName == KItemName)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemUrlTestL

    Description: Test getting the item's url using the Url method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemUrlTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Getting item's url with Url method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TPtrC itemUrl = item->Url();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    _LIT( KItemUrl ,"");
    if (itemUrl == KItemUrl)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemWapApTestL

    Description: Test getting the item's access point using the WapAp method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemWapApTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Getting item's access point with WapAp method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TFavouritesWapAp itemAP = item->WapAp();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (itemAP.IsDefault())
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemUserNameTestL

    Description: Test getting the item's user name using the UserName method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemUserNameTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Getting item's user name with UserName method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TPtrC itemUserName = item->UserName();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    _LIT( KItemUserName ,"");
    if (itemUserName == KItemUserName)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemPasswordTestL

    Description: Test getting the item's password using the Password method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemPasswordTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Getting item's password with Password method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TPtrC itemPassword = item->Password();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    _LIT( KItemPassword ,"");
    if (itemPassword == KItemPassword)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemContextIdTestL

    Description: Test getting the item's context id using the ContextId method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemContextIdTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Getting item's context id with ContextId method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TInt32 itemContextId = item->ContextId();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (itemContextId == 0)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemIsItemTestL

    Description: Test if the item is an item using the IsItem method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemIsItemTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Checking if the item is an item with IsItem method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TBool itemIsItem = item->IsItem();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (itemIsItem)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemIsFolderTestL

    Description: Test if the item is a folder using the IsFolder method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemIsFolderTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Checking if the item is a folder with IsFolder method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TBool itemIsFolder = item->IsFolder();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (!itemIsFolder)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemIsFactoryItemTestL

    Description: Test if the item is a factory item using the IsFactoryItem method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemIsFactoryItemTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Checking if the item is a factory item with IsFactory method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TBool itemIsFactoryItem = item->IsFactoryItem();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (!itemIsFactoryItem)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemIsReadOnlyTestL

    Description: Test if the item is read-only using the IsReadOnly method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemIsReadOnlyTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Checking if the item is read-only item with IsReadOnly method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TBool itemIsReadOnly = item->IsReadOnly();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (!itemIsReadOnly)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemModifiedTestL

    Description: Test getting the last modified time using the Modified method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemModifiedTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Getting the item's last modified time with Modified method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TTime itemModified = item->Modified();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (itemModified != NULL)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemClearLTestL

    Description: Test clearing the item using the ClearL method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemClearLTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Clearing the item with ClearL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    item->SetType(CFavouritesItem::EFolder);
    item->SetNameL( _L("Item Name") );
    item->ClearL();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ((item->Type() == CFavouritesItem::EFolder) || (item->Name() == _L("Item Name")))
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemSetParentFolderTestL

    Description: Test setting the item's parent folder using the SetParentFolder method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemSetParentFolderTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Setting the item's parent folder with SetParentFolder method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    item->SetParentFolder(3);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (item->ParentFolder() == 3)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemSetTypeTestL

    Description: Test setting the item's type using the SetType method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemSetTypeTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Setting the item's type with SetType method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    item->SetType(CFavouritesItem::EFolder);
    
    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (item->Type() == CFavouritesItem::EFolder)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemSetNameLTestL

    Description: Test setting the item's name using the SetNameL method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemSetNameLTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Setting the item's name with SetNameL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    item->SetNameL( _L("Item Name") );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (item->Name() == _L("Item Name"))
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemSetUrlLTestL

    Description: Test setting the item's url using the SetUrlL method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemSetUrlLTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Setting the item's url with SetUrlL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    item->SetUrlL( _L("http://www.nokia.com") );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (item->Url() == _L("http://www.nokia.com"))
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemSetWapApTestL

    Description: Test setting the item's access point using the SetWapAp method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemSetWapApTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Setting the item's access point with SetWapAp method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();

    TFavouritesWapAp accessPoint;
    accessPoint.SetApId( 22 );
    item->SetWapAp( accessPoint );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (item->WapAp().ApId() == 22)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemSetUserNameLTestL

    Description: Test setting the item's user name using the SetUserNameL method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemSetUserNameLTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Setting the item's user name with SetUserNameL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    item->SetUserNameL( _L("New User") );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (item->UserName() == _L("New User"))
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemSetPasswordLTestL

    Description: Test setting the item's password using the SetPasswordL method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemSetPasswordLTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Setting the item's password with SetPasswordL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    item->SetPasswordL( _L("12345") );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (item->Password() == _L("12345"))
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemSetContextIdTestL

    Description: Test setting the item's context id using the SetContextId method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemSetContextIdTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Setting the item's context id with SetContextId method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    item->SetContextId(22);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (item->ContextId() == 22)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemIsHiddenTestL

    Description: Test if the item is hidden using the IsHidden method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/

TInt CFavouritesBCTest::ItemIsHiddenTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Checking if the item is hidden item with IsHidden method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    TBool itemIsHidden = item->IsHidden();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (!itemIsHidden)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: ItemSetHiddenTestL

    Description: Test setting the item's hidden value using the SetHidden method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CFavouritesBCTest::ItemSetHiddenTestL( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Setting the item's hidden value with SetHidden method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CFavouritesItem* item = CFavouritesItem::NewLC();
    
    item->SetHidden(1);

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (item->IsHidden() == 1)
	    {
	    _LIT( KDescription , "Test case passed");
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed");
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( item );

    // Case was executed
    return KErrNone;
    }

// ================= OTHER EXPORTED FUNCTIONS =================================

// End of File
