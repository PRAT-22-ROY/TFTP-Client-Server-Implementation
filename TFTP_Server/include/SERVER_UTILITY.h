/**********************************************************************************************
 **  FILENAME	      : SERVER_UTILITY.h	
 **:wq
 **  DESCRIPTION      : This file defines macros and header files for source.c 
 ** 
 **
 **  REVISION HISTORY :
 **  
 **  DATE	    NAME		   REFERENCE	    REASON
 **  ------------------------------------------------------------------------------------
 **  29 Mar 2022    
 **
 **
 **  Copyright @ 2022 Capgemini Engineering All Rights Reserved
 **
 ********************************************************************************************/
/***************************************
 * 		INCLUDES
 **************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>



#define MYPORT "4950" // port to be opened on server
#define SERVERPORT "4950" // the port users will be connecting to
#define MAXBUFLEN 550 // get sockaddr, IPv4 or IPv6:
#define MAX_READ_LEN 512 // maximum data size that can be sent on one packet
#define MAX_FILENAME_LEN 100 // maximum length of file name supported
#define MAX_PACKETS 99 // maximum number of file packets
#define MAX_TRIES 3 // maximum number of tries if packet times out
#define TIME_OUT 5 // in seconds

/*******************************************************************
 **  FUNCTION NAME	: 
 **
 **  DESCRIPTION	: 
 **
 **  PARAMETERS		:  
 			  
 **
 **  RETURN 		: 
 **
 ******************************************************************/
int readRequest(int, char *, struct sockaddr_storage, socklen_t, int, struct addrinfo *, char []);
int writeRequest(int ,char *, struct sockaddr_storage, socklen_t, int, char []);

