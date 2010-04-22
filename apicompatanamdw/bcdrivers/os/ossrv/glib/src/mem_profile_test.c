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



// This is a manual test case. Successfull execution of this test case will print 
// memory profile on stdout.

#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <stdio.h>
#include <glib.h>
#include <glib_global.h>


int main()
{
	int *a,*b;

	#ifdef SYMBIAN
	
  	#endif
  	
  	g_mem_set_vtable(glib_mem_profiler_table);
  	a = g_malloc(512);
  	b = g_malloc(1024);
    	
  	g_mem_profile();
}
