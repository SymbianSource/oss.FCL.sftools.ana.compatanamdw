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
* Description:  Central Repository NotifyHandler test cases
*
*/

/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */


// INCLUDE FILES
#include <e32math.h>
#include "CenRepNotifyHandlerTest.h"
#include "CenRepNotifyHandlerTestKeys.h"

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
// CCenRepNotifyHandlerTest::Case
// Returns a test case by number.
//
// This function contains an array of all available test cases 
// i.e pair of case name and test function. If case specified by parameter
// aCaseNumber is found from array, then that item is returned.
// 
// The reason for this rather complicated function is to specify all the
// test cases only in one place. It is not necessary to understand how
// function pointers to class member functions works when adding new test
// cases. See function body for instructions how to add new test case.
// -----------------------------------------------------------------------------
//
const TCaseInfo CCenRepNotifyHandlerTest::Case ( 
    const TInt aCaseNumber ) const 
     {

    /**
    * To add new test cases, implement new test case function and add new 
    * line to KCases array specify the name of the case and the function 
    * doing the test case
    * In practice, do following
    * 1) Make copy of existing test case function and change its name
    *    and functionality. Note that the function must be added to 
    *    CenRepNotifyHandlerTest.cpp file and to CenRepNotifyHandlerTest.h 
    *    header file.
    * 2) Add entry to following KCases array either by using FUNCENTRY or 
    *    ENTRY macro. 
    * ENTRY macro takes two parameters: test case name and test case 
    * function name.
    * FUNCENTRY macro takes only test case function name as a parameter and uses
    * that as a test case name and test case function name.
    */
    
    static TCaseInfoInternal const KCases[] =
        {
        // To add new test cases, add new items to this array
        //FUNCENTRY( PrintTest ),
        ENTRY( "COMMONENGINE [CCenRepNotifyHandler ListeningToSingleIntKey]", ListeningToSingleIntKey ),
		ENTRY( "COMMONENGINE [CCenRepNotifyHandler ListeningToSingleRealKey]", ListeningToSingleRealKey ),
        ENTRY( "COMMONENGINE [CCenRepNotifyHandler ListeningToSingleStringKey]", ListeningToSingleStringKey ),
        ENTRY( "COMMONENGINE [CCenRepNotifyHandler ListeningToSingleBinaryKey]", ListeningToSingleBinaryKey ),                            
        ENTRY( "COMMONENGINE [CCenRepNotifyHandler ListeningToAllKeys]", ListeningToAllKeys),      
        ENTRY( "COMMONENGINE [CCenRepNotifyHandler NoMultipleNotifiesOnSameValueChange]", NoMultipleNotifiesOnSameValueChange),    
        ENTRY( "COMMONENGINE [CCenRepNotifyHandler NoNotificationAfterStopListening]", NoNotificationAfterStopListening), 
        ENTRY( "COMMONENGINE [CCenRepNotifyHandler NotificationAfterWholeRepositoryReset]", NotificationAfterWholeRepositoryReset ), 
        ENTRY( "COMMONENGINE [CCenRepNotifyHandler NotificationAfterRepositoryKeyReset]", NotificationAfterRepositoryKeyReset ), 
        ENTRY( "COMMONENGINE [CCenRepNotifyHandler ListeningForTwoNotificationHandler]", ListeningForTwoNotificationHandler), 
        /* ENTRY( "COMMONENGINE 0011 [CCenRepNotifyHandler  ]",  ), */       
                              

        };

    // Verify that case number is valid
    if( (TUint) aCaseNumber >= sizeof( KCases ) / 
                               sizeof( TCaseInfoInternal ) )
        {

        // Invalid case, construct empty object
        TCaseInfo null( (const TText*) L"" );
        null.iMethod = NULL;
        return null;

        } 

    // Construct TCaseInfo object and return it
    TCaseInfo tmp ( KCases[ aCaseNumber ].iCaseName );
    tmp.iMethod = KCases[ aCaseNumber ].iMethod;
    return tmp;
     
    }


// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::InitializeNotifyData
// -----------------------------------------------------------------------------
//
void CCenRepNotifyHandlerTest::InitializeNotifyData()
{
	iNotifyInt = 0;
	iNotifyReal = 0;
	iNotifyString = _L("");
	iNotifyBinary = _L8("");
	iNotifyError = 0;
	iNotificationId = 0;
	iSession->Set(KKey1, KKeyStringInit);
	iSession->Set(KKey2, 1234);
	iSession->Set(KKey3, 1.234);
	iSession->Set(KKey4, KKeyBinaryInit);	
}

    
// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::ListeningToSingleIntKey
//
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::ListeningToSingleIntKey( 
    TTestResult& aResult )    
    {

	TInt ret(0);
	TRAPD(err, iSession = CRepository::NewL(KTestUid));
	if(err != KErrNone) return err;
	
	iLog->Log(_L("STARTING COMMONENGINE [CCenRepNotifyHandler ListeningToSingleIntKey]"));
	InitializeNotifyData();
	
	TRAP(err, iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iSession, CCenRepNotifyHandler::EIntKey, KKey2));
	if(err != KErrNone) return err;
    
   //start listening for notifications
    iLog->Log(_L("Start listening: %d"), ret);
    TRAP(ret, iNotifyHandler->StartListeningL());

    iLog->Log(_L("Set new value for KKey2"));
    iSession->Set(KKey2, 54321);
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;
    	    
    if((iNotifyInt == 54321) && (iNotifyError==0))
    {
    	aResult.SetResult( KErrNone, _L("") );		
    	iLog->Log(_L("ListeningToSingleIntKey PASSED"));
	
    }
    else
    {
    	if(iNotifyError==0)
    		aResult.SetResult(KErrGeneral, _L(""));
    	else 
    	   	aResult.SetResult(iNotifyError, _L("Error in notify handler"));
	
	   	iLog->Log(_L("ListeningToSingleIntKey FAILED\n\nKeyword: %d, Value: %d, iNotifyError:%d"), KKey1, iNotifyInt, iNotifyError );

    }
        
    iLog->Log(_L("Stop listening"));
    iNotifyHandler->StopListening();
    
    delete iNotifyHandler;
    iNotifyHandler = NULL;	
    delete iSession;
   	iSession = NULL;	
   	iLog->Log(_L("COMPLETED : COMMONENGINE [CCenRepNotifyHandler ListeningToSingleIntKey]\n\n"));     

    // Case was executed
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::ListeningToSingleRealKey
// 
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::ListeningToSingleRealKey( TTestResult& aResult )
    {
     
	iLog->Log(_L("STARTING : COMMONENGINE [CCenRepNotifyHandler ListeningToSingleRealKey]"));
	
	TInt ret(0);
	TRAPD(err, iSession = CRepository::NewL(KTestUid));
	if(err != KErrNone) return err;
	
	InitializeNotifyData();
  TRAP(err, iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iSession, CCenRepNotifyHandler::ERealKey, KKey3));
  if(err != KErrNone) return err;
    
    iLog->Log(_L("Start listening: %d"), ret);    
    TRAP(ret, iNotifyHandler->StartListeningL());

    ret = iSession->Set(KKey3, 1.67);
    
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;
    
    if((iNotifyReal == 1.67) && (iNotifyError == 0))
    {
    	// Sets test case result and description(Maximum size is KStifMaxResultDes)
    	aResult.SetResult( KErrNone, _L("") );
    	iLog->Log(_L("ListeningToSingleRealKey PASSED"));
    }
    else
    {
    	if(iNotifyError==0)
    		aResult.SetResult(KErrGeneral, _L(""));
    	else 
    	   	aResult.SetResult(iNotifyError, _L("Error in notification process"));
	
	   	iLog->Log(_L("ListeningToSingleRealKey FAILED\n\nKeyword: %d, Value: %e, iNotifyError:%d"), KKey1, iNotifyReal, iNotifyError );

    }
    
    iLog->Log(_L("Stop listening"));
    iNotifyHandler->StopListening();
    
    delete iNotifyHandler;
    iNotifyHandler = NULL;	
    delete iSession;
    iSession = NULL;	
    
    iLog->Log(_L("COMPLETED : COMMONENGINE [CCenRepNotifyHandler ListeningToSingleRealKey]\n\n"));
    // Case was executed
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::ListeningToSingleStringKey
//
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::ListeningToSingleStringKey( TTestResult& aResult )
    {
    
	iLog->Log(_L("STARTING : COMMONENGINE [CCenRepNotifyHandler ListeningToSingleStringKey]"));
     
	TInt ret;
	TRAPD(err, iSession = CRepository::NewL(KTestUid));
	if(err != KErrNone) return err;
	
    InitializeNotifyData();
	TRAP(err, iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iSession, CCenRepNotifyHandler::EStringKey, KKey1));
	if(err != KErrNone)	return err;
	    
    TRAP(ret, iNotifyHandler->StartListeningL());
    iLog->Log(_L("Start listening: %d"), ret);

    iSession->Set(KKey1, KKeyString);
    
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;

    if((iNotifyString==KKeyString) /*ETrue*/ && (iNotifyError == 0) /*ETrue*/)
    {
       	aResult.SetResult( KErrNone, _L("") );
    	iLog->Log(_L("ListeningToSingleStringKey PASSED"));
    }
    else
    {
    	if(iNotifyError==0)
    		aResult.SetResult(KErrGeneral, _L(""));
    	else 
    	   	aResult.SetResult(iNotifyError, _L("Error in notification process"));
    	
    	iLog->Log(_L("ListeningToSingleStringKey FAILED\n\nKeyword: %d, Value: %e, iNotifyError:%d"), KKey1, iNotifyReal, iNotifyError );
    }
    
	iLog->Log(_L("Stop listening"));
	iNotifyHandler->StopListening();
	delete iNotifyHandler;
	iNotifyHandler = NULL;	
	delete iSession;
	iSession = NULL;	

	iLog->Log(_L("COMPLETED : COMMONENGINE [CCenRepNotifyHandler ListeningToSingleStringKey]\n\n"));	
    // Case was executed*/
    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::ListeningToSingleBinaryKey
// Another printing to UI test.
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::ListeningToSingleBinaryKey( TTestResult& aResult )
    {
    
    iLog->Log(_L("STARTING : COMMONENGINE [CCenRepNotifyHandler ListeningToSingleBinaryKey]"));

	TInt ret;
	TRAPD(err, iSession = CRepository::NewL(KTestUid));
	if(err != KErrNone) return err;
	
	InitializeNotifyData();
	TRAP(err, iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iSession, CCenRepNotifyHandler::EBinaryKey, KKey4));
	if(err != KErrNone) return err;

    TRAP(ret, iNotifyHandler->StartListeningL());
    iLog->Log(_L("Start listening: %d"), ret);

	iSession->Set(KKey4, KKeyBinary);
	
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;

    if((iNotifyBinary==KKeyBinary) && (iNotifyError == 0))
    {
    	// Sets test case result and description(Maximum size is KStifMaxResultDes)
    	aResult.SetResult( KErrNone, _L(""));
    	iLog->Log(_L("ListeningToSingleBinaryKey PASSED"));
    }
    else
    {
    	if(iNotifyError==0)
    		aResult.SetResult(KErrGeneral, _L(""));
    	else 
    	   	aResult.SetResult(iNotifyError, _L("Error in notification process"));
    	
    	iLog->Log(_L("ListeningToSingleBinaryKey FAILED\nKeyword: %d, Value: %S, iNotifyError: %d"), KKey4, &iNotifyBinary, iNotifyError);
    }
    
   iLog->Log(_L("Stop listening"));
   iNotifyHandler->StopListening();
	delete iNotifyHandler;
	iNotifyHandler = NULL;	
	delete iSession;
	iSession = NULL;	
   
   iLog->Log(_L("COMPLETED : COMMONENGINE [CCenRepNotifyHandler ListeningToSingleBinaryKey]\n\n"));
    // Case was executed*/
    return KErrNone;
    
    }
  
// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::ListeningToAllKeys
// 
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::ListeningToAllKeys( TTestResult& aResult )
    {
    
    iLog->Log(_L("STARTING : COMMONENGINE [CCenRepNotifyHandler ListeningToAllKeys]"));
	
	TInt ret(0);
	//create session
	TRAPD(err, iSession = CRepository::NewL(KTestUid));
	if(err != KErrNone) return err;
	
	InitializeNotifyData();	
	//create handler
	TRAP(err, iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iSession));
	if(err != KErrNone) return err;
	
    //start listening fo notifications
    TRAP(ret, iNotifyHandler->StartListeningL());
    iLog->Log(_L("Start listening: %d"), ret);
	
	//Create new key
	iSession->Create(KNewTestKey1, KGenericString);
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;
	
	//Set integer value for Key1
	iSession->Set(KKey2, KGenericInt);
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;
  	
  	/* TeK: 10.8.2005 Modified KGenericString compare //// iNotifyString.Compare(KGenericString) */ 
    if((iNotifyInt == KGenericInt) /*ETrue*/ && (iNotifyError == 0) /*ETrue*/)
    {
    	// Sets test case result and description(Maximum size is KStifMaxResultDes)
    	aResult.SetResult( KErrNone, _L(""));
    	iLog->Log(_L("ListeningToAllKeys PASSED"));
    }
    else
    {
    	if(iNotifyError==0)
    	{
    		aResult.SetResult(KErrGeneral, _L(""));
    	}
    		
    	else 
    	{
    	   	aResult.SetResult(iNotifyError, _L("Error in notification process"));	
    	}
    	   	
    	
    	iLog->Log(_L("ListeningToAllKeys FAILED\n iNotifyString: %S, iNotifyInt: %d, iNotifyError: %d"), &iNotifyString, iNotifyInt, iNotifyError);
    }
    
   iLog->Log(_L("Stop listening"));
   iNotifyHandler->StopListening();
 	 delete iNotifyHandler;
	 iNotifyHandler = NULL;	
	 delete iSession;
	 iSession = NULL;	
   
   iLog->Log(_L("COMPLETED : COMMONENGINE [CCenRepNotifyHandler ListeningToAllKeys]\n\n"));
    // Case was executed*/
   return KErrNone;
   
   }
    
// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::NoMultipleNotifiesOnSameValueChange
// 
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::NoMultipleNotifiesOnSameValueChange( TTestResult& aResult )
    {
    
    iLog->Log(_L("STARTING : COMMONENGINE [CCenRepNotifyHandler NoMultipleNotifiesOnSameValueChange]"));
	
	TInt ret;
	TRAPD(err, iSession = CRepository::NewL(KTestUid));
	if(err != KErrNone) return err;
	
	InitializeNotifyData();
	
	TRAP(err, iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iSession));
	if(err != KErrNone) return err;
	
    TRAP(ret, iNotifyHandler->StartListeningL());
    iLog->Log(_L("Start listening: %d"), ret);
	
	iSession->Set(KKey2, 11);
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;
    
    TBool result = ((iNotifyInt==11) /*ETrue*/ && (iNotifyError == 0) /*ETrue*/);
    
    iNotifyError = 0;
    iNotifyInt = 0;
    
    //try to set same value again	
	iSession->Set(KKey2, 11);
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;
  	
    if( (iNotifyInt == 0) /*ETrue*/ && (iNotifyError == 0) /*ETrue*/ && result /*ETrue*/ )
    {
    	// Sets test case result and description(Maximum size is KStifMaxResultDes)
    	aResult.SetResult( KErrNone, _L(""));
    	iLog->Log(_L("NoMultipleNotifiesOnSameValueChange PASSED"));
    }
    else
    {
    	if(iNotifyError==0)
    	{
    		aResult.SetResult(KErrGeneral, _L(""));
    	}
    		
    	else 
    	{
    	   	aResult.SetResult(iNotifyError, _L("Error in notification process"));	
    	}
    	   	
    	
    	iLog->Log(_L("NoMultipleNotifiesOnSameValueChange FAILED\n iNotifyInt: %d, iNotifyError: %d, First notification: %d"), iNotifyInt, iNotifyError, result);
    }
    
   iNotifyString = _L("");
   iNotifyInt = 0;
   iLog->Log(_L("Stop listening"));
   iNotifyHandler->StopListening();
	 delete iNotifyHandler;
	 iNotifyHandler = NULL;	
	 delete iSession;
	 iSession = NULL;	
   
   iLog->Log(_L("COMPLETED : COMMONENGINE [CCenRepNotifyHandler NoMultipleNotifiesOnSameValueChange]\n\n"));
    // Case was executed*/
   return KErrNone;
   
   }
    
// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::NoNotificationAfterStopListening
// 
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::NoNotificationAfterStopListening( TTestResult& aResult )
    {
    
    iLog->Log(_L("STARTING : COMMONENGINE [CCenRepNotifyHandler NoNotificationAfterStopListening]"));
	
	TInt ret;
	TRAPD(err, iSession = CRepository::NewL(KTestUid));
	if(err != KErrNone) return err;
	
	InitializeNotifyData();
	
	TRAP(err, iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iSession));
	if(err != KErrNone) return err;
	
    TRAP(ret, iNotifyHandler->StartListeningL());
    iLog->Log(_L("Start listening: %d"), ret);
	
	//Update value
	iSession->Set(KKey2, 12);
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;
    
    TBool result = ((iNotifyInt==12) /*ETrue*/ && (iNotifyError == 0) /*ETrue*/);
    
    iNotifyError = 0;
    iNotifyInt = 0;
    
    iLog->Log(_L("Stop listening"));
    iNotifyHandler->StopListening();
    
    //update value again	
	iSession->Set(KKey2, 13);
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;
  	
  	//notification should not be received after stop listening
    if( (iNotifyInt == 0) /*ETrue*/ && (iNotifyError == 0) /*ETrue*/ && result /*ETrue*/ )
    {
    	// Sets test case result and description(Maximum size is KStifMaxResultDes)
    	aResult.SetResult( KErrNone, _L(""));
    	iLog->Log(_L("NoNotificationAfterStopListening PASSED"));
    }
    else
    {
    	if(iNotifyError==0)
    	{
    		aResult.SetResult(KErrGeneral, _L(""));
    	}
    		
    	else 
    	{
    	   	aResult.SetResult(iNotifyError, _L("Error in notification process"));	
    	}
    	   	
    	
    	iLog->Log(_L(" FAILED\n iNotifyInt: %d, iNotifyError: %d, First notification: %d"), iNotifyInt, iNotifyError, result);
    }
    
	 delete iNotifyHandler;
	 iNotifyHandler = NULL;	
	 delete iSession;
	 iSession = NULL;	
   
   iLog->Log(_L("COMPLETED : COMMONENGINE 0007  [CCenRepNotifyHandler NoNotificationAfterStopListening]\n\n"));
    // Case was executed*/
   return KErrNone;
   
   }    

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::NotificationAfterWholeRepositoryReset
// 
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::NotificationAfterWholeRepositoryReset( TTestResult& aResult )
    {
    
    iLog->Log(_L("STARTING : COMMONENGINE  [CCenRepNotifyHandler NotificationAfterWholeRepositoryReset]"));
	
	TInt ret;
	TRAPD(err, iSession = CRepository::NewL(KTestUid));
	if(err != KErrNone) return err;
	
	InitializeNotifyData();
	
	//Create new value to repository
	iSession->Create(KNewTestKey2, KResetTestString);
	
	//close session to be sure that the value is saved
	delete iSession;
	iSession = NULL; 	
    
    //open session again and find the key
	TRAP(err, iSession = CRepository::NewL(KTestUid));
	if(err != KErrNone) return err;
    
    TBuf16<NCentralRepositoryConstants::KMaxUnicodeStringLength> buf;
    iSession->Get(KNewTestKey2, buf);
    
    //if key wasn't found
    if (buf != KResetTestString)
    {
    	aResult.SetResult(KErrGeneral, _L(""));
    	iLog->Log(_L("NotificationAfterWholeRepositoryReset FAILED\n ResetTestString: %S"), &buf);
    	return KErrNone;
    }
    
	TRAP(err, iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iSession));
	if(err != KErrNone) return err;
    
	TRAP(ret, iNotifyHandler->StartListeningL());
        
    //reset whole repository	
	iSession->Reset();
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;

	//KInvalidNotificationId should be received 
	TBool result (iNotificationId == NCentralRepositoryConstants::KInvalidNotificationId);
	
   	iLog->Log(_L("Stop listening"));
   	iNotifyHandler->StopListening();
     
    buf.Zero();
    iSession->Get(KNewTestKey2, buf);
  
    if ( result /*ETrue*/ && (buf == _L("")) /*ETrue*/ )
    {
    	// Sets test case result and description(Maximum size is KStifMaxResultDes)
    	aResult.SetResult( KErrNone, _L(""));
    	iLog->Log(_L("NotificationAfterWholeRepositoryReset PASSED"));
    }
    else
    {
    	if(iNotifyError==0)
    	{
    		aResult.SetResult(KErrGeneral, _L(""));
    	}
    		
    	else 
    	{
    	   	aResult.SetResult(iNotifyError, _L("Error in notification process"));	
    	}
    	   	
    	
    	iLog->Log(_L("NotificationAfterWholeRepositoryReset FAILED\n NotificationId: %d, Buffer: %S"), iNotificationId, &buf);
    }
    
	 delete iNotifyHandler;
	 iNotifyHandler = NULL;	
	 delete iSession;
	 iSession = NULL;	
   
   iLog->Log(_L("COMPLETED : COMMONENGINE [CCenRepNotifyHandler NotificationAfterWholeRepositoryReset]\n\n"));
    // Case was executed*/
   return KErrNone;
   
   }    
    
// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::NotificationAfterRepositoryKeyReset
// 
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::NotificationAfterRepositoryKeyReset( TTestResult& aResult )
{
    
    iLog->Log(_L("STARTING : COMMONENGINE [CCenRepNotifyHandler NotificationAfterRepositoryKeyReset]"));
	
	TInt ret;
	TRAPD(err, iSession = CRepository::NewL(KTestUid));
	if(err != KErrNone) return err;
	
	InitializeNotifyData();
	
	//Create new value to repository
	iSession->Set(KKey1, KResetKeyTestString);
	
    //close session to be sure that the value is saved
	delete iSession;
	iSession = NULL;	
    
    //open session again and find the key
	TRAP(err, iSession = CRepository::NewL(KTestUid));
	if(err != KErrNone) return err;
    
    
    TBuf16<NCentralRepositoryConstants::KMaxUnicodeStringLength> buf;
	iSession->Get(KKey1, buf);
    
    //if key wasn't found
    if (buf != KResetKeyTestString)
    {
    	aResult.SetResult(KErrGeneral, _L("KResetKeyTestString not set"));
    	iLog->Log(_L("NotificationAfterRepositoryKeyReset FAILED\n KResetKeyTestString: %S"), &buf);
    	return KErrNone;
    }
    
    //delete first key
    //iSession->Delete(KKey1);
    /* TeK 11.8.2005 Removed delete */
    
	TRAP(err, iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iSession, CCenRepNotifyHandler::EStringKey, KKey1 ));
	if(err != KErrNone) return err;
    
	TRAP(ret, iNotifyHandler->StartListeningL());
        
    //reset first keyword
	iSession->Reset(KKey1);
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;
	
     
    if ( (iNotificationId == KKey1) ) /* TeK 11.8.2005 */
    {
    	// Sets test case result and description(Maximum size is KStifMaxResultDes)
    	aResult.SetResult( KErrNone, _L(""));
    	iLog->Log(_L("NotificationAfterRepositoryKeyReset PASSED"));
    }
    else
    {
    	if(iNotifyError==0)
    	{
    		aResult.SetResult(KErrGeneral, _L(""));
    	}
    		
    	else 
    	{
    	   	aResult.SetResult(iNotifyError, _L("Error in notification process"));	
    	}
    	   	
    	
    	iLog->Log(_L("NotificationAfterRepositoryKeyReset FAILED\n NotificationId: %d, iNotifyString: %S"), iNotificationId, &iNotifyString);
    }
    
   iLog->Log(_L("Stop listening"));
   iNotifyHandler->StopListening();

    
	 delete iNotifyHandler;
	 iNotifyHandler = NULL;	
	 delete iSession;
	 iSession = NULL;	
   
   iLog->Log(_L("COMPLETED : COMMONENGINE [CCenRepNotifyHandler NotificationAfterRepositoryKeyReset]\n\n"));
    // Case was executed*/
   return KErrNone;
   }
   
// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::ListeningForTwoNotificationHandler
// 
// -----------------------------------------------------------------------------
//
TInt CCenRepNotifyHandlerTest::ListeningForTwoNotificationHandler( TTestResult& aResult )
{
    
	iLog->Log(_L("STARTING : COMMONENGINE [CCenRepNotifyHandler ListeningForTwoNotificationHandler]"));
	
	TInt ret;
	TRAPD(err, iSession = CRepository::NewL(KTestUid));
	if(err != KErrNone) return err;
	
	InitializeNotifyData();
	//create handler for specific keyword
	TRAP(err, iNotifyHandler = CCenRepNotifyHandler::NewL(*this, *iSession, CCenRepNotifyHandler::EBinaryKey, KKey4));
	if(err != KErrNone) return err;
	
	//create handler for whole repository
	TRAP(err, iSecondHandler = CCenRepNotifyHandler::NewL(*this, *iSession));
	if(err != KErrNone) return err;
	
	
	TRAP(ret, iNotifyHandler->StartListeningL());
	iLog->Log(_L("Start listening: %d"), ret);
	TRAP(ret, iSecondHandler->StartListeningL());
    iLog->Log(_L("Start listening: %d"), ret);
	
	iSession->Set(KKey4, KBinaryTestValue);
    TRAP(err, CTestScheduler::StartAndStopL(5000));
    if(err != KErrNone) return err;

    if ( (iNotificationId == KKey4) && (iNotifyBinary == KBinaryTestValue) && (iSecondBinary == KBinaryTestValue) && (iSecondNotificationId == KKey4) )
    {
    	// Sets test case result and description(Maximum size is KStifMaxResultDes)
    	aResult.SetResult( KErrNone, _L(""));
    	iLog->Log(_L("ListeningForTwoNotificationHandler PASSED"));
    }
    else
    {
    	if(iNotifyError==0)
    	{
    		aResult.SetResult(KErrGeneral, _L(""));
    	}
    		
    	else 
    	{
    	   	aResult.SetResult(iNotifyError, _L("Error in notification process"));	
    	}
    	   	
    	
    	iLog->Log(_L("ListeningForTwoNotificationHandler FAILED\n NotificationId: %d, iNotifyString: %S"), iNotificationId, &iNotifyString);
    }
    
   	iLog->Log(_L("Stop listening iNotifyHandler"));
   	iNotifyHandler->StopListening();
   	iLog->Log(_L("Stop listening iSecondHandler"));
   	iSecondHandler->StopListening();
	
   	
   	delete iNotifyHandler;
   	iNotifyHandler = NULL;	
   	delete iSecondHandler;
   	iSecondHandler = NULL;	
    delete iSession;
    iSession = NULL;	
   	iLog->Log(_L("COMPLETED : COMMONENGINE [CCenRepNotifyHandler ListeningForTwoNotificationHandler]\n\n"));
    // Case was executed*/
   	return KErrNone;

}


    
//HANDLING NOTIFICATIONS    
   
// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::HandleNotifyInt
// 
// -----------------------------------------------------------------------------
//
void CCenRepNotifyHandlerTest::HandleNotifyInt(TUint32 aId, TInt aNewValue)
{
	iNotifyInt = aNewValue;
	iNotificationId = aId;
	
	iLog->Log(_L("HandleNotifyInt - Keyword: %d, Value: %d"), iNotificationId, iNotifyInt);
}

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::HandleNotifyReal
// 
// -----------------------------------------------------------------------------
//
void CCenRepNotifyHandlerTest::HandleNotifyReal(TUint32 aId, TReal aNewValue)
{
	iNotifyReal = (TReal)aNewValue;
	iNotificationId = aId;
	iLog->Log(_L("HandleNotifyReal - Keyword: %d, Value: %e"), iNotificationId, iNotifyReal);
}

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::HandleNotifyString
// 
// -----------------------------------------------------------------------------
//
void CCenRepNotifyHandlerTest::HandleNotifyString(TUint32 aId, const TDesC16& aNewValue)
{
	iNotifyString.Append(aNewValue);
	iNotificationId = aId;
	iLog->Log(_L("HandleNotifyString - Keyword: %d, Value: %S"), iNotificationId, &iNotifyString);
}

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::HandleNotifyBinary
// 
// -----------------------------------------------------------------------------
//
void CCenRepNotifyHandlerTest::HandleNotifyBinary(TUint32 aId, const TDesC8& aNewValue)
{
	iNotifyBinary.Append(aNewValue);
	iNotificationId = aId;
	iLog->Log(_L("HandleNotifyBinary - Keyword: %d, Value: %S"), iNotificationId, &iNotifyBinary);
}

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::HandleNotifyGeneric
// 
// -----------------------------------------------------------------------------
//
void CCenRepNotifyHandlerTest::HandleNotifyGeneric( TUint32 aId )
{
       
    switch (aId)
		{	
		case NCentralRepositoryConstants::KInvalidNotificationId:
			iNotificationId = aId;
			iLog->Log(_L("KInvalidNotification"));
			//mitä tässä tehdään?!
			/*Repository wide reset*/
			break;

		case KNewTestKey1:
			iSession->Get(KNewTestKey1, iNotifyString);
			iNotificationId = aId;
			iLog->Log(_L("KNewTestKey1 notification %S"), &iNotifyString);
			break;
		
		case KKey2:
			iSession->Get(KKey2, iNotifyInt);
			iNotificationId = aId;
			iLog->Log(_L("KKey2 notification %d"), iNotifyInt);
			break;
				
		case KKey4:
			iSession->Get(KKey4, iSecondBinary); 
			iSecondNotificationId = aId;
			iLog->Log(_L("KKey4 notification %S"), &iSecondBinary);
			
		default:
			//nothing to do?
			break;
		}

}

// -----------------------------------------------------------------------------
// CCenRepNotifyHandlerTest::HandleNotifyError
// 
// -----------------------------------------------------------------------------
//
void CCenRepNotifyHandlerTest::HandleNotifyError(TUint32 aId, TInt error, CCenRepNotifyHandler* aHandler)
{
	//initialize if forgotten
	if (iNotifyError < 0)
		iNotifyError = KErrNone;
	
	iLog->Log(_L("HandleNotifyError %d, Keyword %d"), error, aId);
	iNotifyError = error; 
	
	iLog->Log(_L("Start listening again"));
	TRAPD(err, aHandler->StartListeningL());
	if(err != KErrNone) iNotifyError = err;
	
	return;
}


// -----------------------------------------------------------------------------
// ?classname::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
?type ?classname::?member_function(
   ?arg_type arg,
   ?arg_type arg )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// ?function_name implements...
// ?implementation_description.
// Returns: ?value_1: ?description
//          ?value_n: ?description
//                    ?description
// -----------------------------------------------------------------------------
//
/*
?type  ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg )  // ?description
    {

    ?code

    }
*/
//  End of File
