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
#include "DRM_CAF.h"
#include <SettingServerClient.h>

// INCLUDE FILES




_LIT( KDrmDir, "c:\\drm\\" );
_LIT( KMessagesDir, "c:\\drm\\messages\\");
_LIT(KInputDir, "c:\\");
_LIT(KEncryptedDir, "c:\\");
_LIT(KDecryptedDir, "c:\\");
_LIT( KFilesDir, "c:\\drm\\messages\\files\\");
_LIT(KRightsDir, "c:\\");



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
// CDRM_CAF::CDRM_CAF
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CDRM_CAF::CDRM_CAF( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CDRM_CAF::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDRM_CAF::ConstructL()
    {
    //Read logger settings to check whether test case name is to be
    //appended to log file name.
       
    User::LeaveIfError( iFs.Connect() );
   // CleanupClosePushL( iFs );
 
    CreateDirL();
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
        logFileName.Format(KDRM_CAFLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(KDRM_CAFLogFile);
        }

    iLog = CStifLogger::NewL( KDRM_CAFLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// CDRM_CAF::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDRM_CAF* CDRM_CAF::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CDRM_CAF* self = new (ELeave) CDRM_CAF( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CDRM_CAF::~CDRM_CAF()
    { 
    //CleanupStack::PopAndDestroy(); // Gfs
    // Delete resources allocated from test methods
    Delete();
    iFs.Close();
    
    // Delete logger
    delete iLog; 
    //CleanupStack::PopAndDestroy(); // Gfs
    
    }

//-----------------------------------------------------------------------------
// CDRM_CAF::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CDRM_CAF::SendTestClassVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
	moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("DRM_CAF.dll");

	TBool newVersionOfMethod = ETrue;
	TestModuleIf().SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
	TestModuleIf().SetBehavior(CTestModuleIf::ETestLeaksHandles);
	}

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// LibEntryL is a polymorphic Dll entry point.
// Returns: CScriptBase: New CScriptBase derived object
// -----------------------------------------------------------------------------
//
EXPORT_C CScriptBase* LibEntryL(CTestModuleIf& aTestModuleIf ) // Backpointer to STIF Test Framework
    {

    return ( CScriptBase* ) CDRM_CAF::NewL( aTestModuleIf );

    }
void CDRM_CAF::CreateDirL()
    {
    TInt error = iFs.MkDir(KDrmDir);
    if (error == KErrAlreadyExists || error == KErrNone)
        {
        error = iFs.MkDir(KMessagesDir);
        if (error == KErrAlreadyExists || error == KErrNone)
            {
            error = iFs.MkDir(KEncryptedDir);
            }
        
        if (error == KErrAlreadyExists || error == KErrNone)
            {
            error = iFs.MkDir(KFilesDir);
            }
        
        if (error == KErrAlreadyExists || error == KErrNone)
            {
            error = iFs.MkDir(KDecryptedDir);
            }
        
        if (error == KErrAlreadyExists || error == KErrNone)
            {
            error = iFs.MkDir(KRightsDir);
            }
        
        if (error != KErrAlreadyExists && error != KErrNone)
            {
            User::LeaveIfError(error);
            }
        }
    else
        {
        User::LeaveIfError(error);
        }
   // CleanupStack::PopAndDestroy(); // Gfs
    }

//  End of File
