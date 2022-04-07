/**********************************************************************************************
 **  FILENAME	      : server.c	
 **
 **  DESCRIPTION      : This is the server file
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
#include "SERVER_UTILITY.h"
// converts block number to length-2 string
void s_to_i(char *f, int n){
	if(n==0){
		f[0] = '0', f[1] = '0', f[2] = '\0';
	} else if(n%10 > 0 && n/10 == 0){
		char c = n+'0';
		f[0] = '0', f[1] = c, f[2] = '\0';
	} else if(n%100 > 0 && n/100 == 0){
		char c2 = (n%10)+'0';
		char c1 = (n/10)+'0';
		f[0] = c1, f[1] = c2, f[2] = '\0';
	} else {
		f[0] = '9', f[1] = '9', f[2] = '\0';
	}
}

// makes RRQ packet
char* make_rrq(char *filename){
	char *packet;
	packet = malloc(2+strlen(filename));
	memset(packet, 0, sizeof(packet));
	strcat(packet, "01");//opcode
	strcat(packet, filename);
	return packet;
}

// makes WRQ packet
char* make_wrq(char *filename){
	char *packet;
	packet = malloc(2+strlen(filename));
	memset(packet, 0, sizeof(packet));
	strcat(packet, "02");//opcode
	strcat(packet, filename);
	return packet;
}

// makes data packet
char* make_data_pack(int block, char *data){
	char *packet;
	char temp[3];
	s_to_i(temp, block);
	packet = malloc(4+strlen(data));
	memset(packet, 0, sizeof (packet));
	strcat(packet, "03");//opcode
	strcat(packet, temp);
	strcat(packet, data);
	return packet;
}

// makes ACK packet
char* make_ack(char* block){
	char *packet;
	packet = malloc(2+strlen(block));
	memset(packet, 0, sizeof (packet));
	strcat(packet, "04");//opcode
	strcat(packet, block);
	return packet;
}

// makes ERR packet
char* make_err(char *errcode, char* errmsg){
	char *packet;
	packet = malloc(4+strlen(errmsg));
	memset(packet, 0, sizeof (packet));
	strcat(packet, "05");//opcode
	strcat(packet, errcode);
	strcat(packet, errmsg);
	return packet;
} 
/*******************************************************************
 **  FUNCTION NAME	: get_in_addr
 **
 **  DESCRIPTION	: 
 **
 **  PARAMETERS		: 
 **
 **  RETURN 		: 
 **
 ******************************************************************/
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) 
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/*******************************************************************
 **  FUNCTION NAME	: check_timeout
 **
 **  DESCRIPTION	: 
 **
 **  PARAMETERS		: 
 **
 **  RETURN 		: 
 **
 ******************************************************************/
//CHECKS FOR TIMEOUT
int check_timeout(int sockfd, char *buf, struct sockaddr_storage their_addr, socklen_t addr_len)
{
	fd_set fds;
	int n;
	struct timeval tv;

	// set up the file descriptor set
	FD_ZERO(&fds);
	FD_SET(sockfd, &fds);

	// set up the struct timeval for the timeout
	tv.tv_sec = TIME_OUT;
	tv.tv_usec = 0;

	// wait until timeout or data received
	n = select(sockfd+1, &fds, NULL, NULL, &tv);
	if (n == 0)
	{
		printf("timeout\n");
		return -2; // timeout!
	} 
	else if (n == -1)
	{
		printf("error\n");
		return -1; // error	
	}
	return recvfrom(sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len);
}

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
int maxTries(int sockfd, char *buf, struct sockaddr_storage their_addr, socklen_t addr_len, int numbytes, struct addrinfo *p, char *t_msg)
{
	int times;
	for(times=0;times<=MAX_TRIES;++times)
	{
		if(times == MAX_TRIES)
		{
			printf("SERVER: MAX NUMBER OF TRIES REACHED\n");
			return EXIT_FAILURE;
		}
		numbytes = check_timeout(sockfd, buf, their_addr, addr_len);
		if(numbytes == -1)
		{//error
			perror("SERVER: recvfrom");
			return EXIT_FAILURE;
		} else if(numbytes == -2)
		{//timeout
			printf("SERVER: try no. %d\n", times+1);
			int temp_bytes;
			if((temp_bytes = sendto(sockfd, t_msg, strlen(t_msg), 0, p->ai_addr, p->ai_addrlen)) == -1){
				perror("SERVER: ACK: sendto");
				return EXIT_FAILURE;
		}
			printf("SERVER: sent %d bytes AGAIN\n", temp_bytes);
			continue;
		} else 
		{ //valid
			return EXIT_SUCCESS;
		}
	}
}
/*******************************************************************
 **  FUNCTION NAME	: readRequest
 **
 **  DESCRIPTION	: 
 **
 **  PARAMETERS		: 
 **
 **  RETURN 		: 
 **
 ******************************************************************/
int readRequest(int sockfd, char *buf, struct sockaddr_storage their_addr, socklen_t addr_len, int numbytes, struct addrinfo *p, char s[])
{
		char filename[MAX_FILENAME_LEN];
		strcpy(filename, buf+2);

		FILE *fp = fopen(filename, "rb");
		if(fp == NULL || access(filename, F_OK) == -1){ //SENDING ERROR PACKET - FILE NOT FOUND
			fprintf(stderr,"SERVER: file '%s' does not exist, sending error packet\n", filename);
			char *e_msg = make_err("02", "ERROR_FILE_NOT_FOUND");
			printf("%s\n", e_msg);
			sendto(sockfd, e_msg, strlen(e_msg), 0, (struct sockaddr *)&their_addr, addr_len);
			exit(1);
		}

		//STARTING TO SEND FILE
		int block = 1;
		fseek(fp, 0, SEEK_END);
		int total = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		int remaining = total;
		if(remaining == 0)
			++remaining;
		else if(remaining%MAX_READ_LEN == 0)
			--remaining;

		while(remaining>0){
			//READING FILE
			char temp[MAX_READ_LEN+5];
			if(remaining>MAX_READ_LEN){
				fread(temp, MAX_READ_LEN, sizeof(char), fp);
				temp[MAX_READ_LEN] = '\0';
				remaining -= (MAX_READ_LEN);
			} else {
				fread(temp, remaining, sizeof(char), fp);
				temp[remaining] = '\0';
				remaining = 0;
			}

			//SENDING - DATA PACKET
			char *t_msg = make_data_pack(block, temp);
			if((numbytes = sendto(sockfd, t_msg, strlen(t_msg), 0, (struct sockaddr *)&their_addr, addr_len)) == -1){
				perror("SERVER ACK: sendto");
				exit(1);
			}
			printf("SERVER: sent %d bytes\n", numbytes);

			//WAITING FOR ACKNOWLEDGEMENT - DATA PACKET
			//maxTries func
			maxTries(sockfd, buf, their_addr, addr_len, numbytes, p, t_msg);

			printf("SERVER: got packet from %s\n", inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s));
			printf("SERVER: packet is %d bytes long\n", numbytes);
			buf[numbytes] = '\0';
			printf("SERVER: packet contains \"%s\"\n", buf);				
			++block;
			if(block>MAX_PACKETS)
				block = 1;
		}
		fclose(fp);
}

/*******************************************************************
 **  FUNCTION NAME	: writeRequest
 **
 **  DESCRIPTION	: 
 **
 **  PARAMETERS		: 
 **
 **  RETURN 		: 
 **
 ******************************************************************/
int writeRequest(int sockfd, char *buf, struct sockaddr_storage their_addr, socklen_t addr_len, int numbytes, char s[])
{
	char *message = make_ack("00");
	char last_recv_message[MAXBUFLEN];strcpy(last_recv_message, buf);
	char last_sent_ack[10];strcpy(last_sent_ack, message);
	if((numbytes = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&their_addr, addr_len)) == -1)
	{
		perror("SERVER ACK: sendto");
		exit(1);
	}

	printf("SERVER: sent %d bytes\n", numbytes);
	char filename[MAX_FILENAME_LEN];
	strcpy(filename, buf+2);
	strcat(filename, "_server");

	if(access(filename, F_OK) != -1)
	{ //SENDING ERROR PACKET - DUPLICATE FILE
		fprintf(stderr,"SERVER: file %s already exists, sending error packet\n", filename);
		char *e_msg = make_err("06", "ERROR_FILE_ALREADY_EXISTS");
		sendto(sockfd, e_msg, strlen(e_msg), 0, (struct sockaddr *)&their_addr, addr_len);
		exit(1);
	}

	FILE *fp = fopen(filename, "wb");
	if(fp == NULL || access(filename, W_OK) == -1)
	{ //SENDING ERROR PACKET - ACCESS DENIED
		fprintf(stderr,"SERVER: file %s access denied, sending error packet\n", filename);
		char *e_msg = make_err("05", "ERROR_ACCESS_DENIED");
		sendto(sockfd, e_msg, strlen(e_msg), 0, (struct sockaddr *)&their_addr, addr_len);
		exit(1);
	}

	int c_written;
	do{
		//RECEIVING FILE - PACKET DATA
		if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) 
		{
			perror("SERVER: recvfrom");
			exit(1);
		}
		printf("SERVER: got packet from %s\n", inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s));
		printf("SERVER: packet is %d bytes long\n", numbytes);
		buf[numbytes] = '\0';
		printf("SERVER: packet contains \"%s\"\n", buf);

		//SENDING LAST ACK AGAIN - AS IT HAS NOT REACHED
		if(strcmp(buf, last_recv_message) == 0)
		{
			sendto(sockfd, last_sent_ack, strlen(last_sent_ack), 0, (struct sockaddr *)&their_addr, addr_len);
			continue;
		}

		//WRITING FILE
		c_written = strlen(buf+4);
		fwrite(buf+4, sizeof(char), c_written, fp);
		strcpy(last_recv_message, buf);

		//SENDING ACKNOWLEDGEMENT - PACKET DATA
		char block[3];
		strncpy(block, buf+2, 2);
		block[2] = '\0';
		char *t_msg = make_ack(block);
		if((numbytes = sendto(sockfd, t_msg, strlen(t_msg), 0, (struct sockaddr *)&their_addr, addr_len)) == -1)
		{
			perror("SERVER ACK: sendto");
			exit(1);
		}
		printf("SERVER: sent %d bytes\n", numbytes);
		strcpy(last_sent_ack, t_msg);
	}
       	while(c_written == MAX_READ_LEN);
	printf("NEW FILE: %s SUCCESSFULLY MADE\n", filename);
	fclose(fp);
}


