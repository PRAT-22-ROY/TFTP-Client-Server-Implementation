/**********************************************************************************************
 **  FILENAME	      : 	
 **
 **  DESCRIPTION      : This file is used for client
 ** 
 **
 **  REVISION HISTORY :
 **  
 **  DATE	    NAME	      REFERENCE	                REASON
 **  ------------------------------------------------------------------------------------
 **  04 April 2022    Pratik Roy                Creation of Writer process
 **
 **
 **  Copyright @ 2022 Capgemini Engineering All Rights Reserved
 **
 ********************************************************************************************/
# include "CLIENT_UTILITY.h"

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


/*******************************************************************
 **  FUNCTION NAME	: main
 **
 **  DESCRIPTION	: 
 **			  
 **			  
 **
 **  PARAMETERS		: argc, argv
 **
 **  RETURN 		: 
 **
 ******************************************************************/



/*******************************************************************
 **  FUNCTION NAME	: errorHandler
 **
 **  DESCRIPTION	: Handles the errors
 **
 **  PARAMETERS		: return type of functions and their error
 **
 **  RETURN 		: void
 **
 ******************************************************************/
void errorHandler(int ret, const char *mesg)
{
	if(ret == -1)
	{
		perror(mesg);
		exit(EXIT_FAILURE);
	}
}
