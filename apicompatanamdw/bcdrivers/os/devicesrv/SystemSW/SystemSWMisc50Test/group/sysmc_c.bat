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
  

copy C:\TestFramework\TestFramework_systemswmisc50.ini C:\TestFramework\TestFramework.ini
md e:\bctest\
md e:\bctest\results

ATSINTERFACE.EXE -testmodule SystemSWMisc50Test

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\SystemSoftware_misc50.txt