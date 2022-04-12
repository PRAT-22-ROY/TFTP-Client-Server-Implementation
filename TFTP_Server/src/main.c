
/**********************************************************************************************
 **  FILENAME	      : main.c	
 **
 **  DESCRIPTION      : 
 ** 
 **
 **  REVISION HISTORY :
 **  
 **  DATE	    NAME	      REFERENCE	                REASON
 **  ------------------------------------------------------------------------------------
 **  04 April 2022    
 **
 **
 **  Copyright @ 2022 Capgemini Engineering All Rights Reserved
 **
 ********************************************************************************************/

/***************************************
 * 		INCLUDES
 **************************************/
#include "server_utility.h"

int sockfd;


static char *LOGFILE = "../logs/request.log";

/*******************************************************************
 **  FUNCTION NAME	: main 
 **
 **  DESCRIPTION	: 
 **
 **  PARAMETERS		: 
 **
 **  RETURN 		: 
 **
 ******************************************************************/

int main(void)
{
	struct addrinfo hints, *servinfo, *res;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;
	char buf[MAXBUFLEN];
	socklen_t addr_len;
	char dst[INET6_ADDRSTRLEN];
	
	signal(SIGINT,signalHandler);

	/* Configuration of server starts */
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; 
	
	if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) 
	{
		logger("Server: getaddrinfo",'f',__func__,__LINE__);
		fprintf(stderr, "SERVER: getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	/* Loop through all the results and binding to the first */
	for(res = servinfo; res != NULL; res = res->ai_next) 
	{
		if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) 
		{
			logger("Server: socket",'w',__func__,__LINE__);
			perror("SERVER: socket");
			continue;
		}
		if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) 
		{
			logger("Server: socket",'w',__func__,__LINE__);
			close(sockfd);
			perror("SERVER: bind");
			continue;
		}
		break;
	}
	if (res == NULL) 
	{
		logger("Server: failed to bind",'f',__func__,__LINE__);
		fprintf(stderr, "SERVER: failed to bind socket\n");
		return 2;
	}
	freeaddrinfo(servinfo);
	logOpen(LOGFILE);
	
	printf("SERVER: waiting to recvfrom...\n");
	/* Configuration of server ends */
	

	/* Main implementation starts */
	/* Waiting for the first request from client - RRQ/WRQ */
	/* Iterative server implementation */
	while(1)
	{
		memset(&their_addr,0,sizeof(their_addr));
		addr_len = sizeof their_addr;
		if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) 
		{
			logger("Server: recvfrom",'f',__func__,__LINE__);
			errorHandler(numbytes,"SERVER: recvfrom");
		}
		logger("Server got the packet",'i',__func__,__LINE__);
		printf("SERVER: got packet from %s\n", inet_ntop(their_addr.ss_family, getAddress((struct sockaddr *)&their_addr), dst, sizeof dst));
		printf("SERVER: packet is %d bytes long\n", numbytes);
		buf[numbytes] = '\0';
		printf("SERVER: packet contains \"%s\"\n", buf);
		
		/* Read request */
		logger("Server: Read request",'d',__func__,__LINE__);
		if(buf[0] == '0' && buf[1] == '1')
		{
			rv=readRequest(sockfd, buf, their_addr, addr_len, res);
			logMessage("Server received READ REQUEST(RRQ) from %s \n",inet_ntop(their_addr.ss_family, getAddress((struct sockaddr *)&their_addr), dst, sizeof dst));
			if(rv==EXIT_FAILURE)
			{
				logger("Server: Read request unsuccesful",'w',__func__,__LINE__);
				fprintf(stderr,"READ REQUEST UNSUCCESSFUL\n");
			}	
		}
		/* Write request */	
		else if (buf[0] == '0' && buf[1] == '2')
		{
			logger("Server: Write request",'d',__func__,__LINE__);
			rv=writeRequest(sockfd, buf, their_addr, addr_len);
			logMessage("Server received WRITE REQUEST(WRQ) from %s \n",inet_ntop(their_addr.ss_family, getAddress((struct sockaddr *)&their_addr), dst, sizeof dst));
			if(rv==EXIT_FAILURE)
			{
				logger("Server: Write request unsuccesful",'w',__func__,__LINE__);
				fprintf(stderr,"WRITE REQUEST UNSUCCESSFUL\n");
			}
		} 
		else 
		{
			fprintf(stderr,"INVALID REQUEST\n");
			logMessage("Server received an invalid request from %s \n",inet_ntop(their_addr.ss_family, getAddress((struct sockaddr *)&their_addr), dst, sizeof dst));
			logger("Server: Invalid request",'f',__func__,__LINE__);
		}
	}
	/* Main implementation ends */
	return 0;
}


/******************************************************************************
 **  FUNCTION NAME	: signalHandler 
 **
 **  DESCRIPTION	: Handles CTRL+c signal and stops the server program
 **
 **  PARAMETERS		: sig
 **
 **  RETURN 		: void
 **
 *****************************************************************************/

void signalHandler(int sig)
{
	if(sig==SIGINT)
	{
		printf("\n---------SERVER PROGRAM STOPPED--------\nCtrl+c called\n");
		logClose();
		close(sockfd);
		exit(EXIT_SUCCESS);
	}
}		
