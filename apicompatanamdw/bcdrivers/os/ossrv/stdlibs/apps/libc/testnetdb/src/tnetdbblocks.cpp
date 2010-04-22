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


 /*
* ==============================================================================
*  Name        : tnetdbblocks.cpp
*  Part of     : testnetdbblocks
*
*  Description : ?Description
*  Version:   0.5
*
  
*/

#include "tnetdb.h"


// for RHostResolver
#include <ES_SOCK.H>
#include <in_sock.h>


// -----------------------------------------------------------------------------
// CTestNetdb::NetdbTest
// Test for gethostbyname and gethostbyaddress.
// -----------------------------------------------------------------------------
//
TInt CTestNetdb::GethostbynameTest()
    {
    struct hostent *hp = 0;
	struct in_addr *addrp=0;
	char test_url[50] = "" ;
	
    TPtrC string;
    TBuf8<256> bufstring;
    TInt paramLength=0;
    
    _LIT( Kstring, "Param%d" );
	TBuf<8> pNameBuf;
    pNameBuf.Format(Kstring,++iParamCnt);
    while (GetStringFromConfig(ConfigSection(), pNameBuf, string ))
        {
        bufstring.Copy(string);
        paramLength=string.Length();
        char* text=(char *)(bufstring.Ptr());
        *(text+paramLength)='\0';
        strcpy(test_url,text);
        pNameBuf.Format(Kstring,++iParamCnt);
        }  
   	// Test for gethostbyname using a url
    hp = gethostbyname(test_url);
	if (hp != NULL)
	    {
	    addrp = (struct in_addr*)(hp->h_addr_list[0]);
		INFO_PRINTF3(_L ("address %-15s => %s\n"), inet_ntoa(*addrp), hp->h_name);
		INFO_PRINTF1(_L("gethostbyname() Pass\n"));
		}
	else
		{
	    INFO_PRINTF1(_L("gethostbyname() Fail\n"));
		return KErrGeneral;		    
		}
    return KErrNone;
    }
		
	
// -----------------------------------------------------------------------------
// CTestNetdb::GetHostByNameNegativeTest
// Test for gethostbyname by passing NULL
// -----------------------------------------------------------------------------
//
TInt CTestNetdb::GethostbynameNegativeTest()
    {
    struct hostent *hp = NULL;
        
    hp = gethostbyname(NULL);
    
    if (hp != NULL)
	    {
	    INFO_PRINTF1(_L("gethostbyname() failed"));
		return KErrGeneral;
		}
	
	INFO_PRINTF2(_L("gethostbyname() failed with errno no: %d, Test case passed"), errno);
	return KErrNone;		// negative test case
    }
    
/*
*	Testcase	:	GetHostByNameLocalHost
*	Description	:	Verifies the result on passing "localhost" to gethostbyname
*	Result		:	gethostbyname fills up hostent struct with loopback IP 127.0.0.1
**/    

TInt CTestNetdb::GetHostByNameLocalHost()
	{
	struct hostent *h = NULL;
	struct sockaddr_in localaddr;
	char hostname[256]="";
	char ipaddr[20];
	int ret = KErrNone;
	
	//The hostname is always "LocalHost"
	gethostname(hostname,256);

	h=gethostbyname(hostname);
			
	if (h != NULL)
		{
		memcpy(&localaddr.sin_addr, h->h_addr_list[0], 4);
		strcpy(ipaddr,inet_ntoa(localaddr.sin_addr));
		TPtrC8 ipaddrPtr(reinterpret_cast<TUint8*>(ipaddr));
		TBuf8<40> ipAddrBuf;
		ipAddrBuf.Copy(ipaddrPtr);
		INFO_PRINTF1(_L("The correct loopback IP is returned"));
		ret = KErrNone;
		}
	else
		{
		INFO_PRINTF1(_L("gethostbyname returns NULL"));
		ret = KErrGeneral;
		}
		
	return ret;
	}


	
TInt CTestNetdb::GethostbyaddrTest()
	{
	// Test for gethostbyaddr, c
	unsigned long test_addr;
	struct in_addr *addrp=0;
	char test_address[50] ;
    TPtrC string;
    TInt paramLength;
    TBuf8<256> bufstring;
    
    _LIT( Kstring, "Param%d" );
	TBuf<8> pNameBuf;
    pNameBuf.Format(Kstring,++iParamCnt);
    while ( GetStringFromConfig(ConfigSection(), pNameBuf, string ) )
        {
        bufstring.Copy(string);
        paramLength=string.Length();
        char* text=(char *)(bufstring.Ptr());
        *(text+paramLength)='\0';
        strcpy(test_address,text);
        pNameBuf.Format(Kstring,++iParamCnt);
        }  
	struct hostent *hp1=0;
    test_addr=inet_addr(test_address);
    hp1 = gethostbyaddr((const char *)(&test_addr),sizeof(test_addr),AF_INET);
    if (hp1 != NULL)
		{
		addrp = (struct in_addr*)(hp1->h_addr_list[0]);
		INFO_PRINTF3(_L("  address %-15s => %s\n"), inet_ntoa(*addrp), hp1->h_name);
		INFO_PRINTF1(_L("gethostbyaddr() Pass\n"));
		}
    else
	    {		    
		ERR_PRINTF1(_L("gethostbyaddr() Fail\n"));
		return KErrGeneral;
	    }
		return KErrNone;
    }




TInt CTestNetdb::GetprotobynameTest()
    {
    protoent *p =0;
	char proto[50] = "" ;
    TPtrC string;
    TBuf8<256> bufstring;
    TInt paramLength=0;
    _LIT( Kstring, "Param%d" );
	TBuf<8> pNameBuf;
    pNameBuf.Format(Kstring,++iParamCnt);
    while ( GetStringFromConfig(ConfigSection(), pNameBuf, string ) )
        {
        bufstring.Copy(string);
        paramLength=string.Length();
        char* text=(char *)(bufstring.Ptr());
        *(text+paramLength)='\0';
        strcpy(proto,text);
        pNameBuf.Format(Kstring,++iParamCnt);
        }  
   	p=getprotobyname(proto);
   	if(p==NULL)
   		{
   		return KErrGeneral;
   		}
     return KErrNone;
    }
    
 
TInt CTestNetdb::GetprotobynumberTest()
    {
    protoent *p =0;
	int proto=0;
	_LIT( Kproto, "Param%d" );
	TBuf<8> pNameBuf;
    pNameBuf.Format(Kproto,++iParamCnt);
    GetIntFromConfig(ConfigSection(), pNameBuf, proto );
    
    p=getprotobynumber(proto);
   	if(p==NULL)
   		{
   		return KErrGeneral;
   		}
    return KErrNone;
    }   
    
    
 TInt CTestNetdb::GetservbynameTest()
    {
    int i=0;
	servent *p =0;
	char param[2][50]  ;
    TPtrC string;
    TBuf8<256> bufstring;
    TInt paramLength=0;
    _LIT( Kstring, "Param%d" );
	TBuf<8> pNameBuf;
    pNameBuf.Format(Kstring,++iParamCnt);
    while ( GetStringFromConfig(ConfigSection(), pNameBuf, string ) )
        {
        bufstring.Copy(string);
        paramLength=string.Length();
        char* text=(char *)(bufstring.Ptr());
        *(text+paramLength)='\0';
        strcpy(param[i],text);
        i++;
        pNameBuf.Format(Kstring,++iParamCnt);
        }  
   	if(i==1)
   	p=getservbyname(param[0],0);
   	else
   	p=getservbyname(param[0],param[1]);
   	if(p==NULL)
   		{
   		return KErrGeneral;
   		}
    return KErrNone;
    }   
    
TInt CTestNetdb::GetservbyportTest()
    {
    servent *p =0;
	char *param=0;
	int port;
    TPtrC string;
    TBuf8<256> bufstring;
    TInt paramLength=0;
    _LIT( Kport, "Param%d" );
	TBuf<8> pNameBuf;
    pNameBuf.Format(Kport,++iParamCnt);
    GetIntFromConfig(ConfigSection(), pNameBuf, port );
    _LIT( Kstring, "Param%d" );
    pNameBuf.Format(Kstring,++iParamCnt);

    while ( GetStringFromConfig(ConfigSection(), pNameBuf, string ) )
        {
        bufstring.Copy(string);
        paramLength=string.Length();
        char* text=(char *)(bufstring.Ptr());
        *(text+paramLength)='\0';
        param=(char *)malloc(sizeof(paramLength+1));
        strcpy(param,text);
        pNameBuf.Format(Kstring,++iParamCnt);
        }
	
   	p=getservbyport(port,param);
   	if(p==NULL)
   		{
   		free(param);
   		return KErrGeneral;
   		}
   	free(param);
    return KErrNone;
    }   
    
    
TInt CTestNetdb::GetaddrinfoTest()
    {
    char param[10][250]  ;
	char *hostname=0;
	char *servname=0;
	struct addrinfo hint;
	TInt paramLength;
	struct addrinfo *res=NULL;
	int paramint[5];
	int i=0;
    TPtrC string;
    TBuf8<256> bufstring;
    _LIT( Kstring, "Param%d" );
	TBuf<8> pNameBuf;
    pNameBuf.Format(Kstring,++iParamCnt);
    TBool ret = GetStringFromConfig(ConfigSection(), pNameBuf, string );

    while(ret)
        {
        bufstring.Copy(string);
        paramLength=string.Length();
        char* text=(char *)(bufstring.Ptr());
        *(text+paramLength)='\0';
        strcpy(param[i],text);
        i++;
        if(i==2)
			{
			break;
			}
        pNameBuf.Format(Kstring,++iParamCnt);
        ret = GetStringFromConfig(ConfigSection(), pNameBuf, string );
        }  

   	if(strcmp(param[0],"0"))
   		{
   		hostname=(char *)malloc(sizeof(param[0])+1);
   		strcpy(hostname,param[0]);
   		}
   	if(strcmp(param[1],"0"))
   		{
   		servname=(char *)malloc(sizeof(param[1])+1);
   		strcpy(servname,param[1]);
   		}
   	
   	/*Filling the Hint structure*/
    i=0;
    _LIT( Kparamint, "Param%d" );

    pNameBuf.Format(Kparamint,++iParamCnt);
    while (GetIntFromConfig(ConfigSection(), pNameBuf, paramint[i++]))
		{
    	pNameBuf.Format(Kstring,++iParamCnt);	
		}
	hint.ai_flags=paramint[0];
    hint.ai_family=paramint[1];
    hint.ai_socktype=paramint[2];
    hint.ai_protocol=paramint[3];
    hint.ai_addrlen=0;
    hint.ai_addr=0;
    hint.ai_canonname=0;
    hint.ai_next=0;
    int err=getaddrinfo(hostname,servname,&hint,&res);
     if(err!=0)
    	{
    	if(hostname)
    		free(hostname);
    	if(servname)
    		free(servname);
    	if(res)
    		freeaddrinfo(res);
    	return KErrGeneral;
    	}
   	if(hostname)
   		free(hostname);
   	if(servname)
   		free(servname);
   	if(res)
   		freeaddrinfo(res);
   	return KErrNone;
    }   
        
           
    
      
TInt CTestNetdb::GetnameinfoTest()
    {
    struct sockaddr ss;
    TPtrC string;
    TBuf8<256> bufstring;
    char hostname[MAXBUF];
    char servname[MAXBUF];
    int paramint[3];
    int flag;
    int paramLength;
    int i=0;
    
    _LIT( Kstring, "Param%d" );
	TBuf<8> pNameBuf;
    pNameBuf.Format(Kstring,++iParamCnt);
    while (GetIntFromConfig(ConfigSection(), pNameBuf, paramint[i]))
    	{
    	if(i==2)
			{
    		break;
			}
    	i++;
    	pNameBuf.Format(Kstring,++iParamCnt);
    	}
    i=0;
    ss.sa_family=paramint[i++];
    ss.sa_port=paramint[i++];;
    flag=paramint[i];
    
    pNameBuf.Format(Kstring,++iParamCnt);
    
    while (GetStringFromConfig(ConfigSection(), pNameBuf, string))
        {
        bufstring.Copy(string);
        paramLength=string.Length();
        char* text=(char *)(bufstring.Ptr());
        *(text+paramLength)='\0';
        strcpy(ss.sa_data,text);
        pNameBuf.Format(Kstring,++iParamCnt);
        }  
    int err=getnameinfo(&ss,sizeof(struct sockaddr_in),hostname,sizeof(hostname),servname,sizeof(servname),flag);
    if(err==0)
    	{
    	return KErrNone;
    	}
    return KErrGeneral;
    }     
    
 TInt CTestNetdb::GetnameinfoTest1()
    {
	char hostname1[80];
	struct sockaddr_in sdg;
    TPtrC address,name;
    TInt len;
	GetStringFromConfig(ConfigSection(),_L("address"), address);	
    GetStringFromConfig(ConfigSection(),_L("name"), name); 
	TBuf8<200> buf1,buf2;
	buf1.Copy(address);
	char* inputstr = (char*) buf1.Ptr();
	len=buf1.Length();
	inputstr[len]='\0';
    buf2.Copy(name);
	char* inputstr1 = (char*) buf2.Ptr();
	len=buf2.Length();
	inputstr1[len]='\0';
    sdg.sin_family=AF_INET;
    sdg.sin_port=htons(0);
    inet_aton(inputstr,&sdg.sin_addr);  
    int err= getnameinfo( (struct sockaddr*)&sdg, sizeof(struct sockaddr_in), hostname1, sizeof(hostname1), NULL,0,0);
    int i=strcmp(inputstr1,hostname1);
     if(i==0)
     {
     return KErrNone;
     }
     
     return KErrGeneral;
    
    }     
TInt CTestNetdb::SetserventTest()
    {
    int stayopen;
     	
    _LIT( Kstring, "Param%d" );
	TBuf<8> pNameBuf;
	pNameBuf.Format(Kstring,++iParamCnt);
	GetIntFromConfig(ConfigSection(), pNameBuf, stayopen);
     
    setservent(stayopen);
    return KErrNone;
    }     
        
TInt CTestNetdb::Gai_strerrorTest()
    {
    int errnum;
    const char *errordesc;
    const char* temp="Unknown error";
    _LIT( Kstring, "Param%d" );
	TBuf<8> pNameBuf;
	pNameBuf.Format(Kstring,++iParamCnt);
	GetIntFromConfig(ConfigSection(), pNameBuf, errnum);
    
    errordesc=gai_strerror(errnum);
    if(strcmp(errordesc,temp))
		{
        return KErrNone;
        }
    return KErrGeneral;
    }     
            

        
TInt CTestNetdb::FreeaddrinfoTest()
    {
    struct addrinfo *test_struct;
    test_struct=(struct addrinfo*)malloc (sizeof(struct addrinfo));
    test_struct->ai_next=NULL;
    test_struct->ai_canonname=NULL;
    freeaddrinfo(test_struct);
    return KErrNone;
    } 
    
    
     
TInt CTestNetdb::GetserventTest()
    {
    struct servent *p;
    int i;
    for(i=0;i<25;i++)
		{
     	p=getservent();
		}
    if(p)
		{
        return KErrNone;
		}
    else
		{
        return KErrGeneral;
		}
    }    


     
TInt CTestNetdb::EndserventTest()
    {
    struct servent *p;
    p=getservent();
    if(!p)
		{
        return KErrGeneral;
		}
    else
		{
        endservent();
		}
    return KErrNone;
    }
