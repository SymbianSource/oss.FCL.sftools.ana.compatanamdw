/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  HwResManTest class member functions
*
*/



// INCLUDE FILES
#include <Stiftestinterface.h>
#include "HwResManTest.h"

#include <e32svr.h>

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
// CHwResManTest::CHwResManTest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CHwResManTest::CHwResManTest()
    {

    }

// -----------------------------------------------------------------------------
// CHwResManTest::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHwResManTest::ConstructL()
    {
    iLog = CStifLogger::NewL( KHwResManTestLogPath, 
                          KHwResManTestLogFile);

    // Sample how to use logging
    iLog->Log(_L("HwResManTest logging starts!"));
    
    /* Create and install active scheduler */
	myActiveScheduler = new CActiveScheduler;
	CActiveScheduler::Install(myActiveScheduler);
	
	iSession = CRepository::NewL(KCRUidVibraCtrl);
                              
    }
//-----------------------------------------------------------------------------
// CHwResManTest::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CHwResManTest::SendTestModuleVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_MODULE_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_MODULE_VERSION_MINOR;
	moduleVersion.iBuild = TEST_MODULE_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("HwResManTest.dll");
	

	TBool newVersionOfMethod = ETrue;
	CTestModuleIf &test=TestModuleIf();
	test.SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
	test.SetBehavior(CTestModuleIf::ETestLeaksHandles);
	}

// -----------------------------------------------------------------------------
// CHwResManTest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHwResManTest* CHwResManTest::NewL()
    {
    CHwResManTest* self = new (ELeave) CHwResManTest;
    
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    
    }

// Destructor
CHwResManTest::~CHwResManTest()
    { 
    delete iLog;
    delete iSession;
    
	/* Uninstall active scheduler */
	CActiveScheduler::Install(NULL);

	/* Delete active scheduler */
	delete myActiveScheduler;    
       
    }

// -----------------------------------------------------------------------------
// CHwResManTest::InitL
// InitL is used to initialize the Test Module.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::InitL( 
    TFileName& /*aIniFile*/, 
    TBool /*aFirstTime*/ )
    {
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CHwResManTest::GetTestCasesL
// GetTestCases is used to inquire test cases from the Test Module. Test
// cases are stored to array of test cases. The Test Framework will be 
// the owner of the data in the RPointerArray after GetTestCases return
// and it does the memory deallocation. 
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::GetTestCasesL( 
    const TFileName& /*aConfig*/, 
    RPointerArray<TTestCaseInfo>& aTestCases )
    {
    
    // Loop through all test cases and create new
    // TTestCaseInfo items and append items to aTestCase array    
    for( TInt i = 0; Case(i).iMethod != NULL; i++ )
        {
 
	    // Allocate new TTestCaseInfo from heap for a testcase definition.
        TTestCaseInfo* newCase = new( ELeave ) TTestCaseInfo();
    
	    // PushL TTestCaseInfo to CleanupStack.    
        CleanupStack::PushL( newCase );

	    // Set number for the testcase.
	    // When the testcase is run, this comes as a parameter to RunTestCaseL.
        newCase->iCaseNumber = i;

	    // Set title for the test case. This is shown in UI to user.
        newCase->iTitle.Copy( Case(i).iCaseName );

	    // Append TTestCaseInfo to the testcase array. After appended 
	    // successfully the TTestCaseInfo object is owned (and freed) 
	    // by the TestServer. 
        User::LeaveIfError(aTestCases.Append ( newCase ) );
        
	    // Pop TTestCaseInfo from the CleanupStack.
        CleanupStack::Pop( newCase );

        }
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CHwResManTest::RunTestCaseL
// RunTestCaseL is used to run an individual test case specified 
// by aTestCase. Test cases that can be run may be requested from 
// Test Module by GetTestCases method before calling RunTestCase.
// -----------------------------------------------------------------------------
//
TInt CHwResManTest::RunTestCaseL( 
    const TInt aCaseNumber,   
    const TFileName& /*aConfig*/,                 
    TTestResult& aResult )
    {
    SendTestModuleVersion();
    // Return value
    TInt execStatus = KErrNone;

    // Get the pointer to test case function
    TCaseInfo tmp = Case ( aCaseNumber );
    
    iLog->Log(_L("Starting testcase [%S]"), &tmp.iCaseName);

    // Check that case number was valid
    if ( tmp.iMethod != NULL )
        {
        // Valid case was found, call it via function pointer
        iMethod = tmp.iMethod;        
        execStatus  = ( this->*iMethod )( aResult );                  
        }
    else
        {        
        // Valid case was not found, return error.
        execStatus = KErrNotFound;
        }

    // Return case execution status (not the result of the case execution)
    return execStatus;
    
    }
    
void CHwResManTest::VibraModeChanged(CHWRMVibra::TVibraModeState aStatus)
{
	RDebug::Print(_L("CHwResManTest - VibraModeChanged to: %d"), aStatus);
	
	modeUpdated = true;
	myMode = aStatus;
	switch(aStatus)
	{
		case CHWRMVibra::EVibraModeUnknown:
		{
			iLog->Log(_L("HwResManTest Vibra Mode changed to EVibraModeUnknown"));
			
		}
		break;
		
		case CHWRMVibra::EVibraModeON:
		{
			iLog->Log(_L("HwResManTest Vibra Mode changed to EVibraModeON"));
			
		}
		break;
		
		case CHWRMVibra::EVibraModeOFF:
		{
			iLog->Log(_L("HwResManTest Vibra Mode changed to EVibraModeOFF"));
			
		}
		break;
							
		default:
			iLog->Log(_L("HwResManTest Vibra Mode changed to %d"), aStatus);
			
	}
		

}

void CHwResManTest::VibraStatusChanged(CHWRMVibra::TVibraStatus aStatus)
{
	RDebug::Print(_L("CHwResManTest - VibraStatusChanged to: %d"), aStatus);

	statusUpdated = true;
	myStatus = aStatus;
	switch(aStatus)
	{
		case CHWRMVibra::EVibraStatusUnknown:
		{
			iLog->Log(_L("HwResManTest Vibra status changed to EVibraStatusUnknown"));
			
		}
		break;
		
		case CHWRMVibra::EVibraStatusNotAllowed:
		{
			iLog->Log(_L("HwResManTest Vibra status changed to EVibraStatusNotAllowed"));
			
		}
		break;
		
		case CHWRMVibra::EVibraStatusStopped:
		{
			iLog->Log(_L("HwResManTest Vibra status changed to EVibraStatusStopped"));
			
		}
		break;

		case CHWRMVibra::EVibraStatusOn:
		{
			iLog->Log(_L("HwResManTest Vibra status changed to EVibraStatusOn"));
			
		}
		break;
							
		default:
			iLog->Log(_L("HwResManTest Vibra status changed to %d"), aStatus);
			
	}

}    

void CHwResManTest::InitTestVariables()
{

	modeUpdated = false;
	myMode = CHWRMVibra::EVibraModeUnknown;
	statusUpdated = false;
	myStatus = CHWRMVibra::EVibraStatusUnknown;
}

TInt CHwResManTest::RunTestVibra( CHWRMVibra* iVibra, TInt howLong, TInt whatIntensity)
{
	TInt errorStatus;	
	TRAP(errorStatus, iVibra->StartVibraL(howLong, whatIntensity));
	iLog->Log(_L("HwResManTest Vibra start for %d seconds with intensity %d Error:%d"), howLong/1000, whatIntensity, errorStatus);
	return errorStatus;
}

TInt CHwResManTest::RunTestVibra( CHWRMVibra* iVibra, TInt howLong)
{
	TInt errorStatus;	
	TRAP(errorStatus, iVibra->StartVibraL(howLong));
	iLog->Log(_L("HwResManTest Vibra start for %d seconds with default intensity Error:%d"), howLong/1000, errorStatus);
	return errorStatus;
}


TInt CHwResManTest::StopTestVibra(CHWRMVibra* iVibra)
{
	TInt errorStatus;		
	TRAP(errorStatus, iVibra->StopVibraL());
	iLog->Log(_L("HwResManTest Vibra stop called Error:%d"),errorStatus);
	return errorStatus; 
}

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// LibEntryL is a polymorphic Dll entry point
// Returns: CTestModuleBase*: Pointer to Test Module object
// -----------------------------------------------------------------------------
//
EXPORT_C CTestModuleBase* LibEntryL()
    {
    return CHwResManTest::NewL();
    
    }


//  End of File
