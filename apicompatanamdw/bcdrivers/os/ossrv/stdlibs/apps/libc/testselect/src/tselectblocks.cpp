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
*  Name        : tselectblocks.cpp
*  Part of     : testselect
*
*  Description : ?Description
*  Version:   0.5
*
  
*/

#include "tselect.h"

// CONSTANTS
const TUint KTestPort = 2080;

TInt CTestSelect::TestTimeout()
    {    
    
    // Create temporary variables in stack
    TInt timesecs;
    TInt timemicrosecs;
  	
    timemicrosecs = 0;
    timesecs = 10;
  	
    struct timeval tv;
    tv.tv_sec = timesecs;
    tv.tv_usec = timemicrosecs;
    
    time_t time1,time2;
    int err = time(&time1);
    
    int fd = select(1, NULL, NULL,NULL, &tv);  
    err = time(&time2);
    if ( ((time2 - time1) >= timesecs) && fd != -1 )
        {                    
        return KErrNone; 
        }
    else
        {       
        return KErrGeneral; 
        }        
    }
        
    
TInt CTestSelect::TestReadFileDesc()
    {
    
    TInt timesecs = 5;
    TInt timemicrosecs = 0;

    struct timeval tv;
    tv.tv_sec = timesecs;
    tv.tv_usec = timemicrosecs;    
    
    // read only
    int fd = open("c:\\tselect.cfg", O_RDONLY|O_CREAT);
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    int maxfd = fd + 1;
    int ret = select(maxfd, &readfds, NULL, NULL,&tv);    
    if ( ret != -1 && FD_ISSET(fd, &readfds))    
        {
        _LIT(KMsg1, "Read on file fd Test Passed");
        INFO_PRINTF1(KMsg1);
        return KErrNone; 
        }
    else
        {
        _LIT(KMsg1, "Read on file fd Test Failed");
        INFO_PRINTF1(KMsg1);
        return KErrGeneral; 
        }      
    }  
    
TInt CTestSelect::TestWriteFileDesc()
    {
    
    TInt timesecs = 2;
    TInt timemicrosecs = 0;	
    
    struct timeval tv;
    tv.tv_sec = timesecs;
    tv.tv_usec = timemicrosecs;    
        
    // write check        
    int fd = open("c:\\tselect.cfg", O_RDONLY);
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(fd, &writefds);
    int maxfd = fd + 1;
    int ret = select(maxfd, NULL,&writefds, NULL,&tv);    
    if ( ret != -1 && FD_ISSET(fd, &writefds))    
        {
        _LIT(KMsg1, "Write on file fd Test Passed");
        INFO_PRINTF1(KMsg1);
        return KErrNone; 
        }
    else
        {
        _LIT(KMsg1, "Write on file fd Test failed");
        INFO_PRINTF1(KMsg1);
        return KErrGeneral; 
        }    
    }
    
TInt CTestSelect::TestReadWriteFileDesc()
    {    
    // both read and write
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;    
    
    int fd = open("c:\\tselect.cfg", O_RDONLY);
    fd_set readfds;
    FD_ZERO(&readfds);        
    FD_SET(fd, &readfds);
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(fd, &writefds);
    int maxfd = fd + 1;
    int ret = select(maxfd, &readfds, &writefds, NULL,&tv);    
    if ( ret != -1 && FD_ISSET(fd, &readfds) && FD_ISSET(fd, &writefds) )    
        {
        _LIT(KMsg1, "R/W on file fd Test passed");
        INFO_PRINTF1(KMsg1);       
        return KErrNone; 
        }
    else
        {
        _LIT(KMsg1, "R/W on file fd Test failed");
        INFO_PRINTF1(KMsg1);
        return KErrGeneral; 
        }
    }	     
   


TInt CTestSelect::TestPipeReadDesc()
    {   

    int fd[2];		  
    INFO_PRINTF1(_L("Before Pipe "));   
    if ( pipe(fd) < 0 )
        {
        return -1;
        }          

    char a = 's';
    write(fd[1],&a,1);
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fd[0], &readfds);                     
    int ret = select(fd[0] +1, &readfds, NULL, NULL, NULL );    
    if ( ret != -1 && FD_ISSET(fd[0], &readfds))    
        {        
        _LIT(KMsg1, "Read on pipe fd Test passed");
        INFO_PRINTF1(KMsg1);                 
        ret = KErrNone; 
        }
    else
        {
        _LIT(KMsg1, "Read on pipe fd Test failed");
        INFO_PRINTF1(KMsg1);   
        ret = KErrGeneral; 
        }                
    close(fd[0]);
    close(fd[1]);
    return ret;
    
    }

//Test case added to check when write end of a pipe is closed 
TInt CTestSelect::TestPipeReadDesc1()
	{
    int fd[2];		  
    INFO_PRINTF1(_L("Before Pipe "));   
    if ( pipe(fd) < 0 )
        {
        return -1;
        }          

    char a = 's';
    write(fd[1],&a,0);
    fd_set readfds,exceptfds;
    FD_ZERO(&readfds);
    FD_ZERO(&exceptfds);
    FD_SET(fd[0], &readfds); 
    FD_SET(fd[0], &exceptfds);
    FD_SET(fd[1], &exceptfds);
    close(fd[1]);
    int ret = select(fd[0] +1, &readfds, NULL, &exceptfds, NULL );    
    if ( ret != -1 && FD_ISSET(fd[0], &exceptfds))    
        {        
        _LIT(KMsg1, "Read on pipe fd Test passed and passed to set EAnyException on write end of a pipe being closed\n");
        INFO_PRINTF1(KMsg1);                 
        ret = KErrNone; 
        }
    else
        {
        _LIT(KMsg1, "Failed to set EAnyException on write end being closed\n");
        INFO_PRINTF1(KMsg1);   
        ret = KErrGeneral; 
        }                
    close(fd[0]);
    return ret;
	}

   
TInt CTestSelect::TestPipeWriteDesc()
    {       
    int fd[2];		  
    INFO_PRINTF1(_L("Before Pipe "));   
    if ( pipe(fd) < 0 )
        {
        return -1;
        } 
        
    INFO_PRINTF1(_L("Pipe Created"));               
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(fd[1], &writefds);                     
    int ret = select(fd[1] +1, NULL, &writefds, NULL, NULL );    
    iSelectflag = 1;
    
    if ( ret != -1 && FD_ISSET(fd[1], &writefds))    
        {
        _LIT(KMsg1, "Write on pipe fd Test passed");
        INFO_PRINTF1(KMsg1);               
        ret = KErrNone; 
        }
    else
        {
        _LIT(KMsg1, "Write on pipe fd Test failed");
        INFO_PRINTF1(KMsg1);  
        ret = KErrGeneral; 
        }                 
        
    close(fd[0]);
    close(fd[1]);
    
    return ret;
    }  

void* CTestSelect::ServerThread(TAny* ptr)
    {
    CTestSelect* thisptr = (CTestSelect*)ptr;
    int sock_fd,newsock_fd;	
    unsigned int addr_len;
    sockaddr_in serv_addr,new_socket;

    sock_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (sock_fd < 0)
        {		
	return NULL;//KErrGeneral;
        }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(KTestPort);	

    if (bind(sock_fd,(sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
        {
        shutdown(sock_fd,SHUT_RDWR); // 2 -> SHUT_RDWT
        close(sock_fd);
        return NULL;//KErrBind;
        }
    
    if (listen(sock_fd,1) < 0)
        {
        shutdown(sock_fd,SHUT_RDWR); // 2 -> SHUT_RDWT
        close(sock_fd);
        return NULL;//KErrListen;
        }
    
    addr_len = sizeof(new_socket);
    thisptr->iAcceptflag = 1;
	
    newsock_fd = accept(sock_fd,(sockaddr*)&new_socket,&addr_len); // Code blocks here
    char a = 'S';
    write(newsock_fd, &a, 1);
    thisptr->iWriteflag = 1;
	
    while(!thisptr->iSelectflag)
        {
	usleep(10000);  
	}
    close(sock_fd);
	close(newsock_fd);
    return NULL;//KErrNone;	
    }
	
TInt CTestSelect::TestSocketDesc()
    {    
	struct timeval tv;
    struct sockaddr_in testaddr;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    memset( &testaddr,0, sizeof( testaddr));       
       // now connect to the server
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    INFO_PRINTF1(_L("socket in client called"));
    
    pthread_t testThread;
    pthread_create(&testThread, NULL, &ServerThread, (void*)this);   
    
    testaddr.sin_family = AF_INET;
    testaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);	
    testaddr.sin_port = htons(KTestPort);
    while ( !iAcceptflag )
        {
        usleep(10000);    
        }    
        
    INFO_PRINTF1(_L("connect called"));        

    TInt err=connect(fd,(struct sockaddr*)&testaddr, sizeof(testaddr));    
       
    fd_set readfds,writefds;
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_SET(fd, &readfds);
    FD_SET(fd, &writefds);
    int maxfd = fd + 1;
    while ( !iWriteflag )
        {
        usleep(10000);
        }
        
    INFO_PRINTF1(_L("before select "));   
          
    int ret = select(maxfd, &readfds, NULL, NULL,&tv);    
  
    INFO_PRINTF1(_L("after select"));  
    iSelectflag = 1;    
    if ( ret != -1 && FD_ISSET(fd, &readfds))    
        {
        ret = KErrNone; 
        }
    else
        {
        ret = KErrGeneral; 
        }     
        
    close(fd);
   	int *p;
   	pthread_join(testThread,(void**)&p);
    return ret;                 
    }  
    
 //Test case added for select not hanging for zero timeout- DEF122924
TInt CTestSelect::TestSocketDesc2()
    {    
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    INFO_PRINTF1(_L("socket in client called"));
        
    fd_set readfds,writefds,errfds;
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&errfds);
    FD_SET(fd, &readfds);
    int maxfd = fd + 1;
    INFO_PRINTF1(_L("before select "));   
    int ret = select(maxfd, &readfds, &writefds, &errfds,&tv);    
    INFO_PRINTF1(_L("select passes, does not hang."));         
    close(fd);
    return ret;                 
    }  
	    
TInt CTestSelect::TestMultipleDesc()
    {
    
    return KErrNone;
    
    } 

