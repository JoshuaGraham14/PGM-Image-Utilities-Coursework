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

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250

int writeReduced(char *filename, Image *imagePointer, int reductionFactor);

int main(int argc, char **argv)
{ /* main() */
    /* check for correct number of arguments */
    int r; //return value
	if((r = checkArgumentCount(argc, 4)) != 0)
    {
        if (r == -1)
        {
             printf("Usage: %s inputImage.pgm reduction_factor outputImage.pgm\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        return r;
    }

    //Check reduction factor is int and is > 0
    if((r = checkReductionFactor(argv[2])) != 0) return r;
	
	/* variables for storing the image - stored in an Image struct       */
    Image *imagePtr = malloc(sizeof(Image));
    createNewImage(imagePtr);

    /* now start reading in the data         */
    if ((r = readpgmFile(argv[1], imagePtr)) != 0) return r;

    //REDUCE
    int reductionFactor = atoi(argv[2]);
    if ((r = writeReduced(argv[3], imagePtr, reductionFactor)) != 0) return r;

	/* at this point, we are done and can exit with a success code */
    printf("REDUCED\n");
	return EXIT_NO_ERRORS;
} /* main() */

int writeReduced(char *filename, Image *imagePointer, int reductionFactor)
{
    /* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");

    int r;
    /* check whether file opening worked     */
    if ((r = checkOutputFile(outputFile, filename, imagePointer->imageData, imagePointer->commentLine)) != 0) return r;
    
    int reducedWidth = (imagePointer->width+reductionFactor-1)/reductionFactor;
    int reducedHeight = (imagePointer->height+reductionFactor-1)/reductionFactor;
    int originalWidth = imagePointer->width;
    /* write magic number, size & gray value */
    size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", imagePointer->magic_number[1], reducedWidth, reducedHeight, imagePointer->maxGray);

	/* check that dimensions wrote correctly */
	if ((r = checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten)) != 0) return r;

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
		if ((r = checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten)) != 0) return r;

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
    return EXIT_NO_ERRORS;
}