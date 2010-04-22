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
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tcomport.htm
testexecute \tstdapis\tctype.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tctype.htm
testexecute \tstdapis\tdb_blr.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tdb_blr.htm
testexecute \tstdapis\tftw.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tftw.htm
testexecute \tstdapis\tglob_test.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tglob_test.htm
testexecute \tstdapis\tlibcwchar.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tlibcwchar.htm
testexecute \tstdapis\tlink.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tlink.htm
testexecute \tstdapis\tloc_blr.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tloc_blr.htm
testexecute \tstdapis\tmkfifo.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tmkfifo.htm
testexecute \tstdapis\tmmap.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tmmap.htm
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tprogname.htm
testexecute \tstdapis\tregex.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tregex.htm
testexecute \tstdapis\tselect.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tselect.htm
testexecute \tstdapis\tsemaphore.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tsemaphore.htm
testexecute \tstdapis\tshm.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tshm.htm
testexecute \tstdapis\tstdio_auto.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tstdio_auto.htm
testexecute \tstdapis\tstdio_fileop.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tstdio_fileop.htm
testexecute \tstdapis\tstring.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tstring.htm
testexecute \tstdapis\tsyscalls.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tsyscalls.htm
testexecute \tstdapis\tsyscalls1.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tsyscalls1.htm
testexecute \tstdapis\tsyscalls2.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tsyscalls2.htm
testexecute \tstdapis\tsyssim.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tsyssim.htm
testexecute \tstdapis\tsysunistd.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tsysunistd.htm
testexecute \tstdapis\twchar.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_twchar.htm
testexecute \tstdapis\twcharapi.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_twcharapi.htm
testexecute \tstdapis\twctype.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_twctype.htm
testexecute \tstdapis\twideapis.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_twideapis.htm
testexecute \tstdapis\ttime_blr.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_testtime_blr.htm
