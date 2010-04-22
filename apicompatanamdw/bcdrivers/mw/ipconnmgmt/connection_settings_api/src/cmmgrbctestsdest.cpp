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
* for RCmDestination-class. (STIF harcoded test module).
*
*/


#include <cmmanager.h>
#include <cmmanagerdef.h>
#include <cmpluginpacketdatadef.h>
#include <cmdestination.h>
#include <cmconnectionmethod.h>

#ifndef CMMGRBC_S60_101_SUPPORT
#include <gulicon.h> // For CGulIcon
#endif // CMMGRBC_S60_101_SUPPORT

#include "cmmgrbc.h"

// -----------------------------------------------------------------------------
// CCmmgrBc::TDestConstructionL
//
// Tests:
// IMPORT_C RCmDestination()
// IMPORT_C ~RCmDestination()
// IMPORT_C void Close()
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TDestConstructionL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmDestination* cmDest = new( ELeave ) RCmDestination();
    cmDest->Close();
    delete cmDest;

    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TDestCopyConstructionL
//
// Tests:
// IMPORT_C RCmDestination( const RCmDestination& )
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TDestCopyConstructionL( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    _LIT( KCmmgrbcSnapName01, "CmmgrbcTemp01" );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    RCmDestination destination = cmManager.CreateDestinationL( KCmmgrbcSnapName01() );
    CleanupClosePushL( destination );
    destination.UpdateL();

    RCmDestination* destination2 = new( ELeave ) RCmDestination( destination );
    CleanupStack::PushL( destination2 );
    destination2->Close();
    CleanupStack::Pop( destination2 );
    delete destination2;

    destination.DeleteLD();
    CleanupStack::Pop( &destination );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TDestBasicAttributes
//
// Tests:
// IMPORT_C TInt ConnectionMethodCount() const
// IMPORT_C HBufC* NameLC() const
// IMPORT_C TUint32 Id() const
// IMPORT_C TUint32 ElementId() const
// IMPORT_C TUint32 MetadataL( CMManager::TSnapMetadataField ) const
// IMPORT_C CMManager::TProtectionLevel ProtectionLevel() const
// IMPORT_C TBool IsConnectedL() const
// IMPORT_C TBool IsHidden() const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TDestBasicAttributesL( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    _LIT( KCmmgrbcSnapName01, "CmmgrbcTemp01" );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    RCmDestination destination = cmManager.CreateDestinationL( KCmmgrbcSnapName01() );
    CleanupClosePushL( destination );
    destination.UpdateL();

    TInt count( 0 );
    count = destination.ConnectionMethodCount();
    if ( count > 0 )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from ConnectionMethodCount(), count= %d" );
        iLog->Log( KLogStr01, count );
        }

    HBufC* destinationName = destination.NameLC();
    CleanupStack::PopAndDestroy( destinationName );

    TUint32 id = destination.Id();
    _LIT( KLogStr02, "id = %d" );
    iLog->Log( KLogStr02, id );

    TUint32 elementId = destination.ElementId();
    _LIT( KLogStr03, "element id = %d" );
    iLog->Log( KLogStr03, elementId );

    TUint32 metaData( 0 );
    metaData = metaData;
    metaData = destination.MetadataL( CMManager::ESnapMetadataInternet );
    metaData = destination.MetadataL( CMManager::ESnapMetadataHighlight );
    metaData = destination.MetadataL( CMManager::ESnapMetadataHiddenAgent );
    metaData = destination.MetadataL( CMManager::ESnapMetadataDestinationIsLocalised );
    metaData = destination.MetadataL( CMManager::ESnapMetadataPurpose );

    CMManager::TProtectionLevel protLevel( CMManager::EProtLevel0 );
    protLevel = protLevel;
    protLevel = destination.ProtectionLevel();

    TBool isConnected( EFalse );
    isConnected = isConnected;
    isConnected = destination.IsConnectedL();

    TBool isHidden( EFalse );
    isHidden = isHidden;
    isHidden = destination.IsHidden();

    destination.DeleteLD();
    CleanupStack::Pop( &destination );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TDestSetBasicAttributesL
//
// Tests:
// IMPORT_C void SetNameL( const TDesC& )
// IMPORT_C void SetIconL( TUint32 )
// IMPORT_C void SetMetadataL( CMManager::TSnapMetadataField, aValue )
// IMPORT_C void SetProtectionL( CMManager::TProtectionLevel )
// IMPORT_C void SetHiddenL( TBool )
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TDestSetBasicAttributesL( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    _LIT( KCmmgrbcSnapName01, "CmmgrbcTemp01" );
    _LIT( KCmmgrbcSnapName02, "CmmgrbcTemp02" );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    RCmDestination destination = cmManager.CreateDestinationL( KCmmgrbcSnapName01() );
    CleanupClosePushL( destination );
    destination.UpdateL();

    destination.SetNameL( KCmmgrbcSnapName02() );
    TRAPD( err, destination.SetIconL( 1 ) );
    if ( err )
        {
        _LIT( KLogStr01, "LEAVE from SetIconL(id) <%d>" );
        iLog->Log( KLogStr01, err );
        }
    else
        {
        _LIT( KLogStr01, "No leave from SetIconL(id)" );
        iLog->Log( KLogStr01 );
        }
    destination.SetMetadataL( CMManager::ESnapMetadataHighlight, EFalse );
    destination.SetMetadataL( CMManager::ESnapMetadataHiddenAgent, EFalse );
    destination.SetMetadataL( CMManager::ESnapMetadataDestinationIsLocalised, 0 );
    destination.SetMetadataL( CMManager::ESnapMetadataPurpose, 0 );
    destination.SetProtectionL( CMManager::EProtLevel0 );
    destination.SetHiddenL( EFalse );

    destination.DeleteLD();
    CleanupStack::Pop( &destination );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TDestCompareL
//
// Tests:
// IMPORT_C void UpdateL()
// IMPORT_C RCmDestination& operator=( const RCmDestination& )
// IMPORT_C TBool operator==( const RCmDestination& ) const
// IMPORT_C TBool operator!=( const RCmDestination& ) const
// IMPORT_C void DeleteLD()
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TDestCompareL( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    _LIT( KCmmgrbcSnapName01, "CmmgrbcTemp01" );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    RCmDestination destination = cmManager.CreateDestinationL( KCmmgrbcSnapName01() );
    CleanupClosePushL( destination );
    destination.UpdateL();
    TUint32 destinationId = destination.Id();

    RCmDestination destination2;
    CleanupClosePushL( destination2 );
    destination2 = destination;

    if ( !( destination == destination2 ) )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from operator==()" );
        iLog->Log( KLogStr01 );
        }

    if ( destination != destination2 )
        {
        errorCount++;
        _LIT( KLogStr02, "ERROR from operator!=()" );
        iLog->Log( KLogStr02 );
        }

    CleanupStack::PopAndDestroy( &destination2 );
    destination.DeleteLD();
    CleanupStack::Pop( &destination );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TDestCreateConnMethodsL
//
// Tests:
// IMPORT_C RCmConnectionMethod CreateConnectionMethodL( TUint32 )
// IMPORT_C RCmConnectionMethod CreateConnectionMethodL( TUint32, TUint32 )
// IMPORT_C RCmConnectionMethod ConnectionMethodByIDL( TInt ) const
// IMPORT_C RCmConnectionMethod ConnectionMethodL( TInt ) const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TDestCreateAndOpenConnMethodsL( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    _LIT( KCmmgrbcSnapName01, "CmmgrbcTemp01" );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    // Create destination
    RCmDestination destination = cmManager.CreateDestinationL( KCmmgrbcSnapName01() );
    CleanupClosePushL( destination );
    destination.UpdateL();

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
        _LIT( KCmmgrbcIapName, "CmmgrbcTempIap" );
        _LIT( KCmmgrbcIapAp, "internet" );

        // Create a connection method
        RCmConnectionMethod connectionMethod1;
        connectionMethod1 = destination.CreateConnectionMethodL( KUidPacketDataBearerType );
        CleanupClosePushL( connectionMethod1 );
        connectionMethod1.SetStringAttributeL( CMManager::ECmName, KCmmgrbcIapName() );
        connectionMethod1.SetStringAttributeL( CMManager::EPacketDataAPName, KCmmgrbcIapAp() );
        destination.UpdateL();
        TUint32 id1 = connectionMethod1.GetIntAttributeL( CMManager::ECmIapId );

        // Create connection method with existing id, should fail
        TInt err1( KErrNone );
        TInt err2( KErrNone );
        RCmConnectionMethod connectionMethod2;
        TRAP( err1, connectionMethod2 = destination.CreateConnectionMethodL( KUidPacketDataBearerType, id1 ) );
        CleanupClosePushL( connectionMethod2 );
        TRAP( err2, destination.UpdateL() );
        if ( err1 != KErrAlreadyExists && err2 != KErrAlreadyExists )
            {
            errorCount++;
            _LIT( KLogStr01, "ERROR (no leave) from CreateConnectionMethodL(bearer,id), codes <%d> <%d>" );
            iLog->Log( KLogStr01, err1, err2 );
            }
        connectionMethod2.Close();
        CleanupStack::PopAndDestroy( &connectionMethod2 );

        // Open connection method with id
        RCmConnectionMethod connectionMethod3 = destination.ConnectionMethodByIDL( id1 );
        CleanupClosePushL( connectionMethod3 );
        CleanupStack::PopAndDestroy( &connectionMethod3 );

        // Open connection method with index
        RCmConnectionMethod connectionMethod4 = destination.ConnectionMethodL( 0 );
        CleanupClosePushL( connectionMethod4 );
        CleanupStack::PopAndDestroy( &connectionMethod4 );

        CleanupStack::PopAndDestroy( &connectionMethod1 );
        }

    // Remove the created destination
    destination.DeleteLD();
    CleanupStack::Pop( &destination );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TDestPriorityL
//
// Tests:
// IMPORT_C TUint PriorityL( const RCmConnectionMethod& ) const
// IMPORT_C void ModifyPriorityL( RCmConnectionMethod&, TUint )
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TDestPriorityL( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    _LIT( KCmmgrbcSnapName01, "CmmgrbcTempSnap" );
    _LIT( KCmmgrbcIapName1, "CmmgrbcTempIap1" );
    _LIT( KCmmgrbcIapName2, "CmmgrbcTempIap2" );
    _LIT( KCmmgrbcIapAp, "internet" );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    // Create destination
    RCmDestination destination = cmManager.CreateDestinationL( KCmmgrbcSnapName01() );
    CleanupClosePushL( destination );
    destination.UpdateL();
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
        // Create 2 connection methods inside the SNAP
        RCmConnectionMethod connectionMethod1;
        connectionMethod1 = destination.CreateConnectionMethodL( KUidPacketDataBearerType );
        CleanupClosePushL( connectionMethod1 );
        connectionMethod1.SetStringAttributeL( CMManager::ECmName, KCmmgrbcIapName1() );
        connectionMethod1.SetStringAttributeL( CMManager::EPacketDataAPName, KCmmgrbcIapAp() );

        RCmConnectionMethod connectionMethod2;
        connectionMethod2 = destination.CreateConnectionMethodL( KUidPacketDataBearerType );
        CleanupClosePushL( connectionMethod2 );
        connectionMethod2.SetStringAttributeL( CMManager::ECmName, KCmmgrbcIapName2() );
        connectionMethod2.SetStringAttributeL( CMManager::EPacketDataAPName, KCmmgrbcIapAp() );

        destination.UpdateL();
        MyDelay();

        _LIT( KLogStr01, "Priorities are: < %d >< %d >" );
        TUint prio1( 0 );
        TUint prio2( 0 );

        prio1 = destination.PriorityL( connectionMethod1 );
        prio2 = destination.PriorityL( connectionMethod2 );
        iLog->Log( KLogStr01, prio1, prio2 );

        destination.ModifyPriorityL( connectionMethod2, 0 );
        destination.UpdateL();
        MyDelay();

        prio1 = destination.PriorityL( connectionMethod1 );
        prio2 = destination.PriorityL( connectionMethod2 );
        iLog->Log( KLogStr01, prio1, prio2 );

        CleanupStack::PopAndDestroy( &connectionMethod2 );
        CleanupStack::PopAndDestroy( &connectionMethod1 );
        }

    // Remove the created destination
    destination.DeleteLD();
    CleanupStack::Pop( &destination );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TDestAddRemoveConnMethodsL
//
// Tests:
// IMPORT_C TInt AddConnectionMethodL( RCmConnectionMethod )
// IMPORT_C TInt AddEmbeddedDestinationL( const RCmDestination& )
// IMPORT_C void DeleteConnectionMethodL( RCmConnectionMethod& )
// IMPORT_C void RemoveConnectionMethodL( RCmConnectionMethod )
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TDestAddRemoveConnMethodsL( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    _LIT( KCmmgrbcSnapName01, "CmmgrbcTempSnap1" );
    _LIT( KCmmgrbcSnapName02, "CmmgrbcTempSnap2" );
    _LIT( KCmmgrbcIapName1, "CmmgrbcTempIap1" );
    _LIT( KCmmgrbcIapName2, "CmmgrbcTempIap2" );
    _LIT( KCmmgrbcIapAp, "internet" );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    // Create 2 destinations
    RCmDestination destination1 = cmManager.CreateDestinationL( KCmmgrbcSnapName01() );
    CleanupClosePushL( destination1 );
    destination1.UpdateL();
    MyDelay();

    RCmDestination destination2 = cmManager.CreateDestinationL( KCmmgrbcSnapName02() );
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
        // Create 2 connection methods
        RCmConnectionMethod connectionMethod1;
        connectionMethod1 = cmManager.CreateConnectionMethodL( KUidPacketDataBearerType );
        CleanupClosePushL( connectionMethod1 );
        connectionMethod1.SetStringAttributeL( CMManager::ECmName, KCmmgrbcIapName1() );
        connectionMethod1.SetStringAttributeL( CMManager::EPacketDataAPName, KCmmgrbcIapAp() );
        connectionMethod1.UpdateL();
        MyDelay();

        RCmConnectionMethod connectionMethod2;
        connectionMethod2 = cmManager.CreateConnectionMethodL( KUidPacketDataBearerType );
        CleanupClosePushL( connectionMethod2 );
        connectionMethod2.SetStringAttributeL( CMManager::ECmName, KCmmgrbcIapName2() );
        connectionMethod2.SetStringAttributeL( CMManager::EPacketDataAPName, KCmmgrbcIapAp() );
        connectionMethod2.UpdateL();
        MyDelay();

        destination1.AddConnectionMethodL( connectionMethod1 );
        destination1.AddConnectionMethodL( connectionMethod2 );

        destination1.AddEmbeddedDestinationL( destination2 );
        destination1.UpdateL();
        MyDelay();

        destination1.DeleteConnectionMethodL( connectionMethod2 );
        destination1.RemoveConnectionMethodL( connectionMethod1 );
        destination1.UpdateL();
        MyDelay();

        connectionMethod1.DeleteL();
        MyDelay();

        CleanupStack::PopAndDestroy( &connectionMethod2 );
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
// CCmmgrBc::TDestIconL
//
// Tests:
// IMPORT_C CGulIcon* IconL() const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TDestIconL( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    _LIT( KCmmgrbcSnapName01, "CmmgrbcTempSnap" );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    RCmDestination destination = cmManager.CreateDestinationL( KCmmgrbcSnapName01() );
    CleanupClosePushL( destination );
    destination.UpdateL();

    CGulIcon* p;
    p = NULL;
    TRAPD( err, p = destination.IconL() );
    if ( err )
        {
        _LIT( KLogStr01, "LEAVE from IconL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    else
        {
        _LIT( KLogStr01, "No LEAVE from IconL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    delete p;

    destination.DeleteLD();
    CleanupStack::Pop( &destination );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }
#endif

// -----------------------------------------------------------------------------
// CCmmgrBc::TDestTemp01L
//
// ID fail test
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TDestTemp01L( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    _LIT( KCmmgrbcSnapName01, "IdFailSnap" );
    _LIT( KCmmgrbcIapName, "IdFailIap" );
    _LIT( KCmmgrbcIapAp, "internet" );

    TInt temp( 0 );
    _LIT( KLogStr99, "mark %d" );
    iLog->Log( KLogStr99, ++temp );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

    // Create destination
    RCmDestination destination = cmManager.CreateDestinationL( KCmmgrbcSnapName01() );
    CleanupClosePushL( destination );
    destination.UpdateL();

    // Create a connection method
    RCmConnectionMethod connectionMethod1;
    connectionMethod1 = destination.CreateConnectionMethodL( KUidPacketDataBearerType );
    CleanupClosePushL( connectionMethod1 );
    connectionMethod1.SetStringAttributeL( CMManager::ECmName, KCmmgrbcIapName() );
    connectionMethod1.SetStringAttributeL( CMManager::EPacketDataAPName, KCmmgrbcIapAp() );
    destination.UpdateL();
    TUint32 id1 = connectionMethod1.GetIntAttributeL( CMManager::ECmIapId );

    // Create connection method with existing id, should fail
    TInt err( KErrNone );
    RCmConnectionMethod connectionMethod2;
    connectionMethod2 = destination.CreateConnectionMethodL( KUidPacketDataBearerType, id1 );
    CleanupClosePushL( connectionMethod2 );
    connectionMethod2.SetStringAttributeL( CMManager::ECmName, KCmmgrbcIapName() );
    connectionMethod2.SetStringAttributeL( CMManager::EPacketDataAPName, KCmmgrbcIapAp() );
    TRAP( err, destination.UpdateL() );
    if ( err != KErrAlreadyExists )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR (no leave) from CreateConnectionMethodL(bearer,id), codes <%d> <%d>" );
        iLog->Log( KLogStr01, err, err );
        }
    connectionMethod2.Close();
    CleanupStack::PopAndDestroy( &connectionMethod2 );
    CleanupStack::PopAndDestroy( &connectionMethod1 );

    // Remove the created destination
    _LIT( KLogStr02, "Calling DeleteLD()" );
    iLog->Log( KLogStr99, ++temp );
    iLog->Log( KLogStr02 );
    destination.DeleteLD();
    iLog->Log( KLogStr99, ++temp );
    CleanupStack::Pop( &destination );
    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// End of file
