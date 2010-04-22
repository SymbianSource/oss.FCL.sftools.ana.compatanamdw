/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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



#ifndef ISVTELEPHONYTESTPARSER_H
#define ISVTELEPHONYTESTPARSER_H

//  INCLUDES
#include    <e32base.h>
#include    <etel3rdparty.h>
#include    "IsvTelephonyTest.hrh"

// FORWARD DECLARATIONS
class MIsvTelephonyTestMessageHandler; 

// CLASS DECLARATION

/**
*  Class for parsing test result data to log/UI
*
*  @lib 
*  @since 
*/
class CIsvTelephonyTestParser : public CBase
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        * @param aMessageHandler Reference to class 
        * implementing abstract class MIsvTelephonyTestMessageHandler 
        */
        static CIsvTelephonyTestParser* NewL(
        	MIsvTelephonyTestMessageHandler& aMessageHandler );
        
        /**
        * Destructor.
        */
        virtual ~CIsvTelephonyTestParser();

    public: // New functions
        
        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aVersion Version data
        */
		void ParseGetVersion( TVersion& aVersion );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aPhoneId Phone id data
        */
		void ParseGetPhoneId( 
			CTelephony::TPhoneIdV1& aPhoneId );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aSubscriberId Subscriber id data
        */
		void ParseGetSubscriberId( 
			CTelephony::TSubscriberIdV1& aSubscriberId );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aMode Mode data
        */
		void ParseGetFlightMode( 
			CTelephony::TFlightModeV1& aFlightMode );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aIndicator Indicator data
        */
		void ParseGetIndicator( 
			CTelephony::TIndicatorV1& aIndicator );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aBatteryInfo Battery info data
        */
		void ParseGetBatteryInfo( 
			CTelephony::TBatteryInfoV1& aBatteryInfo );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aSignalStrength Signal strength data
        */
		void ParseGetSignalStrength( 
			CTelephony::TSignalStrengthV1& aSignalStrength );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aLock Lock selection 
        * @param aLockInfo Lock info data
        */
		void ParseGetLockInfo( 
			CTelephony::TIccLock& aLock,
			CTelephony::TIccLockInfoV1& aLockInfo );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aPhoneLine
        * @param aCallStatus
        */
        void ParseGetLineStatus(
        	CTelephony::TPhoneLine& aPhoneLine,
    		CTelephony::TCallStatusV1& aCallStatus ); 

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aCallSelection
        * @param aCallInfo
        * @param aRemotePartyInfo
        */
        void ParseGetCallInfoL( 
 			CTelephony::TCallSelectionV1& aCallSelection, 
 			CTelephony::TCallInfoV1& aCallInfo, 
 			CTelephony::TRemotePartyInfoV1& aRemotePartyInfo );
 			    		
        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aNetworkRegistration Network registration data
        */
		void ParseGetNetworkRegistrationStatus(
    		CTelephony::TNetworkRegistrationV1& aNetworkRegistration ); 

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aNetworkInfo Network info data
        */
		void ParseGetCurrentNetworkInfo(
    		CTelephony::TNetworkInfoV1& aNetworkInfo ); 

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aNetworkName Network name data
        */
		void ParseGetCurrentNetworkName(
    		CTelephony::TNetworkNameV1& aNetworkName ); 

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aOperatorName Operator name data
        */
		void ParseGetOperatorName(
    		CTelephony::TOperatorNameV1& aOperatorName ); 

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aCallForwardingCondition Cal
        * @param aCallForwardingStatus 
        * @param aServiceGroup 
        */
		void ParseGetCallForwardingStatus(
		 	CTelephony::TCallForwardingCondition& aCallForwardingCondition, 
		 	CTelephony::TCallForwardingSupplServicesV1& aCallForwardingStatus, 
		 	CTelephony::TServiceGroup& aServiceGroup );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aCallBarringCondition 
        * @param aCallBarringStatus 
        * @param aServiceGroup 
        */
        void ParseGetCallBarringStatus( 
		 	CTelephony::TCallBarringCondition& aCallBarringCondition, 		 	
		 	CTelephony::TCallBarringSupplServicesV1& aCallBarringStatus,
		 	CTelephony::TServiceGroup& aServiceGroup );  

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aCallWaitingStatus 
        * @param aServiceGroup 
        */
        void ParseGetCallWaitingStatus( 		 	
		 	CTelephony::TCallWaitingSupplServicesV1& aCallWaitingStatus,
		 	CTelephony::TServiceGroup& aServiceGroup );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aIdentityService 
        * @param aIdentityServiceStatus 
        */
        void ParseGetIdentityServiceStatus( 		 	
		 	CTelephony::TIdentityService& aIdentityService,
		 	CTelephony::TIdentityServiceV1& aIdentityServiceStatus );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aCallId
        */
        void ParseCallId( 
			CTelephony::TCallId& aCallId ); 
			
        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aCallParams 
        * @param aTelNumber
        * @param aCallId
        * @param aPhoneLine 
        */
        void ParseDialNewCall( 
		 	CTelephony::TCallParamsV1& aCallParams, 
		 	CTelephony::TTelNumber& aTelNumber, 
			CTelephony::TCallId& aCallId, 
			CTelephony::TPhoneLine& aPhoneLine ); 

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aCallId 
        * @param aCallCaps
        */
        void ParseGetCallDynamicCaps( 		 	
			CTelephony::TCallId& aCallId, 
			CTelephony::TCallCapsV1& aCallCaps );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aCallId 
        * @param aCallStatus
        */
        void ParseGetCallStatus( 		 	
			CTelephony::TCallId& aCallId, 
			CTelephony::TCallStatusV1& aCallStatus );

        /**
        * Parses parameter data and outputs it to a 
        * log and/or UI  
        * @param aCallStatus
        */
        void ParseCallStatus( 		 	
			CTelephony::TCallStatusV1& aCallStatus );
														 	
    private:

        /**
        * C++ default constructor.
        * @param aMessageHandler Reference to class 
        * implementing abstract class MIsvTelephonyTestMessageHandler 
        */
        CIsvTelephonyTestParser( 
			MIsvTelephonyTestMessageHandler& aMessageHandler );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private:    // Data
        // Reference to message handler
		MIsvTelephonyTestMessageHandler& iMessageHandler;  

    };

#endif      // ISVTELEPHONYTESTPARSER_H
            
// End of File
