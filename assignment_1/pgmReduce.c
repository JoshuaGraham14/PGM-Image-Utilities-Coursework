 /***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_1                    */
/* TASK IV                         */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 07/03/22        */
/***********************************/

/***********************************/
/* pgmReduce                       */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>
#include <stdbool.h>

#include "pgmImage.h"
#include "pgmErrors.h"

#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_INPUT_FILE 2
#define EXIT_BAD_OUTPUT_FILE 3

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250

int writeReduced(char *filename, Image *imagePointer, int reductionFactor);

int main(int argc, char **argv)
{ /* main() */
	/* check for correct number of arguments */
	if (argc != 4)
    { /* wrong arg count *//* main routine                    */
		/* print an error message        */
		printf("Usage: %s input_file reduction_factor output_file\n", argv[0]);
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
    } /* wrong arg count */

    if (atoi(argv[2]) < 1)
    {
        //reduction factor n must be greater than 0
    }
	
	/* variables for storing the image - stored in an Image struct       */
    Image inputImage = {.magic_number={'0','0'}, .magic_Number=(unsigned short *) inputImage.magic_number, .commentLine=NULL, .width=0, .height=0, .maxGray=255, .imageData=NULL};
    Image *inputImagePtr = &inputImage;

    /* now start reading in the data         */
    int returnValue = readpgmFile(argv[1], inputImagePtr);
	if (returnValue != 0)
    {
        return EXIT_BAD_INPUT_FILE;
    }

    //REDUCE
    int reductionFactor = atoi(argv[2]);
    if (writeReduced(argv[3], inputImagePtr, reductionFactor) == 1)
    {
        printf("NOT REDUCED - ERROR");
        return EXIT_BAD_OUTPUT_FILE;
    }

	/* at this point, we are done and can exit with a success code */
    printf("REDUCED\n");
	return EXIT_NO_ERRORS;
} /* main() */

int writeReduced(char *filename, Image *imagePointer, int reductionFactor)
{
    /* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");

    /* check whether file opening worked     */
    if (checkOutputFile(outputFile, filename, imagePointer->imageData, imagePointer->commentLine) == 1) return 1;
    
    int reducedWidth = (imagePointer->width+reductionFactor-1)/reductionFactor;
    int reducedHeight = (imagePointer->height+reductionFactor-1)/reductionFactor;
    int originalWidth = imagePointer->width;
    /* write magic number, size & gray value */
    size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", imagePointer->magic_number[1], reducedWidth, reducedHeight, imagePointer->maxGray);

	/* check that dimensions wrote correctly */
	if (checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten) == 1) return 1;

    long nImageBytes = imagePointer->width * imagePointer->height * sizeof(unsigned char);

    unsigned char *nextGrayValue;
    int widthCounter = 0;
    int heightCounter = 0;
    /* pointer for efficient write code      */
    for (nextGrayValue = imagePointer->imageData; nextGrayValue < imagePointer->imageData + nImageBytes; nextGrayValue++)
    { /* per gray value */
    /* get next char's column        */
		int nextCol = (nextGrayValue - imagePointer->imageData + 1) % imagePointer->width;
        
        int newCol = 1;

        if (widthCounter%reductionFactor==0 && heightCounter%reductionFactor==0)
        {
            if ((widthCounter+reductionFactor+1) > originalWidth)
            {
                newCol = 0;
            }

            if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
            {
                nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (newCol ? ' ' : '\n'));
            }
            else 
            {
                fwrite(nextGrayValue, 1, 1, outputFile);
            }
        }
        
		/* sanity check on write         */
		if (checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten) == 1) return 1;

        if(nextCol == 0)
        {
            heightCounter++;
            widthCounter=0;
        }
        else
        {
            widthCounter++;
        }
    } /* per gray value */
    return 0;
}