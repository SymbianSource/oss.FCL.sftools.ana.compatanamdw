@rem
@rem Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
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


md e:\BCTest
md e:\BCTest\Results



copy C:\TestFramework\TestFramework_cppwrap.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\bccppwrap.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_cppwrap.txt



copy C:\TestFramework\TestFramework_mrtruntime.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\bccsruntimesup.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_csruntime.txt


copy C:\TestFramework\TestFramework_mrtexp.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\BCException.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_exception.txt


copy C:\TestFramework\TestFramework_mrtnons.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\BCNoNamespace.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_nonamespace.txt


copy C:\TestFramework\TestFramework_mrtopenc.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\BCOpenCHeaders.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_opencheaders.txt


copy C:\TestFramework\TestFramework_ocw.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\BCOpenCWrap.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_opencwrap.txt


copy C:\TestFramework\TestFramework_mrtthread.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\bcthread.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_thread.txt


copy C:\TestFramework\TestFramework_mrttypea.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\BCTypeAttrib.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_typeattrib.txt


copy C:\TestFramework\TestFramework_mrttypei.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\BCTypeInfo.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_typeinfo.txt


copy C:\TestFramework\TestFramework_ct.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule chartypes
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_chartypes.txt


copy C:\TestFramework\TestFramework_mrtmath.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\tmath_operations.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_mathoperations.txt


copy C:\TestFramework\TestFramework_mrtmem.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\tmemory.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_tmemory.txt


copy C:\TestFramework\TestFramework_mrtutil.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\tutility.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_utility.txt


copy C:\TestFramework\testframework_wc.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule widecharclassapiBCTest
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_widecharclass.txt


copy C:\TestFramework\TestFramework_tstl_1.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\tstl_1.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_tstl.txt


copy C:\TestFramework\TestFramework_tlocale.ini C:\TestFramework\TestFramework.ini
ATSINTERFACE.EXE -testmodule testscripter -config C:\TestFramework\tlocale.cfg
copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\OsSrv_Stdcpp_tlocale.txt
