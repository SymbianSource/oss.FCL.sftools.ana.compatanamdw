/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  TestScripter Class which has the list of test cases
*
*/



// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "testlbslocacquisition.h"
#include "testpositionserver.h"
#include "testpositioner.h"
#include "testpositionInfo.h"
#include "testpositioncourseinfo.h"
#include "testpositiongenericinfo.h"

#include "testCoordinate.h"
#include "testlocality.h"
#include "testposition.h"
#include "testcourse.h"
#include "testpositionquality.h"
#include "testpositionmodule.h"
#include "testsatellite.h"
#include "testcriteria.h"
#include "testrequestor.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestLbsLocAcquisition::Delete() 
    {	
    if(iPositioner)
    	{
    	delete iPositioner;	
    	iPositioner = NULL;
    	}	
    if(iPosServer)
    	{
    	delete iPosServer;	
    	iPosServer = NULL;
    	}	
    if(iPositionInfo)
    	{
    	delete iPositionInfo;	
    	iPositionInfo = NULL;
    	}	
    if(iPositionCourseInfo)
    	{
    	delete iPositionCourseInfo;	
    	iPositionCourseInfo = NULL;
    	}	
    if(iPositionGenericInfo)
    	{
    	delete iPositionGenericInfo;	
    	iPositionGenericInfo = NULL;
    	}
    }

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::RunMethodL( 
    CStifItemParser& aItem ) 
    { 

     static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "Connect", CTestLbsLocAcquisition::Connect ),
     	ENTRY( "ConnectPanic", CTestLbsLocAcquisition::ConnectPanic ),   
        ENTRY( "VersionCheck", CTestLbsLocAcquisition::VersionCheck ),    
        ENTRY( "Disconnect", CTestLbsLocAcquisition::Disconnect ),
        ENTRY( "DisconnectPanicOutstanding", CTestLbsLocAcquisition::DisconnectPanicOutstandingL ),
        ENTRY( "GetDefaultModule", CTestLbsLocAcquisition::GetDefaultModule ),
        ENTRY( "GetDefaultModulePanicNoServer", CTestLbsLocAcquisition::GetDefaultModulePanicNoServer ), 
        ENTRY( "GetModuleNum", CTestLbsLocAcquisition::GetModuleNum ),               
        ENTRY( "GetModuleNumPanicNoServer", CTestLbsLocAcquisition::GetModuleNumPanicNoServer ),   
        ENTRY( "GetModuleInfoIndex", CTestLbsLocAcquisition::GetModuleInfoIndexL ), 
        ENTRY( "GetModuleInfoIndexPanicNoServer", CTestLbsLocAcquisition::GetModuleInfoIndexPanicNoServerL ),
        ENTRY( "GetModuleInfoId", CTestLbsLocAcquisition::GetModuleInfoIdL ),
        ENTRY( "GetModuleInfoIdPanicNoServer", CTestLbsLocAcquisition::GetModuleInfoIdPanicNoServerL ),
        ENTRY( "GetModuleStatus", CTestLbsLocAcquisition::GetModuleStatusL ),
        ENTRY( "GetModuleChangeNotification", CTestLbsLocAcquisition::GetModuleChangeNotificationL ),
        ENTRY( "GetModuleChangeNotificationCancel", CTestLbsLocAcquisition::GetModuleChangeNotificationCancelL ),
        ENTRY( "GetModuleChangeNotificationPanicNoServer", CTestLbsLocAcquisition::GetModuleChangeNotificationPanicNoServerL ),
        ENTRY( "GetModuleChangeNotificationPanicDuplicate", CTestLbsLocAcquisition::GetModuleChangeNotificationPanicDuplicateL ),
        ENTRY( "CancelModuleStatusRequest", CTestLbsLocAcquisition::CancelModuleStatusRequest ),
        ENTRY( "CancelModuleStatusRequestPanicNoConnect", CTestLbsLocAcquisition::CancelModuleStatusRequestPanicNoConnect ),        
        ENTRY( "OpenPositioner", CTestLbsLocAcquisition::OpenPositioner ),
        ENTRY( "OpenPositionerByCriteria", CTestLbsLocAcquisition::OpenPositionerByCriteria ),
        ENTRY( "OpenPositionerPanicNotClosed", CTestLbsLocAcquisition::OpenPositionerPanicNotClosed ),
        ENTRY( "OpenPositionerPanicBadHandle", CTestLbsLocAcquisition::OpenPositionerPanicBadHandle ),
        ENTRY( "ClosePositioner", CTestLbsLocAcquisition::ClosePositioner ),   
        ENTRY( "ClosePositionerPanicNotCancelled", CTestLbsLocAcquisition::ClosePositionerPanicNotCancelled ), 
        ENTRY( "SetRequestor", CTestLbsLocAcquisition::SetRequestorL ),
        ENTRY( "SetRequestorPanicNoOpen", CTestLbsLocAcquisition::SetRequestorPanicNoOpenL ),
        ENTRY( "SetRequestorstack", CTestLbsLocAcquisition::SetRequestorStackL ),
        ENTRY( "SetRequestorStackPanicNoOpen", CTestLbsLocAcquisition::SetRequestorStackPanicNoOpenL ),        
        ENTRY( "SetUpdateOp", CTestLbsLocAcquisition::SetUpdateOpL ),
        ENTRY( "SetUpdateOpPanicNoOpen", CTestLbsLocAcquisition::SetUpdateOpPanicNoOpenL ),  
        ENTRY( "GetUpdateOp", CTestLbsLocAcquisition::GetUpdateOpL ),
        ENTRY( "GetUpdateOpPanicNoOpen", CTestLbsLocAcquisition::GetUpdateOpPanicNoOpenL ),
        ENTRY( "GetLastKnownPostion", CTestLbsLocAcquisition::GetLastKnownPostionL ),        
        ENTRY( "GetLastKnownPostionCancel", CTestLbsLocAcquisition::GetLastKnownPostionCancelL ),
        ENTRY( "GetLastKnownPostionPanicNoOpen", CTestLbsLocAcquisition::GetLastKnownPostionPanicNoOpenL ),
        ENTRY( "CancelGetLastKnownPostion", CTestLbsLocAcquisition::CancelGetLastKnownPostionL ),
        ENTRY( "CancelGetLastKnownPostionPanicNoConnect", CTestLbsLocAcquisition::CancelGetLastKnownPostionPanicNoConnectL ),        
        ENTRY( "GetPositionInfo", CTestLbsLocAcquisition::GetPositionInfoL ),
        ENTRY( "GetPositionInfoCancel", CTestLbsLocAcquisition::GetPositionInfoCancelL ),
        ENTRY( "GetPositionInfoPanicNoOpen", CTestLbsLocAcquisition::GetPositionInfoPanicNoOpenL ),
        ENTRY( "GetPositionInfoPanicDuplicate", CTestLbsLocAcquisition::GetPositionInfoPanicDuplicateL ),
        ENTRY( "CancelGetPositionInfo", CTestLbsLocAcquisition::CancelGetPositionInfoL ),
        ENTRY( "CancelGetPositionInfoPanicNoConnect", CTestLbsLocAcquisition::CancelGetPositionInfoPanicNoConnectL ),        
        ENTRY( "PositionerExtendedInterfaceL", CTestLbsLocAcquisition::PositionerExtendedInterfaceL ),        
        ENTRY( "DeleteLastKnownPostionCache", CTestLbsLocAcquisition::DeleteLastKnownPostionCacheL),
        ENTRY( "CheckModuleId", CTestLbsLocAcquisition::CheckModuleIdL ),
        ENTRY( "CheckUpdateType", CTestLbsLocAcquisition::CheckUpdateTypeL ),
        ENTRY( "CheckPosition", CTestLbsLocAcquisition::CheckPosition ),
        ENTRY( "CheckCourse", CTestLbsLocAcquisition::CheckCourse ),
        ENTRY( "CheckNewL", CTestLbsLocAcquisition::CheckNewL ),
        ENTRY( "CheckRequestedFields", CTestLbsLocAcquisition::CheckRequestedFieldsL ),        
        ENTRY( "CheckOrderOfRequestedField", CTestLbsLocAcquisition::CheckOrderOfRequestedFieldL ),
        ENTRY( "CheckClearPositionData", CTestLbsLocAcquisition::CheckClearPositionDataL ),
        ENTRY( "CheckClearRequestedFields", CTestLbsLocAcquisition::CheckClearRequestedFieldsL ),
        ENTRY( "CheckSetGetValue", CTestLbsLocAcquisition::CheckSetGetValueL ),

         ENTRY( "DefaultConstructor", CTestLbsLocAcquisition::Coordinate ),
         ENTRY( "Constructor1", CTestLbsLocAcquisition::Coordinate ),
         ENTRY( "Constructor2", CTestLbsLocAcquisition::Coordinate ),
         ENTRY( "SetLatLon", CTestLbsLocAcquisition::SettingCoordinate ),
         ENTRY( "SetLatLonAlt", CTestLbsLocAcquisition::SettingCoordinate ),
         ENTRY( "SetDatum", CTestLbsLocAcquisition::SettingDatum ),
         ENTRY( "GetDistance", CTestLbsLocAcquisition::GettingDistance),
         ENTRY( "GetDistance1", CTestLbsLocAcquisition::GettingDistance),
         ENTRY( "GetBearing", CTestLbsLocAcquisition::GetBearingTo),
         ENTRY( "GetBearing1", CTestLbsLocAcquisition::GetBearingTo),
         ENTRY( "MoveCoordinate", CTestLbsLocAcquisition::MoveCoordinate),
         ENTRY( "MoveCoordinate1", CTestLbsLocAcquisition::MoveCoordinate),
         ENTRY( "LocalityDefaultConstructor", CTestLbsLocAcquisition::Locality),
         ENTRY( "LocalityConstructor1", CTestLbsLocAcquisition::Locality),
         ENTRY( "LocalityConstructor2", CTestLbsLocAcquisition::Locality),
         ENTRY( "SetGetHorizontalAcc", CTestLbsLocAcquisition::SetGetHorizontalAcc),
         ENTRY( "SetGetVerticalAcc", CTestLbsLocAcquisition::SetGetVerticalAcc),
         ENTRY( "SetGetAcc", CTestLbsLocAcquisition::SetGetAcc),
         ENTRY( "GetDistLocality1.1", CTestLbsLocAcquisition::GetDistLocality1),
         ENTRY( "GetDistLocality1.2", CTestLbsLocAcquisition::GetDistLocality1),
         ENTRY( "GetDistLocality2.1", CTestLbsLocAcquisition::GetDistLocality2),
         ENTRY( "GetDistLocality2.2", CTestLbsLocAcquisition::GetDistLocality2),
         ENTRY( "GetBearingLocality1.1", CTestLbsLocAcquisition::GetBearingLocality1),
         ENTRY( "GetBearingLocality1.2", CTestLbsLocAcquisition::GetBearingLocality1),
         ENTRY( "GetBearingLocality2.1", CTestLbsLocAcquisition::GetBearingLocality2),
         ENTRY( "GetBearingLocality2.2", CTestLbsLocAcquisition::GetBearingLocality2),
         ENTRY( "PositionDefaultConstructor", CTestLbsLocAcquisition::Position),
         ENTRY( "PositionConstructor1", CTestLbsLocAcquisition::Position),
         ENTRY( "PositionSetTime", CTestLbsLocAcquisition::PositionSetTime),
         ENTRY( "PositionSetCurrentTime", CTestLbsLocAcquisition::SettingCurrentTime),
         ENTRY( "CheckSpeed1", CTestLbsLocAcquisition::CheckSpeed),
         ENTRY( "CheckSpeed2", CTestLbsLocAcquisition::CheckSpeed1),

         ENTRY( "CourseDefaultConstructor", CTestLbsLocAcquisition::Course),
         ENTRY( "SetGetSpeed", CTestLbsLocAcquisition::SettingSpeed),
         ENTRY( "SetGetHeading", CTestLbsLocAcquisition::SettingHeading),
         ENTRY( "SetGetCourse", CTestLbsLocAcquisition::SettingCourse),
         ENTRY( "SetGetSpeedAccuracy", CTestLbsLocAcquisition::SetGetSpeedAccuracy),
         ENTRY( "SetGetHeadingAccuracy", CTestLbsLocAcquisition::SetGetHeadingAccuracy),
         ENTRY( "SetGetCourseAccuracy", CTestLbsLocAcquisition::SetGetCourseAccuracy),
         ENTRY( "DefaultPositionQuality", CTestLbsLocAcquisition::PositionQualityConstructor),
         ENTRY( "CheckPositionClassType", CTestLbsLocAcquisition::CheckPositionClassType),
         ENTRY( "CheckPositionClassSize", CTestLbsLocAcquisition::CheckPositionClassSize),
         ENTRY( "CheckCompare", CTestLbsLocAcquisition::CheckCompare),
         ENTRY( "CheckIsDefined", CTestLbsLocAcquisition::CheckIsDefined),

         ENTRY( "HighWaterMark", CTestLbsLocAcquisition::GettingHighWaterMark),

         ENTRY( "SetTimeToFirstFix1", CTestLbsLocAcquisition::SettingTimeToFirstFix),
         ENTRY( "SetTimeToFirstFix2", CTestLbsLocAcquisition::SettingTimeToFirstFix),
         ENTRY( "SetTimeToNextFix1", CTestLbsLocAcquisition::SettingTimeToNextFix),
         ENTRY( "SetTimeToNextFix2", CTestLbsLocAcquisition::SettingTimeToNextFix),
         ENTRY( "SetHorizontalAccuracy1", CTestLbsLocAcquisition::SettingHorizontalAccuracy),
         ENTRY( "SetHorizontalAccuracy2", CTestLbsLocAcquisition::SettingHorizontalAccuracy),
         ENTRY( "SetVerticalAccuracy1", CTestLbsLocAcquisition::SettingVerticalAccuracy),
         ENTRY( "SetVerticalAccuracy2", CTestLbsLocAcquisition::SettingVerticalAccuracy),
         ENTRY( "SettingCostIndicator", CTestLbsLocAcquisition::SettingCostIndicator),
         ENTRY( "SettingPowerConsumption", CTestLbsLocAcquisition::SettingPowerConsumption),
         ENTRY( "PositionModuleInfo", CTestLbsLocAcquisition::PositionModuleInfo),
         ENTRY( "SettingModuleId", CTestLbsLocAcquisition::SettingModuleId),
         ENTRY( "SettingModuleName", CTestLbsLocAcquisition::SettingModuleName),
         ENTRY( "IsAvailable", CTestLbsLocAcquisition::SettingAvailable),
         ENTRY( "SettingTechnologyType", CTestLbsLocAcquisition::SettingTechnologyType),
         ENTRY( "SettingDeviceLocation", CTestLbsLocAcquisition::SettingDeviceLocation),
         ENTRY( "SettingCapabilities", CTestLbsLocAcquisition::SettingCapabilities),
         ENTRY( "SettingClassesSupported", CTestLbsLocAcquisition::SettingClassesSupported),
         ENTRY( "SettingVersion", CTestLbsLocAcquisition::SettingVersion),
         ENTRY( "PositionModuleStatus", CTestLbsLocAcquisition::PositionModuleStatus),
         ENTRY( "SettingDeviceStatus", CTestLbsLocAcquisition::SettingDeviceStatus),
         ENTRY( "SettingDataQualityStatus", CTestLbsLocAcquisition::SettingDataQualityStatus),
         ENTRY( "SettingRequestedEvents", CTestLbsLocAcquisition::SettingRequestedEvents),
         ENTRY( "SetModStatusEventBaseModuleId", CTestLbsLocAcquisition::SetModStatusEventBaseModuleId),
         ENTRY( "SettingOccurredEvents", CTestLbsLocAcquisition::SettingOccurredEvents),
         ENTRY( "SettingSystemModuleEvents", CTestLbsLocAcquisition::SettingSystemModuleEvents),
         ENTRY( "DefaultPosModuleStatusEvent", CTestLbsLocAcquisition::PositionModuleStatusEvent),
         ENTRY( "PosModuleStatusEventConstructor1", CTestLbsLocAcquisition::PositionModuleStatusEventCons),
         ENTRY( "SettingModuleStatus", CTestLbsLocAcquisition::SettingModuleStatus),
         ENTRY( "SettingUpdateInterval", CTestLbsLocAcquisition::SettingUpdateInterval),
         ENTRY( "SettingUpdateTimeOut", CTestLbsLocAcquisition::SettingUpdateTimeOut),
         ENTRY( "SettingMaxUpdateAge", CTestLbsLocAcquisition::SettingMaxUpdateAge),
         ENTRY( "DefaultPosUpdateOptions", CTestLbsLocAcquisition::PositionUpdateOptions),
         ENTRY( "PosUpdateOptionsConstructor1", CTestLbsLocAcquisition::PositionUpdateOptionsCons),
         ENTRY( "PartialUpdates", CTestLbsLocAcquisition::PartialUpdates),
         ENTRY( "DefaultSatelliteData", CTestLbsLocAcquisition::SatelliteData),
         ENTRY( "SettingSatelliteId", CTestLbsLocAcquisition::SettingSatelliteId),
         ENTRY( "SettingAzimuth", CTestLbsLocAcquisition::SettingAzimuth),
         ENTRY( "SettingElevation", CTestLbsLocAcquisition::SettingElevation),
         ENTRY( "IsUsed", CTestLbsLocAcquisition::SettingIsUsed),
         ENTRY( "SignalStrength", CTestLbsLocAcquisition::SettingSignalStrength),
         ENTRY( "DefaultPositionSatelliteInfo", CTestLbsLocAcquisition::PositionSatelliteInfo),
         ENTRY( "SettingSatelliteTime", CTestLbsLocAcquisition::SettingSatelliteTime),
         ENTRY( "SettingHorizontalDoP", CTestLbsLocAcquisition::SettingHorizontalDoP),
         ENTRY( "SettingVerticalDoP", CTestLbsLocAcquisition::SettingVerticalDoP),
         ENTRY( "SettingTimeDoP", CTestLbsLocAcquisition::SettingTimeDoP),
         ENTRY( "CheckNumSatellitesInView", CTestLbsLocAcquisition::CheckNumSatellitesInView),
         ENTRY( "CheckClearSatellitesInView", CTestLbsLocAcquisition::CheckClearSatellitesInView),
         ENTRY( "CheckNumSatellitesUsed", CTestLbsLocAcquisition::CheckNumSatellitesUsed),
         ENTRY( "CheckAppendSatelliteData", CTestLbsLocAcquisition::CheckAppendSatelliteData),
         ENTRY( "CheckGetSatelliteData", CTestLbsLocAcquisition::CheckGetSatelliteData),
         ENTRY( "PositionSelectionOrder", CTestLbsLocAcquisition::PositionSelectionOrder),
         ENTRY( "SetOrderTimeToFirstFix", CTestLbsLocAcquisition::SettingOrderTimeToFirstFix),
         ENTRY( "SetOrderTimeToNextFix", CTestLbsLocAcquisition::SettingOrderTimeToNextFix),
         ENTRY( "SetOrderHorizontalAccuracy", CTestLbsLocAcquisition::SettingOrderHorizontalAccuracy),
         ENTRY( "SetOrderVerticalAccuracy", CTestLbsLocAcquisition::SettingOrderVerticalAccuracy),
         ENTRY( "SetOrderCostIndicator", CTestLbsLocAcquisition::SettingOrderCostIndicator),
         ENTRY( "SetOrderPowerConsumption", CTestLbsLocAcquisition::SettingOrderPowerConsumption),
         ENTRY( "CheckResetSelectionOrder", CTestLbsLocAcquisition::CheckResetSelectionOrder),
         ENTRY( "CheckClearSelectionOrder", CTestLbsLocAcquisition::CheckClearSelectionOrder),
         ENTRY( "NumSelectionItems", CTestLbsLocAcquisition::CheckNumSelectionItems),
         ENTRY( "CheckGetSelectionItem", CTestLbsLocAcquisition::CheckGetSelectionItem),
         ENTRY( "SettingRequiredCapabilities", CTestLbsLocAcquisition::SettingRequiredCapabilities),
         ENTRY( "CheckClearRequiredCapabilities", CTestLbsLocAcquisition::CheckClearRequiredCapabilities),
         ENTRY( "SettingRequiredQuality", CTestLbsLocAcquisition::SettingRequiredQuality),
         ENTRY( "SettingSelectionOrder", CTestLbsLocAcquisition::SettingSelectionOrder),
         ENTRY( "CheckResetCriteria", CTestLbsLocAcquisition::CheckResetCriteria),
         ENTRY( "CheckClearCriteria", CTestLbsLocAcquisition::CheckClearCriteria),
         ENTRY( "DefaultPositionCriteria", CTestLbsLocAcquisition::PositionCriteria),
         ENTRY( "PositionCriteria1", CTestLbsLocAcquisition::PositionCriteria1),
         ENTRY( "SettingRequestor", CTestLbsLocAcquisition::SettingRequestorL),
         ENTRY( "GettingRequestorData", CTestLbsLocAcquisition::GettingRequestorDataL),
         ENTRY( "GettingRequestorType", CTestLbsLocAcquisition::GettingRequestorTypeL),
         ENTRY( "GettingRequestorFormat", CTestLbsLocAcquisition::GettingRequestorFormatL),
         ENTRY( "RequestorNew", CTestLbsLocAcquisition::RequestorNew),
         ENTRY( "RequestorNewL", CTestLbsLocAcquisition::RequestorNewL),
         ENTRY( "RequestorNewLC", CTestLbsLocAcquisition::RequestorNewLC),
         ENTRY( "RequestorNewL1", CTestLbsLocAcquisition::RequestorNewL1),
         ENTRY( "RequestorExtendedInterfaceL", CTestLbsLocAcquisition::RequestorExtendedInterfaceL),
         
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::Connect
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::Connect( CStifItemParser& /*aItem*/ )
    {
	return iPosServer->Connect();
    }      

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::ConnectPanic
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::ConnectPanic( CStifItemParser& /*aItem*/ )
	{
	TInt err = iPosServer->Connect();
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerHandleNotClosed );
	TInt err1 = iPosServer->Connect();
	return KErrNone;
	}
	
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::VersionCheck
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::VersionCheck( CStifItemParser& /*aItem*/ )
    {
	return iPosServer->VersionCheck();
    } 

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::Disconnect
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::Disconnect( CStifItemParser& /*aItem*/ )
    {
	return iPosServer->Disconnect();
    }
    
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::DisconnectPanicOutstandingL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::DisconnectPanicOutstandingL( CStifItemParser& aItem )
    {
    TInt event;
	User::LeaveIfError(aItem.GetNextInt(event));
	TUint PsyUidInInt;
	TUid PsyUid;
	User::LeaveIfError(aItem.GetNextInt(PsyUidInInt, EHex));
	PsyUid.iUid = PsyUidInInt;
    
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionRequestsNotCancelled );    
	iPosServer->DisconnectPanicOutstanding(event, PsyUid);
	return KErrNone;
    }    

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetDefaultModule
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::GetDefaultModule( CStifItemParser& /*aItem*/ )	
	{
	return iPosServer->GetDefaultModule();
	}
	
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetDefaultModulePanicNoServer
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::GetDefaultModulePanicNoServer( CStifItemParser& /*aItem*/ )	
	{
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle);
	return iPosServer->GetDefaultModule();
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetModuleNum
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//	
TInt CTestLbsLocAcquisition::GetModuleNum( CStifItemParser& /*aItem*/ )	
	{
	return iPosServer->GetModuleNum();		
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetModuleNumPanicNoServer
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//	
TInt CTestLbsLocAcquisition::GetModuleNumPanicNoServer( CStifItemParser& /*aItem*/ )	
	{
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle);
	iPosServer->GetModuleNum();	
	return KErrNone;	
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetModuleInfoIndexL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::GetModuleInfoIndexL(CStifItemParser& aItem)
	{
	TInt index;
	User::LeaveIfError(aItem.GetNextInt(index));
	return iPosServer->GetModuleInfoIndex(index);
	}
	
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetModuleInfoIndexPanicNoServerL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//	
TInt CTestLbsLocAcquisition::GetModuleInfoIndexPanicNoServerL(CStifItemParser& aItem)
	{
	TInt index;
	User::LeaveIfError(aItem.GetNextInt(index));
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle);
	iPosServer->GetModuleInfoIndex(index);
	return KErrNone;
	}
	
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetModuleInfoIdL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::GetModuleInfoIdL(CStifItemParser& aItem)
	{

	 TUint PsyUidInInt;
	 TUid PsyUid;
	 //Get the PSYUid from the Stif framework
	 User::LeaveIfError(aItem.GetNextInt(PsyUidInInt, EHex));

	 //lex.Val(PsyUidInInt,EHex);	 
	 PsyUid.iUid = PsyUidInInt;
	
	 return iPosServer->GetModuleInfoId(PsyUid);
	
	}
	
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetModuleInfoIdPanicNoServerL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::GetModuleInfoIdPanicNoServerL(CStifItemParser& aItem)
	{
	 TUint PsyUidInInt;
	 TUid PsyUid;
	 //Get the PSYUid from the Stif framework
	 User::LeaveIfError(aItem.GetNextInt(PsyUidInInt, EHex));

	 //lex.Val(PsyUidInInt,EHex);	 
	 PsyUid.iUid = PsyUidInInt;
	
	 TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle);
	 iPosServer->GetModuleInfoId(PsyUid);
	return KErrNone;
	
	}			

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetModuleStatusL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//					
TInt CTestLbsLocAcquisition::GetModuleStatusL(CStifItemParser& aItem)
	{
	TUint PsyUidInInt;
	TUid PsyUid;
	//Get the PSYUid from the Stif framework
	User::LeaveIfError(aItem.GetNextInt(PsyUidInInt, EHex));

	//lex.Val(PsyUidInInt,EHex);	 
	PsyUid.iUid = PsyUidInInt;
	 
	return iPosServer->GetModuleStatus(PsyUid);
	
	}			

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetModuleChangeNotificationL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//	
TInt CTestLbsLocAcquisition::GetModuleChangeNotificationL(CStifItemParser& aItem)
	{
	TInt event;
	User::LeaveIfError(aItem.GetNextInt(event));
	TUint PsyUidInInt;
	TUid PsyUid;
	User::LeaveIfError(aItem.GetNextInt(PsyUidInInt, EHex));
	PsyUid.iUid = PsyUidInInt;
	
	TInt  err = iPosServer->GetModuleChangeNotification(event, PsyUid);
	return err;	
	}	

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetModuleChangeNotificationCancelL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//	
TInt CTestLbsLocAcquisition::GetModuleChangeNotificationCancelL(CStifItemParser& aItem)
	{
	TInt event;
	User::LeaveIfError(aItem.GetNextInt(event));
	TUint PsyUidInInt;
	TUid PsyUid;
	User::LeaveIfError(aItem.GetNextInt(PsyUidInInt, EHex));
	PsyUid.iUid = PsyUidInInt;
	
	TInt  err = iPosServer->GetModuleChangeNotificationCancel(event, PsyUid);
	return err;	
	}	

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetModuleChangeNotificationPanicNoServerL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::GetModuleChangeNotificationPanicNoServerL(CStifItemParser& aItem)
	{
	TInt event;
	User::LeaveIfError(aItem.GetNextInt(event));
	TUint PsyUidInInt;
	TUid PsyUid;
	User::LeaveIfError(aItem.GetNextInt(PsyUidInInt, EHex));
	PsyUid.iUid = PsyUidInInt;
	
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle);
	TInt  err = iPosServer->GetModuleChangeNotification(event, PsyUid);
	return KErrNone;
	}	

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetModuleChangeNotificationPanicDuplicateL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//	
TInt CTestLbsLocAcquisition::GetModuleChangeNotificationPanicDuplicateL(CStifItemParser& aItem)
	{
	TInt event;
	User::LeaveIfError(aItem.GetNextInt(event));
	TUint PsyUidInInt;
	TUid PsyUid;
	User::LeaveIfError(aItem.GetNextInt(PsyUidInInt, EHex));
	PsyUid.iUid = PsyUidInInt;
	
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionDuplicateRequest);
	iPosServer->GetModuleChangeNotificationPanicDuplicate(event, PsyUid);
	return KErrNone;
	}	

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CancelModuleStatusRequest
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::CancelModuleStatusRequest( CStifItemParser& /*aItem*/ )	
	{
	return iPosServer->CancelRequest(); 
	}
 
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CancelModuleStatusRequestPanicNoConnect
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//	
TInt CTestLbsLocAcquisition::CancelModuleStatusRequestPanicNoConnect( CStifItemParser& /*aItem*/ )	
	{
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle);
	iPosServer->CancelRequest(); 
	return KErrNone;	
	}

//-------------Start of RPositioner

// ---------------------------------------------------------
// CLbsPostionClient::OpenPositioner
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestLbsLocAcquisition::OpenPositioner( CStifItemParser& aItem )
	{
	return iPositioner->OpenPositionerResolver(iPosServer->PositionServer(), aItem );
	}
	
// ---------------------------------------------------------
// CLbsPostionClient::OpenPositioner
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestLbsLocAcquisition::OpenPositionerByCriteria( CStifItemParser& /*aItem*/ )
	{
	return iPositioner->OpenPositionerByCriteria(iPosServer->PositionServer());
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::OpenPositionerPanicNotClosed
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::OpenPositionerPanicNotClosed( CStifItemParser& aItem )
	{
	TInt err = iPositioner->OpenPositionerResolver(iPosServer->PositionServer(), aItem );	
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerHandleNotClosed );	
	iPositioner->OpenPositionerResolver(iPosServer->PositionServer(), aItem );
	return KErrNone;	
	}
	
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::OpenPositionerPanicBadHandle
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::OpenPositionerPanicBadHandle( CStifItemParser& aItem )
	{	
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle );	
	iPositioner->OpenPositionerResolver(iPosServer->PositionServer(), aItem );	
	return KErrNone;
	}
	
// ---------------------------------------------------------
// CLbsPostionClient::ClosePositioner
//
// (other items are commented in a header).
// ---------------------------------------------------------
//
TInt CTestLbsLocAcquisition::ClosePositioner( CStifItemParser& /*aItem*/ )
    {
	iPositioner->ClosePositioner();
	return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::SetRequestorL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::SetRequestorL(CStifItemParser& aItem)
	{
	TInt reqType;
	TInt reqFormat;	
	TPtrC reqService;
	User::LeaveIfError(aItem.GetNextInt(reqType));
	User::LeaveIfError(aItem.GetNextInt(reqFormat));
	User::LeaveIfError(aItem.GetNextString(reqService));	

	return iPositioner->SetRequestor(reqType,reqFormat,reqService);
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::SetRequestorPanicNoOpenL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::SetRequestorPanicNoOpenL(CStifItemParser& aItem)
	{
	TInt reqType;
	TInt reqFormat;	
	TPtrC reqService;
	User::LeaveIfError(aItem.GetNextInt(reqType));
	User::LeaveIfError(aItem.GetNextInt(reqFormat));
	User::LeaveIfError(aItem.GetNextString(reqService));
	
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle );			
	iPositioner->SetRequestor(reqType,reqFormat,reqService);
	return KErrNone;
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::SetRequestorStackL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::SetRequestorStackL(CStifItemParser& aItem)
	{

	return iPositioner->SetRequestorStackL(aItem);
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::SetRequestorStackPanicNoOpenL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::SetRequestorStackPanicNoOpenL(CStifItemParser& aItem)
	{	
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle );			
	iPositioner->SetRequestorStackL(aItem);
	return KErrNone;
	}
		
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::SetUpdateOpL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
	
TInt CTestLbsLocAcquisition::SetUpdateOpL(CStifItemParser& aItem)
	{
	TInt interval;
	TInt timeOut;
	TInt age;
	User::LeaveIfError(aItem.GetNextInt(interval));
	User::LeaveIfError(aItem.GetNextInt(timeOut));
	User::LeaveIfError(aItem.GetNextInt(age));
	return iPositioner->SetUpdateOp(interval,timeOut,age);	
	}		

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::SetUpdateOpPanicNoOpenL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::SetUpdateOpPanicNoOpenL(CStifItemParser& aItem)
	{
	TInt interval;
	TInt timeOut;
	TInt age;
	User::LeaveIfError(aItem.GetNextInt(interval));
	User::LeaveIfError(aItem.GetNextInt(timeOut));
	User::LeaveIfError(aItem.GetNextInt(age));

	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle );		
	iPositioner->SetUpdateOp(interval,timeOut,age);	
	return KErrNone;
	}
		
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetUpdateOpL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
	
TInt CTestLbsLocAcquisition::GetUpdateOpL(CStifItemParser& aItem)
	{
	TInt interval;
	TInt timeOut;
	TInt age;
	User::LeaveIfError(aItem.GetNextInt(interval));
	User::LeaveIfError(aItem.GetNextInt(timeOut));
	User::LeaveIfError(aItem.GetNextInt(age));
	return iPositioner->GetUpdateOp(interval,timeOut,age);	
	}		

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetUpdateOpPanicNoOpenL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::GetUpdateOpPanicNoOpenL(CStifItemParser& aItem)
	{
	TInt interval;
	TInt timeOut;
	TInt age;
	User::LeaveIfError(aItem.GetNextInt(interval));
	User::LeaveIfError(aItem.GetNextInt(timeOut));
	User::LeaveIfError(aItem.GetNextInt(age));

	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle );		
	iPositioner->GetUpdateOp(interval,timeOut,age);	
	return KErrNone;
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetLastKnownPostionL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::GetLastKnownPostionL(CStifItemParser& aItem)
	{		
	return iPositioner->GetLastKnownPostionResolverL(aItem);	
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetLastKnownPostionCancelL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::GetLastKnownPostionCancelL(CStifItemParser& aItem)
	{		
	return iPositioner->GetLastKnownPostionCancelResolverL(aItem);	
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetLastKnownPostionPanicNoOpenL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::GetLastKnownPostionPanicNoOpenL(CStifItemParser& aItem)
	{
	
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle);
	iPositioner->GetLastKnownPostionResolverL(aItem);
	return KErrNone;
	}		

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CancelGetLastKnownPostionL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::CancelGetLastKnownPostionL(CStifItemParser& aItem)	
	{
	iPositioner->SetRequestStateL(aItem);
	return iPositioner->CancelRequest(); 	
	}
 
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CancelGetLastKnownPostionPanicNoConnectL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//	
TInt CTestLbsLocAcquisition::CancelGetLastKnownPostionPanicNoConnectL(CStifItemParser& aItem)	
	{
	iPositioner->SetRequestStateL(aItem);
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle);
	iPositioner->CancelRequest(); 	
	return KErrNone;
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetPositionInfoL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::GetPositionInfoL(CStifItemParser& aItem)
	{		
	return iPositioner->GetPositionInfoResolverL(aItem);	
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetPositionInfoCancelL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::GetPositionInfoCancelL(CStifItemParser& aItem)
	{		
	return iPositioner->GetPositionInfoCancelResolverL(aItem);	
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetPositionInfoPanicNoOpenL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::GetPositionInfoPanicNoOpenL(CStifItemParser& aItem)
	{
	
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle);
	iPositioner->GetPositionInfoResolverL(aItem);
	return KErrNone;
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::GetPositionInfoPanicDuplicateL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//	
TInt CTestLbsLocAcquisition::GetPositionInfoPanicDuplicateL(CStifItemParser& aItem)
	{
	
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionDuplicateRequest);
	iPositioner->GetPositionInfoResolverL(aItem);
	return KErrNone;
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CancelGetPositionInfoL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//		
TInt CTestLbsLocAcquisition::CancelGetPositionInfoL(CStifItemParser& aItem)	
	{
	iPositioner->SetRequestStateL(aItem);	
	return iPositioner->CancelRequest(); 	
	}
 
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CancelGetPositionInfoPanicNoConnectL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//	
TInt CTestLbsLocAcquisition::CancelGetPositionInfoPanicNoConnectL(CStifItemParser& aItem)	
	{
	iPositioner->SetRequestStateL(aItem);
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionServerBadHandle);
	iPositioner->CancelRequest(); 	
	return KErrNone;
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::PositionerExtendedInterfaceL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::PositionerExtendedInterfaceL( CStifItemParser& /*aItem*/ )
	{
	return iPositioner->TestExtendedInterface();
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::DeleteLastKnownPostionCacheL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::DeleteLastKnownPostionCacheL( CStifItemParser& /*aItem*/ )
	{
	return iPositioner->DeleteLastKnownPostionCacheL();
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::ClosePositionerPanicNotCancelled
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::ClosePositionerPanicNotCancelled( CStifItemParser& /*aItem*/ )
	{
	TPositionInfo posiInfo;
	TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionRequestsNotCancelled );
	iPositioner->ClosePosServerPanic(&posiInfo);
	return KErrNone;	
	}	

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CheckModuleIdL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::CheckModuleIdL( CStifItemParser& aItem )
	{
	return iPositionInfo->CheckModuleIdL(aItem);	
	}
	
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CheckUpdateTypeL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::CheckUpdateTypeL( CStifItemParser& aItem )
	{
	return iPositionInfo->CheckUpdateTypeL(aItem);	
	}
	
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CheckPosition
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::CheckPosition( CStifItemParser& /*aItem*/ )
	{
	return iPositionInfo->CheckPosition();	
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CheckCourse
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::CheckCourse( CStifItemParser& /*aItem*/ )
	{
	return iPositionCourseInfo->CheckCourse();	
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CheckNewL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::CheckNewL( CStifItemParser& aItem )
	{
	return iPositionGenericInfo->CheckNewL(aItem);	
	}
	
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CheckRequestedFieldsL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::CheckRequestedFieldsL( CStifItemParser& /*aItem*/ )
	{
	return iPositionGenericInfo->CheckRequestedFieldsL();	
	}
	
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CheckOrderOfRequestedFieldL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::CheckOrderOfRequestedFieldL( CStifItemParser& /*aItem*/ )
	{
	return iPositionGenericInfo->CheckOrderOfRequestedFieldL();	
	}

// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CheckClearPositionDataL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::CheckClearPositionDataL( CStifItemParser& /*aItem*/ )
	{
	return iPositionGenericInfo->CheckClearPositionDataL();	
	}
	
// -----------------------------------------------------------------------------
// CTestLbsLocAcquisition::CheckClearRequestedFieldsL
// 
// (other items are commented in a header)
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::CheckClearRequestedFieldsL( CStifItemParser& /*aItem*/ )
	{
	return iPositionGenericInfo->CheckClearRequestedFieldsL();	
	}

// -----------------------------------------------------------------------------
// CTestPositionGenericInfo::CheckSetGetValueL
//
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTestLbsLocAcquisition::CheckSetGetValueL( CStifItemParser& aItem )
	{
	return iPositionGenericInfo->CheckSetGetValueL(aItem);
	}
	
// -------------------------------------------------------------------------
// 			All TClasses
// -------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Test case for the constructors of TCoordinate class
// -----------------------------------------------------------------------------
//   
TInt CTestLbsLocAcquisition::Coordinate(CStifItemParser& aItem)
	{
	    TTestCoordinate co_ordinate(iLog);
	    return co_ordinate.CreateCoordinate(aItem); 
	}
	
// -----------------------------------------------------------------------------
// Test case for setting the coordinate values
// -----------------------------------------------------------------------------

TInt CTestLbsLocAcquisition:: SettingCoordinate(CStifItemParser& aItem)
    {
        TTestCoordinate co_ordinate(iLog);
        return co_ordinate.SetCoordinate(aItem);   
    }
	
// -----------------------------------------------------------------------------
// Test case for setting the datum
// -----------------------------------------------------------------------------

TInt CTestLbsLocAcquisition::SettingDatum(CStifItemParser& /*aItem*/) 
    {
        TTestCoordinate co_ordinate(iLog);
        return co_ordinate.SetGetDatum();
    }
	
// -----------------------------------------------------------------------------
// Test case for obtaining the distance between two coordinates
// -----------------------------------------------------------------------------

TInt CTestLbsLocAcquisition::GettingDistance(CStifItemParser& aItem)
    {
              
        TTestCoordinate co_ordinate(iLog);
        return co_ordinate.GetDistance(aItem);
    }
// -----------------------------------------------------------------------------
// Test case for obtaining the bearing between two coordinates
// -----------------------------------------------------------------------------
TInt CTestLbsLocAcquisition::GetBearingTo(CStifItemParser& aItem)
    {
        TTestCoordinate co_ordinate(iLog);
        return co_ordinate.GetBearing(aItem);
    }

// -----------------------------------------------------------------------------
// Test case for moving the coordinate object
// -----------------------------------------------------------------------------
TInt CTestLbsLocAcquisition::MoveCoordinate(CStifItemParser& aItem)
    {
        TTestCoordinate co_ordinate(iLog);
        return co_ordinate.MoveTo(aItem);
    }

// -----------------------------------------------------------------------------
// Test case for the constructors of TLocality class
// -----------------------------------------------------------------------------

TInt CTestLbsLocAcquisition::Locality(CStifItemParser& aItem)
	{
	    TTestLocality locality(iLog);
	    return locality.CreateLocality(aItem); 
	}

// -----------------------------------------------------------------------------
// Test case for setting the horizontal accuracy
// -----------------------------------------------------------------------------

TInt CTestLbsLocAcquisition::SetGetHorizontalAcc(CStifItemParser& aItem)
    {
        TTestLocality locality(iLog);
	    return locality.SetGetHorAccuracy(aItem);
    }
    
// -----------------------------------------------------------------------------
// Test case for setting the vertical accuracy
// -----------------------------------------------------------------------------

TInt CTestLbsLocAcquisition::SetGetVerticalAcc(CStifItemParser& aItem)
    {
        TTestLocality locality(iLog);
	    return locality.SetGetVerAccuracy(aItem);
    }
// -----------------------------------------------------------------------------
// Test case for setting the horizontal & vertical accuracy
// -----------------------------------------------------------------------------

TInt CTestLbsLocAcquisition::SetGetAcc(CStifItemParser& aItem)
    {
        TTestLocality locality(iLog);
	    return locality.SetGetAccuracy(aItem);
    }
    
// -----------------------------------------------------------------------------
// Test case for obtaining distance between coordinates
// -----------------------------------------------------------------------------

TInt  CTestLbsLocAcquisition:: GetDistLocality1(CStifItemParser& aItem)
    {
        TTestLocality locality(iLog);
	    return locality.GetDistance(aItem);
    }
 // -----------------------------------------------------------------------------
// Test case for obtaining distance between localities
// -----------------------------------------------------------------------------   
    
 TInt  CTestLbsLocAcquisition:: GetDistLocality2(CStifItemParser& aItem)
    {
         TTestLocality locality(iLog);
	     return locality.GetDistance1(aItem);
    }
  
 // -----------------------------------------------------------------------------
// Test case for obtaining bearing between coordinates
// -----------------------------------------------------------------------------
 
  
  TInt CTestLbsLocAcquisition::GetBearingLocality1(CStifItemParser& aItem)
    {
        TTestLocality locality(iLog);
	    return locality.GetBearing(aItem);    
    }
    
    
// -----------------------------------------------------------------------------
// Test case for obtaining bearing between localities
// -----------------------------------------------------------------------------
 
  
  TInt CTestLbsLocAcquisition::GetBearingLocality2(CStifItemParser& aItem)
    {
        TTestLocality locality(iLog);
	    return locality.GetBearing1(aItem);    
    }
    
    
    
    
// -----------------------------------------------------------------------------
// Test case for the constructors of TPosition class
// -----------------------------------------------------------------------------

TInt CTestLbsLocAcquisition::Position(CStifItemParser& aItem)
	{
	    TTestPosition position(iLog);
	    return position.CreatePosition(aItem); 
	}
// -----------------------------------------------------------------------------
// Test case for setting & getting the time
// -----------------------------------------------------------------------------

TInt CTestLbsLocAcquisition::PositionSetTime(CStifItemParser& aItem)
	{
	    TTestPosition position(iLog);
	    return position.SetGetTime(aItem); 
	}
// -----------------------------------------------------------------------------
// Test case for setting current time
// -----------------------------------------------------------------------------
TInt CTestLbsLocAcquisition::SettingCurrentTime(CStifItemParser& /*aItem*/)
    {
        
	    TTestPosition position(iLog);
	    return position.SettingTime();
    }
    
// -----------------------------------------------------------------------------
// Test case for checking Speed method
// -----------------------------------------------------------------------------
TInt CTestLbsLocAcquisition::CheckSpeed(CStifItemParser& aItem)
    {
        
	    TTestPosition position(iLog);
	    return position.GetSpeed(aItem);
    }
    
// -----------------------------------------------------------------------------
// Test case for checking Speed method with accuracy
// -----------------------------------------------------------------------------
TInt CTestLbsLocAcquisition::CheckSpeed1(CStifItemParser& aItem)
    {
        
	    TTestPosition position(iLog);
	    return position.GetSpeed1(aItem);
    }    
    
// -----------------------------------------------------------------------------
// Test case for Default Constructor of TCourse
// -----------------------------------------------------------------------------
TInt CTestLbsLocAcquisition::Course(CStifItemParser& /*aItem*/)
    {
        
	    TTestCourse course(iLog);
	    return course.DefaultConstructor();
    }
    
    
// -----------------------------------------------------------------------------
//  Test case for setting & getting the speed
// -----------------------------------------------------------------------------
TInt CTestLbsLocAcquisition:: SettingSpeed(CStifItemParser& aItem)
    {
        
	    TTestCourse course(iLog);
	    return course.SetGetSpeed(aItem);
    }
    
    
// -----------------------------------------------------------------------------
//  Test case for setting & getting the heading
// -----------------------------------------------------------------------------
TInt CTestLbsLocAcquisition:: SettingHeading(CStifItemParser& aItem)
    {
        
	    TTestCourse course(iLog);
	    return course.SetGetHeading(aItem);
    }
    
// -----------------------------------------------------------------------------
//  Test case for setting & getting the course
// -----------------------------------------------------------------------------
TInt CTestLbsLocAcquisition:: SettingCourse(CStifItemParser& aItem)
    {
        
	    TTestCourse course(iLog);
	    return course.SetGetCourse(aItem);
    }
// -----------------------------------------------------------------------------
//  Test case for setting & getting the speed accuracy
// -----------------------------------------------------------------------------
TInt CTestLbsLocAcquisition:: SetGetSpeedAccuracy(CStifItemParser& aItem)
    {
        
	    TTestCourse course(iLog);
	    return course.SetGetSpeedAcc(aItem);
    }
// -----------------------------------------------------------------------------
//  Test case for setting & getting the heading accuracy
// -----------------------------------------------------------------------------
TInt CTestLbsLocAcquisition:: SetGetHeadingAccuracy(CStifItemParser& aItem)
    {
        
	    TTestCourse course(iLog);
	    return course.SetGetHeadingAcc(aItem);
    }
// -----------------------------------------------------------------------------
//  Test case for setting & getting the course accuracy
// -----------------------------------------------------------------------------
TInt CTestLbsLocAcquisition:: SetGetCourseAccuracy(CStifItemParser& aItem)
    {
        
	    TTestCourse course(iLog);
	    return course.SetGetCourseAcc(aItem);
    }
    
// -----------------------------------------------------------------------------
//  Test case for PositionClassType
// -----------------------------------------------------------------------------    
 TInt CTestLbsLocAcquisition:: CheckPositionClassType(CStifItemParser& /*aItem*/)
    {
        TTestPositionQuality posquality(iLog);
        return posquality.GetPositionClassType();
    }
    
    
// -----------------------------------------------------------------------------
//  Test case for PositionClassSize
// -----------------------------------------------------------------------------    
 TInt CTestLbsLocAcquisition:: CheckPositionClassSize(CStifItemParser& /*aItem*/)
    {
        TTestPositionQuality posquality(iLog);
        return posquality.GetPositionClassSize();
    }  
    
    
    
// -----------------------------------------------------------------------------
//  Test case for Compare
// -----------------------------------------------------------------------------    
 TInt CTestLbsLocAcquisition:: CheckCompare(CStifItemParser& /*aItem*/)
    {
        TTestPositionQuality posquality(iLog);
        return posquality.DoCompare();
    }  
    
 // -----------------------------------------------------------------------------
//  Test case for IsDefined
// -----------------------------------------------------------------------------    
 TInt CTestLbsLocAcquisition:: CheckIsDefined(CStifItemParser& /*aItem*/)
    {
        TTestPositionQuality posquality(iLog);
        return posquality.GetIsDefined();
    }     
    
// -----------------------------------------------------------------------------
//  Test case for getting the HighWaterMark
// -----------------------------------------------------------------------------    
 TInt CTestLbsLocAcquisition:: GettingHighWaterMark(CStifItemParser& /*aItem*/)
    {
        TTestPositionQuality posquality(iLog);
        return posquality.GetHighWaterMark();
    }
   
    
// -----------------------------------------------------------------------------
//  Test case for default constructor of TPositionQuality class
// -----------------------------------------------------------------------------    
 TInt CTestLbsLocAcquisition:: PositionQualityConstructor(CStifItemParser& /*aItem*/)
    {
        TTestPositionQuality posquality(iLog);
        return posquality.DefaultPositionQuality();
    }
// -----------------------------------------------------------------------------
// Test case for setting & gettting the time to first fix
// -----------------------------------------------------------------------------   

TInt CTestLbsLocAcquisition::SettingTimeToFirstFix(CStifItemParser& aItem)   
    {
        TTestPositionQuality posquality(iLog);
        TInt time1 = 0;
        
        TInt error = aItem.GetNextInt(time1);
        TTimeIntervalMicroSeconds  time2(time1);
        if(time2 < 0) //expecting panic.
            {
                TestModuleIf().SetExitReason( CTestModuleIf::EPanic, EPositionBadTime );
            }
        return posquality.SetGetTimeToFirstFix(time1);
    }
    
// -----------------------------------------------------------------------------
// Test case for setting & gettting the time to next fix
// -----------------------------------------------------------------------------   

TInt CTestLbsLocAcquisition::SettingTimeToNextFix(CStifItemParser& aItem)   
    {
        TTestPositionQuality posquality(iLog);
        TInt time1 = 0;
        
        TInt error = aItem.GetNextInt(time1);
        TTimeIntervalMicroSeconds  time2(time1);
        if(time2 < 0) //expecting panic.
            {
                TestModuleIf().SetExitReason( CTestModuleIf::EPanic, EPositionBadTime );
            }
        return posquality.SetGetTimeToNextFix(time1);
    }    

// -----------------------------------------------------------------------------
// Test case for setting & gettting the horizontal accuracy
// -----------------------------------------------------------------------------   

TInt CTestLbsLocAcquisition::SettingHorizontalAccuracy(CStifItemParser& aItem)   
    {
        TTestPositionQuality posquality(iLog);
        TInt haccuracy1 = 0;
        
        TInt error = aItem.GetNextInt(haccuracy1);
        TReal32 haccuracy2 = static_cast<TReal32>(haccuracy1);
        if(haccuracy2 < 0) //expecting panic.
            {
                TestModuleIf().SetExitReason( CTestModuleIf::EPanic, EPositionBadAccuracy );
            }
        return posquality.SetGetHorizontalAccuracy(haccuracy2);
    }    


// -----------------------------------------------------------------------------
// Test case for setting & gettting the vertical accuracy
// -----------------------------------------------------------------------------   

TInt CTestLbsLocAcquisition::SettingVerticalAccuracy(CStifItemParser& aItem)   
    {
        TTestPositionQuality posquality(iLog);
        TInt vaccuracy1 = 0;
        
        TInt error = aItem.GetNextInt(vaccuracy1);
        TReal32 vaccuracy2 = static_cast<TReal32>(vaccuracy1);
        if(vaccuracy2 < 0) //expecting panic.
            {
                TestModuleIf().SetExitReason( CTestModuleIf::EPanic, EPositionBadAccuracy );
            }
        return posquality.SetGetVerticalAccuracy(vaccuracy2);
    }    

// -----------------------------------------------------------------------------
// Test case for setting & gettting the cost indicator
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingCostIndicator(CStifItemParser& aItem) 
    {
        TTestPositionQuality posquality(iLog);
        return posquality.SetGetCostIndicator(aItem);
    }
 
 

// -----------------------------------------------------------------------------
// Test case for setting & gettting the cost indicator
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingPowerConsumption(CStifItemParser& aItem) 
    {
        TTestPositionQuality posquality(iLog);
        return posquality.SetGetPowerConsumption(aItem);
    }
    
// -----------------------------------------------------------------------------
// Test case for constructor of TPositionModuleInfoBase
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::PositionModuleInfo(CStifItemParser& /*aItem*/) 
    {
        TTestPositionQuality posquality(iLog);
        return posquality.PositionModuleInfoConst();
    }
    
    
// -----------------------------------------------------------------------------
// Test case for setting & getting ModuleId
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingModuleId(CStifItemParser& /*aItem*/) 
    {
        TTestPositionQuality posquality(iLog);
        return posquality.SetGetModuleId();
    }
  
// -----------------------------------------------------------------------------
// Test case for setting & getting ModuleName
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingModuleName(CStifItemParser& aItem) 
    {
        TTestPositionQuality posquality(iLog);
        return posquality.SetGetModuleName(aItem);
    }  
    
    
// -----------------------------------------------------------------------------
// Test case for checking if module is available
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingAvailable(CStifItemParser& aItem) 
    {
        TTestPositionQuality posquality(iLog);
        return posquality.SetGetIsAvailable(aItem);
    }  

// -----------------------------------------------------------------------------
// Test case for setting & getting TechnologyType
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingTechnologyType(CStifItemParser& aItem) 
    {
        TTestPositionQuality posquality(iLog);
        return posquality.SetGetTechnologyType(aItem);
    }
    
    
// -----------------------------------------------------------------------------
// Test case for setting & getting DeviceLocation
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingDeviceLocation(CStifItemParser& aItem) 
    {
        TTestPositionQuality posquality(iLog);
        return posquality.SetGetDeviceLocation(aItem);
    }
// -----------------------------------------------------------------------------
// Test case for setting & getting Capabilities
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingCapabilities(CStifItemParser& aItem) 
    {
        TTestPositionQuality posquality(iLog);
        return posquality.SetGetCapabilities(aItem);
    }
    
 // -----------------------------------------------------------------------------
// Test case for setting & getting Classes Supported
// -----------------------------------------------------------------------------  
   
    
   TInt CTestLbsLocAcquisition:: SettingClassesSupported(CStifItemParser& aItem)
    {
        TInt posClassFamily1 = 0;
        TInt posInfoClasstype1 = 0;
        TInt err1 = aItem.GetNextInt(posClassFamily1);
        TInt err2 = aItem.GetNextInt(posInfoClasstype1);
        TPositionClassFamily posClassFamily = EPositionInfoFamily;
    	TPositionInfoClassType posInfoClasstype = 0;
    	
    	 TTestPositionQuality posquality(iLog);
    
        if(!err1 && !err2)
            {
                switch(posClassFamily1)
                    {
                        case 0: posClassFamily = EPositionInfoFamily;
                                break;
                        case 1: posClassFamily = EPositionModuleInfoFamily;
                                break;
                        case 2: posClassFamily = EPositionModuleStatusFamily;
                                break;
                        case 3: posClassFamily = EPositionModuleStatusEventFamily;
                                break;
                        case 4: posClassFamily = EPositionModuleQualityFamily;
                                break;
                        case 5: posClassFamily = EPositionPositionCriteriaFamily;
                                break;
                        case 6: posClassFamily = EPositionLastFamily;
                                break;
                        default: TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionInvalidClassType);
                                 break;
                    
                    }
                 switch(posInfoClasstype)
                    {
                        case 0: posInfoClasstype = EPositionInfoUnknownClass;
                                break;
                        case 1: posInfoClasstype = EPositionInfoClass;
                                break;
                        case 2: posInfoClasstype = EPositionGenericInfoClass;
                                break;
                        case 3: posInfoClasstype = EPositionCourseInfoClass;
                                break;
                        case 4: posInfoClasstype = EPositionSatelliteInfoClass;
                                break;
                        case 5: posInfoClasstype = EPositionInfoFirstCustomClass;
                                break;
                        default:break;
                    
                            
                    }
                   return posquality.SetGetClassesSupported(posClassFamily,posInfoClasstype);
                    
                    
                    
            }
            else return KErrGeneral;
    }
        
        
 // -----------------------------------------------------------------------------
// Test case for setting & getting Version
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingVersion(CStifItemParser& aItem)
    {
        TTestPositionQuality posquality(iLog);
        return posquality.SetGetVersion(aItem);
    }
        
        
 // -----------------------------------------------------------------------------
// Test case for default constructor of TPositionModuleStatusBase
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::PositionModuleStatus(CStifItemParser& /*aItem*/)
    {
        TTestPositionModule position(iLog);
        return position.DefaultPositionModuleStatus();
    }
    
 // -----------------------------------------------------------------------------
// Test case for setting & getting Device Status
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingDeviceStatus(CStifItemParser& aItem)
    {
        TTestPositionModule position(iLog);
        return position.SetGetDeviceStatus(aItem);
    }
    
 // -----------------------------------------------------------------------------
// Test case for setting & getting DataQuality Status
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingDataQualityStatus(CStifItemParser& aItem)
    {
        TTestPositionModule position(iLog);
        return position.SetGetDataQualityStatus(aItem);
    }
    
    
    
 // -----------------------------------------------------------------------------
// Test case for setting & getting Requested Events
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingRequestedEvents(CStifItemParser& aItem)
    {
        TTestPositionModule position(iLog);
        return position.SetGetRequestedEvents(aItem);
    }
    
 // -----------------------------------------------------------------------------
// Test case for setting & getting ModuleId
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SetModStatusEventBaseModuleId(CStifItemParser& /*aItem*/)
    {
        TTestPositionModule position(iLog);
        return position.SetGetModuleId();
    }
    
// -----------------------------------------------------------------------------
// Test case for setting & getting Occurred Events
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingOccurredEvents(CStifItemParser& aItem)
    {
        TTestPositionModule position(iLog);
        return position.SetGetOccurredEvents(aItem);
    }
    
// -----------------------------------------------------------------------------
// Test case for setting & getting SystemModule Events
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingSystemModuleEvents(CStifItemParser& aItem)
    {
        TTestPositionModule position(iLog);
        return position.SetGetSystemModuleEvents(aItem);
    }
    
// -----------------------------------------------------------------------------
// Test case for default constructor of TPositionModuleStatusEvent
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::PositionModuleStatusEvent(CStifItemParser& /*aItem*/)
    {
        TTestPositionModule position(iLog);
        return position.DefaultPositionModuleStatusEvent();
    }
    
// -----------------------------------------------------------------------------
// Test case for default constructor of TPositionModuleStatusEvent
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::PositionModuleStatusEventCons(CStifItemParser& aItem)
    {
        TTestPositionModule position(iLog);
        return position.PositionModuleStatusEvent1(aItem);
    }
    
    
    
// -----------------------------------------------------------------------------
// Test case for setting & getting ModuleStatus
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingModuleStatus(CStifItemParser& aItem)
    {
        TTestPositionModule position(iLog);
        return position.SetGetModuleStatus(aItem);
    }
    
// -----------------------------------------------------------------------------
// Test case for setting & getting UpdateInterval
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingUpdateInterval(CStifItemParser& aItem)
    {
        TTestPositionModule position(iLog);
        TInt interval = 0;
        TInt err = aItem.GetNextInt(interval);
        TTimeIntervalMicroSeconds time(interval);
        if(!err)
            {
                if(interval<0) //expecting panic
                    {
                        TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionBadTime);
                    }
                
                    return position.SetGetUpdateInterval(time);
            }
         else
            return KErrGeneral;
        
    }
    
// -----------------------------------------------------------------------------
// Test case for setting & getting UpdateTimeOut
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingUpdateTimeOut(CStifItemParser& aItem)
    {
        TTestPositionModule position(iLog);
        TInt timeOut = 0;
        TInt err = aItem.GetNextInt(timeOut);
        TTimeIntervalMicroSeconds time(timeOut);
        if(!err)
            {
                if(timeOut<0) //expecting panic
                    {
                        TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionBadTime);
                    }
                
                    return position.SetGetUpdateTimeOut(time);
            }
         else
            return KErrGeneral;
        
    }
    
    
// -----------------------------------------------------------------------------
// Test case for setting & getting MaxUpdateAge
// -----------------------------------------------------------------------------  

TInt CTestLbsLocAcquisition::SettingMaxUpdateAge(CStifItemParser& aItem)
    {
        TTestPositionModule position(iLog);
        TInt maxAge = 0;
        TInt err = aItem.GetNextInt(maxAge);
        TTimeIntervalMicroSeconds time(maxAge);
        if(!err)
            {
                if(maxAge<0) //expecting panic
                    {
                        TestModuleIf().SetExitReason(CTestModuleIf::EPanic , EPositionBadTime);
                    }
                
                    return position.SetGetMaxUpdateAge(time);
            }
         else
            return KErrGeneral;
        
    }
    
    
// -----------------------------------------------------------------------------
// Test case for default constructor of TPositionUpdateOptions
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::PositionUpdateOptions(CStifItemParser& /*aItem*/)
    {
        TTestPositionModule position(iLog);
        return position.DefaultPosUpdateOptions();
    }
    
    
// -----------------------------------------------------------------------------
// Test case for constructor of TPositionUpdateOptions with arguments
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::PositionUpdateOptionsCons(CStifItemParser& /*aItem*/)
    {
        TTestPositionModule position(iLog);
        return position.PosUpdateOptions1();
    }
    
// -----------------------------------------------------------------------------
// Test case for checking if partial updates are allowed
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::PartialUpdates(CStifItemParser& aItem)
    {
        TTestPositionModule position(iLog);
        return position.SetGetPartialUpdates(aItem);
    }
  
// -----------------------------------------------------------------------------
// Test case for Default Constructor of TSatelliteData
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SatelliteData(CStifItemParser& /*aItem*/)
    {
        TTestSatellite sat(iLog);
        return sat.DefaultSatelliteData();
    }
// -----------------------------------------------------------------------------
// Test case for setting & getting SatelliteId
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingSatelliteId(CStifItemParser& aItem)
    {
        TTestSatellite sat(iLog);
        return sat.SetGetSatelliteId(aItem);
    }  
  
// -----------------------------------------------------------------------------
// Test case for setting & getting Azimuth
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingAzimuth(CStifItemParser& aItem)
    {
        TTestSatellite sat(iLog);
        return sat.SetGetAzimuth(aItem);
    } 
    
// -----------------------------------------------------------------------------
// Test case for setting & getting Elevation
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingElevation(CStifItemParser& aItem)
    {
        TTestSatellite sat(iLog);
        return sat.SetGetElevation(aItem);
    }  
 
// -----------------------------------------------------------------------------
// Test case for checking if Used
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingIsUsed(CStifItemParser& aItem)
    {
        TTestSatellite sat(iLog);
        return sat.SetGetIsUsed(aItem);
    }  

// -----------------------------------------------------------------------------
// Test case for setting & getting the signal strength
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingSignalStrength(CStifItemParser& aItem)
    {
        TTestSatellite sat(iLog);
        return sat.SetGetSignalStrength(aItem);
    }  
    
    
// -----------------------------------------------------------------------------
// Test case for Default Constructor of TPositionSatelliteInfo
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::PositionSatelliteInfo(CStifItemParser& /*aItem*/)
    {
        TTestSatellite sat(iLog);
        return sat.DefaultPositionSatelliteInfo();
    }

// -----------------------------------------------------------------------------
// Test case for setting & getting the satellite time
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingSatelliteTime(CStifItemParser& aItem)
    {
        TTestSatellite sat(iLog);
        return sat.SetGetSatelliteTime(aItem);
    }
// -----------------------------------------------------------------------------
// Test case for setting & getting the HorizontalDoP
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingHorizontalDoP(CStifItemParser& aItem)
    {
        TTestSatellite sat(iLog);
        return sat.SetGetHorizontalDoP(aItem);
    }  
 
// -----------------------------------------------------------------------------
// Test case for setting & getting the VerticalDoP
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingVerticalDoP(CStifItemParser& aItem)
    {
        TTestSatellite sat(iLog);
        return sat.SetGetVerticalDoP(aItem);
    }  
 
// -----------------------------------------------------------------------------
// Test case for setting & getting the TimeDoP
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingTimeDoP(CStifItemParser& aItem)
    {
        TTestSatellite sat(iLog);
        return sat.SetGetTimeDoP(aItem);
    }  
     
     
// -----------------------------------------------------------------------------
// Test case to check the NumSatellitesInView
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::CheckNumSatellitesInView(CStifItemParser& /*aItem*/)
    {
        TTestSatellite sat(iLog);
        return sat.GetNumSatellitesInView();
    } 
    
// -----------------------------------------------------------------------------
// Test case for ClearSatellitesInView
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::CheckClearSatellitesInView(CStifItemParser& /*aItem*/)
    {
        TTestSatellite sat(iLog);
        return sat.DoClearSatellitesInView();
    } 
    
    
// -----------------------------------------------------------------------------
// Test case to check the NumSatellitesUsed
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::CheckNumSatellitesUsed(CStifItemParser& /*aItem*/)
    {
        TTestSatellite sat(iLog);
        return sat.GetNumSatellitesUsed();
    } 
    
// -----------------------------------------------------------------------------
// Test case for AppendSatelliteData
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::CheckAppendSatelliteData(CStifItemParser& /*aItem*/)
    {
        TTestSatellite sat(iLog);
        return sat.DoAppendSatelliteData();
    } 
    
// -----------------------------------------------------------------------------
// Test case for GetSatelliteData
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::CheckGetSatelliteData(CStifItemParser& /*aItem*/)
    {
        TTestSatellite sat(iLog);
        return sat.ToGetSatelliteData();
    } 
    
// -----------------------------------------------------------------------------
// Test case for Default Constructor of TPositionSelectionOrder
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::PositionSelectionOrder(CStifItemParser& /*aItem*/)
    {
        TTestCriteria criteria(iLog);
        return criteria.DefaultPositionSelectionOrder();
    }
    
// -----------------------------------------------------------------------------
// Test case for SetOrderTimeToFirstFix
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingOrderTimeToFirstFix(CStifItemParser& aItem)
    {
        TTestCriteria criteria(iLog);
        return criteria.DoSetOrderTimeToFirstFix(aItem);
    }
    
    
// -----------------------------------------------------------------------------
// Test case for SetOrderTimeToNextFix
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingOrderTimeToNextFix(CStifItemParser& aItem)
    {
        TTestCriteria criteria(iLog);
        return criteria.DoSetOrderTimeToNextFix(aItem);
    }

// -----------------------------------------------------------------------------
// Test case for SetOrderHorizontalAccuracy
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingOrderHorizontalAccuracy(CStifItemParser& aItem)
    {
        TTestCriteria criteria(iLog);
        return criteria.DoSetOrderHorizontalAccuracy(aItem);
    }
    
// -----------------------------------------------------------------------------
// Test case for SetOrderVerticalAccuracy
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingOrderVerticalAccuracy(CStifItemParser& aItem)
    {
        TTestCriteria criteria(iLog);
        return criteria.DoSetOrderVerticalAccuracy(aItem);
    }
    
    
// -----------------------------------------------------------------------------
// Test case for SetOrderCostIndicator
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingOrderCostIndicator(CStifItemParser& aItem)
    {
        TTestCriteria criteria(iLog);
        return criteria.DoSetOrderCostIndicator(aItem);
    }
    
    
// -----------------------------------------------------------------------------
// Test case for SetOrderPowerConsumption
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingOrderPowerConsumption(CStifItemParser& aItem)
    {
        TTestCriteria criteria(iLog);
        return criteria.DoSetOrderPowerConsumption(aItem);
    }
    
    
// -----------------------------------------------------------------------------
// Test case for CheckResetSelectionOrder
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::CheckResetSelectionOrder(CStifItemParser& /*aItem*/)
    {
        TTestCriteria criteria(iLog);
        return criteria.DoResetSelectionOrder();
    }
    
// -----------------------------------------------------------------------------
// Test case for CheckClearSelectionOrder
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::CheckClearSelectionOrder(CStifItemParser& /*aItem*/)
    {
        TTestCriteria criteria(iLog);
        return criteria.DoClearSelectionOrder();
    }
    
  
// -----------------------------------------------------------------------------
// Test case for CheckNumSelectionItems
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::CheckNumSelectionItems(CStifItemParser& /*aItem*/)
    {
        TTestCriteria criteria(iLog);
        return criteria.GetNumSelectionItems();
    }  
    
    
// -----------------------------------------------------------------------------
// Test case for CheckGetSelectionItem
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::CheckGetSelectionItem(CStifItemParser& /*aItem*/)
    {
        TTestCriteria criteria(iLog);
        return criteria.DoGetSelectionItem();
    }

// -----------------------------------------------------------------------------
// Test case for setting & getting RequiredCapabilities
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingRequiredCapabilities(CStifItemParser& aItem)
    {
        TTestCriteria criteria(iLog);
        return criteria.SetGetRequiredCapabilities(aItem);
    }
    
    
    
// -----------------------------------------------------------------------------
// Test case for ClearRequiredCapabilities
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::CheckClearRequiredCapabilities(CStifItemParser& /*aItem*/)
    {
        TTestCriteria criteria(iLog);
        return criteria.DoClearRequiredCapabilities();
    }
    
// -----------------------------------------------------------------------------
// Test case for setting & getting RequiredQuality
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingRequiredQuality(CStifItemParser& /*aItem*/)
    {
        TTestCriteria criteria(iLog);
        return criteria.SetGetRequiredQuality();
    } 
    
// -----------------------------------------------------------------------------
// Test case for setting & getting SelectionOrder
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingSelectionOrder(CStifItemParser& /*aItem*/)
    {
        TTestCriteria criteria(iLog);
        return criteria.SetGetSelectionOrder();
    }   
    
// -----------------------------------------------------------------------------
// Test case for ResetCriteria
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::CheckResetCriteria(CStifItemParser& /*aItem*/)
    {
        TTestCriteria criteria(iLog);
        return criteria.DoResetCriteria();
    }     
// -----------------------------------------------------------------------------
// Test case for ClearCriteria
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::CheckClearCriteria(CStifItemParser& /*aItem*/)
    {
        TTestCriteria criteria(iLog);
        return criteria.DoClearCriteria();
    }     

// -----------------------------------------------------------------------------
// Test Case for default constructor of TPositionCriteria
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::PositionCriteria(CStifItemParser& /*aItem*/)
    {
        TTestCriteria criteria(iLog);
        return criteria.DefaultPositionCriteria();
    }     

// -----------------------------------------------------------------------------
// Test Case for  constructor of TPositionCriteria with 
// required capabilities as parameter
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::PositionCriteria1(CStifItemParser& aItem)
    {
        TTestCriteria criteria(iLog);
        return criteria.PositionCriteriaCons(aItem);
    }
    
// -----------------------------------------------------------------------------
// Test case for setting & getting requestorL
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::SettingRequestorL(CStifItemParser& aItem)
    {
        TTestRequestor requestor(iLog);
        return requestor.SetGetRequestorL(aItem);
    } 
    
    
// -----------------------------------------------------------------------------
// Test case for getting  requestor dataL
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::GettingRequestorDataL(CStifItemParser& aItem)
    {
        TTestRequestor requestor(iLog);
        return requestor.GetRequestorDataL(aItem);
    } 
    
// -----------------------------------------------------------------------------
// Test case for getting  requestor typeL
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::GettingRequestorTypeL(CStifItemParser& aItem)
    {
        TTestRequestor requestor(iLog);
        return requestor.GetRequestorTypeL(aItem);
    } 
    
// -----------------------------------------------------------------------------
// Test case for getting  requestor formatL
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::GettingRequestorFormatL(CStifItemParser& aItem)
    {
        TTestRequestor requestor(iLog);
        return requestor.GetRequestorFormatL(aItem);
    }    
   
// -----------------------------------------------------------------------------
// Test case for  CRequestor::New
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::RequestorNew(CStifItemParser& aItem)
    {
        TTestRequestor requestor(iLog);
        return requestor.TestRequestorNew(aItem);
    } 
    
// -----------------------------------------------------------------------------
// Test case for  CRequestor::NewL
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::RequestorNewL(CStifItemParser& aItem)
    {
        TTestRequestor requestor(iLog);
        return requestor.TestRequestorNewL(aItem);
    } 
    
// -----------------------------------------------------------------------------
// Test case for  CRequestor::NewLC
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::RequestorNewLC(CStifItemParser& aItem)
    {
        TTestRequestor requestor(iLog);
        return requestor.TestRequestorNewLC(aItem);
    } 

// -----------------------------------------------------------------------------
// Test case for  CRequestor::NewL with RReadStream instance
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::RequestorNewL1(CStifItemParser& aItem)
    {
        TTestRequestor requestor(iLog);
        return requestor.TestRequestorNewL1(aItem);
    } 
    
// -----------------------------------------------------------------------------
// Test case for  CRequestor::ExtendedInterface
// -----------------------------------------------------------------------------  
TInt CTestLbsLocAcquisition::RequestorExtendedInterfaceL( CStifItemParser& /*aItem*/ )
	{
        TTestRequestor requestor(iLog);
		return requestor.TestExtendedInterface();
	}

//  End of File
