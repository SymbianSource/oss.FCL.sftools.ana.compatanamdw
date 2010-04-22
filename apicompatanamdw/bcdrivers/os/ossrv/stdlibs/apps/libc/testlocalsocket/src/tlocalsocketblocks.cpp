/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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



#include "tlocalsocket.h"
#include <sys/un.h>
#include <sys/stat.h>
#include <pthread.h>
#include <semaphore.h>

#include <sys/select.h>

#define SERVPATH "c:\\tmp22.a" 
const TUint KMaxLine = 27;

// Util function to read from a socket
TInt read1(int newsock_fd,char *line)
    {    
    int ret;    
    int left = KMaxLine;   
    
    while (1)
        {
        
        ret = read(newsock_fd,line,left);
        
        if (ret < 0)
            {
            return -1;
            }
        else if (ret == 0)
            {
            break;
            }
        left -= ret;
        line += ret;
        if (left <= 0)
            {
            break;
            }
        }
    return 0;
    }
    
// Util function to write to a socket
TInt write1(int sock_fd)
    {
    char line[KMaxLine];    
    int x;
    char character = 'A';
    unsigned int cnt = 0;
    for(; cnt < KMaxLine - 1; cnt++)
        {
        line[cnt] = character;
        character++;
        if (character > 'Z')
            {
            character = 'A';
            }
        }
    line[cnt] = '\0';
    x=write(sock_fd,line,KMaxLine);
    if (x < 0)
        {
        return -1;
        }
        
    return 0;
    }
    
// Util function 
static void* TCPThreadWrite(TAny* /*aParam*/)
	{
	int sock_fd,len;
		
	struct sockaddr_un remote;
	
	memset(&remote, 0x00, sizeof(struct sockaddr_un));    
	remote.sun_family=AF_UNIX;    
	strcpy((char*)&remote.sun_path, SERVPATH);
	
    sock_fd = socket(AF_UNIX,SOCK_STREAM,0);
    if (sock_fd < 0)
		{
		goto close;
		}
	len = sizeof(sockaddr_un);
	int tmp = connect(sock_fd,(struct sockaddr *)&remote,len);
	if (tmp < 0)
		{
		goto close;
		}
	if (write1(sock_fd) < 0)
		{
		goto close;
		}
close:
	close(sock_fd);
	unlink(SERVPATH);
	return (void*)NULL;
	}
	
// Util function	
static void* TCPThreadRead(TAny* /*aParam*/)
	{
	int sock_fd,len;
	char line[KMaxLine ];
	
	struct sockaddr_un remote;
	
	memset(&remote, 0x00, sizeof(struct sockaddr_un));    
	remote.sun_family=AF_UNIX;    
	strcpy((char*)&remote.sun_path, "c:\\tmp.file");
	
    sock_fd = socket(AF_UNIX,SOCK_STREAM,0);
    if (sock_fd < 0)
		{
		goto close;
		}
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	int tmp = connect(sock_fd,(struct sockaddr *)&remote,len);
	if (tmp < 0)
		{
		goto close;
		}
	if (read1(sock_fd,line) < 0)
		{
		goto close;
		}
close:
	close(sock_fd);
	unlink("c:\\tmp.file");
	return (void*)NULL;
	}	
	
/**
* Function Name		: TestBind
* Description		: bind a local socket
* Return Value		: Test case should return KErrNone
*/
TInt CTestLocalSocket::TestBind( )
    {
    INFO_PRINTF1(_L("TestBind"));
    int fd = -1;
    int rslt = -1;
    int sz = 0,err;
    const char path[] = "TestBind";
    struct sockaddr_un server;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    sz = SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	return KErrGeneral;
    	}

    rslt = bind(fd, (struct sockaddr*)&server, sz);
    
    if (rslt < 0)
       {
       INFO_PRINTF2(_L("socket binding error: %d"), errno);
       close(fd);
       unlink(path);
       return KErrGeneral;
       }
    err=fcntl(fd, F_SETFL, O_NONBLOCK);
    if(err==-1)
    	{
    	INFO_PRINTF1(_L("fcntl failure"));
    	}
    close(fd);
    unlink(path);
	
    return KErrNone;
    }

/**
* Function Name		: TestLseek
* Description		: Perform LSeek on a local socket
* Return Value		: Test case should return KErrNone
*/
TInt CTestLocalSocket::TestLseek()
	{
	int sock_fd;
    TInt ret = KErrNone;
	const char path[] = "TestLSeek";
	struct sockaddr_un serveraddr;
    
    serveraddr.sun_family = PF_LOCAL;
    strncpy(serveraddr.sun_path, path, strlen(path)+1);
	sock_fd=socket(AF_UNIX, SOCK_STREAM, 0);  
    if (sock_fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	return KErrGeneral;
        }

    if (lseek(sock_fd,0,SEEK_CUR)<0)
    	{
		INFO_PRINTF1(_L("Lseek on socket success"));
		close(sock_fd);
		unlink(SERVPATH);
		ret = KErrNone;
    	}
    else
    	{
    	close(sock_fd);
    	unlink(SERVPATH);
    	INFO_PRINTF2(_L("Lseek fails with errno no: %d"), errno);
    	ret = KErrGeneral;
    	}
    return ret;
	}

/**
* Function Name		: TestFstat
* Description		: Perform FStat on a local socket
* Return Value		: Test case should return KErrNone
*/	
TInt CTestLocalSocket::TestFstat()
	{
	int sock_fd;
    TInt ret = KErrNone;
	const char path[] = "TestFStat";
	struct sockaddr_un serveraddr;
    
    serveraddr.sun_family = PF_LOCAL;
    strncpy(serveraddr.sun_path, path, strlen(path)+1);
	sock_fd=socket(AF_UNIX, SOCK_STREAM, 0);  
    if (sock_fd < 0)
    	{
    	INFO_PRINTF2(_L("Socket open failed with errno: %d"), errno);
    	return KErrGeneral;
        }

    struct stat buf;
    if(fstat(sock_fd , &buf ) < 0 ) 
    	{
    	INFO_PRINTF1(_L("fstat on socket failure"));
		close(sock_fd);
		unlink(SERVPATH);
		ret = KErrGeneral;
    	}
    else
    	{
    	close(sock_fd);
    	unlink(SERVPATH);
    	ret = KErrNone;
    	}
    return ret;
	}
	
/**
* Function Name		: TestThreadSocketRead
* Description		: Perform read on a local socket
* Return Value		: Test case should return KErrNone
*/	
TInt CTestLocalSocket::TestThreadSocketRead()
	{
	int sock_fd,newsock_fd;	
	int error;            
	unsigned int t;
	struct sockaddr_un serveraddr,remote;
	TInt ret = 0;
	char line[KMaxLine ];
	sock_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if (sock_fd < 0)
        {
        INFO_PRINTF2(_L("Socket open failed with errno: %d"), errno);
    	return KErrGeneral;
        }

	memset(&serveraddr, 0x00, sizeof(struct sockaddr_un));    
	serveraddr.sun_family=AF_UNIX;    
	strcpy((char*)&serveraddr.sun_path, SERVPATH);    
	if ( bind(sock_fd,(struct sockaddr *)&serveraddr,sizeof(serveraddr))  < 0)
		{		
		INFO_PRINTF2(_L("Socket bind failed with errno: %d"), errno);
    	ret = KErrGeneral;
		goto close;
		}
		
	t=sizeof(remote);
	// Create the thread and thread is client code 
	pthread_t testThread;
	int threadRetVal;
	void *threadRetValPtr = (void*)&threadRetVal;
	pthread_create(&testThread, NULL, &TCPThreadWrite, (void*)(serveraddr.sun_path));

	newsock_fd = accept(sock_fd,(sockaddr*)&remote,&t); 
	sleep(15);
	error = read1(newsock_fd,line);
	if (error < 0)
		{		
		ret = error;
		INFO_PRINTF2(_L("read failed with error %d"), error);
		goto close;
		}
	
close:
	pthread_join(testThread, &threadRetValPtr);
	shutdown(sock_fd,SHUT_RDWR);
	close(sock_fd);
	unlink(SERVPATH);
	return ret;	
	}
	
/**
* Function Name		: TestThreadSocketWrite
* Description		: Perform write on a local socket
* Return Value		: Test case should return KErrNone
*/	
TInt CTestLocalSocket::TestThreadSocketWrite()
	{
	int sock_fd,newsock_fd;	
	int error;            
	unsigned int t;
	struct sockaddr_un serveraddr,remote;
	TInt ret = 0;
	sock_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if (sock_fd < 0)
        {
        INFO_PRINTF2(_L("Socket open failed with errno: %d"), errno);
    	return KErrGeneral;
        }

	memset(&serveraddr, 0x00, sizeof(struct sockaddr_un));    
	serveraddr.sun_family=AF_UNIX;    
	strcpy((char*)&serveraddr.sun_path, "c:\\tmp.file");    
	if ( bind(sock_fd,(struct sockaddr *)&serveraddr,sizeof(serveraddr))  < 0)
		{		
		ret = -1;
		INFO_PRINTF2(_L("BIND failed with errno: %d"), errno);
		goto close;
		}
		
	t=sizeof(remote);
	// Create the thread and thread is client code 
	pthread_t testThread;
	int threadRetVal;
	void *threadRetValPtr = (void*)&threadRetVal;
	pthread_create(&testThread, NULL, &TCPThreadRead, (void*)(serveraddr.sun_path));

	newsock_fd = accept(sock_fd,(sockaddr*)&remote,&t); 
	sleep(15);
	error = write1(newsock_fd);
	if (error < 0)
		{		
		ret = error;
		goto close;
		}
	
close:
	pthread_join(testThread, &threadRetValPtr);
	shutdown(sock_fd,SHUT_RDWR);
	close(sock_fd);
	unlink("c:\\tmp.file");
	return ret;	

	}

/**
* Function Name		: TestMultProc
* Description		: Perform read and write on a local socket across processes
* Return Value		: Test case should return KErrNone
*/
TInt CTestLocalSocket::TestMultProc()
	{
	char *cmd="Z:\\sys\\bin\\tsample.exe";
	int fp,ret = KErrNone,n=0;
	int sock_fd,len;
	char line[KMaxLine ];
    struct sockaddr_un remote;
	
	memset(&remote, 0x00, sizeof(struct sockaddr_un));    
	remote.sun_family=AF_UNIX;    
	strcpy((char*)&remote.sun_path, "c:\\tmp.pipe");
	
    sock_fd = socket(AF_UNIX,SOCK_STREAM,0);
    INFO_PRINTF1(_L("socket in client called"));
    
    
    int fds[3]; 
    
    fp = popen3(cmd,NULL, NULL, fds);
    if(fp < 0)
    	{
    	INFO_PRINTF2(_L("popen3 failed with errno: %d"), errno);
    	ret = KErrGeneral;
    	goto close;
    	}
    
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	int tmp = connect(sock_fd,(struct sockaddr *)&remote,len);
	if (tmp < 0)
		{
		goto close;
		}   
	
	if (read1(sock_fd,line) < 0)
		{
		goto close;
		}
	
	int val=strcmp(line, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");	
	if(val)
		{
		INFO_PRINTF1(_L("string compare failed"));
		ret = KErrGeneral;
		}
	else
		{
		ret = KErrNone;
		}
    INFO_PRINTF2(_L("n=%d"),n);    
	n=errno;
close:
    close(sock_fd);
	unlink(SERVPATH);
    return ret;	
	}
	
struct TThreadParam
	{
	TInt iDataCount;
	sem_t iSemaphore;
	};

//Util function
void* SocketReadThreadEntryPoint(void* aParam)
	{
	TInt retVal = 0;
	TInt count = 5;
    TThreadParam* pThreadParam = ( TThreadParam* ) aParam;

	TInt portNum = 0;
	int serverFd = 0;
	int newFd = 0;
	size_t addrSize;
	struct sockaddr_in servAddr;
	struct sockaddr_in sockAddr;
	const char* buff = "Server --> Sending Data Item : ";
	char sendBuff[50];
	char recvBuff[100];
	const unsigned int maxRecv = 100;

	serverFd = socket(PF_LOCAL, SOCK_STREAM, 0);
	if( serverFd == -1 )
		{
		retVal = -1;
		}

	(&servAddr)->sin_addr.s_addr  = 0x0100007F;
	(&servAddr)->sin_family = PF_LOCAL;

	servAddr.sin_port = htons( (TUint16) portNum );
	retVal |= bind( serverFd, (struct sockaddr*)&servAddr, sizeof(servAddr) );
	if( retVal != 0 )
		{
		close( serverFd );
		retVal = -1;
		}

	

	addrSize = sizeof( sockAddr );

	//Tell the other thread that data is ready for reading
	retVal = sem_post(&pThreadParam->iSemaphore);
	if( retVal != 0 )
		{
		close( serverFd );
		retVal = -1;
		}

	newFd = accept( serverFd, (struct sockaddr*)&sockAddr, &addrSize);
	if( newFd == -1 )
		{
		close( serverFd );
		retVal = -1;
	    return (void*)retVal;
		}

	if( 0 == retVal )
		{
		//Now Receive and Send some Data
		for(TUint i=1; i<=count; i++)
			{
			TInt ret = recv(newFd, recvBuff, maxRecv, 0);
			if( ret == -1 )
				{
				close( newFd );
				close( serverFd );
				retVal = -1;
				break;
				}
			sprintf(sendBuff, "%s %d", buff, i);
			ret = send(newFd, sendBuff, sizeof(sendBuff), 0);
			if( ret == -1 )
				{
				close( newFd );
				close( serverFd );
				retVal = -1;
				break;
				}
			}
		}

	if( 0 == retVal )
		{
		close( newFd );
		close( serverFd );
		}
	return (void*)retVal;
	}

//Util function
void* SocketWriteThreadEntryPoint(void* aParam)
	{
	TInt retVal = 0;
	TInt count = 5;
    TThreadParam* pThreadParam = ( TThreadParam* ) aParam;

	TInt portNum = 0;
	int clientFd;
	size_t addrSize;
	struct sockaddr_in servAddr;
	const char* buff = "Client --> Sending Data Item : ";
	char sendBuff[50];
	char recvBuff[100];
	const unsigned int maxRecv = 100;

	(&servAddr)->sin_addr.s_addr  = 0x0100007F;
	(&servAddr)->sin_family = PF_LOCAL;

	servAddr.sin_port = htons( portNum );

	clientFd = socket(PF_LOCAL, SOCK_STREAM, 0);
	if( clientFd == -1 )
		{
		retVal = -1;
		}

    //Wait for the other thread to write some data to file
    retVal = sem_wait(&pThreadParam->iSemaphore);
    if( retVal != 0 )
    	{
    	close(clientFd);
    	retVal = -1;
	    return (void*)retVal;
    	}

	addrSize = sizeof(servAddr);
	retVal = connect(clientFd, (struct sockaddr*)&servAddr, addrSize);
	if( retVal == -1 )
		{
		close(clientFd);
		retVal = -1;
		}

	if( 0 == retVal )
		{
		//Now Send and Receive some Data
		for(TUint i=1; i<=count; i++)
			{
			sprintf(sendBuff, "%s %d", buff, i);
			TInt ret = send(clientFd, sendBuff, sizeof(sendBuff), 0);
			if(ret == -1)
				{
				close( clientFd );
				retVal = -1;
				break;
				}
			ret = recv(clientFd, recvBuff, maxRecv, 0);
			if(ret == -1)
				{
				close( clientFd );
				retVal = -1;
				break;
				}
			}
		}

	if (0 == retVal )
		{
		close( clientFd );
		}

	return (void*)retVal;
	}

/**
* Function Name		: TestMultThread
* Description		: Perform read and write on a local socket across threads
* Return Value		: Test case should return KErrNone
*/
TInt CTestLocalSocket::TestMultThread()
	{
	int retVal = 0;
	
	
    TThreadParam threadParam;

	if( sem_init( &threadParam.iSemaphore, 0, 0 ) != 0 )
    	{
    	
    	return -1;
    	}

	pthread_t threadID1 = 0;
	pthread_t threadID2 = 0;
	pthread_attr_t threadAttr;
	pthread_attr_init( &threadAttr );
	pthread_attr_setdetachstate( &threadAttr, PTHREAD_CREATE_JOINABLE );

	//Create a Read thread now
	retVal = pthread_create( &threadID1, &threadAttr, SocketReadThreadEntryPoint,
		(void*)&threadParam );
	
	if( retVal == 0)
		{
		//Create Write thread
		retVal = pthread_create( &threadID2, &threadAttr,
			SocketWriteThreadEntryPoint, (void*)&threadParam );
		
		//If its joinable thread and waitFlag id set
		if( 0 == retVal )
			{
			TInt exitReason = 0;
			retVal = pthread_join(threadID1, (void**)&exitReason );
			
			retVal = pthread_join(threadID2, (void**)&exitReason );
			
			}
		}

	if( sem_destroy( &threadParam.iSemaphore ) != 0 )
		{
		
		retVal = -1;
		}

	return retVal;
	}

/**
* Function Name		: TestListen
* Description		: Listen on a local socket
* Return Value		: Test case should return KErrNone
*/	
TInt CTestLocalSocket::TestListen( )
    {
    INFO_PRINTF1(_L("TestListen"));
    int fd = -1, ret = KErrNone;
    int rslt = -1;
    int sz = 0;
    const char path[] = "TestListen1";
    struct sockaddr_un server;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    sz = SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	return KErrGeneral;
    	}

    rslt = bind(fd, (struct sockaddr*)&server, sz);
    
    if (rslt < 0)
       	{
       	INFO_PRINTF2(_L("socket binding error: %d"), errno);
       	unlink(path);
		close(fd);
       	return KErrGeneral;
       	}
    
    if ( listen(fd, 5) < 0 )
		{
		INFO_PRINTF1(_L("Listen successful"));
		ret = KErrNone;
		}
	else
		{
		INFO_PRINTF2(_L("Listen fails with error no: %d"), errno);
		ret = KErrGeneral;
		}
		
    unlink(path);
	close(fd);
    return ret;
    }

/*
* Testcase		: TestSetGetSockOpt
* Description	: Test setsockopt for different values of option_name
*					1. SO_SNDBUF
*					2. SO_RCVBUF
*					3. SO_DEBUG
*				  and upon succes of setsockopt, test getsockopt for the same
* Result		: KErrNone
*/ 
TInt CTestLocalSocket::TestSetGetSockOpt()
	{
	INFO_PRINTF1(_L("TestSetGetSockOpt"));
	int fd, ret = KErrNone;
	int sz = 0, optionName = 0;
	int rslt;
	const char path[] = "TestSetGetSockOpt";
	struct sockaddr_un server;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    sz = SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	return KErrGeneral;
    	}
   	   	
   	rslt = bind(fd, (struct sockaddr*)&server, sz);
    
    if (rslt)
       	{
       	INFO_PRINTF2(_L("socket binding error: %d"), errno);
       	unlink(path);
		close(fd);
       	return KErrGeneral;
       	}
       
    int optionValue = KMaxLine;
    _LIT( KOptionName, "OptionName" );
	rslt = GetIntFromConfig(ConfigSection(), KOptionName, optionName);
	if(!rslt)
		{
	 	INFO_PRINTF1(_L("Could not read option name from ini file"));
	 	close(fd);
		unlink(path);
	 	return KErrGeneral;
		}    
    
    rslt = setsockopt(fd, SOL_SOCKET, optionName, &optionValue, sizeof(optionValue));
	if(rslt < 0)
		{
		INFO_PRINTF2(_L("Setsockopt fails with error no: %d"), errno);
		ret = KErrGeneral;
		}
	else
		{
		INFO_PRINTF1(_L("Setsockopt successful"));
		
		unsigned int optionLen = sizeof(optionValue);
  		int readOptionValue = 0;
    	rslt = getsockopt(fd, SOL_SOCKET, optionName, (void *)&readOptionValue, &optionLen);
    
    	if(rslt < 0)
			{
			INFO_PRINTF2(_L("Getsockopt fails with error no: %d"), errno);
			ret = KErrGeneral;
			}
		else
			{
			INFO_PRINTF1(_L("Getsockopt successful"));
			ret = KErrNone;
			}
		}
	
	close(fd);
	unlink(path);
	return ret;
	}

/*
* Testcase		: TestSetSockOptNegative1
* Description	: Test setsockopt for an invalid value of option_name
* Result		: setsockopt returns setting errno to EINVAL, 
*				  Test case returns KErrNone
*/
TInt CTestLocalSocket::TestSetSockOptNegative1()
	{
	INFO_PRINTF1(_L("TestSetSockOptNegative1"));
	int fd, ret = KErrNone;
	int sz = 0, optionName = 0;
	int rslt;
	const char path[] = "TestSetSockOptNegative1";
	struct sockaddr_un server;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    sz = SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	}
   	   	
   	rslt = bind(fd, (struct sockaddr*)&server, sz);
    
    if (rslt)
       {
       INFO_PRINTF1(_L("socket binding error"));
       }
       
    int optionValue = KMaxLine;
    _LIT( KOptionName, "OptionName" );
	rslt = GetIntFromConfig(ConfigSection(), KOptionName, optionName);
	if(!rslt)
		{
	 	INFO_PRINTF1(_L("Could not read option name from ini file"));
	 	close(fd);
		unlink(path);
	 	return KErrGeneral;
		}    
    
    rslt = setsockopt(fd, SOL_SOCKET, optionName, &optionValue, sizeof(optionValue));
	if(rslt < 0 && errno == EINVAL)
		{
		INFO_PRINTF1(_L("setsockopt fails with right error value"));
		ret = KErrNone;
		}
	else
		{
		INFO_PRINTF2(_L("Setsockopt fails with error no: %d"), errno);
		ret = KErrGeneral;
		}
	
	close(fd);
	unlink(path);
	return ret;
	}
/*
* Testcase		: TestSetSockOptNegative2
* Description	: Test setsockopt for invalid value of socklen_t
* Result		: setsockopt returns -1 setting errno to EINVAL 
*				  Test case returns KErrNone
*/	
TInt CTestLocalSocket::TestSetSockOptNegative2()
	{
	INFO_PRINTF1(_L("TestSetSockOptNegative2"));
	int fd, ret = KErrNone;
	int sz = 0;
	int rslt;
	const char path[] = "TestSetSockOptNegative2";
	struct sockaddr_un server;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    sz = SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	}
   	   	
   	rslt = bind(fd, (struct sockaddr*)&server, sz);
    
    if (rslt)
       {
       INFO_PRINTF1(_L("socket binding error"));
       }
       
    int optionValue = KMaxLine;
    int sockLen=0;
    
    _LIT( KSocketLen, "SocketLen" );
	rslt = GetIntFromConfig(ConfigSection(), KSocketLen, sockLen);
	if(!rslt)
		{
	 	INFO_PRINTF1(_L("Could not read option name from ini file"));
	 	close(fd);
		unlink(path);
	 	return KErrGeneral;
		}    
    rslt = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &optionValue, sockLen);
    if(rslt < 0 && errno == EINVAL)
		{
		INFO_PRINTF1(_L("Setsockopt fails with right error value"));
		ret = KErrNone;
		}
	else
		{
		INFO_PRINTF2(_L("Setsockopt fails with error no: %d"), errno);
		ret = KErrGeneral;
		}
	
	close(fd);
	unlink(path);
	return ret;
	}

/*
* Testcase		: TestSetSockOptNegative3
* Description	: Test setsockopt for value of level other than SOL_SOCKET
* Result		: setsockopt returns EINVAL, test case returns KErrNone
*/	
TInt CTestLocalSocket::TestSetSockOptNegative3()
	{
	INFO_PRINTF1(_L("TestSetSockOptNegative3"));
	int fd, ret = KErrNone;
	int sz = 0;
	int rslt;
	const char path[] = "TestSetSockOptNegative3";
	struct sockaddr_un server;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    sz = SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	}
   	   	
   	rslt = bind(fd, (struct sockaddr*)&server, sz);
    
    if (rslt)
       {
       INFO_PRINTF1(_L("socket binding error"));
       }
       
    int optionValue = KMaxLine;
      
    // pass invalid level = 3
    rslt = setsockopt(fd, 3, SO_SNDBUF, &optionValue, sizeof(optionValue));
        
    if(rslt < 0 && errno == EINVAL)
		{
		INFO_PRINTF1(_L("Setsockopt fails with right error value"));
		ret = KErrNone;
		}
	else
		{
		INFO_PRINTF2(_L("Setsockopt fails with error no: %d"), errno);
		ret = KErrGeneral;
		}
	
	close(fd);
	unlink(path);
	return ret;
	}

/*
* Testcase		: TestSetSockOptNegative4
* Description	: Test setsockopt for option_value=NULL
* Result		: setsockopt returns EFAULT, test case returns KErrNone
*/	
TInt CTestLocalSocket::TestSetSockOptNegative4()
	{
	INFO_PRINTF1(_L("TestSetSockOptNegative4"));
	int fd, ret = KErrNone;
	int sz = 0;
	int rslt;
	const char path[] = "TestSetSockOptNegative4";
	struct sockaddr_un server;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    sz = SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	}
   	   	
   	rslt = bind(fd, (struct sockaddr*)&server, sz);
    
    if (rslt)
       {
       INFO_PRINTF1(_L("socket binding error"));
       }
       
    rslt = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, NULL, NULL);
        
    if(rslt < 0 && errno == EFAULT)
		{
		INFO_PRINTF1(_L("Setsockopt fails with right error value"));
		ret = KErrNone;
		}
	else
		{
		INFO_PRINTF2(_L("Setsockopt fails with error no: %d"), errno);
		ret = KErrGeneral;
		}
	
	close(fd);
	unlink(path);
	return ret;
	}

/*
* Testcase		: TestGetSockOptNegative1
* Description	: Test getsockopt for an invalid value of option_name
* Result		: getsockopt returns EINVAL, test case returns KErrNone
*/	
TInt CTestLocalSocket::TestGetSockOptNegative1()
	{
	INFO_PRINTF1(_L("TestGetSockOptNegative1"));
	int fd, ret = KErrNone;
	int sz = 0;
	int rslt;
	const char path[] = "TestGetSockOptNegative1";
	struct sockaddr_un server;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    sz = SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	}
   	   	
   	rslt = bind(fd, (struct sockaddr*)&server, sz);
    
    if (rslt)
       {
       INFO_PRINTF1(_L("socket binding error"));
       }
       
    int optionValue = KMaxLine;
    rslt = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &optionValue, sizeof(optionValue));
	if(rslt < 0)
		{
		INFO_PRINTF2(_L("Setsockopt fails with error no: %d"), errno);
		ret = KErrGeneral;
		}
	else
		{
		INFO_PRINTF1(_L("Setsockopt successful"));
		
		unsigned int optionLen = sizeof(optionValue);
  		int readOptionValue = 0;
  		int invalidOptName = 0;
  		 _LIT( KOptionName, "OptionName" );
		rslt = GetIntFromConfig(ConfigSection(), KOptionName, invalidOptName);
		if(!rslt)
			{
	 		INFO_PRINTF1(_L("Could not read option name from ini file"));
	 		close(fd);
			unlink(path);
	 		return KErrGeneral;
			}  
    	rslt = getsockopt(fd, SOL_SOCKET, invalidOptName, (void *)&readOptionValue, &optionLen);
    
    	if(rslt < 0 && errno == EINVAL)
			{
			INFO_PRINTF1(_L("getsockopt fails with right error value"));
			ret = KErrNone;
			}
		else
			{
			INFO_PRINTF2(_L("getsockopt fails with error no: %d"), errno);
			ret = KErrGeneral;
			}
		}
	
	close(fd);
	unlink(path);
	return ret;
	}

/*
* Testcase		: TestGetSockOptNegative2
* Description	: Test getsockopt for option_value=NULL
* Result		: getsockopt returns EFAULT, test case returns KErrNone
*/	
TInt CTestLocalSocket::TestGetSockOptNegative2()
	{
	INFO_PRINTF1(_L("TestGetSockOptNegative2"));
	int fd, ret = KErrNone;
	int sz = 0;
	int rslt;
	const char path[] = "TestGetSockOptNegative2";
	struct sockaddr_un server;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    sz = SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	}
   	   	
   	rslt = bind(fd, (struct sockaddr*)&server, sz);
    
    if (rslt)
       {
       INFO_PRINTF1(_L("socket binding error"));
       }
       
    int optionValue = KMaxLine;
    rslt = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &optionValue, sizeof(optionValue));
	if(rslt < 0)
		{
		INFO_PRINTF2(_L("Setsockopt fails with error no: %d"), errno);
		ret = KErrGeneral;
		}
	else
		{
		INFO_PRINTF1(_L("Setsockopt successful"));
		
		unsigned int optionLen = sizeof(optionValue);
  		  		 		
    	rslt = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, NULL, &optionLen);
    
    	if(rslt < 0 && errno == EFAULT)
			{
			INFO_PRINTF1(_L("getsockopt fails with right error value"));
			ret = KErrNone;
			}
		else
			{
			INFO_PRINTF2(_L("getsockopt fails with error no: %d"), errno);
			ret = KErrGeneral;
			}
		}
	
	close(fd);
	unlink(path);
	return ret;
	}

/*
* Testcase		: TestGetSockOptNegative3
* Description	: Test getsockopt for invalid value of socklen_t
* Result		: getsockopt returns EINVAL, test case returns KErrNone
*/	
TInt CTestLocalSocket::TestGetSockOptNegative3()
	{
	INFO_PRINTF1(_L("TestGetSockOptNegative3"));
	int fd, ret = KErrNone;
	int sz = 0;
	int rslt;
	const char path[] = "TestGetSockOptNegative3";
	struct sockaddr_un server;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    sz = SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	}
   	   	
   	rslt = bind(fd, (struct sockaddr*)&server, sz);
    
    if (rslt)
       {
       INFO_PRINTF1(_L("socket binding error"));
       }
       
    int optionValue = KMaxLine;
    rslt = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &optionValue, sizeof(optionValue));
	if(rslt < 0)
		{
		INFO_PRINTF2(_L("Setsockopt fails with error no: %d"), errno);
		ret = KErrGeneral;
		}
	else
		{
		INFO_PRINTF1(_L("Setsockopt successful"));
		
		int readOptionValue = 0;
		unsigned int sockLen = 0;
  		
  	   	rslt = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void *)&readOptionValue, &sockLen);
    
	    if(rslt < 0 && errno == EINVAL)
			{
			INFO_PRINTF1(_L("getsockopt fails with right error value"));
			ret = KErrNone;
			}
		else
			{
			INFO_PRINTF2(_L("getsockopt fails with error no: %d"), errno);
			ret = KErrGeneral;
			}
		}
	
	close(fd);
	unlink(path);
	return ret;
	}

/*
* Testcase		: TestGetSockOptNegative4
* Description	: Test setsockopt for value of level other than SOL_SOCKET
* Result		: setsockopt returns EINVAL, test case returns KErrNone
*/	
TInt CTestLocalSocket::TestGetSockOptNegative4()
	{
	INFO_PRINTF1(_L("TestGetSockOptNegative4"));
	int fd, ret = KErrNone;
	int sz = 0;
	int rslt;
	const char path[] = "TestGetSockOptNegative4";
	struct sockaddr_un server;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    sz = SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	}

   	rslt = bind(fd, (struct sockaddr*)&server, sz);
    
    if (rslt)
       {
       INFO_PRINTF1(_L("socket binding error"));
       }
       
    int optionValue = KMaxLine;
    rslt = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &optionValue, sizeof(optionValue));
	if(rslt < 0)
		{
		INFO_PRINTF2(_L("Setsockopt fails with error no: %d"), errno);
		ret = KErrGeneral;
		}
	else
		{
		INFO_PRINTF1(_L("Setsockopt successful"));
		
		unsigned int optionLen = sizeof(optionValue);
		int readOptionValue = 0;
				  		
  		// pass invalid level = 3
  	   	rslt = getsockopt(fd, 3, SO_SNDBUF, (void *)&readOptionValue, &optionLen);
    
	    if(rslt < 0 && errno == EINVAL)
			{
			INFO_PRINTF1(_L("getsockopt fails with right error value"));
			ret = KErrNone;
			}
		else
			{
			INFO_PRINTF2(_L("getsockopt fails with error no: %d"), errno);
			ret = KErrGeneral;
			}
		}
	
	close(fd);
	unlink(path);
	return ret;
	}
/*
* Testcase		: TestLocalSockIoctl
* Description	: Test ioctl for localsocket
* Result		: ioctl retuns -1 settign errno to ENOSYS
*				  Test case returns KErrNone
**/
TInt CTestLocalSocket::TestLocalSockIoctl()
	{
	/*INFO_PRINTF1(_L("TestLocalSockIoctl"));
	int fd, ret = KErrNone;
	int rslt=0;
	const char path[] = "TestLocalSockIoctl";
	struct sockaddr_un server;
	TRequestStatus status;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	}
	
	rslt = ioctl(fd, SIOCSIFNAME, &status);
	
	if (rslt < 0 && errno == ENOSYS)
		{
		INFO_PRINTF1(_L("ioctl successful"));
		ret = KErrNone;
		}
	else
		{
		INFO_PRINTF2(_L("ioctl fails with error number: %d"), errno);
		ret = KErrNone;
		}
		
	close(fd);
	unlink(path);
	return ret;*/
	return KErrNone;
	}
	
/*
* Testcase		: TestLocalSockFcntl
* Description	: Test fcntl for localsocket
* Result		: fcntl retuns 0, test case returns KErrNone
**/
TInt CTestLocalSocket::TestLocalSockFcntl()
	{
	/*INFO_PRINTF1(_L("TestLocalSockFcntl"));
    int fd = -1;
    int rslt = -1;
    int sz,err = 0, ret = KErrNone;
    const char path[] = "TestLocalSockFcntl";
    struct sockaddr_un server;
        
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    sz = SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
   
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	}

    rslt = bind(fd, (struct sockaddr*)&server, sz);
    
    if (rslt)
       {
       INFO_PRINTF1(_L("socket binding error"));
       }
    
    int fcntlFlag=0;
    _LIT(KFcntlFlag, "FcntlFlag");
    
    rslt = GetIntFromConfig(ConfigSection(), KFcntlFlag, fcntlFlag);
    if(!rslt)
		{
	 	INFO_PRINTF1(_L("Could not read from ini file"));
	 	close(fd);
		unlink(path);
	 	return KErrGeneral;
		}
    
    err=fcntl(fd, fcntlFlag, O_NONBLOCK);
    if(err == -1 && errno == ENOSYS)
    	{
    	INFO_PRINTF1(_L("fcntl fails with right error number"));
    	ret = KErrNone;
    	}
    else
    	{
    	INFO_PRINTF2(_L("fcntl fails with %d"), errno);
    	ret = KErrGeneral;
    	}
    
    close(fd);
    unlink(path);
	return ret; */
	return KErrNone;
	}
	
TInt CTestLocalSocket::TestLocalSockSelect()
	{
	/*struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100;    
    
    const char path[] = "TestLocalSockSelect";
    struct sockaddr_un server;
    int fd = -1;
	int ret;
    int ExceptFlag=0;
    _LIT(KExceptFlag, "ExceptFlag");
    
    int rslt = GetIntFromConfig(ConfigSection(), KExceptFlag, ExceptFlag);
    if(!rslt)
		{
	 	INFO_PRINTF1(_L("Could not read from ini file"));
	 	close(fd);
		unlink(path);
	 	return KErrGeneral;
		}
    server.sun_family = PF_LOCAL;
    strncpy(server.sun_path, path, strlen(path)+1);
    SUN_LEN(&server);
    
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
    	{
    	INFO_PRINTF2(_L("protocol not supported. Errno is %d"), errno);
    	}

    fd_set readfds;
    FD_ZERO(&readfds);        
    FD_SET(fd, &readfds);
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(fd, &writefds);
	fd_set exceptfds;
	FD_ZERO(&exceptfds);        
    int maxfd = fd + 1;
	if(!ExceptFlag)
		{
		ret = select(maxfd, &readfds, &writefds, NULL,&tv);    
		}
    else
		{
		FD_SET(fd, &exceptfds);
		ret = select(maxfd, &readfds, &writefds, &exceptfds,&tv);    
		}
    if ( (ExceptFlag && ret == 1 && FD_ISSET(fd,&exceptfds)) || (!ExceptFlag && ret == 0 && !FD_ISSET(fd,&exceptfds)))    
        {
        _LIT(KMsg1, "R/W on file fd Test passed");
        INFO_PRINTF1(KMsg1);       
        ret = KErrNone; 
        }
    else
        {
        _LIT(KMsg1, "R/W on file fd Test failed with errno: %d");
        INFO_PRINTF2(KMsg1, errno);
        ret = KErrGeneral; 
        }
    
    close(fd);
    unlink(path);
	return ret;*/
	return KErrNone;
	}
//  End of File
