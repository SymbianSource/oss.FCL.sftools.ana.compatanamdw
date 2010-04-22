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


#include "tmulticastclient.h"


#define MSGBUFSIZE 4096
#define MULTICAST_PORT 5000
#define MULTICAST_GROUP "224.0.10.110"

TInt CTestMulticastClient::TestClient()
    {
  	struct sockaddr_in addr;
	unsigned int addrlen;
	int fd, nbytes=0;
	int err = 0,ret = KErrNone;
	int onOff=1,ttl = 3;
	unsigned int ttllen = sizeof(ttl);
	int option = 1;
	int counter  = 0;   
	struct ip_mreq mreq;
	char msgbuf[MSGBUFSIZE];
	
	
	/* create what looks like an ordinary UDP socket */
	if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) 
		{
	  	perror("socket");
	  	sleep(3);
	  	INFO_PRINTF1(_L("Socket creation failed"));
	  	}
	
	 err = setsockopt(fd,SOL_SOCKET, SO_REUSEADDR,(char *)&onOff, sizeof( onOff ));
	 if (err != 0)
	 	{
	  	INFO_PRINTF1(_L("SO_REUSEADDR not supported!\n"));
	 	}

	 memset((void *)&addr,0,sizeof(struct sockaddr_in));
	 addr.sin_family=AF_INET;
	 addr.sin_addr.s_addr = htonl(INADDR_ANY); /* differs from sender */
	 						
	 addr.sin_port=htons(MULTICAST_PORT);
	 
	 
	 /* bind to receive address */
	 if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) 
	 	{
	  	perror("bind");
	  	sleep(3);	  
	  	INFO_PRINTF1(_L("Socket binding failed"));
	  	return KErrGeneral;
	 	} 
	 else 
	 	{
	 	INFO_PRINTF1(_L("socket bound and waiting..."));
	 	}
	 	
	 /* use setsockopt() to request that the kernel join a multicast group */
	 memset( ( void * )&mreq, 0, sizeof( struct ip_mreq ) );
	 mreq.imr_interface.s_addr = htonl( INADDR_ANY );
	 mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
	
	 
	 if ((err = setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char *)&mreq,sizeof(struct ip_mreq))) < 0) 
	 	{
	   	perror("setsockopt");
	   	INFO_PRINTF1(_L("The new P.I.P.S socket can not support Multicast!!!"));
	   	sleep(3);
	   	return KErrGeneral;
	 	}
	 INFO_PRINTF1(_L("Now the new P.I.P.S socket has joined the multicast group.."));
 
	 ret = setsockopt( fd, IPPROTO_IP,IP_MULTICAST_TTL, &ttl, sizeof( ttl ) );
	 if (ret != 0) 
	 	{
        INFO_PRINTF1(_L("SO_REUSEADDR not supported!"));
        sleep(3);
	 	}
	
	 ret = getsockopt(fd, IPPROTO_IP, IP_MULTICAST_TTL, ( void * )&ttl, &ttllen );
	 if(ret != 0)
	 	{
	 	INFO_PRINTF1(_L("Getting the IP_MULTICAST_TTL option Failed!"));
	 	sleep(3);
	 	}
	 
	 INFO_PRINTF1(_L("Setsockopt SO_BROADCAST"));
	 
	 if( setsockopt( fd, SOL_SOCKET, SO_BROADCAST,( char * )&option, sizeof( option ) ) != 0 ) 
	 	{
	 	close(fd);
	    INFO_PRINTF1(_L("SO_BROADCAST not supported!"));
	    sleep(3);
	    return KErrGeneral;
	 	}
	
	 /* now just enter a read-print loop */
	 while (1) 
	 	{
	   	addrlen=sizeof(addr);
	   	INFO_PRINTF1(_L("waiting for msg.."));
	   	
	   	nbytes = recvfrom(fd, msgbuf, MSGBUFSIZE, 0, (struct sockaddr *)&addr,&addrlen);
	   	if ( nbytes < 0 ) 
	   		{
	        perror("recvfrom");
	 	    sleep(3);
	        return KErrGeneral;
	   		}
	   	msgbuf[nbytes] = '\0';
	   	INFO_PRINTF1(_L("Msg recvd\n"));
	   	counter++;
	   	
	   	if (counter >= 10) 
	   		{
		 	setsockopt(fd, IPPROTO_IP, IP_DROP_MEMBERSHIP,
			(char *)&mreq,sizeof(struct ip_mreq));
		   	INFO_PRINTF1(_L("dropped from multicast group......"));
		   	return 0;
	   		}
	   	INFO_PRINTF2(_L("%d msgs received"), counter);
	   	
 		}
	 
	}
	
		
