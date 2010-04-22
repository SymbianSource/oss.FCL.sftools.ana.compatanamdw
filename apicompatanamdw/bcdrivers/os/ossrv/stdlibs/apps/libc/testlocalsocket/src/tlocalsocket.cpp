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


#include "tlocalsocket.h"

CTestLocalSocket::~CTestLocalSocket() 
	{ 
	}  

CTestLocalSocket::CTestLocalSocket(const TDesC& aStepName)
	{
	// MANDATORY Call to base class method to set up the human readable name for logging.
	SetTestStepName(aStepName);		
	}

TVerdict CTestLocalSocket::doTestStepPreambleL()
	{
	__UHEAP_MARK;	
	SetTestStepResult(EPass);
	return TestStepResult();
	}

TVerdict CTestLocalSocket::doTestStepPostambleL()
	{
	__UHEAP_MARKEND;
	return TestStepResult();
	}


TVerdict CTestLocalSocket::doTestStepL()
	{
	int err;

   	if(TestStepName() == KTestBind)
   		{
		INFO_PRINTF1(_L("TestBind():"));
		err = TestBind();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestLseek)
   		{
		INFO_PRINTF1(_L("TestLseek():"));
		err = TestLseek();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestFstat)
   		{
		INFO_PRINTF1(_L("TestFstat():"));
		err = TestFstat();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestThreadSocketRead)
   		{
		INFO_PRINTF1(_L("TestThreadSocketRead():"));
		err = TestThreadSocketRead();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestThreadSocketWrite)
   		{
		INFO_PRINTF1(_L("TestThreadSocketWrite():"));
		err = TestThreadSocketWrite();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestMultProc)
   		{
		INFO_PRINTF1(_L("TestMultProc():"));
		err = TestMultProc();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestMultThread)
   		{
		INFO_PRINTF1(_L("TestMultThread():"));
		err = TestMultThread();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestListen)
   		{
		INFO_PRINTF1(_L("TestListen():"));
		err = TestListen();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestSetGetSockOpt)
   		{
		INFO_PRINTF1(_L("TestSetGetSockOpt():"));
		err = TestSetGetSockOpt();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestSetSockOptNegative1)
   		{
		INFO_PRINTF1(_L("TestSetSockOptNegative1():"));
		err = TestSetSockOptNegative1();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestSetSockOptNegative2)
   		{
		INFO_PRINTF1(_L("TestSetSockOptNegative2():"));
		err = TestSetSockOptNegative2();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestSetSockOptNegative3)
   		{
		INFO_PRINTF1(_L("TestSetSockOptNegative3():"));
		err = TestSetSockOptNegative3();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestSetSockOptNegative4)
   		{
		INFO_PRINTF1(_L("TestSetSockOptNegative4():"));
		err = TestSetSockOptNegative4();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestGetSockOptNegative1)
   		{
		INFO_PRINTF1(_L("TestGetSockOptNegative1():"));
		err = TestGetSockOptNegative1();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestGetSockOptNegative2)
   		{
		INFO_PRINTF1(_L("TestGetSockOptNegative2():"));
		err = TestGetSockOptNegative2();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestGetSockOptNegative3)
   		{
		INFO_PRINTF1(_L("TestGetSockOptNegative3():"));
		err = TestGetSockOptNegative3();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestGetSockOptNegative4)
   		{
		INFO_PRINTF1(_L("TestGetSockOptNegative4():"));
		err = TestGetSockOptNegative4();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestLocalSockIoctl)
   		{
		INFO_PRINTF1(_L("TestLocalSockIoctl():"));
		err = TestLocalSockIoctl();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestLocalSockFcntl)
   		{
		INFO_PRINTF1(_L("TestLocalSockFcntl():"));
		err = TestLocalSockFcntl();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	if(TestStepName() == KTestLocalSockSelect)
   		{
		INFO_PRINTF1(_L("TestLocalSockSelect():"));
		err = TestLocalSockSelect();
		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
		}
	return TestStepResult(); 

	}
 

