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
* Description:  DownloadMgrBCTest test module.
*
*/



#ifndef DOWNLOADMGRBCTEST_H
#define DOWNLOADMGRBCTEST_H

// INCLUDES
#include "StifTestModule.h"
#include <StifLogger.h>
#include <f32file.h>
#include <DownloadMgrClient.h>
#include <CDownloadMgrUiLibRegistry.h>

// CONSTANTS
const TInt KThisAppUid = 0x101FB3E7;

// MACROS
//#define ?macro ?macro_def
#define TEST_MODULE_VERSION_MAJOR 51
#define TEST_MODULE_VERSION_MINOR 9
#define TEST_MODULE_VERSION_BUILD 38

// Logging path
_LIT( KDownloadMgrBCTestLogPath, "\\logs\\testframework\\DownloadMgrBCTest\\" ); 
// Log file
_LIT( KDownloadMgrBCTestLogFile, "DownloadMgrBCTest.txt" ); 

// Function pointer related internal definitions
// Rounding known bug in GCC

#ifdef __VC32__
#define GETPTR 
#else
#define GETPTR &
#endif  
#define ENTRY(str,func) {_S(str), GETPTR func,0,0,0}
#define FUNCENTRY(func) {_S(#func), GETPTR func,0,0,0}
#define OOM_ENTRY(str,func,a,b,c) {_S(str), GETPTR func,a,b,c}
#define OOM_FUNCENTRY(func,a,b,c) {_S(#func), GETPTR func,a,b,c}

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
class CDownloadMgrBCTest;
class CActiveDownloadMgrDbNotifier;

// A typedef for function that does the actual testing,
// function is a type 
// TInt CDemoModule::<NameOfFunction> ( TTestResult& aResult )
typedef TInt (CDownloadMgrBCTest::* TestFunction)(TTestResult&);    

// CLASS DECLARATION

/**
*  An internal structure containing a test case name and
*  the pointer to function doing the test
*
*  @lib ?library
*  @since ?Series60_version
*/
class TCaseInfoInternal
    {
    public:
        const TText*    iCaseName;
        TestFunction    iMethod;
        TBool           iIsOOMTest;
        TInt            iFirstMemoryAllocation;
        TInt            iLastMemoryAllocation;
    };

// CLASS DECLARATION

/**
*  A structure containing a test case name and
*  the pointer to function doing the test
*
*  @lib ?library
*  @since ?Series60_version
*/
class TCaseInfo
    {
    public:
        TPtrC           iCaseName;    
        TestFunction    iMethod;
        TBool           iIsOOMTest;
        TInt            iFirstMemoryAllocation;
        TInt            iLastMemoryAllocation;

    TCaseInfo( const TText* a ) : iCaseName( (TText*) a )
        {        
        };

    };

// CLASS DECLARATION

/**
*  This a DownloadMgrBCTest class.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CDownloadMgrBCTest) : public CTestModuleBase,
                                        public MHttpDownloadMgrObserver,
                                        public MHttpDownloadMgrNextUriObserver
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CDownloadMgrBCTest* NewL();

        /**
        * Destructor.
        */
        virtual ~CDownloadMgrBCTest();

    public: // New functions

        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );

    public: // Functions from base classes

        /**
        * From CTestModuleBase InitL is used to initialize the DownloadMgrBCTest. 
        *       It is called once for every instance of DownloadMgrBCTest after
        *       its creation.
        * @since ?Series60_version
        * @param aIniFile Initialization file for the test module (optional)
        * @param aFirstTime Flag is true when InitL is executed for first 
        *               created instance of DownloadMgrBCTest.
        * @return Symbian OS error code
        */
        TInt InitL( TFileName& aIniFile, TBool aFirstTime );

        /**
        * From CTestModuleBase GetTestCasesL is used to inquiry test cases 
        *   from DownloadMgrBCTest. 
        * @since ?Series60_version
        * @param aTestCaseFile Test case file (optional)
        * @param aTestCases  Array of TestCases returned to test framework
        * @return Symbian OS error code
        */
        TInt GetTestCasesL( const TFileName& aTestCaseFile, 
                            RPointerArray<TTestCaseInfo>& aTestCases );

        /**
        * From CTestModuleBase RunTestCaseL is used to run an individual 
        *   test case. 
        * @since ?Series60_version
        * @param aCaseNumber Test case number
        * @param aTestCaseFile Test case file (optional)
        * @param aResult Test case result returned to test framework (PASS/FAIL)
        * @return Symbian OS error code (test case execution error, which is 
        *           not reported in aResult parameter as test case failure).
        */   
        TInt RunTestCaseL( const TInt aCaseNumber, 
                           const TFileName& aTestCaseFile,
                           TTestResult& aResult );

        /**
        * From CTestModuleBase; OOMTestQueryL is used to specify is particular
        * test case going to be executed using OOM conditions
        * @param aTestCaseFile Test case file (optional)
        * @param aCaseNumber Test case number (optional)
        * @param aFailureType OOM failure type (optional)
        * @param aFirstMemFailure The first heap memory allocation failure value (optional)
        * @param aLastMemFailure The last heap memory allocation failure value (optional)
        * @return TBool
        */
        virtual TBool OOMTestQueryL( const TFileName& /* aTestCaseFile */, 
                                     const TInt /* aCaseNumber */, 
                                     TOOMFailureType& /* aFailureType */,
                                     TInt& /* aFirstMemFailure */, 
                                     TInt& /* aLastMemFailure */ );

        /**
        * From CTestModuleBase; User may add implementation for OOM test 
        * environment initialization. Usually no implementation is required.
        * @param aTestCaseFile Test case file (optional)
        * @param aCaseNumber Test case number (optional)
        * @return None
        */
        virtual void OOMTestInitializeL( const TFileName& /* aTestCaseFile */, 
                                    const TInt /* aCaseNumber */ ); 

        /**
        * From CTestModuleBase; OOMHandleWarningL. User may add implementation 
        * for OOM test warning handling. Usually no implementation is required.
        * @param aTestCaseFile Test case file (optional)
        * @param aCaseNumber Test case number (optional)
        * @param aFailNextValue FailNextValue for OOM test execution (optional)
        * @return None
        */
        virtual void OOMHandleWarningL( const TFileName& /* aTestCaseFile */,
                                        const TInt /* aCaseNumber */, 
                                        TInt& /* aFailNextValue */);

        /**
        * From CTestModuleBase; OOMTestFinalizeL may be used to finalize OOM
        * test environment. Usually no implementation is required.
        * @param aTestCaseFile Test case file (optional)
        * @param aCaseNumber Test case number (optional)
        * @return None
        */
        virtual void OOMTestFinalizeL( const TFileName& /* aTestCaseFile */, 
                                       const TInt /* aCaseNumber */ );
				/**
         * Method used to log version of test module
         */
        void SendTestModuleVersion();
                                       

    private:    // from MHttpDownloadMgrObserver

        void HandleDMgrEventL( RHttpDownload& aDownload, THttpDownloadEvent aEvent );

    private:    // from MHttpDownloadMgrObserver

        void NextUriL( RHttpDownload& aDownload, const TDesC8& aUri );

    private:   // Functions to test RHttpDownload interface

        /**
        * RHttpDownload Start test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadStartTest( TTestResult& aResult );
        
        /**
        * RHttpDownload Pause test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadPauseTest( TTestResult& aResult );
        
        /**
        * RHttpDownload Reset test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadResetTest( TTestResult& aResult );
        
        /**
        * RHttpDownload Delete test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadDeleteTest( TTestResult& aResult );
        
        /**
        * RHttpDownload Move test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadMoveTest( TTestResult& aResult );
        
        /**
        * RHttpDownload GetIntAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadGetIntAttributeTest( TTestResult& aResult );
        
        /**
        * RHttpDownload GetBoolAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadGetBoolAttributeTest( TTestResult& aResult );
        
        /**
        * RHttpDownload GetStringAttribute test case with TDes16 argument.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadGetStringAttribute16Test( TTestResult& aResult );
        
        /**
        * RHttpDownload GetStringAttribute test case with TDes8 argument.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadGetStringAttribute8Test( TTestResult& aResult );
        
        /**
        * RHttpDownload GetFileHandleAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadGetFileHandleAttributeTest( TTestResult& aResult );
        
        /**
        * RHttpDownload SetIntAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadSetIntAttributeTest( TTestResult& aResult );
        
        /**
        * RHttpDownload SetBoolAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadSetBoolAttributeTest( TTestResult& aResult );
        
        /**
        * RHttpDownload SetStringAttribute test case with TDes16 argument.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadSetStringAttribute16Test( TTestResult& aResult );
        
        /**
        * RHttpDownload SetStringAttribute test case with TDes8 argument.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadSetStringAttribute8Test( TTestResult& aResult );
        
        /**
        * RHttpDownload SetFileHandleAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadSetFileHandleAttributeTest( TTestResult& aResult );

    private:   // Functions to test RHttpDownloadMgr interface

        /**
        * RHttpDownloadMgr ConnectL test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerConnectLTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr Version test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerVersionTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr Close test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerCloseTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr CurrentDownloads test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerCurrentDownloadsTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr CreateDownloadL test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerCreateDownloadLWithBoolTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr CreateDownloadL test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerCreateDownloadLTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr CreateClientSideDownloadL test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerCreateClientSideDownloadLTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr CreateCodDownloadL test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerCreateCodDownloadLTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr FindDownload test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerFindDownloadTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr PauseAll test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerPauseAllTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr StartAll test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerStartAllTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr ResetAll test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerResetAllTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr DeleteAll test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerDeleteAllTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr Disconnect test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerDisconnectTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr GetIntAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerGetIntAttributeTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr GetBoolAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerGetBoolAttributeTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr GetStringAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerGetStringAttribute16Test( TTestResult& aResult );

        /**
        * RHttpDownloadMgr GetStringAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerGetStringAttribute8Test( TTestResult& aResult );

        /**
        * RHttpDownloadMgr SetIntAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerSetIntAttributeTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr SetBoolAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerSetBoolAttributeTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr SetStringAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerSetStringAttribute16Test( TTestResult& aResult );

        /**
        * RHttpDownloadMgr SetStringAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerSetStringAttribute8Test( TTestResult& aResult );

        /**
        * RHttpDownloadMgr SetDefaultIntAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerSetDefaultIntAttributeTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr SetDefaultBoolAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerSetDefaultBoolAttributeTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr SetDefaultStringAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerSetDefaultStringAttribute16Test( TTestResult& aResult );

        /**
        * RHttpDownloadMgr SetDefaultStringAttribute test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerSetDefaultStringAttribute8Test( TTestResult& aResult );

        /**
        * RHttpDownloadMgr AddObserverL test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerAddObserverLTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr RemoveObserver test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerRemoveObserverTest( TTestResult& aResult );

        /**
        * RHttpDownloadMgr SetNextUriObserver test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerSetNextUriObserverTest( TTestResult& aResult );
        
        /**
        * RHttpDownloadMgr GetIntAttribute Album test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt ManagerGetIntAttributeTestAlbum( TTestResult& aResult );
        
  
 /**
        * RHttpDownloadMgr GetIntAttribute Album test case.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadGetBoolAttributeTestAlbum( TTestResult& aResult );

  /**
        * RHttpDownload GetStringAttribute test case with TDes16 argument.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadGetStringAttribute16TestAlbum( TTestResult& aResult );
               
  /**
        * RHttpDownload GetStringAttribute test case with TDes16 argument.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadGetStringAttribute8TestAlbum( TTestResult& aResult );      
        
        
        /**
        * RHttpDownload SetStringAttribute test case with TDes16 argument.
        * @since ?Series60_version
        * @param aResult Test case result (PASS/FAIL)
        * @return Symbian OS error code (test case execution error 
        *   that is not returned as test case result in aResult)
        */
        TInt DownloadSetStringAttribute16TestAlbum( TTestResult& aResult );
               
  /**
    * Sets the download data (media information).
    * @param sizeBytes The length of descriptor (second parameter) in bytes.
		* @param aValue The value to be set.
    * @return None.
   */
     TInt SetDownloadDataAttribute( TTestResult& aResult );
     
       /**
    * Sets the download data (media information).
    * @param sizeBytes The length of descriptor (second parameter) in bytes.
		* @param aValue The value to be set.
    * @return None.
   */
     TInt SetTrackDataAttribute( TTestResult& aResult );
               
               
    private:

        /**
        * C++ default constructor.
        */
        CDownloadMgrBCTest();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        // Prohibit copy constructor if not deriving from CBase.
        // ?classname( const ?classname& );
        // Prohibit assigment operator if not deriving from CBase.
        // ?classname& operator=( const ?classname& );

        /**
        * Function returning test case name and pointer to test case function.
        * @since ?Series60_version
        * @param aCaseNumber test case number
        * @return TCaseInfo 
        */
        const TCaseInfo Case ( const TInt aCaseNumber ) const;

    public:     // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        // Pointer to test (function) to be executed
        TestFunction iMethod;

        CStifLogger * iLog;
        
        RFs iFileSystem;
        RHttpDownloadMgr  iDownloadManager;

        // Reserved pointer for future extension
        //TAny* iReserved;

    public:     // Friend classes
        //?friend_class_declaration;
    protected:  // Friend classes
        //?friend_class_declaration;
    private:    // Friend classes
        //?friend_class_declaration;

    };

#endif      // DOWNLOADMGRBCTEST_H

// End of File
