/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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

/* Changed by Vaibhav - 13Aug07 for Removing CodeScanner Warnings - High/medium */


// INCLUDE FILES
#include <e32std.h>
#include <c32comm.h>
#include <etel.h> 
#include <Etel3rdParty.h>
#include "IsvTelephonyTestEngine.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine* CIsvTelephonyTestEngine::NewL
// Two-phased constructor.
// ----------------------------------------------------------------------------
//
CIsvTelephonyTestEngine* CIsvTelephonyTestEngine::NewL()
    {
    CIsvTelephonyTestEngine* self = new (ELeave) CIsvTelephonyTestEngine;        
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();    
    return self;
    }

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::~CIsvTelephonyTestEngine
// Destructor.
// ----------------------------------------------------------------------------
//
CIsvTelephonyTestEngine::~CIsvTelephonyTestEngine()
    {
    Cancel();    
    delete iTelephony; 
    }

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::RunL
// Handles the active object’s request completion event.
// ----------------------------------------------------------------------------
//
void CIsvTelephonyTestEngine::RunL()
    {
    iWait.AsyncStop();
    }

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::DoCancel
// Implements cancellation of an outstanding request.
// ----------------------------------------------------------------------------
//
void CIsvTelephonyTestEngine::DoCancel()
    {
    //Based on the command, invoke the appropriate CancelAsync APIs
    switch( iTelApiCmd )
        {
		case EGetPhoneId :
            iTelephony->CancelAsync( CTelephony::EGetPhoneIdCancel );
            break;
		case EGetSubscriberId :
            iTelephony->CancelAsync( CTelephony::EGetSubscriberIdCancel );
            break;
		case EGetFlightMode :
            iTelephony->CancelAsync( CTelephony::EGetFlightModeCancel );
            break;
		case EGetIndicator :
            iTelephony->CancelAsync( CTelephony::EGetIndicatorCancel );
            break;
        case EGetBatteryInfo : 
            iTelephony->CancelAsync( CTelephony::EGetBatteryInfoCancel );
            break;
        case EGetSignalStrength :
            iTelephony->CancelAsync( CTelephony::EGetSignalStrengthCancel );
            break;
        case EGetLockInfo :
            iTelephony->CancelAsync( CTelephony::EGetLockInfoCancel );
            break;        
		case ESendDTMFTones:
            iTelephony->CancelAsync( CTelephony::ESendDTMFTonesCancel );
            break;
      	case EDialNewCall :
            iTelephony->CancelAsync( CTelephony::EDialNewCallCancel );
            break;        
      	case EHold :
            iTelephony->CancelAsync( CTelephony::EHoldCancel );
            break;        
      	case EResume :
            iTelephony->CancelAsync( CTelephony::EResumeCancel );
            break;        
      	case ESwap :
            iTelephony->CancelAsync( CTelephony::ESwapCancel );
            break;        
      	case EHangup :
            iTelephony->CancelAsync( CTelephony::EHangupCancel );
            break;        
      	case EAnswerIncomingCall :
            iTelephony->CancelAsync( CTelephony::EAnswerIncomingCallCancel );
            break;        
		case ENwRegistrationStatus :
            iTelephony->CancelAsync( CTelephony::EGetNetworkRegistrationStatusCancel );
            break;
		case EGetCurrentNetworkInfo :
            iTelephony->CancelAsync( CTelephony::EGetCurrentNetworkInfoCancel );
            break;
		case EGetCurrentNetworkName:
            iTelephony->CancelAsync( CTelephony::EGetCurrentNetworkNameCancel );
            break;            
      	case EGetOperatorName :
            iTelephony->CancelAsync( CTelephony::EGetOperatorNameCancel );
            break;        
        case EGetCallForwardingStatus :
            iTelephony->CancelAsync( CTelephony::EGetCallForwardingStatusCancel );
            break;        
        case EGetBarringStatus :
            iTelephony->CancelAsync( CTelephony::EGetCallBarringStatusCancel );
            break;        
        case EGetWaitingStatus :
            iTelephony->CancelAsync( CTelephony::EGetCallWaitingStatusCancel );
            break;        
        case EGetIdentityStatus :
            iTelephony->CancelAsync( CTelephony::EGetIdentityServiceStatusCancel );
            break;        
      	case ENotifyChange :
      		switch( iNotificationEvent )
      			{
      			case CTelephony::EOwnedCall1StatusChange : 
      				iTelephony->CancelAsync( CTelephony::EOwnedCall1StatusChangeCancel );
      				break; 
      			case CTelephony::EOwnedCall2StatusChange : 
      				iTelephony->CancelAsync( CTelephony::EOwnedCall2StatusChangeCancel );
      				break; 
      			case CTelephony::EVoiceLineStatusChange : 
      				iTelephony->CancelAsync( CTelephony::EVoiceLineStatusChangeCancel );
      				break; 
      			default: 
      				break; 
      			}            
            break;                    
        default :
            break;
        }
    }

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::CIsvTelephonyTestEngine
// Default constructor.
// ----------------------------------------------------------------------------
//
CIsvTelephonyTestEngine::CIsvTelephonyTestEngine()
    :CActive( EPriorityStandard )    
    { 
    CActiveScheduler::Add( this );
    }

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::ConstructL
// It creates a CTelephony object and initializes a locally 
// contained command table.
// ----------------------------------------------------------------------------
//
void CIsvTelephonyTestEngine::ConstructL()
    {
    //Creating Telephony object. 
    iTelephony = CTelephony::NewL();
    }

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::StartWait
// Checks for the active scheduler wait class's start state and then starts the
// wait
// ----------------------------------------------------------------------------
//
void CIsvTelephonyTestEngine::StartWait( )
    {
    // For testing CancelAsync     
    if( iCancelAsyncs == (TBool) ETrue )
    	{
    	DoCancel();     	    	
    	}    
    	    
    if ( iWait.IsStarted() != (TBool) ETrue )
        {
        iWait.Start();
        }
    }

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::SetCancelAsyncs
// Cancels the asynchronous tests with CancelAsync
// until flag aSetting is cleared 
// ----------------------------------------------------------------------------
//
void CIsvTelephonyTestEngine::SetCancelAsyncs( TBool aSetting )
	{	
	iCancelAsyncs = aSetting; 
	}

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetVersion
// Test function that calls Version of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetVersion( TVersion& aVersion )
	{
	aVersion = iTelephony->Version(); 
	
	return KErrNone; 
	}

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetPhoneId
// Test function that calls GetPhoneId of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetPhoneId( 
	CTelephony::TPhoneIdV1& aPhoneId )
	{
    CTelephony::TPhoneIdV1Pckg aPhoneIdPckg( aPhoneId );
    
    iTelApiCmd = EGetPhoneId;    
     
    iTelephony->GetPhoneId( iStatus, aPhoneIdPckg );
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
	}

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetSubscriberId
// Test function that calls GetSubscriberId of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetSubscriberId( 
	CTelephony::TSubscriberIdV1& aSubscriberId )
	{
    CTelephony::TSubscriberIdV1Pckg aSubscriberIdPckg( aSubscriberId );
    
    iTelApiCmd = EGetSubscriberId;
    
    iTelephony->GetSubscriberId( iStatus, aSubscriberIdPckg );
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
	}

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetFlightMode
// Test function that calls GetFlightMode of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetFlightMode( 
	CTelephony::TFlightModeV1& aFlightMode )
	{
    CTelephony::TFlightModeV1Pckg flightModePckg( aFlightMode ); 
    
    iTelApiCmd = EGetFlightMode;
    
    iTelephony->GetFlightMode( iStatus, flightModePckg );
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
	}

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetIndicator
// Test function that calls GetIndicator of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetIndicator( 	
	CTelephony::TIndicatorV1& aIndicator )
	{
    CTelephony::TIndicatorV1Pckg indicatorPckg( aIndicator );  
    
    iTelApiCmd = EGetIndicator;
    
    iTelephony->GetIndicator( iStatus, indicatorPckg );
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
	}

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetBatteryInfo
// Test function that calls GetBatteryInfo of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetBatteryInfo( 
	CTelephony::TBatteryInfoV1& aBatteryInfo )
	{
    CTelephony::TBatteryInfoV1Pckg batteryInfoPckg( aBatteryInfo );  
    
    iTelApiCmd = EGetBatteryInfo;
    
    iTelephony->GetBatteryInfo( iStatus, batteryInfoPckg );
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
	}        	
    
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetSignalStrength
// Test function that calls GetSignalStrength of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetSignalStrength( 
	CTelephony::TSignalStrengthV1& aSignalStrength )        	
	{
    CTelephony::TSignalStrengthV1Pckg signalStrengthPckg( aSignalStrength );  
    
    iTelApiCmd = EGetSignalStrength;
    
    iTelephony->GetSignalStrength( iStatus, signalStrengthPckg );
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
	}    	

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetLockInfo
// Test function that calls GetLockInfo of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetLockInfo( 
	CTelephony::TIccLock& aLock, 
	CTelephony::TIccLockInfoV1& aLockInfo )
	{
    CTelephony::TIccLockInfoV1Pckg lockInfoPckg( aLockInfo );  
    
    iTelApiCmd = EGetLockInfo;
    
    iTelephony->GetLockInfo( iStatus, aLock, lockInfoPckg );
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
	}    	

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestSendDTMFTones
// Test function that calls SendDTMFTones of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestSendDTMFTones(
	const TDesC& aDTMFTones )
	{
    iTelApiCmd = ESendDTMFTones;
    
    iTelephony->SendDTMFTones( iStatus, aDTMFTones );
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
	}    	
	
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetLineStatus
// Test function that calls GetLineStatus of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetLineStatus(
	CTelephony::TPhoneLine& aPhoneLine,
	CTelephony::TCallStatusV1& aCallStatus )
	{
    TInt result; 	
    
    iTelApiCmd = EGetLockInfo;
    
    CTelephony::TCallStatusV1Pckg callStatusPckg( aCallStatus );  
    result = iTelephony->GetLineStatus( aPhoneLine, callStatusPckg );
						
	return result; 
	}  

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetCallInfo
// Test function that calls GetCallInfo of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetCallInfo( 
	CTelephony::TCallSelectionV1& aCallSelection, 
	CTelephony::TCallInfoV1& aCallInfo, 
	CTelephony::TRemotePartyInfoV1& aRemotePartyInfo )	    			
	{
	TInt result; 

    iTelApiCmd = EGetCallInfo;
    
	CTelephony::TCallSelectionV1Pckg callSelectionPckg( aCallSelection );   
    CTelephony::TCallInfoV1Pckg callInfoPckg( aCallInfo );  
	CTelephony::TRemotePartyInfoV1Pckg remotePartyInfoPckg( aRemotePartyInfo );  	    			
    
    result = iTelephony->GetCallInfo( 
    	callSelectionPckg, 
    	callInfoPckg, 
    	remotePartyInfoPckg );

	return result; 
	}  

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetNetworkRegistrationStatus
// Test function that calls GetNetworkRegistrationStatus of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetNetworkRegistrationStatus(
	CTelephony::TNetworkRegistrationV1& aNetworkRegistration )        		
    {    
	CTelephony::TNetworkRegistrationV1Pckg 
		networkRegistrationPckg( aNetworkRegistration );

    iTelApiCmd = ENwRegistrationStatus;
		
    iTelephony->GetNetworkRegistrationStatus( iStatus, networkRegistrationPckg );    
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
    }
	
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetCurrentNetworkInfo
// Test function that calls GetCurrentNetworkInfo of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetCurrentNetworkInfo( 
	CTelephony::TNetworkInfoV1& aNetworkInfo )
    {    
	CTelephony::TNetworkInfoV1Pckg networkInfoPckg( aNetworkInfo );

    iTelApiCmd = EGetCurrentNetworkInfo;

    iTelephony->GetCurrentNetworkInfo( iStatus, networkInfoPckg );    
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
    }

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetCurrentNetworkName
// Test function that calls GetCurrentNetworkName of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetCurrentNetworkName( 
	CTelephony::TNetworkNameV1& aNetworkName )
    {    
	CTelephony::TNetworkNameV1Pckg networkNamePckg( aNetworkName );

    iTelApiCmd = EGetCurrentNetworkName;

    iTelephony->GetCurrentNetworkName( iStatus, networkNamePckg );    
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
    }

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetOperatorName
// Test function that calls GetCurrentNetworkName of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetOperatorName( 
	CTelephony::TOperatorNameV1& aOperatorName )
    {    
	CTelephony::TOperatorNameV1Pckg operatorNamePckg( aOperatorName );

    iTelApiCmd = EGetOperatorName;

    iTelephony->GetOperatorName( iStatus, operatorNamePckg );    
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
    }
    	
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetCallForwardingStatus
// Test function that calls GetCallForwardingStatus of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetCallForwardingStatus( 
 	CTelephony::TCallForwardingCondition& aCallForwardingCondition, 
 	CTelephony::TCallForwardingSupplServicesV1& aCallForwardingStatus, 
 	CTelephony::TServiceGroup& aServiceGroup )    	
    {    
	CTelephony::TCallForwardingSupplServicesV1Pckg 
		callForwardingStatusPckg( aCallForwardingStatus );		

    iTelApiCmd = EGetCallForwardingStatus;

    iTelephony->GetCallForwardingStatus( 
    	iStatus, 
    	aCallForwardingCondition, 
    	callForwardingStatusPckg,
    	aServiceGroup );        	
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
    }
    
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetCallBarringStatus
// Test function that calls GetCallBarringStatus of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetCallBarringStatus( 
 	CTelephony::TCallBarringCondition& aCallBarringCondition, 		 	
 	CTelephony::TCallBarringSupplServicesV1& aCallBarringStatus,
 	CTelephony::TServiceGroup& aServiceGroup )    
    {    
	CTelephony::TCallBarringSupplServicesV1Pckg 
		callBarringStatusPckg( aCallBarringStatus );		

    iTelApiCmd = EGetBarringStatus;

    iTelephony->GetCallBarringStatus( 
    	iStatus, 
    	aCallBarringCondition, 
    	callBarringStatusPckg,
    	aServiceGroup );        	
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
    }

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetCallBarringStatus
// Test function that calls GetCallBarringStatus of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetCallWaitingStatus( 		 	
 	CTelephony::TCallWaitingSupplServicesV1& aCallWaitingStatus,
 	CTelephony::TServiceGroup& aServiceGroup )    		 	
    {    
	CTelephony::TCallWaitingSupplServicesV1Pckg 
		callWaitingStatusPckg( aCallWaitingStatus );		

    iTelApiCmd = EGetWaitingStatus;

    iTelephony->GetCallWaitingStatus( 
    	iStatus,     	
    	callWaitingStatusPckg,
    	aServiceGroup );        	
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
    }

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetIdentityServiceStatus
// Test function that calls GetIdentityServiceStatus of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetIdentityServiceStatus( 		 	
 	CTelephony::TIdentityService& aIdentityService,
 	CTelephony::TIdentityServiceV1& aIdentityServiceStatus )
    {    
	CTelephony::TIdentityServiceV1Pckg
		identityServiceStatusPckg( aIdentityServiceStatus );		

    iTelApiCmd = EGetIdentityStatus;

    iTelephony->GetIdentityServiceStatus( 
    	iStatus,     	
    	aIdentityService,
    	identityServiceStatusPckg );        	
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
    }

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestDialNewCall
// Test function that calls DialNewCall of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestDialNewCall( 
 	CTelephony::TCallParamsV1& aCallParams, 
 	CTelephony::TTelNumber& aTelNumber, 
	CTelephony::TCallId& aCallId, 
	CTelephony::TPhoneLine& aPhoneLine )
    {    
	CTelephony::TCallParamsV1Pckg callParamsPckg( aCallParams );		

    iTelApiCmd = EDialNewCall;

    iTelephony->DialNewCall( 
    	iStatus,     	
    	callParamsPckg,
    	aTelNumber,
    	aCallId,
    	aPhoneLine );        	
    SetActive();
    StartWait(); 
						
	return iStatus.Int(); 
    }	

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetCallDynamicCaps
// Test function that calls GetCallDynamicCaps of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetCallDynamicCaps( 		 	
	CTelephony::TCallId& aCallId, 
	CTelephony::TCallCapsV1& aCallCaps )
    {    
	CTelephony::TCallCapsV1Pckg callCapsPckg( aCallCaps );		
	TInt result; 		

    iTelApiCmd = EGetCallDynamicCaps;

    result = iTelephony->GetCallDynamicCaps(     	
    	aCallId,
    	callCapsPckg );        	
	
	return result; 
    }	
    	
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestGetCallStatus
// Test function that calls GetCallStatus of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestGetCallStatus( 		 	
	CTelephony::TCallId& aCallId, 
	CTelephony::TCallStatusV1& aCallStatus )
    {    
	CTelephony::TCallStatusV1Pckg callStatusPckg( aCallStatus );		
	TInt result; 		

    iTelApiCmd = EGetCallStatus;

    result = iTelephony->GetCallStatus(     	
    	aCallId,
    	callStatusPckg );        	
	
	return result; 
    }	

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestHold
// Test function that calls Hold of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestHold( 
	CTelephony::TCallId& aCallId )
    {    		
    iTelApiCmd = EHold;

    iTelephony->Hold(  
    	iStatus,   	
    	aCallId );        	
    SetActive();
    StartWait(); 
	
	return iStatus.Int(); 
    }	

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestResume
// Test function that calls Resume of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestResume( 
	CTelephony::TCallId& aCallId )
    {    		
    iTelApiCmd = EResume;

    iTelephony->Resume(  
    	iStatus,   	
    	aCallId );        	
    SetActive();
    StartWait(); 
	
	return iStatus.Int(); 
    }					    	

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestSwap
// Test function that calls Swap of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestSwap( 
	CTelephony::TCallId& aCallId1,
	CTelephony::TCallId& aCallId2 )
    {    		
    iTelApiCmd = ESwap;

    iTelephony->Swap(  
    	iStatus,   	
    	aCallId1,
    	aCallId2 );        	
    SetActive();
    StartWait(); 
	
	return iStatus.Int(); 
    }					    	

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestHangup
// Test function that calls Hangup of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestHangup( 
	CTelephony::TCallId& aCallId )
    {    		
    iTelApiCmd = EHangup;

    iTelephony->Hangup(  
    	iStatus,   	
    	aCallId );        	
    SetActive();
    StartWait(); 
	
	return iStatus.Int(); 
    }					    	
                
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestAnswerIncomingCall
// Test function that calls AnswerIncomingCall of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestAnswerIncomingCall( 		 	
	CTelephony::TCallId& aCallId, 
	CTelephony::TPhoneLine& aPhoneLine )
    {    		
    // AnswerIncomingCall needs special test approach, calling 
    // CTelephony::AnswerIncomingCall function opens a new timer handle
    // that is not closed while CTelephony object exists. STIF tool recognizes 
    // this as handle leak unless CTelephony is constructed and deleted within the 
    // AnswerIncomingCall function (not a real leak)    
    TInt result;
	CTelephony::TCallStatusV1 callStatus; 
	CTelephony::TCallStatusV1Pckg callStatusPckg( callStatus );

    iTelApiCmd = EAnswerIncomingCall;
	
	// Precondition: wait incoming call
 	result = TestNotifyChangeVoiceLineStatus ( 
 		CTelephony::EVoiceLineStatusChange,
 		callStatusPckg ); 			
	// Execute test
	if( KErrNone == result && CTelephony::EStatusRinging == callStatus.iStatus )
	    {
    	// Test AnswerIncomingCall
        iTelephony->AnswerIncomingCall(
        	iStatus,      	
        	aCallId,
        	aPhoneLine );        	
        SetActive();
        StartWait(); 	    
        result = iStatus.Int(); 	
	    }
    // Restore initial state: end call   		 
    TestHangup( aCallId );
    
    // Delete and re-construct the CTelephony in order to overcome false handle 
    // leak detection problem described earlier
    delete iTelephony; 
    iTelephony = NULL;	
    TRAPD(err, iTelephony = CTelephony::NewL());
    if(err != KErrNone)
    return err;
        
	return result; 
    }	

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestNotifyChangeVoiceLineStatus 
// Test function that calls NotifyChange of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestNotifyChangeVoiceLineStatus (	
	CTelephony::TNotificationEvent aNotificationEvent,
	TDes8& aNotificationPckg )
    {
	iTelApiCmd = ENotifyChange;    	
	iNotificationEvent = aNotificationEvent; 
	
	iTelephony->NotifyChange(
		iStatus, 
		iNotificationEvent, 
		aNotificationPckg );
	SetActive();
	StartWait(); 				
	
	return iStatus.Int(); 	
    }    	                
    
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestFindDeviceStatus
// Test function that calls FindDeviceStatus of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestFindDeviceStatus()
    {
	TInt result;  	
	TInt deviceStatus; 		

	iTelApiCmd = EFindDeviceStatus;		
	
	// FindDeviceStatus is deprecated and should return KErrNotSupported	
	result = iTelephony->FindDeviceStatus( deviceStatus ); 
		
	return result; 
    }    
    
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestEstablishDataCall
// Test function that calls EstablishDataCall of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestEstablishDataCall()
    {
	TInt result;  	
	TInt dataChannel; 

	iTelApiCmd = EEstablishDataCall;	
		
	// EstablishDataCall is deprecated and should return KErrNotSupported	
	result = iTelephony->EstablishDataCall( dataChannel, KNullDesC ); 
	
	return result; 
    }    

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestEstablishDataCallAsync
// Test function that calls EstablishDataCall of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestEstablishDataCallAsync()
    {
	TInt dataChannel; 	

	iTelApiCmd = EEstablishDataCall;		
	
	// EstablishDataCall is deprecated and should return KErrNotSupported	
	iTelephony->EstablishDataCall( iStatus, dataChannel, KNullDesC );
	SetActive();
	StartWait(); 				
	
	return iStatus.Int(); 	
    }    
    
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestTerminateDataCall
// Test function that calls TerminateDataCall of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestTerminateDataCall()		
    {
	TInt result;  	

	iTelApiCmd = ETerminateDataCall;	
	
	// TerminateDataCall is deprecated and should return KErrNotSupported	
	result = iTelephony->TerminateDataCall();
	
	return result; 
    }    
    
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestReceiveDataCall
// Test function that calls ReceiveDataCall of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestReceiveDataCall()		
    {
	TInt result; 
	TInt dataChannel; 

	iTelApiCmd = EReceiveDataCall;	
	
	// ReceiveDataCall is deprecated and should return KErrNotSupported	
	result = iTelephony->ReceiveDataCall( dataChannel );
	
	return result; 
    }    
    
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestReceiveDataCallAsync
// Test function that calls ReceiveDataCall of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestReceiveDataCallAsync()
    {
	TInt dataChannel; 

	iTelApiCmd = EReceiveDataCall;	
	
	// ReceiveDataCall is deprecated and should return KErrNotSupported	
	iTelephony->ReceiveDataCall( iStatus, dataChannel );
	SetActive();
	StartWait(); 				
	
	return iStatus.Int(); 	
    }    		

// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestCancelEstablishDataCall
// Test function that calls CancelEstablishDataCall of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestCancelEstablishDataCall()		
    {
	TInt result; 

	iTelApiCmd = ECancelEstablishDataCall;	
	
	// CancelEstablishDataCall is deprecated
	iTelephony->CancelEstablishDataCall();
	result = KErrNone; 
	
	return result; 
    }    
    
// ----------------------------------------------------------------------------
// CIsvTelephonyTestEngine::TestCancelReceiveDataCall
// Test function that calls CancelReceiveDataCall of CTelephony class.
// ----------------------------------------------------------------------------
//
TInt CIsvTelephonyTestEngine::TestCancelReceiveDataCall()
    {
	TInt result; 

	iTelApiCmd = ECancelReceiveDataCall;	
	
	// CancelReceiveDataCall is deprecated
	iTelephony->CancelReceiveDataCall();
	result = KErrNone; 
    
    return result;
    }    	    

// End of File  
