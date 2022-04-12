/**********************************************************************************************
 **  FILENAME	      : SERVER_UTILITY.h	
 **
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

#ifndef __SERVER_UTILITY_H__
#define __SEVER_UTILITY_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>


/***************************************
 * 		MACROS	
 **************************************/

#define MYPORT "4950" /* Port to be opened on server */
#define SERVERPORT "4950" /* The port users will be connecting to */
#define MAXBUFLEN 550 /* To get sockaddr, IPv4 or IPv6 */
#define MAX_READ_LEN 512 /* Maximum data size that can be sent on one packet */
#define MAX_FILENAME_LEN 100 /* Maximum length of file name supported */
#define MAX_PACKETS 99 /* Maximum number of file packets */
#define MAX_TRIES 3 /* Maximum number of tries if packet times out */
#define TIME_OUT 5 /* in seconds */
#define DATA_OPCODE "03"  /*opcode for data packet*/
#define ACK_OPCODE "04"   /*opcode for acknowledgement packet*/
#define ERR_OPCODE "05"   /*opcode for error packet*/
#define WRQ_ACK "00"      /*Acknowledgement block for write request*/


/*******************************************************************
 **  FUNCTION NAME	: logOpen 
 **
 **  DESCRIPTION	: 
 **
 **  PARAMETERS	:  
 **
 **  RETURN 		: 
 **
 ******************************************************************/
void logOpen(const char *logFileName);

/*******************************************************************
 **  FUNCTION NAME	: logClose
 **
 **  DESCRIPTION	: 
 **
 **  PARAMETERS		:  
 **
 **  RETURN 		: 
 **
 ******************************************************************/
void logClose(void);
 
/*******************************************************************
 **  FUNCTION NAME	: logMessage
 **
 **  DESCRIPTION	: Maintaining logs of all requests from client
 **
 **  PARAMETERS	: const char *format, ....
 **
 **  RETURN 		: void
 **
 ******************************************************************/
void logMessage(const char *format,...);

/*******************************************************************
 **  FUNCTION NAME	: numberToString
 **
 **  DESCRIPTION	: Converts block number to string of length 2
 **
 **  PARAMETERS	: char *temp, int num
 **
 **  RETURN 		: void
 **
 ******************************************************************/
void numberToString(char *str, int num);

/*******************************************************************
 **  FUNCTION NAME	: makeDataPacket
 **
 **  DESCRIPTION	: Makes data packet
 **
 **  PARAMETERS	: int block, char *data
 **
 **  RETURN 		: packet
 **
 ******************************************************************/
char* makeDataPacket(int block, char *data);

/*******************************************************************
 **  FUNCTION NAME	: makeACK
 **
 **  DESCRIPTION	: Makes acknowledgement packet
 **
 **  PARAMETERS	: char* block
 **
 **  RETURN 		: packet
 **
 ******************************************************************/
char* makeACK(char* block);

/*******************************************************************
 **  FUNCTION NAME	: makeERR
 **
 **  DESCRIPTION	: Makes error packet 
 **
 **  PARAMETERS		: char *errcode, char* errmsg
 **
 **  RETURN 		: packet
 **
 ******************************************************************/
char* makeERR(char *errcode, char* errmsg);

/*******************************************************************
 **  FUNCTION NAME	: checkTimeout
 **
 **  DESCRIPTION	: Checks for the timeout condition
 **
 **  PARAMETERS	:  
 **
 **  RETURN 		: 
 **
 ******************************************************************/
int checkTimeout(int sockfd, char *buf, struct sockaddr_storage their_addr, socklen_t addr_len);

/*******************************************************************
 **  FUNCTION NAME	: maxTries
 **
 **  DESCRIPTION	: The maximum number of tries the host will
 			  try to send the packet to the other host
 **
 **  PARAMETERS		:  
 **
 **  RETURN 		: numbytes
 **
 ******************************************************************/
int maxTries(int sockfd, char *buf, struct sockaddr_storage their_addr, socklen_t addr_len, struct addrinfo *res, char *t_msg);
 
/*******************************************************************
 **  FUNCTION NAME	: getAddress
 **
 **  DESCRIPTION	: 
 **
 **  PARAMETERS	:  
 **
 **  RETURN 		: void
 **
 ******************************************************************/
void *getAddress(struct sockaddr *sa);
 
/*******************************************************************
 **  FUNCTION NAME	: readRequest
 **
 **  DESCRIPTION	: Server upon receiving read request
 **
 **  PARAMETERS	:  
 **
 **  RETURN 		: 
 **
 ******************************************************************/
int readRequest(int sockfd, char *buf, struct sockaddr_storage their_addr, socklen_t addr_len, struct addrinfo *res);

/*******************************************************************
 **  FUNCTION NAME	: writeRequest
 **
 **  DESCRIPTION	: Server gets a write request with the 
 			  filename
 **
 **  PARAMETERS	:  
 			  
 **
 **  RETURN 		: 
 **
 ******************************************************************/
int writeRequest(int sockfd, char *buf, struct sockaddr_storage their_addr, socklen_t addr_len);

/*******************************************************************
 **  FUNCTION NAME	: errorHandler
 **
 **  DESCRIPTION	: Handles the error
 **
 **  PARAMETERS	:  int ret, const char *mesg
 **
 **  RETURN 		: void
 **
 ******************************************************************/
void errorHandler(int ret, const char *errMesg);
/******************************************************************************
 **  FUNCTION NAME	: signalHandler 
 **
 **  DESCRIPTION	: Handles CTRL+c signal and stops the server program
 **
 **  PARAMETERS	: sig
 **
 **  RETURN 		: void
 **
 *****************************************************************************/
void signalHandler(int sig);

/*******************************************************************
 **  FUNCTION NAME	: logger
 **
 **  DESCRIPTION	: Used for debug log messages using 
 			  4 levels 
 **
 **  PARAMETERS	:  char* message, char logType
 			  
 **
 **  RETURN 		: EXIT_SUCCESS
 **
 ******************************************************************/
int logger(char* message, char logType, const char *funcName,int lineNo );

#endif

