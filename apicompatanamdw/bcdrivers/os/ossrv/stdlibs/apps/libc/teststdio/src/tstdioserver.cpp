/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
*  Name        : tstdioserver.cpp
*  Part of     : teststdio
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
#include "tstdioserver.h"
#include "tstdio.h"


_LIT(KServerName, "tstdio");

CStdioTestServer* CStdioTestServer::NewL()
	{
	CStdioTestServer *server = new(ELeave) CStdioTestServer();
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
	CStdioTestServer* server = NULL;
	// Create the CTestServer derived server
	TRAPD(err, server = CStdioTestServer::NewL());
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
TInt main()
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

CTestStep* CStdioTestServer::CreateTestStep(const TDesC& aStepName)
	{
	CTestStep* testStep = NULL;

	// This server creates just one step but create as many as you want
	// They are created "just in time" when the worker thread is created
	// install steps
	if(aStepName == Kremove1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kremove2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Krename1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Ktempnam1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Ktempnam2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfclose1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfflush1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfopen1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfopen2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfopen3)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Ksetbuf1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Ksetbuf2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Ksetvbuf1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Ksetvbuf2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Ksetvbuf3)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kclearerr1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfeof1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kferror1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfread1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfread2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfread3)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfwrite1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfwrite2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfwrite3)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfgetpos1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfseek1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfseek2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfsetpos1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfsetpos2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kftell1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Krewind1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfgetc1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfgets1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfgets2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfgets3)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfputc1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfputc2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfputc3)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfputc4)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfputs1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfputs2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfputs3)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfputs4)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kgetc1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kputc1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kputc2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kputc3)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kputc4)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kungetc1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfileno1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfileno2)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kgetw1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kputw1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kgetdirentries1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kgetdirentries2)
		{
 		testStep = new CTestStdio(aStepName);
  		} 
	if(aStepName == Kfreopen1)
		{
		testStep = new CTestStdio(aStepName);
		}
	//----Defect 111519
	if(aStepName == Kbinaryopen)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kbinaryfopen)
		{
		testStep = new CTestStdio(aStepName);
		}
	//----
	if(aStepName == KprintfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest14L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest15L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest16L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest17L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest18L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest19L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest20L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest21L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest22L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest23L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest24L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest25L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest26L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KprintfTest27L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest14L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest15L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest16L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest17L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest18L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest19L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest20L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest21L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest22L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest23L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest24L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest25L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest26L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfprintfTest27L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest14L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest15L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest16L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest17L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest18L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest19L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest20L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest21L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest22L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest23L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest24L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest25L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest26L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest27L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest28L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTest29L)
		{
		testStep = new CTestStdio(aStepName);
		}		
	if(aStepName == KsprintfTestInfL)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsprintfTestNanL)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest14L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest15L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest16L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest17L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest18L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest19L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest20L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest21L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest22L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest23L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest24L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest25L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest26L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsnprintfTest27L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest14L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest15L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest16L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest17L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest18L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest19L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest20L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest21L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest22L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest23L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest24L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest25L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest26L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvprintfTest27L)
		{
		testStep = new CTestStdio(aStepName);
		}
	
	if(aStepName == Kfprintfbasic)
		{
		testStep = new CTestStdio(aStepName);
		}
	
	if(aStepName == KscanfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KscanfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KscanfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KscanfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KscanfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KscanfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KscanfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KscanfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KscanfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KscanfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KscanfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KscanfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KscanfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsscanfTest14L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfscanfTest14L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvscanfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsscanfTest14L)
		{
		testStep = new CTestStdio(aStepName);
		}
		testStep = new CTestStdio(aStepName);
	if(aStepName == KvfscanfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfscanfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfscanfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfscanfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfscanfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfscanfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfscanfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfscanfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfscanfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfscanfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfscanfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfscanfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfscanfTest14L)
		{
		testStep = new CTestStdio(aStepName);
		}
	
	if(aStepName == KvsprintfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest14L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest15L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest16L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest17L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest18L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest19L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest20L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest21L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest22L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest23L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest24L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest25L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest26L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsprintfTest27L)
		{
		testStep = new CTestStdio(aStepName);
		}
	
	if(aStepName == KvsnprintfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest14L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest15L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest16L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest17L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest18L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest19L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest20L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest21L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest22L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest23L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest24L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest25L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest26L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvsnprintfTest27L)
		{
		testStep = new CTestStdio(aStepName);
		}
	
	if(aStepName == KvfprintfTest1L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest2L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest3L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest4L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest5L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest6L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest7L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest8L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest9L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest10L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest11L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest12L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest13L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest14L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest15L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest16L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest17L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest18L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest19L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest20L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest21L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest22L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest23L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest24L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest25L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest26L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvfprintfTest27L)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfseek_multithreaded)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kprintf_multithreaded)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kfreopen_multithreaded)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kputc_multithreaded)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KTestsprintf1)
		{
		testStep = new CTestStdio(aStepName);
		}
	//for DEF114259	
	if(aStepName == KInvalidDriveTests29)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KputcTest)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KclrerrTest)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KgetcTest)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfilenoTest)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KfeofTest)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KvasprintfTest1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KasprintfTest1)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KwopenTest)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == Kposix_spawnattr_destroyTest)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsetgroupsTest)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KgetpwentTest)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KbrkTest)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KsigactionTest)
		{
		testStep = new CTestStdio(aStepName);
		}
	if(aStepName == KwfreopenTest)
		{
		testStep = new CTestStdio(aStepName);
		}
	
	return testStep;
	}

