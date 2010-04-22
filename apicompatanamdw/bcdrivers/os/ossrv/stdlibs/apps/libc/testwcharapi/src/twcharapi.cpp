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



// INCLUDE FILES

#include "twcharapi.h"

CTestWCharApi::~CTestWCharApi() 
	{ 
	}  

CTestWCharApi::CTestWCharApi(const TDesC& aStepName)
	{
	// MANDATORY Call to base class method to set up the human readable name for logging.
	SetTestStepName(aStepName);		
	}

TVerdict CTestWCharApi::doTestStepPreambleL()
	{
	__UHEAP_MARK;	
	SetTestStepResult(EPass);
	return TestStepResult();
	}



TVerdict CTestWCharApi::doTestStepPostambleL()
	{
	__UHEAP_MARKEND;	
	return TestStepResult();
	}

TVerdict CTestWCharApi::doTestStepL()
	{
		int err;

   		
		if(TestStepName() == Ktwasctime)
   			{
   	   		INFO_PRINTF1(_L("twasctime():"));
   	   		err = twasctime();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}
   	   	else
   	   		if(TestStepName() == Ktwctime)
   			{
   	   		INFO_PRINTF1(_L("twctime():"));
   	   		err = twctime();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}
   	   	else
   	   		if(TestStepName() == Ktwcslcat)
   			{
   	   		INFO_PRINTF1(_L("twcslcat():"));
   	   		err = twcslcat();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}
   	   	else
   	   		if(TestStepName() == Ktwcslcpy)
   			{
   	   		INFO_PRINTF1(_L("twcslcpy():"));
   	   		err = twcslcpy();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}
   	   	else
   	   		if(TestStepName() == Ktwsetlocale)
   			{
   	   		INFO_PRINTF1(_L("twsetlocale():"));
   	   		err = twsetlocale();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}
   	   	else
   	   		if(TestStepName() == Ktwperror)
   			{
   	   		INFO_PRINTF1(_L("twperror():"));
   	   		err = twperror();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}
   	   	else
   	   		if(TestStepName() == Ktwcserror)
   			{
   	   		INFO_PRINTF1(_L("twcserror():"));
   	   		err = twcserror();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}
   	   	else
   	   		if(TestStepName() == Ktwfindfirst)
   			{
   	   		INFO_PRINTF1(_L("twfindfirst():"));
   	   		err = twfindfirst();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}
   	   	else
   	   		if(TestStepName() == Ktwfindclose)
   			{
   	   		INFO_PRINTF1(_L("twfindclose():"));
   	   		err = twfindclose();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}
   	   	else
   	   		if(TestStepName() == Ktwtelldir)
   			{
   	   		INFO_PRINTF1(_L("twtelldir():"));
   	   		err = twtelldir();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}   	   		
   	   	else
   	   		if(TestStepName() == Ktwseekdir)
   			{
   	   		INFO_PRINTF1(_L("twseekdir():"));
   	   		err = twseekdir();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}   
   	   	else
   	   		if(TestStepName() == Ktwsetlocale1)
   			{
   	   		INFO_PRINTF1(_L("twsetlocale1():"));
   	   		err = twsetlocale1();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}   
   	   	else
   	   		if(TestStepName() == Ktwfindfirst1)
   			{
   	   		INFO_PRINTF1(_L("twfindfirst1():"));
   	   		err = twfindfirst1();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}   
   	   	else
   	   		if(TestStepName() == Ktwfindnext1)
   			{
   	   		INFO_PRINTF1(_L("twfindnext1():"));
   	   		err = twfindnext1();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}      	   	
   	   	else if(TestStepName() == Kwcreat2)
			{
			INFO_PRINTF1(_L("wcreat2():"));
			err = wcreat2();
			SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
			}	 
		else if(TestStepName() == Kwpopen3_1)
			{
			INFO_PRINTF1(_L("wpopen3_1():"));
			err = wpopen3_1();
			SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
			}  	   		   	   		   	   	
		return TestStepResult(); 

	}
 

	
