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

testexecute \tstdapis\tdouble_blr.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tdouble_blr.htm

testexecute \tstdapis\tdouble_pow.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tdouble_pow.htm

testexecute \tstdapis\tdouble_misc.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tdouble_misc.htm

testexecute \tstdapis\tldouble_blr.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tldouble_blr.htm

testexecute \tstdapis\tldouble_pow.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tldouble_pow.htm

testexecute \tstdapis\tldouble_misc.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tldouble_misc.htm

testexecute \tstdapis\tfloat_blr.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_tfloat_blr.htm

