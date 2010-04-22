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

testexecute c:\sip\sipprofile\t_csipprofile.script 
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_csipprofile.htm

testexecute c:\sip\sipprofile\t_csipmanagedprofile.script 
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_csipmanagedprofile.htm

testexecute c:\sip\sipprofile\t_csipprofileregistry.script 
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_csipprofileregistry.htm

testexecute c:\sip\sipprofile\t_csipmanagedprofileregistry.script 
copy c:\Logs\Testexecute\TestResults.htm e:\BCTest\results\Symbian_SIP_csipmanagedprofileregistry.htm
