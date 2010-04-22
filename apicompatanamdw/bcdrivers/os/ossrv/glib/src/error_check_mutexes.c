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

#include <glib.h>
#include <stdio.h>

#ifdef SYMBIAN
#include <glib_global.h>
#include "mrt2_glib2_test.h"
#endif /*SYMBIAN*/



void test_error_check_mutexes()
{
  
  GThread *thread =NULL;
  GMutex* test_g_mutex_mutex = NULL;
  
  g_thread_init(NULL);	
  
  test_g_mutex_mutex = g_mutex_new ();

  g_assert (g_mutex_trylock (test_g_mutex_mutex));
  g_assert (g_mutex_trylock (test_g_mutex_mutex) == FALSE);
  g_mutex_unlock (test_g_mutex_mutex);
  g_mutex_free (test_g_mutex_mutex);
}





int main (int   argc,
      char *argv[])
{
	#ifdef SYMBIAN
	int handler = g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
	#endif /*SYMBIAN*/


	
	
	test_error_check_mutexes();
	
	#ifdef SYMBIAN
  	testResultXml("error_check_mutexes");
  	#endif /* EMULATOR */
	
	return 0;
}