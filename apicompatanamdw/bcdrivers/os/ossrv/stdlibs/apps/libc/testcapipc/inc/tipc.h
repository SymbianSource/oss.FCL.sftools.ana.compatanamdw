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
*  Name        : tipc.h
*  Part of     : testipc
*
*  Description : ?Description
*  Version:   0.5
*
  
*/

#ifndef __TESTipc_H__
#define __TESTipc_H__

#include <test/TestExecuteStepBase.h>
#include <sys/ipc.h> 
#include <errno.h>

#include <e32std.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

#include <pthread.h>
#include <semaphore.h>

#include <stdarg.h>



// MACROS
//#define ?macro ?macro_def
#define BUF_SIZE 100

// CONSTANTS
//const ?type ?constant_var = ?constant;
const TInt bufSize = 200;


//utility functions
void MakeSpace(char *);



//literals for file operations
_LIT(Kftoksys, "ftoksys");
_LIT(Kftokprivate, "ftokprivate");

class CTestipc : public CTestStep
	{
public:
	~CTestipc(); 
	CTestipc(const TDesC& aStepName);
	TVerdict doTestStepL();
	TVerdict doTestStepPreambleL();
	TVerdict doTestStepPostambleL();
private:
	
	
	
	//Captests for file operations
	TInt ftoksys();
    TInt ftokprivate();

	
	
	};
#endif 

