/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* This file contains implementation of binary compability test cases
* for RCmManager-class. (STIF harcoded test module).
*
*/


#include <cmmanager.h>
#include <cmmanagerdef.h>
#include <cmgenconnsettings.h>
#include <cmdestination.h>
#include <cmconnectionmethod.h>
#include <cmpluginpacketdatadef.h>

#ifndef CMMGRBC_S60_101_SUPPORT
#include <gulicon.h> // For CGulIcon
#endif // CMMGRBC_S60_101_SUPPORT

#include "cmmgrbc.h"

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerConstructionL
//
// Tests:
// inline RCmManager()
// IMPORT_C void OpenL()
// IMPORT_C void Close()
// IMPORT_C void OpenLC()
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerConstructionL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager* cmManager = new( ELeave ) RCmManager();
    CleanupStack::PushL( cmManager );

    cmManager->OpenL();
    cmManager->Close();

    CleanupStack::Pop( cmManager );
    cmManager->OpenLC();
    CleanupStack::PopAndDestroy( cmManager );

    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerCreateTablesAndOpenL
//
// Tests:
// IMPORT_C void CreateTablesAndOpenL()
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerCreateTablesAndOpenL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.CreateTablesAndOpenL();

    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerBearerPriorityArray
//
// Tests:
// IMPORT_C void BearerPriorityArrayL( RArray<TBearerPriority>& ) const
// IMPORT_C void UpdateBearerPriorityArrayL( const RArray<TBearerPriority>& )
// IMPORT_C void CleanupGlobalPriorityArray( RArray<TBearerPriority>& ) const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerBearerPriorityArrayL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    RArray<TBearerPriority> array;
    CleanupClosePushL( array );
    cmManager.BearerPriorityArrayL( array );
    cmManager.UpdateBearerPriorityArrayL( array );
    cmManager.CleanupGlobalPriorityArray( array );
    CleanupStack::PopAndDestroy( &array );

    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerDefConnSettingsL
//
// Tests:
// IMPORT_C void ReadDefConnL( TCmDefConnValue& )
// IMPORT_C void WriteDefConnL( const TCmDefConnValue& )
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerDefConnSettingsL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    TCmDefConnValue defConn;
    cmManager.ReadDefConnL( defConn );
    cmManager.WriteDefConnL( defConn );

    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

#ifdef CMMGRBC_S60_092_SUPPORT
// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerGenConnSettingsL
//
// Tests:
// IMPORT_C void ReadGenConnSettingsL( TCmGenConnSettings& )
// IMPORT_C void WriteGenConnSettingsL( const TCmGenConnSettings& )
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerGenConnSettingsL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    TCmGenConnSettings genConnSettings;
    cmManager.ReadGenConnSettingsL( genConnSettings );
    cmManager.WriteGenConnSettingsL( genConnSettings );

    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }
#endif // CMMGRBC_S60_092_SUPPORT

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerEasyWlanIdL
//
// Tests:
// IMPORT_C TUint32 EasyWlanIdL() const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerEasyWlanIdL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    TUint32 id = cmManager.EasyWlanIdL();

    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerGetBearerInfoL
//
// Tests:
// IMPORT_C TUint32 GetBearerInfoIntL( TUint32, TUint32 ) const
// IMPORT_C TBool GetBearerInfoBoolL( TUint32, TUint32 ) const
// IMPORT_C HBufC* GetBearerInfoStringL( TUint32, TUint32 ) const
// IMPORT_C HBufC8* GetBearerInfoString8L( TUint32, TUint32 ) const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerGetBearerInfoL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    TInt err( KErrNone );
    TUint32 intValue = 0;
    TBool boolValue = 0;
    HBufC* bufPointer = NULL;
    HBufC8* buf8Pointer = NULL;

    TRAP( err, intValue = cmManager.GetBearerInfoIntL( 0, 0 ) );
    if ( err != KErrNotSupported )
        {
        intValue = intValue;
        errorCount++;
        _LIT( KLogStr01, "ERROR from GetBearerInfoIntL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    TRAP( err, boolValue = cmManager.GetBearerInfoBoolL( 0, 0 ) );
    if ( err != KErrNotSupported )
        {
        boolValue = boolValue;
        errorCount++;
        _LIT( KLogStr01, "ERROR from GetBearerInfoBoolL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    TRAP( err, bufPointer = cmManager.GetBearerInfoStringL( 0, 0 ) );
    if ( err != KErrNotSupported )
        {
        bufPointer = bufPointer;
        errorCount++;
        _LIT( KLogStr01, "ERROR from GetBearerInfoStringL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    TRAP( err, buf8Pointer = cmManager.GetBearerInfoString8L( 0, 0 ) );
    if ( err != KErrNotSupported )
        {
        buf8Pointer = buf8Pointer;
        errorCount++;
        _LIT( KLogStr01, "ERROR from GetBearerInfoString8L(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerGetConnMethodInfoL
//
// Tests:
// IMPORT_C TUint32 GetConnectionMethodInfoIntL( TUint32, TUint32 ) const
// IMPORT_C TBool GetConnectionMethodInfoBoolL( TUint32, TUint32 ) const
// IMPORT_C HBufC* GetConnectionMethodInfoStringL( TUint32, TUint32 ) const
// IMPORT_C HBufC8* GetConnectionMethodInfoString8L( TUint32, TUint32 ) const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerGetConnMethodInfoL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    TInt err( KErrNone );
    TUint32 intValue = 0;
    TBool boolValue = 0;
    HBufC* bufPointer = NULL;
    HBufC8* buf8Pointer = NULL;

    TRAP( err, intValue = cmManager.GetConnectionMethodInfoIntL( 0, 0 ) );
    if ( err != KErrNotFound )
        {
        intValue = intValue;
        errorCount++;
        _LIT( KLogStr01, "ERROR from GetConnectionMethodInfoIntL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    TRAP( err, boolValue = cmManager.GetConnectionMethodInfoBoolL( 0, 0 ) );
    if ( err != KErrNotFound )
        {
        boolValue = boolValue;
        errorCount++;
        _LIT( KLogStr01, "ERROR from GetConnectionMethodInfoBoolL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    TRAP( err, bufPointer = cmManager.GetConnectionMethodInfoStringL( 0, 0 ) );
    if ( err != KErrNotFound )
        {
        bufPointer = bufPointer;
        errorCount++;
        _LIT( KLogStr01, "ERROR from GetConnectionMethodInfoStringL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    TRAP( err, buf8Pointer = cmManager.GetConnectionMethodInfoString8L( 0, 0 ) );
    if ( err != KErrNotFound )
        {
        buf8Pointer = buf8Pointer;
        errorCount++;
        _LIT( KLogStr01, "ERROR from GetConnectionMethodInfoString8L(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerAllDestinationsL
//
// Tests:
// IMPORT_C void AllDestinationsL( RArray<TUint32>& ) const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerAllDestinationsL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    RArray<TUint32> idArray;
    CleanupClosePushL( idArray );
    cmManager.AllDestinationsL( idArray );

    CleanupStack::PopAndDestroy( &idArray );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerAllConnMethodsL
//
// Tests:
// IMPORT_C void ConnectionMethodL( RArray<TUint32>&, TBool, TBool, TBool ) const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerAllConnMethodsL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    RArray<TUint32> idArray;
    CleanupClosePushL( idArray );
    cmManager.ConnectionMethodL( idArray, EFalse, EFalse, ETrue );

    CleanupStack::PopAndDestroy( &idArray );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerSupportedBearersL
//
// Tests:
// IMPORT_C void SupportedBearersL( RArray<TUint32>& ) const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerSupportedBearersL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    RArray<TUint32> bearerArray;
    CleanupClosePushL( bearerArray );
    cmManager.SupportedBearersL( bearerArray );

    CleanupStack::PopAndDestroy( &bearerArray );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerCreateAndOpenDestinationsL
//
// Tests:
// IMPORT_C RCmDestination CreateDestinationL( const TDesC& )
// IMPORT_C RCmDestination CreateDestinationL( const TDesC&, TUint32 )
// IMPORT_C RCmDestination DestinationL( TUint32 ) const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerCreateAndOpenDestinationsL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    _LIT( KCmmgrbcSnapName01, "CmmgrbcTemp01" );
    _LIT( KCmmgrbcSnapName02, "CmmgrbcTemp02" );

    RCmDestination destination = cmManager.CreateDestinationL( KCmmgrbcSnapName01() );
    CleanupClosePushL( destination );
    destination.UpdateL();
    TUint32 destinationId = destination.Id();
    CleanupStack::PopAndDestroy( &destination );

    TInt err( KErrNone );
    RCmDestination destination2;
    TRAP( err, destination2 = cmManager.CreateDestinationL( KCmmgrbcSnapName02(), destinationId ) );
    CleanupClosePushL( destination2 );
    if ( err != KErrAlreadyExists )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from CreateDestinationL(name,id), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    CleanupStack::PopAndDestroy( &destination2 );

    RCmDestination destination3 = cmManager.DestinationL( destinationId );
    CleanupClosePushL( destination3 );
    destination3.DeleteLD();
    CleanupStack::Pop( &destination3 );

    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerCreateAndOpenConnMethodsL
//
// Tests:
// IMPORT_C RCmConnectionMethod CreateConnectionMethodL( TUint32 )
// IMPORT_C RCmConnectionMethod CreateConnectionMethodL( TUint32, TUint32 )
// IMPORT_C RCmConnectionMethod ConnectionMethodL( TUint32 ) const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerCreateAndOpenConnMethodsL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    TInt err( KErrNone );
    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    RCmConnectionMethod connMethod1;
    TRAP( err, connMethod1 = cmManager.CreateConnectionMethodL( 0 ) );
    CleanupClosePushL( connMethod1 );
    if ( err != KErrArgument )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from CreateConnectionMethodL(bearer), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;
    CleanupStack::PopAndDestroy( &connMethod1 );

    RCmConnectionMethod connMethod2;
    TRAP( err, connMethod2 = cmManager.CreateConnectionMethodL( 0, 1 ) );
    CleanupClosePushL( connMethod2 );
    if ( err != KErrArgument )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from CreateConnectionMethodL(bearer,id), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;
    CleanupStack::PopAndDestroy( &connMethod2 );

    RArray<TUint32> idArray;
    CleanupClosePushL( idArray );
    cmManager.ConnectionMethodL( idArray, EFalse, EFalse, ETrue );
    if ( idArray.Count() > 0 )
        {
        _LIT( KLogStr02, "id = %d" );
        for ( TInt i = 0; i < idArray.Count(); i++ )
            {
            iLog->Log( KLogStr02, idArray[i] );
            }
        RCmConnectionMethod connMethod3;
        connMethod3 = cmManager.ConnectionMethodL( idArray[idArray.Count()-1] );
        CleanupClosePushL( connMethod3 );
        CleanupStack::PopAndDestroy( &connMethod3 );
        }
    else
        {
        RCmConnectionMethod connMethod3;
        TRAP( err, connMethod3 = cmManager.ConnectionMethodL( 1 ) );
        CleanupClosePushL( connMethod3 );
        if ( err != KErrNotFound )
            {
            errorCount++;
            _LIT( KLogStr01, "ERROR from ConnectionMethodL(id), code <%d>" );
            iLog->Log( KLogStr01, err );
            }
        err = KErrNone;
        CleanupStack::PopAndDestroy( &connMethod3 );
        }
    CleanupStack::PopAndDestroy( &idArray );

    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerCopyAndRemoveAllConnMethodL
//
// Tests:
// IMPORT_C TInt CopyConnectionMethodL( RCmDestination&, RCmConnectionMethod& )
// IMPORT_C void RemoveAllReferencesL( RCmConnectionMethod& )
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerCopyAndRemoveAllConnMethodL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    _LIT( KCmmgrbcSnapName01, "CmmgrbcTempSnap1" );
    _LIT( KCmmgrbcSnapName02, "CmmgrbcTempSnap2" );
    _LIT( KCmmgrbcIapName1, "CmmgrbcTempIap1" );
    _LIT( KCmmgrbcIapAp, "internet" );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    // Create 2 destinations
    RCmDestination destination1;
    destination1 = cmManager.CreateDestinationL( KCmmgrbcSnapName01() );
    CleanupClosePushL( destination1 );
    destination1.UpdateL();
    MyDelay();

    RCmDestination destination2;
    destination2 = cmManager.CreateDestinationL( KCmmgrbcSnapName02() );
    CleanupClosePushL( destination2 );
    destination2.UpdateL();
    MyDelay();

    // Check supported bearers. If packet data bearer is not supported, test
    // can't be executed.
    // Since packet data should always be supported, fail the test so the cause
    // can be investigated.
    RArray<TUint32> bearerArray;
    CleanupClosePushL( bearerArray );
    cmManager.SupportedBearersL( bearerArray );

    TBool packetDataSupported( EFalse );
    for ( TInt i = 0; i < bearerArray.Count(); i++ )
        {
        if ( bearerArray[i] == KUidPacketDataBearerType )
            {
            packetDataSupported = ETrue;
            }
        }
    CleanupStack::PopAndDestroy( &bearerArray );

    if ( !packetDataSupported )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR: Packet data bearer is unsupported. Test stopped" );
        iLog->Log( KLogStr01 );
        }
    else
        {
        // Create a connection method
        RCmConnectionMethod connectionMethod1;
        connectionMethod1 = destination1.CreateConnectionMethodL( KUidPacketDataBearerType );
        CleanupClosePushL( connectionMethod1 );
        connectionMethod1.SetStringAttributeL( CMManager::ECmName, KCmmgrbcIapName1() );
        connectionMethod1.SetStringAttributeL( CMManager::EPacketDataAPName, KCmmgrbcIapAp() );
        destination1.UpdateL();
        MyDelay();

        cmManager.CopyConnectionMethodL( destination2, connectionMethod1 );
        MyDelay();
        cmManager.RemoveAllReferencesL( connectionMethod1 );
        MyDelay();

        connectionMethod1.DeleteL();
        MyDelay();
        CleanupStack::PopAndDestroy( &connectionMethod1 );
        }

    // Remove the created destinations
    destination1.DeleteLD();
    MyDelay();
    destination2.DeleteLD();
    MyDelay();

    CleanupStack::Pop( &destination2 );
    CleanupStack::Pop( &destination1 );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerMoveAndRemoveConnMethodL
//
// Tests:
// IMPORT_C TInt MoveConnectionMethodL( RCmDestination&, RCmDestination&, RCmConnectionMethod& )
// IMPORT_C void RemoveConnectionMethodL( RCmDestination&, RCmConnectionMethod& )
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerMoveAndRemoveConnMethodL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    _LIT( KCmmgrbcSnapName01, "CmmgrbcTempSnap1" );
    _LIT( KCmmgrbcSnapName02, "CmmgrbcTempSnap2" );
    _LIT( KCmmgrbcIapName1, "CmmgrbcTempIap1" );
    _LIT( KCmmgrbcIapAp, "internet" );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    // Create 2 destinations
    RCmDestination destination1;
    destination1 = cmManager.CreateDestinationL( KCmmgrbcSnapName01() );
    CleanupClosePushL( destination1 );
    destination1.UpdateL();
    MyDelay();

    RCmDestination destination2;
    destination2 = cmManager.CreateDestinationL( KCmmgrbcSnapName02() );
    CleanupClosePushL( destination2 );
    destination2.UpdateL();
    MyDelay();

    // Check supported bearers. If packet data bearer is not supported, test
    // can't be executed.
    // Since packet data should always be supported, fail the test so the cause
    // can be investigated.
    RArray<TUint32> bearerArray;
    CleanupClosePushL( bearerArray );
    cmManager.SupportedBearersL( bearerArray );

    TBool packetDataSupported( EFalse );
    for ( TInt i = 0; i < bearerArray.Count(); i++ )
        {
        if ( bearerArray[i] == KUidPacketDataBearerType )
            {
            packetDataSupported = ETrue;
            }
        }
    CleanupStack::PopAndDestroy( &bearerArray );

    if ( !packetDataSupported )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR: Packet data bearer is unsupported. Test stopped" );
        iLog->Log( KLogStr01 );
        }
    else
        {
        // Create a connection method
        RCmConnectionMethod connectionMethod1;
        connectionMethod1 = destination1.CreateConnectionMethodL( KUidPacketDataBearerType );
        CleanupClosePushL( connectionMethod1 );
        connectionMethod1.SetStringAttributeL( CMManager::ECmName, KCmmgrbcIapName1() );
        connectionMethod1.SetStringAttributeL( CMManager::EPacketDataAPName, KCmmgrbcIapAp() );
        destination1.UpdateL();
        MyDelay();

        cmManager.MoveConnectionMethodL( destination1, destination2, connectionMethod1 );
        MyDelay();
        cmManager.RemoveConnectionMethodL( destination2, connectionMethod1 );
        MyDelay();

        connectionMethod1.DeleteL();
        MyDelay();
        CleanupStack::PopAndDestroy( &connectionMethod1 );
        }

    // Remove the created destinations
    destination1.DeleteLD();
    MyDelay();
    destination2.DeleteLD();
    MyDelay();

    CleanupStack::Pop( &destination2 );
    CleanupStack::Pop( &destination1 );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

#ifndef CMMGRBC_S60_101_SUPPORT
// -----------------------------------------------------------------------------
// CCmmgrBc::TCmManagerUncategorizedIconL
//
// Tests:
// IMPORT_C CGulIcon* UncategorizedIconL() const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TCmManagerUncategorizedIconL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    CGulIcon* p;
    p = NULL;
    TRAPD( err, p = cmManager.UncategorizedIconL() );
    if ( err )
        {
        _LIT( KLogStr01, "LEAVE from UncategorizedIconL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    else
        {
        _LIT( KLogStr01, "No LEAVE from UncategorizedIconL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    delete p;

    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }
#endif // CMMGRBC_S60_101_SUPPORT

// End of file
