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


#include "tseminit.h"
#include <unistd.h> 
#include <errno.h>
#include <stdio.h>
#include <e32std.h>
#include <stdlib.h>
#include <string.h>


CTestSeminit::~CTestSeminit() 
	{ 
	}  

CTestSeminit::CTestSeminit(const TDesC& aStepName)
	{
	// MANDATORY Call to base class method to set up the human readable name for logging.
	SetTestStepName(aStepName);		
	}

TVerdict CTestSeminit::doTestStepPreambleL()
	{
	__UHEAP_MARK;	
	SetTestStepResult(EPass);
	return TestStepResult();
	}



TVerdict CTestSeminit::doTestStepPostambleL()
	{
	__UHEAP_MARKEND;	
	return TestStepResult();
	}


TVerdict CTestSeminit::doTestStepL()
	{
	int err;

   	if(TestStepName() == KTestSem273)
   		{
   	   	INFO_PRINTF1(_L("TestSem273():"));
   	   	err = TestSem273();
   	   	SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   	}
	else if(TestStepName() == KTestSem274)
   		{
   	   	INFO_PRINTF1(_L("TestSem274():"));
   	   	err = TestSem274();
   	   	SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   	}
	else if(TestStepName() == KTestSem689)
   		{
   	   	INFO_PRINTF1(_L("TestSem689():"));
   	   	err = TestSem689();
   	   	SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   	}
   	else if(TestStepName() == KTestSem690)
   		{
   	   	INFO_PRINTF1(_L("TestSem690():"));
   	   	err = TestSem690();
   	   	SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   	}
	else if(TestStepName() == KTestSem691)
   		{
   	   	INFO_PRINTF1(_L("TestSem691():"));
   	   	err = TestSem691();
   	   	SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   	}
	else if(TestStepName() == KTestSem692)
   		{
   	   	INFO_PRINTF1(_L("TestSem692():"));
   	   	err = TestSem692();
   	   	SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   	}
	else if(TestStepName() == KTestSem693)
   		{
   	   	INFO_PRINTF1(_L("TestSem693():"));
   	   	err = TestSem693();
   	   	SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   	}
	else if(TestStepName() == KTestSem694)
   		{
   	   	INFO_PRINTF1(_L("TestSem694():"));
   	   	err = TestSem694();
   	   	SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   	}
	else if(TestStepName() == KTestSem695)
   		{
   	   	INFO_PRINTF1(_L("TestSem695():"));
   	   	err = TestSem695();
   	   	SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   	}
	else if(TestStepName() == KTestSem696)
   		{
   	   	INFO_PRINTF1(_L("TestSem696():"));
   	   	err = TestSem696();
   	   	SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   	}
   	   	
	return TestStepResult(); 

	}
 
	
