/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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


 /*
* ==============================================================================
*  Name        : tmutexserver.cpp
*  Part of     : testmutex
*
*  Description : ?Description
*  Version:   0.5
*
  
*/

#include <c32comm.h>

#if defined (__WINS__)
#define PDD_NAME		_L("ECDRV")
#else
#define PDD_NAME		_L("EUART1")
#define PDD2_NAME		_L("EUART2")
#define PDD3_NAME		_L("EUART3")
#define PDD4_NAME		_L("EUART4")
#endif

#define LDD_NAME		_L("ECOMM")

/**
 * @file
 *
 * Pipe test server implementation
 */
#include "tmutexserver.h"
#include "tmutex.h"


_LIT(KServerName, "tmutex");

CMutexTestServer* CMutexTestServer::NewL()
	{
	CMutexTestServer *server = new(ELeave) CMutexTestServer();
	CleanupStack::PushL(server);
	server->ConstructL(KServerName);
	CleanupStack::Pop(server);
	return server;
	}

static void InitCommsL()
    {
    TInt ret = User::LoadPhysicalDevice(PDD_NAME);
    User::LeaveIfError(ret == KErrAlreadyExists?KErrNone:ret);

#ifndef __WINS__
    ret = User::LoadPhysicalDevice(PDD2_NAME);
    ret = User::LoadPhysicalDevice(PDD3_NAME);
    ret = User::LoadPhysicalDevice(PDD4_NAME);
#endif

    ret = User::LoadLogicalDevice(LDD_NAME);
    User::LeaveIfError(ret == KErrAlreadyExists?KErrNone:ret);
    ret = StartC32();
    User::LeaveIfError(ret == KErrAlreadyExists?KErrNone:ret);
    }

LOCAL_C void MainL()
	{
	// Leave the hooks in for platform security
#if (defined __DATA_CAGING__)
	RProcess().DataCaging(RProcess::EDataCagingOn);
	RProcess().SecureApi(RProcess::ESecureApiOn);
#endif
	//InitCommsL();
	
	CActiveScheduler* sched=NULL;
	sched=new(ELeave) CActiveScheduler;
	CActiveScheduler::Install(sched);
	CMutexTestServer* server = NULL;
	// Create the CTestServer derived server
	TRAPD(err, server = CMutexTestServer::NewL());
	if(!err)
		{
		// Sync with the client and enter the active scheduler
		RProcess::Rendezvous(KErrNone);
		sched->Start();
		}
	delete server;
	delete sched;
	}

/**
 * Server entry point
 * @return Standard Epoc error code on exit
 */
TInt E32Main()
	{
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	if(cleanup == NULL) 
		{
		return KErrNoMemory;  
		}
	TRAP_IGNORE(MainL());
	delete cleanup;
	__UHEAP_MARKEND;
	
	return KErrNone;
	}

CTestStep* CMutexTestServer::CreateTestStep(const TDesC& aStepName)
	{
	CTestStep* testStep = NULL;

	// This server creates just one step but create as many as you want
	// They are created "just in time" when the worker thread is created
	// install steps
	if(aStepName == KPThreadMutexLock)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadMutexLockRecursive)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadMutexLockErrorCheck)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadMutexTimedlock)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadMutexTrylock)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadMutexUnlock)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadOnce)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadMutexattrSettype)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KSemInit)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KSemDestroy)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KSemTryWait)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KSemWait)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KSemTimedWait)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KSemPost)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KSemClose)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KSemUnlink)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KSemGetValue)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KSemMicroSleepwaitNP)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KSemPostMultiple)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadCondAttrInit)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadCondAttrDestroy)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadCondInit)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadCondDestroy)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadCondTimedwait)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadCondWait)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadCondSignal)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadCondBroadcast)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KDelay)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadAttrStaticInitL)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadAttrStaticInitTimedLockL)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadAttrStaticInitTryLockL)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KPThreadAttrStaticInitUnlockL)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest1)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest2)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest3)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest4)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest5)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest6)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest7)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest8)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest9)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest10)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest11)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest12)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest13)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest14)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest15)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest16)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest17)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest18)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest19)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest20)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest21)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest22)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest23)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest24)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest25)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest26)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest27)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest28)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest29)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest30)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest31)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest32)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest33)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest34)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest35)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest36)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest37)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest38)
		{
		testStep = new CTestMutex(aStepName);
		}
	if(aStepName == KIntgTest39)
		{
		testStep = new CTestMutex(aStepName);
		}

	return testStep;
	}

