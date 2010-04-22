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

copy C:\TestFramework\TestFramework_lmsearch.ini C:\TestFramework\TestFramework.ini

md c:\Documents
md c:\Logs
md c:\Logs\TestFramework
md c:\Logs\TestFramework\testlmksearchapi
md e:\bctest
md e:\bctest\results

ATSINTERFACE.EXE -testmodule testscripter -config c:\testframework\testlmksearchapi.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\bctest\results\LocationSrv_LandmarksSearch.txt

