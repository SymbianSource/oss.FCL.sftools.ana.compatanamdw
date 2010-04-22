/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:      ?Description
*
*/



// INCLUDE FILES
#include    "BrCtlBCTestApp.h"
#include    "BrCtlBCTestDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CBrCtlBCTestApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CBrCtlBCTestApp::AppDllUid() const
    {
    return KUidBrCtlBCTest;
    }

// ---------------------------------------------------------
// CDictionaryStore* CBrCtlBCTestApp::OpenIniFileLC(RFs& aFs) const
// overrides CAknApplication::OpenIniFileLC to enable INI file support
// ---------------------------------------------------------
//
CDictionaryStore* CBrCtlBCTestApp::OpenIniFileLC(RFs& aFs) const
{
    return CEikApplication::OpenIniFileLC(aFs);
}
   
// ---------------------------------------------------------
// CBrCtlBCTestApp::CreateDocumentL()
// Creates CBrCtlBCTestDocument object
// ---------------------------------------------------------
//
CApaDocument* CBrCtlBCTestApp::CreateDocumentL()
    {
    return CBrCtlBCTestDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ==============

#include <eikstart.h>

LOCAL_C CApaApplication* NewApplication( )
    {
    return new CBrCtlBCTestApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File  

