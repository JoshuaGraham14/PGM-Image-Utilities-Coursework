/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_1                    */
/* TASK III                        */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 07/03/22        */
/***********************************/

/***********************************/
/* Improved pgm echo               */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include <stdbool.h>

#include "pgmErrors.h"
#include "pgmImage.h"

#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_INPUT_FILE 2
#define EXIT_BAD_OUTPUT_FILE 3

int main(int argc, char **argv)
{ /* main() */
	/* check for correct number of arguments */
	if (argc != 3)	
    { /* wrong arg count *//* main routine                    */
		/* print an error message        */
		printf("Usage: %s input_file output_file\n", argv[0]);
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
    }

	/* variables for storing the image - stored in an Image struct       */
    Image inputImage = {.magic_number={'0','0'}, .magic_Number=(unsigned short *) inputImage.magic_number, .commentLine=NULL, .width=0, .height=0, .maxGray=255, .imageData=NULL};
    Image *inputImagePtr = &inputImage;

    // *TO DO*: Check magic nuber is P2
    int returnValue = readpgmFile(argv[1], inputImagePtr);
	if (returnValue != 0)
    {
        return EXIT_BAD_INPUT_FILE;
    }

    inputImage.magic_number[1] = '5';

    returnValue = writepgmFile(argv[2], inputImagePtr);
    if (returnValue != 0)
    {
        return EXIT_BAD_OUTPUT_FILE;
    }

	/* at this point, we are done and can exit with a success code */
    printf("ECHOED\n");
	return EXIT_NO_ERRORS;
} /* main() */