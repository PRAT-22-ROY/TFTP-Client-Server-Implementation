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
 **  12 Mar 2022  Sprint_Group_5  TFTP_SRS  Sprint Assessment   
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
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS	:  const char *logFileName
 **
 **  RETURN 		: void
 **
 ******************************************************************/
void logOpen(const char *logFileName);

/*******************************************************************
 **  FUNCTION NAME	: logClose
 **
 **  DESCRIPTION	: Function Prototype
 **
 **  PARAMETERS		:  None
 **
 **  RETURN 		: void
 **
 ******************************************************************/
void logClose(void);
 
/*******************************************************************
 **  FUNCTION NAME	: logMessage
 **
 **  DESCRIPTION	: Function Prototype
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
 **  DESCRIPTION	: Function prototype
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
 **  DESCRIPTION	: Function prototype
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
 **  DESCRIPTION	: Function prototype 
 **
 **  PARAMETERS		: char *errcode, char* errmsg
 **
 **  RETURN 		: packet
 **
 ******************************************************************/
char* makeERR(char *errcode, char* errmsg);

/*****************************************************************************
 **  FUNCTION NAME	: checkTimeout
 **
 **  DESCRIPTION	: Function prototype
 **
 **  PARAMETERS	:  int sockfd, char *buf, struct sockaddr_storage their_addr, 
                   socklen_t addr_len
 **
 **  RETURN 		: -2 or -1 or number of bytes received
 **
 *****************************************************************************/
int checkTimeout(int sockfd, char *buf, struct sockaddr_storage their_addr, socklen_t addr_len);

/***************************************************************************
 **  FUNCTION NAME	: maxTries
 **
 **  DESCRIPTION	: Function prototype
 **
 **  PARAMETERS		: int sockfd, char *buf, struct sockaddr_storage their_addr, 
                   socklen_t addr_len, struct addrinfo *res, char *t_msg 
 **
 **  RETURN 		: numbytes
 **
 ***************************************************************************/
int maxTries(int sockfd, char *buf, struct sockaddr_storage their_addr, socklen_t addr_len, struct addrinfo *res, char *t_msg);
 
/*******************************************************************
 **  FUNCTION NAME	: getAddress
 **
 **  DESCRIPTION	: Function prototype
 **
 **  PARAMETERS	:  struct sockaddr *sa
 **
 **  RETURN 		: void
 **
 ******************************************************************/
void *getAddress(struct sockaddr *sa);
 
/****************************************************************************
 **  FUNCTION NAME	: readRequest
 **
 **  DESCRIPTION	: Function prototype
 **
 **  PARAMETERS	:  int sockfd, char *buf, struct sockaddr_storage their_addr, 
                   socklen_t addr_len, struct addrinfo *res
 **
 **  RETURN 		: EXIT_SUCCESS or EXIT_FAILURE
 **
 *****************************************************************************/
int readRequest(int sockfd, char *buf, struct sockaddr_storage their_addr, socklen_t addr_len, struct addrinfo *res);

/***************************************************************************
 **  FUNCTION NAME	: writeRequest
 **
 **  DESCRIPTION	: Function prototype
 **
 **  PARAMETERS	: int sockfd, char *buf, struct sockaddr_storage their_addr,
                  socklen_t addr_len 
 			  
 **
 **  RETURN 		: EXIT_SUCCESS or EXIT_FAILURE
 **
 ***************************************************************************/
int writeRequest(int sockfd, char *buf, struct sockaddr_storage their_addr, socklen_t addr_len);

/*******************************************************************
 **  FUNCTION NAME	: errorHandler
 **
 **  DESCRIPTION	: Function prototype
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
 **  DESCRIPTION	: Function prototype
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
 **  DESCRIPTION	: Function prototype 
 **
 **  PARAMETERS	:  char* message, char logType
 			  
 **
 **  RETURN 		: EXIT_SUCCESS
 **
 ******************************************************************/
int logger(char* message, char logType, const char *funcName,int lineNo );

#endif

