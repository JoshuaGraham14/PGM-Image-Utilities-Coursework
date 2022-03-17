/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_1                    */
/* TASK II                         */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 13/03/22        */
/***********************************/

/***********************************/
/* reads two pgm files and compares*/
/* them to see if they are         */
/* logically equivalent            */ 
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>

#include "pgmImage.h"
#include "pgmErrors.h"

#define EXIT_NO_ERRORS 0
#define EXIT_BAD_INPUT_FILE 2
#define EXIT_BAD_OUTPUT_FILE 3

int compareImages(Image *inputImage1, Image *inputImage2);

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: 1st input file name    */
/* argv[2]: 2nd input file name    */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
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
    Image inputImage1 = {.magic_number={'0','0'}, .magic_Number=(unsigned short *) inputImage1.magic_number, .commentLine=NULL, .width=0, .height=0, .maxGray=255, .imageData=NULL};
    Image *inputImagePtr1 = &inputImage1;

    Image inputImage2 = {.magic_number={'0','0'}, .magic_Number=(unsigned short *) inputImage2.magic_number, .commentLine=NULL, .width=0, .height=0, .maxGray=255, .imageData=NULL};
    Image *inputImagePtr2 = &inputImage2;

	/* now start reading in the data         */
    int returnValue = readpgmFile(argv[1], inputImagePtr1);
	if (returnValue != 0)
    {
        return EXIT_BAD_INPUT_FILE;
    }

	returnValue = readpgmFile(argv[2], inputImagePtr2);
    if (returnValue != 0)
    {
         return EXIT_BAD_OUTPUT_FILE;
    }

    //COMPARE:
    if (compareImages(inputImagePtr1, inputImagePtr2) == 1)
    {
        printf("DIFFERENT\n");
    }
    else 
    {
        printf("IDENTICAL\n");
    }
	return EXIT_NO_ERRORS;
} /* main() */


int compareImages(Image *inputImage1, Image *inputImage2)
{
    //COMPARE: magic number, width, height & maxGray
    if (!(
    strcmp((const char *)inputImage1->magic_number, (const char *)inputImage2->magic_number) == 0 ||
    inputImage1->width==inputImage2->width ||
    inputImage1->height==inputImage2->height ||
    inputImage1->maxGray==inputImage2->maxGray
    ))
    {
        return 1;
    }

    //COMPARE: image data
    long nImageBytes = inputImage1->width * inputImage1->height * sizeof(unsigned char);
    int i;
    for (i = 0; i<nImageBytes; i++)
    {
        if(inputImage1->imageData[i] != inputImage2->imageData[i])
        {
            return 1;
        }
    }
    
    return 0;
}