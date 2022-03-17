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
#define EXIT_BAD_INPUT_FILE 2
#define EXIT_BAD_OUTPUT_FILE 3

int main(int argc, char **argv)
{ /* main() */
	
    /* check for correct number of arguments */
    int returnValue = checkArgumentCount(argc, 3);
	if(returnValue != 0)
    {
        printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
        return returnValue;
    }

	/* variables for storing the image - stored in an Image struct       */
    Image inputImage = {.magic_number={'0','0'}, .magic_Number=(unsigned short *) inputImage.magic_number, .commentLine=NULL, .width=0, .height=0, .maxGray=255, .imageData=NULL};
    Image *inputImagePtr = &inputImage;

    // *TO DO*: Check magic nuber is P2
    returnValue = readpgmFile(argv[1], inputImagePtr);
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
    printf("CONVERTED\n");
	return EXIT_NO_ERRORS;
} /* main() */