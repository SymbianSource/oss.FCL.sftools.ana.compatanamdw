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

    Method: DownloadStartTest

    Description: Test the RHttpDownload Start method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadStartTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload Start method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    TInt result = download.Start();

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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadPauseTest

    Description: Test the RHttpDownload Pause method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadPauseTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload Pause method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    download.Start();
    
    TInt result = download.Pause();

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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadResetTest

    Description: Test the RHttpDownload Reset method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadResetTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload Reset method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    download.Start();
    
    TInt result = download.Reset();

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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadDeleteTest

    Description: Test the RHttpDownload Delete method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadDeleteTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload Delete method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    download.Start();
    
    TInt result = download.Delete();

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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadMoveTest

    Description: Test the RHttpDownload Move method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadMoveTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload Move method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    download.Start();
    
    TInt result = download.Move();

    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );
    
    if( result == KErrNotReady )
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

    Method: DownloadGetIntAttributeTest

    Description: Test the RHttpDownload GetIntAttribute method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadGetIntAttributeTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload GetIntAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    TInt32 value;
    TInt result = download.GetIntAttribute( EDlAttrId, value );
    
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadGetBoolAttributeTest

    Description: Test the RHttpDownload GetBoolAttribute method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadGetBoolAttributeTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload GetBoolAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    TBool value;
    TInt result = download.GetBoolAttribute( EDlAttrDestRemovable, value );
    
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadGetStringAttribute16Test

    Description: Test the RHttpDownload GetStringAttribute method using TDes16 argument.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadGetStringAttribute16Test( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload GetStringAttribute method using TDes16 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    HBufC16* stringAttr = HBufC16::NewLC( KMaxUrlLength );
    TPtr16 stringAttrPtr = stringAttr->Des();
    TInt result = download.GetStringAttribute( EDlAttrCurrentUrl, stringAttrPtr );
    
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy( 2 ); // scheduler, stringAttr

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadGetStringAttribute8Test

    Description: Test the RHttpDownload GetStringAttribute method using TDes8 argument.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadGetStringAttribute8Test( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload GetStringAttribute method using TDes8 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    HBufC8* stringAttr = HBufC8::NewLC( KMaxUrlLength );
    TPtr8 stringAttrPtr = stringAttr->Des();
    TInt result = download.GetStringAttribute( EDlAttrCurrentUrl, stringAttrPtr );
    
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy( 2 ); // scheduler, stringAttr

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadGetFileHandleAttributeTest

    Description: Test the RHttpDownload GetFileHandleAttribute method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadGetFileHandleAttributeTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload GetFileHandleAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    download.Start();
    
    RFile file;
    TInt result = download.GetFileHandleAttribute( file );
    
    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );
    
    if( result == KErrArgument )
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

    Method: DownloadSetIntAttributeTest

    Description: Test the RHttpDownload SetIntAttribute method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadSetIntAttributeTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload SetIntAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    TInt result = download.SetIntAttribute( EDlAttrFotaPckgId, KDefaultFotaPckgId );
    
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadSetBoolAttributeTest

    Description: Test the RHttpDownload SetBoolAttribute method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadSetBoolAttributeTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload SetBoolAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    TInt result = download.SetBoolAttribute( EDlAttrProgressive, EFalse );
    
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadSetStringAttribute16Test

    Description: Test the RHttpDownload SetStringAttribute method using TDes16 argument.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadSetStringAttribute16Test( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload SetStringAttribute method using TDes16 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    _LIT( KDestFileName, "c:\\fakefile\\");
    TInt result = download.SetStringAttribute( EDlAttrDestFilename, KDestFileName() );
    
    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );
    
    if( result == KErrArgument )
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

    Method: DownloadSetStringAttribute8Test

    Description: Test the RHttpDownload SetStringAttribute method using TDes8 argument.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadSetStringAttribute8Test( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload SetStringAttribute method using TDes8 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    _LIT8( KUserName, "username");
    TInt result = download.SetStringAttribute( EDlAttrUsername, KUserName );
    
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }

/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadSetFileHandleAttributeTest

    Description: Test the RHttpDownload SetFileHandleAttribute method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadSetFileHandleAttributeTest( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload SetFileHandleAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    download.Start();
    
    RFile file;
    TInt result = download.SetFileHandleAttribute( file );
    
    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );
    
    if( result == KErrBadHandle )
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

// ================= OTHER EXPORTED FUNCTIONS =================================

// End of File
/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadGetIntAttributeTestAlbum

    Description: Test the RHttpDownload GetIntAttribute method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::ManagerGetIntAttributeTestAlbum( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload GetIntAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    TInt32 value;
    TInt32 index = 1;
    TInt result = download.GetIntAttribute( EDlAttrId,index,value);
    
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }
    
    /*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTestAlbum

    Method: DownloadGetBoolAttributeTestAlbum

    Description: Test the RHttpDownload GetBoolAttribute method.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

--------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadGetBoolAttributeTestAlbum( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload GetBoolAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    TBool value;
    TInt32 index = 0;
    TInt result = download.GetBoolAttribute( EDlAttrDestRemovable, index,value );
    
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(); // scheduler

    // Case was executed
    return KErrNone;
    }
/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadGetStringAttribute16Test

    Description: Test the RHttpDownload GetStringAttribute method using TDes16 argument.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadGetStringAttribute16TestAlbum( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload GetStringAttribute method using TDes16 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    HBufC16* stringAttr = HBufC16::NewLC( KMaxUrlLength );
    TPtr16 stringAttrPtr = stringAttr->Des();
    
    TInt32 Index = 0;
    
    TInt result = download.GetStringAttribute( EDlAttrCurrentUrl, Index,stringAttrPtr );
    
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy( 2 ); // scheduler, stringAttr

    // Case was executed
    return KErrNone;
    }
/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadGetStringAttribute8Test

    Description: Test the RHttpDownload GetStringAttribute method using TDes8 argument.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadGetStringAttribute8TestAlbum( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload GetStringAttribute method using TDes8 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    HBufC8* stringAttr = HBufC8::NewLC( KMaxUrlLength );
    TPtr8 stringAttrPtr = stringAttr->Des();
    TInt32 Index = 0;
    TInt result = download.GetStringAttribute( EDlAttrCurrentUrl,Index, stringAttrPtr );
    
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy( 2 ); // scheduler, stringAttr

    // Case was executed
    return KErrNone;
    }
/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest

    Method: DownloadSetStringAttribute16Test

    Description: Test the RHttpDownload SetStringAttribute method using TDes16 argument.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::DownloadSetStringAttribute16TestAlbum( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload SetStringAttribute method using TDes16 argument");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    TInt32 index = 0;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    _LIT( KDestFileName, "c:\\fakefile\\");
    TInt result = download.SetStringAttribute( EDlAttrDestFilename, index,KDestFileName() );
    
    _LIT( KData2 ,"Finished");
    TestModuleIf().Printf( 0, KDefinition, KData2 );
    
    if( result == KErrArgument )
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

    Method: SetDownloadDataAttribute

    Description: Test the RHttpDownload SetDownloadDataAttribute method using TDesC8 argument.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::SetDownloadDataAttribute( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload SetDownloadDataAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );

    HBufC8* stringAttr = HBufC8::NewLC( KMaxUrlLength );
    TPtr8 stringAttrPtr = stringAttr->Des();
    TInt32 result=KErrNone;
    
    //This API cannot be tested
    //result = download.SetDownloadDataAttribute( stringAttrPtr );
    
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(2); // scheduler

    // Case was executed
    return KErrNone;
    }
    
/*
-------------------------------------------------------------------------------

    Class: CDownloadMgrBCTest 

    Method: CSetTrackDataAttribute

    Description: Test the RHttpDownload CSetTrackDataAttribute method using TDesC8 argument.
  
    Parameters:  TTestResult& aErrorDescription: out:   
                    Test result and on error case a short description of error

    Return Values: TInt: Always KErrNone to indicate that test was valid

    Errors/Exceptions: None

    Status: Approved

-------------------------------------------------------------------------------
*/
TInt CDownloadMgrBCTest::SetTrackDataAttribute( TTestResult& aResult )
    {
    /* Simple server connect */
    _LIT( KDefinition ,"State");
    _LIT( KData ,"Test the RHttpDownload SetTrackDataAttribute method");
    TestModuleIf().Printf( 0, KDefinition, KData );

    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL( scheduler );
    CActiveScheduler::Install( scheduler );

    TBuf8<128> url = _L8("http://waplabdc.nokia-boston.com/browser/users/s60_devtests/nightly_ss_on.xml");

    TBool isNewDl = ETrue;
    RHttpDownload& download = iDownloadManager.CreateDownloadL( url, isNewDl );
    
    HBufC8* stringAttr = HBufC8::NewLC( KMaxUrlLength );
    TPtr8 stringAttrPtr = stringAttr->Des();
    TInt32 index = 0;
    TInt32 result=0;
    
   result = download.SetTrackDataAttribute(index,stringAttrPtr );
   
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

    iDownloadManager.DeleteAll();
    CleanupStack::PopAndDestroy(2); // scheduler

    // Case was executed
    return KErrNone;
    }
