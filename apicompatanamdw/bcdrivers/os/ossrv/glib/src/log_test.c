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



// This test case is part automated and part manual. On running the test case 
// an output is expected on the screen. All the other APIs which are tested, 
// if they fail will write in the log file.

#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <stdio.h>
#include <string.h>
#include "glib.h"

#ifdef SYMBIAN
#include "mrt2_glib2_test.h"
#endif /*SYMBIAN*/

void myLogHandler(const gchar *log_domain,GLogLevelFlags log_level,const gchar *message,gpointer user_data)
{
	char *data = (char *)user_data;
	sprintf(data,"%s",message);
}

int main (int argc,char *argv[])
{
	gchar message[100],message1[100];
	int id = -1;
	GLogFunc log_func;
	
	#ifdef SYMBIAN

	#endif /*SYMBIAN*/
	
	log_func = g_log_set_default_handler(myLogHandler,message);
	g_log(NULL,G_LOG_LEVEL_MESSAGE,"test message");
	
	// checks g_log_set_default_handler. The new handler
	// will put the message in the message array and the 
	// same is tested using the assert below.
	g_assert(!strcmp(message,"test message"));
	
	log_func = g_log_set_default_handler(log_func,message);
	
	g_assert(log_func == myLogHandler);
	
	id = g_log_set_handler ("test domain",G_LOG_LEVEL_MESSAGE, &myLogHandler, message1);
	
	g_log("test domain",G_LOG_LEVEL_MESSAGE,"test message2");
	
	// checks g_log_set_handler. The new handler
	// will put the message in the message1 array and the 
	// same is tested using the assert below.
	g_assert(id != -1 && !strcmp(message1,"test message2"));
	
	g_log_remove_handler("test domain",id);
	
	// This log message should print on stdout
	// as the handler is removed.
	g_log("test domain",G_LOG_LEVEL_MESSAGE,"test message printed \nsuccessfully\n");
	printf("Press any key to exit");
	
	getchar();
	
}