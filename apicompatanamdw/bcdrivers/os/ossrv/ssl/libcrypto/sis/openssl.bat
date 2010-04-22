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


md e:\bctest
md e:\bctest\results
md e:\bctest\results\ssl

openssl.exe c:\tpkcs7d.txt
openssl.exe c:\treq2.txt
openssl.exe c:\treq.txt
openssl.exe c:\trsa.txt
openssl.exe c:\tsid.txt
openssl.exe c:\tx5091.txt
openssl.exe c:\tx5092.txt
openssl.exe c:\tx509.txt
openssl.exe c:\tcrl.txt
openssl.exe c:\testenc.txt
openssl.exe c:\testgen.txt
openssl.exe c:\testss.txt
openssl.exe c:\test_verify.txt
openssl.exe c:\tpkcs7.txt

copy c:\spd_logs\xml\*.xml e:\bctest\results\ssl\

