@rem
@rem Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
@rem All rights reserved.
@rem This component and the accompanying materials are made available
@rem under the terms of "Eclipse Public License v1.0"
@rem which accompanies this distribution, and is available
@rem at the URL "http://www.eclipse.org/legal/epl-v10.html".
@rem
@rem Initial Contributors:
@rem Nokia Corporation - initial contribution.
@rem
@rem Contributors:
@rem
@rem Description: 
@rem
  

md e:\bctest\
md e:\bctest\results

ATSINTERFACE.EXE -testmodule featuremanagertest

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_FeatureManager.txt

ATSINTERFACE.EXE -testmodule finditemenginetest

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_FindItemEngine.txt

ATSINTERFACE.EXE -testmodule light

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_Light.txt

ATSINTERFACE.EXE -testmodule PhoneParserTest

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_PhoneParser.txt

ATSINTERFACE.EXE -testmodule PlatformEnvTest

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_PlatformEnv.txt

ATSINTERFACE.EXE -testmodule PowerStateTest

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_PowerState.txt

ATSINTERFACE.EXE -testmodule sysutiltest

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_SysUtil.txt

ATSINTERFACE.EXE -testmodule stiftextresolvertest

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_StifTextResolver.txt

ATSINTERFACE.EXE -testmodule HwResManTest

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_HwResMan.txt

vibration.exe

ATSINTERFACE.EXE -testmodule vibractrltest

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\SystemSoftware_VibraCtrl.txt

LogFileReader.exe c:\logs\TestFramework\SystemSW\vibration_Preconfig.txt	e:\bctest\results\DeviceSrv_SystemSoftware_VibraCtrl.txt
copy 6edcba99.txt c:\private\10202be9\6edcba99.txt

ATSINTERFACE.EXE -testmodule cenrepnotifyhandlertest

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_CenRepNotifyHandler.txt

ATSINTERFACE.EXE -testmodule PlatformVerTest

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_PlatformVer.txt

ATSINTERFACE.EXE -testmodule AccMonAPIBCTests

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_accmonitoring.txt

ATSINTERFACE.EXE -testmodule SystemSWMisc50Test

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_SystemSWMisc50Test.txt

ATSINTERFACE.EXE -testmodule SystemSWMisc52Test

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\DeviceSrv_SystemSoftware_SystemSWMisc52Test.txt