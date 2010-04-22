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



// INCLUDE FILES
#include <StifLogger.h>
#include <StifTestModule.h>
#include "IsvTelephonyTestParser.h"
#include "IsvTelephonyTestMessageHandler.h"

// LOCAL CONSTANTS AND MACROS
_LIT( KUnknownEnumValueError, "error: unknown enum value" );
_LIT( KTimeFormatLong, "%-B%:0%J%:1%T%:2%S%:3%+B" ); 

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::CIsvTelephonyTestParser
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CIsvTelephonyTestParser::CIsvTelephonyTestParser(
	MIsvTelephonyTestMessageHandler& aMessageHandler )
	:iMessageHandler( aMessageHandler )
    {
    }

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CIsvTelephonyTestParser* CIsvTelephonyTestParser::NewL(
	MIsvTelephonyTestMessageHandler& aMessageHandler )
    {
    CIsvTelephonyTestParser* self = new(ELeave) 
    	CIsvTelephonyTestParser( aMessageHandler );     
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// Destructor
CIsvTelephonyTestParser::~CIsvTelephonyTestParser()
    {
    }

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetVersion
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetVersion( TVersion& aVersion )
	{
	TBuf<KMessageHandlerMaxMessageSize> buffer;  
	
	// Version 
 	iMessageHandler.PrintMessage( KVersion() ); 	 	
 	buffer.Copy( KVersionMajor );
 	buffer.AppendNum( aVersion.iMajor ); 
 	buffer.Append( KVersionMinor );
 	buffer.AppendNum( aVersion.iMinor );  	
 	buffer.Append( KVersionBuild );
 	buffer.AppendNum( aVersion.iBuild ); 
 	iMessageHandler.PrintMessage( buffer );
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetPhoneId
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetPhoneId( 
	CTelephony::TPhoneIdV1& aPhoneId )
	{
	// Manufacturer
	iMessageHandler.PrintMessage( KPhoneManufacturer() ); 			 	
	iMessageHandler.PrintMessage( aPhoneId.iManufacturer ); 			
	iMessageHandler.PrintMessage( KPhoneModel() ); 			 	
	iMessageHandler.PrintMessage( aPhoneId.iModel ); 			
	iMessageHandler.PrintMessage( KPhoneSerialNumber() ); 			 	
	iMessageHandler.PrintMessage( aPhoneId.iSerialNumber ); 			
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetSubscriberId
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetSubscriberId( 
	CTelephony::TSubscriberIdV1& aSubscriberId )
	{
	// Subscriber id
	iMessageHandler.PrintMessage( KSubscriberId() ); 			
	iMessageHandler.PrintMessage( aSubscriberId.iSubscriberId ); 			
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetFlightMode
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetFlightMode( 
	CTelephony::TFlightModeV1& aFlightMode )
	{
	// Flight mode
	iMessageHandler.PrintMessage( KFlightMode() ); 			
    if( CTelephony::EFlightModeOn == aFlightMode.iFlightModeStatus )
    	{
    	iMessageHandler.PrintMessage( KOn() ); 			
    	}
    else
    	{
    	iMessageHandler.PrintMessage( KOff() ); 			
    	}        
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetIndicator
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetIndicator( 
	CTelephony::TIndicatorV1& aIndicator )
	{	
	// Indicator
	iMessageHandler.PrintMessage( KIndicator() ); 	
	if( CTelephony::KIndChargerConnected & aIndicator.iIndicator )
		{
		iMessageHandler.PrintMessage( KChargerConnected() ); 
		}
	else 
		{
		iMessageHandler.PrintMessage( KChargerDisconnected() ); 
		}			
	if( CTelephony::KIndNetworkAvailable & aIndicator.iIndicator )
		{
		iMessageHandler.PrintMessage( KNetworkAvailable() ); 
		}
	else
		{
		iMessageHandler.PrintMessage( KNetworkUnavailable() ); 
		}				
	if( CTelephony::KIndCallInProgress & aIndicator.iIndicator )
		{
		iMessageHandler.PrintMessage( KCallInProgress() ); 
		}
	else
		{
		iMessageHandler.PrintMessage( KCallNotInProgress() ); 
		}
		
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetBatteryInfo
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetBatteryInfo( 
	CTelephony::TBatteryInfoV1& aBatteryInfo )
	{
	TBuf<KMessageHandlerMaxMessageSize> buffer; 

	// Battery info
	iMessageHandler.PrintMessage( KBatteryInfo() ); 		
	// Battery info: status 
	iMessageHandler.PrintMessage( KStatus() ); 	
	switch( aBatteryInfo.iStatus )
		{
		case CTelephony::EPowerStatusUnknown: 
			iMessageHandler.PrintMessage( KPowerStatusUnknown() ); 	
			break; 
		case CTelephony::EPoweredByBattery: 
			iMessageHandler.PrintMessage( KPoweredByBattery() ); 	
			break; 
		case CTelephony::EBatteryConnectedButExternallyPowered: 
			iMessageHandler.PrintMessage( KConnectedButExternallyPowered() ); 	
			break; 
		case CTelephony::ENoBatteryConnected: 
			iMessageHandler.PrintMessage( KNoBatteryConnected() ); 	
			break; 
		case CTelephony::EPowerFault: 
			iMessageHandler.PrintMessage( KPowerFault() ); 	
			break; 
		default:
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}    	   					
	// Battery info: charge level
	iMessageHandler.PrintMessage( KChargeLevel() ); 	
	buffer.Num( aBatteryInfo.iChargeLevel ); 
	iMessageHandler.PrintMessage( buffer ); 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetSignalStrength
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetSignalStrength( 
	CTelephony::TSignalStrengthV1& aSignalStrength )
	{
	TBuf<KMessageHandlerMaxMessageSize> buffer; 
	
	// Signal strength
	iMessageHandler.PrintMessage( KSignalStrength() ); 	
	// Signal strength: bar 
	iMessageHandler.PrintMessage( KBar() ); 	
	buffer.Num( aSignalStrength.iBar ); 
	iMessageHandler.PrintMessage( buffer ); 	
	// Signal strength: signal strength 
	iMessageHandler.PrintMessage( KStrength() ); 	
	buffer.Num( aSignalStrength.iSignalStrength ); 
	iMessageHandler.PrintMessage( buffer ); 
	}	

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetLockInfo
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetLockInfo( 
	CTelephony::TIccLock& aLock, 
	CTelephony::TIccLockInfoV1& aLockInfo )
	{
	// Lock 
	iMessageHandler.PrintMessage( KLock() ); 	
	switch( aLock)
		{
		case CTelephony::ELockPin1: 
			iMessageHandler.PrintMessage( KLockPin1() ); 	
			break; 
		case CTelephony::ELockPin2: 
			iMessageHandler.PrintMessage( KLockPin2() ); 	
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}

	// Lock info
	iMessageHandler.PrintMessage( KLockInfo() ); 		
	// Lock info: status
	iMessageHandler.PrintMessage( KStatus() ); 
	switch( aLockInfo.iStatus )
		{
		case CTelephony::EStatusLockUnknown: 
			iMessageHandler.PrintMessage( KUnknown() ); 	
			break; 
		case CTelephony::EStatusLocked: 
			iMessageHandler.PrintMessage( KLocked() ); 	
			break; 
		case CTelephony::EStatusUnlocked: 
			iMessageHandler.PrintMessage( KUnlocked() ); 	
			break; 
		case CTelephony::EStatusBlocked: 
			iMessageHandler.PrintMessage( KBlocked() ); 	
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}		
	// Lock info: setting
	iMessageHandler.PrintMessage( KSetting() ); 	
	switch( aLockInfo.iSetting )
		{
		case CTelephony::ELockSetUnknown: 
			iMessageHandler.PrintMessage( KUnknown() ); 	
			break; 
		case CTelephony::ELockSetEnabled: 
			iMessageHandler.PrintMessage( KEnabled() ); 	
			break; 
		case CTelephony::ELockSetDisabled: 
			iMessageHandler.PrintMessage( KDisabled() ); 	 	
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetLineStatus
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetLineStatus(
	CTelephony::TPhoneLine& aPhoneLine,
	CTelephony::TCallStatusV1& aCallStatus )
	{
	// Phone line
	iMessageHandler.PrintMessage( KPhoneLine() ); 
	switch( aPhoneLine )
		{
		case CTelephony::EVoiceLine:
			iMessageHandler.PrintMessage( KVoiceLine() ); 
			break; 
		case CTelephony::EDataLine:
			iMessageHandler.PrintMessage( KDataLine() ); 
			break; 
		case CTelephony::EFaxLine:
			iMessageHandler.PrintMessage( KFaxLine() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	
	// Call status
	iMessageHandler.PrintMessage( KCallStatus() ); 
	switch( aCallStatus.iStatus )
		{
		case CTelephony::EStatusUnknown:
			iMessageHandler.PrintMessage( KUnknown() ); 
			break; 
		case CTelephony::EStatusIdle:
			iMessageHandler.PrintMessage( KIdle() ); 
			break; 
		case CTelephony::EStatusDialling:
			iMessageHandler.PrintMessage( KDialling() ); 
			break; 
		case CTelephony::EStatusRinging:
			iMessageHandler.PrintMessage( KRinging() ); 
			break; 
		case CTelephony::EStatusAnswering:
			iMessageHandler.PrintMessage( KAnswering() ); 
			break; 
		case CTelephony::EStatusConnecting:
			iMessageHandler.PrintMessage( KConnecting() ); 
			break; 
		case CTelephony::EStatusConnected:
			iMessageHandler.PrintMessage( KConnected() ); 
			break; 
		case CTelephony::EStatusReconnectPending:
			iMessageHandler.PrintMessage( KReconnectPending() ); 
			break; 
		case CTelephony::EStatusDisconnecting:
			iMessageHandler.PrintMessage( KDisconnecting() ); 
			break; 
		case CTelephony::EStatusHold:
			iMessageHandler.PrintMessage( KOnHold() ); 
			break; 
		case CTelephony::EStatusTransferring:
			iMessageHandler.PrintMessage( KTransferring() ); 
			break; 
		case CTelephony::EStatusTransferAlerting:
			iMessageHandler.PrintMessage( KTransferAlerting() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetCallInfoL
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetCallInfoL( 
	CTelephony::TCallSelectionV1& aCallSelection, 
	CTelephony::TCallInfoV1& aCallInfo, 
	CTelephony::TRemotePartyInfoV1& aRemotePartyInfo )
	{
	TBuf<KMessageHandlerMaxMessageSize> buffer; 
	
	// Call selection
	iMessageHandler.PrintMessage( KCallSelection() ); 
	// Call selection: line
	iMessageHandler.PrintMessage( KLine() ); 	
	switch( aCallSelection.iLine )
		{
		case CTelephony::EVoiceLine:
			iMessageHandler.PrintMessage( KVoiceLine() ); 
			break; 
		case CTelephony::EDataLine:
			iMessageHandler.PrintMessage( KDataLine() ); 
			break; 
		case CTelephony::EFaxLine:
			iMessageHandler.PrintMessage( KFaxLine() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}

	// Call selection: status
	iMessageHandler.PrintMessage( KStatus() ); 	
	switch( aCallSelection.iLine )
		{
		case CTelephony::EActiveCall:
			iMessageHandler.PrintMessage( KActiveCall() ); 
			break; 
		case CTelephony::EHeldCall:
			iMessageHandler.PrintMessage( KHeldCall() ); 
			break; 
		case CTelephony::EInProgressCall:
			iMessageHandler.PrintMessage( KInProgressCall() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}		

	// Call info 
	iMessageHandler.PrintMessage( KCallInfo() ); 
	// Call info: status
	iMessageHandler.PrintMessage( KStatus() ); 
	switch( aCallInfo.iStatus )
		{
		case CTelephony::EStatusUnknown:
			iMessageHandler.PrintMessage( KUnknown() ); 
			break; 
		case CTelephony::EStatusIdle:
			iMessageHandler.PrintMessage( KIdle() ); 
			break; 
		case CTelephony::EStatusDialling:
			iMessageHandler.PrintMessage( KDialling() ); 
			break; 
		case CTelephony::EStatusRinging:
			iMessageHandler.PrintMessage( KRinging() ); 
			break; 
		case CTelephony::EStatusAnswering:
			iMessageHandler.PrintMessage( KAnswering() ); 
			break; 
		case CTelephony::EStatusConnecting:
			iMessageHandler.PrintMessage( KConnecting() ); 
			break; 
		case CTelephony::EStatusConnected:
			iMessageHandler.PrintMessage( KConnected() ); 
			break; 
		case CTelephony::EStatusReconnectPending:
			iMessageHandler.PrintMessage( KReconnectPending() ); 
			break; 
		case CTelephony::EStatusDisconnecting:
			iMessageHandler.PrintMessage( KDisconnecting() ); 
			break; 
		case CTelephony::EStatusHold:
			iMessageHandler.PrintMessage( KOnHold() ); 
			break; 
		case CTelephony::EStatusTransferring:
			iMessageHandler.PrintMessage( KTransferring() ); 
			break; 
		case CTelephony::EStatusTransferAlerting:
			iMessageHandler.PrintMessage( KTransferAlerting() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}

	// Call info: start time
	iMessageHandler.PrintMessage( KStartTime() ); 	        
    TTime startTime( aCallInfo.iStartTime ); 
    startTime.FormatL( buffer, KTimeFormatLong() );               
    iMessageHandler.PrintMessage( buffer );

	// Call info: duration
	iMessageHandler.PrintMessage( KDuration() ); 	
	buffer.Num( aCallInfo.iDuration.Int() ); 
	iMessageHandler.PrintMessage( buffer ); 		

	// Call info: dialled party
	iMessageHandler.PrintMessage( KDialledParty() ); 		
	iMessageHandler.PrintMessage( KTypeOfNumber() ); 	
	switch(  aCallInfo.iDialledParty.iTypeOfNumber )
		{
		case CTelephony::EUnknownNumber:
			iMessageHandler.PrintMessage( KUnknownNumber() ); 
			break; 
		case CTelephony::EInternationalNumber:
			iMessageHandler.PrintMessage( KInternationalNumber() ); 
			break; 
		case CTelephony::ENationalNumber:
			iMessageHandler.PrintMessage( KNationalNumber() ); 
			break; 
		case CTelephony::ENetworkSpecificNumber:
			iMessageHandler.PrintMessage( KNetworkSpecificNumber() ); 
			break; 
		case CTelephony::ESubscriberNumber:
			iMessageHandler.PrintMessage( KSubscriberNumber() ); 
			break; 
		case CTelephony::EAlphanumericNumber:
			iMessageHandler.PrintMessage( KAlphanumericNumber() ); 
			break; 
		case CTelephony::EAbbreviatedNumber:
			iMessageHandler.PrintMessage( KAbbreviatedNumber() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	iMessageHandler.PrintMessage( KNumberPlan() ); 		
	switch(  aCallInfo.iDialledParty.iNumberPlan )
		{
		case CTelephony::EUnknownNumberingPlan:
			iMessageHandler.PrintMessage( KUnknownNumberingPlan() ); 
			break; 
		case CTelephony::EIsdnNumberPlan:
			iMessageHandler.PrintMessage( KIsdnNumberPlan() ); 
			break; 
		case CTelephony::EDataNumberPlan:
			iMessageHandler.PrintMessage( KDataNumberPlan() ); 
			break; 
		case CTelephony::ETelexNumberPlan:
			iMessageHandler.PrintMessage( KTelexNumberPlan() ); 
			break; 
		case CTelephony::EServiceCentreSpecificPlan1:
			iMessageHandler.PrintMessage( KServiceCentreSpecificPlan1() ); 
			break; 
		case CTelephony::EServiceCentreSpecificPlan2:
			iMessageHandler.PrintMessage( KServiceCentreSpecificPlan2() ); 
			break; 
		case CTelephony::ENationalNumberPlan:
			iMessageHandler.PrintMessage( KNationalNumberPlan() ); 
			break; 
		case CTelephony::EPrivateNumberPlan:
			iMessageHandler.PrintMessage( KPrivateNumberPlan() ); 
			break; 
		case CTelephony::EERMESNumberPlan:
			iMessageHandler.PrintMessage( KErmesNumberPlan() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	iMessageHandler.PrintMessage( KDialledPartyTelNumber() ); 	
	iMessageHandler.PrintMessage( aCallInfo.iDialledParty.iTelNumber ); 		

	// Call info: exit code
	iMessageHandler.PrintMessage( KExitCode() ); 	
	buffer.Num( aCallInfo.iExitCode ); 
	iMessageHandler.PrintMessage( buffer ); 		
	
	// Call info: security
	iMessageHandler.PrintMessage( KSecurity() ); 			
	switch(  aCallInfo.iSecurity )
		{
		case CTelephony::ECipheringOff:
			iMessageHandler.PrintMessage( KCipheringOff() ); 
			break; 
		case CTelephony::ECipheringGSM:
			iMessageHandler.PrintMessage( KCipheringGSM() ); 
			break; 
		case CTelephony::ECipheringWCDMA:
			iMessageHandler.PrintMessage( KCipheringWCDMA() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}

	// Call info: call id
	iMessageHandler.PrintMessage( KDialledPartyCallId() ); 	
	buffer.Num( aCallInfo.iCallId ); 
	iMessageHandler.PrintMessage( buffer ); 
	
	// Remote party info 
	iMessageHandler.PrintMessage( KRemotePartyInfo() ); 
	// Remote party info: remote id status 
	iMessageHandler.PrintMessage( KRemoteIdStatus() ); 
	switch( aRemotePartyInfo.iRemoteIdStatus )
		{
		case CTelephony::ERemoteIdentityUnknown:
			iMessageHandler.PrintMessage( KRemoteIdentityUnknown() ); 
			break; 
		case CTelephony::ERemoteIdentityAvailable:
			iMessageHandler.PrintMessage( KRemoteIdentityAvailable() ); 
			break; 
		case CTelephony::ERemoteIdentitySuppressed:
			iMessageHandler.PrintMessage( KRemoteIdentitySuppressed() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}

	// Remote party info: calling name 
	iMessageHandler.PrintMessage( KCallingName() ); 
	iMessageHandler.PrintMessage( aRemotePartyInfo.iCallingName ); 

	// Remote party info: remote number
	iMessageHandler.PrintMessage( KRemoteNumber() ); 		
	iMessageHandler.PrintMessage( KTypeOfNumber() ); 	
	switch(  aRemotePartyInfo.iRemoteNumber.iTypeOfNumber )
		{
		case CTelephony::EUnknownNumber:
			iMessageHandler.PrintMessage( KUnknownNumber() ); 
			break; 
		case CTelephony::EInternationalNumber:
			iMessageHandler.PrintMessage( KInternationalNumber() ); 
			break; 
		case CTelephony::ENationalNumber:
			iMessageHandler.PrintMessage( KNationalNumber() ); 
			break; 
		case CTelephony::ENetworkSpecificNumber:
			iMessageHandler.PrintMessage( KNetworkSpecificNumber() ); 
			break; 
		case CTelephony::ESubscriberNumber:
			iMessageHandler.PrintMessage( KSubscriberNumber() ); 
			break; 
		case CTelephony::EAlphanumericNumber:
			iMessageHandler.PrintMessage( KAlphanumericNumber() ); 
			break; 
		case CTelephony::EAbbreviatedNumber:
			iMessageHandler.PrintMessage( KAbbreviatedNumber() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	iMessageHandler.PrintMessage( KNumberPlan() ); 		
	switch(  aRemotePartyInfo.iRemoteNumber.iNumberPlan )
		{
		case CTelephony::EUnknownNumberingPlan:
			iMessageHandler.PrintMessage( KUnknownNumberingPlan() ); 
			break; 
		case CTelephony::EIsdnNumberPlan:
			iMessageHandler.PrintMessage( KIsdnNumberPlan() ); 
			break; 
		case CTelephony::EDataNumberPlan:
			iMessageHandler.PrintMessage( KDataNumberPlan() ); 
			break; 
		case CTelephony::ETelexNumberPlan:
			iMessageHandler.PrintMessage( KTelexNumberPlan() ); 
			break; 
		case CTelephony::EServiceCentreSpecificPlan1:
			iMessageHandler.PrintMessage( KServiceCentreSpecificPlan1() ); 
			break; 
		case CTelephony::EServiceCentreSpecificPlan2:
			iMessageHandler.PrintMessage( KServiceCentreSpecificPlan2() ); 
			break; 
		case CTelephony::ENationalNumberPlan:
			iMessageHandler.PrintMessage( KNationalNumberPlan() ); 
			break; 
		case CTelephony::EPrivateNumberPlan:
			iMessageHandler.PrintMessage( KPrivateNumberPlan() ); 
			break; 
		case CTelephony::EERMESNumberPlan:
			iMessageHandler.PrintMessage( KErmesNumberPlan() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	iMessageHandler.PrintMessage( KDialledPartyTelNumber() ); 	
	iMessageHandler.PrintMessage( aRemotePartyInfo.iRemoteNumber.iTelNumber ); 		

	// Remote party info: call direction
	iMessageHandler.PrintMessage( KCallDirection() ); 
	switch( aRemotePartyInfo.iRemoteIdStatus )
		{
		case CTelephony::EDirectionUnknown:
			iMessageHandler.PrintMessage( KDirectionUnknown() ); 
			break; 
		case CTelephony::EMobileOriginated:
			iMessageHandler.PrintMessage( KMobileOriginated() ); 
			break; 
		case CTelephony::EMobileTerminated:
			iMessageHandler.PrintMessage( KMobileTerminated() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}	
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetNetworkRegistrationStatus
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetNetworkRegistrationStatus(
	CTelephony::TNetworkRegistrationV1& aNetworkRegistration )
	{
	// Registration status
	iMessageHandler.PrintMessage( KNetworkRegistrationStatus() ); 	
	switch( aNetworkRegistration.iRegStatus )
		{
		case CTelephony::ERegistrationUnknown: 
			iMessageHandler.PrintMessage( KUnknown() ); 	
			break; 
		case CTelephony::ENotRegisteredNoService: 
			iMessageHandler.PrintMessage( KNotRegisteredNoService() ); 	
			break; 
		case CTelephony::ENotRegisteredEmergencyOnly: 
			iMessageHandler.PrintMessage( KNotRegisteredNoService() ); 	
			break; 
		case CTelephony::ENotRegisteredSearching: 
			iMessageHandler.PrintMessage( KNotRegisteredSearched() ); 	
			break; 
		case CTelephony::ERegisteredBusy: 
			iMessageHandler.PrintMessage( KRegisteredBusy() ); 	
			break; 
		case CTelephony::ERegisteredOnHomeNetwork: 
			iMessageHandler.PrintMessage( KRegisteredOnHomeNetwork() ); 	
			break; 
		case CTelephony::ERegistrationDenied: 
			iMessageHandler.PrintMessage( KRegistrationDenied() ); 	
			break; 
		case CTelephony::ERegisteredRoaming: 
			iMessageHandler.PrintMessage( KRegisteredRoaming() ); 	
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	}	
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetCurrentNetworkInfo
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetCurrentNetworkInfo(
    CTelephony::TNetworkInfoV1& aNetworkInfo )
    {
    TBuf<KMessageHandlerMaxMessageSize> buffer; 
    
	// Network Info: Mode 	
	iMessageHandler.PrintMessage( KNetworkMode() ); 
	switch( aNetworkInfo.iMode )
		{
		case CTelephony::ENetworkModeUnknown:
		    iMessageHandler.PrintMessage( KUnknown() ); 
			break; 
		case CTelephony::ENetworkModeUnregistered:
			iMessageHandler.PrintMessage( KUnregistered() ); 
			break; 
		case CTelephony::ENetworkModeGsm:
			iMessageHandler.PrintMessage( KGSM() ); 
			break; 
		case CTelephony::ENetworkModeAmps:
			iMessageHandler.PrintMessage( KAMPS() ); 
			break; 
		case CTelephony::ENetworkModeCdma95:
			iMessageHandler.PrintMessage( KCDMA95() ); 
			break; 
		case CTelephony::ENetworkModeCdma2000:
			iMessageHandler.PrintMessage( KCDMA2000() ); 
			break; 
		case CTelephony::ENetworkModeWcdma:
			iMessageHandler.PrintMessage( KWCDMA() ); 
			break; 
		case CTelephony::ENetworkModeTdcdma:
			iMessageHandler.PrintMessage( KTDCDMA() ); 
			break; 	
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break; 				
		}

	// Network Info: Status 	
	iMessageHandler.PrintMessage( KNetworkStatus() ); 
	switch( aNetworkInfo.iStatus )
		{
		case CTelephony::ENetworkStatusUnknown:
			iMessageHandler.PrintMessage( KUnknown() ); 
			break; 
		case CTelephony::ENetworkStatusAvailable:
			iMessageHandler.PrintMessage( KAvailable() ); 
			break; 
		case CTelephony::ENetworkStatusCurrent:
			iMessageHandler.PrintMessage( KCurrent() ); 
			break; 
		case CTelephony::ENetworkStatusForbidden:
			iMessageHandler.PrintMessage( KForbidden() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break; 				
		}		

	// Network Info: Country Code	
	iMessageHandler.PrintMessage( KCountryCode() );
	iMessageHandler.PrintMessage( aNetworkInfo.iCountryCode );
	// Network Info: Network Id	
	iMessageHandler.PrintMessage( KNetworkId() ); 	
	iMessageHandler.PrintMessage( aNetworkInfo.iNetworkId );
	// Network Info: Network Display Tag	
	iMessageHandler.PrintMessage( KDisplayTag() );
	iMessageHandler.PrintMessage( aNetworkInfo.iDisplayTag );   	
	// Network Info: Network Display Tag	
	iMessageHandler.PrintMessage( KShortName() ); 	
	iMessageHandler.PrintMessage( aNetworkInfo.iShortName ); 
	// Network Info: Long Name	
	iMessageHandler.PrintMessage( KLongName() ); 
	iMessageHandler.PrintMessage( aNetworkInfo.iLongName ); 
	
	// Network Info: Band Info 
	iMessageHandler.PrintMessage( KBandInfo() ); 
	switch( aNetworkInfo.iBandInfo )
		{
		case CTelephony::EBandUnknown:
			iMessageHandler.PrintMessage( KUnknown() ); 	
			break; 
		case CTelephony::E800BandA:
			iMessageHandler.PrintMessage( K800A() ); 	
			break; 
		case CTelephony::E800BandB:
			iMessageHandler.PrintMessage( K800B() ); 	
			break; 
		case CTelephony::E800BandC:
			iMessageHandler.PrintMessage( K800C() ); 	
			break; 
		case CTelephony::E1900BandA:
			iMessageHandler.PrintMessage( K1900A() ); 	
			break; 
		case CTelephony::E1900BandB:
			iMessageHandler.PrintMessage( K1900B() ); 	
			break; 
		case CTelephony::E1900BandC:
			iMessageHandler.PrintMessage( K1900C() ); 	
			break; 
		case CTelephony::E1900BandD:
			iMessageHandler.PrintMessage( K1900D() ); 	
			break; 				
		case CTelephony::E1900BandE:
			iMessageHandler.PrintMessage( K1900E() ); 	
			break; 				
		case CTelephony::E1900BandF:
			iMessageHandler.PrintMessage( K1900F() ); 	
			break; 	
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break; 				
		}

	// Network Info: CDMA SID	
	iMessageHandler.PrintMessage( KCDMASID() ); 
	iMessageHandler.PrintMessage( aNetworkInfo.iCdmaSID );

	// Network Info: Access 
	iMessageHandler.PrintMessage( KNetworkAccess() ); 
	switch( aNetworkInfo.iAccess )
		{
		case CTelephony::ENetworkAccessUnknown:
			iMessageHandler.PrintMessage( KUnknown() ); 
			break; 
		case CTelephony::ENetworkAccessGsm:
			iMessageHandler.PrintMessage( KGSM() ); 
			break; 
		case CTelephony::ENetworkAccessGsmCompact:
			iMessageHandler.PrintMessage( KGSMCompact() ); 
			break; 
		case CTelephony::ENetworkAccessUtran:
			iMessageHandler.PrintMessage( KUTRAN() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break; 				
		}
			
	// Network Info: Area Known  
	iMessageHandler.PrintMessage( KArea() ); 
	switch( aNetworkInfo.iAreaKnown )
		{
		case ETrue:
			iMessageHandler.PrintMessage( KKnown() ); 
			break; 
		case EFalse:
			iMessageHandler.PrintMessage( KUnknown() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break; 								
		}
		
	// Network Info: Location Area Code
	iMessageHandler.PrintMessage( KLocationAreaCode() );
	buffer.Num( aNetworkInfo.iLocationAreaCode ); 
	iMessageHandler.PrintMessage( buffer ); 
	// Network Info: Cell Id		
	iMessageHandler.PrintMessage( KCellId() );
	buffer.Num( aNetworkInfo.iCellId ); 
	iMessageHandler.PrintMessage( buffer );  	
    }

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetCurrentNetworkName
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetCurrentNetworkName(
	CTelephony::TNetworkNameV1& aNetworkName )
	{
	// Network name
	iMessageHandler.PrintMessage( KNetworkName() ); 			
	iMessageHandler.PrintMessage( aNetworkName.iNetworkName ); 			
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetOperatorName
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetOperatorName(
	CTelephony::TOperatorNameV1& aOperatorName )
	{
	// Operator name 
	iMessageHandler.PrintMessage( KOperatorName() ); 			
	iMessageHandler.PrintMessage( aOperatorName.iOperatorName ); 			
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetCallForwardingStatus
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetCallForwardingStatus(
 	CTelephony::TCallForwardingCondition& /*aCallForwardingCondition*/, 
 	CTelephony::TCallForwardingSupplServicesV1& aCallForwardingStatus, 
 	CTelephony::TServiceGroup& aServiceGroup )		    		
	{
	// Call forwarding condition
	iMessageHandler.PrintMessage( KCallForwardingCondition() ); 
	switch( aCallForwardingStatus.iCallForwardingCondition )
		{
		case CTelephony::ECallForwardingUnconditional:
			iMessageHandler.PrintMessage( KUnconditional() ); 
			break; 
		case CTelephony::ECallForwardingBusy:
			iMessageHandler.PrintMessage( KBusy() ); 
			break; 
		case CTelephony::ECallForwardingNoReply:
			iMessageHandler.PrintMessage( KNoReply() ); 
			break; 
		case CTelephony::ECallForwardingNotReachable:
			iMessageHandler.PrintMessage( KNotReachable() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}	
		
	// Call forwarding status
	iMessageHandler.PrintMessage( KCallForwardingStatus() ); 
	switch( aCallForwardingStatus.iCallForwarding )
		{
		case CTelephony::EStatusActive:
			iMessageHandler.PrintMessage( KActive() ); 
			break; 
		case CTelephony::ENotActive:
			iMessageHandler.PrintMessage( KNotActive() ); 
			break; 
		case CTelephony::ENotProvisioned:
			iMessageHandler.PrintMessage( KNotProvisioned() ); 
			break; 
		case CTelephony::ENotAvailable:
			iMessageHandler.PrintMessage( KNotAvailable() ); 
			break; 
		case CTelephony::EUnknown:
			iMessageHandler.PrintMessage( KUnknown() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
		
	// Service group
	iMessageHandler.PrintMessage( KServiceGroup() ); 
	switch( aServiceGroup )
		{
		case CTelephony::EVoiceService:
			iMessageHandler.PrintMessage( KVoiceService() ); 
			break; 
		case CTelephony::EFaxService:
			iMessageHandler.PrintMessage( KFaxService() ); 
			break; 
		case CTelephony::EDataService:
			iMessageHandler.PrintMessage( KDataService() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}		
	}	

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetCallBarringStatus
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetCallBarringStatus( 
 	CTelephony::TCallBarringCondition& /*aCallBarringCondition*/, 		 	
 	CTelephony::TCallBarringSupplServicesV1& aCallBarringStatus,
 	CTelephony::TServiceGroup& aServiceGroup )
	{
	// Barring condition
	iMessageHandler.PrintMessage( KBarringCondition() ); 
	switch( aCallBarringStatus.iCallBarringCondition )
		{
		case CTelephony::EBarAllIncoming:
			iMessageHandler.PrintMessage( KAllIncoming() ); 
			break; 
		case CTelephony::EBarIncomingRoaming:
			iMessageHandler.PrintMessage( KIncomingRoaming() ); 
			break; 
		case CTelephony::EBarAllOutgoing:
			iMessageHandler.PrintMessage( KAllOutgoing() ); 
			break; 
		case CTelephony::EBarOutgoingInternational:
			iMessageHandler.PrintMessage( KOutgoingInternational() ); 
			break; 
		case CTelephony::EBarOutgoingInternationalExHC:
			iMessageHandler.PrintMessage( KOutgoingInternationalExceptToHC() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}		
		
	// Call barring status	
	iMessageHandler.PrintMessage( KCallBarringStatus() ); 
	switch( aCallBarringStatus.iCallBarring )
		{
		case CTelephony::EStatusActive:
			iMessageHandler.PrintMessage( KActive() ); 
			break; 
		case CTelephony::ENotActive:
			iMessageHandler.PrintMessage( KNotActive() ); 
			break; 
		case CTelephony::ENotProvisioned:
			iMessageHandler.PrintMessage( KNotProvisioned() ); 
			break; 
		case CTelephony::ENotAvailable:
			iMessageHandler.PrintMessage( KNotAvailable() ); 
			break; 
		case CTelephony::EUnknown:
			iMessageHandler.PrintMessage( KUnknown() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}

	// Service group
	iMessageHandler.PrintMessage( KServiceGroup() ); 
	switch( aServiceGroup )
		{
		case CTelephony::EVoiceService:
			iMessageHandler.PrintMessage( KVoiceService() ); 
			break; 
		case CTelephony::EFaxService:
			iMessageHandler.PrintMessage( KFaxService() ); 
			break; 
		case CTelephony::EDataService:
			iMessageHandler.PrintMessage( KDataService() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}	
	}	

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetCallWaitingStatus
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetCallWaitingStatus( 		 	
 	CTelephony::TCallWaitingSupplServicesV1& aCallWaitingStatus,
 	CTelephony::TServiceGroup& aServiceGroup )
	{
	// Service group
	iMessageHandler.PrintMessage( KServiceGroup() ); 
	switch( aServiceGroup )
		{
		case CTelephony::EVoiceService:
			iMessageHandler.PrintMessage( KVoiceService() ); 
			break; 
		case CTelephony::EFaxService:
			iMessageHandler.PrintMessage( KFaxService() ); 
			break; 
		case CTelephony::EDataService:
			iMessageHandler.PrintMessage( KDataService() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}	

	// Call waiting status	
	iMessageHandler.PrintMessage( KCallWaitingStatus() ); 
	switch( aCallWaitingStatus.iCallWaiting )
		{
		case CTelephony::EStatusActive:
			iMessageHandler.PrintMessage( KActive() ); 
			break; 
		case CTelephony::ENotActive:
			iMessageHandler.PrintMessage( KNotActive() ); 
			break; 
		case CTelephony::ENotProvisioned:
			iMessageHandler.PrintMessage( KNotProvisioned() ); 
			break; 
		case CTelephony::ENotAvailable:
			iMessageHandler.PrintMessage( KNotAvailable() ); 
			break; 
		case CTelephony::EUnknown:
			iMessageHandler.PrintMessage( KUnknown() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	}	

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetIdentityServiceStatus
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetIdentityServiceStatus( 		 	
 	CTelephony::TIdentityService& aIdentityService,
 	CTelephony::TIdentityServiceV1& aIdentityServiceStatus )
 	{
	// Identity service
	iMessageHandler.PrintMessage( KIdentityService() ); 
	switch( aIdentityService )
		{
		case CTelephony::EIdServiceUnspecified:
			iMessageHandler.PrintMessage( KUnspecified() ); 
			break; 
		case CTelephony::EIdServiceCallerPresentation:
			iMessageHandler.PrintMessage( KCallerPresentation() ); 
			break; 
		case CTelephony::EIdServiceCallerRestriction:
			iMessageHandler.PrintMessage( KCallerRestriction() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}	

	// Identity service status	
	iMessageHandler.PrintMessage( KIdentityServiceStatus() ); 
	switch( aIdentityServiceStatus.iIdentityStatus )
		{
		case CTelephony::EIdServiceActivePermanent:
			iMessageHandler.PrintMessage( KActivePermanent() ); 
			break; 
		case CTelephony::EIdServiceActiveDefaultRestricted:
			iMessageHandler.PrintMessage( KActiveDefaultRestricted() ); 
			break; 
		case CTelephony::EIdServiceActiveDefaultAllowed:
			iMessageHandler.PrintMessage( KActiveDefaultAllowed() ); 
			break; 
		case CTelephony::EIdServiceNotProvisioned:
			iMessageHandler.PrintMessage( KNotProvisioned() ); 
			break; 
		case CTelephony::EIdServiceUnknown:
			iMessageHandler.PrintMessage( KUnknown() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	}	

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseCallId
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseCallId( 
	CTelephony::TCallId& aCallId )
	{
	// Call id
	iMessageHandler.PrintMessage( KCallId() ); 
	switch( aCallId )
		{
		case CTelephony::EISVCall1:
			iMessageHandler.PrintMessage( KIsvCall1() ); 
			break; 
		case CTelephony::EISVCall2:
			iMessageHandler.PrintMessage( KIsvCall2() ); 
			break; 
		case CTelephony::EISVMaxNumOfCalls:
			iMessageHandler.PrintMessage( KIsvMaxNumberOfCalls() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	}
		
// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseDialNewCall
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseDialNewCall( 
 	CTelephony::TCallParamsV1& aCallParams, 
 	CTelephony::TTelNumber& aTelNumber, 
	CTelephony::TCallId& aCallId, 
	CTelephony::TPhoneLine& aPhoneLine )
	{
	// Call params
	iMessageHandler.PrintMessage( KCallParams() ); 
	switch( aCallParams.iIdRestrict )
		{
		case CTelephony::EIdRestrictDefault:
			iMessageHandler.PrintMessage( KCLIRRestrictDefault() ); 
			break; 
		case CTelephony::ESendMyId:
			iMessageHandler.PrintMessage( KCLIRSendMyId() ); 
			break; 
		case CTelephony::EDontSendMyId:
			iMessageHandler.PrintMessage( KCLIRDontSendMyId() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}	

	// Telelphone number 
	iMessageHandler.PrintMessage( KTelNumber() ); 
	iMessageHandler.PrintMessage( aTelNumber ); 

	// Call id	
	ParseCallId( aCallId );

	// Phone line
	iMessageHandler.PrintMessage( KPhoneLine() ); 
	switch( aPhoneLine )
		{
		case CTelephony::EVoiceLine:
			iMessageHandler.PrintMessage( KVoiceLine() ); 
			break; 
		case CTelephony::EDataLine:
			iMessageHandler.PrintMessage( KDataLine() ); 
			break; 
		case CTelephony::EFaxLine:
			iMessageHandler.PrintMessage( KFaxLine() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	}	

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetCallDynamicCaps
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetCallDynamicCaps( 		 	
	CTelephony::TCallId& aCallId, 
	CTelephony::TCallCapsV1& aCallCaps )						 	
	{
	TBuf<KMessageHandlerMaxMessageSize> buffer; 
	
	// Call id
	ParseCallId( aCallId );

	// Call dynamic caps
	iMessageHandler.PrintMessage( KCallDynamicCaps() ); 
    // the capability is sum of flags so check each capability
    if( aCallCaps.iControlCaps & CTelephony::KCapsHold )
    	{
    	buffer.Append( KHold() );
    	}
    if( aCallCaps.iControlCaps & CTelephony::KCapsResume )
    	{
    	buffer.Append( KResume() );
    	}
    if( aCallCaps.iControlCaps & CTelephony::KCapsSwap )
    	{
    	buffer.Append( KSwap() );
    	}
    iMessageHandler.PrintMessage( buffer );     	
	}
	
// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseGetCallStatus
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseGetCallStatus( 		 	
	CTelephony::TCallId& aCallId, 
	CTelephony::TCallStatusV1& aCallStatus )
	{	
	// Call id
	ParseCallId( aCallId ); 	
	// Call status 
	ParseCallStatus( aCallStatus ); 
	}

// -----------------------------------------------------------------------------
// CIsvTelephonyTestParser::ParseCallStatus
// -----------------------------------------------------------------------------
//
void CIsvTelephonyTestParser::ParseCallStatus( 		 		
	CTelephony::TCallStatusV1& aCallStatus )
	{
	TBuf<KMessageHandlerMaxMessageSize> buffer; 
	
	// Call status
	iMessageHandler.PrintMessage( KCallStatus() ); 
	switch( aCallStatus.iStatus )
		{
		case CTelephony::EStatusUnknown:
			iMessageHandler.PrintMessage( KUnknown() ); 
			break; 
		case CTelephony::EStatusIdle:
			iMessageHandler.PrintMessage( KIdle() ); 
			break; 
		case CTelephony::EStatusDialling:
			iMessageHandler.PrintMessage( KDialling() ); 
			break; 
		case CTelephony::EStatusRinging:
			iMessageHandler.PrintMessage( KRinging() ); 
			break; 
		case CTelephony::EStatusAnswering:
			iMessageHandler.PrintMessage( KAnswering() ); 
			break; 
		case CTelephony::EStatusConnecting:
			iMessageHandler.PrintMessage( KConnecting() ); 
			break; 
		case CTelephony::EStatusConnected:
			iMessageHandler.PrintMessage( KConnected() ); 
			break; 
		case CTelephony::EStatusReconnectPending:
			iMessageHandler.PrintMessage( KReconnectPending() ); 
			break; 
		case CTelephony::EStatusDisconnecting:
			iMessageHandler.PrintMessage( KDisconnecting() ); 
			break; 
		case CTelephony::EStatusHold:
			iMessageHandler.PrintMessage( KOnHold() ); 
			break; 
		case CTelephony::EStatusTransferring:
			iMessageHandler.PrintMessage( KTransferring() ); 
			break; 
		case CTelephony::EStatusTransferAlerting:
			iMessageHandler.PrintMessage( KTransferAlerting() ); 
			break; 
		default: 
			iMessageHandler.PrintMessage( KUnknownEnumValueError() ); 
			break;
		}
	}	
// ========================== OTHER EXPORTED FUNCTIONS =========================

//  End of File  
