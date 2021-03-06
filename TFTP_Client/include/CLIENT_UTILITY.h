/**********************************************************************************************
 **  FILENAME	      : client_utility.h	
 **
 **  DESCRIPTION      : This file defines macros and header files for client.c and main.c 
 ** 
 **
 **  REVISION HISTORY :
 **  
 **  DATE	    NAME		   REFERENCE	    REASON
 **  ------------------------------------------------------------------------------------
 **  12 April 2022   Sprint_Group_5         TFTP   Sprint Assessment
 **
 **
 **  Copyright @ 2022 Capgemini Engineering All Rights Reserved
 **
 ********************************************************************************************/

/***************************************
 * 		INCLUDES
 **************************************/
 
 #ifndef __CLIENT_UTILITY_H__
 #define __CLIENT_UTILITY_H__

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <time.h>


/***************************************
 * 		MACROS
 **************************************/
# define MYPORT "4950" 	/* port to be opened on server */
# define SERVERPORT "4950" 	/* the port users will be connecting to */
# define MAXBUFLEN 550 	/* get sockaddr, IPv4 or IPv6 */
# define MAX_READ_LEN 512 	/* maximum data size that can be sent on one packet */
# define MAX_FILENAME_LEN 100 /* maximum length of file name supported */
# define MAX_PACKETS 99 	/* maximum number of file packets */
# define MAX_TRIES 3 		/* maximum number of tries if packet times out */
# define TIME_OUT 5 		/* in seconds */
#define RRQ_OPCODE "01"	/*opcode for read request*/
#define WRQ_OPCODE "02"	/*opcode for write reqest*/
#define DATA_OPCODE "03"	/*opcode for data packet*/
#define ACK_OPCODE "04"	/*opcode for acknowledgement packet*/
#define ERR_OPCODE "05"	/*opcode for error packet*/

/*******************************************************************
 **  FUNCTION NAME	: numberToString
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	: char *str, int num		  
 **
 **  RETURN 		:  void
 **
 ******************************************************************/
 void numberToString(char *str, int num);
 
/*******************************************************************
 **  FUNCTION NAME	: makeRRQ
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	: char *filename  
 **
 **  RETURN 		:  packet
 **
 ******************************************************************/
 char* makeRRQ(char *filename);
 
/*******************************************************************
 **  FUNCTION NAME	: makeRRQ
 **
 **  DESCRIPTION	: Funtion Prototype
 **
 **  PARAMETERS	: char *filename 			  
 **
 **  RETURN 		:  packet
 **
 ******************************************************************/
 char* makeWRQ(char *filename);
 
/*******************************************************************
 **  FUNCTION NAME	: makeDataPacket
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	: int block, char *data 			  
 **
 **  RETURN 		:  packet
 **
 ******************************************************************/
 char* makeDataPacket(int block, char *data);
 
/*******************************************************************
 **  FUNCTION NAME	: makeACK
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	: char* block			  
 **
 **  RETURN 		:  packet
 **
 ******************************************************************/
 char* makeACK(char* block);
 
/*******************************************************************
 **  FUNCTION NAME	: makeERR
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	: char *errcode, char* errmsg 			  
 **
 **  RETURN 		: packet
 **
 ******************************************************************/
 char* makeERR(char *errcode, char* errmsg);
 
/*******************************************************************
 **  FUNCTION NAME	: getAddress
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	: struct sockaddr *sa  			  
 **
 **  RETURN 		:  void
 **
 ******************************************************************/
 void *getAddress(struct sockaddr *sa);
 
/******************************************************************************
 **  FUNCTION NAME	: checkTimeout
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	: int sockfd, char *buf, struct sockaddr_storage *their_addr,
                         socklen_t addr_len			  
 **
 **  RETURN 		:  -2 or -1 or number of bytes received
 **
 ******************************************************************************/
 int checkTimeout(int sockfd, char *buf, struct sockaddr_storage *their_addr, socklen_t addr_len);
 
/************************************************************************************************
 **  FUNCTION NAME	: maxTries
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	: int sockfd,char *buf,struct sockaddr_storage *their_addr, socklen_t addr_len,
                         struct addrinfo *res,char *last_messag 			  
 **
 **  RETURN 		: numBytes
 **
 ***********************************************************************************************/
 int maxTries(int sockfd,char *buf,struct sockaddr_storage *their_addr, socklen_t addr_len,struct addrinfo *res,char *last_message);
 
/**************************************************************************************
 **  FUNCTION NAME	: readFile
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	: int sockfd, struct sockaddr_storage their_addr,struct addrinfo *res,
                         char *file,char *server  			  
 **
 **  RETURN 		:  EXIT_SUCCESS
 **
 **************************************************************************************/
 int readFile(int sockfd, struct sockaddr_storage their_addr,struct addrinfo *res, char *file,char *server);
 
/**************************************************************************************
 **  FUNCTION NAME	: writeFile 
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	: int sockfd, struct sockaddr_storage their_addr,struct addrinfo *res,
                         char *file,char *server 			  
 **
 **  RETURN 		: EXIT_SUCCESS
 **
 ***************************************************************************************/
 int writeFile(int sockfd, struct sockaddr_storage their_addr,struct addrinfo *res,char *file,char *server);
 
/*******************************************************************
 **  FUNCTION NAME	: errorHandler
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	: int ret, const char *mesg  			  
 **
 **  RETURN 		:  void
 **
 ******************************************************************/
 void errorHandler(int ret, const char *mesg);

/*******************************************************************
 **  FUNCTION NAME	: logger
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	: char* message, char logType,const char *funcName,
                         int lineNo  			  
 **
 **  RETURN 		: EXIT_SUCCESS 
 **
 ******************************************************************/
 int logger(char* message, char logType,const char *funcName,int lineNo);
 
 #endif 
