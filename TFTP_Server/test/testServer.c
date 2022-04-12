/*******************************************************************************************

 *     FILENAME           :    testServer.c
 *
 *     DESCRIPTION        :    Sprint-1 : 
 
 				
 *
 *     REVISION HISTORY   :   Last revised on (  )
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
#include <server_utility.h>

/******************************************************
**FUNCTION NAME : 
**
**DESCRIPTION : 
**
**RETURNS : NA
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
**FUNCTION NAME : 
**
**DESCRIPTION : 
**
**RETURNS : NA
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
**FUNCTION NAME : 
**
**DESCRIPTION : 
**
**RETURNS : NA
**
*********************************************************/
void testMakeERR(void)
{
	char *errOne="FILE_NOT_FOUND";
	char *errTwo="FILE_ALREADY_EXISTS";
   	CU_ASSERT(0 == strcmp(makeERR("02",errOne),"0502FILE_NOT_FOUND"));
   	CU_ASSERT(0 == strcmp(makeERR("06",errTwo),"0506FILE_ALREADY_EXISTS"));
}
