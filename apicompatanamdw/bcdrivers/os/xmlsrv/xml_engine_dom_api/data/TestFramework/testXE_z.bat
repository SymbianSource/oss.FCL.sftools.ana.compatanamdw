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

copy z:\TestFramework\TestFramework_xmleng.ini C:\TestFramework\TestFramework.ini
md e:\BCTest
md e:\BCTest\results

ATSINTERFACE.EXE -testmodule testscripter -config c:\testframework\DomBinCont.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\XmlSrv_XMLEngDOM_BinCont.txt

ATSINTERFACE.EXE -testmodule testscripter -config c:\testframework\DomFileCont.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\XmlSrv_XMLEngDOM_FileCont.txt

ATSINTERFACE.EXE -testmodule testscripter -config c:\testframework\DomChunkCont.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\XmlSrv_XMLEngDOM_ChunkCont.txt

ATSINTERFACE.EXE -testmodule testscripter -config c:\testframework\DomNotWF.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\XmlSrv_XMLEngDOM_NotWF.txt

ATSINTERFACE.EXE -testmodule testscripter -config c:\testframework\DomChunkparser.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\XmlSrv_XMLEngDOM_DomChunkparser.txt

ATSINTERFACE.EXE -testmodule testscripter -config c:\testframework\DomElem.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\XmlSrv_XMLEngDOM_DomElem.txt

ATSINTERFACE.EXE -testmodule testscripter -config c:\testframework\DomEncoding.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\XmlSrv_XMLEngDOM_DomEncoding.txt

ATSINTERFACE.EXE -testmodule testscripter -config c:\testframework\DomModif.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\XmlSrv_XMLEngDOM_DomModif.txt

ATSINTERFACE.EXE -testmodule testscripter -config c:\testframework\DomWF.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\XmlSrv_XMLEngDOM_WF.txt

ATSINTERFACE.EXE -testmodule testscripter -config c:\testframework\DomXmlId.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\XmlSrv_XMLEngDOM_DomXmlId.txt

ATSINTERFACE.EXE -testmodule testscripter -config c:\testframework\DomNodeFilter.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\XmlSrv_XMLEngDOM_DomNodeFilter.txt

ATSInterface.exe -testmodule testScripter -config c:\testframework\DomXPath.cfg

copy c:\Logs\TestFramework\TestReport.txt e:\BCTest\results\XmlSrv_XMLEngDOM_DomXPath.txt