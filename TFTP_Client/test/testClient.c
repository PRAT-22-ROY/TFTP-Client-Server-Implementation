/*******************************************************************************************

 *     FILENAME           :    testClient.c
 *
 *     DESCRIPTION        :    Sprint-1  
 
 				
 *
 *     REVISION HISTORY   :   Last revised on (12/04/2022)
 *
 *     DATE                GROUP MEMBERS              REFERENCE               REASON
 *     --------------------------------------------------------------------------------------------------
 *                                     Sprint1-implementation
                          
				
 *
 
 *     Copyright Â© 2022 Capgemini Group  All Rights Reserved
 *
 *******************************************************************************************/

/***************************************************************************
 *                          INCLUDES
 ***************************************************************************/
 
#include <stdio.h>
#include <string.h>
#include <CUnit.h>
#include <Basic.h>
#include <client_utility.h>


/******************************************************
**FUNCTION NAME : testMakeRRQ
**
**DESCRIPTION : Function to test makeRRQ function
**
**RETURNS : void
**
*********************************************************/
void testMakeRRQ(void)
{
	char *fileOne="sample";
	char *fileTwo="server_program";
   	CU_ASSERT(0 == strcmp(makeRRQ(fileOne),"01sample"));
      	CU_ASSERT(0 == strcmp(makeRRQ(fileTwo),"01server_program"));
}	

/******************************************************
**FUNCTION NAME : testMakeWRQ
**
**DESCRIPTION : Function to test makeWRQ function
**
**RETURNS : void
**
*********************************************************/
void testMakeWRQ(void)
{
	char *fileOne="sample";
	char *fileTwo="server_program";
   	CU_ASSERT(0 == strcmp(makeWRQ(fileOne),"02sample"));
      	CU_ASSERT(0 == strcmp(makeWRQ(fileTwo),"02server_program"));
}	

/******************************************************
**FUNCTION NAME : testMakeACK
**
**DESCRIPTION : Function to test makeACK function
**
**RETURNS : void
**
*********************************************************/
void testMakeACK(void)
{
	char *blockOne="03";
	char *blockTwo="54";
   	CU_ASSERT(0 == strcmp(makeACK(blockOne),"0403"));
      	CU_ASSERT(0 == strcmp(makeACK(blockTwo),"0454"));
}

/******************************************************
**FUNCTION NAME : testMakeData 
**
**DESCRIPTION : Function to test makeData function
**
**RETURNS : void
**
*********************************************************/
void testMakeData(void)
{
	char *dataOne="hello world";
	int blockOne=3;
	char *dataTwo="system programming";
	int blockTwo=38;
   	CU_ASSERT(0 == strcmp(makeDataPacket(blockOne,dataOne),"0303hello world"));
   	CU_ASSERT(0 == strcmp(makeDataPacket(blockTwo,dataTwo),"0338system programming"));
}

/******************************************************
**FUNCTION NAME : testMakeERR
**
**DESCRIPTION : Function to test test makeERR function
**
**RETURNS : void
**
*********************************************************/
void testMakeERR(void)
{
	char *errOne="FILE_NOT_FOUND";
	char *errTwo="FILE_ALREADY_EXISTS";
   	CU_ASSERT(0 == strcmp(makeERR("02",errOne),"0502FILE_NOT_FOUND"));
   	CU_ASSERT(0 == strcmp(makeERR("06",errTwo),"0506FILE_ALREADY_EXISTS"));
}
