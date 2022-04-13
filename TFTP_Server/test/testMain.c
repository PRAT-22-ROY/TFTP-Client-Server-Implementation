/*******************************************************************************************

 *     FILENAME           :    testMain.c
 *
 *     DESCRIPTION        :    File to perform CUnit unit test on the functions present in server.c program
 *
 *
 *
 *     REVISION HISTORY   :   Last revised on (12/04/2022)
 *
 *     DATE                GROUP MEMBERS              REFERENCE               REASON
 *     --------------------------------------------------------------------------------------------------
 *    12th April 2022       Sprint Group-5              TFTP               Sprint-implementation
 *                          
 *				
 *
 
 *     Copyright Â© 2022 Capgemini Group  All Rights Reserved
 *
 *******************************************************************************************/
 
/***************************************************************************
 *                          INCLUDES
 ***************************************************************************/ 
 
#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <server_utility.h>
#include <testServer.h>

static FILE* temp_file = NULL;



/******************************************************
** FUNCTION NAME : init_suite1
**
** DESCRIPTION : The suite initialization function.
**              Opens the temporary file used by the tests.
**
** RETURNS : Returns zero on success, non-zero otherwise.
**
*********************************************************/

int init_suite1(void)
{
	   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
	      return -1;
	   }
	   else {
	      return 0;
	   }
}


/******************************************************
** FUNCTION NAME : clean_suite1
**
** DESCRIPTION : The suite cleanup function.
**               Closes the temporary file used by the tests.
**             
**
** RETURNS : Returns zero on success, non-zero otherwise.
**
*********************************************************/
int clean_suite1(void)
{
	   if (0 != fclose(temp_file)) {
	      return -1;
	   }
	   else {
	      temp_file = NULL;
	      return 0;
	   }
}

/******************************************************
** FUNCTION NAME : main
**
** DESCRIPTION : Intializes and registers all testing functions.
**               in CUnit registry  
**             
** RETURNS : Returns zero on success, non-zero otherwise.
**
*********************************************************/

int main()
{
	   CU_pSuite pSuite = NULL;

	   /* initialize the CUnit test registry */
	   if (CUE_SUCCESS != CU_initialize_registry())
	      return CU_get_error();

	   /* add a suite to the registry */
	   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
	   if (NULL == pSuite) {
	      CU_cleanup_registry();
	      return CU_get_error();
	   }

	   /* add the tests to the suite */
	   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
	   if(NULL == CU_add_test(pSuite, "test of makeACK()", testMakeACK))
	   {
	      CU_cleanup_registry();
	      return CU_get_error();
	   }
	   
	   if(NULL == CU_add_test(pSuite, "test of makeDataPacket()", testMakeData)){
	      CU_cleanup_registry();
	      return CU_get_error();
	   }
	   
	   if(NULL == CU_add_test(pSuite, "test of makeERR()", testMakeERR)){
	      CU_cleanup_registry();
	      return CU_get_error();
	   }
	   
	   /* Run all tests using the CUnit Basic interface */
	   CU_basic_set_mode(CU_BRM_VERBOSE);
	   CU_basic_run_tests();
	   CU_cleanup_registry();
	   return CU_get_error();
}
