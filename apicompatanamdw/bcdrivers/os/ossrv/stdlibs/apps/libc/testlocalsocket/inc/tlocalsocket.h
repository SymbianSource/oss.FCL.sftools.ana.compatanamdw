/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:
*
*/



#ifndef __TESTLOCALSOCKET_H__
#define __TESTLOCALSOCKET_H__

#include <test/TestExecuteStepBase.h>

// INCLUDE FILES
#include <unistd.h> 
#include <errno.h>
#include <stdio.h>
#include <e32std.h>
#include <stdlib.h>
#include <string.h>

#include <e32svr.h>
#include <e32def.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <e32std.h>
#include <sys/unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include <net/if.h>
#include <sys/sockio.h>


_LIT(KTestBind, "TestBind");
_LIT(KTestLseek, "TestLseek");
_LIT(KTestFstat, "TestFstat");
_LIT(KTestThreadSocketRead, "TestThreadSocketRead");
_LIT(KTestThreadSocketWrite, "TestThreadSocketWrite");
_LIT(KTestMultProc, "TestMultProc");
_LIT(KTestMultThread, "TestMultThread");
_LIT(KTestListen, "TestListen");
_LIT(KTestSetGetSockOpt, "TestSetGetSockOpt");
_LIT(KTestSetSockOptNegative1, "TestSetSockOptNegative1");
_LIT(KTestSetSockOptNegative2, "TestSetSockOptNegative2");
_LIT(KTestSetSockOptNegative3, "TestSetSockOptNegative3");
_LIT(KTestSetSockOptNegative4, "TestSetSockOptNegative4");
_LIT(KTestGetSockOptNegative1, "TestGetSockOptNegative1");
_LIT(KTestGetSockOptNegative2, "TestGetSockOptNegative2");
_LIT(KTestGetSockOptNegative3, "TestGetSockOptNegative3");
_LIT(KTestGetSockOptNegative4, "TestGetSockOptNegative4");
_LIT(KTestLocalSockIoctl, "TestLocalSockIoctl");
_LIT(KTestLocalSockFcntl, "TestLocalSockFcntl");
_LIT(KTestLocalSockSelect, "TestLocalSockSelect");

class CTestLocalSocket : public CTestStep
	{
public:
	~CTestLocalSocket(); 
	CTestLocalSocket(const TDesC& aStepName);
	TVerdict doTestStepL();
	TVerdict doTestStepPreambleL();
	TVerdict doTestStepPostambleL();
private:
	void GetParameters(char aParamets[10][256]);
	TInt TestBind();
	TInt TestLseek();
	TInt TestFstat();
	TInt TestThreadSocketRead();
	TInt TestThreadSocketWrite();
	TInt TestMultProc();
	TInt TestMultThread();
	TInt TestListen();
	TInt TestSetGetSockOpt();
	TInt TestSetSockOptNegative1();
	TInt TestSetSockOptNegative2();
	TInt TestSetSockOptNegative3();
	TInt TestSetSockOptNegative4();
	TInt TestGetSockOptNegative1();
	TInt TestGetSockOptNegative2();
	TInt TestGetSockOptNegative3();
	TInt TestGetSockOptNegative4();
	TInt TestLocalSockIoctl();
	TInt TestLocalSockFcntl();
	TInt TestLocalSockSelect();
	};
#endif 
