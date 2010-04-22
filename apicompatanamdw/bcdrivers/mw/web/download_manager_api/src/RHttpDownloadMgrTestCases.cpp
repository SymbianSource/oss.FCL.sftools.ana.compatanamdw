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
* Description: 
*
*
*/



// INCLUDE FILES
#include <e32math.h>
#include <es_sock.h>
#include "DownloadMgrBCTest.h"

// EXTERNAL DATA STRUCTURES
// None

// EXTERNAL FUNCTION PROTOTYPES
// None

// CONSTANTS
// None

// MACROS
// None

// LOCAL CONSTANTS AND MACROS
// None

// MODULE DATA STRUCTURES
// None

// LOCAL FUNCTION PROTOTYPES
// None

// FORWARD DECLARATIONS
// None

// ==================== LOCAL FUNCTIONS =======================================

// ============================ MEMBER FUNCTIONS ===============================

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerConnectLTest

    Description: Test the RHttpDownloadMgr ConnectL method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerConnectLTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr ConnectL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    RHttpDownloadMgr downloadMgr;

    downloadMgr.ConnectL( TUid::Uid( KThisAppUid ), *this, EFalse );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

	// RHttpDownloadMgr::ConnectL provides no results, so if we've gotten this far assume success
    _LIT( KDescription , "Test case passed" );
    aResult.SetResult( KErrNone, KDescription );

    downloadMgr.Close();

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerVersionTest

    Description: Test the RHttpDownloadMgr Version method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerVersionTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr Version method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    TVersion version;

    version = iDownloadManager.Version();

    if (version.iMinor > 0)
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerCloseTest

    Description: Test the RHttpDownloadMgr Close method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerCloseTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr Close method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    RHttpDownloadMgr downloadMgr;

    downloadMgr.ConnectL( TUid::Uid( KThisAppUid ), *this, EFalse );

    downloadMgr.Close();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

	// RHttpDownloadMgr::Close provides no results, so if we've gotten this far assume success
    _LIT( KDescription , "Test case passed" );
    aResult.SetResult( KErrNone, KDescription );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerCurrentDownloadsTest

    Description: Test the RHttpDownloadMgr CurrentDownloads method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerCurrentDownloadsTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr CurrentDownloads method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    const CDownloadArray* array;
    array = &iDownloadManager.CurrentDownloads();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if (array->Count() == 0)
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerCreateDownloadLWithBoolTest

    Description: Test the RHttpDownloadMgr CreateDownloadL method with TBool argument.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerCreateDownloadLWithBoolTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr CreateDownloadL method with TBool argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ( &download != NULL )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerCreateDownloadLTest

    Description: Test the RHttpDownloadMgr CreateDownloadL method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerCreateDownloadLTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr CreateDownloadL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    RHttpDownload& download = iDownloadManager.CreateDownloadL( url );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ( &download != NULL )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerCreateClientSideDownloadLTest

    Description: Test the RHttpDownloadMgr CreateClientSideDownloadL method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerCreateClientSideDownloadLTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr CreateClientSideDownloadL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    _LIT( KUnableToTest1 ,"Unable to test CreateClientSideDownloadL method");
    TestModuleIf().Printf( 0, KDefinition, KUnableToTest1 );

    _LIT( KUnableToTest2 ,"S60 3rd Edition SDK does not provide a way to create the required CHttpTransaction");
    TestModuleIf().Printf( 0, KDefinition, KUnableToTest2 );

//    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
//    CleanupStack::PushL( scheduler );
//    CActiveScheduler::Install( scheduler );

//    CUrlRequestInfo* requestInfo = CUrlRequestInfo::NewL();
//    CleanupStack::NewL( requestInfo );
//    _LIT( KUrl, "http://testsuite.nokia-boston.com");
//    requestInfo->SetUrlL( KUrl() );

//    TBool isNewDl = ETrue;
//    RHttpDownload& download = iDownloadManager.CreateClientSideDownloadL( NULL, isNewDl );
//    RHttpDownload& download = NULL;

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

//    if ( &download != NULL )
//	    {
//	    _LIT( KDescription , "Test case passed" );
//	    aResult.SetResult( KErrNone, KDescription );
//	    }
//    else
//	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
//	    }

//    iDownloadManager.DeleteAll();
//    CleanupStack::PopAndDestroy( 2 ); // scheduler, requestInfo

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerCreateCodDownloadLTest

    Description: Test the RHttpDownloadMgr CreateCodDownloadL method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerCreateCodDownloadLTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr CreateCodDownloadL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    _LIT8( KCodUrl, "testsuite.nokia-boston.com" );
    HBufC8* buf = HBufC8::NewLC( KCodUrl().Length() );
    buf->Des().Copy( KCodUrl() );
    _LIT8( KCodMimeType, "text/x-co-desc" );


    TInt retVal;
    RHttpDownload* download;
    download = &iDownloadManager.CreateCodDownloadL( KCodUrl(),
        	                                         buf->Des(),
        	                                         KCodMimeType(),
        	                                         NULL,
        	                                         retVal );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ( &download != NULL )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy( 2 ); // scheduler, buf

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerFindDownloadTest

    Description: Test the RHttpDownloadMgr FindDownload method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerFindDownloadTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr FindDownload method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    TBuf<128> url = _L("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");
    _LIT8( KMsgBody, "123456789123456789123456789");

    HBufC8* urlToFind = HBufC8::NewLC( url.Length() );
    urlToFind->Des().Copy( url );

    RHttpDownload* download = iDownloadManager.FindDownload( *urlToFind, KMsgBody() );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ( download == NULL )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // urlToFind

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerPauseAllTest

    Description: Test the RHttpDownloadMgr PauseAll method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerPauseAllTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr PauseAll method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    RHttpDownload& download = iDownloadManager.CreateDownloadL( url );

    download.Start();

    TInt result = iDownloadManager.PauseAll();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerStartAllTest

    Description: Test the RHttpDownloadMgr StartAll method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerStartAllTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr StartAll method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    RHttpDownload& download = iDownloadManager.CreateDownloadL( url );

    TInt result = iDownloadManager.StartAll();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerResetAllTest

    Description: Test the RHttpDownloadMgr ResetAll method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerResetAllTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr ResetAll method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    RHttpDownload& download = iDownloadManager.CreateDownloadL( url );

    iDownloadManager.StartAll();

    TInt result = iDownloadManager.ResetAll();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerDeleteAllTest

    Description: Test the RHttpDownloadMgr DeleteAll method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerDeleteAllTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr DeleteAll method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    RHttpDownload& download = iDownloadManager.CreateDownloadL( url );

    TInt result = iDownloadManager.DeleteAll();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerDisconnectTest

    Description: Test the RHttpDownloadMgr Disconnect method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerDisconnectTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr Disconnect method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    RHttpDownload& download = iDownloadManager.CreateDownloadL( url );

    TInt result = iDownloadManager.Disconnect();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if ( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerGetIntAttributeTest

    Description: Test the RHttpDownloadMgr GetIntAttribute method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerGetIntAttributeTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr GetIntAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TInt32 value;
    TInt result = iDownloadManager.GetIntAttribute( EDlMgrAppUid, value );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerGetBoolAttributeTest

    Description: Test the RHttpDownloadMgr GetBoolAttribute method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerGetBoolAttributeTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr GetBoolAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBool value;
    TInt result = iDownloadManager.GetBoolAttribute( EDlMgrConnected, value );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerGetStringAttribute16Test

    Description: Test the RHttpDownloadMgr GetStringAttribute method with TDesC16 argument.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerGetStringAttribute16Test( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr GetStringAttribute method with TDesC16 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    HBufC16* stringAttr = HBufC16::NewLC( KMaxUrlLength );
    TPtr16 stringAttrPtr = stringAttr->Des();
    TInt result = iDownloadManager.GetStringAttribute( EDlMgrCodFolder, stringAttrPtr );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy( 2 ); // scheduler, stringAttr

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerGetStringAttribute8Test

    Description: Test the RHttpDownloadMgr GetStringAttribute method with TDesC8 argument.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerGetStringAttribute8Test( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr GetStringAttribute method with TDesC8 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    _LIT( KFailReason1 ,"RHttpDownloadMgr GetStringAttribute method with TDesC8 argument results in a panic/leave every time it is called");
    TestModuleIf().Printf( 0, KDefinition, KFailReason1 );

    _LIT( KFailReason2 ,"Unable to test GetStringAttribute method with TDesC8 argument");
    TestModuleIf().Printf( 0, KDefinition, KFailReason2 );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    _LIT( KDescription , "Test case failed" );
    aResult.SetResult( KErrGeneral, KDescription );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerSetIntAttributeTest

    Description: Test the RHttpDownloadMgr SetIntAttribute method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerSetIntAttributeTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr SetIntAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TInt result = iDownloadManager.SetIntAttribute( EDlMgrExitAction, EExitNothing );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerSetBoolAttributeTest

    Description: Test the RHttpDownloadMgr SetBoolAttribute method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerSetBoolAttributeTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr SetBoolAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TInt result = iDownloadManager.SetBoolAttribute( EDlMgrEnableCookies, ETrue );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerSetStringAttribute16Test

    Description: Test the RHttpDownloadMgr SetStringAttribute method with TDesC16 argument.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerSetStringAttribute16Test( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr SetStringAttribute method with TDesC16 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    RSocketServ iSocketServ;
    RConnection iConnection;

    TInt tempResult = iSocketServ.Connect();
    tempResult = tempResult;

    tempResult = iConnection.Open( iSocketServ );
    tempResult = tempResult;

    TName name;

    iConnection.Name( name );

    TInt result = iDownloadManager.SetStringAttribute( EDlMgrConnectionName, name );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if( result == KErrPermissionDenied )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    iConnection.Close();
    iSocketServ.Close();

    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerSetStringAttribute8Test

    Description: Test the RHttpDownloadMgr SetStringAttribute method with TDesC8 argument.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerSetStringAttribute8Test( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr SetStringAttribute method with TDesC8 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    _LIT( KFailReason1 ,"RHttpDownloadMgr SetStringAttribute method with TDesC8 argument results in a panic/leave every time it is called");
    TestModuleIf().Printf( 0, KDefinition, KFailReason1 );

    _LIT( KFailReason2 ,"Unable to test SetStringAttribute method with TDesC8 argument");
    TestModuleIf().Printf( 0, KDefinition, KFailReason2 );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    _LIT( KDescription , "Test case failed" );
    aResult.SetResult( KErrGeneral, KDescription );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerSetDefaultIntAttributeTest

    Description: Test the RHttpDownloadMgr SetDefaultIntAttribute method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerSetDefaultIntAttributeTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr SetDefaultIntAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TInt result = iDownloadManager.SetDefaultIntAttribute( EDlAttrAction, ELaunch );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerSetDefaultBoolAttributeTest

    Description: Test the RHttpDownloadMgr SetDefaultBoolAttribute method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerSetDefaultBoolAttributeTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr SetDefaultBoolAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TInt result = iDownloadManager.SetDefaultBoolAttribute( EDlAttrDisconnectOnReset, ETrue );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerSetDefaultStringAttribute16Test

    Description: Test the RHttpDownloadMgr SetDefaultStringAttribute method with TDesC16 argument.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerSetDefaultStringAttribute16Test( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr SetDefaultStringAttribute method with TDesC16 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    _LIT( KDestFilename, "c:\\logs\\DownloadMgr\\" );
    TInt result = iDownloadManager.SetDefaultStringAttribute( EDlAttrDestFilename, KDestFilename() );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerSetDefaultStringAttribute8Test

    Description: Test the RHttpDownloadMgr SetDefaultStringAttribute method with TDesC8 argument.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerSetDefaultStringAttribute8Test( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr SetDefaultStringAttribute method with TDesC8 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    _LIT8( KUserName, "username");
    TInt result = iDownloadManager.SetDefaultStringAttribute( EDlAttrUsername, KUserName() );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

    if( result == KErrNone )
	    {
	    _LIT( KDescription , "Test case passed" );
	    aResult.SetResult( KErrNone, KDescription );
	    }
    else
	    {
	    _LIT( KDescription , "Test case failed" );
	    aResult.SetResult( KErrGeneral, KDescription );
	    }

    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerAddObserverLTest

    Description: Test the RHttpDownloadMgr AddObserverL method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerAddObserverLTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr AddObserverL method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    iDownloadManager.AddObserverL( *this );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

	// RHttpDownloadMgr::AddObserverL provides no results, so if we've gotten this far assume success
    _LIT( KDescription , "Test case passed" );
    aResult.SetResult( KErrNone, KDescription );

    iDownloadManager.RemoveObserver( *this );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerRemoveObserverTest

    Description: Test the RHttpDownloadMgr RemoveObserver method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerRemoveObserverTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr RemoveObserver method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    iDownloadManager.AddObserverL( *this );

    iDownloadManager.RemoveObserver( *this );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

	// RHttpDownloadMgr::RemoveObserver provides no results, so if we've gotten this far assume success
    _LIT( KDescription , "Test case passed" );
    aResult.SetResult( KErrNone, KDescription );

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: ManagerSetNextUriObserverTest

    Description: Test the RHttpDownloadMgr SetNextUriObserver method.

    Parameters:  TTestResult& aErrorDescription: out:
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerSetNextUriObserverTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownloadMgr SetNextUriObserver method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    iDownloadManager.SetNextUriObserver( this );

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );

	// RHttpDownloadMgr::SetNextUriObserver provides no results, so if we've gotten this far assume success
    _LIT( KDescription , "Test case passed" );
    aResult.SetResult( KErrNone, KDescription );

    // Case was executed
    return KErrNone;
    }

// ================= OTHER EXPORTED FUNCTIONS =================================

// End of File
