/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  DownloadMgrBCTest class member functions
*
*/



// INCLUDE FILES
#include <Stiftestinterface.h>
#include "DownloadMgrBCTest.h"

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS

// MACROS

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

// ---------------------------------------------------------
// DeleteFileL
// ---------------------------------------------------------
//
void DeleteFileL( const TDesC& aFile, RFs& aFs )
    {
    TParse file;
    User::LeaveIfError( aFs.Parse( aFile, file ) );
    TUint att;
    TInt res = aFs.Att( file.FullName(), att );
    if ( res == KErrNone )
        {
        User::LeaveIfError( aFs.Delete( file.FullName() ) );
        }
    }

// ---------------------------------------------------------
// CopyFileL
// ---------------------------------------------------------
//
void CopyFileL( const TDesC& aSrc, const TDesC& aDst, RFs& aFs )
    {
    RFile src;
    RFile dst;
    TBuf8<256> buf;

    User::LeaveIfError( src.Open
        ( aFs, aSrc, EFileRead | EFileShareReadersOnly | EFileStream ) );
    CleanupClosePushL<RFile>( src );
    (void)aFs.MkDirAll( aDst );    
    (void)aFs.SetAtt( aDst, 0, KEntryAttReadOnly ); // Overwrite read-only.
    User::LeaveIfError( dst.Replace
        ( aFs, aDst, EFileWrite | EFileShareExclusive | EFileStream ) );
    CleanupClosePushL<RFile>( dst );
    FOREVER
        {
        User::LeaveIfError( src.Read( buf ) );
        if ( !buf.Length() )
            {
            break;
            }
        User::LeaveIfError( dst.Write( buf ) );
        }
    CleanupStack::PopAndDestroy( 2 );   // close dst, src
    }


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CDownloadMgrBCTest::CDownloadMgrBCTest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CDownloadMgrBCTest::CDownloadMgrBCTest()
    {

    }

// -----------------------------------------------------------------------------
// CDownloadMgrBCTest::ConstructL
// Symbian 2nd phase constructor can leave.
// Note: If OOM test case uses STIF Logger, then STIF Logger must be created
// with static buffer size parameter (aStaticBufferSize). Otherwise Logger 
// allocates memory from heap and therefore causes error situations with OOM 
// testing. For more information about STIF Logger construction, see STIF Users 
// Guide.
// -----------------------------------------------------------------------------
//
void CDownloadMgrBCTest::ConstructL()
    {
    iLog = CStifLogger::NewL( KDownloadMgrBCTestLogPath, 
                          KDownloadMgrBCTestLogFile);
                          
    User::LeaveIfError( iFileSystem.Connect() );

    iDownloadManager.ConnectL( TUid::Uid( KThisAppUid ), *this, EFalse );
    }

//-----------------------------------------------------------------------------
// CDownloadMgrBCTest::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CDownloadMgrBCTest::SendTestModuleVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_MODULE_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_MODULE_VERSION_MINOR;
	moduleVersion.iBuild = TEST_MODULE_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("DownloadMgrBCTest.dll");
	

	TBool newVersionOfMethod = ETrue;
	CTestModuleIf &test=TestModuleIf();
	test.SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
	test.SetBehavior(CTestModuleIf::ETestLeaksHandles);
	}

// -----------------------------------------------------------------------------
// CDownloadMgrBCTest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDownloadMgrBCTest* CDownloadMgrBCTest::NewL()
    {
    CDownloadMgrBCTest* self = new (ELeave) CDownloadMgrBCTest;

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CDownloadMgrBCTest::~CDownloadMgrBCTest()
    {
    iDownloadManager.Close();
    iFileSystem.Close();
    delete iLog;
    }

// -----------------------------------------------------------------------------
// CDownloadMgrBCTest::InitL
// InitL is used to initialize the Test Module.
// -----------------------------------------------------------------------------
//
TInt CDownloadMgrBCTest::InitL( 
    TFileName& /*aIniFile*/, 
    TBool /*aFirstTime*/ )
    {
    return KErrNone;

    }

/*
-------------------------------------------------------------------------------

    Class: CDemoModule

    Method: Case

    Description: Returns a test case by number.

    This function contains an array of all available test cases 
    i.e pair of case name and test function. If case specified by parameter
    aCaseNumber is found from array, then that item is returned.

    The reason for this rather complicated function is to specify all the
    test cases only in one place. It is not necessary to understand how
    function pointers to class member functions works when adding new test
    cases. See function body for instructions how to add new test case.
    
    Parameters:    const TInt aCaseNumber :in:      Test case number

    Return Values: const TCaseInfo Struct containing case name & function

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/ 
const TCaseInfo CDownloadMgrBCTest::Case ( 
    const TInt aCaseNumber ) const 
     {

    /*
    * To add new test cases, implement new test case function and add new 
    * line to KCases array specify the name of the case and the function 
    * doing the test case
    * In practice, do following
    *
    * 1) Make copy of existing test case function and change its name
    *    and functionality. Note that the function must be added to 
    *    OOMHard.cpp file and to OOMHard.h 
    *    header file.
    *
    * 2) Add entry to following KCases array either by using:
    *
    * 2.1: FUNCENTRY or ENTRY macro
    * ENTRY macro takes two parameters: test case name and test case 
    * function name.
    *
    * FUNCENTRY macro takes only test case function name as a parameter and
    * uses that as a test case name and test case function name.
    *
    * Or
    *
    * 2.2: OOM_FUNCENTRY or OOM_ENTRY macro. Note that these macros are used
    * only with OOM (Out-Of-Memory) testing!
    *
    * OOM_ENTRY macro takes five parameters: test case name, test case 
    * function name, TBool which specifies is method supposed to be run using
    * OOM conditions, TInt value for first heap memory allocation failure and 
    * TInt value for last heap memory allocation failure.
    * 
    * OOM_FUNCENTRY macro takes test case function name as a parameter and uses
    * that as a test case name, TBool which specifies is method supposed to be
    * run using OOM conditions, TInt value for first heap memory allocation 
    * failure and TInt value for last heap memory allocation failure. 
    */ 

    static TCaseInfoInternal const KCases[] =
        {
        // To add new test cases, add new items to this array
        
        // NOTE: When compiled to GCCE, there must be Classname::
        // declaration in front of the method name, e.g. 
        // CDemoModule::PrintTest. Otherwise the compiler
        // gives errors.
                
        
        ENTRY( "Manager GetIntAttribute test Album", CDownloadMgrBCTest::ManagerGetIntAttributeTestAlbum ),
        ENTRY( "Download GetBoolAttribute test Album", CDownloadMgrBCTest::DownloadGetBoolAttributeTestAlbum),
        ENTRY( "Download GetStringAttribute test with TDes16 argument Album", CDownloadMgrBCTest::DownloadGetStringAttribute16TestAlbum ),
        ENTRY( "Download GetStringAttribute test with TDes8 argument Album", CDownloadMgrBCTest::DownloadGetStringAttribute8TestAlbum ),
        ENTRY( "Download SetStringAttribute test with TDes16 argument Album", CDownloadMgrBCTest::DownloadSetStringAttribute16TestAlbum ),
        ENTRY( "Download SetDownloadDataAttribute test with TDesC8", CDownloadMgrBCTest::SetDownloadDataAttribute ),
        ENTRY( "Download SetTrackDataAttribute test with TDesC8", CDownloadMgrBCTest::SetTrackDataAttribute ),
        ENTRY( "Download Start test", CDownloadMgrBCTest::DownloadStartTest ),
        ENTRY( "Download Pause test", CDownloadMgrBCTest::DownloadPauseTest ),
        ENTRY( "Download Reset test", CDownloadMgrBCTest::DownloadResetTest ),
        ENTRY( "Download Delete test", CDownloadMgrBCTest::DownloadDeleteTest ),
        ENTRY( "Download Move test", CDownloadMgrBCTest::DownloadMoveTest ),
        ENTRY( "Download GetIntAttribute test", CDownloadMgrBCTest::DownloadGetIntAttributeTest ),
        ENTRY( "Download GetBoolAttribute test", CDownloadMgrBCTest::DownloadGetBoolAttributeTest ),
        ENTRY( "Download GetStringAttribute test with TDes16 argument", CDownloadMgrBCTest::DownloadGetStringAttribute16Test ),
        ENTRY( "Download GetStringAttribute test with TDes8 argument", CDownloadMgrBCTest::DownloadGetStringAttribute8Test ),
        ENTRY( "Download GetFileHandleAttribute test", CDownloadMgrBCTest::DownloadGetFileHandleAttributeTest ),
        ENTRY( "Download SetIntAttribute test", CDownloadMgrBCTest::DownloadSetIntAttributeTest ),
        ENTRY( "Download SetBoolAttribute test", CDownloadMgrBCTest::DownloadSetBoolAttributeTest ),
        ENTRY( "Download SetStringAttribute test with TDes16 argument", CDownloadMgrBCTest::DownloadSetStringAttribute16Test ),
        ENTRY( "Download SetStringAttribute test with TDes8 argument", CDownloadMgrBCTest::DownloadSetStringAttribute8Test ),
        ENTRY( "Download SetFileHandleAttribute test with TDes8 argument", CDownloadMgrBCTest::DownloadSetFileHandleAttributeTest ),
        ENTRY( "Manager ConnectL test", CDownloadMgrBCTest::ManagerConnectLTest ),
        ENTRY( "Manager Version test", CDownloadMgrBCTest::ManagerVersionTest ),
        ENTRY( "Manager Close test", CDownloadMgrBCTest::ManagerCloseTest ),
        ENTRY( "Manager CurrentDownloads test", CDownloadMgrBCTest::ManagerCurrentDownloadsTest ),
        ENTRY( "Manager CreateDownloadL test with Bool argument", CDownloadMgrBCTest::ManagerCreateDownloadLWithBoolTest ),
        ENTRY( "Manager CreateDownloadL test", CDownloadMgrBCTest::ManagerCreateDownloadLTest ),
        //ENTRY( "Manager CreateClientSideDownloadL test", CDownloadMgrBCTest::ManagerCreateClientSideDownloadLTest ),
        ENTRY( "Manager CreateCodDownloadL test", CDownloadMgrBCTest::ManagerCreateCodDownloadLTest ),
        ENTRY( "Manager FindDownload test", CDownloadMgrBCTest::ManagerFindDownloadTest ),
        ENTRY( "Manager PauseAll test", CDownloadMgrBCTest::ManagerPauseAllTest ),
        ENTRY( "Manager StartAll test", CDownloadMgrBCTest::ManagerStartAllTest ),
        ENTRY( "Manager ResetAll test", CDownloadMgrBCTest::ManagerResetAllTest ),
        ENTRY( "Manager DeleteAll test", CDownloadMgrBCTest::ManagerDeleteAllTest ),
        ENTRY( "Manager Disconnect test", CDownloadMgrBCTest::ManagerDisconnectTest ),
        ENTRY( "Manager GetIntAttribute test", CDownloadMgrBCTest::ManagerGetIntAttributeTest ),
        ENTRY( "Manager GetBoolAttribute test", CDownloadMgrBCTest::ManagerGetBoolAttributeTest ),
        ENTRY( "Manager GetStringAttribute test with TDesC16 argument", CDownloadMgrBCTest::ManagerGetStringAttribute16Test ),
        //ENTRY( "Manager GetStringAttribute test with TDesC8 argument", CDownloadMgrBCTest::ManagerGetStringAttribute8Test ),
        ENTRY( "Manager SetIntAttribute test", CDownloadMgrBCTest::ManagerSetIntAttributeTest ),
        ENTRY( "Manager SetBoolAttribute test", CDownloadMgrBCTest::ManagerSetBoolAttributeTest ),
        ENTRY( "Manager SetStringAttribute test with TDesC16 argument", CDownloadMgrBCTest::ManagerSetStringAttribute16Test ),
        //ENTRY( "Manager SetStringAttribute test with TDesC8 argument", CDownloadMgrBCTest::ManagerSetStringAttribute8Test ),
        ENTRY( "Manager SetDefaultIntAttribute test", CDownloadMgrBCTest::ManagerSetDefaultIntAttributeTest ),
        ENTRY( "Manager SetDefaultBoolAttribute test", CDownloadMgrBCTest::ManagerSetDefaultBoolAttributeTest ),
        ENTRY( "Manager SetDefaultStringAttribute test with TDesc16 argument", CDownloadMgrBCTest::ManagerSetDefaultStringAttribute16Test ),
        ENTRY( "Manager SetDefaultStringAttribute test with TDesc8 argument", CDownloadMgrBCTest::ManagerSetDefaultStringAttribute8Test ),
        ENTRY( "Manager AddObserverL test", CDownloadMgrBCTest::ManagerAddObserverLTest ),
        ENTRY( "Manager RemoveObserver test", CDownloadMgrBCTest::ManagerRemoveObserverTest ),
        ENTRY( "Manager SetNextUriObserver test", CDownloadMgrBCTest::ManagerSetNextUriObserverTest ),
        };

    // Verify that case number is valid
    if( (TUint) aCaseNumber >= sizeof( KCases ) / 
                               sizeof( TCaseInfoInternal ) )
        {

        // Invalid case, construct empty object
        TCaseInfo null( (const TText*) L"" );
        null.iMethod = NULL;
        null.iIsOOMTest = EFalse;
        null.iFirstMemoryAllocation = 0;
        null.iLastMemoryAllocation = 0;
        return null;

        } 

    // Construct TCaseInfo object and return it
    TCaseInfo tmp ( KCases[ aCaseNumber ].iCaseName );
    tmp.iMethod = KCases[ aCaseNumber ].iMethod;
    tmp.iIsOOMTest = KCases[ aCaseNumber ].iIsOOMTest;
    tmp.iFirstMemoryAllocation = KCases[ aCaseNumber ].iFirstMemoryAllocation;
    tmp.iLastMemoryAllocation = KCases[ aCaseNumber ].iLastMemoryAllocation;
    return tmp;

    }

void CDownloadMgrBCTest::HandleDMgrEventL( RHttpDownload& /*aDownload*/, THttpDownloadEvent /*aEvent*/ )
    {

    }

void CDownloadMgrBCTest::NextUriL( RHttpDownload& /*aDownload*/, const TDesC8& /*aUri*/ )
	{

	}


// -----------------------------------------------------------------------------
// CDownloadMgrBCTest::GetTestCasesL
// GetTestCases is used to inquire test cases from the Test Module. Test
// cases are stored to array of test cases. The Test Framework will be 
// the owner of the data in the RPointerArray after GetTestCases return
// and it does the memory deallocation. 
// -----------------------------------------------------------------------------
//
TInt CDownloadMgrBCTest::GetTestCasesL( 
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
// CDownloadMgrBCTest::RunTestCaseL
// RunTestCaseL is used to run an individual test case specified 
// by aTestCase. Test cases that can be run may be requested from 
// Test Module by GetTestCases method before calling RunTestCase.
// -----------------------------------------------------------------------------
//
TInt CDownloadMgrBCTest::RunTestCaseL(
    const TInt aCaseNumber,
    const TFileName& /*aConfig*/,
    TTestResult& aResult )
    {
    	SendTestModuleVersion();
    // Return value
    TInt execStatus = KErrNone;

    // Get the pointer to test case function
    TCaseInfo tmp = Case ( aCaseNumber );

    _LIT( KLogInfo, "Starting testcase [%S]" );
    iLog->Log( KLogInfo, &tmp.iCaseName);

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

// -----------------------------------------------------------------------------
// CDownloadMgrBCTest::OOMTestQueryL
// Used to check if a particular test case should be run in OOM conditions and 
// which memory allocations should fail.    
//
// NOTE: This method is virtual and must be implemented only if test case
// should be executed using OOM conditions.  
// -----------------------------------------------------------------------------
//
TBool CDownloadMgrBCTest::OOMTestQueryL( 
                                const TFileName& /* aTestCaseFile */, 
                                const TInt /* aCaseNumber */, 
                                TOOMFailureType& /* aFailureType */, 
                                TInt& /* aFirstMemFailure */, 
                                TInt& /* aLastMemFailure */ ) 
    {
    _LIT( KOOMTestQueryL, "CDownloadMgrBCTest::OOMTestQueryL" );
    iLog->Log( KOOMTestQueryL ); 

    return EFalse;

    }

// -----------------------------------------------------------------------------
// CDownloadMgrBCTest::OOMTestInitializeL
// Used to perform the test environment setup for a particular OOM test case. 
// Test Modules may use the initialization file to read parameters for Test 
// Module initialization but they can also have their own configure file or 
// some other routine to initialize themselves.  
//
// NOTE: This method is virtual and must be implemented only if test case
// should be executed using OOM conditions.  
// -----------------------------------------------------------------------------
//
void CDownloadMgrBCTest::OOMTestInitializeL( 
                                const TFileName& /* aTestCaseFile */, 
                                const TInt /* aCaseNumber */ )
    {
    }

// -----------------------------------------------------------------------------
// CDownloadMgrBCTest::OOMHandleWarningL
// In some cases the heap memory allocation should be skipped, either due to
// problems in the OS code or components used by the code being tested, or even 
// inside the tested components which are implemented this way on purpose (by 
// design), so it is important to give the tester a way to bypass allocation 
// failures.
//
// NOTE: This method is virtual and must be implemented only if test case
// should be executed using OOM conditions.  
// -----------------------------------------------------------------------------
//
void CDownloadMgrBCTest::OOMHandleWarningL( 
                                const TFileName& /* aTestCaseFile */,
                                const TInt /* aCaseNumber */, 
                                TInt& /* aFailNextValue */ )
    {
    }

// -----------------------------------------------------------------------------
// CDownloadMgrBCTest::OOMTestFinalizeL
// Used to perform the test environment cleanup for a particular OOM test case.
//
// NOTE: This method is virtual and must be implemented only if test case
// should be executed using OOM conditions.  
// -----------------------------------------------------------------------------
//                  
void CDownloadMgrBCTest::OOMTestFinalizeL( 
                                const TFileName& /* aTestCaseFile */, 
                                const TInt /* aCaseNumber */ )
    {
    }

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// LibEntryL is a polymorphic Dll entry point
// Returns: CTestModuleBase*: Pointer to Test Module object
// -----------------------------------------------------------------------------
//
EXPORT_C CTestModuleBase* LibEntryL()
    {
    return CDownloadMgrBCTest::NewL();

    }

// -----------------------------------------------------------------------------
// SetRequirements handles test module parameters(implements evolution
// version 1 for test module's heap and stack sizes configuring).
// Returns: TInt: Symbian error code.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt SetRequirements( CTestModuleParam*& /*aTestModuleParam*/, 
                                TUint32& /*aParameterValid*/ )
    {

    /* --------------------------------- NOTE ---------------------------------
    USER PANICS occurs in test thread creation when:
    1) "The panic occurs when the value of the stack size is negative."
    2) "The panic occurs if the minimum heap size specified is less
       than KMinHeapSize".
       KMinHeapSize: "Functions that require a new heap to be allocated will
       either panic, or will reset the required heap size to this value if
       a smaller heap size is specified".
    3) "The panic occurs if the minimum heap size specified is greater than
       the maximum size to which the heap can grow".
    Other:
    1) Make sure that your hardware or Symbian OS is supporting given sizes.
       e.g. Hardware might support only sizes that are divisible by four.
    ------------------------------- NOTE end ------------------------------- */

    // Normally STIF uses default heap and stack sizes for test thread, see:
    // KTestThreadMinHeap, KTestThreadMinHeap and KStackSize.
    // If needed heap and stack sizes can be configured here by user. Remove
    // comments and define sizes.

/*
    aParameterValid = KStifTestModuleParameterChanged;

    CTestModuleParamVer01* param = CTestModuleParamVer01::NewL();
    // Stack size
    param->iTestThreadStackSize= 16384; // 16K stack
    // Heap sizes
    param->iTestThreadMinHeap = 4096;   // 4K heap min
    param->iTestThreadMaxHeap = 1048576;// 1M heap max

    aTestModuleParam = param;
*/
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
