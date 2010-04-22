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
* Description:  Test Class which has the list of test cases
*
*/



// INCLUDE FILES
#include <Stiftestinterface.h>
#include "testlbslocacquisition.h"
#include "testpositionserver.h"
#include "testpositioner.h"
#include "testpositionInfo.h"
#include "testpositioncourseinfo.h"
#include "testpositiongenericinfo.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CTestLbsLocAcquisition
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestLbsLocAcquisition::CTestLbsLocAcquisition( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestLbsLocAcquisition::ConstructL()
    {
    iLog = CStifLogger::NewL( KtlbslocacquisitionLogPath, 
                          KtlbslocacquisitionLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
	
	iPosServer = new(ELeave) CTestPositionServer(iLog);
	iPositioner = new(ELeave) CTestPositioner(iLog);
	iPositionInfo = new(ELeave) CTestPositionInfo(iLog);
	iPositionCourseInfo = new(ELeave) CTestPositionCourseInfo(iLog);
	iPositionGenericInfo = new(ELeave) CTestPositionGenericInfo(iLog);
	SendTestModuleVersion();
    }

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestLbsLocAcquisition* CTestLbsLocAcquisition::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTestLbsLocAcquisition* self = new (ELeave) CTestLbsLocAcquisition( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTestLbsLocAcquisition::~CTestLbsLocAcquisition()
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

    return ( CScriptBase* ) CTestLbsLocAcquisition::NewL( aTestModuleIf );

    }

void CTestLbsLocAcquisition::SendTestModuleVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_MODULE_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_MODULE_VERSION_MINOR;
	moduleVersion.iBuild = TEST_MODULE_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("LocAquisition.dll");
	

	TBool newVersionOfMethod = ETrue;
	CTestModuleIf &test=TestModuleIf();
	test.SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
	test.SetBehavior(CTestModuleIf::ETestLeaksHandles);
	}

//  End of File
