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
* This file contains hardcoded module implementation.
*
*/


#include <extendedconnpref.h>
#include "econnprefbc.h"

// -----------------------------------------------------------------------------
// CEConnPrefBc::TEcpbcConstuction
//
// Tests: IMPORT_C TExtendedConnPref();
// -----------------------------------------------------------------------------
//
TInt CEConnPrefBc::TEcpbcConstuction( TTestResult& aResult )
    {
    TInt errorCount( 0 );

    TExtendedConnPref* extConnPref = new TExtendedConnPref();
    if ( !extConnPref )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from TExtendedConnPref(), code <%d>" );
        iLog->Log( KLogStr01, KErrNoMemory );
        }
    delete extConnPref;

    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CEConnPrefBc::TEcpbcSnapPurpose
//
// Tests: IMPORT_C void SetSnapPurpose( CMManager::TSnapPurpose aSnapPurpose );
//        IMPORT_C CMManager::TSnapPurpose SnapPurpose() const;
// -----------------------------------------------------------------------------
//
TInt CEConnPrefBc::TEcpbcSnapPurpose( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    TExtendedConnPref extConnPref;

    extConnPref.SetSnapPurpose( CMManager::ESnapPurposeUnknown );
    if ( extConnPref.SnapPurpose() != CMManager::ESnapPurposeUnknown )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetSnapPurpose(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetSnapPurpose( CMManager::ESnapPurposeInternet );
    if ( extConnPref.SnapPurpose() != CMManager::ESnapPurposeInternet )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetSnapPurpose(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetSnapPurpose( CMManager::ESnapPurposeOperator );
    if ( extConnPref.SnapPurpose() != CMManager::ESnapPurposeOperator )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetSnapPurpose(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetSnapPurpose( CMManager::ESnapPurposeMMS );
    if ( extConnPref.SnapPurpose() != CMManager::ESnapPurposeMMS )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetSnapPurpose(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetSnapPurpose( CMManager::ESnapPurposeIntranet );
    if ( extConnPref.SnapPurpose() != CMManager::ESnapPurposeIntranet )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetSnapPurpose(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }

    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CEConnPrefBc::TEcpbcSnapId
//
// Tests: IMPORT_C void SetSnapId( TUint32 aSnapId );
//        IMPORT_C TUint32 SnapId() const;
// -----------------------------------------------------------------------------
//
TInt CEConnPrefBc::TEcpbcSnapId( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    TExtendedConnPref extConnPref;

    const TUint32 KSnapId01 = 0;
    const TUint32 KSnapId02 = 1;
    const TUint32 KSnapId03 = 5;
    const TUint32 KSnapId04 = 32;

    extConnPref.SetSnapId( KSnapId01 );
    if ( extConnPref.SnapId() != KSnapId01 )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetSnapId(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetSnapId( KSnapId02 );
    if ( extConnPref.SnapId() != KSnapId02 )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetSnapId(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetSnapId( KSnapId03 );
    if ( extConnPref.SnapId() != KSnapId03 )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetSnapId(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetSnapId( KSnapId04 );
    if ( extConnPref.SnapId() != KSnapId04 )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetSnapId(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }

    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CEConnPrefBc::TEcpbcIapId
//
// Tests: IMPORT_C void SetIapId( TUint32 aIapId );
//        IMPORT_C TUint32 IapId() const;
// -----------------------------------------------------------------------------
//
TInt CEConnPrefBc::TEcpbcIapId( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    TExtendedConnPref extConnPref;

    const TUint32 KIapId01 = 0;
    const TUint32 KIapId02 = 1;
    const TUint32 KIapId03 = 5;
    const TUint32 KIapId04 = 32;

    extConnPref.SetIapId( KIapId01 );
    if ( extConnPref.IapId() != KIapId01 )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetIapId(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetIapId( KIapId02 );
    if ( extConnPref.IapId() != KIapId02 )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetIapId(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetIapId( KIapId03 );
    if ( extConnPref.IapId() != KIapId03 )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetIapId(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetIapId( KIapId04 );
    if ( extConnPref.IapId() != KIapId04 )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetIapId(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }

    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CEConnPrefBc::TEcpbcBearerSet
//
// Tests: IMPORT_C void SetBearerSet( TUint32 aBearerSet );
//        IMPORT_C TUint32 BearerSet() const;
// -----------------------------------------------------------------------------
//
TInt CEConnPrefBc::TEcpbcBearerSet( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    TExtendedConnPref extConnPref;

    extConnPref.SetBearerSet( TExtendedConnPref::EExtendedConnBearerUnknown );
    if ( extConnPref.BearerSet() != TExtendedConnPref::EExtendedConnBearerUnknown )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetBearerSet(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetBearerSet( TExtendedConnPref::EExtendedConnBearerCellular );
    if ( extConnPref.BearerSet() != TExtendedConnPref::EExtendedConnBearerCellular )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetBearerSet(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetBearerSet( TExtendedConnPref::EExtendedConnBearerWLAN );
    if ( extConnPref.BearerSet() != TExtendedConnPref::EExtendedConnBearerWLAN )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetBearerSet(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }

    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CEConnPrefBc::TEcpbcNoteBehaviour
//
// Tests: IMPORT_C void SetNoteBehaviour( TUint32 aNoteBehaviour );
//        IMPORT_C TUint32 NoteBehaviour() const;
// -----------------------------------------------------------------------------
//
TInt CEConnPrefBc::TEcpbcNoteBehaviour( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    TExtendedConnPref extConnPref;

    extConnPref.SetNoteBehaviour( TExtendedConnPref::ENoteBehaviourDefault );
    if ( extConnPref.NoteBehaviour() != TExtendedConnPref::ENoteBehaviourDefault )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetNoteBehaviour(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetNoteBehaviour( TExtendedConnPref::ENoteBehaviourConnDisableNotes );
    if ( extConnPref.NoteBehaviour() != TExtendedConnPref::ENoteBehaviourConnDisableNotes )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetNoteBehaviour(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetNoteBehaviour( TExtendedConnPref::ENoteBehaviourConnDisableQueries );
    if ( extConnPref.NoteBehaviour() != TExtendedConnPref::ENoteBehaviourConnDisableQueries )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetNoteBehaviour(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetNoteBehaviour( TExtendedConnPref::ENoteBehaviourConnSilent );
    if ( extConnPref.NoteBehaviour() != TExtendedConnPref::ENoteBehaviourConnSilent )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetNoteBehaviour(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }

    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CEConnPrefBc::TEcpbcDisconnectDialog
//
// Tests: IMPORT_C void SetDisconnectDialog( TBool aEnableDisconnectDialog );
//        IMPORT_C TBool DisconnectDialog() const;
// -----------------------------------------------------------------------------
//
TInt CEConnPrefBc::TEcpbcDisconnectDialog( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    TExtendedConnPref extConnPref;

    extConnPref.SetDisconnectDialog( ETrue );
    if ( !extConnPref.DisconnectDialog() )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetDisconnectDialog(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }

    extConnPref.SetDisconnectDialog( EFalse );
    if ( extConnPref.DisconnectDialog() )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetDisconnectDialog(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }

    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CEConnPrefBc::TEcpbcConnSelectionDialog
//
// Tests: IMPORT_C void SetConnSelectionDialog( TBool aConnSelectionDialog );
//        IMPORT_C TBool ConnSelectionDialog() const;
// -----------------------------------------------------------------------------
//
TInt CEConnPrefBc::TEcpbcConnSelectionDialog( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    TExtendedConnPref extConnPref;

    extConnPref.SetConnSelectionDialog( ETrue );
    if ( !extConnPref.ConnSelectionDialog() )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetConnSelectionDialog(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }

    extConnPref.SetConnSelectionDialog( EFalse );
    if ( extConnPref.ConnSelectionDialog() )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetConnSelectionDialog(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }

    return SetTestCaseResult( aResult, errorCount );
    }

// -----------------------------------------------------------------------------
// CEConnPrefBc::TEcpbcForcedRoaming
//
// Tests: IMPORT_C void SetForcedRoaming( TBool aForcedRoaming );
//        IMPORT_C TBool ForcedRoaming() const;
// -----------------------------------------------------------------------------
//
TInt CEConnPrefBc::TEcpbcForcedRoaming( TTestResult& aResult )
    {
    TInt errorCount( 0 );
    TExtendedConnPref extConnPref;

    extConnPref.SetForcedRoaming( ETrue );
    if ( !extConnPref.ForcedRoaming() )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetForcedRoaming(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }
    extConnPref.SetForcedRoaming( EFalse );
    if ( extConnPref.ForcedRoaming() )
        {
        errorCount++;
        _LIT( KLogStr01, "ERROR from SetForcedRoaming(), code <%d>" );
        iLog->Log( KLogStr01, KErrCorrupt );
        }

    return SetTestCaseResult( aResult, errorCount );
    }


// End of file
