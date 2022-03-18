/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_1                    */
/* TASK IV                         */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 15/03/22        */
/***********************************/

/***********************************/
/* Reduces an input file by a      */
/* factor of n and outputs the new */
/* file.                           */
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

//writeReduced function declared
int writeReduced(char *filename, Image *imagePointer, int reductionFactor);

int main(int argc, char **argv)
{ /* main() */

    /* check for correct number of arguments */
    int r; //return value variable
    /* check if there were 4 CLI arguments   */
	if((r = checkArgumentCount(argc, 4)) != 0)
    {
        /* if there weren't 4 CLI arguments:   */
        if (r == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: %s inputImage.pgm reduction_factor outputImage.pgm\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() method */
        return r;
    }

    /* Check reduction factor is valid */
    if((r = checkReductionFactor(argv[2])) != 0) return r;
	
	/* create an imagePtr to store the pgm image data as an Image struct */
    Image *imagePtr = malloc(sizeof(Image)); // dynamically allocate memory for imagePtr
    createNewImage(imagePtr); // fills imagePtr struct field values with NULL data 

    /* Read data from input file, store data in imagePtr                */
    /* Only return r (the return value) if it reading wasn't successful */
	if ((r = readpgmFile(argv[1], imagePtr)) != 0) return r;

    /* Reduce the file */
    int reductionFactor = atoi(argv[2]); //get the reduction factor.
    /* Call the write reduced function - return r only if not successful */
    if ((r = writeReduced(argv[3], imagePtr, reductionFactor)) != 0) return r;

	/* at this point, we are done and can exit with a success code */
    printf("REDUCED\n");
	return EXIT_NO_ERRORS;
} /* main() */

/***********************************/
/* FUNC: writeReduced              */
/*                                 */
/* Parameters:                     */
/* - filename: filename string     */
/* - imagePointer: Image pointer   */
/* - reductionFactor: Reduction Factor */
/*                                 */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int writeReduced(char *filename, Image *imagePointer, int reductionFactor)
{
    /* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");

    int r;  //return value variable
    /* check whether file opening worked - return r only if not successful */
    if ((r = checkOutputFile(outputFile, filename, imagePointer->imageData, imagePointer->commentLine)) != 0) return r;
    
    int reducedWidth = (imagePointer->width+reductionFactor-1)/reductionFactor;
    int reducedHeight = (imagePointer->height+reductionFactor-1)/reductionFactor;
    int originalWidth = imagePointer->width;

    /* write magic number, reduced size & gray value */
    size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", imagePointer->magic_number[1], reducedWidth, reducedHeight, imagePointer->maxGray);

	/* check that dimensions wrote correctly - return r only if not successful */
	if ((r = checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten)) != 0) return r;

    /* allocate the data pointer             */
    long nImageBytes = imagePointer->width * imagePointer->height * sizeof(unsigned char);

    unsigned char *nextGrayValue;
    /* int variables to track width and height of imageData iteration */
    int widthCounter = 0;
    int heightCounter = 0;
    /* pointer for efficient write code      */
    for (nextGrayValue = imagePointer->imageData; nextGrayValue < imagePointer->imageData + nImageBytes; nextGrayValue++)
    { /* per gray value */
        /* get next char's column        */
		int nextCol = (nextGrayValue - imagePointer->imageData + 1) % imagePointer->width;
        
        /* create newCol variable        */
        int newCol = 1;

        /* IF: widthCounter MOD reductionFactor = 0 AND heightCounter MOD reductionFactor = 0 */
        /* then store this pixel */
        if (widthCounter%reductionFactor==0 && heightCounter%reductionFactor==0)
        {
            /* check whether the pixel pointer has reached the end of reduced width (i.e, the end of a reduced size row)*/
            if ((widthCounter+reductionFactor+1) > originalWidth)
            {
                /* if so -> newCol is True (i.e, =0) */
                newCol = 0;
            }

            /* check whether you are writing in ASCII or binary format */
            if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
            {
                /* write the entry & whitespace  */
                nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (newCol ? ' ' : '\n'));
            }
            else 
            {
                /* write the entry to disk in binary  */
                fwrite(nextGrayValue, 1, 1, outputFile);
            }
        }
        
		/* sanity check on write - return r only if not successful */
		if ((r = checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten)) != 0) return r;

        /* check whether the pixel pointer has reached the end of the original files width (i.e, the end of a row)*/
        if(nextCol == 0)
        {
            /* has reached end of row */ 
            heightCounter++; //increment heightCounter, as we are moving to a new row.
            widthCounter=0; //widthCounter set back to column 0.
        }
        else
        {
            /* hasn't reached end of row */ 
            widthCounter++; //increment widthCounter, as we are moving to a new column in the same row.
        }
    } /* per gray value */
    /* no errors so exit with return with success code */
    return EXIT_NO_ERRORS;
}