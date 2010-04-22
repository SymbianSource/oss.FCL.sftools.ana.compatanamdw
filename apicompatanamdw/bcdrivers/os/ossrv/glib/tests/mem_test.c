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
#include <stdlib.h>
#include <glib_global.h>

#ifdef SYMBIAN
#include "mrt2_glib2_test.h"
#endif /*SYMBIAN*/

void myLogHandler(const gchar* log_domain, GLogLevelFlags log_level,
					const gchar* message, gpointer user_data)
{
	FILE *fp;
	fp = fopen("c:\\meminfo.txt","a");
	
	if(fp)
	{
		fprintf(fp,message);
		fprintf(fp,"\n");
		fclose(fp);
	}
}

void g_mem_is_system_malloc_test()
{
	g_assert(g_mem_is_system_malloc());
}

void g_mem_chunk_reset_test()
{
	gchar *name = "chunk";
	GMemChunk *mem_chunk = g_mem_chunk_new(name,2,10,G_ALLOC_AND_FREE);
	guint16 *x = g_mem_chunk_alloc(mem_chunk);
	*x = 50;
	g_mem_chunk_reset(mem_chunk);
	*x = 10;
}

void g_mem_test()
{
	GMemVTable temp_glib_mem_vtable = {
		malloc,
		realloc,
		free,
		calloc,
		malloc,
		realloc,
	};
	
	gchar *name = "chunk";
	GMemChunk *mem_chunk;
	guint16 *x = NULL;
	
	FILE *fp;
	
	g_mem_set_vtable(&temp_glib_mem_vtable);
	mem_chunk = g_mem_chunk_new(name,2,10,G_ALLOC_AND_FREE);
	x = g_mem_chunk_alloc(mem_chunk);
	g_assert(x != NULL);
}

int
main (int argc, char *argv[])
{
	#ifdef SYMBIAN
	
	g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
	#endif /*SYMBIAN*/
	
	g_mem_is_system_malloc_test();
	g_mem_chunk_reset_test();
	g_mem_test();
	
	#ifdef SYMBIAN
  	testResultXml("mem_test");
  	#endif /* EMULATOR */
  
	return 0;
}
