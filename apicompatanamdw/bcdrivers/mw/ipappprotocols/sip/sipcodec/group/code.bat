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

testexecute c:\sip\sipcodec\t_sipstrings.script 
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_sipstrings.htm

testexecute c:\sip\sipcodec\t_csipcallidheader.script 
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_sipcallidheader.htm

testexecute c:\sip\sipcodec\t_csipaddress.script 
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_csipaddress.htm

testexecute c:\sip\sipcodec\t_csipcseqheader.script 
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_csipcseqheader.htm

testexecute c:\sip\sipcodec\t_csipextensionheader.script
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_csipextensionheader.htm

testexecute c:\sip\sipcodec\t_csiprackheader.script 
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_csiprackheader.htm

testexecute c:\sip\sipcodec\t_csipalloweventsheader.script 
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_csipalloweventsheader.htm

testexecute c:\sip\sipcodec\t_csiprefertoheader.script 
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_csiprefertoheader.htm

testexecute c:\sip\sipcodec\t_csipreplytoheader.script 
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_csipreplytoheader.htm
