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



#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <stdio.h>
#include <glib.h>
#include <string.h>

#ifdef SYMBIAN
#include "mrt2_glib2_test.h"
#endif /*SYMBIAN*/

int main (int argc, char *argv[])
{
	GCompletion *cmp;
	GList *items;
	gchar *prefix;

	#ifdef SYMBIAN
	g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
	#endif 

	cmp = g_completion_new (NULL);

	items = NULL;
	items = g_list_append (items, "Abcdef");
	items = g_list_append (items, "AbcDEF");
	items = g_list_append (items, "bc");
	items = g_list_append (items, "bd");
			
	g_completion_add_items (cmp, items);
	
	g_completion_set_compare(cmp,strncasecmp);
	
	items = g_completion_complete (cmp, "aB", &prefix);
	g_assert (!strcmp ("aBc", prefix));
	g_free (prefix);
		
	g_completion_remove_items(cmp,items);
	
	items = g_completion_complete (cmp, "aB", &prefix);
	g_assert(items == NULL);
	
	items = g_completion_complete (cmp, "b", &prefix);
	g_assert(!strcmp("b",prefix));
	g_free(prefix);
	
	g_completion_clear_items(cmp);
	
	items = g_completion_complete (cmp, "b", &prefix);
	g_assert(items == NULL);
	
	#if SYMBIAN
  	testResultXml("completion_test");
  	#endif /* EMULATOR */	

	return 0;
}
