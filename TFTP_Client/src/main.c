/**********************************************************************************************
 **  FILENAME	      : main.c	
 **
 **  DESCRIPTION      : entry point to the client program. 
 ** 
 **
 **  REVISION HISTORY :
 **  
 **  DATE	    NAME	      REFERENCE	                REASON
 **  ------------------------------------------------------------------------------------
 **  04 April 2022    Sprint_Group_5    TFTP_01,TFTP01      Sprint Assessment
 **
 **
 **  Copyright @ 2022 Capgemini Engineering All Rights Reserved
 **
 ********************************************************************************************/

/***************************************
 * 		INCLUDES
 **************************************/

#include "client_utility.h"


/*******************************************************************
 **  FUNCTION NAME	: main
 **
 **  DESCRIPTION	: performs client configuration and calls readFile or writeFile based on the users input.
 **
 **  PARAMETERS		: int argc, char *argv[]
 **
 **  RETURN 		: returns 0
 **
 ******************************************************************/
int main(int argc, char* argv[])
{
	int sockfd;
	struct addrinfo hints, *servinfo, *res;
	int rv;
	struct sockaddr_storage their_addr;
	
	their_addr.ss_family = AF_UNSPEC;

	if(argc != 4)
	{
		/* Checks if args is valid */
		logger("Invalid number of arguments",'w',__func__,__LINE__);
		fprintf(stderr,"USAGE: tftp_c GET/PUT server filename\n");
		exit(1);
	}
	char *server = argv[2]; /* Server address */
	char *file = argv[3]; /* File name on which operation has to be done */
	
	/* Configuration of client starts */
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	if((rv = getaddrinfo(server, SERVERPORT, &hints, &servinfo)) != 0)
	{
		logger("Client: getaddrinfo",'f',__func__,__LINE__);
		fprintf(stderr, "CLIENT: getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	/* Loop through all the results and make a socket */
	for(res = servinfo; res != NULL; res = res->ai_next) 
	{
		if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
		{
			logger("Client: socket",'w',__func__,__LINE__);
			perror("CLIENT: socket");
			continue;
		}
		break;
	}
	if(res == NULL)
	{
		logger("Client: failed to bind",'f',__func__,__LINE__);
		fprintf(stderr, "CLIENT: failed to bind socket\n");
		return 2;
	}
	/* Configuration of client ends */
	/* Main implementation starts */
	if(strcmp(argv[1], "GET") == 0 || strcmp(argv[1], "get") == 0)
	{ 
		/* Get data from the server */
		logger("Client: requesting file from server",'i',__func__,__LINE__);
		readFile(sockfd,their_addr,res,file,server);
	} 
	else if(strcmp(argv[1], "PUT") == 0 || strcmp(argv[1], "put") == 0)
	{	
		/* Write data to server */	
		logger("Client: writing file to server",'i',__func__,__LINE__);
		writeFile(sockfd,their_addr,res,file,server);
	} else 
	{ 
		/* Invalid request */
		logger("Client: wrong input format",'w',__func__,__LINE__);
		fprintf(stderr,"USAGE: tftp_c GET/PUT server filename\n");
		exit(1);
	}
	/* Main implementation ends */
	freeaddrinfo(servinfo);
	close(sockfd);
	return 0;
}
