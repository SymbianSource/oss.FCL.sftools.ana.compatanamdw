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
* Description:  Ctestdbmanagementapi class
*
*/



// INCLUDE FILES
#include <Stiftestinterface.h>
#include "testdbmanagementapi.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestdbmanagementapi::Ctestdbmanagementapi
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
Ctestdbmanagementapi::Ctestdbmanagementapi( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// Ctestdbmanagementapi::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void Ctestdbmanagementapi::ConstructL()
    {
    iLog = CStifLogger::NewL( KtestdbmanagementapiLogPath, 
                          KtestdbmanagementapiLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
		SendTestModuleVersion();
    }
//-----------------------------------------------------------------------------
// Ctestdbmanagementapi::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void Ctestdbmanagementapi::SendTestModuleVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_MODULE_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_MODULE_VERSION_MINOR;
	moduleVersion.iBuild = TEST_MODULE_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("testdbmanagementapi.dll");
	

	TBool newVersionOfMethod = ETrue;
	CTestModuleIf &test=TestModuleIf();
	test.SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
	test.SetBehavior(CTestModuleIf::ETestLeaksHandles);
	}

// -----------------------------------------------------------------------------
// Ctestdbmanagementapi::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
Ctestdbmanagementapi* Ctestdbmanagementapi::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    Ctestdbmanagementapi* self = new (ELeave) Ctestdbmanagementapi( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
Ctestdbmanagementapi::~Ctestdbmanagementapi()
    { 

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
EXPORT_C CScriptBase* LibEntryL( 
    CTestModuleIf& aTestModuleIf ) // Backpointer to STIF Test Framework
    {

    return ( CScriptBase* ) Ctestdbmanagementapi::NewL( aTestModuleIf );

    }


//  End of File
