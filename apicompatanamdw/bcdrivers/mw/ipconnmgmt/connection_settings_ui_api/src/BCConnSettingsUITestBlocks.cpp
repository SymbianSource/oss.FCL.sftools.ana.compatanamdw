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
#include "BCConnSettingsUITest.h"

#include <coemain.h>
#include <cmapplicationsettingsui.h> 
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CBCConnSettingsUITest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CBCConnSettingsUITest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CBCConnSettingsUITest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CBCConnSettingsUITest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestNewL", CBCConnSettingsUITest::TestNewL ),
        ENTRY( "TestNewLC", CBCConnSettingsUITest::TestNewLC ),
        ENTRY( "TestDelete", CBCConnSettingsUITest::TestDelete ),
        ENTRY( "TestRunApplicationSettings1", CBCConnSettingsUITest::TestRunApplicationSettings1 ),
        ENTRY( "TestRunApplicationSettings2", CBCConnSettingsUITest::TestRunApplicationSettings2 ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CBCConnSettingsUITest::TestRunApplicationSettings1
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CBCConnSettingsUITest::TestRunApplicationSettings1( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KBCConnSettingsUITest, "BCConnSettingsUITest" );
    _LIT( KRunAppSettings, "In RunApplicationSettingsL(TCmSettingSelection)" );
    TestModuleIf().Printf( 0, KBCConnSettingsUITest, KRunAppSettings );

    // Print to log file
    iLog->Log( KRunAppSettings );
    TInt err = KErrNone;
    TCmSettingSelection selection;
    TRAP(err, iSettings->RunApplicationSettingsL(selection));
    
    return err;
    }

// -----------------------------------------------------------------------------
// CBCConnSettingsUITest::TestRunApplicationSettings2
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CBCConnSettingsUITest::TestRunApplicationSettings2( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KBCConnSettingsUITest, "BCConnSettingsUITest" );
    _LIT( KRunAppSettings, "In RunApplicationSettingsL(TCmSettingSelection, TUint, TBearerFilterArray)" );
    TestModuleIf().Printf( 0, KBCConnSettingsUITest, KRunAppSettings );

    // Print to log file
    iLog->Log( KRunAppSettings );
    TInt err = KErrNone;
    TCmSettingSelection selection;
    TUint btField = CMManager::EShowAlwaysAsk;
    TBearerFilterArray array;
    TRAP(err, iSettings->RunApplicationSettingsL(selection, btField, array));

    return err;

    }

// -----------------------------------------------------------------------------
// CBCConnSettingsUITest::TestNewL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CBCConnSettingsUITest::TestNewL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KBCConnSettingsUITest, "BCConnSettingsUITest" );
    _LIT( KNew, "In NewL" );
    TestModuleIf().Printf( 0, KBCConnSettingsUITest, KNew );

    // Print to log file
    iLog->Log( KNew );

    TInt err = KErrNone;
    TRAP(err, iSettings = CCmApplicationSettingsUi::NewL());
//    CCoeEnv::Static()->AppUi()->AddToStackL( iSettings );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CBCConnSettingsUITest::TestNewLC
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CBCConnSettingsUITest::TestNewLC( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KBCConnSettingsUITest, "BCConnSettingsUITest" );
    _LIT( KNew, "In NewLC" );
    TestModuleIf().Printf( 0, KBCConnSettingsUITest, KNew );
    
    // Print to log file
    iLog->Log( KNew );

    TInt err = KErrNone;
    TRAP(err, iSettings = CCmApplicationSettingsUi::NewLC(); CleanupStack::Pop(););
//    CCoeEnv::Static()->AppUi()->AddToStackL( iSettings );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CBCConnSettingsUITest::TestDelete
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CBCConnSettingsUITest::TestDelete( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KBCConnSettingsUITest, "BCConnSettingsUITest" );
    _LIT( KNew, "In Destructor" );
    TestModuleIf().Printf( 0, KBCConnSettingsUITest, KNew );
    
    // Print to log file
    iLog->Log( KNew );

//    CCoeEnv::Static()->AppUi()->RemoveFromStack( iSettings );
    delete iSettings;
    iSettings = NULL;
    
    return KErrNone;
    }

//  [End of File] - Do not remove
