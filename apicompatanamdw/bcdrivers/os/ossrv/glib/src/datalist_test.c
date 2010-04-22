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

#ifdef SYMBIAN
#include "mrt2_glib2_test.h"
#endif /*SYMBIAN*/

void func(GQuark key_id,gpointer data,gpointer user_data)
{
	gint *udata = (int *)user_data;
	(*udata)++;
}

void datalist_test()
{
	GData *datalist;
	GQuark q1,q2;
	gchar *str1 = "test1",*str2 = "test2",*str3,*str4;
	int user_data = 0;
	int flags;
	
	g_datalist_init(&datalist);
	
	//check for g_datalist_init.
	g_assert(datalist == NULL);
	
	q1 = g_quark_from_string(str1);
	q2 = g_quark_from_string(str2);
	
	g_datalist_id_set_data_full(&datalist,q1,str1,NULL);
	g_datalist_id_set_data_full(&datalist,q2,str2,NULL);
	
	str3 = g_datalist_id_get_data(&datalist,q1);
	str4 = g_datalist_id_get_data(&datalist,q2);
	
	//checks g_datalist_id_set_data_full and g_datalist_id_get_data
	g_assert(!strcmp(str1,str3) && !strcmp(str2,str4));
	
	str3 = g_datalist_id_get_data(&datalist,5);
	
	g_assert(str3 == NULL);
	
	g_datalist_foreach(&datalist,func,&user_data);
	
	// checks g_datalist_foreach. user_data should become 2 as the function will be called twice for
	// 2 data elements
	g_assert(user_data == 2);
	
	g_datalist_set_flags(&datalist,0x0);
	
	flags = g_datalist_get_flags(&datalist);
	
	//checks g_datalist_set_flags and g_datalist_set_flags
	g_assert(flags == 0);
	
}

int
main (int   argc,
      char *argv[])
{
  
	#ifdef SYMBIAN
	g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
	g_set_print_handler(mrtPrintHandler);
	#endif /*SYMBIAN*/
	
	datalist_test();
	
	#if SYMBIAN
	testResultXml("datalist_test");
  	#endif /* EMULATOR */
  
	return 0;
}