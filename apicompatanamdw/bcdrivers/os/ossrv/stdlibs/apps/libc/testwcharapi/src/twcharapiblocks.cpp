/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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



// INCLUDE FILES
#include "twcharapi.h"


// -----------------------------------------------------------------------------
// Ctwcharapi::twseekdir
// Testcase Description: Tests the behaviour of wseekdir() for different values of
// offset value. A directory list is created first and wtelldir(), wseekdir() and
// wreaddir() are used in combination.
// -----------------------------------------------------------------------------
//
TInt CTestWCharApi::twseekdir()
    {

   TInt expectedVal  = 0;
   TBuf8<50> string;
   TPtrC String;
   WDIR *Handle;
   
   _LIT( Klen, "Parameter1" );
   TBool res = GetIntFromConfig(ConfigSection(), Klen, expectedVal);	
   if(!res)
	{
	 	_LIT(Kerr , "Failed to read the value") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
	}
      
   wchar_t *file =L"c:\\test_wseekdir"; 
   wchar_t *file1 =L"Test_seek1.txt"; 
   wchar_t *file2 =L"Test_seek2.txt"; 
   wchar_t *file3 =L"Test_seek3.txt"; 
 
   wunlink(file1) ;
   wunlink(file2) ;
   wunlink(file3) ; 
   
   if(!wrmdir(file))
   {
    	_LIT(Kerr , "Failed to remove the given directory") ;
    	 INFO_PRINTF1(Kerr) ;
   }
   
   if(wchdir(file) < 0 ) 
   	{
   		if(wmkdir(file , 0777) < 0 ) 
   		{
   	
   			_LIT(Kerr , "Failed to create the given directory") ;
   	 		INFO_PRINTF1(Kerr) ;
   	 		return KErrGeneral ;
   		}
   	}
   
   if(wchdir(file) < 0 ) 
   	{
   	
   	_LIT(Kerr , "Failed to change the given directory") ;
   	 INFO_PRINTF1(Kerr) ;
   	 return KErrGeneral ;
   	}
   
   int fd = wopen(file1 , O_CREAT | O_RDWR , 0777) ;
   
   if(fd < 0 ) 
   	{
   	 _LIT(Kerr , "failed to open create file Test_seek1.txt") ;
   	 INFO_PRINTF1(Kerr) ;
   	 return KErrGeneral ;
   	}
   	
   	close (fd) ;
   	
   fd = wopen(file2 , O_CREAT | O_RDWR , 0777) ;
   
   if(fd < 0 ) 
   	{
   	 _LIT(Kerr , "failed to open create file Test_seek2.txt") ;
   	 INFO_PRINTF1(Kerr) ;
   	 return KErrGeneral ;
   	}
   	
   	close (fd) ; 
   	
   	
    fd = wopen(file3 , O_CREAT | O_RDWR , 0777) ;
   
   if(fd < 0 ) 
   	{
   	 _LIT(Kerr , "failed to open create file Test_seek3.txt") ;
   	 INFO_PRINTF1(Kerr) ;
   	 return KErrGeneral ;
   	}
   	
   	close (fd) ; 
   	off_t offset = 0;
   	if(expectedVal < 0 ) 
   	{  	   
   	   
   	   Handle = wopendir (file) ;   	   
   	   if(!Handle )	 
   	   {
   	     _LIT(Kerr , "Failed to open directory with NULL pointer ") ;
   	     INFO_PRINTF1(Kerr) ;
   	     return KErrNone ;	
   	   }
   	     
   	   
   	   offset = wtelldir(Handle);
   	   wseekdir(Handle, offset-1 ) ;
   	   struct wdirent *Dir ;
   	   Dir = wreaddir(Handle);
   	   if(!(Dir)) 
   	   	{
   	   	  _LIT(Kok , "invalid seek \n") ;
   	   	  INFO_PRINTF1(Kok) ;
   	   	}
   	   	else 
   	   	 {
   	   	   _LIT(Kerr , "read from from invalid handle \n") ;
   	   		INFO_PRINTF1(Kerr) ;
   	   		wclosedir(Handle);
   	   		return KErrGeneral ;
   	   	 }
   	   
   	   
   	   	 
   	   wrewinddir(Handle) ;
   	   offset = wtelldir(Handle);
   	   wseekdir(Handle, offset+4 ) ;
   		Dir = wreaddir(Handle);
   	   	 if(!Dir) 
   	   	 {
   	   	   _LIT(Kok , "Failed to read from the directory.... ") ;
   	   	   INFO_PRINTF1(Kok) ;
   	   	 }
   	   	wclosedir(Handle) ; 
	  	 
	  	Handle = NULL;
   	   	wseekdir(Handle,offset+4 );
   	   	wtelldir(Handle);
   		Dir = wreaddir(Handle);
   	   	 if(!Dir) 
   	   	 {
   	   	   _LIT(Kok , "Failed to read from the directory.... ") ;
   	   	   INFO_PRINTF1(Kok) ;
   	   	 }
   	   				
   	}
   	else
   	{
   	  	
    	struct wdirent *Dir ;
    	Handle =  wopendir (file);
    	if (Handle == NULL) 
   		{
   			_LIT(Kerr , "Failed to open given directory \n") ;
   			INFO_PRINTF1(Kerr) ;
   			return KErrGeneral ;
   		}
   	
   	 	wrewinddir(Handle) ;
   	 	offset = wtelldir(Handle);
   	 	wseekdir(Handle , offset + 2) ;
   	   	 
   		Dir = wreaddir(Handle);
      	 if(!Dir) 
   	   	 {
   	   	  _LIT(Kerr , "Failed to read from the directory.")  ;
   	   	  INFO_PRINTF1(Kerr) ;
   	   	  wclosedir(Handle) ;
   	   	  return KErrGeneral ;
   	   	 }
   	   	 
         Dir = wreaddir(Handle);
   	   	 if(!Dir) 
   	   	 {
   	   	  _LIT(Kok , "illegal seek.")  ;
   	   	  INFO_PRINTF1(Kok) ;
   	   	 }
   		
   		 wrewinddir(Handle) ;
   	   	  offset = wtelldir(Handle);
   	   	 wseekdir(Handle ,offset + 1) ;
   	   	 
   	   		Dir = wreaddir(Handle);
   	   	 if(!Dir) 
   	   	 {
   	   	   _LIT(Kerr , "Failed to read from the directory..") ;
   	   	   INFO_PRINTF1(Kerr) ;
   	   	   wclosedir(Handle) ;
   	   	   return KErrGeneral ;
   	   	 }
   	   	 
        	Dir = wreaddir(Handle);
   	   	 if(!Dir) 
   	   	 {
   	   	   _LIT(Kerr , "Failed to read from the directory... ") ;
   	   	   INFO_PRINTF1(Kerr) ;
   	   	   wclosedir(Handle) ;
   	   	   return KErrGeneral ;
   	   	 }
   	   	
   	   	 wrewinddir(Handle) ;
   	   	  offset = wtelldir(Handle);
   	   	 wseekdir(Handle , offset + 0 ) ;

   	   	 	Dir = wreaddir(Handle);
   	   	 if(!Dir) 
   	   	 {
   	   	   _LIT(Kerr , "Failed to read from the directory..... ") ;
   	   	   INFO_PRINTF1(Kerr) ;
   	   	   wclosedir(Handle) ;
   	   	   return KErrGeneral ;
   	   	 } 
   	wclosedir(Handle) ;
   	}
   wunlink(file1) ;
   wunlink(file2) ;
   wunlink(file3) ; 
   
   wrmdir(file) ;
   
   return KErrNone ; 	

}

// -----------------------------------------------------------------------------
// Ctwcharapi::twtelldir
// Testcase Description: Tests the behaviour of twtelldir() on a directory list 
// after reading each of its entry. It also tests its behaviour for a NULL directory
// handle.
// -----------------------------------------------------------------------------
//

TInt CTestWCharApi::twtelldir()
 {
	
   TInt expectedVal  = 0 ;
   TBuf8<50> string ;
   TPtrC String ;

    
   _LIT( Klen, "Parameter1" );
   TBool res = GetIntFromConfig(ConfigSection(), Klen, expectedVal);
   if(!res)
	{
	 	_LIT(Kerr , "Failed to read the value") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
	}
	   
   wchar_t *file =L"c:\\test_wseekdir"; 
   wchar_t *file1 =L"Test_seek1.txt"; 
   wchar_t *file2 =L"Test_seek2.txt"; 
   wchar_t *file3 =L"Test_seek3.txt"; 
    
   wunlink(file1) ;
   wunlink(file2) ;
   wunlink(file3) ; 
   
   if(!wrmdir(file))
   {
   	_LIT(Kerr , "Failed to remove the given directory") ;
   	 INFO_PRINTF1(Kerr) ;
   }
   
   if(wchdir(file) < 0 ) 
   	{
   		if(wmkdir(file , 0777) < 0 ) 
   		{   	
   			_LIT(Kerr , "Failed to create the given directory") ;
   	 		INFO_PRINTF1(Kerr) ;
   	 		return KErrGeneral ;
   		}
   	}
   
   if(wchdir(file) < 0 ) 
   	{
   	
   	_LIT(Kerr , "Failed to change the given directory") ;
   	 INFO_PRINTF1(Kerr) ;
   	 return KErrGeneral ;
   	}
   
   int fd = wopen(file1 , O_CREAT | O_RDWR , 0777) ;
   
   if(fd < 0 ) 
   	{
   	 _LIT(Kerr , "failed to open create file Test_seek1.txt") ;
   	 INFO_PRINTF1(Kerr) ;
   	 return KErrGeneral ;
   	}
   	
   	close (fd) ;
   	
   fd = wopen(file2 , O_CREAT | O_RDWR , 0777) ;
   
   if(fd < 0 ) 
   	{
   	 _LIT(Kerr , "failed to open create file Test_seek2.txt") ;
   	 INFO_PRINTF1(Kerr) ;
   	 return KErrGeneral ;
   	}
   	
   	close (fd) ; 
   	
   	
    fd = wopen(file3 , O_CREAT | O_RDWR , 0777) ;
   
   if(fd < 0 ) 
   	{
   	 _LIT(Kerr , "failed to open create file Test_seek3.txt") ;
   	 INFO_PRINTF1(Kerr) ;
   	 return KErrGeneral ;
   	}
   	
   	close (fd) ; 
   
   	if(expectedVal < 0 ) 
   	{
   		WDIR *Handle = NULL;
   		if(wtelldir(Handle)<0)
   		{
   			_LIT(Kok , "illegal seek.")  ;
   	   	  	INFO_PRINTF1(Kok) ;	
   		}
   		
   	}//expectedVal if 
   	else
   	{
   		int count = 0;
   		struct wdirent *Dir ;
   		WDIR *Handle =  wopendir (file);
   		Dir = wreaddir(Handle);
   		while(Dir) 
   		{
   			count++ ;
   			if(count != wtelldir(Handle)) 
   			{
   				_LIT(Kerr , "value returned from telldir is not same as expected.");
   				INFO_PRINTF1(Kerr) ;
   				wclosedir(Handle);	
   				return KErrGeneral ;
   			}
   			Dir = wreaddir(Handle);
   		}
   	wclosedir(Handle);
   	}
 wunlink(file1) ;
 wunlink(file2) ;
 wunlink(file3) ; 
 
 wrmdir(file) ;
 return KErrNone ;   	
 }

// -----------------------------------------------------------------------------
// Ctwcharapi::twasctime
// Testcase Description: Tests the behaviour of twasctime() with valid tm and invalid(NULL)
// parameters.
// -----------------------------------------------------------------------------
//

TInt CTestWCharApi::twasctime()
 {
 
 	TPtrC Localeread;
 	TInt flag;
 	
	_LIT( KString, "Parameter1" );
	TBool res = GetStringFromConfig(ConfigSection(), KString, Localeread);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read string") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
		}
   
    _LIT( KFlag, "Parameter2" );
    res = GetIntFromConfig(ConfigSection(), KFlag, flag);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read value") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
		}
   	
   if(flag == 0)	
   {
     
   	TBuf8<100> buf;
	buf.Copy(Localeread);
	char* locale = (char*) buf.Ptr();
	locale[buf.Length()]='\0';
	
   	struct tm *timeptr=(struct tm*)malloc(sizeof(struct tm));
   	
   	memset(timeptr, 0, sizeof(struct tm));

	setlocale(LC_ALL, locale);
	
	wchar_t expectedtime[100]; 

	wcscpy(expectedtime,L"Sun Jan  0 00:00:00 1900\n");
	
	wchar_t *s=wasctime(timeptr);

	free(timeptr); 

	if(wcscmp(expectedtime,s)==0)
		return KErrNone ;
	else
		 return KErrGeneral ;
   }
   else
   {
   		wchar_t *s=wasctime(NULL);
   		if(s==NULL)
			return KErrNone ;
		else
		 return KErrGeneral ;
   }
   
 }
 
// -----------------------------------------------------------------------------
// Ctwcharapi::twctime
// Testcase Description: Tests the behaviour of twctime() with valid tm and invalid(NULL)
// parameters.
// -----------------------------------------------------------------------------
//
TInt CTestWCharApi::twctime()
 {
 	TPtrC Localeread;
 	TInt flag;
 	
	_LIT( KString, "Parameter1" );
	TBool res = GetStringFromConfig(ConfigSection(), KString, Localeread);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read string") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
		}
   
    _LIT( KFlag, "Parameter2" );
    res = GetIntFromConfig(ConfigSection(), KFlag, flag);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read value") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
		}
   	
   if(flag == 0)	
   {
     
   	TBuf8<100> buf;
	buf.Copy(Localeread);
	char* locale = (char*) buf.Ptr();
	locale[buf.Length()]='\0';
	
   	time_t timeptr = 0;
	
	setlocale(LC_ALL, locale);
	
	wchar_t expectedtime[100]; 

	wcscpy(expectedtime,L"Thu Jan  1 00:00:00 1970\n");
	
	wchar_t *s=wctime(&timeptr);


	if(wcscmp(expectedtime,s)==0)
		return KErrNone ;
	else
		 return KErrGeneral ;
   }
   else
   {
   		wchar_t *s=wctime(NULL);
   		if(s==NULL)
			return KErrNone ;
		else
		 return KErrGeneral ;
   }
 }


// -----------------------------------------------------------------------------
// Ctwcharapi::twcslcat
// Testcase Description: Tests the behaviour of twcslcat() for different values
// of size including zero.
// -----------------------------------------------------------------------------
//

TInt CTestWCharApi::twcslcat()
 {
 	TInt flag;
 	
    _LIT( KFlag, "Parameter1" );
    TBool res = GetIntFromConfig(ConfigSection(), KFlag, flag);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read value") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
		}
	 wchar_t src[10] = L"Source";
  	 wchar_t dest[20]= L"Destination";


	if (0 == flag)
	{
			// less size 
		size_t t = wcslcat(dest,src,14);
		wchar_t expected[30]; 
		wcscpy(expected,L"DestinationSo");
		
		if(wcscmp(expected,dest)==0)
			return KErrNone ;
		else
			 return KErrGeneral ;
		
	}
	
	if (1 == flag)
	{
		// equal size 
		size_t t = wcslcat(dest,src,18);
		wchar_t expected[30]; 
		wcscpy(expected,L"DestinationSource");
		
		if(wcscmp(expected,dest)==0)
			return KErrNone ;
		else
			 return KErrGeneral ;
		
	}
 	if (2 == flag)
 	{
 			// greater size 
 		size_t t = wcslcat(dest,src,22);
		wchar_t expected[30]; 
		wcscpy(expected,L"DestinationSource");
		
		if(wcscmp(expected,dest)==0)
			return KErrNone ;
		else
			 return KErrGeneral ;
  	}
  	  	
  	if (3 == flag)
 	{
 			// greater size 
 		size_t t = wcslcat(dest,src,0);
		wchar_t expected[30]; 
		wcscpy(expected,L"Destination");
		
		if(wcscmp(expected,dest)==0)
			return KErrNone ;
		else
			 return KErrGeneral ;
  	}
  	
   	return KErrNone ;  	
 }
 
// -----------------------------------------------------------------------------
// Ctwcharapi::twcslcpy
// Testcase Description: Tests the behaviour of twcslcpy() for different values
// of size including zero.
// -----------------------------------------------------------------------------
//
 
 TInt CTestWCharApi::twcslcpy()
 {
 	TInt flag;
 	//wsetlocale(LC_ALL,L"fi_FI.ISO-8859-1");
 	
    _LIT( KFlag, "Parameter1" );
    TBool res = GetIntFromConfig(ConfigSection(), KFlag, flag);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read value") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
		}
  	 
  	 wchar_t src[10] = L"Source";
  	 wchar_t dest[20]= L"Destination";

	if (0 == flag)
	{
		// less size 
		size_t t = wcslcpy(dest,src,4);
		wchar_t expected[20]; 
		wcscpy(expected,L"Sou");
		
		if(wcscmp(expected,dest)==0)
			return KErrNone ;
		else
			 return KErrGeneral ;
		
	}
	
	if (1 == flag)
	{
		// equal size
		size_t t = wcslcpy(dest,src,7);
		wchar_t expected[20]; 
		wcscpy(expected,L"Source");
		
		if(wcscmp(expected,dest)==0)
			return KErrNone ;
		else
			 return KErrGeneral ;	
	}
 	if (2 == flag)
 	{
 		// greater size
 		size_t t = wcslcpy(dest,src,15);
 		wchar_t expected[20]; 
		wcscpy(expected,L"Source");
		
		if(wcscmp(expected,dest)==0)
			return KErrNone ;
		else
		  return KErrGeneral ;
 	}
 
 	if (3 == flag)
 	{
 		// for zero size
 		size_t t = wcslcpy(dest,src,0);
 		wchar_t expected[20]; 
		wcscpy(expected,L"Destination");
		
		if(wcscmp(expected,dest)==0)
			return KErrNone ;
		else
		  return KErrGeneral ;
 	} 	
   	return KErrNone ; 	
 }
 
 
 TInt CTestWCharApi::twsetlocale()
 {
 	TPtrC Localeread;
 	wchar_t wlocale[100];
 	wchar_t *currentlocale;
 	LocateSupportedDLLs();
 
	_LIT( KString, "Parameter1" );
	TBool res = GetStringFromConfig(ConfigSection(), KString, Localeread);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read string") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
		}
   
   	TBuf8<100> buf;
	buf.Copy(Localeread);
	char* locale = (char*) buf.Ptr();
	locale[buf.Length()]='\0';
	
	TInt j = 0;
	TInt flag = 0;
    while(j < SUPPORTED_LOCALES)
    {
    	if((strcmp(locales[j].localeName,locale)== 0) && locales[j].flag)
    	{
    		flag = 1;
			break;	    						
    	}
    	j++;
    }
   
    mbstowcs(wlocale, (char*)locale, 100); 
    if(flag == 1)
    {
    	wchar_t *ret_wlocale;
       	ret_wlocale = wsetlocale(LC_ALL,wlocale);
       	if(ret_wlocale)
       		delete []ret_wlocale;
       	
		currentlocale = wsetlocale(LC_ALL,NULL);
		if (0 ==wcscmp(currentlocale,wlocale))
			{
			delete []currentlocale;
			return KErrNone ;			
			}
		else if(currentlocale)
	    	{
	    	delete []currentlocale;
	    	return KErrGeneral ;	
	    	}
    }
    else
	{
			if (0 ==wcscmp(L"Unspecified",wlocale))
			{
				currentlocale = wsetlocale(LC_ALL,wlocale);
				if(currentlocale == NULL)
					return KErrNone ;
				else
					{
					delete []currentlocale;
					return KErrGeneral ;
					}
					
			}
			return KErrNone ;
	}    
	return KErrNone ;
 }
 
 TInt CTestWCharApi::twsetlocale1()
 {
 	wchar_t* ret;
 	ret = wsetlocale(LC_ALL,NULL);
 	if ( ret == NULL)
 		return KErrNone;
	else if(ret)
		{
		delete []ret;
		return KErrGeneral;
		}
	return KErrNone ;
 	
 }
  
 TInt CTestWCharApi::twperror()
 {
	wperror(L"wperror");
 	return KErrNone ;
 }
 
 TInt CTestWCharApi::twcserror()
 {
 	TPtrC Expectedmsg;
  	wchar_t wmsg[100];
 	wchar_t *errmsg;
 	TPtrC Localeread;
 	TInt errnumber;
 	
    _LIT( KFlag, "Parameter1" );
    TBool res = GetIntFromConfig(ConfigSection(), KFlag, errnumber);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read value") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
		}
  	 
  	// Get Locale To set
	
	_LIT( KString, "Parameter2" );
	res = GetStringFromConfig(ConfigSection(), KString, Localeread);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read string") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
		}
   	
   	TBuf8<100> buf;
   
	buf.Copy(Localeread);
	char* locale = (char*) buf.Ptr();
	locale[buf.Length()]='\0';
	setlocale(LC_ALL,locale);
 	
 	// Get Expected Message
	TBuf8<100> bufmsg;
 	
	_LIT( KString2, "Parameter3" );
	res = GetStringFromConfig(ConfigSection(), KString2, Expectedmsg);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read string") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
		}
  	 
 	bufmsg.Copy(Expectedmsg);
 	_LIT(p," ");
 
 	_LIT( KString3, "Parameter4" );
 	if (GetStringFromConfig(ConfigSection(), KString3, Expectedmsg)) 
   	{
   	
   		bufmsg.Append(p);
		bufmsg.Append(Expectedmsg);
   	}
   		
	char* msg = (char*) bufmsg.Ptr();
	msg[bufmsg.Length()]='\0';
	mbstowcs(wmsg, (char*)msg, 100); 
	
	errmsg = wcserror(errnumber);
	
	if(0==wcscmp(errmsg,wmsg))
	 	return KErrNone ;
 	else
 		return KErrGeneral ;
 }
 
 // -----------------------------------------------------------------------------
// Ctwcharapi::twfindfirst
// Testcase Description: Tests the behaviour of wfindfirst() and twfindnext() 
// by finding the first *.c file in the current directory and also finding the next one
// from there.
// -----------------------------------------------------------------------------
//
TInt CTestWCharApi::twfindfirst()
{
   struct _wfinddata_t c_file;
   long hFile;
	
   wchar_t *file =L"c:\\test_wfindfirst"; 
   wchar_t *file1 =L"Test_seek1.c"; 
   wchar_t *file2 =L"Test_seek2.c"; 
   wchar_t *file3 =L"Test_seek3.c"; 
 
   wunlink(file1) ;
   wunlink(file2) ;
   wunlink(file3) ; 
   
   if(!wrmdir(file))
   {
   	_LIT(Kerr , "Failed to remove the given directory") ;
   	 INFO_PRINTF1(Kerr);
   }
   
   if(wchdir(file) < 0 ) 
   	{
   		if(wmkdir(file , 0777) < 0 ) 
   		{
   	
   			_LIT(Kerr , "Failed to create the given directory") ;
   	 		INFO_PRINTF1(Kerr);
   	 		return KErrGeneral ;
   		}
   	}

   if(wchdir(file) < 0 ) 
   	{
   	
   	_LIT(Kerr , "Failed to change the given directory") ;
   	 INFO_PRINTF1(Kerr);
   	 return KErrGeneral ;
   	}
   
   int fd = wopen(file1 , O_CREAT | O_RDWR , 0777) ;
   
   if(fd < 0 ) 
   	{
   	 _LIT(Kerr , "failed to open create file Test_seek1.txt") ;
   	 INFO_PRINTF1(Kerr);
   	 return KErrGeneral ;
   	}
   	
   	close (fd) ;
   	
   fd = wopen(file2 , O_CREAT | O_RDWR , 0777) ;
   
   if(fd < 0 ) 
   	{
   	 _LIT(Kerr , "failed to open create file Test_seek2.txt") ;
   	 INFO_PRINTF1(Kerr);
   	 return KErrGeneral ;
   	}
   	
   	close (fd) ; 
   	
   	
    fd = wopen(file3 , O_CREAT | O_RDWR , 0777) ;
   
   if(fd < 0 ) 
   	{
   	 _LIT(Kerr , "failed to open create file Test_seek3.txt") ;
   	 INFO_PRINTF1(Kerr);
   	 return KErrGeneral ;
   	}
   	
	close (fd) ; 

   // Find first .c file in current directory 
  if( (hFile = wfindfirst( L"t*.c", &c_file )) == -1L )
  {
    _LIT(Kerr , "failed to find files in directory ") ;
   	 INFO_PRINTF1(Kerr);
   	 return KErrGeneral ;	 
  }
  else
   {
   	  			

   		 	if((wcscmp((wchar_t*)c_file.name,file1))||(c_file.attrib & _A_RDONLY )|| (c_file.attrib & _A_HIDDEN) ||  (c_file.attrib &_A_SYSTEM) || (!(c_file.attrib & _A_ARCH)))
   		 	{
   		 		_LIT(Kerr , "failed to find file in directory ") ;
   	 			INFO_PRINTF1(Kerr);
   				 return KErrGeneral ;
   		 	}
   	
   }
   
   
   
  
   if(wfindnext( hFile, &c_file ) == 0 )
   {
   			  if((wcscmp((wchar_t*)c_file.name,file2))||(c_file.attrib & _A_RDONLY )|| (c_file.attrib & _A_HIDDEN) || (c_file.attrib &_A_SYSTEM) || (!(c_file.attrib & _A_ARCH)))
   			  {
   			     			  			
   			_LIT(Kerr , "failed to find file in directory ") ;
   	 		INFO_PRINTF1(Kerr);
   			 return KErrGeneral ;
   			  }
   	
   }
   else
   {
 		  _LIT(Kerr , "failed to find file in directory ") ;
   	 		INFO_PRINTF1(Kerr);
   			 return KErrGeneral ;	
   	
   }
    
   
   
    
    if(wfindnext( hFile, &c_file ) == 0 )
   {
   	
   			 if((wcscmp((wchar_t*)c_file.name,file3)) ||(c_file.attrib & _A_RDONLY )|| (c_file.attrib & _A_HIDDEN) || (c_file.attrib &_A_SYSTEM) || (!(c_file.attrib & _A_ARCH)))
   			 {
   			 _LIT(Kerr , "failed to find file in directory ") ;
   	 		INFO_PRINTF1(Kerr);
   			 return KErrGeneral ;
   			 }
   		
   }
   else
   {
 		  _LIT(Kerr , "failed to find file in directory ") ;
   	 		INFO_PRINTF1(Kerr);
   			 return KErrGeneral ;	
   	
   }
   
   if(wfindnext( hFile, &c_file ) == 0 )
   {
   			_LIT(Kerr , "find wrong file in directory ") ;
   	 		INFO_PRINTF1(Kerr);
   			 return KErrGeneral ;	
   	
   }
   
    findclose( hFile );


return KErrNone ;
 }
 

// -----------------------------------------------------------------------------
// Ctwcharapi::twfindfirst
// Testcase Description: Tests the behaviour of wfindfirst(), twfindnext() and 
// twfindclose() for invalid parameters.
// -----------------------------------------------------------------------------
//
 
TInt CTestWCharApi::twfindfirst1()
{
	struct _wfinddata_t c_file;
	
	if( (wfindfirst(NULL, &c_file) == EINVAL) && 
				(wfindfirst(L"t*.c", NULL) == EINVAL))
		return KErrNone;

	return KErrGeneral;
}


TInt CTestWCharApi::twfindnext1()
{
	struct _wfinddata_t c_file;
	
	if( (wfindnext(0, &c_file) == EINVAL) && 
				(wfindnext(1, NULL) == EINVAL) )
		return KErrNone;

	return KErrGeneral;
}


TInt CTestWCharApi::twfindclose( )
 {
 	long hFile = 0;
 	
 	if(findclose( hFile )== -1)
 		return KErrNone ;
 
 	return KErrGeneral ;	
 }
  

void CTestWCharApi::LocateSupportedDLLs()
{
	TInt j = 0;
	FILE* stream = NULL;
	stream = fopen("C:\\resource\\locales.txt", "r");
	if(stream == NULL)
	return;	
	
	RSessionBase aSessionBase;
	RLoader loader;
			
	char buffer[25];
	char* buf = fgets(buffer, 50, stream);
	
	while(buf != NULL)
	{
		int  i = 0;
		while(buffer[i] != '=')
		{
			locales[j].localeName[i] = buffer[i];
			i++;				
		}
		locales[j].localeName[i++] = '\0';

		TBuf<20> DllName;
		_LIT(KDllName, "elocl.");
		DllName.Copy(KDllName);
				
		while(buffer[i] && ('\r' != buffer[i]) && ('\n' != buffer[i]))
		{
			DllName.Append(buffer[i]);	
			i++;
		}
		
		TInt r = loader.Connect();
		if(KErrNone == r)
		{
			TLibraryFunction data[22];
			TInt size = 22 * sizeof(TLibraryFunction);
			TPtr8 functionListBuf((TUint8*) data, size, size);
			r = loader.SendReceive(ELoadLocale, TIpcArgs(0, (const TDesC*)&DllName, &functionListBuf) );
			locales[j].flag = (KErrNone == r)? 1:0;
		}
		aSessionBase.Close();
		loader.Close();
		
		buffer[0] = '\0';
		buf = fgets(buffer, 50, stream);
		j++;
	}
	fclose(stream);
}

TInt CTestWCharApi::wcreat2()
	{
    int i;
    i=wcreat(NULL,0777);

	if  (i < 0 && errno == EFAULT) 
		{        
		INFO_PRINTF1(_L("wcreat success"));
        return KErrNone;
		}
	return KErrGeneral;
	}
TInt CTestWCharApi::wpopen3_1()
	{
	int fds[3];
	int childid= wpopen3( NULL,NULL, NULL, fds);
	if  (childid == -1 && errno == ENOENT) 
		{        
        INFO_PRINTF1(_L("wpopen success"));
		return KErrNone;
		}
	return KErrGeneral;
	}
