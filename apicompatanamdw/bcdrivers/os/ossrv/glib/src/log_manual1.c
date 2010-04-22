/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies). 
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



// This is a manual test case. When the test case is executed, the getchar() atthe 
// end is not executed, because the fatal mask is set and g_log calls abort().

#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <stdio.h>
#include <string.h>
#include "glib.h"

#ifdef SYMBIAN
#include "mrt2_glib2_test.h"
#endif /*SYMBIAN*/


int main (int argc,char *argv[])
{
	#ifdef SYMBIAN

	g_set_print_handler(mrtPrintHandler);
	#endif /*SYMBIAN*/
	
	printf("The following test case will abort\n when u press the enter key\n");
	printf("If you see any other message after \nthis message, consider the test\ncase as failed\n");
	getchar();
	
	g_log_set_fatal_mask(NULL,G_LOG_LEVEL_MESSAGE);
	
	g_log(NULL,G_LOG_LEVEL_MESSAGE,"test message");
	
	g_print("log_manual1 failed");
	
	getchar();
}