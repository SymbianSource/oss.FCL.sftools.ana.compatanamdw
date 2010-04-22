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
* Description:  ?Description
*
*/

/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */

// INCLUDE FILES
#include <e32math.h>
#include <s32file.h>
#include <e32cons.h>
#include "BCLogEngineTest.h"
#include <cntdef.h>
#include <logwraplimits.h>
#include <logfilterandeventconstants.hrh>
#include <logengdurations.h>
// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
const TInt KTestAddNum = 5;
const TUid KTestEventUid1 = {KLogCallEventType};  
const TUid KTestEventUid2 = {0x10005393};
const TLogDurationType KTestDurationType1 = 1;	   
const TLogDuration KTestDuration1 = 0x00001234;		
const TLogContactItemId KTestContact1 = 0x00001234;	
const TLogContactItemId KTestContact2 = 0x00012345;
const TLogLink KTestLink1 = 0x1234;				
const TLogLink KTestLink2 = 0x1234567;
const TLogFlags KTestFlags1 = 0x6;					
const TLogFlags KTestFlags2 = 0xA;
const TLogSize KTestMaxLogSize = 0xFFF;
const TLogRecentSize KTestMaxRecentLogSize = 0xF;
const TLogAge KTestMaxEventAge = 0xFFFFFFF;
const TLogRecentList KTestRecentList1 = 1;
const TLogRecentList KTestRecentList2 = 2;
const TLogRecentList KTestRecentList3 = 3;

_LIT(KTestEventDesc1, "Event Type Description");
_LIT(KTestEventDesc2, "Changed Event Description");
_LIT(KTestEventDesc3, "Add Event Type");
_LIT(KTestRemoteParty1, "Remote Party");			
_LIT(KTestRemoteParty2, "Changed Remote Party");	
_LIT(KTestDirection1, "Direction");					
_LIT(KTestDirection2, "Changed Direction");			
_LIT(KTestStatus1, "Status");						
_LIT(KTestStatus2, "Changed Status");				
_LIT(KTestSubject1, "Subject");						
_LIT(KTestSubject2, "Changed Subject");				
_LIT(KTestNumber1, "TheNumber");					
_LIT(KTestNumber2, "Changed Number");				
_LIT8(KTestData1, "ABCDEFGH");						
_LIT8(KTestData2, "IJKLMNOPQRSTUVWXYZ");			

// ============================= LOCAL FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// Create_Console
// Creates a new Console Window
// -----------------------------------------------------------------------------
LOCAL_C CConsoleBase* Create_ConsoleL(const TDesC& title)
	{
    CConsoleBase* console;
    
  console = Console::NewL(title,TSize( KConsFullScreen, KConsFullScreen));
	CleanupStack::PushL( console );
	return 	console;
	}

// -----------------------------------------------------------------------------
// Print
// Prints the result onto screen
// -----------------------------------------------------------------------------
LOCAL_C void Print(CConsoleBase* base, TInt result, const TDesC& text)
	{
	base->Printf(text);
	if( result == KErrNone)
		{
		base->Printf(_L(" passed\n"));
		}
	else
		{
		base->Printf(_L("::Error code %d\n"), result);
		}
	}
	
// -----------------------------------------------------------------------------
// Remove_Console
// Deletes a new Console Window
// -----------------------------------------------------------------------------
LOCAL_C void Remove_Console(CConsoleBase* base)
	{
	//base->Getch();
	CleanupStack::PopAndDestroy(base);
	}
	
void Check(TInt aValue, TInt aExpected )
	{
	if(aValue != aExpected)
		{
		RDebug::Print(_L("*** Expected value: %d, got: %d\r\n"), aExpected, aValue);
		__ASSERT_ALWAYS(aValue != aExpected, User::Panic(_L("Active object Error"), 1));
		}
	}

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CBCLogEngineTest::Case
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
const TCaseInfo CBCLogEngineTest::Case ( 
    const TInt aCaseNumber ) const 
     {

     static TCaseInfoInternal const KCases[] =
        {
    //  ENTRY( "LogClient::NotifyChange", TestNotifyChange ),
        ENTRY( "LogClient::NotifyChangeCancel", &CBCLogEngineTest::TestNotifyChangeCancelL),
        ENTRY( "Log Client", &CBCLogEngineTest::TestLogClientL ),
        ENTRY( "Log Base", &CBCLogEngineTest::TestLogBaseL ),
        ENTRY( "Log Event", &CBCLogEngineTest::TestLogEventL ),
        ENTRY( "Log EventType", &CBCLogEngineTest::TestLogEventTypeL ),
        ENTRY( "Log Filter", &CBCLogEngineTest::TestLogFilterL ),
        ENTRY( "Log Wrapper", &CBCLogEngineTest::TestLogWrapperL ),
		ENTRY( "Log ViewRecent", &CBCLogEngineTest::TestLogViewRecentL ),
        ENTRY( "Log ViewEvent", &CBCLogEngineTest::TestLogViewEventL ),
        ENTRY( "Log FilterList", &CBCLogEngineTest::TestLogFilterListL ),
        ENTRY( "Log ViewDuplicate", &CBCLogEngineTest::TestLogViewDuplicateL ),
        ENTRY( "Log Active", &CBCLogEngineTest::TestLogActiveL )
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

// -----------------------------------------------------------------------------
// TestAddEventL
// Add an Event to the Log Engine. This is an asynchronous request
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestAddEventL( CStifLogger* aLog, CLogClient& aClient, TInt& eventId )
    {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling AddEvent") );
    
  	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	event->SetEventType(KTestEventUid2);
	event->SetRemoteParty(KTestRemoteParty1);
	event->SetDirection(KTestDirection1);
	event->SetDurationType(KTestDurationType1);
	event->SetDuration(KTestDuration1);
	event->SetStatus(KTestStatus1);
	event->SetSubject(KTestSubject1);
	event->SetNumber(KTestNumber1);
	event->SetContact(KTestContact1);
	event->SetLink(KTestLink1);
	event->SetDataL(KTestData1);
	event->SetFlags(KTestFlags1);
		//
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	
	eventId = event->Id();
	TInt result = active->iStatus.Int();				
	    
    if( result == KErrNone )
		{
	   	aLog->Log( _L("AddEvent() completed"));
		aLog->Log( _L("Event found") );
		aLog->Log( _L( "Add event == PASS" ));
		}
	else
		{
		aLog->Log( _L( "Add event == FAIL" ));
		}
	
	CleanupStack::PopAndDestroy(2);	
    return result;
    }

// -----------------------------------------------------------------------------
// TestChangeEventL
// Changes the details of an existing event. This is an asynchronous request
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestChangeEventL( CStifLogger* aLog, CLogClient& aClient, TInt eventId )
	{
	aLog->Log(_L("---------------------------------------------"));
	_LIT( KChangeEvent, "Calling ChangeEvent" );
    aLog->Log( KChangeEvent );
   
    CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	TTime now;
	now.UniversalTime();
	
	event->SetId(eventId);
	event->SetTime(now);
	event->SetEventType(KTestEventUid2);
	event->SetRemoteParty(KTestRemoteParty2);
	event->SetDirection(KTestDirection1);
	event->SetDurationType(KTestDurationType1);
	event->SetDuration(KTestDuration1);
	event->SetStatus(KTestStatus1);
	event->SetSubject(KTestSubject1);
	event->SetNumber(KTestNumber1);
	event->SetContact(KTestContact1);
	event->SetLink(KTestLink1);
	event->SetDataL(KTestData1);
	event->SetFlags(KTestFlags1);
	
	active->StartL();
	aClient.ChangeEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();				
	
	if( result == KErrNone )
		{
	    aLog->Log( _L("ChangeEvent() completed"));
		aLog->Log( _L("Event with changed details found") );
		aLog->Log( _L( "Change event == PASS" ));
		}
	else if( result == KErrNotFound )
		{
		aLog->Log( _L( "Change event == FAIL" ));
		}
	CleanupStack::PopAndDestroy(2);
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestChangeEventTypeL
// Changes the details of an existing event type. This is an asynchronous request
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestChangeEventTypeL( CStifLogger* aLog, CLogClient& aClient )
    {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KChangeEventType, "Calling ChangeEventType" );
    aLog->Log( KChangeEventType );
    
    CLogEventType* type = CLogEventType::NewL();
	CleanupStack::PushL(type);
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	type->SetUid(KTestEventUid2);
	type->SetDescription(KTestEventDesc3);
	type->SetLoggingEnabled(ETrue);

	active->StartL();
	aClient.ChangeEventType(*type, active->iStatus);
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();				
	// Test case passed
	
	if( result == KErrNone )
		{
	    aLog->Log( _L("ChangeEventType() completed") );
		aLog->Log( _L("Event type changed") );
		aLog->Log( _L( "Change event type == PASS" ) );
		}
	else
		{
	   	aLog->Log( _L( "Change event type == FAIL" ));
		}
	CleanupStack::PopAndDestroy(2);
	return result;
    }

// -----------------------------------------------------------------------------
// TestGetEventL
// Gets the details of the specified event. This is an asynchronous request.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetEventL( CStifLogger* aLog, CLogClient& aClient, TInt eventId )
    {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetEvent, "Calling GetEvent" );
    aLog->Log( KGetEvent );
    
    CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL( active );
	
    CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	event->SetId( eventId );

	active->StartL();
	aClient.GetEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy(2);
	if( result == KErrNone )
		{
		aLog->Log( _L("GetEvent() Completed") );
		aLog->Log( _L("New event type is registered") );
		aLog->Log( _L( "Get event type == PASS" ) );
		}
	else
		{
		aLog->Log( _L( "Get event == FAIL" ) );
		}

	return result;
    }

// -----------------------------------------------------------------------------
// GetEventTypeL
// Gets the details of an event type. This is an asynchronous request
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetEventTypeL( CStifLogger* aLog, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
   	aLog->Log( _L("Calling GetEventType") );
    
	CLogEventType* 	logEventType = CLogEventType::NewL();;
	CleanupStack::PushL(logEventType);
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL( active );
	
	logEventType->SetUid(KTestEventUid1);
	active->StartL();
	//IMPORT_C void GetEventType(CLogEventType& aType, TRequestStatus& aStatus);
	aClient.GetEventType( *logEventType, active->iStatus );
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();						
	CleanupStack::PopAndDestroy(2);
	
	if(result == KErrNone)
		{
		aLog->Log( _L("Event type successfully fetched") );
		aLog->Log( _L("GetEventType() Completed") );
		aLog->Log( _L("Get event type==PASS") );
		}
	else
		{
		aLog->Log( _L("Get event type==FAIL") );
		}
	
	return result;
   }

// -----------------------------------------------------------------------------
// TestDeleteEventL
// Deletes the event with the specified unique event ID, from the main event log
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestDeleteEventL( CStifLogger* aLog, CLogClient& aClient, TInt eventId )
   {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling DeleteEvent()") );

	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL( active );
	
	active->StartL();
	//IMPORT_C void DeleteEvent(TLogId aId, TRequestStatus& aStatus);
	aClient.DeleteEvent( eventId, active->iStatus );
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy();
	if(result == KErrNone)
		{
		aLog->Log( _L("DeleteEvent() Completed") );
		aLog->Log( _L("Event type successfully deleted") );
		aLog->Log( _L("Delete event==PASS") );
		}
	else
		{
		aLog->Log( _L( "Delete event == FAIL" ) );
		}		

	return result;
   }

// -----------------------------------------------------------------------------
// TestDeleteEventTypeL
// Removes an existing event type. This is an asynchronous request
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestDeleteEventTypeL( CStifLogger* aLog, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling DeleteEventType()") );

	TUid id = KTestEventUid2;// = KLogCallEventType;
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL( active );

	active->StartL();
	//IMPORT_C void DeleteEventType(TUid aId, TRequestStatus& aStatus);
	aClient.DeleteEventType( id, active->iStatus );
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy();		
	
	if(result == KErrNone)
		{
		aLog->Log( _L("DeleteEventType() Completed") );
		aLog->Log( _L("Event type successfully deleted") );
		aLog->Log( _L("Delete event type==PASS") );
		}
	else
		{
		aLog->Log( _L( "Delete event type==FAIL" ));
		}		
	
	return result;
   }

// -----------------------------------------------------------------------------
// TestAddEventTypeL
// Registers a new event type.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestAddEventTypeL( CStifLogger* aLog, CLogClient& aClient )
    {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling AddEventType()") );
    
    CLogEventType* type = CLogEventType::NewL();
	CleanupStack::PushL(type);
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	type->SetUid(KTestEventUid2);
	type->SetDescription(KTestEventDesc3);
	type->SetLoggingEnabled(ETrue);

	active->StartL();
	aClient.AddEventType(*type, active->iStatus);
	CActiveScheduler::Start();

	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy(2);
	
	if( result == KErrNone )
		{
		aLog->Log( _L("AddEventType() completed") );
		aLog->Log( _L("New event type is registered") );
		aLog->Log( _L( "Add event type == PASS" ) );
		}
	else
		{
		aLog->Log( _L( "Add event type == FAIL" ) );
		}
		
	return result;
    }

// -----------------------------------------------------------------------------
// TestClearLogTimeL(TTime)
// Clears all events from the main event log that occurred before the specified date and time.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestClearLogTimeL( CStifLogger* aLog, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KClearLogTime, "Calling ClearLog(TTime)" );
    aLog->Log( KClearLogTime );

  	TTime now;
	now.UniversalTime();
	TDateTime d = now.DateTime();
	
	TTime date1(now);
	date1 -= TTimeIntervalDays(1);

	TTime date2(date1);
	date2 -= TTimeIntervalDays(1);
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	active->StartL();
	//IMPORT_C void ClearLog(const TTime& aDate, TRequestStatus& aStatus);
	aClient.ClearLog( now, active->iStatus );
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy();	
	
	if(result == KErrNone)
		{
		aLog->Log( _L("ClearLog(TTime) Completed") );
		aLog->Log( _L("Events before given time successfully deleted" ) );
		aLog->Log( _L("Clear log - time == PASS") );
		}
	else
		{
		aLog->Log( _L("Clear log - time == FAIL") );
		}
	
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestClearLog(TInt)
// Clears the specified recent event list.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestClearLogEventListL( CStifLogger* aLog, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KClearLogEventList, "Calling ClearLog(TInt)" );
    aLog->Log( KClearLogEventList );

	TLogRecentList list = KLogNullRecentList;
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	active->StartL();
	//IMPORT_C void ClearLog(TInt aRecentList, TRequestStatus& aStatus);
	aClient.ClearLog( list, active->iStatus );
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy();			
	if(result == KErrNone)
		{
		aLog->Log( _L("Calling ClearLog(TInt) Completed") );
		aLog->Log( _L("Events in given recent list successfully deleted" ) );
		aLog->Log( _L("Clear log - event list == PASS") );
		}
	else
		{
		aLog->Log( _L("Clear log - event list == FAIL") );
		}
	
	return result;
   }


// -----------------------------------------------------------------------------
// TestClearLogTimeSimIdL(TTime, TSimId, TRequestStatus)
// Clears all events from the main event log that occurred before the specified date and time.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestClearLogTimeSimIdL( CStifLogger* aLog, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KClearLogTime, "Calling ClearLog(TTime, TSimId, TRequestStatus)" );
    aLog->Log( KClearLogTime );
		
		TInt result = KErrNone;
		
		#ifdef SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM
  	TTime now;
	now.UniversalTime();
	TDateTime d = now.DateTime();
	
	TTime date1(now);
	date1 -= TTimeIntervalDays(1);

	TTime date2(date1);
	date2 -= TTimeIntervalDays(1);
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	active->StartL();
	//IMPORT_C void ClearLog(const TTime& aDate, TSimId aSimId, TRequestStatus& aStatus);
	aClient.ClearLog( now, KLogNullSimId, active->iStatus );
	CActiveScheduler::Start();
	
	result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy();	
		
	#endif //SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM
	if(result == KErrNone)
		{
		aLog->Log( _L("ClearLog(TTime, TSimId, TRequestStatus) Completed") );
		aLog->Log( _L("Events before given time successfully deleted" ) );
		aLog->Log( _L("Clear log - TTimeSimId == PASS") );
		}
	else
		{
		aLog->Log( _L("Clear log - TTimeSimId == FAIL") );
		}
	
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestClearLogIntSimIdL(TInt, TSimId, TRequestStatus)
// Clears the specified recent event list.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestClearLogIntSimIdL( CStifLogger* aLog, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KClearLogEventList, "Calling ClearLog(TInt, TSimId, TRequestStatus)" );
    aLog->Log( KClearLogEventList );

		TInt result = KErrNone;
	
	#ifdef SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM
	TLogRecentList list = KLogNullRecentList;
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	active->StartL();
	//IMPORT_C void ClearLog(TInt aRecentList, TSimId aSimId, TRequestStatus& aStatus);
	aClient.ClearLog( list, KLogNullSimId, active->iStatus );
	CActiveScheduler::Start();
	
	result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy();	
		
		#endif //SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM
				
	if(result == KErrNone)
		{
		aLog->Log( _L("Calling ClearLog(TInt, TSimId, TRequestStatus) Completed") );
		aLog->Log( _L("Events in given recent list successfully deleted" ) );
		aLog->Log( _L("Clear log - TTimeIntSimId == PASS") );
		}
	else
		{
		aLog->Log( _L("Clear log - TTimeIntSimId == FAIL") );
		}
	
	return result;
   }


// -----------------------------------------------------------------------------
// TestChangeConfigL
// Changes the Log Engine configuration
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestChangeConfigL( CStifLogger* aLog, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KChangeConfig, "Calling ChangeConfig()" );
    aLog->Log( KChangeConfig );
	 
	TLogConfig config;
	config.iMaxLogSize = KTestMaxLogSize;
	config.iMaxRecentLogSize = KTestMaxRecentLogSize;
	config.iMaxEventAge = KTestMaxEventAge;
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	active->StartL();
	//IMPORT_C void ChangeConfig(const TLogConfig& aConfig, TRequestStatus& aStatus);
	aClient.ChangeConfig( config, active->iStatus );
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();
	CleanupStack::PopAndDestroy();			
	if(result == KErrNone)
		{
		aLog->Log( _L("ChangeConfig() completed") );
		aLog->Log( _L("Log engine configuration has been changed") );
		aLog->Log( _L("Change config == PASS") );
		}
	else
		{
		aLog->Log( _L("Change config == FAIL") );
		}
	return result;
   }
   
 // -----------------------------------------------------------------------------
// TestGetConfigL
// Gets the Log Engine configuration
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetConfigL( CStifLogger* aLog, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetConfig, "Calling GetConfig()" );
    aLog->Log( KGetConfig );
	
   	TLogConfig config;
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	active->StartL();
	//IMPORT_C void GetConfig(TLogConfig& aConfig, TRequestStatus& aStatus);
	aClient.GetConfig( config, active->iStatus );
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();
	CleanupStack::PopAndDestroy();		
	if(result == KErrNone)
		{
		aLog->Log( _L("GetConfig() completed") );
		aLog->Log( _L("Log engine configuration has been successfully fetched") );
		aLog->Log( _L("Get Config == PASS") );
		}
	else
		{
		aLog->Log( _L("Get Config == FAIL") );
		}
	
	return result;
   }

// -----------------------------------------------------------------------------
// TestGetString
// Gets a standard string from the specified resource in logwrap.dll resource file
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetString( CStifLogger* aLog, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetString, "Calling GetString()" );
    aLog->Log( KGetString );
    
 	TLogString string;
	
	//IMPORT_C TInt GetString(TDes& aString, TInt aId) const;
	TInt result = aClient.GetString( string, R_LOG_DEL_PENDING );

	if( result == KErrNone )
		{
		aLog->Log( _L("GetString() completed") );
		aLog->Log( _L( "Resource string successfully fetched" ) );
		aLog->Log( _L( "Get string == PASS" ) );
		}
	else
		{
		aLog->Log( _L( "Get string == FAIL" ) );
		}
	
	return result;
   }
   

// -----------------------------------------------------------------------------
// TestSetGlobalChangeObserverL
// 
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetGlobalChangeObserverL( CStifLogger* aLog, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetGlobalChangeObserver, "Calling SetGlobalChangeObserverL()" );
    aLog->Log( KSetGlobalChangeObserver );
 
    TBool boolean(ETrue);
	TClientObserverTestReceiver observer(boolean);
	
	//IMPORT_C void SetGlobalChangeObserverL(MLogClientChangeObserver* aObserver);
	TRAPD( result, aClient.SetGlobalChangeObserverL( &observer ));

	if( result == KErrNone )
		{
		aLog->Log( _L("SetGlobalChangeObserverL() completed") );
		aLog->Log( _L("Global change observer successfully set" ) );
		aLog->Log( _L("Set global change observer == PASS") );
		}
	else
		aLog->Log( _L("Set global change observer == FAIL") );
	
	return result;
   }

// -----------------------------------------------------------------------------
// TestAddEventL(CLogBase)
// Add an Event to the Log Engine via CLogWrapper
// -----------------------------------------------------------------------------
LOCAL_C TInt TestAddEventL( CStifLogger* aLog, CLogWrapper& aWrapper ,TInt& eventId )
    {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling AddEvent()") );
       
  	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	event->SetEventType(KTestEventUid1);
	event->SetRemoteParty(KTestRemoteParty1);
	event->SetDirection(KTestDirection1);
	event->SetDurationType(KTestDurationType1);
	event->SetDuration(KTestDuration1);
	event->SetStatus(KTestStatus1);
	event->SetSubject(KTestSubject1);
	event->SetNumber(KTestNumber1);
	event->SetContact(KTestContact1);
	event->SetDataL(KTestData1);
	event->SetFlags(KTestFlags1);
		//
	active->StartL();
	aWrapper.Log().AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	
	eventId = event->Id();
	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy(2);
	
	if( result == KErrNotSupported )
		{
	   	aLog->Log( _L("AddEvent() completed"));
		aLog->Log( _L("AddEvent returned -5 (KErrNotSupported) as expected") );
		aLog->Log( _L( "Add event - via CLogWrapper == PASS" ));
		}
	else if( result == KErrNone )
		{
	   	aLog->Log( _L("AddEvent() completed"));
		aLog->Log( _L("AddEvent returned 0 (KErrNone) (Log Engine Installed) ") );
		aLog->Log( _L( "Add event - via CLogWrapper == PASS" ));
		}
	else
		{
		aLog->Log( _L( "Add event - via CLogWrapper == FAIL" ));
		}
    // Case was executed
    return result;
    }

// -----------------------------------------------------------------------------
// TestChangeEventL(CLogBase)
// Changes the details of an existing event via CLogWrapper.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestChangeEventL( CStifLogger* aLog, CLogWrapper& aWrapper, TInt eventId )
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log( _L("Calling ChangeEvent()") );
	
    CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	TTime now;
	now.UniversalTime();
	
	event->SetId(eventId);
	event->SetTime(now);
	event->SetEventType(KTestEventUid1);
	event->SetRemoteParty(KTestRemoteParty1);
	event->SetDirection(KTestDirection1);
	event->SetDurationType(KTestDurationType1);
	event->SetDuration(KTestDuration1);
	event->SetStatus(KTestStatus1);
	event->SetSubject(KTestSubject1);
	event->SetNumber(KTestNumber1);
	event->SetContact(KTestContact1);
	event->SetDataL(KTestData1);
	event->SetFlags(KTestFlags1);
	
	active->StartL();
	aWrapper.Log().ChangeEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy(2);
	if( result == KErrNotSupported )
		{
	    aLog->Log( _L("ChangeEvent() completed"));
		aLog->Log( _L("ChangeEvent returned -5 (KErrNotSupported) as expected") );
		aLog->Log( _L( "Change event - via CLogWrapper == PASS" ));
		}
	else if( result == KErrNone )
		{
	   	aLog->Log( _L("ChangeEvent() completed"));
		aLog->Log( _L("ChangeEvent returned 0 (KErrNone) (Log Engine Installed) ") );
		aLog->Log( _L( "Change event - via CLogWrapper == PASS" ));
		}
	else
		{
	   	aLog->Log( _L( "Change event - via CLogWrapper == FAIL" ));
		}

	return result;
	}

// -----------------------------------------------------------------------------
// TestGetEventL
// Gets the details of an existing event via CLogWrapper
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetEventL( CStifLogger* aLog, CLogWrapper& aWrapper, TInt eventId )
    {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling GetEvent") );
    
    CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL( active );
	
    CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	event->SetId( eventId );

	active->StartL();
	aWrapper.Log().GetEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy(2);
	if( result == KErrNotSupported )
		{
		aLog->Log( _L("GetEvent() Completed") );
		aLog->Log( _L("GetEvent returned -5 (KErrNotSupported) as expected") );
		aLog->Log( _L( "Get event - via CLogWrapper == PASS" ) );
		}
	else if( result == KErrNone )
		{
	   	aLog->Log( _L("GetEvent() completed"));
		aLog->Log( _L("GetEvent returned 0 (KErrNone) (Log Engine Installed) ") );
		aLog->Log( _L( "Get event - via CLogWrapper == PASS" ));
		}
	else
		{
		aLog->Log( _L( "Get event - via CLogWrapper == FAIL" ) );
		}
	return result;
    }
    
// -----------------------------------------------------------------------------
// TestDeleteEventL
// Deletes an event from the log Via CLogWrapper
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestDeleteEventL( CStifLogger* aLog, CLogWrapper& aWrapper, TInt eventId )
   {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling DeleteEvent()") );
    
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL( active );
	
	active->StartL();
	//IMPORT_C void DeleteEvent(TLogId aId, TRequestStatus& aStatus);
	aWrapper.Log().DeleteEvent( eventId, active->iStatus );
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy();
	if(result == KErrNotSupported)
		{
		aLog->Log( _L("DeleteEvent() Completed") );
		aLog->Log( _L("DeleteEvent returned -5 (KErrNotSupported) as expected") );
		aLog->Log( _L("Delete event - via CLogWrapper == PASS") );
		}
	else if( result == KErrNone )
		{
	   	aLog->Log( _L("DeleteEvent() completed"));
		aLog->Log( _L("DeleteEvent returned 0 (KErrNone) (Log Engine Installed) ") );
		aLog->Log( _L( "Delete event - via CLogWrapper == PASS" ));
		}
	else
		{
		aLog->Log( _L( "Delete event - via CLogWrapper == FAIL" ) );
		}
	return result;
   }
 
// -----------------------------------------------------------------------------
// TestGetString(CLogBase)
// Gets a standard string from the logwrap.dll resource file via CLogWrapper
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetString( CStifLogger* aLog, CLogWrapper& aWrapper )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetString, "Calling GetString()" );
    aLog->Log( KGetString );

 	TLogString string;
	
	//IMPORT_C TInt GetString(TDes& aString, TInt aId) const;
	TInt result = aWrapper.Log().GetString( string, R_LOG_DEL_PENDING );
	
	if( result == KErrNotSupported )
		{
		aLog->Log( _L("GetString() completed") );
		aLog->Log( _L( "GetString returned -5 (KErrNotSupported) as expected" ) );
		aLog->Log( _L( "Get string - via CLogWrapper == PASS" ) );
		}
	else if( result == KErrNone )
		{
	   	aLog->Log( _L("DeleteEvent() completed"));
		aLog->Log( _L("DeleteEvent returned 0 (KErrNone) (Log Engine Installed) ") );
		aLog->Log( _L( "Delete event - via CLogWrapper == PASS" ));
		}
	else
		{
		aLog->Log( _L( "Get string - via CLogWrapper == FAIL" ) );
		}
	
	return result;
   }

// -----------------------------------------------------------------------------
// TestLoadResourcesL
// 
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestLoadResourcesL( CStifLogger* aLog, CMyLogClient& aClient )
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log( _L("Calling LoadResourcesL()") );
	
	RFs session;
	User::LeaveIfError(session.Connect());
	//IMPORT_C void LoadResourcesL(RFs& aFs);
 	TRAPD( result, aClient.LoadResourcesL( session ));
	
	session.Close();
	
	if(result == KErrNone)
		{
		aLog->Log(_L("LoadResourcesL() completed"));
		aLog->Log(_L("Resources successfully loaded"));
		aLog->Log(_L("Load resources - via CLogClient == PASS"));
		}
	else
		aLog->Log(_L("Load resources - via CLogClient == FAIL"));
	
	return result;
	}
	
// -----------------------------------------------------------------------------
// TestResourceFile
// 
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestResourceFile( CStifLogger* aLog, CMyLogClient& aClient )
	{
	aLog->Log(_L("---------------------------------------------"));
	aLog->Log( _L("Calling ResourceFile()") );
	//inline const CResourceFile* ResourceFile() const;
	const CResourceFile* file = aClient.ResourceFile();
	
	aLog->Log(_L("ResourceFile() completed"));
	aLog->Log(_L("Resources file successfully fetched"));
	aLog->Log(_L("Get resource file - via CLogClient == PASS"));

	return KErrNone;
	}     
// -----------------------------------------------------------------------------
// TestClearFlags
// Clears the specified flags for this event
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestClearFlags( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
   	_LIT( KClearFlags, "Calling ClearFlags()" );
    aLog->Log( KClearFlags );
	TInt result = KErrNone;
	
	TLogFlags clearFlags = KTestFlags1; 
	TLogFlags oldFlags = aEvent.Flags();
	
	//inline void ClearFlags(TLogFlags aFlags);
	aEvent.ClearFlags( clearFlags );
	
	TLogFlags newFlags = aEvent.Flags();
	
	if(((~clearFlags) & oldFlags) == newFlags)
		{
		aLog->Log( _L("ClearFlags() completed") );
		aLog->Log( _L("Given flags in current event successfully cleared") );
		aLog->Log( _L( "Clear flags == PASS" ) );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Clear flags == FAIL" ) );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestCopyL
// Makes a copy of the specified log event
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestCopyL( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
	_LIT( KCopyL, "Calling CopyL()" );
    aLog->Log( KCopyL );
    TInt result = KErrNone;
    
	CLogEvent* logEvent = CLogEvent::NewL();
	logEvent->SetEventType(KTestEventUid1);
	logEvent->SetRemoteParty(KTestRemoteParty1);
	logEvent->SetDirection(KTestDirection1);
	logEvent->SetDurationType(KTestDurationType1);
	logEvent->SetDuration(KTestDuration1);
	logEvent->SetStatus(KTestStatus1);
	logEvent->SetSubject(KTestSubject1);
	logEvent->SetNumber(KTestNumber1);
	logEvent->SetContact(KTestContact1);
	logEvent->SetLink(KTestLink1);
	logEvent->SetDataL(KTestData1);
	logEvent->SetFlags(KTestFlags1);
	
	//IMPORT_C void CopyL(const CLogEvent& aEvent);
	aEvent.CopyL( *logEvent );
	
	if(	aEvent.EventType() == logEvent->EventType() &&
	aEvent.RemoteParty() == logEvent->RemoteParty() &&
	aEvent.Direction() == logEvent->Direction() &&
	aEvent.DurationType() == logEvent->DurationType() &&
	aEvent.Duration() == logEvent->Duration() &&
	aEvent.Status() == logEvent->Status() &&
	aEvent.Subject() == logEvent->Subject() &&
	aEvent.Number() == logEvent->Number() &&
	aEvent.Contact() == logEvent->Contact() &&
	aEvent.Link() == logEvent->Link() &&
	aEvent.Data() == logEvent->Data() &&
	aEvent.Flags() == logEvent->Flags()
	)
		{
		aLog->Log( _L("CopyL() completed") );
		aLog->Log( _L("Values in given log event were successfully copied to current event" ) );
		aLog->Log( _L("Copy - log event == PASS" ));
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Copy - log event == FAIL" ) );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestGetContact
// Gets the contact ID associated with the event
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetContact( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
   	_LIT( KGetContact, "Calling Contact()" );
    aLog->Log( KGetContact );
	TInt result = KErrNone;
	
   	//inline TContactItemId Contact() const;
	TLogContactItemId getContact = aEvent.Contact();
	
	if( getContact == KTestContact1 )
		{
		aLog->Log( _L("Contact() completed") );
		aLog->Log( _L("Result data: contact id: %d"), getContact );
		aLog->Log( _L("Get contact == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get Contact == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetContact
// Sets the contact ID associated with the event.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetContact( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetContact, "Calling SetContact()" );
    aLog->Log( KSetContact );
    TInt result = KErrNone;
    
	TLogContactItemId setContact = KTestContact1;
	//inline void SetContact(TContactItemId aContact);
	aEvent.SetContact( setContact );
	
	if( setContact == aEvent.Contact() )
		{
		aLog->Log( _L("SetContact() completed") );
		aLog->Log( _L("Contact id has been successfully stored") );
		aLog->Log( _L("Set contact == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Contact == Fail" ) );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestGetId
// Gets the unique event ID associated with this log event
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetId( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetId, "Calling Id()" );
    aLog->Log( KGetId );
	TInt result = KErrNone;
	 
 	TLogId id( KLogCallEventType );
 	
 	//inline TLogId Id() const;
	TLogId getId = aEvent.Id();
	
	if(id == getId )
		{
		aLog->Log( _L("Id() completed"));
		aLog->Log( _L("Result data: Id: %d"), getId );
		aLog->Log( _L("Get id - log event == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get id - log event == FAIL") );
		}
		
	return result;
   }
 
// -----------------------------------------------------------------------------
// TestSetId
// Sets the unique event ID.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetId( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetId, "Calling SetId()" );
    aLog->Log( KSetId );
 	TInt result = KErrNone;
 	
   	TLogId id = KLogCallEventType;
	
	//inline void SetId(TLogId aId);
	aEvent.SetId(id);
	
	if(id == aEvent.Id())
		{
		aLog->Log( _L("SetId() completed") );
		aLog->Log( _L("id has been successfully stored") );
		aLog->Log( _L("Set Id == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Id == Fail" ) );
		}
	
	return result;	
   }

// -----------------------------------------------------------------------------
// TestEventType
// Gets the type of this log event. Event types are identified by a UID
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestEventType( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetEventType, "Calling EventType()" );
    aLog->Log( KGetEventType );
	TInt result = KErrNone;
	
	//inline TUid EventType() const;
	TUid getUid = aEvent.EventType();
	
	if( getUid == KTestEventUid2 )
		{
		aLog->Log( _L("EventType() completed") );
		aLog->Log( _L("Event type successfully fetched") );
		aLog->Log( _L("Get event type - log event == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Get event type - log event == FAIL" ) );
		}
	
	return result;		
   }
   
// -----------------------------------------------------------------------------
// TestSetEventType
// Sets the type of this log event. Event types are identified by a UID
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetEventType( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetEventType, "Calling SetEventType()" );
    aLog->Log( KSetEventType );
	TInt result = KErrNone;
	
 	TUid setUid = KTestEventUid2;
	
	//inline void SetEventType(TUid aId);
	aEvent.SetEventType( setUid );
	
	if( setUid == aEvent.EventType() )
		{
		aLog->Log( _L("SetEventType() completed") );
		aLog->Log( _L("Event type successfully stored" ) ); 
		aLog->Log( _L("Set event type - log event == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Set event type - log event == FAIL" ) );
		}
		
	return result;	
   }
   
// -----------------------------------------------------------------------------
// TestGetRemoteParty
// Gets the remote party associated with this event
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetRemoteParty( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetRemoteParty, "Calling RemoteParty()" );
    aLog->Log( KGetRemoteParty );
	
    TInt result = KErrNone;

	//inline const TDesC& RemoteParty() const;
	const TBufC<24> getRemote = aEvent.RemoteParty();
	
	if( getRemote == KTestRemoteParty1 )
		{
		aLog->Log( _L("RemoteParty() completed") );
		aLog->Log( _L("Result data: remote party: %S"), &getRemote);
		aLog->Log( _L("Get remote party == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get remote party == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetRemoteParty
// Sets the remote party associated with this event.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetRemoteParty( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetRemoteParty, "Calling RemoteParty()" );
    aLog->Log( KSetRemoteParty );
	TInt result = KErrNone;
	
	TBufC<16> setRemote(KTestRemoteParty1);
	
	//inline void SetRemoteParty(const TDesC& aRemote);
	aEvent.SetRemoteParty( setRemote );
	
	if( setRemote == aEvent.RemoteParty() )
		{
		aLog->Log( _L("SetRemoteParty() completed") );
		aLog->Log( _L("Remote party detail successfully stored") );
		aLog->Log( _L("Set remote party == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set remote party == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestGetTimeL
// Gets the time that this event was created
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetTimeL( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetTime, "Calling Time()" );
    aLog->Log( KGetTime );
	TInt result = KErrNone;
	
	TBuf<30> string;
	_LIT( KFormat, "%*E%*D%X%*N%*Y %1 %2 '%3 %H%:1%T%:2%S");
	TTime setTime(TDateTime(2006,EJanuary,01,12,0,0,0));
	//inline const TTime& Time() const;
	TTime getTime = aEvent.Time();
	
	if( getTime == setTime )
		{
		getTime.FormatL(string, KFormat);
		aLog->Log( _L("Time() completed") );
		aLog->Log( _L("result data: time: %S" ),&string );
		aLog->Log( _L("Get time == PASS") );
		}
	else
		{
		aLog->Log( _L("Get time == FAIL") );
		}
		
	return result;
   }
 
// -----------------------------------------------------------------------------
// TestSetTime
// Sets the time that this event was created
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetTime( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetTime, "Calling SetTime()" );
    aLog->Log( KSetTime );
 	TInt result = KErrNone;
 	
	TTime setTime(TDateTime(2006,EJanuary,01,12,0,0,0));

	//inline void SetTime(const TTime& aTime);
	aEvent.SetTime( setTime );

	if( setTime == aEvent.Time() )
		{
		aLog->Log( _L("SetTime() completed") );
		aLog->Log( _L("Time detail successfully stored" ) );
		aLog->Log( _L("Set time == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set time == FAIL") );
		}
		
	return result;	
   }
   
// -----------------------------------------------------------------------------
// TestGetDurationType
// Gets the duration type
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetDurationType( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetDurationType, "Calling DurationType()" );
    aLog->Log( KGetDurationType );
	TInt result = KErrNone;
	
	TLogDurationType getType;

	//inline TLogDurationType DurationType() const;
	getType = aEvent.DurationType();
	
	if( getType == KTestDurationType1 )
		{
		aLog->Log( _L("DurationType() completed") );
		aLog->Log( _L("Result data: duration type: %d" ), getType );
		aLog->Log( _L("Get duration type == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get duration type == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetDurationType
// Sets the duration type.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetDurationType( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetDurationType, "Calling SetDurationType()" );
    aLog->Log( KSetDurationType );
 	TInt result = KErrNone;
 	
	TLogDurationType setType( KTestDurationType1 );
	//inline void SetDurationType(TLogDurationType aDurationType);
	aEvent.SetDurationType( setType );
	
	if( setType == aEvent.DurationType() )
		{
		aLog->Log( _L("SetDurationType() completed") );
		aLog->Log( _L("Duration type detail successfully stored" ) );
		aLog->Log( _L("Set duration type == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set duration type == FAIL") );
		}
   
   return result;
   }
   
// -----------------------------------------------------------------------------
// TestGetStatus
// Gets the delivery status of this event
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetStatus( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetStatus, "Calling Status()" );
    aLog->Log( KGetStatus );
	TInt result = KErrNone;
	
	TBufC<16> status;
	//inline const TDesC& Status() const;
	status = aEvent.Status();
		
	if( status == KTestStatus2 )
		{
		aLog->Log( _L("Status() completed") );
		aLog->Log( _L("Result data: Status : %S" ), &status );
		aLog->Log( _L("Get status == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get status == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetStatus
// Sets the delivery status of this event
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetStatus( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
   	_LIT( KSetStatus, "Calling SetStatus()" );
    aLog->Log( KSetStatus );
	TInt result = KErrNone;

 	const TBufC<16> setStatus( KTestStatus2 );
	//inline void SetStatus(const TDesC& aStatus);
	aEvent.SetStatus( setStatus );
	
	if( setStatus == aEvent.Status() )
		{
		aLog->Log( _L("SetStatus() completed") );
		aLog->Log( _L("Status has been successfully stored" ) );
		aLog->Log( _L("Set Status == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Status == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestGetDirection
// Gets the direction of the call represented by this event. The direction of a call means incoming, outgoing etc
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetDirection( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetDirection, "Calling Direction()" );
    aLog->Log( KGetDirection );
	TInt result = KErrNone;
	
	TBufC<24> getDirection;
	//inline const TDesC& Direction() const;
	getDirection = aEvent.Direction();
	
	if( getDirection == KTestDirection2 )
		{
		aLog->Log( _L("Direction() completed") );
		aLog->Log( _L("Result data: Direction : %S" ), &getDirection );
		aLog->Log( _L("Get direction == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get direction == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetDirection
// Sets the direction of the call represented by this event.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetDirection( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
 	_LIT( KSetDirection, "Calling SetDirection()" );
    aLog->Log( KSetDirection );
	TInt result = KErrNone;
	
	const TBufC<24> setDirection(KTestDirection2);
	//inline void SetDirection(const TDesC& aDirection);
	aEvent.SetDirection( setDirection );
	
	if( setDirection == aEvent.Direction() )
		{
		aLog->Log( _L("SetDirection() completed") );
		aLog->Log( _L("Direction has been successfully stored") );
		aLog->Log( _L("Set Direction == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Direction == FAIL") );
		}

	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetDuration
// Sets the duration of the event.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetDuration( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetDuration, "Calling SetDuration()" );
    aLog->Log( KSetDuration );
 	TInt result = KErrNone;
 	
	TLogDuration setDuration(KTestDuration1);
	//inline void SetDuration(TLogDuration aDuration);
	aEvent.SetDuration( setDuration );
	
	if( setDuration == aEvent.Duration() )
		{
		aLog->Log( _L("SetDuration() completed") );
		aLog->Log( _L("Duration has been successfully stored" ) );
		aLog->Log( _L("Set Duration == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Duration == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestGetDuration
// Gets the duration of the event.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetDuration( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetDuration, "Calling Duration()" );
    aLog->Log( KGetDuration );
 	TInt result = KErrNone;
 	
 	TLogDuration getDuration;
 	//inline TLogDuration Duration() const;
	getDuration = aEvent.Duration();
	
	if( getDuration == KTestDuration1 )
		{
		aLog->Log( _L("Duration() completed") );
		aLog->Log( _L("Result data: Duration : %S"), &getDuration );
		aLog->Log( _L("Get Duration == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get Duration == FAIL") );
		}
   
   return result;
   }

// -----------------------------------------------------------------------------
// TestGetSubject
// Gets the subject of this event.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetSubject( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
   	_LIT( KGetSubject, "Calling Subject()" );
    aLog->Log( KGetSubject );
	TInt result = KErrNone;
	
	TBufC<24> getSubject;
 	//inline const TDesC& Subject() const;
	getSubject = aEvent.Subject();
	
	if( getSubject == KTestSubject2 )
		{
		aLog->Log( _L("Subject() completed") );
		aLog->Log( _L("Result data: Subject : %S"), &getSubject );
		aLog->Log( _L("Get Subject == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get Subject == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetSubject
// Sets the subject of this event.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetSubject( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetSubject, "Calling SetSubject()" );
    aLog->Log( KSetSubject );
	TInt result = KErrNone;
	
  	const TBufC<24> setSubject( KTestSubject2 );
	//inline void SetSubject(const TDesC& aSubject);
	aEvent.SetSubject( setSubject );
	
	if( setSubject == aEvent.Subject() )
		{
		aLog->Log( _L("SetSubject() completed") );
		aLog->Log( _L("Subject has been successfully stored") );
		aLog->Log( _L("Set Subject == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Subject == FAIL") );
		}
	
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestGetNumber
// Gets the phone number associated with the event.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetNumber( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetNumber, "Calling Number()" );
    aLog->Log( KGetNumber );
	TInt result = KErrNone;
	
	TBufC<24> getNumber;
	//inline const TDesC& Number() const;
	getNumber = aEvent.Number();
	
	if( getNumber == KTestNumber2 )
		{
		aLog->Log( _L("Number() completed") );
		aLog->Log( _L("Result data: Number : %S"), &getNumber);
		aLog->Log( _L("Get Number == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get Number == FAIL") );
		}	
		
   return result;	
   }
   
// -----------------------------------------------------------------------------
// TestSetNumber
// Sets the phone number associated with this event
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetNumber( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
	_LIT( KSetNumber, "Calling SetNumber()" );
    aLog->Log( KSetNumber );
	TInt result = KErrNone;
	
	const TBufC<24> setNumber( KTestNumber2 );
	//inline void SetNumber(const TDesC& aNumber);
	aEvent.SetNumber(setNumber);
	
	if( setNumber == aEvent.Number() )
		{
		aLog->Log( _L("SetNumber() completed") );
		aLog->Log( _L("Number has been successfully stored") );
		aLog->Log( _L("Set Number == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Number == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestGetLink
// Gets the link value
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetLink( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetLink, "Calling Link()" );
    aLog->Log( KGetLink );
    TInt result = KErrNone;
    
    TLogLink getLink;
	//inline TLogLink Link() const;
	getLink = aEvent.Link();
	
	if( getLink == KTestLink2 )
		{
		aLog->Log( _L("Link() completed") );
		aLog->Log( _L("Result data: Link id : %d" ), getLink );
		aLog->Log( _L("Get Link == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get Link == FAIL") );
		}
	
	return result;	
   }
   
// -----------------------------------------------------------------------------
// TestSetLink
// Sets the link value.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetLink( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetLink, "Calling SetLink()" );
    aLog->Log( KSetLink );
    TInt result = KErrNone;
	
	TLogLink setLink( KTestLink2 );
	
	//inline void SetLink(TLogLink aLink);
	aEvent.SetLink( setLink );
	
	if( setLink == aEvent.Link() )
		{
		aLog->Log( _L("SetLink() completed") );
		aLog->Log( _L("Link has been successfully set" ) );
		aLog->Log( _L("Set Link == PASS") );	
		}
	else
		{
		aLog->Log( _L("Set Link == FAIL") );
		}
	
	return result;
   }

// -----------------------------------------------------------------------------
// TestGetDescription
// Gets the human readable name describing the event type.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetDescription( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetDescription, "Calling Description()" );
    aLog->Log( KGetDescription );
	TInt result = KErrNone;
	
	TBufC<32> getDesc;
	//inline const TDesC& Description() const;
	getDesc = aEvent.Description();
	
	if( getDesc == KTestEventDesc2 )
		{
		aLog->Log( _L("Description() completed") );
		aLog->Log( _L("Result data: Description : %S" ), &getDesc );
		aLog->Log( _L("Get Description == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get Description == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetDescription
// Sets the human readable name describing the event type. 
// This can be overridden by logengine
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetDescription( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetDescription, "Calling SetDescription()" );
    aLog->Log( KSetDescription );
	TInt result = KErrNone;
	
	const TBufC<32> setDesc( KTestEventDesc2 );
	//inline void SetDescription(const TDesC& aDescription);
	aEvent.SetDescription( setDesc );
	
	if( aEvent.Description() == setDesc )
		{
		aLog->Log( _L("SetDescription() completed") );
		aLog->Log( _L("Description has been successfully stored" ) );
		aLog->Log( _L("Set Description == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Description == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestGetFlags
// Gets the flags set for this event
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetFlags( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetFlags, "Calling Flags()" );
    aLog->Log( KGetFlags );
	TInt result = KErrNone;
	
	TLogFlags getFlags = 0;

	//inline TLogFlags Flags() const;
	getFlags = aEvent.Flags();
	
	if( getFlags == KTestFlags2 )
		{
		aLog->Log( _L("Flags() completed") );
		aLog->Log( _L("Result data: Flags : %d"), getFlags );
		aLog->Log( _L("Get Flags == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get Flags == FAIL") );
		}
	
	return result;	
   }
   
// -----------------------------------------------------------------------------
// TestSetFlags
// Sets the specified flags for this event
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetFlags( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetFlags, "Calling SetFlags()" );
    aLog->Log( KSetFlags );
	TInt result = KErrNone;
	
	TLogFlags setFlags( KTestFlags2 );
	//inline void SetFlags(TLogFlags aFlags);
	aEvent.SetFlags( setFlags );
	
	TLogFlags getFlags = aEvent.Flags();
	if( setFlags == getFlags )
		{
		aLog->Log( _L("SetFlags() completed") );
		aLog->Log( _L("Flags stored successfully") );
		aLog->Log( _L("Set Flags == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Flags == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestGetData
// Gets event specific data
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetData( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling Data()") );
    TInt result = KErrNone;
    
    TBufC8<24> getData;
    //inline const TDesC8& Data() const;
	getData = aEvent.Data();
	
	if( getData == KTestData2 )
		{
		aLog->Log( _L("Data() completed") );
		aLog->Log( _L("Result data: Data : %S" ), &getData );
		aLog->Log( _L("Get Data == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get Data == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetDataTdes
// Sets event specific data from the specified stream
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetDataTdesL( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetDataTdes, "Calling SetData(TDesC8)" );
    aLog->Log( KSetDataTdes );
	TInt result = KErrNone;

	const TBufC8<24> setData( KTestData2 );
	//IMPORT_C void SetDataL(const TDesC8& aData);
	aEvent.SetDataL( setData );
	
	if( setData == aEvent.Data() )
		{
		aLog->Log( _L("SetData(TDesC8)  completed") );
		aLog->Log( _L("Data(TDesC8) stored successfully") );
		aLog->Log( _L("Set data - TDesC8 == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set data - TDesC8 == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetDataStream
// Sets event specific data from the specified stream
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetDataStreamL( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling SetData(RReadStream)") );
	TInt result = KErrNone;

   	RFs session;
    TBufC8<24> setData;
    User::LeaveIfError(session.Connect());
    TBufC<24> storename(_L("C:\\LogEngine_SetData"));
	RFileReadStream read;
	TInt err = read.Open(session, storename, EFileRead);
	
	RFileWriteStream write;
	setData = KTestData1;
	TInt len = setData.Length();
	
	write.Create(session, storename, EFileWrite);
	err = write.Open(session, storename, EFileWrite);
	write.WriteL( setData );
	write.CommitL();
	write.Close();

	err = read.Open(session, storename, EFileRead);

	//IMPORT_C void SetDataL(RReadStream& aStream, TInt aLen);
	aEvent.SetDataL( read, len );
	
	read.Close();
	TBufC8<24> getData = aEvent.Data();
	
	//now delete the store
	err = session.Delete(storename);
	if(err != KErrNone) 
		{
		RDebug::Print(_L("Error %d deleting \"%S\" file.\n"), err, &storename);
		}
	
	session.Close();
	if( getData == setData )
		{
		aLog->Log( _L("SetData(RReadStream)  completed") );
		aLog->Log( _L("Data(RReadStream) stored successfully") );
		aLog->Log( _L("Set data - RReadStream == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set data - RReadStream == FAIL") );
		}
		
	return result;
   }
      
// -----------------------------------------------------------------------------
// TestInternalizeL
// 
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestInternalizeL( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KInternalize, "Calling InternalizeL()" );
    aLog->Log( KInternalize );
    TInt result = KErrNone;
    
    RFs session;
    User::LeaveIfError(session.Connect());
	TBufC<24> storename(_L("C:\\LogEngine_IO"));
	RFileReadStream read;
	TInt err = read.Open(session, storename, EFileRead);

	//IMPORT_C void InternalizeL(RReadStream &aStream)
	TRAP( result, aEvent.InternalizeL( read ));
	
	read.Close();
	
	//now delete the store
	err = session.Delete(storename);
	if(err != KErrNone) 
		{
		RDebug::Print(_L("Error %d deleting \"%S\" file.\n"), err, &storename);
		}
	if( result == KErrNone )
		{
		aLog->Log( _L("InternalizeL()  completed") );
		aLog->Log( _L("Internalize == PASS") );	
		}
	else
		aLog->Log( _L("Internalize == FAIL") );	
		
	session.Close();	
	return result;	
   }
   
// -----------------------------------------------------------------------------
// TestExternalizeL
// 
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestExternalizeL( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
   	_LIT( KExternalize, "Calling ExternalizeL()" );
    aLog->Log( KExternalize );

	RFs session;
    User::LeaveIfError(session.Connect());
	TBufC<24> storename(_L("C:\\LogEngine_IO"));
	aEvent.SetEventType(KTestEventUid2);
	aEvent.SetRemoteParty(KTestRemoteParty1);
	aEvent.SetDirection(KTestDirection1);
	aEvent.SetDurationType(KTestDurationType1);
	aEvent.SetDuration(KTestDuration1);
	aEvent.SetStatus(KTestStatus1);
	aEvent.SetSubject(KTestSubject1);
	aEvent.SetNumber(KTestNumber1);
	aEvent.SetContact(KTestContact1);
	aEvent.SetLink(KTestLink1);
	aEvent.SetDataL(KTestData1);
	aEvent.SetFlags(KTestFlags1);
	
	RFileWriteStream write;
	write.Create(session, storename, EFileWrite);
	TInt err = write.Open(session, storename, EFileWrite);
		
	//IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	TRAPD( result, aEvent.ExternalizeL( write ));
	
	write.Close();
	
	if( result == KErrNone )
		{
		_LIT( KComplete, "ExternalizeL()  completed" );
		_LIT( KResult, "Externalize == PASS" );
		aLog->Log( KComplete );
		aLog->Log( KResult );
		}
	else
		aLog->Log(_L("Externalize == FAIL"));
	
	session.Close();
	return result;
   }


// -----------------------------------------------------------------------------
// TestLogEventSetSimId(TSimId)
// Sets the specified end time to be used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestLogEventSetSimId( CStifLogger* aLog, CLogEvent& aEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KLogEventSetSimId, "Calling LogEventSetSimId()" );
    aLog->Log( KLogEventSetSimId );
	TInt result = KErrNone;
	
	#ifdef SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM
	
	TSimId idSim = KLogNullSimId;
	
	aEvent.SetSimId( idSim );
	
	if( aEvent.SimId() != KLogNullSimId )
		{
			result = KErrGeneral;
		}
	#endif //SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM
	
	if( result == KErrNone )
		{
		aLog->Log( _L("LogEventSetSimId() completed") );
		aLog->Log( _L("SimId successfully processed") );
		aLog->Log( _L("LogEventSetSimId == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("LogEventSetSimId == FAIL") );
		}
		
		
	return result;
   } 
   
   
 
 
// -----------------------------------------------------------------------------
// TestLoggingEnabled
// Determines whether logging for this event type is enabled.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestLoggingEnabled( CStifLogger* aLog, CLogEventType& aType )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KLogging, "Calling LoggingEnabled()" );
    aLog->Log( KLogging );
	TInt result = KErrNone;
	
 	//inline TBool LoggingEnabled() const;
	TBool logging = aType.LoggingEnabled();
	
	if( logging == EFalse )
		{
		aLog->Log( _L("LoggingEnabled() completed") );
		aLog->Log( _L( "Result data: Logging enabled: %s"), &logging );
		aLog->Log( _L( "Get logging enabled == PASS" ) );	
		}
	else
		aLog->Log( _L( "Get logging enabled == FAIL" ) );	
	
	return result;
   }

// -----------------------------------------------------------------------------
// TestSetLoggingEnabled
// Enables or disables logging for this event type.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetLoggingEnabled( CStifLogger* aLog, CLogEventType& aType )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetLogging, "Calling SetLoggingEnabled()" );
    aLog->Log( KSetLogging );
	TInt result = KErrNone;
	
 	TBool logging = EFalse;
	
	//inline void SetLoggingEnabled(TBool aEnable);
	aType.SetLoggingEnabled( logging );
	
	if( aType.LoggingEnabled() == EFalse )
		{
		aLog->Log( _L("SetLoggingEnabled() completed") );
		aLog->Log( _L( "Logging setting successfully stored" ) );
		aLog->Log( _L( "Set logging enabled == PASS" ) );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Set logging enabled == FAIL" ) );
		}
	
	return result;
   }

// -----------------------------------------------------------------------------
// TestSetDescription
// Sets the human readable and localised name of the event type
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetDescription( CStifLogger* aLog, CLogEventType& aType )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetDescription, "Calling SetDescription()" );
    aLog->Log( KSetDescription );
	TInt result = KErrNone;
	
 	TBufC<24> desc( KTestEventDesc1 );
	
	//inline void SetDescription(const TDesC& aDescription);
	aType.SetDescription( desc );
	
	if( aType.Description() == KTestEventDesc1 )
		{
		aLog->Log( _L("SetDescription() completed") );
		aLog->Log( _L( "Description successfully stored" ) );
		aLog->Log( _L( "Set description == PASS" ) );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Set description == FAIL" ) );
		}
	
	return result;
   }

// -----------------------------------------------------------------------------
// TestGetDescription
// Gets the human readable and localised name of the event type
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetDescription( CStifLogger* aLog, CLogEventType& aType )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetDescription, "Calling GetDescription()" );
    aLog->Log( KGetDescription );
	TInt result = KErrNone;
	
 	//inline const TDesC& Description() const;
	TBufC<24> desc = aType.Description();
	
	if( desc == KTestEventDesc1 )
		{
		aLog->Log( _L("GetDescription() completed") );
		aLog->Log( _L( "result data:  description: %s" ), &desc );
		aLog->Log( _L( "Get description == PASS" ) );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Get description == FAIL" ) );
		}
	
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestCopyL
// Makes a copy of the specified event type
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestCopyL( CStifLogger* aLog, CLogEventType& aType )
   {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling Copy()") );
	TInt result = KErrNone;
	
	CLogEventType* setType = CLogEventType::NewL();
	aType.SetUid(KLogCallEventTypeUid);
	
	setType->Copy( aType );
	
	if( aType.Description() == setType->Description() &&
	aType.LoggingEnabled() == setType->LoggingEnabled() &&
	aType.Uid() == setType->Uid() )
		{
		aLog->Log( _L("Copy() completed") );
		aLog->Log( _L( "Copy successfully completed " ) );
		aLog->Log( _L( "Copy == PASS" ) );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Copy == FAIL" ) );
		}
	
	delete setType;
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestGetUid
// Gets the UID identifying the event type.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetUid( CStifLogger* aLog, CLogEventType& aType )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetDescription, "Calling Uid()" );
    aLog->Log( KGetDescription );
	TInt result = KErrNone;
	
 	//inline TUid Uid() const;
	TUid id = aType.Uid();
	
	if( id == KTestEventUid2 )
		{
		aLog->Log( _L("Uid() completed") );
		aLog->Log( _L( "Result data: Uid: %d" ), id );
		aLog->Log( _L( "Get Uid == PASS" ) );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Get Uid == FAIL" ) );
		}
	
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetUid
// Sets the UID identifying the event type
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetUid( CStifLogger* aLog, CLogEventType& aType )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetDescription, "Calling SetUid()" );
    aLog->Log( KGetDescription );
	TInt result = KErrNone;
	
	TUid id( KTestEventUid2 );
 	//inline void SetUid(TUid aUid);
	aType.SetUid( id );
	
	if( aType.Uid() == KTestEventUid2 )
		{
		aLog->Log( _L("SetUid() completed") );
		aLog->Log( _L( "Uid successfully stored" ) );
		aLog->Log( _L( "Set Uid == PASS" ) );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Set Uid == FAIL" ) );
		}
	
	return result;
   }

  
// -----------------------------------------------------------------------------
// TestEventType(CLogFilter)
// Gets the event type used by the filter.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestEventType( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetEventType, "Calling EventType()" );
    aLog->Log( KGetEventType );
	TInt result = KErrNone;
	
	//inline TUid EventType() const;
	TUid id = aFilter.EventType();
	
	if( id == KTestEventUid2 )
		{
		aLog->Log( _L("EventType() completed") );
		aLog->Log( _L("Event type successfully fetched") );
		aLog->Log( _L("Get event type - log event == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Get event type - log event == FAIL" ) );
		}
	
	return result;		
   }

// -----------------------------------------------------------------------------
// TestGetFlags(CLogFilter)
// Gets the flags used by the filter.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetFlags( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetFlags, "Calling Flags()" );
    aLog->Log( KGetFlags );
	TInt result = KErrNone;
	
	TLogFlags getFlags = 0;
	//inline TLogFlags Flags() const;
	getFlags = aFilter.Flags();
	
	if( getFlags == KTestFlags2 )
		{
		aLog->Log( _L("Flags() completed") );
		aLog->Log( _L("Result data: Flags : %d"), getFlags );
		aLog->Log( _L("Get Flags == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get Flags == FAIL") );
		}
	
	return result;	
   }
   
// -----------------------------------------------------------------------------
// TestSetFlags(CLogFilter)
// Sets the specified flags to be used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetFlags( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetFlags, "Calling SetFlags()" );
    aLog->Log( KSetFlags );
	TInt result = KErrNone;
	
	TLogFlags setFlags( KTestFlags2 );
	//inline void SetFlags(TLogFlags aFlags);
	aFilter.SetFlags( setFlags );
	
	if( setFlags == aFilter.Flags() )
		{
		aLog->Log( _L("SetFlags() completed") );
		aLog->Log( _L("Flags stored successfully") );
		aLog->Log( _L("Set Flags == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Flags == FAIL") );
		}
		
	return result;
   }
  
// -----------------------------------------------------------------------------
// TestSetEventType(CLogFilter)
// Sets the event type to be used by the filter.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetEventType( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetEventType, "Calling SetEventType()" );
    aLog->Log( KSetEventType );
	TInt result = KErrNone;
	
 	TUid id = KTestEventUid2;
	
	//inline void SetEventType(TUid aId);
	aFilter.SetEventType( id );
	
	if( aFilter.EventType() == KTestEventUid2 )
		{
		aLog->Log( _L("SetEventType() completed") );
		aLog->Log( _L("Event type successfully stored" ) ); 
		aLog->Log( _L("Set event type - log event == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Set event type - log event == FAIL" ) );
		}
		
	return result;	
   }
 

// -----------------------------------------------------------------------------
// TestSetContact(CLogFilter)
// Sets the contact ID to be used by the filter.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetContact( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetContact, "Calling SetContact()" );
    aLog->Log( KSetContact );
    TInt result = KErrNone;
    
	TLogContactItemId id = KTestContact1;
	//inline void SetContact(TContactItemId aContact);
	aFilter.SetContact( id );
	
	if( id == aFilter.Contact() )
		{
		aLog->Log( _L("SetContact() completed") );
		aLog->Log( _L("Contact id has been successfully stored") );
		aLog->Log( _L("Set contact == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Contact == Fail" ) );
		}
		
	return result;	
	} 

// -----------------------------------------------------------------------------
// TestSetStatus(CLogFilter)
// Sets the delivery status to be used by the filter.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetStatus( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
   	_LIT( KSetStatus, "Calling SetStatus()" );
    aLog->Log( KSetStatus );
	TInt result = KErrNone;

 	const TBufC<16> setStatus( KTestStatus2 );
	//inline void SetStatus(const TDesC& aStatus);
	aFilter.SetStatus( setStatus );
	
	if( setStatus == aFilter.Status() )
		{
		aLog->Log( _L("SetStatus() completed") );
		aLog->Log( _L("Status has been successfully stored" ) );
		aLog->Log( _L("Set Status == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Status == FAIL") );
		}
		
	return result;
   }

// -----------------------------------------------------------------------------
// TestSetDirection(CLogFilter)
// Sets the direction string to be used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetDirection( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
 	_LIT( KSetDirection, "Calling SetDirection()" );
    aLog->Log( KSetDirection );
	TInt result = KErrNone;
	
	const TBufC<24> direction(KTestDirection2);
	//inline void SetDirection(const TDesC& aDirection);
	aFilter.SetDirection( direction );
	
	if( direction == aFilter.Direction() )
		{
		aLog->Log( _L("SetDirection() completed") );
		aLog->Log( _L("Direction has been successfully stored") );
		aLog->Log( _L("Set Direction == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Direction == FAIL") );
		}

	return result;
   }
   
// -----------------------------------------------------------------------------
// SetDurationType(CLogFilter)
// Sets the duration type to be used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetDurationType( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetDurationType, "Calling SetDurationType()" );
    aLog->Log( KSetDurationType );
 	TInt result = KErrNone;
 	
	TLogDurationType type( KTestDurationType1 );
	//inline void SetDurationType(TLogDurationType aDurationType);
	aFilter.SetDurationType( type );
	
	if( aFilter.DurationType() == type)
		{
		aLog->Log( _L("SetDurationType() completed") );
		aLog->Log( _L("Duration type detail successfully stored" ) );
		aLog->Log( _L("Set duration type == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set duration type == FAIL") );
		}
   
   return result;
   }

// -----------------------------------------------------------------------------
// TestClearFlags(CLogFilter)
// Clears the specified flags to be used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestClearFlags( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
   	_LIT( KClearFlags, "Calling ClearFlags()" );
    aLog->Log( KClearFlags );
	TInt result = KErrNone;
	
	TLogFlags clearFlags = KTestFlags1; 
	TLogFlags oldFlags = aFilter.Flags();
	
	//inline void ClearFlags(TLogFlags aFlags);
	aFilter.ClearFlags( clearFlags );
	
	TLogFlags newFlags = aFilter.Flags(); 	
	TLogFlags flags = (~clearFlags) & oldFlags;
	if( flags == newFlags ) 
		{
		aLog->Log( _L("ClearFlags() completed") );
		aLog->Log( _L("Given flags in current event successfully cleared") );
		aLog->Log( _L( "Clear flags == PASS" ) );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L( "Clear flags == FAIL" ) );
		}
		
	return result;
   }
        
// -----------------------------------------------------------------------------
// TestGetContact(CLogFilter)
// Gets the contact ID used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetContact( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
   	_LIT( KGetContact, "Calling Contact()" );
    aLog->Log( KGetContact );
	TInt result = KErrNone;
	
   	TLogContactItemId setId( KTestContact2 );
   	
 	aFilter.SetContact( setId );
	//inline TContactItemId Contact() const;
	TLogContactItemId getId = aFilter.Contact();
	
	if( getId == setId )
		{
		aLog->Log( _L("Contact() completed") );
		aLog->Log( _L("Result data: contact id: %d"), getId );
		aLog->Log( _L("Get contact == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get Contact == FAIL") );
		}
		
	
	return result;
   }
     
// -----------------------------------------------------------------------------
// TestGetDurationType(CLogFilter)
// Gets the duration type used by the filter.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetDurationType( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetDurationType, "Calling DurationType()" );
    aLog->Log( KGetDurationType );
	TInt result = KErrNone;
	
	TLogDurationType type;
	//inline TLogDurationType DurationType() const;
	type = aFilter.DurationType();
	
	if( type == KTestDurationType1 )
		{
		aLog->Log( _L("DurationType() completed") );
		aLog->Log( _L("Result data: duration type: %d" ), type );
		aLog->Log( _L("Get duration type == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get duration type == FAIL") );
		}
		
	return result;
   }
   

// -----------------------------------------------------------------------------
// TestGetStatus(CLogFilter)
// Gets the delivery status used by the filter.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetStatus( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetStatus, "Calling Status()" );
    aLog->Log( KGetStatus );
	TInt result = KErrNone;
	
	TBufC<16> status;
	
	//inline const TDesC& Status() const;
	status = aFilter.Status();
		
	if( status == KTestStatus2 )
		{
		aLog->Log( _L("Status() completed") );
		aLog->Log( _L("Result data: Status : %S" ), &status );
		aLog->Log( _L("Get status == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get status == FAIL") );
		}
		
	return result;
   }
   

 // -----------------------------------------------------------------------------
// TestGetDirection(CLogFilter)
// Gets the direction string used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetDirection( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetDirection, "Calling Direction()" );
    aLog->Log( KGetDirection );
	TInt result = KErrNone;
	
	TBufC<24> direction;
  	//inline const TDesC& Direction() const;
	direction = aFilter.Direction();
	
	if( direction == KTestDirection2 )
		{
		aLog->Log( _L("Direction() completed") );
		aLog->Log( _L("Result data: Direction : %S" ), &direction );
		aLog->Log( _L("Get direction == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get direction == FAIL") );
		}
		
	return result;
   }
   


// -----------------------------------------------------------------------------
// TestGetNumber(CLogFilter)
// Gets the phone number used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetNumber( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetNumber, "Calling Number()" );
    aLog->Log( KGetNumber );
	TInt result = KErrNone;
	
	TBufC<24> number;
 	//inline const TDesC& Number() const;
	number = aFilter.Number();
	
	if( number == KTestNumber2 )
		{
		aLog->Log( _L("Number() completed") );
		aLog->Log( _L("Result data: Number : %S"), &number);
		aLog->Log( _L("Get Number == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get Number == FAIL") );
		}	
		
   return result;	
   }
   
// -----------------------------------------------------------------------------
// TestSetNumber(CLogFilter)
// Sets the phone number to be used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetNumber( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
	_LIT( KSetNumber, "Calling SetNumber()" );
    aLog->Log( KSetNumber );
	TInt result = KErrNone;
	
	const TBufC<24> number( KTestNumber2 );
	//inline void SetNumber(const TDesC& aNumber);
	aFilter.SetNumber(number);
	
	if( number == aFilter.Number() )
		{
		aLog->Log( _L("SetNumber() completed") );
		aLog->Log( _L("Number has been successfully stored") );
		aLog->Log( _L("Set Number == PASS") );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set Number == FAIL") );
		}
		
	return result;
   }
   
 // -----------------------------------------------------------------------------
// TestGetRemoteParty(CLogFilter)
// Gets the remote party string used by the filter.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetRemoteParty( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetRemoteParty, "Calling RemoteParty()" );
    aLog->Log( KGetRemoteParty );
	
    TInt result = KErrNone;
    //inline const TDesC& RemoteParty() const;
	const TBufC<24> remote = aFilter.RemoteParty();
	
	if( remote == KTestRemoteParty1 )
		{
		aLog->Log( _L("RemoteParty() completed") );
		aLog->Log( _L("Result data: remote party: %S"), &remote);
		aLog->Log( _L("Get remote party == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get remote party == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetRemoteParty(CLogFilter)
// Sets the remote party string to be used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetRemoteParty( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetRemoteParty, "Calling RemoteParty()" );
    aLog->Log( KSetRemoteParty );
	TInt result = KErrNone;
	
	TBufC<16> remote(KTestRemoteParty1);
	
	//inline void SetRemoteParty(const TDesC& aRemote);
	aFilter.SetRemoteParty( remote );
	
	if( aFilter.RemoteParty() == KTestRemoteParty1 )
		{
		aLog->Log( _L("SetRemoteParty() completed") );
		aLog->Log( _L("Remote party detail successfully stored") );
		aLog->Log( _L("Set remote party == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set remote party == FAIL") );
		}
		
	return result;
   }
// -----------------------------------------------------------------------------
// TestGetNullFields(CLogFilter)
// Identifies the fields defined as NULL in the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetNullFields( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KNullFields, "Calling NullFields()" );
    aLog->Log( KNullFields );
	TInt result = KErrNone;
	
	//inline TUint32 NullFields() const;
	TUint32 getFields = aFilter.NullFields();
	
	if( getFields == 100000 )
		{
		aLog->Log( _L("NullFields() completed") );
		aLog->Log( _L("Result data: null fields: %d"), getFields );
		aLog->Log( _L("Get null fields == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get null fields == FAIL") );
		}
		
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetNullFields(CLogFilter)
// Defines NULL fields to the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetNullFields( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetNullFields, "Calling SetNullFields()" );
    aLog->Log( KSetNullFields );
	TInt result = KErrNone;
	
	TUint32 setFields = 100000;
	
	//inline void SetNullFields(TUint32 aFields);
	aFilter.SetNullFields( setFields );
	
	if( aFilter.NullFields() == 100000 )
		{
		aLog->Log( _L("SetNullFields() completed") );
		aLog->Log( _L("Null fields successfully stored") );
		aLog->Log( _L("Set null fields == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set null fields == FAIL") );
		}
		
	return result;
   } 
   
// -----------------------------------------------------------------------------
// TestCopyL(CLogFilter)
// Makes a copy of a filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestCopyL( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KCopy, "Calling Copy()" );
    aLog->Log( KCopy );
	TInt result = KErrNone;
	
	CLogFilter* temp = CLogFilter::NewL();
	
	//IMPORT_C void Copy(const CLogFilter& aFilter);
	temp->Copy( aFilter );
	
	if( aFilter.EventType() == temp->EventType() &&
	aFilter.RemoteParty() == temp->RemoteParty() &&
	aFilter.Direction() == temp->Direction() &&
	aFilter.DurationType() == temp->DurationType() &&
	aFilter.Status() == temp->Status() &&
	aFilter.Number() == temp->Number() &&
	aFilter.Contact() == temp->Contact() &&
	aFilter.Flags() == temp->Flags() )
		{
		aLog->Log( _L("Copy() completed") );
		aLog->Log( _L("Filter details successfully copied") );
		aLog->Log( _L("Copy == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Copy == FAIL") );
		}
		
	return result;
   } 
   
// -----------------------------------------------------------------------------
// TestStartTime(CLogFilter)
// Gets the start time used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestStartTime( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KStartTime, "Calling StartTime()" );
    aLog->Log( KStartTime );
	TInt result = KErrNone;
	
	//inline const TTime& StartTime() const;
	TTime start = aFilter.StartTime();
	
	if( start == 100000 )
		{
		aLog->Log( _L("StartTime() completed") );
		aLog->Log( _L("Result data: Start time: yymmdd hh:mm:ss") );
		aLog->Log( _L("Get start time == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get start time == FAIL") );
		}
		
	return result;
   } 
   
 // -----------------------------------------------------------------------------
// TestEndTime(CLogFilter)
// Gets the end time used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestEndTime( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KEndTime, "Calling EndTime()" );
    aLog->Log( KEndTime );
	TInt result = KErrNone;
	
	//inline const TTime& EndTime() const;
	TTime end = aFilter.EndTime();
	
	if( end == 100000 )
		{
		aLog->Log( _L("EndTime() completed") );
		aLog->Log( _L("Result data: End time: yymmdd hh:mm:ss") );
		aLog->Log( _L("Get end time == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get start time == FAIL") );
		}
		
	return result;
   } 
   
 // -----------------------------------------------------------------------------
// TestSetStartTime(CLogFilter)
// Sets the specified start time to be used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetStartTime( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetStartTime, "Calling SetStartTime()" );
    aLog->Log( KSetStartTime );
	TInt result = KErrNone;
	
	TTime setStart = 100000;
	
	//inline void SetStartTime(const TTime& aStartTime);
	aFilter.SetStartTime( setStart );
	
	if( aFilter.StartTime() == 100000 )
		{
		aLog->Log( _L("SetStartTime() completed") );
		aLog->Log( _L("Result data: Start time: yymmdd hh:mm:ss") );
		aLog->Log( _L("Get start time == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Get start time == FAIL") );
		}
		
	return result;
   } 
   
// -----------------------------------------------------------------------------
// TestSetEndTime(CLogFilter)
// Sets the specified end time to be used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetEndTime( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetEndTime, "Calling SetEndTime()" );
    aLog->Log( KSetEndTime );
	TInt result = KErrNone;
	
	TTime setEnd = 100000;
	
	//inline void SetEndTime(const TTime& aEndTime);
	aFilter.SetEndTime( setEnd );
	
	if( aFilter.EndTime() == 100000 )
		{
		aLog->Log( _L("SetEndTime() completed") );
		aLog->Log( _L("End time successfully stored") );
		aLog->Log( _L("Set end time == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Set end time == FAIL") );
		}
		
	return result;
   } 



// -----------------------------------------------------------------------------
// TestLogFilterSetSimId(TSimId)
// Sets the specified end time to be used by the filter
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestLogFilterSetSimId( CStifLogger* aLog, CLogFilter& aFilter )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KLogFilterSetSimId, "Calling LogFilterSetSimId()" );
    aLog->Log( KLogFilterSetSimId );
	TInt result = KErrNone;
	
	#ifdef SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM
	
	TSimId idSim = KLogNullSimId;
	
	aFilter.SetSimId( idSim );
	
	if( aFilter.SimId() != KLogNullSimId )
		{
			result = KErrGeneral;
		}
	
	#endif //SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM 
	
	if( result == KErrNone )
		{
		aLog->Log( _L("LogFilterSetSimId() completed") );
		aLog->Log( _L("SimId successfully processed") );
		aLog->Log( _L("LogFilterSetSimId == PASS") );
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("LogFilterSetSimId == FAIL") );
		}
		
	return result;
   } 
   
  
 
// -----------------------------------------------------------------------------
// GetClientAvailable
// Determines whether the Log Engine is installed
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetClientAvailable( CStifLogger* aLog, CLogWrapper& aWrapper )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetClientAvailable, "Calling ClientAvailable()" );
    aLog->Log( KGetClientAvailable );

 	//IMPORT_C TBool ClientAvailable() const;
	TBool client = aWrapper.ClientAvailable();
	
	aLog->Log( _L("ClientAvailable() completed") );
	aLog->Log( _L( "Result data: Client available: %d" ), client );
	aLog->Log( _L( "Get client available == PASS" ) );
	
	return KErrNone;
   }

// -----------------------------------------------------------------------------
// TestGetLog
// Gets a reference to the Log Engine object
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetLogL( CStifLogger* aLog, CLogWrapper& aWrapper )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetLog, "Calling Log()" );
    aLog->Log( KGetLog );
		
	CLogBase* base = new(ELeave) CLogBase( 0 );
	CleanupStack::PushL(base);
	
 	//inline CLogBase& Log();
	base = &aWrapper.Log();
	
	aLog->Log( _L("Log() completed") );
	aLog->Log( _L("Log reference successfully fetched" ) );
	aLog->Log( _L("Get log == PASS" ) );
	
	CleanupStack::PopAndDestroy();
	return KErrNone;
   }
   
// -----------------------------------------------------------------------------
// TestClearDuplicatesL
// 
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestClearDuplicatesL( CStifLogger* aLog, CLogViewRecent& aLogRecent, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KClearDuplicates, "Calling ClearDuplicatesL()" );
    aLog->Log( KClearDuplicates );
	TInt result = KErrNone;
	
	CActiveLogEngine* active = new(ELeave)CActiveLogEngine();
	CleanupStack::PushL(active);

	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);

	CLogViewDuplicate* aLogDuplicateView = CLogViewDuplicate::NewL(aClient);
	CleanupStack::PushL(aLogDuplicateView);
	
	aClient.ClearLog(KLogNullRecentList, active->iStatus);
	active->StartL();
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	TBuf<KLogMaxDirectionLength> incoming;
	aClient.GetString(incoming, R_LOG_DIR_IN);

	event->SetEventType(KLogCallEventTypeUid);

	// Add 5 recent events to each list - with 5 duplicates each

	// Incoming
	event->SetDirection(incoming);
	TInt recent;
	for(recent = 1; recent <= 5; recent++)
		{
		event->SetContact(recent);
		for(TInt duplicate = 1; duplicate <= 6; duplicate++)
			{
			active->StartL();
			aClient.AddEvent(*event, active->iStatus);
			CActiveScheduler::Start();
			result = active->iStatus.Int();
			}
		}

	// Check incoming
	TBool res = aLogRecent.SetRecentListL(KLogRecentIncomingCalls, active->iStatus);
	TInt count = aLogRecent.CountL(); // == 5);

	// Clear duplicates for incoming
	aLogRecent.ClearDuplicatesL();
	count = aLogRecent.CountL(); // == 5);

	do
		{
		active->StartL();
		CActiveScheduler::Start();
		result = active->iStatus.Int();

		// No duplicates should exist for this view now
		res = aLogRecent.DuplicatesL(*aLogDuplicateView, active->iStatus);
		count = aLogDuplicateView->CountL(); // == 0);
		}
	while(aLogRecent.NextL(active->iStatus));

	if( result == KErrNone && count == 0)
		{
		aLog->Log( _L("ClearDuplicatesL() completed") );
		aLog->Log( _L("Duplicates successfully cleared" ) );
		aLog->Log( _L("Clear duplicates == PASS" ) );	
		}
	else
		{
		aLog->Log( _L("Clear duplicates == FAIL" ) );	
		}	
	
	CleanupStack::PopAndDestroy(3);
	return result;
   }

// -----------------------------------------------------------------------------
// TestSetRecentListL
// Initialises or refreshes the view for the specified recent event list.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetRecentListL( CStifLogger* aLog, CLogViewRecent& aLogRecent, CLogClient& aClient )
   {
   	aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetRecentList, "Calling SetRecentListL(TLogRecentList)" );
    aLog->Log( KSetRecentList );
	
	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	TBuf<KLogMaxDirectionLength> buf;
	aClient.GetString(buf, R_LOG_DIR_IN);

	event->SetEventType(KTestEventUid1);
	event->SetDirection(buf);

	TInt count;
	for( count=0; count<KTestAddNum; count++)	
		{
		event->SetContact(count);
		
		active->StartL();
		aClient.AddEvent(*event, active->iStatus);
		CActiveScheduler::Start();
		
		if(active->iStatus.Int() != KErrNone) break;
		}
	
	TLogRecentList list = KTestRecentList1;
	
	active->StartL();
 	//IMPORT_C TBool SetRecentListL(TLogRecentList aList, TRequestStatus& aStatus);
	aLogRecent.SetRecentListL( list, active->iStatus );
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();
	TInt lst_num = aLogRecent.RecentList();
	TInt total = aLogRecent.CountL();;
	count = aLogRecent.CountL();
	if( total == KTestAddNum )
	while( --count > 0 )
	   {
	    active->StartL();
		aLogRecent.NextL(active->iStatus);
		CActiveScheduler::Start();
		
		if( active->iStatus.Int() != KErrNone ||
				lst_num != KTestRecentList1 ) 
			break;
	   }
		
	if( result == KErrNone && count == 0 )
		{
		aLog->Log( _L("SetRecentListL(TLogRecentList) completed") );
		aLog->Log( _L("Recent list successfully stored" ) );
		aLog->Log( _L("Set recent list (TLogRecentList) == PASS" ) );
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L("Set recent list (TLogRecentList) == FAIL" ) );
		}
	
	CleanupStack::PopAndDestroy(2);
	return result;
   }

// -----------------------------------------------------------------------------
// TestSetRecentListL(CLogFilter)
// Initialises or refreshes the view for the specified recent event list, conforming to the specified filter.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetRecentListFilterL( CStifLogger* aLog, CLogViewRecent& aLogRecent, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetRecentList, "Calling SetRecentListL(TLogRecentList, CLogFilter)" );
    aLog->Log( KSetRecentList );

	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);

	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	CLogFilter* filter = CLogFilter::NewL();
	CleanupStack::PushL(filter);
	
	TBuf<KLogMaxDirectionLength> buf;
	aClient.GetString(buf, R_LOG_DIR_OUT);

	event->SetEventType(KTestEventUid1);
	event->SetDirection(buf);
	
	TInt count;
	for( count=0; count<KTestAddNum; count++)	
		{
		event->SetContact(count);
		
		active->StartL();
		aClient.AddEvent(*event, active->iStatus);
		CActiveScheduler::Start();
		
		if(active->iStatus.Int() != KErrNone) break;
		}
	
	TLogRecentList list = KTestRecentList2;
	filter->SetEventType(KTestEventUid1);
	filter->SetDirection(buf);
	filter->SetContact(1);
	
	active->StartL();
	//IMPORT_C TBool SetRecentListL(TLogRecentList aList, const CLogFilter& aFilter, TRequestStatus& aStatus);
	aLogRecent.SetRecentListL( list, *filter, active->iStatus );
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();
	TInt lst_num = aLogRecent.RecentList();
	count = aLogRecent.CountL();
	
	while( --count > 0 )
	   {
	    active->StartL();
		aLogRecent.NextL(active->iStatus);
		CActiveScheduler::Start();
		
		if( active->iStatus.Int() != KErrNone ||
				lst_num != KTestRecentList2 ) 
			break;
	   }
	 
	if( result == KErrNone && count == 0)
		{
		aLog->Log( _L("SetRecentListL(TLogRecentList, CLogFilter) completed") );
		aLog->Log( _L("Recent list successfully stored" ) );
		aLog->Log( _L("Set recent list (TLogRecentList, CLogFilter) == PASS" ) );	
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L("Set recent list (TLogRecentList, CLogFilter) == FAIL" ) );
		}
	
	CleanupStack::PopAndDestroy(3);
	return result;
   }

// -----------------------------------------------------------------------------
// TestSetRecentListFilterListL
// Initialises or refreshes the view for the specified recent event list, conforming to the set of specified filters.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetRecentListFilterListL( CStifLogger* aLog, CLogViewRecent& aLogRecent, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetRecentList, "Calling SetRecentListL(TLogRecentList, CLogFilterList)" );
    aLog->Log( KSetRecentList );
	
	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);

	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	CLogFilter* filterOne = CLogFilter::NewL();
	CleanupStack::PushL(filterOne);
	
	CLogFilter* filterTwo = CLogFilter::NewL();
	CleanupStack::PushL(filterTwo);

	CLogFilterList* list = new(ELeave) CLogFilterList();
	CleanupStack::PushL(list);
	
	TBuf<KLogMaxDirectionLength> buf;
	aClient.GetString(buf, R_LOG_DIR_IN);

	event->SetEventType(KTestEventUid1);
	event->SetDirection(buf);

	TInt count;
	for( count=0; count<KTestAddNum; count++)	
		{
		event->SetContact(count);
		
		active->StartL();
		aClient.AddEvent(*event, active->iStatus);
		CActiveScheduler::Start();
		
		if(active->iStatus.Int() != KErrNone) break;
		}
	
	TLogRecentList list_num = KTestRecentList1;
		
	filterOne->SetEventType(KTestEventUid1);
	filterOne->SetDirection(buf);
	
	filterTwo->SetContact(1);
	
	list->AppendL(filterOne);
	list->AppendL(filterTwo);
	
	active->StartL();
	//IMPORT_C TBool SetRecentListL(TLogRecentList aList, const CLogFilterList& aFilterList, TRequestStatus& aStatus);
	aLogRecent.SetRecentListL( list_num, *list, active->iStatus );
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();
	TInt lst_num = aLogRecent.RecentList();
	TInt total = aLogRecent.CountL();;
	count = aLogRecent.CountL();
	
	while( --count > 0 )
	   {
	    active->StartL();
		aLogRecent.NextL(active->iStatus);
		CActiveScheduler::Start();
		
		if( active->iStatus.Int() != KErrNone ||
				lst_num != KTestRecentList3 ) 
			break;
	   }
	 
	 if( result == KErrNone && count == 0)
		{
		aLog->Log( _L("SetRecentListL(TLogRecentList, CLogFilterList) completed") );
		aLog->Log( _L("Recent list successfully stored" ) );
		aLog->Log( _L("Set recent list (TLogRecentList, CLogFilter) == PASS" ) );	
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L("Set recent list (TLogRecentList, CLogFilterList) == FAIL" ) );
		}
	
	CleanupStack::PopAndDestroy(5);
	return result;
   }

// -----------------------------------------------------------------------------
// TestGetDuplicatesL
// Refreshes the specified duplicate event view with the duplicates of the current 
// event in the recent event list view.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetDuplicatesL( CStifLogger* aLog, CLogViewRecent& aLogRecent, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetDuplicates, "Calling DuplicatesL(CLogViewDuplicate)" );
    aLog->Log( KGetDuplicates );
	
	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);

	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	CLogViewDuplicate* aLogViewDuplicate = CLogViewDuplicate::NewL(aClient);
	CleanupStack::PushL(aLogViewDuplicate);
	
	TBool res = aLogRecent.SetRecentListL(KLogRecentIncomingCalls, active->iStatus);
	active->StartL();
	CActiveScheduler::Start();
	TInt count = aLogRecent.CountL();

	res = aLogRecent.DuplicatesL(*aLogViewDuplicate, active->iStatus);
	active->StartL();
	CActiveScheduler::Start();
	count = aLogViewDuplicate->CountL();

	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();

	res = aLogRecent.SetRecentListL(KLogRecentIncomingCalls, active->iStatus);
	active->StartL();
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	count = aLogRecent.CountL();
	res = aLogRecent.FirstL(active->iStatus);
	active->StartL();
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	
	TLogId lastId = event->Id();
	count = aLogViewDuplicate->CountL(); // == 0

	event->SetRemoteParty(KTestRemoteParty1);
	event->SetContact(KTestContact1);
	event->SetNumber(KNullDesC);

	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	res = aLogRecent.SetRecentListL(KLogRecentIncomingCalls, active->iStatus);
	active->StartL();
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	count = aLogRecent.CountL(); // == 1);
	res = aLogRecent.FirstL(active->iStatus);
	active->StartL();
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	//TEST(view->Event().Id() == event->Id());

	res = aLogRecent.DuplicatesL(*aLogViewDuplicate, active->iStatus);
	active->StartL();
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	count = aLogViewDuplicate->CountL(); // == 1);
	//TEST(dView->Event().Id() == lastId);
	lastId = event->Id();

	event->SetRemoteParty(KTestRemoteParty1);
	event->SetContact(0);
	event->SetNumber(KNullDesC);

	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	res = aLogRecent.SetRecentListL(KLogRecentIncomingCalls, active->iStatus);
	active->StartL();
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	count = aLogRecent.CountL(); // == 1);
	res = aLogRecent.FirstL(active->iStatus);
	active->StartL();
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	//TEST(view->Event().Id() == event->Id());

	res = aLogRecent.DuplicatesL(*aLogViewDuplicate, active->iStatus);
	active->StartL();
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	count = aLogViewDuplicate->CountL(); // == 2);
	//TEST(dView->Event().Id() == lastId);

	count = aLogRecent.CountL();
	result = active->iStatus.Int();
	if( result == KErrNone )
		{
		aLog->Log( _L("DuplicatesL(CLogViewDuplicate) completed") );
		aLog->Log( _L("Duplicates successfully fetched" ) );
		aLog->Log( _L("Get DuplicatesL(CLogViewDuplicate) == PASS" ) );	
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L("Get DuplicatesL(CLogViewDuplicate) == FAIL" ) );
		}
	
	CleanupStack::PopAndDestroy(3);
	return result;
   }


// -----------------------------------------------------------------------------
// TestGetDuplicatesFilterL
// Refreshes the specified duplicate event view with the duplicates of the current 
// event in the recent event list view and conforming to the specified filter. 
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetDuplicatesFilterL( CStifLogger* aLog, CLogViewRecent& aLogRecent, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetDuplicates, "Calling DuplicatesL(CLogViewDuplicate,CLogFilter)" );
    aLog->Log( KGetDuplicates );
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);

	CLogFilter* filter = CLogFilter::NewL();
	CleanupStack::PushL(filter);

	CLogViewDuplicate* aLogViewDuplicate = CLogViewDuplicate::NewL(aClient);
	CleanupStack::PushL(aLogViewDuplicate);
	
	// Make sure there are no entries in any recent lists
	active->StartL();
	aClient.ClearLog(KLogNullRecentList, active->iStatus);
	CActiveScheduler::Start();
	TInt result = active->iStatus.Int();

	// Incoming
	TBuf<KLogMaxDirectionLength> incoming;
	aClient.GetString(incoming, R_LOG_DIR_IN);

	event->SetEventType(KLogCallEventTypeUid);
	event->SetDirection(incoming);
	event->SetRemoteParty(KTestRemoteParty1);
	event->SetContact(KTestContact1);
	event->SetNumber(KTestNumber1);
	
	// Add event
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	event->SetDurationType(KLogDurationValid);

	// Add event
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	event->SetStatus(KTestStatus1);

	// Add event
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	event->SetDurationType(KLogDurationNone);
	event->SetStatus(KNullDesC);

	// Add event - This will be the entry in recent list
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	// Should only be one event in recent list - the rest are duplicates
	active->StartL();
	aLogRecent.SetRecentListL(KLogRecentIncomingCalls, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	TInt count = aLogRecent.CountL(); // == 1);

	// Check duplicate count
	active->StartL();
	aLogRecent.DuplicatesL(*aLogViewDuplicate, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	count = aLogViewDuplicate->CountL(); //== 3);

	filter->SetDurationType(KLogDurationValid);

	active->StartL();
	aLogRecent.DuplicatesL(*aLogViewDuplicate, *filter, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	count = aLogViewDuplicate->CountL(); // == 2);

	if( result == KErrNone )
		{
		aLog->Log( _L("DuplicatesL(CLogViewDuplicate,CLogFilter) completed") );
		aLog->Log( _L("Duplicates successfully fetched" ) );
		aLog->Log( _L("Get duplicates (CLogViewDuplicate,CLogFilter)  == PASS" ) );	
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L("Get duplicates (CLogViewDuplicate,CLogFilter)  == FAIL" ) );
		}
	
	CleanupStack::PopAndDestroy(4);
	return result;
   }


// -----------------------------------------------------------------------------
// TestGetDuplicatesFilterListL
// Refreshes the specified duplicate event view with the duplicates of the current 
// event in the recent event list view and conforming to the set of specified filters.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetDuplicatesFilterListL( CStifLogger* aLog, CLogViewRecent& aLogRecent, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetDuplicates, "Calling DuplicatesL(CLogViewDuplicate,CLogFilterList)" );
    aLog->Log( KGetDuplicates );
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);

	CLogFilter* filter = CLogFilter::NewL();
	CleanupStack::PushL(filter);

	CLogViewDuplicate* aLogViewDuplicate = CLogViewDuplicate::NewL(aClient);
	CleanupStack::PushL(aLogViewDuplicate);
	
	CLogFilterList* list = new(ELeave) CLogFilterList();
	CleanupStack::PushL(list);
	
	// Make sure there are no entries in any recent lists
	active->StartL();
	aClient.ClearLog(KLogNullRecentList, active->iStatus);
	CActiveScheduler::Start();
	TInt result = active->iStatus.Int();

	// Incoming
	TBuf<KLogMaxDirectionLength> incoming;
	aClient.GetString(incoming, R_LOG_DIR_IN);

	event->SetEventType(KLogCallEventTypeUid);
	event->SetDirection(incoming);
	event->SetRemoteParty(KTestRemoteParty1);
	event->SetContact(KTestContact1);
	event->SetNumber(KTestNumber1);
	
	// Add event
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	event->SetDurationType(KLogDurationValid);

	// Add event
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	event->SetStatus(KTestStatus1);

	// Add event
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	event->SetDurationType(KLogDurationNone);
	event->SetStatus(KNullDesC);

	// Add event - This will be the entry in recent list
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	// Should only be one event in recent list - the rest are duplicates
	active->StartL();
	aLogRecent.SetRecentListL(KLogRecentIncomingCalls, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	TInt count = aLogRecent.CountL(); // == 1);

	// Check duplicate count
	active->StartL();
	aLogRecent.DuplicatesL(*aLogViewDuplicate, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	count = aLogViewDuplicate->CountL(); //== 3);

	list->AppendL(filter);
	
	filter->SetDurationType(KLogDurationValid);

	active->StartL();
	aLogRecent.DuplicatesL(*aLogViewDuplicate, *list, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	count = aLogViewDuplicate->CountL(); // == 2);

	if( result == KErrNone )
		{
		aLog->Log( _L("DuplicatesL(CLogViewDuplicate,CLogFilterList) completed") );
		aLog->Log( _L("Duplicates successfully fetched" ) );
		aLog->Log( _L("Get duplicates (CLogViewDuplicate,CLogFilterList)  == PASS" ) );	
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L("Get duplicates (CLogViewDuplicate,CLogFilterList) == FAIL" ) );
		}
	
	CleanupStack::PopAndDestroy(5);
	return result;
   }

// -----------------------------------------------------------------------------
// TestGetRecentList
// Gets the recent event list number that identifies the recent event list to 
// which the current entry belongs
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetRecentList( CStifLogger* aLog, CLogViewRecent& aLogRecent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetRecentList, "Calling RecentListL()" );
    aLog->Log( KGetRecentList );
	TInt result = KErrNone;
		
	TLogRecentList list = 0;
	
	//inline TLogRecentList RecentList() const;
	list = aLogRecent.RecentList();
	
	if( list == KTestRecentList1 )	
		{
		aLog->Log( _L("RecentListL() completed") );
		aLog->Log( _L("Recent list successfully stored" ) );
		aLog->Log( _L("Get recent list  == PASS" ) );	
		}
	else
		{
		aLog->Log( _L("Get recent list  == FAIL" ) );	
		}	
		
	return result;
   }

// -----------------------------------------------------------------------------
// TestRemoveL(LogId)
// Removes the event with the specified unique event ID from the view.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestRemoveOnLogIdL( CStifLogger* aLog, CLogViewRecent& aLogRecent, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KRemove, "Calling RemoveL(TLogId)" );
    aLog->Log( KRemove );
	TInt result = KErrNone;
	
	CActiveLogEngine* active = new(ELeave)CActiveLogEngine;
	CleanupStack::PushL(active);
	
	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	// Make sure there are no entries in any recent lists
	active->StartL();
	aClient.ClearLog(KLogNullRecentList, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	TLogString buf;
	aClient.GetString(buf, R_LOG_DIR_IN);

	// Add some events
	event->SetEventType(KLogCallEventTypeUid);
	event->SetDirection(buf);
	event->SetDurationType(KLogDurationNone);
	event->SetContact(KTestContact1);
	event->SetStatus(KTestStatus1);

	// Add event
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	// Create the view
	active->StartL();
	TBool res = aLogRecent.SetRecentListL(KLogNullRecentList, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	
	TInt count = aLogRecent.CountL();
	TInt id = aLogRecent.Event().Id();
	aLogRecent.RemoveL(id);
	
	count = aLogRecent.CountL();
	if( !count )
		{
		aLog->Log( _L("RemoveL(TLogId) completed") );
		aLog->Log( _L("Event successfully removed" ) );
		aLog->Log( _L("Remove (TLogId)  == PASS" ) );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Remove (TLogId)  == FAIL" ) );	
		}		
	CleanupStack::PopAndDestroy(2);
	return result;
   }

// -----------------------------------------------------------------------------
// TestRemoveL
// Removes the current event from its recent event list.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestRemoveL( CStifLogger* aLog, CLogViewRecent& aLogRecent, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KRemove, "Calling RemoveL(TRequestStatus)" );
    aLog->Log( KRemove );
	
	CActiveLogEngine* active = new(ELeave)CActiveLogEngine;
	CleanupStack::PushL(active);
	
	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	// Make sure there are no entries in any recent lists
	active->StartL();
	aClient.ClearLog(KLogNullRecentList, active->iStatus);
	CActiveScheduler::Start();
	TInt result = active->iStatus.Int();
	TLogString buf;
	aClient.GetString(buf, R_LOG_DIR_IN);

	// Add some events
	event->SetEventType(KLogCallEventTypeUid);
	event->SetDirection(buf);
	event->SetDurationType(KLogDurationNone);
	event->SetContact(KTestContact1);
	event->SetStatus(KTestStatus1);
	// Add event
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	
	event->SetContact(KTestContact2);
	// Add event
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	
	// Create the view
	active->StartL();
	TBool res = aLogRecent.SetRecentListL(KLogNullRecentList, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	
	TInt count = aLogRecent.CountL();//2
	active->StartL();
	//IMPORT_C TBool RemoveL(TRequestStatus& aStatus);
	TBool rem = aLogRecent.RemoveL(active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	
	count = aLogRecent.CountL();
	if( rem == EFalse )
		aLog->Log( _L("No Events in View"));
		
	if( result == KErrNone && count==1 )
		{
		aLog->Log( _L("RemoveL(TRequestStatus) completed") );
		aLog->Log( _L("Event successfully removed" ) );
		aLog->Log( _L("Remove (TRequestStatus)  == PASS" ) );	
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L("Remove (TRequestStatus)  == FAIL" ) );	
		}
		
	CleanupStack::PopAndDestroy(2);
	return result;
   }


// -----------------------------------------------------------------------------
// TestSetFilterL(CLogFilter)
// Initialises or refreshes the event view defined by the specified filter.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetFilterL( CStifLogger* aLog, CLogViewEvent& aLogViewEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetFilter, "Calling SetFilterL(CLogFilter)" );
    aLog->Log( KSetFilter );

	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	CLogFilter* logFilter = CLogFilter::NewL();
	CleanupStack::PushL(logFilter);
	
	logFilter->SetContact(KTestContact1);
	
 	active->StartL();
	//IMPORT_C TBool SetFilterL(const CLogFilter& aFilter, TRequestStatus& aStatus);
	TBool view = aLogViewEvent.SetFilterL( *logFilter, active->iStatus );
	CActiveScheduler::Start(); 
	
	TInt result = active->iStatus.Int();
	if( view == EFalse )
		{
		aLog->Log( _L("No Views Defined"));
		}
		
	if( result == KErrNone )
		{
		aLog->Log( _L("SetFilterL(CLogFilter) completed") );
		aLog->Log( _L( "Filter successfully stored" ) );
		aLog->Log( _L( "Set filter (CLogFilter) == PASS" ) );
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L( "Set filter (CLogFilter) == FAIL" ) );
		}
		
	CleanupStack::PopAndDestroy(2);
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestSetFilterL(CLogFilterList)
// Initialises or refreshes the event view defined by the set of specified filters
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetFilterL( CStifLogger* aLog, CLogViewEvent& aLogViewEvent, CLogFilterList& aLogFilterList )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetFilter, "Calling SetFilterL(CLogFilterList)" );
    aLog->Log( KSetFilter );

	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);

	CLogFilter* filterOne = CLogFilter::NewL();
    CleanupStack::PushL( filterOne );
    
    CLogFilter* filterTwo = CLogFilter::NewL();
    CleanupStack::PushL( filterTwo );
    
    filterOne->SetContact(KTestContact1);
    filterTwo->SetContact(KTestContact2);
      
    aLogFilterList.AppendL( filterOne );
    aLogFilterList.AppendL( filterTwo );
    
	active->StartL();
	//IMPORT_C TBool SetFilterL(const CLogFilterList& aFilterList, TRequestStatus& aStatus);
	TBool view = aLogViewEvent.SetFilterL( aLogFilterList, active->iStatus );
	CActiveScheduler::Start(); 
	
	TInt result = active->iStatus.Int();
	if( view == EFalse )
		{
		aLog->Log( _L("No Views Defined"));
		}
	
	if( result == KErrNone )
		{
		aLog->Log( _L("SetFilterL(CLogFilterList) completed") );
		aLog->Log( _L( "Filter successfully stored" ) );
		aLog->Log( _L( "Set filter (CLogFilterList) == PASS" ) );
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L( "Set filter (CLogFilterList) == FAIL" ) );
		}

	CleanupStack::PopAndDestroy(3);		
	return result;
   }

// -----------------------------------------------------------------------------
// TestSetFilterParseFilterByFilterL
// 
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetFilterParseFilterByFilterL( CStifLogger* aLog, CLogViewEvent& aLogViewEvent, CLogClient& aClient )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetFilter, "Calling SetFilterParseFilterByFilterL()" );
    aLog->Log( KSetFilter );

 	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);

	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	CLogFilterList* filterList = new(ELeave) CLogFilterList();
	CleanupStack::PushL(filterList);

	// VOICE CALL
	event->SetEventType(KLogCallEventTypeUid);
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	TEST(active->iStatus.Int(),KErrNone);
	const TLogId event1 = event->Id();

	// SMS, CONTACT SEARCHED
	event->SetEventType(KLogShortMessageEventTypeUid);
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	TEST(active->iStatus.Int(),KErrNone);
	const TLogId event2 = event->Id();

	CLogFilter* filter1 = CLogFilter::NewL();
	CleanupStack::PushL(filter1);
	filter1->SetEventType(KLogCallEventTypeUid); // ALL VOICE CALL EVENTS
	filterList->AppendL(filter1);
	
	TInt count = aLogViewEvent.CountL(); //0
	TBool view = aLogViewEvent.SetFilterParseFilterByFilterL(*filterList, active->iStatus);
	TEST( view, ETrue);
	
	active->StartL();
	CActiveScheduler::Start();
	TEST(active->iStatus.Int(),KErrNone);
	count = aLogViewEvent.CountL(); //1
	
	// Check correct events
	active->StartL();
	view = aLogViewEvent.FirstL(active->iStatus);
	CActiveScheduler::Start();
	TEST(active->iStatus.Int(),KErrNone);
	TLogId eventId = aLogViewEvent.Event().Id();
	TEST(eventId,event1);
	TEST( view, ETrue);
	
	TInt result = active->iStatus.Int();
	if( result == KErrNone )
		{
		aLog->Log( _L("SetFilterParseFilterByFilterL() completed") );
		aLog->Log( _L( "Filter successfully stored" ) );
		aLog->Log( _L( "Set filter parse filter by filter == PASS" ) );
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L( "Set filter parse filter by filter == FAIL" ) );
		}
	
	CleanupStack::PopAndDestroy(4);	
	return result;
   }

// -----------------------------------------------------------------------------
// TestCopyL
// Creates a copy of this set of event view filters.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestCopyL( CStifLogger* aLog, CLogFilterList& aLogFilterList )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KCopy, "Calling CopyL()" );
    aLog->Log( KCopy );
	TInt result = KErrGeneral;		
	
	CLogFilter* filterOne = CLogFilter::NewL();
    CleanupStack::PushL( filterOne );
    
    CLogFilter* filterTwo = CLogFilter::NewL();
    CleanupStack::PushL( filterTwo );
    
    filterOne->SetContact(KTestContact1);
    filterTwo->SetContact(KTestContact2);
    
    aLogFilterList.AppendL( filterOne );
    aLogFilterList.AppendL( filterTwo );
    
	CLogFilterList* list = new(ELeave) CLogFilterList();
	CleanupStack::PushL( list );
	//IMPORT_C CLogFilterList* CopyL() const;
	list = aLogFilterList.CopyL();
	
	TInt count = aLogFilterList.Count();
	if( list->Count() == count )
		{
		for( TInt i=0;i<count; i++ )
			if(list->At(i) != aLogFilterList.At(i)) break;
		result = KErrNone;
		}
		
	if( result == KErrNone )	
		{
		aLog->Log( _L("CopyL() completed") );
		aLog->Log( _L( "Filter list details successfully copied" ) );
		aLog->Log( _L( "CopyL == PASS" ) );		
		}
	else
		{
		aLog->Log( _L( "CopyL == FAIL" ) );		
		}
	
	CleanupStack::PopAndDestroy(3);
	return result;
   }
   
// -----------------------------------------------------------------------------
// TestCopyLC
// Creates a copy of this set of event view filters and 
// puts a pointer to the copy onto the cleanup stack.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestCopyLC( CStifLogger* aLog, CLogFilterList& aLogFilterList )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KCopy, "Calling CopyLC()" );
    aLog->Log( KCopy );
	TInt result = KErrGeneral;	
	
	CLogFilterList* list = new(ELeave) CLogFilterList();
	CleanupStack::PushL( list );
	//IMPORT_C CLogFilterList* CopyLC() const;
	list = aLogFilterList.CopyLC();
	
	TInt count = aLogFilterList.Count();
	if( list->Count() == count )
		{
		for( TInt i=0;i<count; i++ )
			if(list->At(i) == aLogFilterList.At(i)) break;
		result = KErrNone;
		}
	
	if( result == KErrNone )	
		{
		aLog->Log( _L("CopyLC() completed") );
		aLog->Log( _L( "Filter list details successfully copied" ) );
		aLog->Log( _L( "CopyLC == PASS" ) );		
		}
	else
		{
		aLog->Log( _L( "CopyLC == FAIL" ) );		
		}
		
	CleanupStack::PopAndDestroy(2);	
	return result;
   }
 
// -----------------------------------------------------------------------------
// TestRemoveL(LogId)
// Removes the event with the specified unique event ID from the view
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestRemoveOnLogIdL( CStifLogger* aLog, CLogViewDuplicate& aLogDuplicate, CLogClient& aClient)
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KRemove, "Calling RemoveL(TLogId)" );
    aLog->Log( KRemove );
	TInt result = KErrNone;
	
	CActiveLogEngine* active = new(ELeave)CActiveLogEngine;
	CleanupStack::PushL(active);
	
	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);

	CLogViewRecent* view = CLogViewRecent::NewL(aClient);
	CleanupStack::PushL(view);

	// Make sure there are no entries in any recent lists
	active->StartL();
	aClient.ClearLog(KLogNullRecentList, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	// Incoming
	TLogString buf;
	aClient.GetString(buf, R_LOG_DIR_IN);

	// Add some events
	event->SetEventType(KLogCallEventTypeUid);
	event->SetDirection(buf);
	event->SetDurationType(KLogDurationNone);
	event->SetContact(KTestContact1);
	event->SetStatus(KTestStatus1);

	TInt count = KTestAddNum;
	while(count--)
		{
		// Add event
		active->StartL();
		aClient.AddEvent(*event, active->iStatus);
		CActiveScheduler::Start();
		result = active->iStatus.Int();
		}

	// Create the view
	active->StartL();
	TBool res = view->SetRecentListL(KLogNullRecentList, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	// Create the duplicate view
	active->StartL();
	res = view->DuplicatesL(aLogDuplicate, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	count = view->CountL(); // 1 
	count = aLogDuplicate.CountL(); // 4
	
	TInt id = aLogDuplicate.Event().Id();
	while(aLogDuplicate.NextL(active->iStatus))
		{
		active->StartL();
		CActiveScheduler::Start();
		result = active->iStatus.Int();

		// Try removing the previous event
		aLogDuplicate.RemoveL(id);
		id = aLogDuplicate.Event().Id();
	    }
	
	aLogDuplicate.RemoveL(id);
	count = aLogDuplicate.CountL();//0	
	if( !count )
		{
		aLog->Log( _L("RemoveL(TLogId) completed") );
		aLog->Log( _L("Event successfully removed" ) );
		aLog->Log( _L("Remove (TLogId)  == PASS" ) );	
		}
	else
		{
		result = KErrGeneral;
		aLog->Log( _L("Remove (TLogId)  == FAIL" ) );	
		}
	
	CleanupStack::PopAndDestroy(3);
	return result;
   }

// -----------------------------------------------------------------------------
// TestRemoveL
// Removes the current event from the duplicate list
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestRemoveL( CStifLogger* aLog, CLogViewDuplicate& aLogDuplicate, CLogClient& aClient)
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KRemove, "Calling RemoveL(TRequestStatus)" );
    aLog->Log( KRemove );
	TInt result = KErrNone;
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);

	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);

	CLogViewRecent* view = CLogViewRecent::NewL(aClient);
	CleanupStack::PushL(view);

	// Make sure there are no entries in any recent lists
	active->StartL();
	aClient.ClearLog(KLogNullRecentList, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	// Incoming
	TLogString buf;
	aClient.GetString(buf, R_LOG_DIR_IN);

	// Add some events
	event->SetEventType(KLogCallEventTypeUid);
	event->SetDirection(buf);
	event->SetDurationType(KLogDurationNone);
	event->SetContact(KTestContact1);
	event->SetStatus(KTestStatus1);

	TInt count = KTestAddNum;
	while(count--)
		{
		// Add event
		active->StartL();
		aClient.AddEvent(*event, active->iStatus);
		CActiveScheduler::Start();
		result = active->iStatus.Int();
		}

	// Create the view
	active->StartL();
	TBool res = view->SetRecentListL(KLogNullRecentList, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();

	// Create the duplicate view
	active->StartL();
	res = view->DuplicatesL(aLogDuplicate, active->iStatus);
	CActiveScheduler::Start();
	result = active->iStatus.Int();
	count = view->CountL(); // == 1);
	count = aLogDuplicate.CountL(); //9
	
	TLogId id = view->Event().Id();
	while(view->NextL(active->iStatus))
		{
		active->StartL();
		CActiveScheduler::Start();
		result = active->iStatus.Int();

		// Try removing the previous event
		view->RemoveL(active->iStatus);
		active->StartL();
		CActiveScheduler::Start();
		result = active->iStatus.Int();
		id = view->Event().Id();
		}

	if( res == EFalse )
		aLog->Log( _L("No Events in View"));
		
	if( result == KErrNone)
		{
		aLog->Log( _L("RemoveL(TRequestStatus) completed") );
		aLog->Log( _L("Event successfully removed" ) );
		aLog->Log( _L("Remove (TRequestStatus)  == PASS" ) );	
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L("Remove (TRequestStatus)  == FAIL" ) );	
		}
		
	CleanupStack::PopAndDestroy(3);
	return result;
   }

// -----------------------------------------------------------------------------
// TestSource
// Returns the unique ID of the event for which all the events in this view are duplicates
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSource( CStifLogger* aLog, CLogViewDuplicate& aLogDuplicate)
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSource, "Calling Source()" );
    aLog->Log( KSource );
	TInt result = KErrNone;
	
	//inline TLogId Source() const;
	TLogId id = aLogDuplicate.Source();
	
	aLog->Log( _L("Source() completed") );
	aLog->Log( _L("Result data: Event id: %d" ), id );
	aLog->Log( _L("Source ()  == PASS" ) );
		
	return result;
   }

// -----------------------------------------------------------------------------
// TestGetCountL
// Gets the number of events in the view
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetCountL( CStifLogger* aLog, CLogViewEvent& aViewEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetCount, "Calling CountL()" );
    aLog->Log( KGetCount );
	TInt result = KErrNone;
	
	//IMPORT_C TInt CountL();
	TInt count = aViewEvent.CountL();
	
	aLog->Log( _L("CountL() completed") );
	aLog->Log( _L( "Result data: Count: %d" ), count );
	aLog->Log( _L( "Get count == PASS" ) );
	
	return result;
   }

// -----------------------------------------------------------------------------
// TestGetEventL
// Returns details of the log event at the current position within the view.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestGetEventL( CStifLogger* aLog, CLogViewEvent& aViewEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KGetEvent, "Calling Event()" );
    aLog->Log( KGetEvent );
	TInt result = KErrNone;
	
	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	//inline const CLogEvent& Event() const;
	event->CopyL(aViewEvent.Event());
	
	aLog->Log( _L("Event() completed") );
	aLog->Log( _L("Result data: Event id: %d"), event->Id());
	aLog->Log( _L("Get event == PASS") );
		
	CleanupStack::PopAndDestroy();
	return result;
   }

// -----------------------------------------------------------------------------
// TestFirstL
// Moves the current position in the view to the first event
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestFirstL( CStifLogger* aLog, CLogViewEvent& aViewEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KFirst, "Calling First()" );
    aLog->Log( KFirst );
		
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL( active );
	
	active->StartL();
	//IMPORT_C TBool FirstL(TRequestStatus& aStatus);
	TBool event = aViewEvent.FirstL(active->iStatus);
	CActiveScheduler::Start();
	
	if( event == EFalse )
		{
		aLog->Log( _L("No Event in View"));
		}
	
	TInt result = active->iStatus.Int();
	if( result == KErrNone )
		{
		aLog->Log( _L("FirstL() completed") );	
		aLog->Log( _L( "Moved to first event successfully") );
		aLog->Log( _L( "First == PASS" ) );	
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L( "First == FAIL" ) );	
		}
	
	CleanupStack::PopAndDestroy();
	return result;
   }

// -----------------------------------------------------------------------------
// TestLastL
// Moves the current position in the view to the last event
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestLastL( CStifLogger* aLog, CLogViewEvent& aViewEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KLast, "Calling Last()" );
    aLog->Log( KLast );
		
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL( active );
	
	active->StartL();
	//IMPORT_C TBool LastL(TRequestStatus& aStatus);
	TBool event = aViewEvent.LastL(active->iStatus);
	CActiveScheduler::Start();
	
	if( event == EFalse )
		{
		aLog->Log( _L("No Event in View"));
		}
	
	TInt result = active->iStatus.Int();
	if( result == KErrNone )
		{
		aLog->Log( _L("LastL() completed") );	
		aLog->Log( _L( "Moved to last event successfully") );
		aLog->Log( _L( "Last == PASS" ) );	
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L( "Last == FAIL" ) );	
		}
	
	CleanupStack::PopAndDestroy();
	return result;
   }

// -----------------------------------------------------------------------------
// TestNextL
// Moves the current position in the view to the next event.
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestNextL( CStifLogger* aLog, CLogViewEvent& aViewEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KNext, "Calling NextL()" );
    aLog->Log( KNext );
		
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL( active );
	
	active->StartL();
	//IMPORT_C TBool NextL(TRequestStatus& aStatus);
	TBool event = aViewEvent.NextL(active->iStatus);
	CActiveScheduler::Start();
	
	if( event == EFalse )
		{
		aLog->Log( _L("No Event in View"));
		}
	
	TInt result = active->iStatus.Int();
	if( result == KErrNone )
		{
		aLog->Log( _L("NextL() completed") );	
		aLog->Log( _L("Moved to next event successfully") );
		aLog->Log( _L("Next == PASS" ) );
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L( "Next == FAIL" ) );	
		}
	
	CleanupStack::PopAndDestroy();
	return result;
   }

// -----------------------------------------------------------------------------
// TestPreviousL
// Moves the current position in the view to the previous event. 
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestPreviousL( CStifLogger* aLog, CLogViewEvent& aViewEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KPrevious, "Calling PreviousL()" );
    aLog->Log( KPrevious );
		
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL( active );
	
	active->StartL();
	//IMPORT_C TBool PreviousL(TRequestStatus& aStatus);
	TBool event = aViewEvent.PreviousL(active->iStatus);
	CActiveScheduler::Start();
	
	if( event == EFalse )
		{
		aLog->Log( _L("No Event in View"));
		}
	
	TInt result = active->iStatus.Int();
	if( result == KErrNone )
		{
		aLog->Log( _L("PreviousL() completed") );	
		aLog->Log( _L("Moved to previous event successfully") );
		aLog->Log( _L("Next == PASS" ) );
		}
	else
		{
		aLog->Log( _L("Error -- %d"), result );
		aLog->Log( _L("Previous == FAIL" ) );	
		}
	
	CleanupStack::PopAndDestroy();
	return result;
   }

// -----------------------------------------------------------------------------
// TestSetFlags
// 
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestSetFlags( CStifLogger* aLog, CLogViewEvent& aViewEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KSetFlags, "Calling SetFlagsL()" );
    aLog->Log( KSetFlags );
	TInt result = KErrNone;
	
	TLogFlags flags = KTestFlags1;
	//IMPORT_C void SetFlagsL(TLogFlags aFlags);
	TRAP( result, aViewEvent.SetFlagsL( flags ));
	
	if( result == KErrNone )
		{
		aLog->Log( _L("SetFlagsL() completed") );
		aLog->Log( _L("Flags successfully set"));
		aLog->Log( _L("Set Flags == PASS") );
		}
	else
		aLog->Log( _L("Set Flags == FAIL") );
				
	return result;
   }


// -----------------------------------------------------------------------------
// TestDoCancelL(CLogView)
// Implements cancellation of an outstanding request
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestDoCancelL( CStifLogger* aLog, CLogViewEvent& aViewEvent )
   {
    aLog->Log(_L("---------------------------------------------"));
    _LIT( KDoCancel, "Calling DoCancel()" );
    aLog->Log( KDoCancel );
	TInt result = KErrNone;
	
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL( active );
	
	active->StartL();
	TBool event = aViewEvent.FirstL(active->iStatus);
	//The active object's Cancel in turn calls CLogView::DoCancel();
	aViewEvent.Cancel();
	CActiveScheduler::Start();

	if(active->iStatus.Int() == KErrCancel)
		{
		aLog->Log( _L("DoCancel() completed") );
		aLog->Log( _L("Outstanding request successfully cancelled") );
		aLog->Log( _L("Do Cancel == PASS") );
		}
	else
		{
		aLog->Log( _L("Do Cancel == FAIL") );
		}
		
	CleanupStack::PopAndDestroy();
	return result;
   }


// -----------------------------------------------------------------------------
// TestCompleteL
// Add an Event to the Log Engine
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestCompleteL( CStifLogger* aLog, CLogClient& aClient )
    {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling Complete()") );
       
  	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	CMyLogActive* active = new(ELeave) CMyLogActive();
	CleanupStack::PushL(active);
	
	event->SetEventType(KTestEventUid1);
	event->SetRemoteParty(KTestRemoteParty1);
	event->SetDirection(KTestDirection1);
	event->SetDurationType(KTestDurationType1);
	event->SetDuration(KTestDuration1);
	event->SetStatus(KTestStatus1);
	event->SetSubject(KTestSubject1);
	event->SetNumber(KTestNumber1);
	event->SetContact(KTestContact1);
	event->SetDataL(KTestData1);
	event->SetFlags(KTestFlags1);
		//
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	CActiveScheduler::Start();
	
	active->Complete(active->iStatus.Int());
	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy(2);
	
	if( result == KErrNone )
		{
	   	aLog->Log( _L("Complete() completed"));
		aLog->Log( _L("Complete successfully done") );
		aLog->Log( _L( "Complete == PASS" ));
		}
	else
		{
		aLog->Log( _L( "Complete == FAIL" ));
		}
    // Case was executed
    return result;
    }

// -----------------------------------------------------------------------------
// TestDoCancelL
// Add an Event to the Log Engine
// Implements cancellation of an outstanding request
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestDoCancelL( CStifLogger* aLog ,CLogClient& aClient )
    {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling DoCancel()") );
       
  	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	CMyLogActive* active = new(ELeave) CMyLogActive;
	CleanupStack::PushL(active);
	
	event->SetEventType(KTestEventUid1);
	event->SetRemoteParty(KTestRemoteParty1);
	event->SetDirection(KTestDirection1);
	event->SetDurationType(KTestDurationType1);
	event->SetDuration(KTestDuration1);
	event->SetStatus(KTestStatus1);
	event->SetSubject(KTestSubject1);
	event->SetNumber(KTestNumber1);
	event->SetContact(KTestContact1);
	event->SetDataL(KTestData1);
	event->SetFlags(KTestFlags1);
		//
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	aClient.Cancel();
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy(2);
	
	if( result == KErrCancel )
		{
	   	aLog->Log( _L("DoCancel() completed"));
		aLog->Log( _L("DoCancel successfully done") );
		aLog->Log( _L( "Do cancel == PASS" ));
		}
	else
		{
		aLog->Log( _L( "Do cancel == FAIL" ));
		}
    // Case was executed
    return result;
    }

// -----------------------------------------------------------------------------
// TestQueueL
// Add an Event to the Log Engine
// -----------------------------------------------------------------------------
//
LOCAL_C TInt TestQueueL( CStifLogger* aLog ,CLogClient& aClient )
    {
    aLog->Log(_L("---------------------------------------------"));
    aLog->Log( _L("Calling Queue()") );
       
  	CLogEvent* event = CLogEvent::NewL();
	CleanupStack::PushL(event);
	
	CMyLogActive* active = new(ELeave) CMyLogActive;
	CleanupStack::PushL(active);
	
	event->SetEventType(KTestEventUid1);
	event->SetRemoteParty(KTestRemoteParty1);
	event->SetDirection(KTestDirection1);
	event->SetDurationType(KTestDurationType1);
	event->SetDuration(KTestDuration1);
	event->SetStatus(KTestStatus1);
	event->SetSubject(KTestSubject1);
	event->SetNumber(KTestNumber1);
	event->SetContact(KTestContact1);
	event->SetDataL(KTestData1);
	event->SetFlags(KTestFlags1);
		//
	active->StartL();
	aClient.AddEvent(*event, active->iStatus);
	active->Queue(active->iStatus);
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();				
	CleanupStack::PopAndDestroy(2);
	
	if( result == KErrNone )
		{
	   	aLog->Log( _L("Queue() completed"));
		aLog->Log( _L("Queue successfully done") );
		aLog->Log( _L( "Queue == PASS" ));
		}
	else
		{
		aLog->Log( _L( "Queue == FAIL" ));
		}
    // Case was executed
    return result;
    }


 // -----------------------------------------------------------------------------
// CBCLogEngineTest::TestNotifyChangeL
// Requests notification of changes to the Log Engine database. 
// This is an asynchronous request
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestNotifyChangeL( TTestResult& aResult )
   {
    iLog->Log(_L("---------------------------------------------"));
    _LIT( KNotifyChange, "Calling NotifyChange()" );
    iLog->Log( KNotifyChange );
	
	TTimeIntervalMicroSeconds32 delay(5000);
	CActiveLogEngine* active = new(ELeave) CActiveLogEngine;
	CleanupStack::PushL(active);
	
	active->StartL();
	//IMPORT_C void NotifyChange(TTimeIntervalMicroSeconds32 aDelay, TRequestStatus& aStatus);
	iLogClient->NotifyChange( delay, active->iStatus );
	CActiveScheduler::Start();
	
	TInt result = active->iStatus.Int();
	CleanupStack::PopAndDestroy();					
	if(result == KErrNone)
		{
		iLog->Log( _L("NotifyChange() completed") );
		iLog->Log( _L("Change notification successfully received" ) );
		iLog->Log( _L( "Notify change == PASS" ) );
		}
	else
		{
		iLog->Log( _L( "Notify change == FAIL" ) );
		}
	
	CConsoleBase* console = Create_ConsoleL(_L("NotifyChange"));	
	Print(console, result, _L("NotifyChange") );
	Remove_Console( console );
	return result;
   }
  
// -----------------------------------------------------------------------------
// CBCLogEngineTest::TestNotifyChangeCancelL
// Cancels any outstanding notification request for changes to Log Engine database
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestNotifyChangeCancelL( TTestResult& aResult )
   {
    iLog->Log(_L("---------------------------------------------"));
   	_LIT( KNotifyChangeCancel, "Calling NotifyChangeCancel()" );
    iLog->Log( KNotifyChangeCancel );
	TInt result = KErrNone;
	
	//IMPORT_C void NotifyChangeCancel();
	iLogClient->NotifyChangeCancel();
	
	iLog->Log( _L("NotifyChangeCancel() completed") );
	iLog->Log( _L( "Notify change cancel == PASS" ) );
	
	CConsoleBase* console = Create_ConsoleL(_L("NotifyChangeCancel"));	
	Print(console, result, _L("NotifyChangeCancel") );
	Remove_Console( console );
	return result;
   }
   
// -----------------------------------------------------------------------------
// CBCLogEngineTest::TestLogClientL
// Log Engine implementation
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestLogClientL( TTestResult& aResult )
	{
	_LIT( KLogClient, "Calling LogClient" );
    iLog->Log( KLogClient );
    
    TInt result = KErrNone;
//Notify Change :: Implemented seperately
//Notify Change Cancel

	CConsoleBase* console = Create_ConsoleL(_L("CLogClient"));
//Add Event Type
	result = TestAddEventTypeL( iLog, *iLogClient );
	Print(console, result, _L("AddEventType") );
	
//Add Event    
    TInt eventId;
    result = TestAddEventL( iLog, *iLogClient, eventId );
	Print(console, result, _L("AddEvent") );
	
//Change Event		
    result = TestChangeEventL( iLog, *iLogClient, eventId );
    Print(console, result, _L("ChangeEvent") );
    
 //Get Event	
    result = TestGetEventL( iLog, *iLogClient, eventId );
	Print(console, result, _L("GetEvent") );
	
//Change Event Type		
    result = TestChangeEventTypeL( iLog, *iLogClient );
    Print(console, result, _L("ChangeEventType") );
    
//Get Event Type
	result = TestGetEventTypeL( iLog, *iLogClient );
	Print(console, result, _L("GetEventType") );
		
//Delete Event
   	result = TestDeleteEventL( iLog, *iLogClient, eventId );
	Print(console, result, _L("DeleteEvent") );
	
//Delete Event Type
   	result = TestDeleteEventTypeL( iLog, *iLogClient );
	Print(console, result, _L("DeleteEventType") );
	
//Clear Log( TTime )
 	result = TestClearLogTimeL( iLog, *iLogClient );
	Print(console, result, _L("ClearLog(TTime)") );
	
//Clear Log( Event list )
 	result = TestClearLogEventListL( iLog, *iLogClient );
	Print(console, result, _L("ClearLog(List)") );
	
//Change Config
 	result = TestChangeConfigL( iLog, *iLogClient );
	Print(console, result, _L("ChangeConfig") );
		
//Get Config
	result = TestGetConfigL( iLog, *iLogClient );
	Print(console, result, _L("GetConfig") );
	
//Get string
 	result = TestGetString( iLog, *iLogClient );
	Print(console, result, _L("GetString") );
	
//Set Global Change Observer
	result = TestSetGlobalChangeObserverL( iLog, *iLogClient );
	Print(console, result, _L("SetGlobalChangeObserverL") );
	
//#ifdef SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM		
//Clear Log( TTime, TSimId, TRequestStatus )
 	result = TestClearLogTimeSimIdL( iLog, *iLogClient );
	Print(console, result, _L("ClearLogTTimeSimIdL") );
	
//Clear Log( TInt, TSimId, TRequestStatus )
 	result = TestClearLogIntSimIdL( iLog, *iLogClient );
	Print(console, result, _L("ClearLogTTimeIntSimIdL") );
//#endif //SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM		

//construction CLogClient
//Destruction CLogClient	
	Remove_Console( console );
	return result;
	}

// -----------------------------------------------------------------------------
// CBCLogEngineTest::TestLogBaseL
// Base class for the log engine implementation.
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestLogBaseL( TTestResult& aResult )
	{
	iLog->Log( _L("Calling LogBase") );
    
    TInt result = KErrNone;
    CConsoleBase* console = Create_ConsoleL(_L("CLogEventType"));
//AddEvent -- Wrapper
	TInt eventId;
	result = TestAddEventL( iLog, *iLogWrapper, eventId );
	Print(console, result, _L("AddEvent") );
	
//Change Event	-- Wrapper	
    result = TestChangeEventL( iLog, *iLogWrapper, eventId );
	Print(console, result, _L("ChangeEvent") );
	
//Get Event	-- Wrapper
    result = TestGetEventL( iLog, *iLogWrapper,eventId );
	Print(console, result, _L("GetEvent") );
	
//Delete Event
   	result = TestDeleteEventL( iLog, *iLogWrapper, eventId );
	Print(console, result, _L("DeleteEvent") );
		
//Get string
	result = TestGetString( iLog, *iLogWrapper );
	Print(console, result, _L("GetString") );
	
//Load Resources
/*	CMyLogClient* myClient = new(ELeave) CMyLogClient();
	CleanupStack::PushL( myClient );
	
	result = TestLoadResourcesL( iLog, *myClient );
	Print(console, result, _L("LoadResources") );
		
//Get Resource File
	result = TestResourceFile( iLog, *myClient );
	Print(console, result, _L("ResourceFile") );
	
	CleanupStack::PopAndDestroy();
*/	
//construction CLogBase
//destruction CLogBase
	Remove_Console( console );
	return result;	
	}
// -----------------------------------------------------------------------------
// CBCLogEngineTest::TestLogEventL
// Encapsulates the details of an event.
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestLogEventL( TTestResult& aResult )
	{
	_LIT( KAddEvent, "Calling LogEvent" );
    iLog->Log( KAddEvent );
    
    TInt result = KErrNone;
    CConsoleBase* console = Create_ConsoleL(_L("CLogEventType"));
//Copy Event
    result = TestCopyL( iLog, *iLogEvent );
	Print(console, result, _L("CopyL") );

//SetContact
	result = TestSetContact( iLog, *iLogEvent );
	Print(console, result, _L("SetContact") );
	
//GetContact
	result = TestGetContact( iLog, *iLogEvent );
	Print(console, result, _L("Contact") );
	
//SetId
 	result = TestSetId( iLog, *iLogEvent );
	Print(console, result, _L("SetId") );

//Id
	result = TestGetId( iLog, *iLogEvent );
	Print(console, result, _L("Id") );

//SetEventType
    result = TestSetEventType( iLog, *iLogEvent );
	Print(console, result, _L("SetEventType") );
	
//Event Type
	result = TestEventType( iLog, *iLogEvent );
	Print(console, result, _L("EventType") );
			
//Set Remote Party
    result = TestSetRemoteParty( iLog, *iLogEvent );
	Print(console, result, _L("SetRemoteParty") );
	
//Remote Party
	result = TestGetRemoteParty( iLog, *iLogEvent );
	Print(console, result, _L("RemoteParty") );
	
//Set Time
	result = TestSetTime( iLog, *iLogEvent );
	Print(console, result, _L("SetTime") );
		
//Get Time
 	result = TestGetTimeL( iLog, *iLogEvent );
	Print(console, result, _L("Time") );
	
//Set Duration Type
 	result = TestSetDurationType( iLog, *iLogEvent );
	Print(console, result, _L("SetDurationType") );
	
//Get Duration Type
	result = TestGetDurationType( iLog, *iLogEvent );
	Print(console, result, _L("DurationType") );

//set Status
	result = TestSetStatus( iLog, *iLogEvent );
	Print(console, result, _L("SetStatus") );
		
//Status
	result = TestGetStatus( iLog, *iLogEvent );
	Print(console, result, _L("Status") );
		
//SetDirection
	result = TestSetDirection( iLog, *iLogEvent );
	Print(console, result, _L("SetDirection") );
	
//Direction
	result = TestGetDirection( iLog, *iLogEvent );
	Print(console, result, _L("Direction") );
		
//SetDuration
 	result = TestSetDuration( iLog, *iLogEvent );
	Print(console, result, _L("SetDuration") );
	
//GetDuration
	result = TestGetDuration( iLog, *iLogEvent );
	Print(console, result, _L("Duration") );
	
//SetSubject
	result = TestSetSubject( iLog, *iLogEvent );
	Print(console, result, _L("SetSubject") );
	
//Subject	
	result = TestGetSubject( iLog, *iLogEvent );
	Print(console, result, _L("Subject") );
		
//SetNumber
	result = TestSetNumber( iLog, *iLogEvent );
	Print(console, result, _L("SetNumber") );

//Number
    result = TestGetNumber( iLog, *iLogEvent);
	Print(console, result, _L("Number") );
	
//SetLink
	result = TestSetLink( iLog, *iLogEvent );
	Print(console, result, _L("SetLink") );
		
//Link
	result = TestGetLink( iLog, *iLogEvent );
	Print(console, result, _L("Link") );
	
//SetDescription
    result = TestSetDescription( iLog, *iLogEvent );
	Print(console, result, _L("SetDescription") );
	
//Description
  	result = TestGetDescription( iLog, *iLogEvent );
	Print(console, result, _L("Description") );
	
//SetFlags
	iLogEvent->ClearFlags(KLogFlagsMask);
    result = TestSetFlags( iLog, *iLogEvent );
	Print(console, result, _L("SetFlags") );
		
//Flags
	result = TestGetFlags( iLog, *iLogEvent );
	Print(console, result, _L("Flags") );
	
//ClearFlags
    result = TestClearFlags( iLog, *iLogEvent );
	Print(console, result, _L("ClearFlags") );
	
//SetData#1
    result = TestSetDataTdesL( iLog, *iLogEvent );
	Print(console, result, _L("SetData(Tdes)") );
	
//Data	
	result = TestGetData( iLog, *iLogEvent );
	Print(console, result, _L("DataL") );
		
//SetData#2
    result = TestSetDataStreamL( iLog, *iLogEvent );
    Print(console, result, _L("SetData(RReadStream)") );
		
//Externalise
	result = TestExternalizeL( iLog, *iLogEvent );
	Print(console, result, _L("CLogEvent::Externalize") );

 //Internalize
	result = TestInternalizeL( iLog, *iLogEvent );
	Print(console, result, _L("CLogEvent::Internalize") );

//#ifdef SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM

// Set SimId
	result = TestLogEventSetSimId( iLog, *iLogEvent );
	Print(console, result, _L("LogEventSetSimId") );

//#endif //SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM

//Construction CLogEvent
 //destruction CLogEvent
 	Remove_Console( console );
	return result;
	}
	
// -----------------------------------------------------------------------------
// CBCLogEngineTest::TestLogEventTypeL
// Encapsulates the details of an event type.
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestLogEventTypeL( TTestResult& aResult )
	{
	iLog->Log( _L("Calling LogEventType") );
    TInt result = KErrNone;
    
    CConsoleBase* console = Create_ConsoleL(_L("CLogEventType"));
// SetLoggingEnabled
	result = TestSetLoggingEnabled( iLog, *iLogType );
	Print(console, result, _L("SetLoggingEnabled"));
	
// LoggingEnabled
	result = TestLoggingEnabled( iLog, *iLogType );
	Print(console, result, _L("LoggingEnabled"));
	
// SetDescription
	result = TestSetDescription( iLog, *iLogType );
	Print(console, result, _L("SetDescription") );
	
// GetDescription
	result = TestGetDescription( iLog, *iLogType );
	Print(console, result, _L("Description") );

// Copy
	result = TestCopyL( iLog, *iLogType );
	Print(console, result, _L("CopyL") );

// SetUid
	result = TestSetUid( iLog, *iLogType );
	Print(console, result, _L("SetUid") );
	
// GetUid
	result = TestGetUid( iLog, *iLogType );
	Print(console, result, _L("Uid") );
	
// Construction CLogEventType
// destruction CLogEventType
	Remove_Console( console );
	return result;	
	}
	
// -----------------------------------------------------------------------------
// TestLogFilterL
// Specifies the conditions that events must satisfy to appear in a view
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestLogFilterL( TTestResult& aResult )
	{
	iLog->Log( _L("Calling LogFilter") );
    
    TInt result = KErrNone;
    CConsoleBase* console = Create_ConsoleL(_L("CLogFilter"));
// Set Event Type
	result = TestSetEventType( iLog, *iLogFilter );
	Print(console, result, _L("SetEventType") );
	
// Get Event Type
	result = TestEventType( iLog, *iLogFilter );
	Print(console, result, _L("EventType") );
	
// Set Flags
    result = TestSetFlags( iLog, *iLogFilter );
    Print(console, result, _L("SetFlags") );
    
// Get Flags
	result = TestGetFlags( iLog, *iLogFilter );
	Print(console, result, _L("Flags") );
	
// Set Contacts
	result = TestSetContact( iLog, *iLogFilter );
	Print(console, result, _L("SetEventType") );
	
// Set Status
	result = TestSetStatus( iLog, *iLogFilter );
	Print(console, result, _L("SetContact") );
	
// Set Direction
	result = TestSetDirection( iLog, *iLogFilter );
	Print(console, result, _L("SetDirection") );
	
// SetDuration Type
	result = TestSetDurationType( iLog, *iLogFilter );
	Print(console, result, _L("SetDurationType") );
	
// Clear Flags
	result = TestClearFlags( iLog, *iLogFilter );
	Print(console, result, _L("ClearFlags") );
	
// Get Contacts
	result = TestGetContact( iLog, *iLogFilter );
	Print(console, result, _L("Contact") );
	
// Copy
	result = TestCopyL( iLog, *iLogFilter );
	Print(console, result, _L("CopyL") );
	
// Get Direction
	result = TestGetDirection( iLog, *iLogFilter );
	Print(console, result, _L("Direction") );
	
// Get Duration Type
	result = TestGetDurationType( iLog, *iLogFilter );
	Print(console, result, _L("DurationType") );
	
// Set End time
	result = TestSetEndTime( iLog, *iLogFilter );
	Print(console, result, _L("SetEndTime") );
	
// Set Start Time
	result = TestSetStartTime( iLog, *iLogFilter );
	Print(console, result, _L("SetStartTime") );
	
// Get Start Time
	result = TestStartTime( iLog, *iLogFilter );
	Print(console, result, _L("StartTime") );
	
// Get End Time
	result = TestEndTime( iLog, *iLogFilter );
	Print(console, result, _L("EndTime") );
	
// Set Null Fields
	result = TestSetNullFields( iLog, *iLogFilter );
	Print(console, result, _L("SetNullFields") );
	
// Get Null Fields
	result = TestGetNullFields( iLog, *iLogFilter );
	Print(console, result, _L("NullFields") );
	
// Set Number
	result = TestSetNumber( iLog, *iLogFilter );
	Print(console, result, _L("SetNumber") );
	
// Get Number
	result = TestGetNumber( iLog, *iLogFilter );
	Print(console, result, _L("Number") );
	
// Set Remote Party
	result = TestSetRemoteParty( iLog, *iLogFilter );
	Print(console, result, _L("SetRemoteParty") );
	
// Get Remote Party
	result = TestGetRemoteParty( iLog, *iLogFilter );
	Print(console, result, _L("RemoteParty") );
	
// Get status
    result = TestGetStatus( iLog, *iLogFilter );
    Print(console, result, _L("Status") );

//#ifdef SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM

// Set SimId
	result = TestLogFilterSetSimId( iLog, *iLogFilter );
	Print(console, result, _L("LogFilterSetSimId") );

//#endif //SYMBIAN_ENABLE_EVENTLOGGER_DUALSIM
	    
// construction CLogFilter
// Destruction CLogFilter
	Remove_Console( console );
	return result;
	}

// -----------------------------------------------------------------------------
// CBCLogEngineTest::TestLogWrapperL
// 
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestLogWrapperL( TTestResult& aResult )
	{
	_LIT( KLogWrapper, "Calling LogWrapper" );
    	iLog->Log( KLogWrapper);
    
   	TInt result = KErrNone;
   	CConsoleBase* console = Create_ConsoleL(_L("CLogWrapper"));
// Get Client Available
	result = TestGetClientAvailable( iLog, *iLogWrapper );
	Print(console, result, _L("ClientAvailable") );
	
// Get Log
	result = TestGetLogL( iLog, *iLogWrapper );
	Print(console, result, _L("Log") );
	
// Construction 
// Destruction
	Remove_Console( console );
	return result;	
	}

// -----------------------------------------------------------------------------
// CBCLogEngineTest::TestLogViewRecentL
// A view on a recent event list
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestLogViewRecentL( TTestResult& aResult )
	{
	_LIT( KViewRecent, "Calling LogViewRecent" );
    iLog->Log( KViewRecent );
    
    TInt result = KErrNone;
    CConsoleBase* console = Create_ConsoleL(_L("CLogViewRecent"));
// Set recent list (TLogRecentList)
	result = TestSetRecentListL( iLog, *iLogViewRecent, *iLogClient );
	Print(console, result, _L("SetRecentListL(TLogRecentList)") );
	
// Set recent list (TLogRecentList, CLogFilter) 
	result = TestSetRecentListFilterL( iLog, *iLogViewRecent, *iLogClient );
	Print(console, result, _L("SetRecentListL(TLogRecentList, CLogFilter)") );
	
// Set recent list (TLogRecentList, CLogFilterList) 
   	result = TestSetRecentListFilterListL( iLog, *iLogViewRecent, *iLogClient );
	Print(console, result, _L("SetRecentListL(TLogRecentList, CLogFilterList)") );
	
// Get duplicates (CLogViewDuplicate) 
	result = TestGetDuplicatesL( iLog, *iLogViewRecent, *iLogClient );
	Print(console, result, _L("SetRecentListL(TLogRecentList, CLogFilterList)") );
	
// Get duplicates (CLogViewDuplicate,CLogFilter) 
	result = TestGetDuplicatesFilterL( iLog, *iLogViewRecent, *iLogClient );
	Print(console, result, _L("SetRecentListL(TLogRecentList, CLogFilterList)") );
	
// Get duplicates (CLogViewDuplicate,CLogFilterList) 
	result = TestGetDuplicatesFilterListL( iLog, *iLogViewRecent, *iLogClient );
	Print(console, result, _L("SetRecentListL(TLogRecentList, CLogFilterList)") );
	
// Clear Duplicates
	result = TestClearDuplicatesL( iLog, *iLogViewRecent, *iLogClient );
	Print(console, result, _L("ClearDuplicates") );
	
// Get recent list 
	result = TestGetRecentList( iLog, *iLogViewRecent );
	Print(console, result, _L("RecentList") );
	
// Remove (TLogId) 
	result = TestRemoveOnLogIdL( iLog, *iLogViewRecent, *iLogClient);
	Print(console, result, _L("Remove(TLogId)") );
	
// Remove (TRequestStatus) 
	result = TestRemoveL( iLog, *iLogViewRecent, *iLogClient);
	Print(console, result, _L("Remove(TRequestStatus)") );
	
// Construction
// Construction (MLogViewChangeObserver) 
// Destruction
	Remove_Console( console );
	return result;
	}

// -----------------------------------------------------------------------------
// CBCLogEngineTest::TestLogViewEventL
// A view on the event log
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestLogViewEventL( TTestResult& aResult )
	{
	_LIT( KViewEvent, "Calling LogViewEvent" );
    iLog->Log( KViewEvent );
    
    TInt result = KErrNone;
    CConsoleBase* console = Create_ConsoleL(_L("CLogViewEvent"));
 
// Set filter (CLogFilter) 
	result = TestSetFilterL( iLog, *iLogViewEvent );
	Print(console, result, _L("SetFilter(CLogFilter)") );
	
// Set filter (CLogFilterList) 
	result = TestSetFilterL( iLog, *iLogViewEvent, *iLogFilterList );
	Print(console, result, _L("SetFilter(CLogFilterList)") );
	
// Set filter parse filter by filter 
	result = TestSetFilterParseFilterByFilterL( iLog, *iLogViewEvent, *iLogClient );
	Print(console, result, _L("SetFilterParseFilterByFilter") );
	
// Construction 
// Construction (MLogViewChangeObserver) 
// Destruction
// Get count 
	result = TestGetCountL( iLog, *iLogViewEvent );
	Print(console, result, _L("CLogView::CountL") );
	
// Get event 
	result = TestGetEventL( iLog, *iLogViewEvent );
	Print(console, result, _L("CLogView::Event") );
	
// First
	result = TestFirstL( iLog, *iLogViewEvent );
	Print(console, result, _L("CLogView::First") );
	
// Next
	result = TestNextL( iLog, *iLogViewEvent );
	Print(console, result, _L("CLogView::Next") );
	
// Previous
	result = TestPreviousL( iLog, *iLogViewEvent );
	Print(console, result, _L("CLogView::Previous") );
	
// Last
	result = TestLastL( iLog, *iLogViewEvent );
	Print(console, result, _L("CLogView::Last") );
	
// SetFlags
/*	result = TestSetFlags( iLog, *iLogViewEvent );
	Print(console, result, _L("CLogView::SetFlags") );
*/
// DoCancel
	result = TestDoCancelL( iLog, *iLogViewEvent );
	Print(console, result, _L("CLogView::DoCancel") );
	
// Destruction
	Remove_Console( console );
	return result;	
	}

// -----------------------------------------------------------------------------
// CBCLogEngineTest::TestLogFilterListL
// A set of event view filters
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestLogFilterListL( TTestResult& aResult )
	{
	_LIT( KFilterList, "Calling LogFilterList" );
    iLog->Log( KFilterList );
    
    TInt result = KErrNone;
    CConsoleBase* console = Create_ConsoleL(_L("CLogFilterList"));
// CopyL
	result = TestCopyL( iLog, *iLogFilterList );
	Print(console, result, _L("CopyL") );
	
// CopyLC
	result = TestCopyLC( iLog, *iLogFilterList );
	Print(console, result, _L("CopyLC") );

// Construction
	Remove_Console( console );
	return result;
	}	

// -----------------------------------------------------------------------------
// CBCLogEngineTest::TestLogViewDuplicateL
// A view of events that are duplicates of an event in a view of recent events
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestLogViewDuplicateL( TTestResult& aResult )
	{
	_LIT( KViewDuplicate, "Calling LogViewDuplicate" );
    iLog->Log( KViewDuplicate );
    
    TInt result = KErrNone;	
    CConsoleBase* console = Create_ConsoleL(_L("CLogViewDuplicate"));
// Remove (TLogId)
	result = TestRemoveOnLogIdL( iLog, *iLogViewDuplicate, *iLogClient );
	Print(console, result, _L("Remove(TLogId)") );
	
// Remove (TRequestStatus) 
	result = TestRemoveL( iLog, *iLogViewDuplicate, *iLogClient );
	Print(console, result, _L("Remove(TRequestStatus) ") );
	
// Source
	result = TestSource( iLog, *iLogViewDuplicate);
	Print(console, result, _L("Source") );
	
// Construction
// Construction (MLogViewChangeObserver) 
// Destruction
	Remove_Console( console );
	return result;
	}

// -----------------------------------------------------------------------------
// CBCLogEngineTest::TestLogActiveL
// Common active object behaviour
// -----------------------------------------------------------------------------
//
TInt CBCLogEngineTest::TestLogActiveL( TTestResult& aResult )
	{
	_LIT( KLogActive, "Calling LogActive" );
    iLog->Log( KLogActive );
    
    TInt result = KErrNone;	
    CConsoleBase* console = Create_ConsoleL(_L("CLogActive"));
// Complete
	result = TestCompleteL( iLog, *iLogClient);
	Print(console, result, _L("CLogActive::Complete") );
	
// DoCancel
	result = TestDoCancelL( iLog, *iLogClient);
	Print(console, result, _L("CLogActive::DoCancel") );
	
// Queue
	result = TestQueueL( iLog, *iLogClient);
	Print(console, result, _L("CLogActive::Queue") );
	
// Construction
// Destruction
	Remove_Console( console );
	return result;
	}
// -----------------------------------------------------------------------------
// ========================== OTHER EXPORTED FUNCTIONS =========================
//  End of File