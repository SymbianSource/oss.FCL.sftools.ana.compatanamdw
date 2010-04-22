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
* Description:  ?Description
*
*/


#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN


#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <fcntl.h>
#include <goption.h>

#ifdef SYMBIAN
#include "mrt2_glib2_test.h"
#endif /*SYMBIAN*/

#define	C2P(c)		((gpointer) ((long) (c)))
#define GINT_TO_POINTER(i)	((gpointer)  (i))
#define GPOINTER_TO_INT(p)	((gint)   (p))
#define TESTPASS	1
#define TESTFAIL	0


void tg_trash_tests()
{
	GTrashStack* stk=NULL;
	gint ip1=5;
	gint ip2=6;
	gint ip3=7;
	gint g_trash_stack_peek_res;
	
	//All test done thro stack_height
	g_assert(g_trash_stack_height(&stk) == 0);
	//Push 2 elements
	g_trash_stack_push(&stk,&ip1);
	g_assert(g_trash_stack_height(&stk) == 1);
	g_trash_stack_push(&stk,&ip2);
	g_assert(g_trash_stack_height(&stk) == 2);
	//Pop one element
	g_trash_stack_pop(&stk);
	g_assert(g_trash_stack_height(&stk) == 1);
	//Push one more
	g_trash_stack_push(&stk,&ip3);
	g_assert(g_trash_stack_height(&stk) == 2);
	//Pop one more
	g_trash_stack_pop(&stk);
	//Check top of stack
	g_trash_stack_peek_res = *(gint*)g_trash_stack_peek(&stk);
	g_assert(g_trash_stack_peek_res == 0);
	
}

int main (int argc,char *argv[])
{

	#ifdef SYMBIAN
 
 	g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO |  G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
 	#endif /*SYMBIAN*/
 	
 	tg_trash_tests();
 #ifdef SYMBIAN
  testResultXml("ttrash");
#endif /* EMULATOR */
 	return 0;
}