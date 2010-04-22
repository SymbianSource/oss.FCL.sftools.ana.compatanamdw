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
#include "glib.h"
#include <stdlib.h>


#ifdef SYMBIAN
#include "mrt2_glib2_test.h"
#endif /*SYMBIAN*/



gboolean res;

void g_unichar_digit_value_test()
{
	gunichar str='a';
	gunichar dig='7';
	   int i;
    i=g_unichar_digit_value(str);
    if(i!=-1)
	{
		g_printf("g_unichar_digit_value failed,str ='a' \n");
		g_assert(FALSE && "g_unichar_digit_value failed str ='a'\n");
	}
    
    i=g_unichar_digit_value(dig);
    if(i!=7 || i==-1)
	{
		g_print("g_unichar_digit_value failed,str ='7' \n");
		g_assert(FALSE && "g_unichar_digit_value failed str ='7'\n");
	}
 
}

void g_unichar_isalnum_test()
{
	gunichar str='8';
   	res=g_unichar_isalnum(str);
    if(res!=TRUE)
	{
		g_print("g_unichar_isalnum failed,str ='8' \n");
		g_assert(FALSE && "g_unichar_isalnum failed\n");
	}
 
}

void g_unichar_iscntrl_test()
{
	gunichar str ='\n';
	res=g_unichar_iscntrl(str);
	if(res!=TRUE)
	{
		g_print("g_unichar_iscntrl failed,str ='\n' \n");
		g_assert(FALSE && "g_unichar_iscntrl failed\n");
	}
	//g_assert(res==TRUE);
	str='a';
	res=g_unichar_iscntrl(str);
	if(res==TRUE)
	{
		g_print("g_unichar_iscntrl failed , str ='a'\n");
		g_assert(FALSE && "g_unichar_iscntrl failed\n");
	}
	//g_assert(g_unichar_iscntrl(str)==FALSE);
}



void g_unichar_isdigit_test()
{
	gunichar str ='6';
	res=g_unichar_isdigit(str);
	if(res!=TRUE)
	{
		g_print("g_unichar_isdigit failed,str ='\n' \n");
		g_assert(FALSE && "g_unichar_isdigit failed\n");
	}
	//g_assert(res==TRUE);
	str='a';
	res=g_unichar_isdigit(str);
	if(res==TRUE)
	{
		g_print("g_unichar_iscntrl failed , str ='a'\n");
		g_assert(FALSE && "g_unichar_iscntrl failed\n");
	}
	//g_assert(g_unichar_iscntrl(str)==FALSE);
}


void g_unichar_islower_test()
{
	gunichar str ='a';
	res=g_unichar_islower(str);
	if(res!=TRUE)
	{
		g_print("g_unichar_islower failed,str ='\n' \n");
		g_assert(FALSE && "g_unichar_islower failed\n");
	}
	//g_assert(res==TRUE);
	str='A';
	res=g_unichar_islower(str);
	if(res==TRUE)
	{
		g_print("g_unichar_islower failed , str ='a'\n");
		g_assert(FALSE && "g_unichar_islower failed\n");
	}
}

void g_unichar_ispunct_test()
{
	gunichar str ='!';
	res=g_unichar_ispunct(str);
	if(res!=TRUE)
	{
		g_print("g_unichar_ispunct failed,str ='\n' \n");
		g_assert(FALSE && "g_unichar_ispunct failed\n");
	}
	//g_assert(res==TRUE);
	str='A';
	res=g_unichar_ispunct(str);
	if(res==TRUE)
	{
		g_print("g_unichar_ispunct failed , str ='a'\n");
		g_assert(FALSE && "g_unichar_ispunct failed\n");
	}
}


void g_unichar_isupper_test()
{
	gunichar str ='A';
	res=g_unichar_isupper(str);
	if(res!=TRUE)
	{
		g_print("g_unichar_isupper failed '\n' \n");
		g_assert(FALSE && "g_unichar_isupper failed\n");
	}
	//g_assert(res==TRUE);
	str='a';
	res=g_unichar_isupper(str);
	if(res==TRUE)
	{
		g_print("g_unichar_isupper failed \n");
		g_assert(FALSE && "g_unichar_isupper failed\n");
	}
}

void g_unichar_isxdigit_test()
{
	gunichar str ='e';
	res=g_unichar_isxdigit(str);
	if(res!=TRUE)
	{
		g_print("g_unichar_isxdigit failed '\n' \n");
		g_assert(FALSE && "g_unichar_isxdigit failed\n");
	}
	//g_assert(res==TRUE);
	str='k';
	res=g_unichar_isxdigit(str);
	if(res==TRUE)
	{
		g_print("g_unichar_isxdigit failed \n");
		g_assert(FALSE && "g_unichar_isxdigit failed\n");
	}
}

void g_unichar_xdigit_value_test()
{
	int i;
	gunichar str ='e';
    i=g_unichar_xdigit_value(str);
	if(i!=14 || i==-1)
	{
		g_print("g_unichar_xdigit_value failed  \n");
		g_assert(FALSE && "g_unichar_xdigit_value failed\n");
	}
	
	str='4';
	i=g_unichar_xdigit_value(str);
	if(i!=4 || i==-1)
	{
		g_print("g_unichar_xdigit_value failed  \n");
		g_assert(FALSE && "g_unichar_xdigit_value failed\n");
	}
	
	
	//g_assert(res==TRUE);
	str='k';
	i=g_unichar_xdigit_value(str);
	if(i!=-1)
	{
		g_print("g_unichar_xdigit_value failed \n");
		g_assert(FALSE && "g_unichar_xdigit_value failed\n");
	}
}


void g_unichar_isgraph_test()
{
	gunichar str ='e';
    res=g_unichar_isgraph(str);
	if(res!=TRUE)
	{
		g_print("g_unichar_isgraph failed '\n' \n");
		g_assert(FALSE && "g_unichar_isgraph failed\n");
	}
	//g_assert(res==TRUE);
	str=' ';
	res=g_unichar_isgraph(str);
	if(res==TRUE)
	{
		g_print("g_unichar_isgraph failed \n");
		g_assert(FALSE && "g_unichar_isgraph failed\n");
	}
}

void g_unichar_isspace_test()
{
	gunichar str ='\t';
    res=g_unichar_isspace(str);
	if(res!=TRUE)
	{
		g_print("g_unichar_isspace failed '\n' \n");
		g_assert(FALSE && "g_unichar_isspace failed\n");
	}
	//g_assert(res==TRUE);
	str='5';
	res=g_unichar_isspace(str);
	if(res==TRUE)
	{
		g_print("g_unichar_isspace failed \n");
		g_assert(FALSE && "g_unichar_isspace failed\n");
	}
}

void g_unichar_isprint_test()
{
	gunichar str1=' ';
	gboolean res1;
	gunichar str2='a';
	res=g_unichar_isprint(str1);
	res1=g_unichar_isprint(str2);
	if(res!=TRUE || res1!=TRUE)
	{
		g_print("g_unichar_isprint failed\n");
		g_assert(FALSE && "g_unichar_isprint failed\n");
	}
	str1='\t';
	res=g_unichar_isprint(str1);
	if (res==TRUE)
	{
	    g_print("g_unichar_isprint failed\n");
		g_assert(FALSE && "g_unichar_isprint failed\n");
		
	}

}


int main (int   argc,
      char *argv[])
{
	#ifdef SYMBIAN
	g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
	#endif /*SYMBIAN*/
	
	g_unichar_digit_value_test();
	g_unichar_isalnum_test();
	g_unichar_iscntrl_test();
	g_unichar_islower_test();
	g_unichar_isupper_test();
	g_unichar_isxdigit_test();	
	g_unichar_xdigit_value_test();
	g_unichar_isgraph_test();
	g_unichar_ispunct_test();
	g_unichar_isspace_test();
	g_unichar_isdigit_test();
	g_unichar_isprint_test();


	#ifdef SYMBIAN
  	testResultXml("unichar_test");
  	#endif /* EMULATOR */
	
	return 0;
}