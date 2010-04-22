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
* for RCmConnectionMethod-class. (STIF harcoded test module).
*
*/


#include <cmmanager.h>
#include <cmpluginpacketdatadef.h>
#include <cmdestination.h>
#include <cmconnectionmethod.h>

#include "cmmgrbc.h"


// -----------------------------------------------------------------------------
// CCmmgrBc::TConnMethodConstructionL
//
// Tests:
// IMPORT_C RCmConnectionMethod()
// IMPORT_C ~RCmConnectionMethod()
// IMPORT_C void Close()
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TConnMethodConstructionL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmConnectionMethod* cmConnMethod = new( ELeave ) RCmConnectionMethod();
    cmConnMethod->Close();
    delete cmConnMethod;

    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TConnMethodCopyConstructionL
//
// Tests:
// IMPORT_C void UpdateL()
// IMPORT_C RCmConnectionMethod( const RCmConnectionMethod& )
// IMPORT_C RCmConnectionMethod CreateCopyL()
// IMPORT_C TBool DeleteL()
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TConnMethodCopyConstructionL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

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
        RCmConnectionMethod connMethod;
        connMethod = cmManager.CreateConnectionMethodL( KUidPacketDataBearerType );
        CleanupClosePushL( connMethod );
        connMethod.SetStringAttributeL( CMManager::ECmName, KCmmgrbcIapName() );
        connMethod.SetStringAttributeL( CMManager::EPacketDataAPName, KCmmgrbcIapAp() );
        connMethod.UpdateL();

        RCmConnectionMethod* connMethod2 = new( ELeave ) RCmConnectionMethod( connMethod );
        connMethod2->Close();
        delete connMethod2;

        RCmConnectionMethod connMethod3;
        connMethod3 = connMethod.CreateCopyL();
        CleanupClosePushL( connMethod3 );
        CleanupStack::PopAndDestroy( &connMethod3 );

        connMethod.DeleteL();
        CleanupStack::PopAndDestroy( &connMethod );
        }

    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TConnMethodSetAttributesL
//
// Tests:
// IMPORT_C void SetIntAttributeL( TUint32, TUint32 )
// IMPORT_C void SetBoolAttributeL( TUint32, TBool )
// IMPORT_C void SetStringAttributeL( TUint32, const TDesC16& )
// IMPORT_C void SetString8AttributeL( TUint32, const TDesC8& )
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TConnMethodSetAttributesL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmConnectionMethod connMethod;
    CleanupClosePushL( connMethod );
    TInt err( KErrNone );

    _LIT16( KCmmgrbcString16, "CmmgrbcTemp16" );
    _LIT8( KCmmgrbcString8, "CmmgrbcTemp8" );

    TRAP( err, connMethod.SetIntAttributeL( 0, 0 ) );
    if ( err != KErrBadHandle )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetIntAttributeL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    TRAP( err, connMethod.SetBoolAttributeL( 0, EFalse ) );
    if ( err != KErrBadHandle )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetBoolAttributeL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    TRAP( err, connMethod.SetStringAttributeL( 0, KCmmgrbcString16() ) );
    if ( err != KErrBadHandle )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetStringAttributeL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    TRAP( err, connMethod.SetString8AttributeL( 0, KCmmgrbcString8() ) );
    if ( err != KErrBadHandle )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetString8AttributeL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    CleanupStack::PopAndDestroy( &connMethod );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TConnMethodGetAttributesL
//
// Tests:
// IMPORT_C TUint32 GetIntAttributeL( TUint32 ) const
// IMPORT_C TBool GetBoolAttributeL( TUint32 ) const
// IMPORT_C HBufC* GetStringAttributeL( TUint32 ) const
// IMPORT_C HBufC8* GetString8AttributeL( const TUint32 ) const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TConnMethodGetAttributesL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmConnectionMethod connMethod;
    CleanupClosePushL( connMethod );
    TInt err( KErrNone );

    TUint32 intValue = 0;
    TBool boolValue = 0;
    HBufC* bufPointer = NULL;
    HBufC8* buf8Pointer = NULL;

    TRAP( err, intValue = connMethod.GetIntAttributeL( 0 ) );
    if ( err != KErrBadHandle )
        {
        intValue = intValue;
        errorCount++;
        _LIT( KLogStr01, "ERROR from GetIntAttributeL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    TRAP( err, boolValue = connMethod.GetBoolAttributeL( 0 ) );
    if ( err != KErrBadHandle )
        {
        boolValue = boolValue;
        errorCount++;
        _LIT( KLogStr01, "ERROR from GetBoolAttributeL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    TRAP( err, bufPointer = connMethod.GetStringAttributeL( 0 ) );
    if ( err != KErrBadHandle )
        {
        bufPointer = bufPointer;
        errorCount++;
        _LIT( KLogStr01, "ERROR from GetStringAttributeL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    TRAP( err, buf8Pointer = connMethod.GetString8AttributeL( 0 ) );
    if ( err != KErrBadHandle )
        {
        buf8Pointer = buf8Pointer;
        errorCount++;
        _LIT( KLogStr01, "ERROR from GetString8AttributeL(), code <%d>" );
        iLog->Log( KLogStr01, err );
        }
    err = KErrNone;

    CleanupStack::PopAndDestroy( &connMethod );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TConnMethodCompareL
//
// Tests:
// IMPORT_C RCmConnectionMethod& operator=( const RCmConnectionMethod& )
// IMPORT_C TBool operator==( RCmConnectionMethod& ) const
// IMPORT_C TBool operator!=( RCmConnectionMethod& ) const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TConnMethodCompareL( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    RCmManager cmManager;
    CleanupClosePushL( cmManager );
    cmManager.OpenL();

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
        RCmConnectionMethod connMethod;
        connMethod = cmManager.CreateConnectionMethodL( KUidPacketDataBearerType );
        CleanupClosePushL( connMethod );
        connMethod.SetStringAttributeL( CMManager::ECmName, KCmmgrbcIapName() );
        connMethod.SetStringAttributeL( CMManager::EPacketDataAPName, KCmmgrbcIapAp() );
        connMethod.UpdateL();

        RCmConnectionMethod connMethod2;
        CleanupClosePushL( connMethod2 );

        connMethod2 = connMethod;

        if ( !( connMethod == connMethod2 ) )
            {
            errorCount++;
            _LIT( KLogStr01, "ERROR from operator==()" );
            iLog->Log( KLogStr01 );
            }

        if ( connMethod != connMethod2 )
            {
            errorCount++;
            _LIT( KLogStr02, "ERROR from operator!=()" );
            iLog->Log( KLogStr02 );
            }

        CleanupStack::PopAndDestroy( &connMethod2 );
        connMethod.DeleteL();
        CleanupStack::PopAndDestroy( &connMethod );
        }

    CleanupStack::PopAndDestroy( &cmManager );
    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CCmmgrBc::TConnMethodAsEmbeddedDestinationL
//
// Tests:
// IMPORT_C RCmDestination DestinationL() const
// -----------------------------------------------------------------------------
//
TInt CCmmgrBc::TConnMethodAsEmbeddedDestinationL( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    _LIT( KCmmgrbcSnapName01, "CmmgrbcTempSnap1" );
    _LIT( KCmmgrbcSnapName02, "CmmgrbcTempSnap2" );

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

    destination1.AddEmbeddedDestinationL( destination2 );
    destination1.UpdateL();
    MyDelay();

    RCmConnectionMethod connectionMethod1;
    CleanupClosePushL( connectionMethod1 );
    connectionMethod1 = destination1.ConnectionMethodL( 0 );

    RCmDestination destination3;
    CleanupClosePushL( destination3 );
    destination3 = connectionMethod1.DestinationL();

    if ( destination2 == destination3 )
        {
        _LIT( KLogStr01, "destinations are the same" );
        iLog->Log( KLogStr01 );
        }
    else
        {
        _LIT( KLogStr01, "destinations are not the same" );
        iLog->Log( KLogStr01 );
        }

    CleanupStack::PopAndDestroy( &destination3 );
    CleanupStack::PopAndDestroy( &connectionMethod1 );

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

// End of file
