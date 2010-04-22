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
#include "MTPbkContactItemField.h"
#include <SettingServerClient.h>
#include <TPbkContactItemField.h>
#include <CPbkContactEngine.h>
#include <CPbkContactItem.h>
#include <CPbkFieldsInfo.h>

// the string which will be set to textfields
_LIT(KFillText, "TESTDATA");
// first name string which will be set to textfields
_LIT(KFirstName, "John");
// email address which will be set to email address fields
_LIT(KEmailAddress, "john@company.com");
// the name of the contact database used in these tests
_LIT(KTestDBName,"c:MT_CPbkContactItem.cdb");
// date string
_LIT(KDate, "20060101:");
// formatted date string
_LIT(KFormattedDate, "02/02/2006");
// string containing spaces
_LIT(KSpacesString, "    ");
// phonenumber for testing purposes
const TInt KPhoneNumber = 5005001;
// lenght of phone number
const TInt KPhoneNumberLenght = 10;
// text's max lenght
const TInt KTextMaxLen = 100;
// size of TPbkContactItemField class
const TInt KClassSize = 12;
// speed dial for number 1
const TInt KSpeedDialOne = 1;


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
// CMTPbkContactItemField::CMTPbkContactItemField
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CMTPbkContactItemField::CMTPbkContactItemField( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CMTPbkContactItemField::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CMTPbkContactItemField::ConstructL()
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
        logFileName.Format(KMTPbkContactItemFieldLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(KMTPbkContactItemFieldLogFile);
        }

    iLog = CStifLogger::NewL( KMTPbkContactItemFieldLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
    iContactEngine = CPbkContactEngine::NewL(KTestDBName,ETrue); 
    
    }

// -----------------------------------------------------------------------------
// CMTPbkContactItemField::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CMTPbkContactItemField* CMTPbkContactItemField::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CMTPbkContactItemField* self = new (ELeave) CMTPbkContactItemField( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CMTPbkContactItemField::~CMTPbkContactItemField()
    { 

    // Delete resources allocated from test methods
    Delete();

    // Delete logger
    delete iLog; 
    delete iContactEngine;

    }

//-----------------------------------------------------------------------------
// CMTPbkContactItemField::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CMTPbkContactItemField::SendTestClassVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
	moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("MTPbkContactItemField.dll");

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

    return ( CScriptBase* ) CMTPbkContactItemField::NewL( aTestModuleIf );

    }


//  End of File
