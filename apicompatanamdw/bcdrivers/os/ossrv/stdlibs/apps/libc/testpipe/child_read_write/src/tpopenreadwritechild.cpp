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


// INCLUDE FILES
#include <e32def.h>
#include <e32std.h>
#include <e32svr.h>
#include <stdio.h>
#include <TestExecuteStepBase.h>
#include <TestExecuteServerBase.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

TInt PopenChildL()
	{		
	char buf[25];	
	char error[50];
	strcpy(error,"throwing error for a check\n");
	
	scanf("%s", buf);	/*read from the parent*/
	printf("%s", buf);  /*write data to the parent*/
	fflush(stdout);
	perror(error); /*write error to the parent*/
	
	sleep(2);
	return KErrNone;	
	}

TInt main()
	{
	//__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TRAPD(error, PopenChildL());
	__ASSERT_ALWAYS(!error, User::Panic(_L("PopenWriteChild PANIC"), error));
	//Destroy cleanup stack
	delete cleanup;
	//__UHEAP_MARKEND;
	return 0;
	}


//  End of File
