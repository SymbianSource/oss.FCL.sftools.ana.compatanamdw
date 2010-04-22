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

md e:\BCTest
md e:\BCTest\results

testexecute \tstdapis\tcomport.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tcomport.htm
testexecute \tstdapis\tctype.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tctype.htm
testexecute \tstdapis\tdb_blr.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tdb_blr.htm
testexecute \tstdapis\tftw.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tftw.htm
testexecute \tstdapis\tglob_test.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tglob_test.htm
testexecute \tstdapis\tlibcwchar.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tlibcwchar.htm
testexecute \tstdapis\tlink.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tlink.htm
testexecute \tstdapis\tloc_blr.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tloc_blr.htm
testexecute \tstdapis\tmkfifo.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tmkfifo.htm
testexecute \tstdapis\tmmap.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tmmap.htm
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tprogname.htm
testexecute \tstdapis\tregex.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tregex.htm
testexecute \tstdapis\tselect.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tselect.htm
testexecute \tstdapis\tsemaphore.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tsemaphore.htm
testexecute \tstdapis\tstdio_auto.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tstdio_auto.htm
testexecute \tstdapis\tstdio_fileop.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tstdio_fileop.htm
testexecute \tstdapis\tsyscalls.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tsyscalls.htm
testexecute \tstdapis\tsyscalls1.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tsyscalls1.htm
testexecute \tstdapis\tsyscalls2.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tsyscalls2.htm
testexecute \tstdapis\tsyssim.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tsyssim.htm
testexecute \tstdapis\tsysunistd.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tsysunistd.htm
testexecute \tstdapis\twchar.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_twchar.htm
testexecute \tstdapis\twcharapi.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_twcharapi.htm
testexecute \tstdapis\twctype.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_twctype.htm
testexecute \tstdapis\twideapis.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_twideapis.htm
ConfTimeZone.exe 1
testexecute \tstdapis\ttime_blr.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_testtime_blr.htm
testexecute \tstdapis\tshm.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tshm.htm
testexecute \tstdapis\tstring.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tstring.htm
ConfTimeZone.exe 2
LogFileReader.exe c:\logs\TestFramework\STDLIBS\Stdlibs_Preconfig.txt	e:\BCTest\results\Symbian_testtime_blr.htm



testexecute \tstdapis\tdl.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_dl.htm


testexecute \tstdapis\tdouble_blr.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tdouble_blr.htm
testexecute \tstdapis\tdouble_pow.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tdouble_pow.htm
testexecute \tstdapis\tdouble_misc.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tdouble_misc.htm
testexecute \tstdapis\tldouble_blr.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tldouble_blr.htm
testexecute \tstdapis\tldouble_pow.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tldouble_pow.htm
testexecute \tstdapis\tldouble_misc.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tldouble_misc.htm
testexecute \tstdapis\tfloat_blr.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_tfloat_blr.htm


testexecute \tstdapis\tcondbroadcast.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tcondbroadcast.htm
testexecute \tstdapis\tconddestroy.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tconddestroy.htm
testexecute \tstdapis\tcondinit.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tcondinit.htm
testexecute \tstdapis\tcondsignal.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tcondsignal.htm
testexecute \tstdapis\tcondwait.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tcondwait.htm
testexecute \tstdapis\tmutex.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tmutex.htm
testexecute \tstdapis\tpthread.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tpthread.htm
testexecute \tstdapis\tpthreadonce.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tpthreadonce.htm
testexecute \tstdapis\tsemdestroy.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tsemdestroy.htm
testexecute \tstdapis\tsemgetvalue.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tsemgetvalue.htm
testexecute \tstdapis\tseminit.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tseminit.htm
testexecute \tstdapis\tsemopen.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tsemopen.htm
testexecute \tstdapis\tsempost.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tsempost.htm
testexecute \tstdapis\tsemtimedwait.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tsemtimedwait.htm
testexecute \tstdapis\tsemtrywait.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tsemtrywait.htm
testexecute \tstdapis\tsemwait.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\OsSrv_Stdlibs_pthread_tsemwait.htm
