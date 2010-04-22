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
* Description:  
*
*/



// INCLUDE FILES
#include <e32math.h>
#include <s32file.h>
#include "IsvTelephonyTest.h"
#include "IsvTelephonyTestEngine.h"
#include "IsvTelephonyTestParser.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::Case
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
const TCaseInfo CIsvTelephonyTest::Case ( 
    const TInt aCaseNumber ) const 
     {
    /**
    * To add new test cases, implement new test case function and add new 
    * line to KCases array specify the name of the case and the function 
    * doing the test case
    * In practice, do following
    * 1) Make copy of existing test case function and change its name
    *    and functionality. Note that the function must be added to 
    *    IsvTelephonyTest.cpp file and to IsvTelephonyTest.h 
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
        
        // Sets and unsets cancellation of async. function tests with 
        // CancelAsync()         
        ENTRY( "SetCancelAsyncs", &CIsvTelephonyTest::SetCancelAsyncs ),		        
        ENTRY( "ClearCancelAsyncs", &CIsvTelephonyTest::ClearCancelAsyncs ),
        // Tests for CTelephony functions 
        ENTRY( "GetVersion", &CIsvTelephonyTest::TestGetVersion ), 
        ENTRY( "GetPhoneId", &CIsvTelephonyTest::TestGetPhoneId ), 
        ENTRY( "GetSubscriberId", &CIsvTelephonyTest::TestGetSubscriberId ),
        ENTRY( "GetFlightMode", &CIsvTelephonyTest::TestGetFlightMode ),
        ENTRY( "GetIndicator", &CIsvTelephonyTest::TestGetIndicator ), 
        ENTRY( "GetBatteryInfo", &CIsvTelephonyTest::TestGetBatteryInfo ),
        ENTRY( "GetSignalStrength", &CIsvTelephonyTest::TestGetSignalStrength ),
        ENTRY( "GetLockInfo", &CIsvTelephonyTest::TestGetLockInfo ),                
        ENTRY( "GetLineStatus", &CIsvTelephonyTest::TestGetLineStatus ),             
        ENTRY( "GetNetworkRegistrationStatus", &CIsvTelephonyTest::TestGetNetworkRegistrationStatus ),                
        ENTRY( "GetCurrentNetworkInfo", &CIsvTelephonyTest::TestGetCurrentNetworkInfo ),
        ENTRY( "GetCurrentNetworkName", &CIsvTelephonyTest::TestGetCurrentNetworkName ),
        ENTRY( "GetOperatorName", &CIsvTelephonyTest::TestGetOperatorName ),
        ENTRY( "GetCallForwardingStatus", &CIsvTelephonyTest::TestGetCallForwardingStatus ),
        ENTRY( "GetCallBarringStatus", &CIsvTelephonyTest::TestGetCallBarringStatus ),        
        ENTRY( "GetCallWaitingStatus", &CIsvTelephonyTest::TestGetCallWaitingStatus ),
        ENTRY( "GetIdentityServiceStatus", &CIsvTelephonyTest::TestGetIdentityServiceStatus ),
        // Tests that require tester to answer MO calls 
        ENTRY( "GetCallInfo", &CIsvTelephonyTest::TestGetCallInfoL ),                     
        ENTRY( "DialNewCall", &CIsvTelephonyTest::TestDialNewCall ),
        ENTRY( "SendDTMFTones", &CIsvTelephonyTest::TestSendDTMFTones ),    
        ENTRY( "GetCallDynamicCaps", &CIsvTelephonyTest::TestGetCallDynamicCaps ),   
        ENTRY( "GetCallStatus", &CIsvTelephonyTest::TestGetCallStatus ),
        ENTRY( "Hold", &CIsvTelephonyTest::TestHold ),
        ENTRY( "Resume", &CIsvTelephonyTest::TestResume ),                                                                                                      
		ENTRY( "Swap", &CIsvTelephonyTest::TestSwap ),
		ENTRY( "Hangup", &CIsvTelephonyTest::TestHangup ),
		// Tests that require tester to create MT call 
		ENTRY( "AnswerIncomingCall", &CIsvTelephonyTest::TestAnswerIncomingCall ),	
		ENTRY( "NotifyChange - VoiceLineStatus", &CIsvTelephonyTest::TestNotifyChangeVoiceLineStatus ),				
		// Tests for deprecated CTelephony functions
		ENTRY( "FindDeviceStatus", &CIsvTelephonyTest::TestFindDeviceStatus ),
		ENTRY( "EstablishDataCall", &CIsvTelephonyTest::TestEstablishDataCall ),
		ENTRY( "EstablishDataCall - async", &CIsvTelephonyTest::TestEstablishDataCallAsync ),
		ENTRY( "TerminateDataCall", &CIsvTelephonyTest::TestTerminateDataCall ),
		ENTRY( "ReceiveDataCall", &CIsvTelephonyTest::TestReceiveDataCall ),
		ENTRY( "ReceiveDataCall - async", &CIsvTelephonyTest::TestReceiveDataCallAsync ),
		ENTRY( "CancelEstablishDataCall", &CIsvTelephonyTest::TestCancelEstablishDataCall ),
		ENTRY( "CancelReceiveDataCall", &CIsvTelephonyTest::TestCancelReceiveDataCall )
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
// CIsvTelephonyTest::SetCancelAsyncs
// Sets cancellation of async. function tests with 
// CancelAsync()         
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::SetCancelAsyncs( TTestResult& aResult )
	{
 	// Set cancellation of async function tests
 	iTestEngine->SetCancelAsyncs( ETrue ); 

	// Set result for STIF framework
	aResult.SetResult( KErrNone, KSetCancelAsyncs );			
	
	return KErrNone; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::ClearCancelAsyncs
// Clears cancellation of async. function tests
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::ClearCancelAsyncs( TTestResult& aResult )
	{
 	// Reset cancellation of async function tests
 	iTestEngine->SetCancelAsyncs( EFalse ); 

	// Set result for STIF framework
	aResult.SetResult( KErrNone, KClearCancelAsyncs );			
	
	return KErrNone; 
	}
		
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetVersion
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetVersion( TTestResult& aResult )
	{
    TInt result;	
	TVersion version;
	
 	// Execute test  		
 	result = iTestEngine->TestGetVersion( version );	 		
	// Parse result data
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetVersion( version ); 
 		}
	// Set result for STIF framework
	aResult.SetResult( result, KGetVersion );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetPhoneId
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetPhoneId( TTestResult& aResult )
	{
    TInt result;
	CTelephony::TPhoneIdV1 phoneId;
	
 	// Execute test  		
 	result = iTestEngine->TestGetPhoneId( phoneId );	 			
	// Parse result data
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetPhoneId( phoneId ); 
 		}
	// Set result for STIF framework
	aResult.SetResult( result, KGetPhoneId );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetSubscriberId
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetSubscriberId( TTestResult& aResult )
	{
    TInt result;
	CTelephony::TSubscriberIdV1 subscriberId;
 	
 	// Execute test  		
 	result = iTestEngine->TestGetSubscriberId( subscriberId ); 
	// Parse result data 
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetSubscriberId( subscriberId ); 
 		}
	// Set result for STIF framework
	aResult.SetResult( result, KGetSubscriberId );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetFlightMode
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetFlightMode( TTestResult& aResult )
	{
    TInt result;
	CTelephony::TFlightModeV1 flightMode;
 	
 	// Execute test  		
 	result = iTestEngine->TestGetFlightMode( flightMode ); 
	// Parse result data 
 	if( KErrNone == result )
 		{	
		iTestParser->ParseGetFlightMode( flightMode ); 
 		}
	// Set result for STIF framework
	aResult.SetResult( result, KGetFlightMode );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetIndicator
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetIndicator( TTestResult& aResult )
	{
    TInt result;
	CTelephony::TIndicatorV1 indicator;
 	
 	// Execute test  		
 	result = iTestEngine->TestGetIndicator( indicator ); 
	// Parse result data 
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetIndicator( indicator ); 
 		}
	// Set result for STIF framework
	aResult.SetResult( result, KGetIndicator );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetBatteryInfo
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetBatteryInfo( TTestResult& aResult )
	{
    TInt result;
	CTelephony::TBatteryInfoV1 batteryInfo;
 	
 	// Execute test  		
 	result = iTestEngine->TestGetBatteryInfo( batteryInfo ); 
	// Parse result data 
	if( KErrNone == result )
 		{
		iTestParser->ParseGetBatteryInfo( batteryInfo ); 
 		}
	// Set result for STIF framework
	aResult.SetResult( result, KGetBatteryInfo );			
		
	return result; 
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestSignalStrength
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetSignalStrength( TTestResult& aResult )
	{
    TInt result;
	CTelephony::TSignalStrengthV1 signalStrength;
 	
 	// Execute test  		
 	result = iTestEngine->TestGetSignalStrength( signalStrength ); 
	// Parse result data 
	if( KErrNone == result )
 		{
		iTestParser->ParseGetSignalStrength( signalStrength ); 
 		}
	// Set result for STIF framework
	aResult.SetResult( result, KGetSignalStrength );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetLockInfo
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetLockInfo( TTestResult& aResult )
	{
    TInt result;
    CTelephony::TIccLock lock; 
	CTelephony::TIccLockInfoV1 lockInfo;
 	
 	// Test for TIccLock::ELockPin1
 	lock = CTelephony::ELockPin1; 
 	result = iTestEngine->TestGetLockInfo( lock, lockInfo ); 
 	if( KErrNone == result )
		{
		iTestParser->ParseGetLockInfo( lock, lockInfo ); 
		} 	
 	
 	// Test for TIccLock::ELockPin2
 	// Lock Pin 2 query qurrenly not supported 

	// Set result for STIF framework
	aResult.SetResult( result, KGetLockInfo );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestSendDTMFTones
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestSendDTMFTones( TTestResult& aResult )
	{
	TInt result; 

	// Initialise variables with tester ini file values
	iCallParams.iIdRestrict = iIdRestrict;	
	
	// Precondition: setup ongoing call  
 	result = iTestEngine->TestDialNewCall(  		
 		iCallParams,
 		iTelNumber1,
 		iCallId1,
 		iPhoneLine );
 	// Execute test  
 	if( KErrNone == result )		
 		{
     	// Inform tester the DTMF Tones to be sent
     	PrintMessage( KSendingFollowingDTMFTones() ); 
     	PrintMessage( iDTMFTones ); 		  		 	     	
 		result = iTestEngine->TestSendDTMFTones( iDTMFTones ); 	
 		} 		 	
	// Restore initial state: end call  		
	iTestEngine->TestHangup( iCallId1 );	  		 				
	// Set result for STIF framework
	aResult.SetResult( result, KSendDTMFTones );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetLineStatus
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetLineStatus( TTestResult& aResult )
	{
    TInt result;
 	
 	// Execute test  		
 	result = iTestEngine->TestGetLineStatus( iPhoneLine, iCallStatus ); 
	// Parse result data 
	if( KErrNone == result )
		{
		iTestParser->ParseGetLineStatus( iPhoneLine, iCallStatus ); 	
		}
	// Set result for STIF framework
	aResult.SetResult( result, KGetLineStatus );			
		
	return result; 
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetCallInfo	
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetCallInfoL( TTestResult& aResult )
	{
	TInt result; 
	
	// Initialise with tester ini file values
	iCallParams.iIdRestrict = iIdRestrict;
	iCallSelection.iLine = iPhoneLine; 
	
	// Precondition: setup ongoing call  
 	result = iTestEngine->TestDialNewCall(  		
 		iCallParams,
 		iTelNumber1,
 		iCallId1,
 		iPhoneLine );	  		 	
 	// Execute test  
 	if( KErrNone == result )		
 		{
 		result = iTestEngine->TestGetCallInfo( 
 			iCallSelection, 
 			iCallInfo, 
 			iRemotePartyInfo ); 	
 		} 	
	// Parse result data 
	if( KErrNone == result )
		{
		iTestParser->ParseGetCallInfoL( 
			iCallSelection,
			iCallInfo, 
			iRemotePartyInfo ); 	
		} 			 	
	// Restore initial state: end call  		
	iTestEngine->TestHangup( iCallId1 );	  		 				
	// Set result for STIF framework
	aResult.SetResult( result, KGetCallInfo );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetNetworkRegistrationStatus
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetNetworkRegistrationStatus( TTestResult& aResult )
	{
    TInt result;
 	CTelephony::TNetworkRegistrationV1 networkRegistration; 
 	 	
 	// Execute test  		
 	result = iTestEngine->TestGetNetworkRegistrationStatus( networkRegistration );	 		
 	// Parse result data 
 	if( KErrNone == result )
 		{
 		iTestParser->ParseGetNetworkRegistrationStatus( networkRegistration ); 	
 		}	
	// Set result for STIF framework
	aResult.SetResult( result, KGetNetworkRegistrationStatus );			
		
	return result; 
	}
		
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetCurrentNetworkInfo
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetCurrentNetworkInfo( TTestResult& aResult )
	{
    TInt result;
 	CTelephony::TNetworkInfoV1 networkInfo; 
 	 	
 	// Execute test  		
 	result = iTestEngine->TestGetCurrentNetworkInfo( networkInfo );	 		
 	// Parse result data 
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCurrentNetworkInfo( networkInfo ); 
 		}
	// Set result for STIF framework
	aResult.SetResult( result, KGetCurrentNetworkInfo );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetCurrentNetworkName
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetCurrentNetworkName( TTestResult& aResult )
	{
    TInt result;
 	CTelephony::TNetworkNameV1 networkName; 
 	 	
 	// Execute test  		
 	result = iTestEngine->TestGetCurrentNetworkName( networkName );	 		
 	// Parse result data 
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCurrentNetworkName( networkName ); 
 		}
	// Set result for STIF framework
	aResult.SetResult( result, KGetCurrentNetworkName );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetOperatorName
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetOperatorName( TTestResult& aResult )
	{
    TInt result;
 	CTelephony::TOperatorNameV1 operatorName; 
 	 	
 	// Execute test  		
 	result = iTestEngine->TestGetOperatorName( operatorName );	 		
 	// Parse result data 
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetOperatorName( operatorName ); 
 		}
 	else if( KErrNotFound == result )	
 		{
     	PrintMessage( KOperatorNameNotFoundFromSIM() ); 
     	// Suppress KErrNotFound, KErrNotFound is expected if SIM card 
     	// doesn't define the operator name  
     	result = KErrNone; 
 		}
 	
	// Set result for STIF framework
	aResult.SetResult( result, KGetOperatorName );			
		
	return result; 
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetCallForwardingStatus		
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetCallForwardingStatus( TTestResult& aResult )
	{
    TInt result;
 	CTelephony::TCallForwardingCondition callForwardingCondition;  	
 	CTelephony::TCallForwardingSupplServicesV1 callForwardingStatus; 
 	// S60 3.0 SDK documentation: only EVoiceService is supported
 	CTelephony::TServiceGroup serviceGroup( CTelephony::EVoiceService ); 
 	 	
 	// Test for TCallForwardingCondition::ECallForwardingUnconditional
 	callForwardingCondition = CTelephony::ECallForwardingUnconditional;  	 	 	
 	result = iTestEngine->TestGetCallForwardingStatus( 
 		callForwardingCondition,
 		callForwardingStatus,
 		serviceGroup );	 	 	
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCallForwardingStatus( 
		 	callForwardingCondition,
	 		callForwardingStatus,
	 		serviceGroup );
 		}

 	// Test for TCallForwardingCondition::ECallForwardingBusy
 	callForwardingCondition = CTelephony::ECallForwardingBusy;  	 	
 	result = iTestEngine->TestGetCallForwardingStatus( 
 		callForwardingCondition,
 		callForwardingStatus,
 		serviceGroup );	 	 	
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCallForwardingStatus( 
		 	callForwardingCondition,
	 		callForwardingStatus,
	 		serviceGroup );
 		}
 		
 	// Test for TCallForwardingCondition::ECallForwardingNoReply
 	callForwardingCondition = CTelephony::ECallForwardingNoReply;	 	
 	result = iTestEngine->TestGetCallForwardingStatus( 
 		callForwardingCondition,
 		callForwardingStatus,
 		serviceGroup );	 	 	
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCallForwardingStatus( 
		 	callForwardingCondition,
	 		callForwardingStatus,
	 		serviceGroup );
 		}
 		
 	// Test for TCallForwardingCondition::ECallForwardingNotReachable
 	callForwardingCondition = CTelephony::ECallForwardingNotReachable;  	 	
 	result = iTestEngine->TestGetCallForwardingStatus( 
 		callForwardingCondition,
 		callForwardingStatus,
 		serviceGroup );	 	 	
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCallForwardingStatus( 
		 	callForwardingCondition,
	 		callForwardingStatus,
	 		serviceGroup );
 		}
 		
	// Set result for STIF framework
	aResult.SetResult( result, KGetCallForwardingStatus );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetCallBarringStatus
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetCallBarringStatus( TTestResult& aResult )
	{
    TInt result;
 	CTelephony::TCallBarringCondition callBarringCondition;  	
 	CTelephony::TCallBarringSupplServicesV1 callBarringStatus; 
 	// S60 3.0 SDK documentation: only EVoiceService is supported
 	CTelephony::TServiceGroup serviceGroup( CTelephony::EVoiceService ); 
 	
 	// Test for TCallBarringCondition::EBarAllIncoming
 	callBarringCondition = CTelephony::EBarAllIncoming;  	 	 	
 	result = iTestEngine->TestGetCallBarringStatus( 
 		callBarringCondition,
 		callBarringStatus,
 		serviceGroup );	 	 	
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCallBarringStatus( 
		 	callBarringCondition,
	 		callBarringStatus,
	 		serviceGroup );
 		}
 		
 	// Test for TCallBarringCondition::EBarIncomingRoaming
 	callBarringCondition = CTelephony::EBarIncomingRoaming;  	 	 	
 	result = iTestEngine->TestGetCallBarringStatus( 
 		callBarringCondition,
 		callBarringStatus,
 		serviceGroup );	 	 	
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCallBarringStatus( 
		 	callBarringCondition,
	 		callBarringStatus,
	 		serviceGroup );
 		}
 		
 	// Test for TCallBarringCondition::EBarAllOutgoing
 	callBarringCondition = CTelephony::EBarAllOutgoing;  	 	 	
 	result = iTestEngine->TestGetCallBarringStatus( 
 		callBarringCondition,
 		callBarringStatus,
 		serviceGroup );	 	 	
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCallBarringStatus( 
		 	callBarringCondition,
	 		callBarringStatus,
	 		serviceGroup );
 		}
 		
 	// Test for TCallBarringCondition::EBarOutgoingInternational
 	callBarringCondition = CTelephony::EBarOutgoingInternational;  	 	 	
 	result = iTestEngine->TestGetCallBarringStatus( 
 		callBarringCondition,
 		callBarringStatus,
 		serviceGroup );	 	 	
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCallBarringStatus( 
		 	callBarringCondition,
	 		callBarringStatus,
	 		serviceGroup );
 		}
 		
 	// Test for TCallBarringCondition::EBarOutgoingInternationalExHC
 	callBarringCondition = CTelephony::EBarOutgoingInternationalExHC;  	 	 	
 	result = iTestEngine->TestGetCallBarringStatus( 
 		callBarringCondition,
 		callBarringStatus,
 		serviceGroup );	 	 	
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCallBarringStatus( 
		 	callBarringCondition,
	 		callBarringStatus,
	 		serviceGroup );
 		}
 		
	// Set result for STIF framework
	aResult.SetResult( result, KGetCallBarringStatus );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetCallWaitingStatus
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetCallWaitingStatus( TTestResult& aResult )
	{
    TInt result; 	
 	CTelephony::TCallWaitingSupplServicesV1 callWaitingStatus; 
 	// S60 3.0 SDK documentation: only EVoiceService is supported
 	CTelephony::TServiceGroup serviceGroup( CTelephony::EVoiceService ); 
	
	// Execute test  		 
 	result = iTestEngine->TestGetCallWaitingStatus(  		
 		callWaitingStatus,
 		serviceGroup );	 
	// Parse result data 
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCallWaitingStatus( 	 	
	 		callWaitingStatus,
	 		serviceGroup );
 		}
	// Set result for STIF framework
	aResult.SetResult( result, KGetCallWaitingStatus );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetIdentityServiceStatus
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetIdentityServiceStatus( TTestResult& aResult )
	{
    TInt result; 	
 	CTelephony::TIdentityService identityService;  	
 	CTelephony::TIdentityServiceV1 identityServiceStatus;
	
	// Test for TIdentityService::EIdServiceUnspecified
	identityService = CTelephony::EIdServiceUnspecified; 	
 	// Execute test  	
 	result = iTestEngine->TestGetIdentityServiceStatus(  		
 		identityService,
 		identityServiceStatus );	 
	// Parse result data 
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetIdentityServiceStatus( 
			identityService, 
			identityServiceStatus );
 		}

	// Test for TIdentityService::EIdServiceCallerPresentation
	identityService = CTelephony::EIdServiceCallerPresentation; 	
 	// Execute test  	
 	result = iTestEngine->TestGetIdentityServiceStatus(  		
 		identityService,
 		identityServiceStatus );	 
	// Parse result data 
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetIdentityServiceStatus( 
			identityService, 
			identityServiceStatus );
 		}
 		
	// Test for TIdentityService::EIdServiceCallerRestriction
	identityService = CTelephony::EIdServiceCallerRestriction; 	
 	// Execute test  	
 	result = iTestEngine->TestGetIdentityServiceStatus(  		
 		identityService,
 		identityServiceStatus );	 
	// Parse result data 
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetIdentityServiceStatus( 
			identityService, 
			identityServiceStatus );
 		}
 		
	// Set result for STIF framework
	aResult.SetResult( result, KGetIdentityServiceStatus );			
		
	return result; 
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestDialNewCall
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestDialNewCall( TTestResult& aResult )
	{
    TInt result; 	
	
	// Initialise with tester ini file values
	iCallParams.iIdRestrict = iIdRestrict;
	
	// Precondition: setup ongoing call  
 	result = iTestEngine->TestDialNewCall(  		
 		iCallParams,
 		iTelNumber1,
 		iCallId1,
 		iPhoneLine );	  		 	
	// Parse result data 
 	if( KErrNone == result )
 		{
		iTestParser->ParseDialNewCall( 	 	
			iCallParams,
	 		iTelNumber1,
	 		iCallId1,
	 		iPhoneLine );
 		} 		
	// Restore initial state: end call  		
	iTestEngine->TestHangup( iCallId1 );	  		 				
 	// Set result for STIF framework
	aResult.SetResult( result, KDialNewCall );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetCallDynamicCaps
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetCallDynamicCaps( TTestResult& aResult )
	{
    TInt result; 	
	
	// Initialise with tester ini file values
	iCallParams.iIdRestrict = iIdRestrict;
	
	// Precondition: setup ongoing call  
 	result = iTestEngine->TestDialNewCall(  		
 		iCallParams,
 		iTelNumber1,
 		iCallId1,
 		iPhoneLine );	  		 	
 	// Execute test	 		
	if( KErrNone == result )
		{
	 	result = iTestEngine->TestGetCallDynamicCaps( iCallId1, iCallCaps );	  		 		
		}
	// Parse result data
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCallDynamicCaps( iCallId1, iCallCaps );	  		 		 		
 		}
	// Restore initial state: end call  		
	iTestEngine->TestHangup( iCallId1 );	  		 				
 	// Set result for STIF framework
	aResult.SetResult( result, KGetCallDynamicCaps );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestGetCallStatus
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestGetCallStatus( TTestResult& aResult )
	{
    TInt result; 	
	
	// Initialise with tester ini file values
	iCallParams.iIdRestrict = iIdRestrict;
	
	// Precondition: setup ongoing call  
 	result = iTestEngine->TestDialNewCall(  		
 		iCallParams,
 		iTelNumber1,
 		iCallId1,
 		iPhoneLine );	  		 	
 	// Execute test	 		
	if( KErrNone == result )
		{
	 	result = iTestEngine->TestGetCallStatus( iCallId1, iCallStatus );	  		 		
		}
	// Parse result data
 	if( KErrNone == result )
 		{
		iTestParser->ParseGetCallStatus( iCallId1, iCallStatus );	  		
		}
	// Restore initial state: end call  		
	iTestEngine->TestHangup( iCallId1 );	  		 				
 	// Set result for STIF framework
	aResult.SetResult( result, KGetCallStatus );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestHold
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestHold( TTestResult& aResult )
	{
    TInt result; 	
	
	// Initialise with tester ini file values
	iCallParams.iIdRestrict = iIdRestrict;
	
	// Precondition: setup ongoing call  
 	result = iTestEngine->TestDialNewCall(  		
 		iCallParams,
 		iTelNumber1,
 		iCallId1,
 		iPhoneLine );	  		 	
	// Execute test
	if( KErrNone == result )
		{		
	 	result = iTestEngine->TestHold( iCallId1 );	  		 				
		}
 	// Check expected result
	if( KErrNone == result )
		{		
	 	result = iTestEngine->TestGetCallStatus( iCallId1, iCallStatus );	  		 		
		iTestParser->ParseGetCallStatus( iCallId1, iCallStatus );
		} 		 		
	// Restore initial state: end call  		
	iTestEngine->TestHangup( iCallId1 );	  		 				
 	// Set result for STIF framework
	aResult.SetResult( result, KHold );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestResume
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestResume( TTestResult& aResult )
	{
    TInt result; 	

	// Initialise with tester ini file values
	iCallParams.iIdRestrict = iIdRestrict;
	
	// Precondition: setup ongoing call  
 	result = iTestEngine->TestDialNewCall(  		
 		iCallParams,
 		iTelNumber1,
 		iCallId1,
 		iPhoneLine );	
 	// Precondition: call is on hold
	if( KErrNone == result )
		{		
	 	result = iTestEngine->TestHold( iCallId1 );	  		 				
		}
	// Execute test
	if( KErrNone == result )
		{		
	 	result = iTestEngine->TestResume( iCallId1 );	  		 				
		}
 	// Check expected result
	if( KErrNone == result )
		{		
	 	result = iTestEngine->TestGetCallStatus( iCallId1, iCallStatus );	  		 		
		iTestParser->ParseGetCallStatus( iCallId1, iCallStatus );
		}
	// Restore initial state: end call  		
	iTestEngine->TestHangup( iCallId1 );	  		 				
 	// Set result for STIF framework
	aResult.SetResult( result, KResume );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestSwap
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestSwap( TTestResult& aResult )
	{
    TInt result; 	
	
	// Initialise with tester ini file values
	iCallParams.iIdRestrict = iIdRestrict;
	
	// Precondition: setup ongoing call 1 
 	result = iTestEngine->TestDialNewCall(  		
 		iCallParams,
 		iTelNumber1,
 		iCallId1,
 		iPhoneLine );	
	// Precondition: setup ongoing call 2
 	result = iTestEngine->TestDialNewCall(  		
 		iCallParams,
 		iTelNumber2,
 		iCallId2,
 		iPhoneLine );	  			
	// Execute test
	if( KErrNone == result )
		{		
	 	result = iTestEngine->TestSwap( iCallId1, iCallId2 );	  		 				
		}
 	// Check expected result
	if( KErrNone == result )
		{		
		// Call 1 status
	 	result = iTestEngine->TestGetCallStatus( iCallId1, iCallStatus );	  		 		
		iTestParser->ParseGetCallStatus( iCallId1, iCallStatus );
		// Call 2 status
	 	result = iTestEngine->TestGetCallStatus( iCallId2, iCallStatus );	  		 		
		iTestParser->ParseGetCallStatus( iCallId2, iCallStatus );
		} 		 		
	// Restore initial state: end call 1  		
	iTestEngine->TestHangup( iCallId1 );	  		 				
	// Restore initial state: end call 2  		
	iTestEngine->TestHangup( iCallId2 );	  		 				
 	// Set result for STIF framework
	aResult.SetResult( result, KSwap );			
		
	return result; 
	}
			
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestHangup
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestHangup( TTestResult& aResult )
	{
    TInt result; 	

	// Initialise with tester ini file values
	iCallParams.iIdRestrict = iIdRestrict;
	
	// Precondition: setup ongoing call  
 	result = iTestEngine->TestDialNewCall(  		
 		iCallParams,
 		iTelNumber1,
 		iCallId1,
 		iPhoneLine );	
	// Execute test
	if( KErrNone == result )
		{		
	 	result = iTestEngine->TestHangup( iCallId1 );	  		 				
		}
 	// Set result for STIF framework
	aResult.SetResult( result, KHangup );			
		
	return result; 
	}
				
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestAnswerIncomingCall
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestAnswerIncomingCall( TTestResult& aResult )
	{
    TInt result; 	
	CTelephony::TCallStatusV1Pckg callStatusPckg( iCallStatus );
	
	// Precondition: inform tester we are expecting an incoming call
	PrintMessage( KWaitingForIncomingCall() );

 	result = iTestEngine->TestAnswerIncomingCall( iCallId1, iPhoneLine );	  		 				

 	// Set result for STIF framework
	aResult.SetResult( result, KAnswerIncomingCall );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestNotifyChangeVoiceLineStatus 
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestNotifyChangeVoiceLineStatus ( TTestResult& aResult )
	{
    TInt result; 	
	CTelephony::TCallStatusV1Pckg callStatusPckg( iCallStatus );
		
	// Precondition: inform tester we are expecting a voice line change, 
	// e.g. an incoming call
	PrintMessage( KWaitingForVoiceLineChange() );
	// Execute test
 	result = iTestEngine->TestNotifyChangeVoiceLineStatus ( 
 		CTelephony::EVoiceLineStatusChange,
 		callStatusPckg );	  		
 	// Check expected result
	if( KErrNone == result )
		{			 	
		iTestParser->ParseCallStatus( iCallStatus );
		} 		 		
 	// Set result for STIF framework
	aResult.SetResult( result, KNotifyChangeVoiceLineStatus );			
		
	return result; 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestFindDeviceStatus
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestFindDeviceStatus( TTestResult& aResult )		
	{
    TInt result; 		
		
	// FindDeviceStatus is deprecated (S60 3.0 SDK) and 
	// should return KErrNotSupported
	if( KErrNotSupported == iTestEngine->TestFindDeviceStatus() )
		{
		result = KErrNone; 	
		}
 	else 
 		{
 		result = KErrGeneral; 
 		}
 	// Inform tester that the function is deprecated
 	PrintMessage( KDeprecatedFunctionTest() );
 	// Set result for STIF framework
	aResult.SetResult( result, KFindDeviceStatus );			
		
	return result; 
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestEstablishDataCall
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestEstablishDataCall( TTestResult& aResult )		
	{
    TInt result; 	
 		 				
	// EstablishDataCall is deprecated (S60 3.0 SDK) and 
	// should return KErrNotSupported
	if( KErrNotSupported == iTestEngine->TestEstablishDataCall() )
		{
		result = KErrNone; 	
		}
 	else 
 		{
 		result = KErrGeneral; 
 		} 	
 	// Inform tester that the function is deprecated
 	PrintMessage( KDeprecatedFunctionTest() );
 	// Set result for STIF framework
	aResult.SetResult( result, KEstablishDataCall );			
		
	return result; 
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestEstablishDataCallAsync
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestEstablishDataCallAsync( TTestResult& aResult )		
	{
    TInt result; 	

	// EstablishDataCall is deprecated (S60 3.0 SDK) and 
	// should return KErrNotSupported
	if( KErrNotSupported == iTestEngine->TestEstablishDataCallAsync() )
		{
		result = KErrNone; 	
		}
 	else 
 		{
 		result = KErrGeneral; 
 		} 	
 	// Inform tester that the function is deprecated
 	PrintMessage( KDeprecatedFunctionTest() );
 	// Set result for STIF framework
	aResult.SetResult( result, KEstablishDataCallAsync );			
		
	return result; 
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestTerminateDataCall
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestTerminateDataCall( TTestResult& aResult )		
	{
    TInt result; 	
	 				
	// TerminateDataCall is deprecated (S60 3.0 SDK) and 
	// should return KErrNotSupported
	if( KErrNotSupported == iTestEngine->TestTerminateDataCall() )
		{
		result = KErrNone; 	
		}
 	else 
 		{
 		result = KErrGeneral; 
 		} 	
 	// Inform tester that the function is deprecated
 	PrintMessage( KDeprecatedFunctionTest() );
 	// Set result for STIF framework
	aResult.SetResult( result, KTerminateDataCall );			
		
	return result; 
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestReceiveDataCall
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestReceiveDataCall( TTestResult& aResult )		
	{
    TInt result; 	
	  		 				
	// ReceiveDataCall is deprecated (S60 3.0 SDK) and 
	// should return KErrNotSupported
	if( KErrNotSupported == iTestEngine->TestReceiveDataCall() )
		{
		result = KErrNone; 	
		}
 	else 
 		{
 		result = KErrGeneral; 
 		} 
 	// Inform tester that the function is deprecated
 	PrintMessage( KDeprecatedFunctionTest() );
 	// Set result for STIF framework
	aResult.SetResult( result, KReceiveDataCall );			
		
	return result; 
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestReceiveDataCallAsync
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestReceiveDataCallAsync( TTestResult& aResult )		
	{
    TInt result; 	
		
	// ReceiveDataCall is deprecated (S60 3.0 SDK) and 
	// should return KErrNotSupported
	if( KErrNotSupported == iTestEngine->TestReceiveDataCallAsync() )
		{
		result = KErrNone; 	
		}
 	else 
 		{
 		result = KErrGeneral; 
 		} 
 	// Inform tester that the function is deprecated
 	PrintMessage( KDeprecatedFunctionTest() );
 	// Set result for STIF framework
	aResult.SetResult( result, KReceiveDataCallAsync );			
		
	return result; 
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestCancelEstablishDataCall
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestCancelEstablishDataCall( TTestResult& aResult )		
	{
    TInt result; 	

	// CancelEstablishDataCall is deprecated (S60 3.0 SDK) and 
	// TestEngine returns KErrNone
	result = iTestEngine->TestCancelEstablishDataCall(); 
 	// Inform tester that the function is deprecated
 	PrintMessage( KDeprecatedFunctionTest() );
 	// Set result for STIF framework
	aResult.SetResult( result, KCancelEstablishDataCall );			
		
	return result; 
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTest::TestCancelReceiveDataCall
// 
// -----------------------------------------------------------------------------
//
TInt CIsvTelephonyTest::TestCancelReceiveDataCall( TTestResult& aResult )			
	{
    TInt result; 	
	
	// CancelReceiveDataCall is deprecated (S60 3.0 SDK) and 
	// TestEngine returns KErrNone
	result = iTestEngine->TestCancelReceiveDataCall(); 
 	// Inform tester that the function is deprecated
 	PrintMessage( KDeprecatedFunctionTest() );
 	// Set result for STIF framework
	aResult.SetResult( result, KCancelReceiveDataCall );			
		
	return result; 
	}
	
//  End of File
