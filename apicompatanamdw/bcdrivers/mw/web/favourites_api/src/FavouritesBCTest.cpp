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
* Description:  FavouritesBCTest class member functions
*
*/



// INCLUDE FILES
#include <Stiftestinterface.h>
#include "FavouritesBCTest.h"

// EXTERNAL DATA STRUCTURES

// EXTERNAL FUNCTION PROTOTYPES  

// CONSTANTS

// MACROS

// LOCAL CONSTANTS AND MACROS

// MODULE DATA STRUCTURES

// LOCAL FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

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
// CFavouritesBCTest::CFavouritesBCTest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CFavouritesBCTest::CFavouritesBCTest()
    {

    }

// -----------------------------------------------------------------------------
// CFavouritesBCTest::ConstructL
// Symbian 2nd phase constructor can leave.
// Note: If OOM test case uses STIF Logger, then STIF Logger must be created
// with static buffer size parameter (aStaticBufferSize). Otherwise Logger 
// allocates memory from heap and therefore causes error situations with OOM 
// testing. For more information about STIF Logger construction, see STIF Users 
// Guide.
// -----------------------------------------------------------------------------
//
void CFavouritesBCTest::ConstructL()
    {
    iLog = CStifLogger::NewL( KFavouritesBCTestLogPath, 
                          KFavouritesBCTestLogFile);
                          
    User::LeaveIfError( iFileSystem.Connect() );

    User::LeaveIfError( iFavouritesSession.Connect() );
    }
//-----------------------------------------------------------------------------
// CFavouritesBCTest::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CFavouritesBCTest::SendTestModuleVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_MODULE_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_MODULE_VERSION_MINOR;
	moduleVersion.iBuild = TEST_MODULE_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("FavouritesBCTest.dll");
	

	TBool newVersionOfMethod = ETrue;
	CTestModuleIf &test=TestModuleIf();
	test.SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
	test.SetBehavior(CTestModuleIf::ETestLeaksHandles);
	}

// -----------------------------------------------------------------------------
// CFavouritesBCTest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CFavouritesBCTest* CFavouritesBCTest::NewL()
    {
    CFavouritesBCTest* self = new (ELeave) CFavouritesBCTest;

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CFavouritesBCTest::~CFavouritesBCTest()
    {
    iFavouritesDb.Close();
    iFavouritesSession.Close();
    iFileSystem.Close();
    delete iLog;
    }

// ----------------------------------------------------------
// CFavouritesDbTester::MapAccessPoint()
// ----------------------------------------------------------
//
TBool CFavouritesBCTest::MapAccessPoint
( TUint aOldUid, TUint& aNewUid )
    {
    aNewUid = aOldUid;
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CFavouritesBCTest::InitL
// InitL is used to initialize the Test Module.
// -----------------------------------------------------------------------------
//
TInt CFavouritesBCTest::InitL( 
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
const TCaseInfo CFavouritesBCTest::Case ( 
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
                
        ENTRY( "Item NewLC test", CFavouritesBCTest::ItemNewLCTestL ),
        ENTRY( "Item NewL test", CFavouritesBCTest::ItemNewLTestL ),
        ENTRY( "Item Destructor test", CFavouritesBCTest::ItemDestructorTestL ),
        ENTRY( "Item Assign(=) operator test", CFavouritesBCTest::ItemAssignTestL ),
        ENTRY( "Item Uid test", CFavouritesBCTest::ItemUidTestL ),
        ENTRY( "Item ParentFolder test", CFavouritesBCTest::ItemParentFolderTestL ),
        ENTRY( "Item Type test", CFavouritesBCTest::ItemTypeTestL ),
        ENTRY( "Item Name test", CFavouritesBCTest::ItemNameTestL ),
        ENTRY( "Item Url test", CFavouritesBCTest::ItemUrlTestL ),
        ENTRY( "Item WapAp test", CFavouritesBCTest::ItemWapApTestL ),
        ENTRY( "Item UserName test", CFavouritesBCTest::ItemUserNameTestL ),
        ENTRY( "Item Password test", CFavouritesBCTest::ItemPasswordTestL ),
        ENTRY( "Item ContextId test", CFavouritesBCTest::ItemContextIdTestL ),
        ENTRY( "Item IsItem test", CFavouritesBCTest::ItemIsItemTestL ),
        ENTRY( "Item IsFolder test", CFavouritesBCTest::ItemIsFolderTestL ),
        ENTRY( "Item IsFactoryItem test", CFavouritesBCTest::ItemIsFactoryItemTestL ),
        ENTRY( "Item IsReadOnly test", CFavouritesBCTest::ItemIsReadOnlyTestL ),
        ENTRY( "Item Modified test", CFavouritesBCTest::ItemModifiedTestL ),
        ENTRY( "Item ClearL test", CFavouritesBCTest::ItemClearLTestL ),
        ENTRY( "Item SetParentFolder test", CFavouritesBCTest::ItemSetParentFolderTestL ),
        ENTRY( "Item SetType test", CFavouritesBCTest::ItemSetTypeTestL ),
        ENTRY( "Item SetNameL test", CFavouritesBCTest::ItemSetNameLTestL ),
        ENTRY( "Item SetUrlL test", CFavouritesBCTest::ItemSetUrlLTestL ),
        ENTRY( "Item SetWapAp test", CFavouritesBCTest::ItemSetWapApTestL ),
        ENTRY( "Item SetUserNameL test", CFavouritesBCTest::ItemSetUserNameLTestL ),
        ENTRY( "Item SetPasswordL test", CFavouritesBCTest::ItemSetPasswordLTestL ),
        ENTRY( "Item SetContextId test", CFavouritesBCTest::ItemSetContextIdTestL ),
        ENTRY( "List Constructor test", CFavouritesBCTest::ListConstructorTestL ),
        ENTRY( "List Destructor test", CFavouritesBCTest::ListDestructorTestL ),
        ENTRY( "List Delete test", CFavouritesBCTest::ListDeleteTestL ),
        ENTRY( "List Delete Range test", CFavouritesBCTest::ListDeleteRangeTestL ),
        ENTRY( "List Sort test", CFavouritesBCTest::ListSortTestL ),
        ENTRY( "List UidToIndex test", CFavouritesBCTest::ListUidToIndexTestL ),
        ENTRY( "List IndexToUid test", CFavouritesBCTest::ListIndexToUidTestL ),
        ENTRY( "List ItemByUid test", CFavouritesBCTest::ListItemByUidTestL ),
        ENTRY( "Db Open test", CFavouritesBCTest::DbOpenTestL ),
        ENTRY( "Db Version test", CFavouritesBCTest::DbVersionTestL ),
        ENTRY( "Db IsDamaged test", CFavouritesBCTest::DbIsDamagedTestL ),
        ENTRY( "Db Recover test", CFavouritesBCTest::DbRecoverTestL ),
        ENTRY( "Db Compact test", CFavouritesBCTest::DbCompactTestL ),
        ENTRY( "Db Size test", CFavouritesBCTest::DbSizeTestL ),
        ENTRY( "Db UpdateStats test", CFavouritesBCTest::DbUpdateStatsTestL ),
        ENTRY( "Db Begin test", CFavouritesBCTest::DbBeginTestL ),
        ENTRY( "Db Commit test", CFavouritesBCTest::DbCommitTestL ),
        ENTRY( "Db Rollback test", CFavouritesBCTest::DbRollbackTestL ),
        ENTRY( "Db CleanupRollbackPushL test", CFavouritesBCTest::DbCleanupRollbackPushLTestL ),
        ENTRY( "Db Get test", CFavouritesBCTest::DbGetTestL ),
        ENTRY( "Db GetAll test", CFavouritesBCTest::DbGetAllTestL ),
        ENTRY( "Db GetUids test", CFavouritesBCTest::DbGetUidsTestL ),
        ENTRY( "Db PreferredUid test", CFavouritesBCTest::DbPreferredUidTestL ),
        ENTRY( "Db Delete test", CFavouritesBCTest::DbDeleteTestL ),
        ENTRY( "Db Update test", CFavouritesBCTest::DbUpdateTestL ),
        ENTRY( "Db Add test", CFavouritesBCTest::DbAddTestL ),
        ENTRY( "Db SetHomepage test", CFavouritesBCTest::DbSetHomepageTestL ),
        ENTRY( "Db SetLastVisited test", CFavouritesBCTest::DbSetLastVisitedTestL ),
        ENTRY( "Db SetFactoryItem test", CFavouritesBCTest::DbSetFactoryItemTestL ),
        ENTRY( "Db SetReadOnly test", CFavouritesBCTest::DbSetReadOnlyTestL ),
        ENTRY( "Db SetModified test", CFavouritesBCTest::DbSetModifiedTestL ),
        ENTRY( "Db SetPreferredUid test", CFavouritesBCTest::DbSetPreferredUidTestL ),
        ENTRY( "Db ItemExists test", CFavouritesBCTest::DbItemExistsTestL ),
        ENTRY( "Db FolderExists test", CFavouritesBCTest::DbFolderExistsTestL ),
        ENTRY( "Db Count test", CFavouritesBCTest::DbCountTestL ),
        ENTRY( "Db SetData test", CFavouritesBCTest::DbSetDataTestL ),
        ENTRY( "Db GetData test", CFavouritesBCTest::DbGetDataTestL ),
        ENTRY( "Db SetBrowserData test", CFavouritesBCTest::DbSetBrowserDataTestL ),
        ENTRY( "Db GetBrowserData test", CFavouritesBCTest::DbGetBrowserDataTestL ),
        ENTRY( "Db MakeUniqueName with folder test", CFavouritesBCTest::DbMakeUniqueNameWithFolderTestL ),
        ENTRY( "Db MakeUniqueName test", CFavouritesBCTest::DbMakeUniqueNameTestL ),
        ENTRY( "Db CreateStartPageItemL test", CFavouritesBCTest::DbCreateStartPageItemLTestL ),
        ENTRY( "Db CreateAdaptiveItemsFolderL test", CFavouritesBCTest::DbCreateAdaptiveItemsFolderLTestL ),
        ENTRY( "Db DeleteFile test", CFavouritesBCTest::DbDeleteFileTestL ),
//        ENTRY( "Db RestoreFactorySettingsL test", CFavouritesBCTest::DbRestoreFactorySettingsLTestL ),
        ENTRY( "WapAp Constructor test", CFavouritesBCTest::WapApConstructorTest ),
        ENTRY( "WapAp Assign with Ap test", CFavouritesBCTest::WapApAssignWithApTest ),
        ENTRY( "WapAp Assign with ApId test", CFavouritesBCTest::WapApAssignWithApIdTest ),
        ENTRY( "WapAp SetNull test", CFavouritesBCTest::WapApSetNullTest ),
        ENTRY( "WapAp SetDefault test", CFavouritesBCTest::WapApSetDefaultTest ),
        ENTRY( "WapAp SetApId test", CFavouritesBCTest::WapApSetApIdTest ),
        ENTRY( "WapAp IsNull test", CFavouritesBCTest::WapApIsNullTest ),
        ENTRY( "WapAp IsDefault test", CFavouritesBCTest::WapApIsDefaultTest ),
        ENTRY( "WapAp ApId test", CFavouritesBCTest::WapApApIdTest ),
        ENTRY( "DbInc Recover test", CFavouritesBCTest::DbIncRecoverTestL ),
        ENTRY( "DbInc Compact test", CFavouritesBCTest::DbIncCompactTestL ),
        ENTRY( "DbInc Next test", CFavouritesBCTest::DbIncNextTestL ),
        ENTRY( "File Close test", CFavouritesBCTest::FileCloseTestL ),
        ENTRY( "File Open test", CFavouritesBCTest::FileOpenTestL ),
        ENTRY( "File Replace test", CFavouritesBCTest::FileReplaceTestL ),
        ENTRY( "File Read test", CFavouritesBCTest::FileReadTestL ),
        ENTRY( "File Write test", CFavouritesBCTest::FileWriteTestL ),
        ENTRY( "File Size test", CFavouritesBCTest::FileSizeTestL ),
        ENTRY( "Session Version test", CFavouritesBCTest::SessionVersionTest ),
        ENTRY( "Session Connect test", CFavouritesBCTest::SessionConnectTest ),
        ENTRY( "Session ResourceMark test", CFavouritesBCTest::SessionResourceMarkTest ),
        ENTRY( "Session ResourceCheck test", CFavouritesBCTest::SessionResourceCheckTest ),
        ENTRY( "Session ResourceCount test", CFavouritesBCTest::SessionResourceCountTest ),
        ENTRY( "Session DeleteDatabase test", CFavouritesBCTest::SessionDeleteDatabaseTestL ),
        ENTRY( "Session __DbgSetAllocFail test", CFavouritesBCTest::SessionDbgSetAllocFailTest ),
        ENTRY( "Notifier constructor test", CFavouritesBCTest::NotifierConstructorTestL ),
        ENTRY( "Notifier destructor test", CFavouritesBCTest::NotifierDestructorTestL ),
        ENTRY( "Notifier Start test", CFavouritesBCTest::NotifierStartTestL ),
        ENTRY( "Db DeleteFolder test", CFavouritesBCTest::DbDeleteFolderTestL ),
        ENTRY( "Item IsHidden test", CFavouritesBCTest::ItemIsHiddenTestL ),
        ENTRY( "Item SetHidden test", CFavouritesBCTest::ItemSetHiddenTestL )
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

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: CreatePopulatedDb

    Description: Populate a test db with items.
  
    Parameters:  None   

    Return Values: None

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
void CFavouritesBCTest::CreatePopulatedDbL()
    {
    DestroyDbItems();

    // Create reference items in inst vars.
    CreateFolderL( iItemFolder1 );
    CreateFolderL( iItemFolder2 );
    CreateItemL( iItem1 );
    CreateItemL( iItem2 );
    CreateItemL( iItem3 );
    CreateItemL( iItem4 );
    CreateItemL( iItem5 );
    CreateItemL( iItem6 );

    // Add items to database.
    iFavouritesDb.Add( *iItemFolder1, EFalse );
    iFavouritesDb.Add( *iItemFolder2, EFalse );

    iItem3->SetParentFolder( iItemFolder1->Uid() );
    iItem4->SetParentFolder( iItemFolder1->Uid() );
    iItem5->SetParentFolder( iItemFolder2->Uid() );
    iItem6->SetParentFolder( iItemFolder2->Uid() );

    // Insert out of order for sort test
    iFavouritesDb.Add( *iItem5, EFalse );
    iFavouritesDb.Add( *iItem1, EFalse );
    iFavouritesDb.Add( *iItem6, EFalse );
    iFavouritesDb.Add( *iItem3, EFalse );
    iFavouritesDb.Add( *iItem2, EFalse );
    iFavouritesDb.Add( *iItem4, EFalse );

    }

/*
-------------------------------------------------------------------------------

    Class: CFavouritesBCTest

    Method: DestroyDb

    Description: Delete the test database and all items in it.
  
    Parameters:  None

    Return Values: None

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
void CFavouritesBCTest::DestroyDbItems()
    {
    delete iItemFolder1;
    delete iItemFolder2;
    delete iItem1;
    delete iItem2;
    delete iItem3;
    delete iItem4;
    delete iItem5;
    delete iItem6;

    iItemFolder1 = NULL;
    iItemFolder2 = NULL;
    iItem1 = NULL;
    iItem2 = NULL;
    iItem3 = NULL;
    iItem4 = NULL;
    iItem5 = NULL;
    iItem6 = NULL;
    }

// -----------------------------------------------------------------------------
// CFavouritesBCTest::GetTestCasesL
// GetTestCases is used to inquire test cases from the Test Module. Test
// cases are stored to array of test cases. The Test Framework will be 
// the owner of the data in the RPointerArray after GetTestCases return
// and it does the memory deallocation. 
// -----------------------------------------------------------------------------
//
TInt CFavouritesBCTest::GetTestCasesL( 
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
// CFavouritesBCTest::RunTestCaseL
// RunTestCaseL is used to run an individual test case specified 
// by aTestCase. Test cases that can be run may be requested from 
// Test Module by GetTestCases method before calling RunTestCase.
// -----------------------------------------------------------------------------
//
TInt CFavouritesBCTest::RunTestCaseL(
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
// CFavouritesBCTest::OOMTestQueryL
// Used to check if a particular test case should be run in OOM conditions and 
// which memory allocations should fail.    
//
// NOTE: This method is virtual and must be implemented only if test case
// should be executed using OOM conditions.  
// -----------------------------------------------------------------------------
//
TBool CFavouritesBCTest::OOMTestQueryL( 
                                const TFileName& /* aTestCaseFile */, 
                                const TInt /* aCaseNumber */, 
                                TOOMFailureType& /* aFailureType */, 
                                TInt& /* aFirstMemFailure */, 
                                TInt& /* aLastMemFailure */ ) 
    {
    _LIT( KOOMTestQueryL, "CFavouritesBCTest::OOMTestQueryL" );
    iLog->Log( KOOMTestQueryL ); 

    return EFalse;

    }

// -----------------------------------------------------------------------------
// CFavouritesBCTest::OOMTestInitializeL
// Used to perform the test environment setup for a particular OOM test case. 
// Test Modules may use the initialization file to read parameters for Test 
// Module initialization but they can also have their own configure file or 
// some other routine to initialize themselves.  
//
// NOTE: This method is virtual and must be implemented only if test case
// should be executed using OOM conditions.  
// -----------------------------------------------------------------------------
//
void CFavouritesBCTest::OOMTestInitializeL( 
                                const TFileName& /* aTestCaseFile */, 
                                const TInt /* aCaseNumber */ )
    {
    }

// -----------------------------------------------------------------------------
// CFavouritesBCTest::OOMHandleWarningL
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
void CFavouritesBCTest::OOMHandleWarningL( 
                                const TFileName& /* aTestCaseFile */,
                                const TInt /* aCaseNumber */, 
                                TInt& /* aFailNextValue */ )
    {
    }

// -----------------------------------------------------------------------------
// CFavouritesBCTest::OOMTestFinalizeL
// Used to perform the test environment cleanup for a particular OOM test case.
//
// NOTE: This method is virtual and must be implemented only if test case
// should be executed using OOM conditions.  
// -----------------------------------------------------------------------------
//                  
void CFavouritesBCTest::OOMTestFinalizeL( 
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
    return CFavouritesBCTest::NewL();

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
