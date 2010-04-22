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
* Description:  
*
*/



// INCLUDE FILES
#include <Stiftestinterface.h>
#include "testlandmarksapi.h"
#include <f32file.h>


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestlandmarksapi::Ctestlandmarksapi
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestLandmarksApi::CTestLandmarksApi( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// Ctestlandmarksapi::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestLandmarksApi::ConstructL()
    {
    iLog = CStifLogger::NewL( KtestlandmarksapiLogPath, 
                          KtestlandmarksapiLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    // Init test database
    CTestPosLandmarkDatabase::InitTestDatabaseL( iLog );
    SendTestModuleVersion();    
    }
//-----------------------------------------------------------------------------
// CTestLandmarksApi::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestLandmarksApi::SendTestModuleVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_MODULE_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_MODULE_VERSION_MINOR;
	moduleVersion.iBuild = TEST_MODULE_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("testlandmarksapi.dll");
	

	TBool newVersionOfMethod = ETrue;
	CTestModuleIf &test=TestModuleIf();
	test.SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
	test.SetBehavior(CTestModuleIf::ETestLeaksHandles);
	}

// -----------------------------------------------------------------------------
// Ctestlandmarksapi::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestLandmarksApi* CTestLandmarksApi::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTestLandmarksApi* self = new (ELeave) CTestLandmarksApi( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTestLandmarksApi::~CTestLandmarksApi()
    { 

    // Delete resources allocated from test methods
    Delete();

    // Delete logger
    delete iLog; 
   
    // Release resources used for landmark
    ReleaseLandmarkResources(); 

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

    return ( CScriptBase* ) CTestLandmarksApi::NewL( aTestModuleIf );

    }


//  End of File
