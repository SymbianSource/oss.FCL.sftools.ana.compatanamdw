/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#include "T_BTUtil.h"

//	EPOC includes
#include <bt_sock.h>

/*@{*/
_LIT(KSdpElementTypeNil,					"ETypeNil");
_LIT(KSdpElementTypeUint,					"ETypeUint");
_LIT(KSdpElementTypeInt,					"ETypeInt");
_LIT(KSdpElementTypeUUID,					"ETypeUUID");
_LIT(KSdpElementTypeString,					"ETypeString");
_LIT(KSdpElementTypeBoolean,				"ETypeBoolean");
_LIT(KSdpElementTypeDES,					"ETypeDES");
_LIT(KSdpElementTypeDEA,					"ETypeDEA");
_LIT(KSdpElementTypeURL,					"ETypeURL");
_LIT(KSdpElementTypeEncoded,				"ETypeEncoded");

_LIT(KCSdpAttrValueDES,						"CSdpAttrValueDES");
_LIT(KCSdpAttrValueDEA,						"CSdpAttrValueDEA");
_LIT(KCSdpAttrValueList,					"CSdpAttrValueList");

_LIT(KLowPowerActiveMode,					"EActiveMode");
_LIT(KLowPowerHoldMode,						"EHoldMode");
_LIT(KLowPowerSniffMode,					"ESniffMode");
_LIT(KLowPowerParkMode,						"EParkMode");
_LIT(KLowPowerScatterMode,					"EScatterMode");
_LIT(KLowPowerAnyLowPowerMode,				"EAnyLowPowerMode");

_LIT(KLowPowerMode,							"lowpowermode%d");

_LIT(KShutdownNormal,						"ENormal");
_LIT(KShutdownStopInput,					"EStopInput");
_LIT(KShutdownStopOutput,					"EStopOutput");
_LIT(KShutdownImmediate,					"EImmediate");

_LIT(KShutdownMethod,						"shutdownmethod");

_LIT(KEPacketsDM1,							"EPacketsDM1");
_LIT(KEPacketsDH1,							"EPacketsDH1");
_LIT(KEPacketsDM3,							"EPacketsDM1");
_LIT(KEPacketsDH3,							"EPacketsDH1");
_LIT(KEPacketsDM5,							"EPacketsDM1");
_LIT(KEPacketsDH5,							"EPacketsDH1");
_LIT(KEPacketsHV1,							"EPacketsHV1");
_LIT(KEPacketsHV2,							"EPacketsHV2");
_LIT(KEPacketsHV3,							"EPacketsHV3");
_LIT(KEAnyACLPacket,						"EAnyACLPacket");
_LIT(KEAnySCOPacket,						"EAnySCOPacket");
_LIT(KEAnyPacket,							"EAnyPacket");

_LIT(KPacketTypes,							"packettypes%d");

_LIT(KENotifyMaster,						"ENotifyMaster");
_LIT(KENotifySlave,							"ENotifySlave");
_LIT(KENotifyActiveMode,					"ENotifyActiveMode");
_LIT(KENotifySniffMode,						"ENotifySniffMode");
_LIT(KENotifyParkMode,						"ENotifyParkMode");
_LIT(KENotifyHoldMode,						"ENotifyHoldMode");
_LIT(KENotifyMaxSlots1,						"ENotifyMaxSlots1");
_LIT(KENotifyMaxSlots3,						"ENotifyMaxSlots3");
_LIT(KENotifyMaxSlots5,						"ENotifyMaxSlots5");
_LIT(KENotifyPacketsDM1,					"ENotifyPacketsDM1");
_LIT(KENotifyPacketsDH1,					"ENotifyPacketsDH1");
_LIT(KENotifyPacketsDM3,					"ENotifyPacketsDM3");
_LIT(KENotifyPacketsDH3,					"ENotifyPacketsDH3");
_LIT(KENotifyPacketsDM5,					"ENotifyPacketsDM5");
_LIT(KENotifyPacketsDH5,					"ENotifyPacketsDH5");
_LIT(KENotifyPacketsHV1,					"ENotifyPacketsHV1");
_LIT(KENotifyPacketsHV2,					"ENotifyPacketsHV2");
_LIT(KENotifyPacketsHV3,					"ENotifyPacketsHV3");
_LIT(KENotifyAuthenticationComplete,		"ENotifyAuthenticationComplete");
_LIT(KENotifyEncryptionChangeOn,			"ENotifyEncryptionChangeOn");
_LIT(KENotifyEncryptionChangeOff,			"ENotifyEncryptionChangeOff");
_LIT(KENotifyPhysicalLinkUp,				"ENotifyPhysicalLinkUp");
_LIT(KENotifyPhysicalLinkDown,				"ENotifyPhysicalLinkDown");
_LIT(KENotifyPhysicalLinkError,				"ENotifyPhysicalLinkError");
_LIT(KENotifySCOLinkUp,						"ENotifySCOLinkUp");
_LIT(KENotifySCOLinkDown,					"ENotifySCOLinkDown");
_LIT(KENotifySCOLinkError,					"ENotifySCOLinkError");

_LIT(KBaseBandMode,							"basebandmode%d");
/*@}*/

TBool CT_BTUtil::ReadSdpElementType(CDataWrapper& aDataWrapper, TSdpElementType& aType, const TDesC& aSection, const TDesC& aField)
	{
	TPtrC	type;
	TBool	ret=aDataWrapper.GetStringFromConfig(aSection, aField, type);
	if ( ret )
		{
		if ( type==KSdpElementTypeNil )
			{
			aType=ETypeNil;
			}
		else if ( type==KSdpElementTypeUint )
			{
			aType=ETypeUint;
			}
		else if ( type==KSdpElementTypeInt )
			{
			aType=ETypeInt;
			}
		else if ( type==KSdpElementTypeUUID )
			{
			aType=ETypeUUID;
			}
		else if ( type==KSdpElementTypeString )
			{
			aType=ETypeString;
			}
		else if ( type==KSdpElementTypeBoolean )
			{
			aType=ETypeBoolean;
			}
		else if ( type==KSdpElementTypeDES )
			{
			aType=ETypeDES;
			}
		else if ( type==KSdpElementTypeDEA )
			{
			aType=ETypeDEA;
			}
		else if ( type==KSdpElementTypeURL )
			{
			aType=ETypeURL;
			}
		else if ( type==KSdpElementTypeEncoded )
			{
			aType=ETypeEncoded;
			}
		else
			{
			TInt	intType;
			ret=aDataWrapper.GetIntFromConfig(aSection, aField, intType);
			if ( ret )
				{
				aType=(TSdpElementType)intType;
				}
			else
				{
				aDataWrapper.ERR_PRINTF1(_L("Unknow input for TSdpElementType"));
				aDataWrapper.SetBlockResult(EFail);
				}
			}
		}

	return ret;
	}

MSdpElementBuilder* CT_BTUtil::ElementBuilderCastL(CDataWrapper& aDataWrapper, const TDesC& aObjectName, const TDesC& aTypeName)
	{
	MSdpElementBuilder*	ret = NULL;
	TAny*				object=aDataWrapper.GetDataObjectL(aObjectName);

	if( aTypeName == KCSdpAttrValueDES )
		{
		ret = static_cast<CSdpAttrValueDES*>(object);
		}
	else if( aTypeName == KCSdpAttrValueDEA )
		{
		ret = static_cast<CSdpAttrValueDEA*>(object);
		}
	else if( aTypeName == KCSdpAttrValueList )
		{
		ret = static_cast<CSdpAttrValueList*>(object);
		}
	else
		{
		aDataWrapper.ERR_PRINTF2(_L("Unknow Type %S for ElementBuilderCastL call"), &aTypeName);
		aDataWrapper.SetBlockResult(EFail);
		}

	return ret;
	}

CSdpAttrValueList* CT_BTUtil::AttrValueListCastL(CDataWrapper& aDataWrapper, const TDesC& aObjectName, const TDesC& aTypeName)
	{
	CSdpAttrValueList*	ret = NULL;
	TAny*				object=aDataWrapper.GetDataObjectL(aObjectName);

	if( aTypeName == KCSdpAttrValueDES )
		{
		ret = static_cast<CSdpAttrValueDES*>(object);
		}
	else if( aTypeName == KCSdpAttrValueDEA )
		{
		ret = static_cast<CSdpAttrValueDEA*>(object);
		}
	else if( aTypeName == KCSdpAttrValueList )
		{
		ret = static_cast<CSdpAttrValueList*>(object);
		}
	else
		{
		aDataWrapper.ERR_PRINTF2(_L("Unknow Type %S for AttrValueListCastL call"), &aTypeName);
		aDataWrapper.SetBlockResult(EFail);
		}

	return ret;
	}

TUint CT_BTUtil::ConvertUUID32toInt(const TUUID& aUUID)
	{
	TUint	result = aUUID[3] + 256*(aUUID[2] + 256*(aUUID[1] + aUUID[0]*256));

	return result;
	}

void CT_BTUtil::GetLowPowerMode(CDataWrapper& aDataWrapper, const TDesC& aSection, TUint32& aModes)
	{
	TBuf<KMaxTestExecuteCommandLength>	tempStore;

	aModes=0;
	TBool	moreData=ETrue;
	TInt	index=0;
	while ( moreData )
		{
		TPtrC	modeName;
		tempStore.Format(KLowPowerMode(), &aSection, ++index);

		moreData=aDataWrapper.GetStringFromConfig(aSection, tempStore, modeName);
		if ( moreData )
			{
			if (modeName == KLowPowerActiveMode)
				{
				aModes |= EActiveMode;
				}
			else if (modeName == KLowPowerHoldMode)
				{
				aModes |= EHoldMode;
				}
			else if (modeName == KLowPowerSniffMode)
				{
				aModes |= ESniffMode;
				}
			else if (modeName == KLowPowerParkMode)
				{
				aModes |= EParkMode;
				}
			else if (modeName == KLowPowerScatterMode)
				{
				aModes |= EScatterMode;
				}
			else if (modeName == KLowPowerAnyLowPowerMode)
				{
				aModes |= EAnyLowPowerMode;
				}
			else
				{
				TInt	intMode;
				if ( aDataWrapper.GetIntFromConfig(aSection, tempStore, intMode) )
					{
					aModes |= intMode;
					}
				else
					{
					aDataWrapper.ERR_PRINTF2(_L("Illegal mode %S"), &tempStore);
					aDataWrapper.SetBlockResult(EFail);
					}
				}
			}
		else if (index==1)
			{
			//Special case as we would want to use default if not found at all
			aModes=EAnyLowPowerMode;
			}
		}
	}

TBool CT_BTUtil::GetShutdown(CDataWrapper& aDataWrapper, const TDesC& aSection, RSocket::TShutdown& aShutdown)
	{

	TPtrC	shutdownMethod;
	TBool	ret=aDataWrapper.GetStringFromConfig(aSection, KShutdownMethod(), shutdownMethod);
	if ( ret )
		{
		if (shutdownMethod == KShutdownNormal)
			{
			aShutdown = RSocket::ENormal;
			}
		else if (shutdownMethod == KShutdownStopInput)
			{
			aShutdown = RSocket::EStopInput;
			}
		else if (shutdownMethod == KShutdownStopOutput)
			{
			aShutdown = RSocket::EStopOutput;
			}
		else if (shutdownMethod == KShutdownImmediate)
			{
			aShutdown = RSocket::EImmediate;
			}
		else
			{
			TInt	intMode;
			if ( aDataWrapper.GetIntFromConfig(aSection, KShutdownMethod(), intMode) )
				{
				aShutdown = (RSocket::TShutdown)intMode;
				}
			else
				{
				aDataWrapper.ERR_PRINTF2(_L("Illegal mode %S"), &KShutdownMethod());
				aDataWrapper.SetBlockResult(EFail);
				ret=EFalse;
				}
			}
		}

	return ret;
	}

void CT_BTUtil::GetTBTPacketType(CDataWrapper& aDataWrapper, const TDesC& aSection, TInt& aType)
	{
	TBuf<KMaxTestExecuteCommandLength>	tempStore;

	aType=0;
	TBool	moreData=ETrue;
	TInt	index=0;
	while ( moreData )
		{
		TPtrC	typeName;
		tempStore.Format(KPacketTypes(), &aSection, ++index);

		moreData=aDataWrapper.GetStringFromConfig(aSection, tempStore, typeName);
		if ( moreData )
			{
			if (typeName == KEPacketsDM1)
				{
				aType |= EPacketsDM1;
				}
			else if (typeName == KEPacketsDH1)
				{
				aType |= EPacketsDH1;
				}
			else if (typeName == KEPacketsDM3)
				{
				aType |= EPacketsDM3;
				}
			else if (typeName == KEPacketsDH3)
				{
				aType |= EPacketsDH3;
				}
			else if (typeName == KEPacketsDM5)
				{
				aType |= EPacketsDM5;
				}
			else if (typeName == KEPacketsDH5)
				{
				aType |= EPacketsDH5;
				}
			else if (typeName == KEPacketsHV1)
				{
				aType |= EPacketsHV1;
				}
		 	else if (typeName == KEPacketsHV2)
				{
				aType |= EPacketsHV2;
				}
		 	else if (typeName == KEPacketsHV3)
				{
				aType |= EPacketsHV3;
				}
		  	else if (typeName == KEAnyACLPacket)
				{
				aType |= EAnyACLPacket;
				}
		  	else if (typeName == KEAnySCOPacket)
				{
				aType |= EAnySCOPacket;
				}
		  	else if (typeName == KEAnyPacket)
				{
				aType |= EAnyPacket;
				}
			else
				{
				TInt	intType;
				if ( aDataWrapper.GetIntFromConfig(aSection, tempStore, intType) )
					{
					aType |= intType;
					}
				else
					{
					aDataWrapper.ERR_PRINTF2(_L("Illegal type %S"), &tempStore);
					aDataWrapper.SetBlockResult(EFail);
					}
				}
			}
		else if (index==1)
			{
			//Special case as we would want to use default if not found at all
			aType=EAnyPacket;
			}
		}
	}


void CT_BTUtil::GetLinkStateNotifierBits(CDataWrapper& aDataWrapper, const TDesC& aSection, TUint32& aModes)
	{
	// This is from BTTypes.h

	// Bitmask values for notifying/requesting notification of the state of a physical link.
	//
	// These values have a two fold purpose:
	// 1) They can be used along with TBTPhysicalLinkStateNotifierCombinations to specify
	// a set of baseband change events for which notification is desired.
	// 2) They can be used to notify the state of a physical link or a subset of that state.
	// For example if only mode change events are being monitored, then at each mode change event
	// only the bit reperesenting the new mode will be returned, however if the whole link state
	// is required, then a combination of bit values indicating that state will be returned.
	//
	// THESE BIT VALUES MUST ONLY BE USED WHEN REQUESTING NOTIFICATION, OR WHEN PARSING THE
	// RESULTS OF A NOTIFICATION. All other baseband state activities should use one of the
	// appropriate Bluetooth SIG specified enums
	// TBTBasebandRole, TBTLinkMode, TBTLinkModeCombinations, TBTPacketType,
	// TBTPacketTypeCombinations
	//

	TBuf<KMaxTestExecuteCommandLength>	tempStore;

	aModes=0;
	TBool	moreData=ETrue;
	TInt	index=0;
	while ( moreData )
		{
		TPtrC	modeName;
		tempStore.Format(KBaseBandMode(), &aSection, ++index);

		moreData=aDataWrapper.GetStringFromConfig(aSection, tempStore, modeName);
		if ( moreData )
			{
			//Master
			if (modeName == KENotifyMaster)
				{
				aModes |= ENotifyMaster;
				}
			//Slave
			else if (modeName == KENotifySlave)
				{
				aModes |= ENotifySlave;
				}
			//Active Mode
			else if (modeName == KENotifyActiveMode)
				{
				aModes |= ENotifyActiveMode;
				}
			//Sniff mode
			else if (modeName == KENotifySniffMode)
				{
				aModes |= ENotifySniffMode;
				}
			//Park mode
			else if (modeName == KENotifyParkMode)
				{
				aModes |= ENotifyParkMode;
				}
			//Hold mode
			else if (modeName == KENotifyHoldMode)
				{
				aModes |= ENotifyHoldMode;
				}
			//Max slots 1
			else if (modeName == KENotifyMaxSlots1)
				{
				aModes |= ENotifyMaxSlots1;
				}
			//Max slots 3
			else if (modeName == KENotifyMaxSlots3)
				{
				aModes |= ENotifyMaxSlots3;
				}
			//Max slots 5
			else if (modeName == KENotifyMaxSlots5)
				{
				aModes |= ENotifyMaxSlots5;
				}
			//Packets DM1
			else if (modeName == KENotifyPacketsDM1)
				{
				aModes |= ENotifyPacketsDM1;
				}
			//Packets DH1
			else if (modeName == KENotifyPacketsDH1)
				{
				aModes |= ENotifyPacketsDH1;
				}
			//Packets DM3
			else if (modeName == KENotifyPacketsDM3)
				{
				aModes |= ENotifyPacketsDM3;
				}
			//Packets DH3
			else if (modeName == KENotifyPacketsDH3)
				{
				aModes |= ENotifyPacketsDH3;
				}
			//Packets DM5
			else if (modeName == KENotifyPacketsDM5)
				{
				aModes |= ENotifyPacketsDM5;
				}
			//Packets DH5
			else if (modeName == KENotifyPacketsDH5)
				{
				aModes |= ENotifyPacketsDH5;
				}
			//HV1
			else if (modeName == KENotifyPacketsHV1)
				{
				aModes |= ENotifyPacketsHV1;
				}
			//HV2
			else if (modeName == KENotifyPacketsHV2)
				{
				aModes |= ENotifyPacketsHV2;
				}
			//HV3
			else if (modeName == KENotifyPacketsHV3)
				{
				aModes |= ENotifyPacketsHV3;
				}
			//Authentication Complete
			else if (modeName == KENotifyAuthenticationComplete)
				{
				aModes |= ENotifyAuthenticationComplete;
				}
			//Encryption Change On
			else if (modeName == KENotifyEncryptionChangeOn)
				{
				aModes |= ENotifyEncryptionChangeOn;
				}
			//Encryption Change Off
			else if (modeName == KENotifyEncryptionChangeOff)
				{
				aModes |= ENotifyEncryptionChangeOff;
				}
			//Physical Link Up
			else if (modeName == KENotifyPhysicalLinkUp)
				{
				aModes |= ENotifyPhysicalLinkUp;
				}
			//Physical Link Down
			else if (modeName == KENotifyPhysicalLinkDown)
				{
				aModes |= ENotifyPhysicalLinkDown;
				}
			//Physical Link Error
			else if (modeName == KENotifyPhysicalLinkError)
				{
				aModes |= ENotifyPhysicalLinkError;
				}
			//SCO Link Up
			else if (modeName == KENotifySCOLinkUp)
				{
				aModes |= ENotifySCOLinkUp;
				}
			//SCO Link Down
			else if (modeName == KENotifySCOLinkDown)
				{
				aModes |= ENotifySCOLinkDown;
				}
			//SCO Link Error
			else if (modeName == KENotifySCOLinkError)
				{
				aModes |= ENotifySCOLinkError;
				}
			else
				{
				TInt	intMode;
				if ( aDataWrapper.GetIntFromConfig(aSection, tempStore, intMode) )
					{
					aModes |= intMode;
					}
				else
					{
					aDataWrapper.ERR_PRINTF2(_L("Illegal type %S"), &KShutdownMethod());
					aDataWrapper.SetBlockResult(EFail);
					}
				}
			}
		}
	}

// method splitted in blocks to save stack space
TBool CT_BTUtil::GetIntValue(TPtrC aConstantName, TInt& aValue)
	{
	TBool	ret	= ETrue;
	// ************************************************************************
	// bt_sock.h
	// ************************************************************************
	_LIT(KBTAddrFamilyName,							"KBTAddrFamily");
	_LIT(KBTLinkManagerName,						"KBTLinkManager");
	_LIT(KL2CAPName,								"KL2CAP");
	_LIT(KRFCOMMName,								"KRFCOMM");
	_LIT(KSDPName,									"KSDP");
	_LIT(KAVCTPName,								"KAVCTP");
	_LIT(KTCIL2CAPName,								"KTCIL2CAP");
	_LIT(KBTMajorName,								"KBTMajor");
	_LIT(KBTMinorName,								"KBTMinor");
	_LIT(KBTBuildName,								"KBTBuild");
	_LIT(KSolBtBlogName,							"KSolBtBlog");
	_LIT(KSolBtHCIName,								"KSolBtHCI");
	_LIT(KSolBtLMName,								"KSolBtLM");
	_LIT(KSolBtL2CAPName,							"KSolBtL2CAP");
	_LIT(KSolBtRFCOMMName,							"KSolBtRFCOMM");
	_LIT(KSolBtAVCTPName,							"KSolBtAVCTP");
	_LIT(KSolBtACLName,								"KSolBtACL");
	_LIT(KSolBtAVDTPSignallingName,					"KSolBtAVDTPSignalling");
	_LIT(KSolBtAVDTPMediaName,						"KSolBtAVDTPMedia");
	_LIT(KSolBtAVDTPReportingName,					"KSolBtAVDTPReporting");
	_LIT(KSolBtAVDTPRecoveryName,					"KSolBtAVDTPRecovery");
	_LIT(KSolBtAVDTPInternalName,					"KSolBtAVDTPInternal");
	_LIT(KSolBtLMProxyName,							"KSolBtLMProxy");
	_LIT(KSolBtSAPBaseName,							"KSolBtSAPBase");
	_LIT(KSCOListenQueSizeName,						"KSCOListenQueSize");
	_LIT(KL2MinMTUName,								"KL2MinMTU");
	_LIT(KMaxPSMName,								"KMaxPSM");
	_LIT(KMinUserPSMName,							"KMinUserPSM");
	_LIT(KMinPSMName,								"KMinPSM");
	_LIT(KHostResInquiryName,						"KHostResInquiry");
	_LIT(KHostResNameName,							"KHostResName");
	_LIT(KHostResIgnoreCacheName,					"KHostResIgnoreCache");
	_LIT(KHostResCacheName,							"KHostResCache");
	_LIT(KL2CAPEchoRequestIoctlName,				"KL2CAPEchoRequestIoctl");
	_LIT(KL2CAPIncomingMTUIoctlName,				"KL2CAPIncomingMTUIoctl");
	_LIT(KL2CAPOutgoingMTUIoctlName,				"KL2CAPOutgoingMTUIoctl");
	_LIT(KL2CAPUpdateChannelConfigIoctlName,		"KL2CAPUpdateChannelConfigIoctl");
	_LIT(KDefaultBasebandConnectionTimeoutName,		"KDefaultBasebandConnectionTimeout");
	_LIT(KLMAddSCOConnIoctlName,					"KLMAddSCOConnIoctl");
	_LIT(KHCIRemoveSCOConnIoctlName,				"KHCIRemoveSCOConnIoctl");
	_LIT(KHCIChangePacketTypeIoctlName,				"KHCIChangePacketTypeIoctl");
	_LIT(KHCIAuthRequestIoctlName,					"KHCIAuthRequestIoctl");
	_LIT(KHCIEncryptIoctlName,						"KHCIAuthRequestIoctl");
	_LIT(KHCIChangeLinkKeyIoctlName,				"KHCIChangeLinkKeyIoctl");
	_LIT(KHCIMasterLinkKeyIoctlName,				"KHCIMasterLinkKeyIoctl");
	_LIT(KHCIHoldModeIoctlName,						"KHCIHoldModeIoctl");
	_LIT(KHCISniffModeIoctlName,					"KHCISniffModeIoctl");
	_LIT(KHCIExitSniffModeIoctlName,				"KHCIExitSniffModeIoctl");
	_LIT(KHCIParkModeIoctlName,						"KHCIParkModeIoctl");
	_LIT(KHCIExitParkModeIoctlName,					"KHCIExitParkModeIoctl");
	_LIT(KHCIReadPageTimeoutIoctlName,				"KHCIReadPageTimeoutIoctl");
	_LIT(KHCIWritePageTimeoutIoctlName,				"KHCIWritePageTimeoutIoctl");
	_LIT(KHCIReadScanEnableIoctlName,				"KHCIReadScanEnableIoctl");
	_LIT(KHCIWriteScanEnableIoctlName,				"KHCIWriteScanEnableIoctl");
	_LIT(KHCIReadDeviceClassIoctlName,				"KHCIReadDeviceClassIoctl");
	_LIT(KHCIWriteDeviceClassIoctlName,				"KHCIWriteDeviceClassIoctl");
	_LIT(KHCIReadVoiceSettingIoctlName,				"KHCIReadVoiceSettingIoctl");
	_LIT(KHCIWriteVoiceSettingIoctlName,			"KHCIWriteVoiceSettingIoctl");
	_LIT(KHCIReadHoldModeActivityIoctlName,			"KHCIReadHoldModeActivityIoctl");
	_LIT(KHCIWriteHoldModeActivityIoctlName,		"KHCIWriteHoldModeActivityIoctl");
	_LIT(KHCILocalVersionIoctlName,					"KHCILocalVersionIoctl");
	_LIT(KHCILocalFeaturesIoctlName,				"KHCILocalFeaturesIoctl");
	_LIT(KHCICountryCodeIoctlName,					"KHCICountryCodeIoctl");
	_LIT(KHCILocalAddressIoctlName,					"KHCILocalAddressIoctl");
	_LIT(KHCIWriteDiscoverabilityIoctlName,			"KHCIWriteDiscoverabilityIoctl");
	_LIT(KHCIReadDiscoverabilityIoctlName,			"KHCIReadDiscoverabilityIoctl");
	_LIT(KHCIReadAuthenticationEnableIoctlName,		"KHCIReadAuthenticationEnableIoctl");
	_LIT(KHCIWriteAuthenticationEnableIoctlName,	"KHCIWriteAuthenticationEnableIoctl");
	_LIT(KL2CAPPassiveAutoBindName,					"KL2CAPPassiveAutoBind");
	_LIT(KRFCOMMModemStatusCmdIoctlName,			"KRFCOMMModemStatusCmdIoctl");
	_LIT(KRFCOMMRemoteLineStatusCmdIoctlName,		"KRFCOMMRemoteLineStatusCmdIoctl");
	_LIT(KRFCOMMRemotePortNegCmdIoctlName,			"KRFCOMMRemotePortNegCmdIoctl");
	_LIT(KRFCOMMRemotePortNegRequestIoctlName,		"KRFCOMMRemotePortNegRequestIoctl");
	_LIT(KRFCOMMConfigChangeIndicationIoctlName,	"KRFCOMMConfigChangeIndicationIoctl");
	_LIT(KRFCOMMLocalPortParameterName,				"KRFCOMMLocalPortParameter");
	_LIT(KRFCOMMGetAvailableServerChannelName,		"KRFCOMMGetAvailableServerChannel");
	_LIT(KRFCOMMMaximumSupportedMTUName,			"KRFCOMMMaximumSupportedMTU");
	_LIT(KRFCOMMGetDebug1Name,						"KRFCOMMGetDebug1");
	_LIT(KRFCOMMGetRemoteModemStatusName,			"KRFCOMMGetRemoteModemStatus");
	_LIT(KRFCOMMGetTransmitCreditName,				"KRFCOMMGetTransmitCredit");
	_LIT(KRFCOMMGetReceiveCreditName,				"KRFCOMMGetReceiveCredit");
	_LIT(KRFCOMMGetReUsedCountName,					"KRFCOMMGetReUsedCount");
	_LIT(KRFCOMMFlowTypeCBFCName,					"KRFCOMMFlowTypeCBFC");
	_LIT(KRFCOMMLocalModemStatusName,				"KRFCOMMLocalModemStatus");
	_LIT(KErrBadHandleName,							"KErrBadHandle");
	_LIT(KZero,										"Zero");
	_LIT(KOne,										"One");
	_LIT(ELMOutboundACLSizeName,					"ELMOutboundACLSize");
	_LIT(ELMInboundACLSizeName,						"ELMInboundACLSize");
	_LIT(KLMGetACLHandleName,						"KLMGetACLHandle");
	_LIT(KLMGetACLLinkCountName,					"KLMGetACLLinkCount");
	_LIT(KLMGetACLLinkArrayName,					"KLMGetACLLinkArray");
	_LIT(KLMSetBasebandConnectionPolicyName,		"KLMSetBasebandConnectionPolicy");
	_LIT(KLMGetBasebandHandleName,					"KLMGetBasebandHandle");
	_LIT(EBBSubscribePhysicalLinkName,				"EBBSubscribePhysicalLink");
	_LIT(EBBBeginRawName,							"EBBBeginRaw");
	_LIT(EBBRequestRoleMasterName,					"EBBRequestRoleMaster");
	_LIT(EBBRequestRoleSlaveName,					"EBBRequestRoleSlave");
	_LIT(EBBCancelModeRequestName,					"EBBCancelModeRequest");
	_LIT(EBBRequestSniffName,						"EBBRequestSniff");
	_LIT(EBBRequestParkName,						"EBBRequestPark");
	_LIT(EBBRequestPreventRoleChangeName,			"EBBRequestPreventRoleChange");
	_LIT(EBBRequestAllowRoleChangeName,				"EBBRequestAllowRoleChange");
	_LIT(EBBRequestChangeSupportedPacketTypesName,	"EBBRequestChangeSupportedPacketTypes");
	_LIT(EBBEnumeratePhysicalLinksName,				"EBBEnumeratePhysicalLinks");
	_LIT(EBBGetPhysicalLinkStateName,				"EBBGetPhysicalLinkState");
	_LIT(EBBGetSniffIntervalName,					"EBBGetSniffInterval");
	_LIT(EBBRequestLinkAuthenticationName,			"EBBRequestLinkAuthentication");
	_LIT(EBBRequestPreventSniffName,				"EBBRequestPreventSniff");
	_LIT(EBBRequestPreventHoldName,					"EBBRequestPreventHold");
	_LIT(EBBRequestPreventParkName,					"EBBRequestPreventPark");
	_LIT(EBBRequestPreventAllLowPowerModesName,		"EBBRequestPreventAllLowPowerModes");
	_LIT(EBBRequestAllowSniffName,					"EBBRequestAllowSniff");
	_LIT(EBBRequestAllowHoldName,					"EBBRequestAllowHold");
	_LIT(EBBRequestAllowParkName,					"EBBRequestAllowPark");
	_LIT(EBBRequestAllowAllLowPowerModesName,		"EBBRequestAllowAllLowPowerModes");
	_LIT(KBTRegisterCodServiceName,					"KBTRegisterCodService");
	_LIT(KBTSecurityDeviceOverrideName,				"KBTSecurityDeviceOverride");
	_LIT(KESockDefaultMessageSlotsName,				"KESockDefaultMessageSlots");
	_LIT(KUseEmbeddedUniqueIdName,					"KUseEmbeddedUniqueId");
	_LIT(KConnProgressDefaultName,					"KConnProgressDefault");
	_LIT(KMaxSockAddrSizeName,						"KMaxSockAddrSize");
	_LIT(KAFUnspecName,								"KAFUnspec");
	_LIT(KSockStreamName,							"KSockStream");
	_LIT(KSockDatagramName,							"KSockDatagram");
	_LIT(KSockSeqPacketName,						"KSockSeqPacket");
	_LIT(KSockRawName,								"KSockRaw");
	_LIT(KSOLSocketName,							"KSOLSocket");
	_LIT(KLevelUnspecifiedName,						"KLevelUnspecified");
	_LIT(KSODebugName,								"KSODebug");
	_LIT(KSORecvBufName,							"KSORecvBuf");
	_LIT(KSOSendBufName,							"KSOSendBuf");
	_LIT(KSONonBlockingIOName,						"KSONonBlockingIO");
	_LIT(KSOBlockingIOName,							"KSOBlockingIO");
	_LIT(KSOSelectPollName,							"KSOSelectPoll");
	_LIT(KSOReadBytesPendingName,					"KSOReadBytesPending");
	_LIT(KSOUrgentDataOffsetName,					"KSOUrgentDataOffset");
	_LIT(KSOSelectLastErrorName,					"KSOSelectLastError");
	_LIT(KSOEnableTransferName,						"KSOEnableTransfer");
	_LIT(KSODisableTransferName,					"KSODisableTransfer");
	_LIT(KSocketBufSizeUndefinedName,				"KSocketBufSizeUndefined");
	_LIT(KSocketDefaultBufferSizeName,				"KSocketDefaultBufferSize");
	_LIT(KSocketInternalOptionBitName,				"KSocketInternalOptionBit");
	_LIT(KIOctlSelectName,							"KIOctlSelect");
	_LIT(KSockSelectReadName,						"KSockSelectRead");
	_LIT(KSockSelectWriteName,						"KSockSelectWrite");
	_LIT(KSockSelectExceptName,						"KSockSelectExcept");
	_LIT(KSockSelectReadContinuationName,			"KSockSelectReadContinuation");
	_LIT(KSockWriteUrgentName,						"KSockWriteUrgent");
	_LIT(KSocketInternalWriteBitName,				"KSocketInternalWriteBit");
	_LIT(KSockWriteSystemMaskName,					"KSockWriteSystemMask");
	_LIT(KSockReadPeekName,							"KSockReadPeek");
	_LIT(KSocketInternalReadBitName,				"KSocketInternalReadBit");
	_LIT(KSockReadContinuationName,					"KSockReadContinuation");
	_LIT(KSIConnectionLessName,						"KSIConnectionLess");
	_LIT(KSIReliableName,							"KSIReliable");
	_LIT(KSIInOrderName,							"KSIInOrder");
	_LIT(KSIMessageBasedName,						"KSIMessageBased");
	_LIT(KSIDatagramName,							"KSIDatagram");
	_LIT(KSIStreamBasedName,						"KSIStreamBased");
	_LIT(KSIPseudoStreamName,						"KSIPseudoStream");
	_LIT(KSIUrgentDataName,							"KSIUrgentData");
	_LIT(KSIConnectDataName,						"KSIConnectData");
	_LIT(KSIDisconnectDataName,						"KSIDisconnectData");
	_LIT(KSIBroadcastName,							"KSIBroadcast");
	_LIT(KSIMultiPointName,							"KSIMultiPoint");
	_LIT(KSIQOSName,								"KSIQOS");
	_LIT(KSIWriteOnlyName,							"KSIWriteOnly");
	_LIT(KSIReadOnlyName,							"KSIReadOnly");
	_LIT(KSIGracefulCloseName,						"KSIGracefulClose");
	_LIT(KSICanReconnectName,						"KSICanReconnect");
	_LIT(KSIPeekDataName,							"KSIPeekData");
	_LIT(KSIRequiresOwnerInfoName,					"KSIRequiresOwnerInfo");
	_LIT(KNSNameResolutionName,						"KNSNameResolution");
	_LIT(KNSHeirarchicalNamingName,					"KNSHeirarchicalNaming");
	_LIT(KNSRemoteDiscoveryName,					"KNSRemoteDiscovery");
	_LIT(KNSServiceResolutionName,					"KNSServiceResolution");
	_LIT(KNSNameRegistrationName,					"KNSNameRegistration");
	_LIT(KNSServiceRegistrationName,				"KNSServiceRegistration");
	_LIT(KNSDynamicAddressingName,					"KNSDynamicAddressing");
	_LIT(KNSInfoDatabaseName,						"KNSInfoDatabase");
	_LIT(KNSRequiresConnectionStartupName,			"KNSRequiresConnectionStartup");
	_LIT(KSocketNoSecurityName,						"KSocketNoSecurity");
	_LIT(KSecureSocketsName,						"KSecureSockets");
	_LIT(KSocketMessageSizeIsStreamName,			"KSocketMessageSizeIsStream");
	_LIT(KSocketMessageSizeUndefinedName,			"KSocketMessageSizeUndefined");
	_LIT(KSocketMessageSizeNoLimitName,				"KSocketMessageSizeNoLimit");
	_LIT(KUndefinedSockTypeName,					"KUndefinedSockType");
	_LIT(KUndefinedProtocolName,					"KUndefinedProtocol");
	_LIT(KErrWouldBlockName,						"KErrWouldBlock");
	_LIT(KErrConnectionTerminatedName,				"KErrConnectionTerminated");
	_LIT(KErrCannotFindProtocolName,				"KErrCannotFindProtocol");
	_LIT(KCOLConnectionName,						"KCOLConnection");
	_LIT(KCOLProviderName,							"KCOLProvider");
	_LIT(KConnInternalOptionBitName,				"KConnInternalOptionBit");
	_LIT(KConnWriteUserDataBitName,					"KConnWriteUserDataBit");
	_LIT(KConnReadUserDataBitName,					"KConnReadUserDataBit");
	_LIT(KCoEnumerateConnectionClientsName,			"KCoEnumerateConnectionClients");
	_LIT(KCoGetConnectionClientInfoName,			"KCoGetConnectionClientInfo");
	_LIT(KCoGetConnectionSocketInfoName,			"KCoGetConnectionSocketInfo");
	_LIT(KConnectionTypeDefaultName,				"KConnectionTypeDefault");
	_LIT(KSubConnParamsInterfaceUidName,			"KSubConnParamsInterfaceUid");
	_LIT(KSubConnEventInterfaceUidName,				"KSubConnEventInterfaceUid");
	_LIT(KSubConnGenericParamsImplUidName,			"KSubConnGenericParamsImplUid");
	_LIT(KSubConnGenericEventsImplUidName,			"KSubConnGenericEventsImplUid");
	_LIT(KSubConGlobalFamilyName,					"KSubConGlobalFamily");
	_LIT(KSubConQoSFamilyName,						"KSubConQoSFamily");
	_LIT(KSubConAuthorisationFamilyName,			"KSubConAuthorisationFamily");
	_LIT(KNotificationEventMaxSizeName,				"KNotificationEventMaxSize");

	// BT Address Family
	if (aConstantName==KBTAddrFamilyName)
		{
		aValue=KBTAddrFamily;
		}
	else if (aConstantName==KBTLinkManagerName)
		{
		aValue=KBTLinkManager;
		}
	else if (aConstantName==KL2CAPName)
		{
		aValue=KL2CAP;
		}
	else if (aConstantName==KRFCOMMName)
		{
		aValue=KRFCOMM;
		}
	else if (aConstantName==KSDPName)
		{
		aValue=KSDP;
		}
	else if (aConstantName==KAVCTPName)
		{
		aValue=KAVCTP;
		}
	else if (aConstantName==KTCIL2CAPName)
		{
		aValue=KTCIL2CAP;
		}
	else if (aConstantName==KBTMajorName)
		{
		aValue=KBTMajor;
		}
	else if (aConstantName==KBTMinorName)
		{
		aValue=KBTMinor;
		}
	else if (aConstantName==KBTBuildName)
		{
		aValue=KBTBuild;
		}
	else if (aConstantName==KSolBtBlogName)
		{
		aValue=KSolBtBlog;
		}
	else if (aConstantName==KSolBtHCIName)
		{
		aValue=KSolBtHCI;
		}
	else if (aConstantName==KSolBtLMName)
		{
		aValue=KSolBtLM;
		}
	else if (aConstantName==KSolBtL2CAPName)
		{
		aValue=KSolBtL2CAP;
		}
	else if (aConstantName==KSolBtRFCOMMName)
		{
		aValue=KSolBtRFCOMM;
		}
	else if (aConstantName==KSolBtAVCTPName)
		{
		aValue=KSolBtAVCTP;
		}
	else if (aConstantName==KSolBtACLName)
		{
		aValue=KSolBtACL;
		}
	else if (aConstantName==KSolBtAVDTPSignallingName)
		{
		aValue=KSolBtAVDTPSignalling;
		}
	else if (aConstantName==KSolBtAVDTPMediaName)
		{
		aValue=KSolBtAVDTPMedia;
		}
	else if (aConstantName==KSolBtAVDTPReportingName)
		{
		aValue=KSolBtAVDTPReporting;
		}
	else if (aConstantName==KSolBtAVDTPRecoveryName)
		{
		aValue=KSolBtAVDTPRecovery;
		}
	else if (aConstantName==KSolBtAVDTPInternalName)
		{
		aValue=KSolBtAVDTPInternal;
		}
	else if (aConstantName==KSolBtLMProxyName)
		{
		aValue=KSolBtLMProxy;
		}
	else if (aConstantName==KSolBtSAPBaseName)
		{
		aValue=KSolBtSAPBase;
		}
	else if (aConstantName==KSCOListenQueSizeName)
		{
		aValue=KSCOListenQueSize;
		}
	else if (aConstantName==KL2MinMTUName)
		{
		aValue=KL2MinMTU;
		}
	else if (aConstantName==KMaxPSMName)
		{
		aValue=KMaxPSM;
		}
	else if (aConstantName==KMinUserPSMName)
		{
		aValue=KMinUserPSM;
		}
	else if (aConstantName==KMinPSMName)
		{
		aValue=KMinPSM;
		}
	else if (aConstantName==KHostResInquiryName)
		{
		aValue=KHostResInquiry;
		}
	else if (aConstantName==KHostResNameName)
		{
		aValue=KHostResName;
		}
	else if (aConstantName==KHostResIgnoreCacheName)
		{
		aValue=KHostResIgnoreCache;
		}
	else if (aConstantName==KHostResCacheName)
		{
		aValue=KHostResCache;
		}
	else if (aConstantName==KL2CAPEchoRequestIoctlName)
		{
		aValue=KL2CAPEchoRequestIoctl;
		}
	else if (aConstantName==KL2CAPIncomingMTUIoctlName)
		{
		aValue=KL2CAPIncomingMTUIoctl;
		}
	else if (aConstantName==KL2CAPOutgoingMTUIoctlName)
		{
		aValue=KL2CAPOutgoingMTUIoctl;
		}
	else if (aConstantName==KL2CAPUpdateChannelConfigIoctlName)
		{
		aValue=KL2CAPUpdateChannelConfigIoctl;
		}
	else if (aConstantName==KDefaultBasebandConnectionTimeoutName)
		{
		aValue=KDefaultBasebandConnectionTimeout;
		}
	else if (aConstantName==KLMAddSCOConnIoctlName)
		{
		aValue=KLMAddSCOConnIoctl;
		}
	else if (aConstantName==KHCIRemoveSCOConnIoctlName)
		{
		aValue=KHCIRemoveSCOConnIoctl;
		}
	else if (aConstantName==KHCIChangePacketTypeIoctlName)
		{
		aValue=KHCIChangePacketTypeIoctl;
		}
	else if (aConstantName==KHCIAuthRequestIoctlName)
		{
		aValue=KHCIAuthRequestIoctl;
		}
	else if (aConstantName==KHCIEncryptIoctlName)
		{
		aValue=KHCIEncryptIoctl;
		}
	else if (aConstantName==KHCIChangeLinkKeyIoctlName)
		{
		aValue=KHCIChangeLinkKeyIoctl;
		}
	else if (aConstantName==KHCIMasterLinkKeyIoctlName)
		{
		aValue=KHCIMasterLinkKeyIoctl;
		}
	else if (aConstantName==KHCIHoldModeIoctlName)
		{
		aValue=KHCIHoldModeIoctl;
		}
	else if (aConstantName==KHCISniffModeIoctlName)
		{
		aValue=KHCISniffModeIoctl;
		}
	else if (aConstantName==KHCIExitSniffModeIoctlName)
		{
		aValue=KHCIExitSniffModeIoctl;
		}
	else if (aConstantName==KHCIParkModeIoctlName)
		{
		aValue=KHCIParkModeIoctl;
		}
	else if (aConstantName==KHCIExitParkModeIoctlName)
		{
		aValue=KHCIExitParkModeIoctl;
		}
	else if (aConstantName==KHCIReadPageTimeoutIoctlName)
		{
		aValue=KHCIReadPageTimeoutIoctl;
		}
	else if (aConstantName==KHCIWritePageTimeoutIoctlName)
		{
		aValue=KHCIWritePageTimeoutIoctl;
		}
	else if (aConstantName==KHCIReadScanEnableIoctlName)
		{
		aValue=KHCIReadScanEnableIoctl;
		}
	else if (aConstantName==KHCIWriteScanEnableIoctlName)
		{
		aValue=KHCIWriteScanEnableIoctl;
		}
	else if (aConstantName==KHCIReadDeviceClassIoctlName)
		{
		aValue=KHCIReadDeviceClassIoctl;
		}
	else if (aConstantName==KHCIWriteDeviceClassIoctlName)
		{
		aValue=KHCIWriteDeviceClassIoctl;
		}
	else if (aConstantName==KHCIReadVoiceSettingIoctlName)
		{
		aValue=KHCIReadVoiceSettingIoctl;
		}
	else if (aConstantName==KHCIWriteVoiceSettingIoctlName)
		{
		aValue=KHCIWriteVoiceSettingIoctl;
		}
	else if (aConstantName==KHCIReadHoldModeActivityIoctlName)
		{
		aValue=KHCIReadHoldModeActivityIoctl;
		}
	else if (aConstantName==KHCIWriteHoldModeActivityIoctlName)
		{
		aValue=KHCIWriteHoldModeActivityIoctl;
		}
	else if (aConstantName==KHCILocalVersionIoctlName)
		{
		aValue=KHCILocalVersionIoctl;
		}
	else if (aConstantName==KHCILocalFeaturesIoctlName)
		{
		aValue=KHCILocalFeaturesIoctl;
		}
	else if (aConstantName==KHCICountryCodeIoctlName)
		{
		aValue=KHCICountryCodeIoctl;
		}
	else if (aConstantName==KHCILocalAddressIoctlName)
		{
		aValue=KHCILocalAddressIoctl;
		}
	else if (aConstantName==KHCIWriteDiscoverabilityIoctlName)
		{
		aValue=KHCIWriteDiscoverabilityIoctl;
		}
	else if (aConstantName==KHCIReadDiscoverabilityIoctlName)
		{
		aValue=KHCIReadDiscoverabilityIoctl;
		}
	else if (aConstantName==KHCIReadAuthenticationEnableIoctlName)
		{
		aValue=KHCIReadAuthenticationEnableIoctl;
		}
	else if (aConstantName==KHCIWriteAuthenticationEnableIoctlName)
		{
		aValue=KHCIWriteAuthenticationEnableIoctl;
		}
	else if (aConstantName==KL2CAPPassiveAutoBindName)
		{
		aValue=KL2CAPPassiveAutoBind;
		}
	else if (aConstantName==KRFCOMMModemStatusCmdIoctlName)
		{
		aValue=KRFCOMMModemStatusCmdIoctl;
		}
	else if (aConstantName==KRFCOMMRemoteLineStatusCmdIoctlName)
		{
		aValue=KRFCOMMRemoteLineStatusCmdIoctl;
		}
	else if (aConstantName==KRFCOMMRemotePortNegCmdIoctlName)
		{
		aValue=KRFCOMMRemotePortNegCmdIoctl;
		}
	else if (aConstantName==KRFCOMMRemotePortNegRequestIoctlName)
		{
		aValue=KRFCOMMRemotePortNegRequestIoctl;
		}
	else if (aConstantName==KRFCOMMConfigChangeIndicationIoctlName)
		{
		aValue=KRFCOMMConfigChangeIndicationIoctl;
		}
	else if (aConstantName==KRFCOMMLocalPortParameterName)
		{
		aValue=KRFCOMMLocalPortParameter;
		}
	else if (aConstantName==KRFCOMMGetAvailableServerChannelName)
		{
		aValue=KRFCOMMGetAvailableServerChannel;
		}
	else if (aConstantName==KRFCOMMMaximumSupportedMTUName)
		{
		aValue=KRFCOMMMaximumSupportedMTU;
		}
	else if (aConstantName==KRFCOMMGetDebug1Name)
		{
		aValue=KRFCOMMGetDebug1;
		}
	else if (aConstantName==KRFCOMMGetRemoteModemStatusName)
		{
		aValue=KRFCOMMGetRemoteModemStatus;
		}
	else if (aConstantName==KRFCOMMGetTransmitCreditName)
		{
		aValue=KRFCOMMGetTransmitCredit;
		}
	else if (aConstantName==KRFCOMMGetReceiveCreditName)
		{
		aValue=KRFCOMMGetReceiveCredit;
		}
	else if (aConstantName==KRFCOMMGetReUsedCountName)
		{
		aValue=KRFCOMMGetReUsedCount;
		}
	else if (aConstantName==KRFCOMMFlowTypeCBFCName)
		{
		aValue=KRFCOMMFlowTypeCBFC;
		}
	else if (aConstantName==KRFCOMMLocalModemStatusName)
		{
		aValue=KRFCOMMLocalModemStatus;
		}
	else if (aConstantName==KErrBadHandleName)
		{
		aValue=KErrBadHandle;
		}
	else if (aConstantName==KZero)
		{
		aValue=0;
		}
	else if (aConstantName==KOne)
		{
		aValue=1;
		}
	else if (aConstantName==ELMOutboundACLSizeName)
		{
		aValue=ELMOutboundACLSize;
		}
	else if (aConstantName==ELMInboundACLSizeName)
		{
		aValue=ELMInboundACLSize;
		}
	else if (aConstantName==KLMGetACLHandleName)
		{
		aValue=KLMGetACLHandle;
		}
	else if (aConstantName==KLMGetACLLinkCountName)
		{
		aValue=KLMGetACLLinkCount;
		}
	else if (aConstantName==KLMGetACLLinkArrayName)
		{
		aValue=KLMGetACLLinkArray;
		}
	else if (aConstantName==KLMSetBasebandConnectionPolicyName)
		{
		aValue=KLMSetBasebandConnectionPolicy;
		}
	else if (aConstantName==KLMGetBasebandHandleName)
		{
		aValue=KLMGetBasebandHandle;
		}
	else if (aConstantName==EBBSubscribePhysicalLinkName)
		{
		aValue=EBBSubscribePhysicalLink;
		}
	else if (aConstantName==EBBBeginRawName)
		{
		aValue=EBBBeginRaw;
		}
	else if (aConstantName==EBBRequestRoleMasterName)
		{
		aValue=EBBRequestRoleMaster;
		}
	else if (aConstantName==EBBRequestRoleSlaveName)
		{
		aValue=EBBRequestRoleSlave;
		}
	else if (aConstantName==EBBCancelModeRequestName)
		{
		aValue=EBBCancelModeRequest;
		}
	else if (aConstantName==EBBRequestSniffName)
		{
		aValue=EBBRequestSniff;
		}
	else if (aConstantName==EBBRequestParkName)
		{
		aValue=EBBRequestPark;
		}
	else if (aConstantName==EBBRequestPreventRoleChangeName)
		{
		aValue=EBBRequestPreventRoleChange;
		}
	else if (aConstantName==EBBRequestAllowRoleChangeName)
		{
		aValue=EBBRequestAllowRoleChange;
		}
	else if (aConstantName==EBBRequestChangeSupportedPacketTypesName)
		{
		aValue=EBBRequestChangeSupportedPacketTypes;
		}
	else if (aConstantName==EBBEnumeratePhysicalLinksName)
		{
		aValue=EBBEnumeratePhysicalLinks;
		}
	else if (aConstantName==EBBGetPhysicalLinkStateName)
		{
		aValue=EBBGetPhysicalLinkState;
		}
	else if (aConstantName==EBBGetSniffIntervalName)
		{
		aValue=EBBGetSniffInterval;
		}
#if 0 //Commented by Vaibhav : Not Needed		
	else if (aConstantName==EBBRequestLinkAuthenticationName)
		{
		aValue=EBBRequestLinkAuthentication;
		}
#endif		
	else if (aConstantName==EBBRequestPreventSniffName)
		{
		aValue=EBBRequestPreventSniff;
		}
	else if (aConstantName==EBBRequestPreventHoldName)
		{
		aValue=EBBRequestPreventHold;
		}
	else if (aConstantName==EBBRequestPreventParkName)
		{
		aValue=EBBRequestPreventPark;
		}
	else if (aConstantName==EBBRequestPreventAllLowPowerModesName)
		{
		aValue=EBBRequestPreventAllLowPowerModes;
		}
	else if (aConstantName==EBBRequestAllowSniffName)
		{
		aValue=EBBRequestAllowSniff;
		}
	else if (aConstantName==EBBRequestAllowHoldName)
		{
		aValue=EBBRequestAllowHold;
		}
	else if (aConstantName==EBBRequestAllowParkName)
		{
		aValue=EBBRequestAllowPark;
		}
	else if (aConstantName==EBBRequestAllowAllLowPowerModesName)
		{
		aValue=EBBRequestAllowAllLowPowerModes;
		}
	else if (aConstantName==KBTRegisterCodServiceName)
		{
		aValue=KBTRegisterCodService;
		}
	else if (aConstantName==KBTSecurityDeviceOverrideName)
		{
		aValue=KBTSecurityDeviceOverride;
		}
	else if (aConstantName==KESockDefaultMessageSlotsName)
		{
		aValue=KESockDefaultMessageSlots;
		}
	else if (aConstantName==KUseEmbeddedUniqueIdName)
		{
		aValue=KUseEmbeddedUniqueId;
		}
	else if (aConstantName==KConnProgressDefaultName)
		{
		aValue=KConnProgressDefault;
		}
	else if (aConstantName==KMaxSockAddrSizeName)
		{
		aValue=KMaxSockAddrSize;
		}
	else if (aConstantName==KAFUnspecName)
		{
		aValue=KAFUnspec;
		}
	else if (aConstantName==KSockStreamName)
		{
		aValue=KSockStream;
		}
	else if (aConstantName==KSockDatagramName)
		{
		aValue=KSockDatagram;
		}
	else if (aConstantName==KSockSeqPacketName)
		{
		aValue=KSockSeqPacket;
		}
	else if (aConstantName==KSockRawName)
		{
		aValue=KSockRaw;
		}
	else if (aConstantName==KSOLSocketName)
		{
		aValue=KSOLSocket;
		}
	else if (aConstantName==KLevelUnspecifiedName)
		{
		aValue=KLevelUnspecified;
		}
	else if (aConstantName==KSODebugName)
		{
		aValue=KSODebug;
		}
	else if (aConstantName==KSORecvBufName)
		{
		aValue=KSORecvBuf;
		}
	else if (aConstantName==KSOSendBufName)
		{
		aValue=KSOSendBuf;
		}
	else if (aConstantName==KSONonBlockingIOName)
		{
		aValue=KSONonBlockingIO;
		}
	else if (aConstantName==KSOBlockingIOName)
		{
		aValue=KSOBlockingIO;
		}
	else if (aConstantName==KSOSelectPollName)
		{
		aValue=KSOSelectPoll;
		}
	else if (aConstantName==KSOReadBytesPendingName)
		{
		aValue=KSOReadBytesPending;
		}
	else if (aConstantName==KSOUrgentDataOffsetName)
		{
		aValue=KSOUrgentDataOffset;
		}
	else if (aConstantName==KSOSelectLastErrorName)
		{
		aValue=KSOSelectLastError;
		}
	else if (aConstantName==KSOEnableTransferName)
		{
		aValue=KSOEnableTransfer;
		}
	else if (aConstantName==KSODisableTransferName)
		{
		aValue=KSODisableTransfer;
		}
	else if (aConstantName==KSocketBufSizeUndefinedName)
		{
		aValue=KSocketBufSizeUndefined;
		}
	else if (aConstantName==KSocketDefaultBufferSizeName)
		{
		aValue=KSocketDefaultBufferSize;
		}
	else if (aConstantName==KSocketInternalOptionBitName)
		{
		aValue=KSocketInternalOptionBit;
		}
	else if (aConstantName==KIOctlSelectName)
		{
		aValue=KIOctlSelect;
		}
	else if (aConstantName==KSockSelectReadName)
		{
		aValue=KSockSelectRead;
		}
	else if (aConstantName==KSockSelectWriteName)
		{
		aValue=KSockSelectWrite;
		}
	else if (aConstantName==KSockSelectExceptName)
		{
		aValue=KSockSelectExcept;
		}
	else if (aConstantName==KSockSelectReadContinuationName)
		{
		aValue=KSockSelectReadContinuation;
		}
	else if (aConstantName==KSockWriteUrgentName)
		{
		aValue=KSockWriteUrgent;
		}
	else if (aConstantName==KSocketInternalWriteBitName)
		{
		aValue=KSocketInternalWriteBit;
		}
	else if (aConstantName==KSockWriteSystemMaskName)
		{
		aValue=KSockWriteSystemMask;
		}
	else if (aConstantName==KSockReadPeekName)
		{
		aValue=KSockReadPeek;
		}
	else if (aConstantName==KSocketInternalReadBitName)
		{
		aValue=KSocketInternalReadBit;
		}
	else if (aConstantName==KSockReadContinuationName)
		{
		aValue=KSockReadContinuation;
		}
	else if (aConstantName==KSIConnectionLessName)
		{
		aValue=KSIConnectionLess;
		}
	else if (aConstantName==KSIReliableName)
		{
		aValue=KSIReliable;
		}
	else if (aConstantName==KSIInOrderName)
		{
		aValue=KSIInOrder;
		}
	else if (aConstantName==KSIMessageBasedName)
		{
		aValue=KSIMessageBased;
		}
	else if (aConstantName==KSIDatagramName)
		{
		aValue=KSIDatagram;
		}
	else if (aConstantName==KSIStreamBasedName)
		{
		aValue=KSIStreamBased;
		}
	else if (aConstantName==KSIPseudoStreamName)
		{
		aValue=KSIPseudoStream;
		}
	else if (aConstantName==KSIUrgentDataName)
		{
		aValue=KSIUrgentData;
		}
	else if (aConstantName==KSIConnectDataName)
		{
		aValue=KSIConnectData;
		}
	else if (aConstantName==KSIDisconnectDataName)
		{
		aValue=KSIDisconnectData;
		}
	else if (aConstantName==KSIBroadcastName)
		{
		aValue=KSIBroadcast;
		}
	else if (aConstantName==KSIMultiPointName)
		{
		aValue=KSIMultiPoint;
		}
	else if (aConstantName==KSIQOSName)
		{
		aValue=KSIQOS;
		}
	else if (aConstantName==KSIWriteOnlyName)
		{
		aValue=KSIWriteOnly;
		}
	else if (aConstantName==KSIReadOnlyName)
		{
		aValue=KSIReadOnly;
		}
	else if (aConstantName==KSIGracefulCloseName)
		{
		aValue=KSIGracefulClose;
		}
	else if (aConstantName==KSICanReconnectName)
		{
		aValue=KSICanReconnect;
		}
	else if (aConstantName==KSIPeekDataName)
		{
		aValue=KSIPeekData;
		}
	else if (aConstantName==KSIRequiresOwnerInfoName)
		{
		aValue=KSIRequiresOwnerInfo;
		}
	else if (aConstantName==KNSNameResolutionName)
		{
		aValue=KNSNameResolution;
		}
	else if (aConstantName==KNSHeirarchicalNamingName)
		{
		aValue=KNSHeirarchicalNaming;
		}
	else if (aConstantName==KNSRemoteDiscoveryName)
		{
		aValue=KNSRemoteDiscovery;
		}
	else if (aConstantName==KNSServiceResolutionName)
		{
		aValue=KNSServiceResolution;
		}
	else if (aConstantName==KNSNameRegistrationName)
		{
		aValue=KNSNameRegistration;
		}
	else if (aConstantName==KNSServiceRegistrationName)
		{
		aValue=KNSServiceRegistration;
		}
	else if (aConstantName==KNSDynamicAddressingName)
		{
		aValue=KNSDynamicAddressing;
		}
	else if (aConstantName==KNSInfoDatabaseName)
		{
		aValue=KNSInfoDatabase;
		}
	else if (aConstantName==KNSRequiresConnectionStartupName)
		{
		aValue=KNSRequiresConnectionStartup;
		}
	else if (aConstantName==KSocketNoSecurityName)
		{
		aValue=KSocketNoSecurity;
		}
	else if (aConstantName==KSecureSocketsName)
		{
		aValue=KSecureSockets;
		}
	else if (aConstantName==KSocketMessageSizeIsStreamName)
		{
		aValue=KSocketMessageSizeIsStream;
		}
	else if (aConstantName==KSocketMessageSizeUndefinedName)
		{
		aValue=KSocketMessageSizeUndefined;
		}
	else if (aConstantName==KSocketMessageSizeNoLimitName)
		{
		aValue=KSocketMessageSizeNoLimit;
		}
	else if (aConstantName==KUndefinedSockTypeName)
		{
		aValue=KUndefinedSockType;
		}
	else if (aConstantName==KUndefinedProtocolName)
		{
		aValue=KUndefinedProtocol;
		}
	else if (aConstantName==KErrWouldBlockName)
		{
		aValue=KErrWouldBlock;
		}
	else if (aConstantName==KErrConnectionTerminatedName)
		{
		aValue=KErrConnectionTerminated;
		}
	else if (aConstantName==KErrCannotFindProtocolName)
		{
		aValue=KErrCannotFindProtocol;
		}
	else if (aConstantName==KCOLConnectionName)
		{
		aValue=KCOLConnection;
		}
	else if (aConstantName==KCOLProviderName)
		{
		aValue=KCOLProvider;
		}
	else if (aConstantName==KConnInternalOptionBitName)
		{
		aValue=KConnInternalOptionBit;
		}
	else if (aConstantName==KConnWriteUserDataBitName)
		{
		aValue=KConnWriteUserDataBit;
		}
	else if (aConstantName==KConnReadUserDataBitName)
		{
		aValue=KConnReadUserDataBit;
		}
	else if (aConstantName==KCoEnumerateConnectionClientsName)
		{
		aValue=KCoEnumerateConnectionClients;
		}
	else if (aConstantName==KCoGetConnectionClientInfoName)
		{
		aValue=KCoGetConnectionClientInfo;
		}
	else if (aConstantName==KCoGetConnectionSocketInfoName)
		{
		aValue=KCoGetConnectionSocketInfo;
		}
	else if (aConstantName==KConnectionTypeDefaultName)
		{
		aValue=KConnectionTypeDefault;
		}
	else if (aConstantName==KSubConnParamsInterfaceUidName)
		{
		aValue=KSubConnParamsInterfaceUid;
		}
	else if (aConstantName==KSubConnEventInterfaceUidName)
		{
		aValue=KSubConnEventInterfaceUid;
		}
	else if (aConstantName==KSubConnGenericParamsImplUidName)
		{
		aValue=KSubConnGenericParamsImplUid;
		}
	else if (aConstantName==KSubConnGenericEventsImplUidName)
		{
		aValue=KSubConnGenericEventsImplUid;
		}
	else if (aConstantName==KSubConGlobalFamilyName)
		{
		aValue=KSubConGlobalFamily;
		}
	else if (aConstantName==KSubConQoSFamilyName)
		{
		aValue=KSubConQoSFamily;
		}
	else if (aConstantName==KSubConAuthorisationFamilyName)
		{
		aValue=KSubConAuthorisationFamily;
		}
	else if (aConstantName==KNotificationEventMaxSizeName)
		{
		aValue=KNotificationEventMaxSize;
		}
	else
		{
		ret=EFalse;
		aValue=-1;
		}

	return ret;
	}
