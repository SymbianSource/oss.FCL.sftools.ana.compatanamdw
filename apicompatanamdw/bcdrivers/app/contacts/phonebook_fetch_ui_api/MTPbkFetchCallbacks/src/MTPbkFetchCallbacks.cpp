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



// INCLUDE FILES
#include <Stiftestinterface.h>
#include "MTPbkFetchCallbacks.h"
#include <SettingServerClient.h>
#include <CPbkSingleEntryFetchDlg.h>
#include <CPbkContactEngine.h>
#include <CPbkContactItem.h>
#include <eikenv.h>
#include <MPbkFetchCallBacks.h>
#include <e32base.h>
#include <avkon.rsg>    //for use of R_AVKON_SOFTKEYS_CALL_CANCEL
#include <cpbkphonenumberselect.h>

#include "CSimulateKeyEvents.h"
#include "T_AddressAndNumberSelect.h"

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CMTPbkFetchCallbacks::CMTPbkFetchCallbacks
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CMTPbkFetchCallbacks::CMTPbkFetchCallbacks( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf ),
		iPbkViewResourceFile(*CCoeEnv::Static())

    {
    }

// -----------------------------------------------------------------------------
// CMTPbkFetchCallbacks::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CMTPbkFetchCallbacks::ConstructL()
    {
    //Read logger settings to check whether test case name is to be
    //appended to log file name.
    RSettingServer settingServer;
    TInt ret = settingServer.Connect();
    if(ret != KErrNone)
        {
        User::Leave(ret);
        }
    // Struct to StifLogger settigs.
    TLoggerSettings loggerSettings; 
    // Parse StifLogger defaults from STIF initialization file.
    ret = settingServer.GetLoggerSettings(loggerSettings);
    if(ret != KErrNone)
        {
        User::Leave(ret);
        } 
    // Close Setting server session
    settingServer.Close();

    TFileName logFileName;
    
    if(loggerSettings.iAddTestCaseTitle)
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL(title);
        logFileName.Format(KMTPbkFetchCallbacksLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(KMTPbkFetchCallbacksLogFile);
        }

    iLog = CStifLogger::NewL( KMTPbkFetchCallbacksLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
	iContactEngine = CPbkContactEngine::NewL(KTestDBName,ETrue);
	iAddressAndNumberSelect = new (ELeave) T_AddressAndNumberSelect();
	iSimulateKeyEvents = CSimulateKeyEvents::NewL();

	iPbkViewResourceFile.OpenL();
    
    }

// -----------------------------------------------------------------------------
// CMTPbkFetchCallbacks::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CMTPbkFetchCallbacks* CMTPbkFetchCallbacks::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CMTPbkFetchCallbacks* self = new (ELeave) CMTPbkFetchCallbacks( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CMTPbkFetchCallbacks::~CMTPbkFetchCallbacks()
    { 

    // Delete resources allocated from test methods
    Delete();

    // Delete logger
    delete iLog; 
	iPbkViewResourceFile.Close();
	delete iSimulateKeyEvents;
	delete iAddressAndNumberSelect;
	delete iContactEngine;

    }

//-----------------------------------------------------------------------------
// CMTPbkFetchCallbacks::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CMTPbkFetchCallbacks::SendTestClassVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
	moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("MTPbkFetchCallbacks.dll");

	TBool newVersionOfMethod = ETrue;
	TestModuleIf().SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
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

    return ( CScriptBase* ) CMTPbkFetchCallbacks::NewL( aTestModuleIf );

    }


//  End of File
