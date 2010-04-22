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

md e:\bctest

md e:\bctest\results

copy z:\testframework\testframework_dwmgr.ini c:\testframework\testframework.ini

copy c:\testframework\testframework_dwmgr.ini c:\testframework\testframework.ini


ATSINTERFACE.EXE -testmodule DownloadMgrBCTest

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\Web_DownloadMgrEngine.txt
