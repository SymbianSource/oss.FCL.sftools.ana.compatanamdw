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

testexecute \tstdapis\tcondbroadcast.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tcondbroadcast.htm

testexecute \tstdapis\tconddestroy.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tconddestroy.htm

testexecute \tstdapis\tcondinit.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tcondinit.htm

testexecute \tstdapis\tcondsignal.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tcondsignal.htm

testexecute \tstdapis\tcondwait.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tcondwait.htm

testexecute \tstdapis\tmutex.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tmutex.htm

testexecute \tstdapis\tpthread.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tpthread.htm

testexecute \tstdapis\tpthreadonce.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tpthreadonce.htm

testexecute \tstdapis\tsemdestroy.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tsemdestroy.htm

testexecute \tstdapis\tsemgetvalue.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tsemgetvalue.htm

testexecute \tstdapis\tseminit.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tseminit.htm

testexecute \tstdapis\tsemopen.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tsemopen.htm

testexecute \tstdapis\tsempost.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tsempost.htm

testexecute \tstdapis\tsemtimedwait.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tsemtimedwait.htm

testexecute \tstdapis\tsemtrywait.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tsemtrywait.htm

testexecute \tstdapis\tsemwait.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_pthread_tsemwait.htm