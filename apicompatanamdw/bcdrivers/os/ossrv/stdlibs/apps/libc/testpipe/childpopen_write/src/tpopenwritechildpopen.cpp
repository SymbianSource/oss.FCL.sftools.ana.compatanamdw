/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include <unistd.h>
#include <TestExecuteStepBase.h>
#include <TestExecuteServerBase.h>

TInt PopenChildL()
	{
	//Parent Process should give this one!!
	char* str= "Child successfull\n";
	printf("%s", str);	
	fflush(stdout);
	sleep(5);
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
