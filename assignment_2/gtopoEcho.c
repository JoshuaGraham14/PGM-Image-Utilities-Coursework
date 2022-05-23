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
/* Takes in as input a file of     */
/* type .dem and outputs it to a   */
/* different file.                 */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* Libraries */
#include <stdio.h> //library for I/O routines
#include <stdlib.h> //library for memory routines

/* Header files */
#include "gtopoImage.h"
#include "gtopoErrors.h"

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: width                  */
/* argv[3]: height                 */
/* argv[4]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int main(int argc, char **argv)
{ /* main() */

	/* check for correct number of arguments */
    int returnVal; //return value variable
    /* check if there were 5 CLI arguments   */
	if((returnVal = checkArgumentCount(argc, 5)) != 0)
    {
        /* if there weren't 5 CLI arguments:   */
        if (returnVal == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: %s inputFile width height outputFile\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() */
        /* method (i.e, ERROR_BAD_ARGUMENT_COUNT=1)                 */
        return returnVal;
    }

	/* create an imagePtr to store the gtopo image data as an Image struct */
    Image *imagePtr = malloc(sizeof(Image)); // dynamically allocate memory for imagePtr

    /* Read data from input file, store data in imagePtr                */
    /* Only return returnVal if reading wasn't successful */
	if ((returnVal = readGtopoFile(argv[1], imagePtr, argv[2], argv[3])) != 0) return returnVal;

    /* Write data to output file and only return returnVal if it wasn't successful */
    /* NOTE: Pass in 1 for 3rd parameter as we are not reducing the size of the image */
	if ((returnVal = writeGtopoFile(argv[4], imagePtr, 1)) != 0) return returnVal;

	/* at this point, we are done and can exit with a success code */
    printf("ECHOED\n");
	return EXIT_NO_ERRORS;
} /* main() */