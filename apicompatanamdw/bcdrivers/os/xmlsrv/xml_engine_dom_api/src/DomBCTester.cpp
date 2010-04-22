/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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



// INCLUDE FILES
#include "DomBCTester.h"
#include "BCTesterDefs.h"
#include <Stiftestinterface.h>

// EXTERNAL DATA STRUCTURES

// EXTERNAL FUNCTION PROTOTYPES

// CONSTANTS

// MACROS

// LOCAL CONSTANTS AND MACROS

// MODULE DATA STRUCTURES

// LOCAL FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CDomBCTester::CDomBCTester
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CDomBCTester::CDomBCTester(CTestModuleIf& aTestModuleIf )
:CScriptBase( aTestModuleIf )
{
}

// -----------------------------------------------------------------------------
// CDomBCTester::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDomBCTester::ConstructL()
{
    iLog = CStifLogger::NewL( KXML_TestLogPath,
                              KXML_TestLogFile,
                              CStifLogger::ETxt,
                              CStifLogger::EFile,
                              EFalse );

    DOM_impl.OpenL( );
    TInt err = parser.Open( DOM_impl );
    if(KErrNone != err)
	    User::Leave(err);

    infoNum = 0;
    iLastError = KErrNone;
}

// -----------------------------------------------------------------------------
// CDomBCTester::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDomBCTester* CDomBCTester::NewL(CTestModuleIf& aTestModuleIf )
{
    CDomBCTester* self = new (ELeave) CDomBCTester( aTestModuleIf );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
}

// Destructor
CDomBCTester::~CDomBCTester()
{
    if(iDoc.NotNull())
    {
        iDoc.Close();
    }

    parser.Close();
    DOM_impl.Close();

    // Delete resources allocated from test methods
    Delete();

    // Delete logger
    delete iLog;
}

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// LibEntryL is a polymorphic Dll entry point.
// Returns: CScriptBase: New CScriptBase derived object
// -----------------------------------------------------------------------------
//
EXPORT_C CScriptBase* LibEntryL(CTestModuleIf& aTestModuleIf ) // Backpointer to STIF Test Framework
{
    return ( CScriptBase* ) CDomBCTester::NewL( aTestModuleIf );
}

//  End of File
