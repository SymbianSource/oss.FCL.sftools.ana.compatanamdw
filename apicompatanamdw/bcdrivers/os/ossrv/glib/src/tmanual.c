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

//Test for g_on_error_query
void tg_on_error_query()
{
	printf("\nThis is a test for g_on_error_query\nChoose the foll:\n");
	g_on_error_query(NULL);
}

//Test for g_printf
void tg_printf()
{
	printf("This is a test for g_printf\n");
 	g_printf("%d\n%s\t%f",9999999,"Abcd#%@",999.999999);
 	printf("\nCase passed!..Press any key");
 	getchar();
}

//Support for print handler tests
void print_func()
{
	return;
}
//Print handler tests
void tg_print_handler_test()
{
	g_print ("%s","\nThis is a test for setting print handler\nbefore setting");
	g_set_print_handler (&print_func);
	g_print ("%s","after setting:Test Failed!");
	getchar();
	g_set_printerr_handler (&print_func);
}

//Test for g_relation_print and g_tuples_index
void tg_relation_print()
{
	gint i;
	GRelation *relation;
	GTuples *tuples;
	gint data [4];
			
	relation = g_relation_new (2);

	g_relation_index (relation, 0, g_int_hash, g_int_equal);
	g_relation_index (relation, 1, g_int_hash, g_int_equal);

	for (i = 0; i < 4; i += 1)
		data[i] = i;

	for (i = 1; i < 3; i += 1)
	{
		g_relation_insert (relation, data + i, data + i + 1);
		g_relation_insert (relation, data + i, data + i - 1);
	}
	
	printf("This is a test case for g_relation_print.\nWhat you will see");
	printf(" is all the tuples in the relation and 2 sets of relations");
	printf("with index 0 and 1:\n");
	g_relation_print(relation);
	
	tuples = g_relation_select (relation, data + 2, 0);
	g_assert(*(gint*) g_tuples_index (tuples, 0, 0) == 2);
	
	g_tuples_destroy(tuples);
	g_relation_destroy(relation);
	
	printf("\nIn case there are no asserts then this case is passed\n");
 	printf("Press any key for next test case\n");
 	getchar();
}

int main (int argc,char *argv[])
{

	#ifdef SYMBIAN
 
 	//g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO |  G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
 	#endif /*SYMBIAN*/
 	
 	tg_relation_print();

 
 	tg_printf();	
 	tg_print_handler_test();
 	//tg_on_error_query();
  	 
 	return 0;
}