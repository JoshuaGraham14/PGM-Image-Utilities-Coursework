/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_2                    */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 04/05/22        */
/***********************************/

/***********************************/
/* Module for handling gtopo errors*/
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* Libraries */
#include <stdio.h> //library for I/O routines
#include <stdlib.h> //library for memory routines

/* Header files */
#include "gtopoErrors.h"

/* FUNC: Check reduction factor is an integer and is greater than 0 */
int checkWidthAndHeight(char *width, char *height)
{
    /* if reduction factor is an integer */
    if (atoi(width) && atoi(height))
    {
        int widthInt = atoi(width);
        int heightInt = atoi(height);
        /* if reduction factor is less than or equal to 0 */
        if (widthInt <= 0 || heightInt <= 0)
        {
            /* print an error message        */
            printf("ERROR: Miscellaneous (width or height parameter invalid)\n");
            /* return an error code          */
            return ERROR_MISCELLANEOUS; 
        }
    }
    else
    {   
        /* print an error message        */
        printf("ERROR: Miscellaneous (width or height parameter invalid)\n");
        /* return an error code          */
        return ERROR_MISCELLANEOUS; 
    }

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}