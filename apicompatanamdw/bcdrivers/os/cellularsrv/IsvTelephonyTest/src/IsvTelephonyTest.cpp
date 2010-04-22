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
* Description:  CIsvTelephonyTest class member functions
*
*/



// INCLUDE FILES
#include <Stiftestinterface.h>
#include <StifParser.h>
#include "IsvTelephonyTest.h"
#include "IsvTelephonyTestEngine.h"
#include "IsvTelephonyTestParser.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::CIsvTelephonyTest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CIsvTelephonyTest::CIsvTelephonyTest()
    {
	iMessageOption = EMessagesLogAndUi; 
    }

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::ConstructL
// Symbian 2nd phase constructor can leave.
//
// Note: If OOM test case uses STIF Logger, then STIF Logger must be created
// with static buffer size parameter (aStaticBufferSize). Otherwise Logger 
// allocates memory from heap and therefore causes error situations with OOM 
// testing. For more information about STIF Logger construction, see STIF Users 
// Guide.
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTest::ConstructL()
    {
    iLogger = CStifLogger::NewL( 
    	KIsvTelephonyTestLogPath, 
    	KIsvTelephonyTestLogFile );    
    
	iTestScheduler = new (ELeave) CActiveScheduler;	
	CActiveScheduler::Install( iTestScheduler );	
	
    iTestEngine = CIsvTelephonyTestEngine::NewL();         
    iTestParser = CIsvTelephonyTestParser::NewL( *this );
    } 
//-----------------------------------------------------------------------------
// CIsvTelephonyTest::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CIsvTelephonyTest::SendTestModuleVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_MODULE_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_MODULE_VERSION_MINOR;
	moduleVersion.iBuild = TEST_MODULE_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("IsvTelephonyTest.dll");
	

	TBool newVersionOfMethod = ETrue;
	CTestModuleIf &test=TestModuleIf();
	test.SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
	test.SetBehavior(CTestModuleIf::ETestLeaksHandles);
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CIsvTelephonyTest* CIsvTelephonyTest::NewL()
    {
    CIsvTelephonyTest* self = new (ELeave) CIsvTelephonyTest; 
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// Destructor
CIsvTelephonyTest::~CIsvTelephonyTest()
    {          	
	iDTMFTones.Close();
	delete iTestParser;  
	delete iTestEngine;
	delete iTestScheduler; 
    }

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::InitL
// InitL is used to initialize the Test Module.
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::InitL( 
    TFileName& aIniFile, 
    TBool /*aFirstTime*/ )
    {        
    TInt result( KErrNone ); 
    
	CStifParser* parser = CStifParser::NewL( KNullDesC, aIniFile );
	CleanupStack::PushL( parser ); 
		
	CStifSectionParser* section = parser->SectionL(
		KInitIsvTelephonyTestSectionStart, 
		KInitSectionEnd );	
	CStifItemParser *item; 
	TPtrC parsePtr;
	
	// Initialise variables from IsvTelephonyTest ini file	
	if( section )
		{	
		// Phone number 1	
		item = section->GetItemLineL( KInitMoPhoneNumber1 );
		result = item->GetString( KInitMoPhoneNumber1, parsePtr );	
		if( KErrNone == result )
			{
			iTelNumber1.Copy( parsePtr ); 
			}
		// Phone number 2
		item = section->GetItemLineL( KInitMoPhoneNumber2 );
		result = item->GetString( KInitMoPhoneNumber2, parsePtr );	
		if( KErrNone == result )
			{
			iTelNumber2.Copy( parsePtr ); 
			}
		// Id restrict (CLIR)					
		item = section->GetItemLineL( KInitIdRestrict );
		result = item->GetString( KInitIdRestrict, parsePtr );	
		if( KErrNone == result )
			{					
			if( parsePtr.Compare(KInitEIdRestrictDefault) == 0 )
				{
				iIdRestrict = CTelephony::EIdRestrictDefault;	
				}
			else if( parsePtr.Compare(KInitESendMyId) == 0 )
				{
				iIdRestrict = CTelephony::ESendMyId;	
				}
			else if( parsePtr.Compare(KInitEDontSendMyId) == 0 )
				{
				iIdRestrict = CTelephony::EDontSendMyId;	
				}
			}		    
		// Phone line
		item = section->GetItemLineL( KInitPhoneLine );
		result = item->GetString( KInitPhoneLine, parsePtr );	
		if( KErrNone == result )
			{					
			if( parsePtr.Compare(KInitEVoiceLine) == 0 )
				{
				iPhoneLine = CTelephony::EVoiceLine;	
				}
			else if( parsePtr.Compare(KInitEDataLine) == 0 )
				{
				iPhoneLine = CTelephony::EDataLine;	
				}
			else if( parsePtr.Compare(KInitEFaxLine) == 0 )
				{
				iPhoneLine = CTelephony::EFaxLine;	
				}
			}		    
		// DTMF tones
		item = section->GetItemLineL( KInitDTMFTones );
		result = item->GetString( KInitDTMFTones, parsePtr );	
		if( KErrNone == result )
			{
			iDTMFTones.Create( parsePtr ); 
			}
		}
		
    CleanupStack::PopAndDestroy( parser ); // parser
    
    return result;
    }

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::GetTestCasesL
// GetTestCases is used to inquire test cases from the Test Module. Test
// cases are stored to array of test cases. The Test Framework will be 
// the owner of the data in the RPointerArray after GetTestCases return
// and it does the memory deallocation. 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::GetTestCasesL( 
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
// CIsvTelephonyTest::RunTestCaseL
// RunTestCaseL is used to run an individual test case specified 
// by aTestCase. Test cases that can be run may be requested from 
// Test Module by GetTestCases method before calling RunTestCase.
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::RunTestCaseL( 
    const TInt aCaseNumber,   
    const TFileName& /*aConfig*/,
    TTestResult& aResult )
    {	
    	SendTestModuleVersion();
    // Return value
    TInt execStatus = KErrNone;

    // Get the pointer to test case function
    TCaseInfo tmp = Case ( aCaseNumber );

	// Write test case start messages to log    
    iLogger->WriteDelimiter(); 
    _LIT( KLogStartTC, "Starting testcase [%S]" );
    iLogger->Log( KLogStartTC, &tmp.iCaseName);

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
	
	// Print result to log/Stif UI
	if( KErrNone == aResult.iResult )
		{
		PrintMessage( KResultPASS() );	
		}
	else
		{
		PrintMessage( KResultFAIL() );	
		TBuf<KMessageHandlerMaxMessageSize> buffer;
		buffer.Copy( KErrorCode );	
		buffer.AppendNum( aResult.iResult );			
		PrintMessage( buffer );	
		}
	
	// If STIF Ui printing is used then a UI flush is needed after each test case 
	if( EMessagesUi == iMessageOption || 
		EMessagesLogAndUi == iMessageOption )
		{
		TestModuleIf().Printf( iStifUiLineCounter, KNullDesC, KNullDesC ); 		
		iStifUiLineCounter = 0; 		
		}
		
    // Return case execution status (not the result of the case execution)
    return execStatus;
    }

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::OOMTestQueryL
// Used to check if a particular test case should be run in OOM conditions and 
// which memory allocations should fail.    
// -----------------------------------------------------------------------------
//
TBool CIsvTelephonyTest::OOMTestQueryL( 
    const TFileName& /* aTestCaseFile */, 
    const TInt aCaseNumber, 
    TOOMFailureType& /* aFailureType */, 
    TInt& aFirstMemFailure, 
    TInt& aLastMemFailure ) 
    {
    aFirstMemFailure = Case( aCaseNumber ).iFirstMemoryAllocation;
    aLastMemFailure = Case( aCaseNumber ).iLastMemoryAllocation;

    return Case( aCaseNumber ).iIsOOMTest;
    }

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::OOMTestInitializeL
// Used to perform the test environment setup for a particular OOM test case. 
// Test Modules may use the initialization file to read parameters for Test 
// Module initialization but they can also have their own configure file or 
// some other routine to initialize themselves.  
//
// NOTE: User may add implementation for OOM test environment initialization.
// Usually no implementation is required.
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTest::OOMTestInitializeL( 
    const TFileName& /* aTestCaseFile */, 
    const TInt /* aCaseNumber */ )
    {
    }

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::OOMHandleWarningL
// In some cases the heap memory allocation should be skipped, either due to
// problems in the OS code or components used by the code being tested, or even 
// inside the tested components which are implemented this way on purpose (by 
// design), so it is important to give the tester a way to bypass allocation 
// failures.
//
// NOTE: User may add implementation for OOM test warning handling. Usually no
// implementation is required.
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTest::OOMHandleWarningL( 
    const TFileName& /* aTestCaseFile */,
    const TInt /* aCaseNumber */, 
    TInt& /* aFailNextValue */ )
    {
    }

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::OOMTestFinalizeL
// Used to perform the test environment cleanup for a particular OOM test case.
//
// NOTE: User may add implementation for OOM test environment finalization.
// Usually no implementation is required.
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTest::OOMTestFinalizeL( 
    const TFileName& /* aTestCaseFile */, 
    const TInt /* aCaseNumber */ )
    {
    }

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::PrintMessage
// Implements MIsvTelephonyTestMessageHandler messaging interface. 
// Message is output to file log or to STIF Ui. 
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTest::PrintMessage( const TDesC& aMessage )
	{
	switch( iMessageOption )
		{
		case EMessagesLog: 
			iLogger->Log( aMessage );			
			break;
		case EMessagesUi: 
			TestModuleIf().Printf( iStifUiLineCounter, KNullDesC, aMessage );
			iStifUiLineCounter++; 			
			break;
		case EMessagesLogAndUi: 
			iLogger->Log( aMessage );			
			TestModuleIf().Printf( iStifUiLineCounter, KNullDesC, aMessage );
			iStifUiLineCounter++; 
			break;
		case EMessagesOff: 			
			break;			
		default: 
		 	break; 		
		}
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::PrintMessage
// Implements MIsvTelephonyTestMessageHandler messaging interface. 
// Message is output to file log or to STIF Ui. 
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTest::PrintMessage( TRefByValue<const TDesC> aMessage,... )
	{
	switch( iMessageOption )
		{
		case EMessagesLog: 
			iLogger->Log( aMessage );			
			break;
		case EMessagesUi: 
			TestModuleIf().Printf( iStifUiLineCounter, KNullDesC, aMessage );
			iStifUiLineCounter++; 			
			break;
		case EMessagesLogAndUi: 
			iLogger->Log( aMessage );			
			TestModuleIf().Printf( iStifUiLineCounter, KNullDesC, aMessage );
			iStifUiLineCounter++; 
			break;
		case EMessagesOff: 			
			break;			
		default: 
		 	break; 		
		}
	}

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// LibEntryL is a polymorphic Dll entry point
// Returns: CTestModuleBase*: Pointer to Test Module object
// -----------------------------------------------------------------------------
//
EXPORT_C CTestModuleBase* LibEntryL()
    {
    return CIsvTelephonyTest::NewL();
    }

// -----------------------------------------------------------------------------
// SetRequirements handles test module parameters(implements evolution
// version 1 for test module's heap and stack sizes configuring).
// Returns: TInt: Symbian error code.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt SetRequirements( 
	CTestModuleParam*& /*aTestModuleParam*/, 
    TUint32& /*aParameterValid*/ )
    {
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// E32Dll is a DLL entry point function
// Returns: KErrNone: No error
// -----------------------------------------------------------------------------
//
#ifndef EKA2 // Hide Dll entry point to EKA2
GLDEF_C TInt E32Dll(
    TDllReason /*aReason*/) // Reason
    {
    return(KErrNone);
    }
#endif // EKA2

//  End of File
