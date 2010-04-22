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


#include "tsemopen.h"
#include <unistd.h> 
#include <errno.h>
#include <stdio.h>
#include <e32std.h>
#include <stdlib.h>
#include <string.h>


CTestSemopen::~CTestSemopen() 
	{ 
	}  

CTestSemopen::CTestSemopen(const TDesC& aStepName)
	{
	// MANDATORY Call to base class method to set up the human readable name for logging.
	SetTestStepName(aStepName);		
	}

TVerdict CTestSemopen::doTestStepPreambleL()
	{
	__UHEAP_MARK;	
	SetTestStepResult(EPass);
	return TestStepResult();
	}

TVerdict CTestSemopen::doTestStepPostambleL()
	{
	__UHEAP_MARKEND;	
	return TestStepResult();
	}


TVerdict CTestSemopen::doTestStepL()
	{
	int err;

   	if(TestStepName() == KTestSem321)
   		{
   	   	INFO_PRINTF1(_L("TestSem321():"));
   	   	err = TestSem321();
   	   	SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   	}
   	      	   	   	   	
	return TestStepResult(); 

	}
 
	
