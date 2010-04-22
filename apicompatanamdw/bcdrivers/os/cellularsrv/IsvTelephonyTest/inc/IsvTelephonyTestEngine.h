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
* Description:  A class that wraps the CTelephony class.
*  Copyright (c) 2005 Nokia. All rights reserved.
*
*/



#ifndef ISVTELEPHONYTESTENGINE_H
#define ISVTELEPHONYTESTENGINE_H

// INCLUDES
#include <e32base.h>
#include <etel3rdparty.h>

// FORWARD DECLARATIONS
class CTelephony;

// CLASS DEFINITIONS

/**
* CIsvTelephonyTest: This class derives from CActive and wraps the 
* CTelephony class. Provides a command table based execution for 
* telephony commands with command specific parsing capabilities.
*/
class CIsvTelephonyTestEngine : public CActive
    {
    public:
    
	  /**
	   * Command Table.
	   */
	   enum TETelApiCmd 
		   	{
	        /** 
	        Get Phone Identity.
	        */
	        EGetPhoneId = 0,
	        /** 
	        Get SubscriberId.
	        */
	        EGetSubscriberId,
			/**
	        Get CurrentNetworkInfo.
	        */
	        EGetCurrentNetworkInfo,
			/**
	        Get CurrentNetworkName.
	        */
	        EGetCurrentNetworkName,
	        /** 
	        Get Flight Mode.
	        */
	        EGetFlightMode,
	        /** 
	        Get Indicator.
	        */
	        EGetIndicator,
	        /** 
	        Get Signal Strength.
	        */
	        EGetSignalStrength,
	        /** 
	        Get Lock Info.
	        */
	        EGetLockInfo,            
	        /** 
	        Send DTMF Tones
	        */
	        ESendDTMFTones,     
	        /** 
	        Get line status 
	        */
	        EGetLineStatus,     
	        /** 
	        Get call info
	        */
			EGetCallInfo, 
	        /** 
	        Get Operator Name.
	        */
	        EGetOperatorName,      
	        /** 
	        Get Call Forwarding Status. 
	        */
	        EGetCallForwardingStatus,                  
	        /** 
	        Get Network registration status.
	        */
	        ENwRegistrationStatus,
	        /**
	        Get Battery Info.
	        */
	        EGetBatteryInfo,
	        /** 
	        Get Call barring status.
	        */
	        EGetBarringStatus,
	        /** 
	        Get Call waiting status.
	        */
	        EGetWaitingStatus,
	        /** 
	        Get identity status.
	        */
	        EGetIdentityStatus,
	        /** 
	        Dial new call.
	        */
	        EDialNewCall,
	        /** 
	        Get call dynamic caps.
	        */
	        EGetCallDynamicCaps,	 
	        /** 
	        Get call status.
	        */
	        EGetCallStatus,	 	        	               
	        /** 
	        Hold.
	        */
	        EHold,
	        /** 
	        Resume.
	        */
	        EResume,
	        /** 
	        Swap.
	        */
	        ESwap,
	        /** 
	        Hangup.
	        */
	        EHangup,	        
	        /** 
	        AnswerIncomingCall.
	        */
	        EAnswerIncomingCall,
	        /** 
	        Notify change.
	        */
			ENotifyChange,
	        /** 
			Find device status.
	        */
			EFindDeviceStatus,
	        /** 
			Establish data call.
	        */
			EEstablishDataCall,
	        /** 
			Terminate data call.
	        */
			ETerminateDataCall,
	        /** 
			Receive data call.
	        */
			EReceiveDataCall,
	        /** 
			Cancel establish data call.
	        */
			ECancelEstablishDataCall,
	        /** 
			Cancel receive data call.
	        */
			ECancelReceiveDataCall, 
	        /** 
	        Maximum number of commands.
	        */
	        EMaxCommands,
	        /**
	        Command None
	        */
	        ECommandNone
	        };    
	        
    public:  // Constructors and destructor
    
        /**
        * Two-phased constructor.
        */
        static CIsvTelephonyTestEngine* NewL();
        
        /**
        * Destructor.
        */
        virtual ~CIsvTelephonyTestEngine();

    public:	// Test functions for individual commands
        
		/**
        * Sets internal cancel async flag, causing async function 
        * tests to be cancelled with CancelAsync() 
        */
		void SetCancelAsyncs( TBool aSetting );

        /**
        * Function for calling CTelephony::Version
        */
		TInt TestGetVersion( TVersion& aVersion );

        /**
        * Function for calling CTelephony::GetPhoneId
        */
		TInt TestGetPhoneId( 
			CTelephony::TPhoneIdV1& aPhoneId );

        /**
        * Function for calling CTelephony::GetSubscriberId
        */
		TInt TestGetSubscriberId( 
			CTelephony::TSubscriberIdV1& aSubscriberId );

        /**
        * Function for calling CTelephony::GetFlightMode
        */
		TInt TestGetFlightMode( 
			CTelephony::TFlightModeV1& aFlightMode );

        /**
        * Function for calling CTelephony::GetIndicator
        */
		TInt TestGetIndicator( 
			CTelephony::TIndicatorV1& aIndicator );

        /**
        * Function for calling CTelephony::GetBatteryInfo
        */
        TInt TestGetBatteryInfo( 
        	CTelephony::TBatteryInfoV1& aBatteryInfo );

        /**
        * Function for calling CTelephony::GetSignalStrength
        */
        TInt TestGetSignalStrength( 
        	CTelephony::TSignalStrengthV1& aSignalStrength );

        /**
        * Function for calling CTelephony::GetLockInfo
        */
        TInt TestGetLockInfo(
        	CTelephony::TIccLock& aLock, 
        	CTelephony::TIccLockInfoV1& aLockInfo );

        /**
        * Function for calling CTelephony::SendDTMFTones
        */
        TInt TestSendDTMFTones(
        	const TDesC& aDTMFTones );

        /**
        * Function for calling CTelephony::GetLineStatus
        */
        TInt TestGetLineStatus(
        	CTelephony::TPhoneLine& aPhoneLine,
    		CTelephony::TCallStatusV1& aCallStatus );

        /**
        * Function for calling CTelephony::GetCallInfo
        */
        TInt TestGetCallInfo( 
 			CTelephony::TCallSelectionV1& aCallSelection, 
 			CTelephony::TCallInfoV1& aCallInfo, 
 			CTelephony::TRemotePartyInfoV1& aRemotePartyInfo );    

        /**
        * Function for calling CTelephony::GetNetworkRegistrationStatus
        */
        TInt TestGetNetworkRegistrationStatus(
        	CTelephony::TNetworkRegistrationV1& aNetworkRegistration );

        /**
        * Function for calling CTelephony::GetCurrentNetworkInfo
        */
        TInt TestGetCurrentNetworkInfo( 
        	CTelephony::TNetworkInfoV1& aNetworkInfo );

        /**
        * Function for calling CTelephony::GetCurrentNetworkName
        */
        TInt TestGetCurrentNetworkName( 
        	CTelephony::TNetworkNameV1& aNetworkName );
						
        /**
        * Function for calling CTelephony::GetOperatorName
        */
        TInt TestGetOperatorName( 
        	CTelephony::TOperatorNameV1& aOperatorName );
        	
        /**
        * Function for calling CTelephony::GetCallForwardingStatus
        */
        TInt TestGetCallForwardingStatus( 
		 	CTelephony::TCallForwardingCondition& aCallForwardingCondition, 		 	
		 	CTelephony::TCallForwardingSupplServicesV1& aCallForwardingStatus,
		 	CTelephony::TServiceGroup& aServiceGroup );  

        /**
        * Function for calling CTelephony::GetCallBarringStatus
        */
        TInt TestGetCallBarringStatus( 
		 	CTelephony::TCallBarringCondition& aCallBarringCondition, 		 	
		 	CTelephony::TCallBarringSupplServicesV1& aCallBarringStatus,
		 	CTelephony::TServiceGroup& aServiceGroup );  
		
        /**
        * Function for calling CTelephony::GetCallWaitingStatus
        */
        TInt TestGetCallWaitingStatus( 		 	
		 	CTelephony::TCallWaitingSupplServicesV1& aCallWaitingStatus,
		 	CTelephony::TServiceGroup& aServiceGroup );  

        /**
        * Function for calling CTelephony::GetIdentityServiceStatus
        */
        TInt TestGetIdentityServiceStatus( 		 	
		 	CTelephony::TIdentityService& aIdentityService,
		 	CTelephony::TIdentityServiceV1& aIdentityServiceStatus );
 	
        /**
        * Function for calling CTelephony::DialNewCall
        */
        TInt TestDialNewCall( 
		 	CTelephony::TCallParamsV1& aCallParams, 
		 	CTelephony::TTelNumber& aTelNumber, 
			CTelephony::TCallId& aCallId, 
			CTelephony::TPhoneLine& aPhoneLine ); 
	 	
        /**
        * Function for calling CTelephony::GetCallDynamicCaps
        */
        TInt TestGetCallDynamicCaps( 		 	
			CTelephony::TCallId& aCallId, 
			CTelephony::TCallCapsV1& aCallCaps ); 

        /**
        * Function for calling CTelephony::GetCallStatus
        */
        TInt TestGetCallStatus( 		 	
			CTelephony::TCallId& aCallId, 
			CTelephony::TCallStatusV1& aCallStatus ); 	 		 	

        /**
        * Function for calling CTelephony::Hold
        */
        TInt TestHold( 
        	CTelephony::TCallId& aCallId ); 	 		 	
	
        /**
        * Function for calling CTelephony::Resume
        */
        TInt TestResume( 
        	CTelephony::TCallId& aCallId ); 	 		 	

        /**
        * Function for calling CTelephony::Swap
        */
        TInt TestSwap( 
        	CTelephony::TCallId& aCallId1,
        	CTelephony::TCallId& aCallId2 ); 	 		 	

        /**
        * Function for calling CTelephony::Hangup
        */
        TInt TestHangup( 
        	CTelephony::TCallId& aCallId ); 	 		 	

        /**
        * Function for calling CTelephony::AnswerIncomingCall
        */
        TInt TestAnswerIncomingCall( 		 	
			CTelephony::TCallId& aCallId, 
			CTelephony::TPhoneLine& aPhoneLine ); 	 		 	

        /**
        * Function for calling CTelephony::NotifyChange
        */
        TInt TestNotifyChangeVoiceLineStatus ( 
        	CTelephony::TNotificationEvent aNotificationEvent, 
        	TDes8& aNotificationPckg );
		
        /**
        * Function for calling CTelephony::FindDeviceStatus
        */
		TInt TestFindDeviceStatus();		

        /**
        * Function for calling CTelephony::EstablishDataCall
        */
		TInt TestEstablishDataCall();		

        /**
        * Function for calling CTelephony::EstablishDataCall
        */
		TInt TestEstablishDataCallAsync();		

        /**
        * Function for calling CTelephony::TerminateDataCall
        */
		TInt TestTerminateDataCall();		

        /**
        * Function for calling CTelephony::ReceiveDataCall
        */
		TInt TestReceiveDataCall();		

        /**
        * Function for calling CTelephony::ReceiveDataCall
        */
		TInt TestReceiveDataCallAsync();		

        /**
        * Function for calling CTelephony::CancelEstablishDataCall
        */
		TInt TestCancelEstablishDataCall();		

        /**
        * Function for calling CTelephony::CancelReceiveDataCall
        */
		TInt TestCancelReceiveDataCall();	
				
    protected:
    
        /**
        * From CActive, RunL.
        * Handles the active object’s request completion event.
        */
        void RunL();
        
        /**
        * From CActive, DoCancel.
        * Implements cancellation of an outstanding request.
        */
        void DoCancel();

        /**
        * Starts the active scheduler wait after testing if it 
        * is already started.
        */                                                        
        void StartWait();

	private: 

        /**
        * Default constructor.
        */
        CIsvTelephonyTestEngine();
        
        /**
        * Second-phase constructor.
        */
        void ConstructL();

    private:    // Data
        // Instance of command table    
        TETelApiCmd iTelApiCmd; 
        
        // Instance of scheduler wait class
        CActiveSchedulerWait iWait; 

        // Pointer to CTelephony class 
        // which contains the Telephony ISV 3rd party API
        CTelephony* iTelephony;      

       	// Notification event
       	CTelephony::TNotificationEvent iNotificationEvent;
       	
       	// Cancel Async flag
       	TBool iCancelAsyncs;
       	
    };

#endif // ISVTELEPHONYTESTENGINE_H
