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
    int r; //return value
	if((r = checkArgumentCount(argc, 3)) != 0)
    {
        if (r == -1)
        {
            printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        return r;
    }

	/* variables for storing the image - stored in an Image struct       */
    Image inputImage = {.magic_number={'0','0'}, .magic_Number=(unsigned short *) inputImage.magic_number, .commentLine=NULL, .width=0, .height=0, .maxGray=255, .imageData=NULL};
    Image *inputImagePtr = &inputImage;

    // *TO DO*: Check magic nuber is P2
    if ((r = readpgmFile(argv[1], inputImagePtr)) != 0) return r;

    inputImage.magic_number[1] = '2';

    if ((r = writepgmFile(argv[2], inputImagePtr)) != 0) return r;

	/* at this point, we are done and can exit with a success code */
    printf("CONVERTED\n");
	return EXIT_NO_ERRORS;
} /* main() */