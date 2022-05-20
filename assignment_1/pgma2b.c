/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_1                    */
/* TASK III                        */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 14/03/22        */
/***********************************/

/***********************************/
/* Takes in an ASCII pgm file      */
/* and outputs a binary pgm file.  */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* Libraries */
#include <stdio.h> //library for I/O routines
#include <stdlib.h> //library for memory routines

/* Header files */
#include "pgmErrors.h"
#include "pgmImage.h"

/***********************************/
/* main routine                    */
/*                                 */
/* 3 CLI parameters:               */
/* argv[0]: executable name        */
/* argv[1]: input file name (ASCII)  */
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{ /* main() */
	
    /* check for correct number of arguments */
    int returnVal; //return value variable
    /* check if there were 3 CLI arguments   */
	if((returnVal = checkArgumentCount(argc, 3)) != 0)
    {
        /* if there weren't 3 CLI arguments:   */
        if (returnVal == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() method */
        return returnVal;
    }

	/* create an imagePtr to store the pgm image data as an Image struct */
    Image *imagePtr = malloc(sizeof(Image)); // dynamically allocate memory for imagePtr

    /* Read data from input file, store data in imagePtr   */
    /* Only return returnVal if reading wasn't successful  */
    if ((returnVal = readpgmFile(argv[1], imagePtr, 1)) != 0) return returnVal;

    /* Set the magicNumber to "P5" which will cause the ASCII image to be written to in binary */
    imagePtr->magic_number[1] = '5';

    /* Write data to output file and only return returnVal if it wasn't successful */
    if ((returnVal = writepgmFile(argv[2], imagePtr, 1)) != 0) return returnVal;

	/* at this point, we are done and can exit with a success code */
    printf("CONVERTED\n");
	return EXIT_NO_ERRORS;
} /* main() */