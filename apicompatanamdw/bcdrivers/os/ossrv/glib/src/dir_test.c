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
#include <string.h>
#include <sys/stat.h>
#include "glib.h"

#ifdef SYMBIAN
#include "mrt2_glib2_test.h"
#endif /*SYMBIAN*/


int main (int   argc,char *argv[])
{
	GDir *dir;
	GError *error;	
		
	#ifdef SYMBIAN
	g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
	#endif /*SYMBIAN*/
	
	dir = g_dir_open("c:\\temp",0,&error);
	
	g_assert(dir != NULL);
	
	g_assert(!strcmp(g_dir_read_name(dir),"tmp"));
	
	g_dir_close(dir);
	
	#if SYMBIAN
  	testResultXml("dir_test");
  	#endif /* EMULATOR */
	
	return 0;
}