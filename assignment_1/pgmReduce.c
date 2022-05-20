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

/***********************************/
/* main routine                    */
/*                                 */
/* 4 CLI parameters:               */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: int reduction factor   */
/* argv[3]: ouput file name        */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{ /* main() */

    /* check for correct number of arguments */
    int returnVal; //return value variable
    /* check if there were 4 CLI arguments   */
	if((returnVal = checkArgumentCount(argc, 4)) != 0)
    {
        /* if there weren't 4 CLI arguments:   */
        if (returnVal == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: %s inputImage.pgm reduction_factor outputImage.pgm\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() method */
        return returnVal;
    }

    /* Check reduction factor is valid */
    if((returnVal = validateFactorInput(argv[2])) != 0) return returnVal;
	
	/* create an imagePtr to store the pgm image data as an Image struct */
    Image *imagePtr = malloc(sizeof(Image)); // dynamically allocate memory for imagePtr

    /* Read data from input file, store data in imagePtr                */
    /* Only return r (the return value) if it reading wasn't successful */
	if ((returnVal = readpgmFile(argv[1], imagePtr, 0)) != 0) return returnVal;

    /* Reduce the file */
    int reductionFactor = atoi(argv[2]); //get the reduction factor.
    /* Call the write reduced function - return r only if not successful */
    if ((returnVal = writeReduced(argv[3], imagePtr, reductionFactor)) != 0) return returnVal;

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
/* Returns: 0 on success           */
/* non-zero error code on fail     */
/*                                 */
/* Purpose:                        */
/* Writes the input image to the   */
/* input filname, but reducing the */
/* image by a factor of            */
/* (reductionFactor) parameter     */
/***********************************/
int writeReduced(char *filename, Image *imagePointer, int reductionFactor)
{
    /* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");

    int returnVal;  //return value variable
    /* check whether file opening worked - return returnVal only if not successful */
    if ((returnVal = checkOutputFile(outputFile)) != 0) return returnVal;
    
    /* Create variables which store the width and height of the image after it has been reduced */
    int reducedWidth = (imagePointer->width+reductionFactor-1)/reductionFactor;
    int reducedHeight = (imagePointer->height+reductionFactor-1)/reductionFactor;

    /* write magic number, reduced size & gray value */
    size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", imagePointer->magic_number[1], reducedWidth, reducedHeight, imagePointer->maxGray);

	/* check that dimensions wrote correctly - only return returnVal if not successful */
	if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return returnVal;

    /* define for-loop variable counters: */
    int columnIndex;
    int rowIndex;

    /* nested iteratation through each element/pixelValue in the imageData array,   */
    /* BUT each loop increments by the reductionFactor in order to reduce the image */
    for (columnIndex = 0; columnIndex < imagePointer->height; columnIndex+=reductionFactor)
    {
        for (rowIndex = 0; rowIndex < imagePointer->width; rowIndex+=reductionFactor)
        {
            /* IF: the image is in ASCII format:   */
            if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
            {
                /* write the entry & whitespace  */
                nBytesWritten = fprintf(outputFile, "%d ", imagePointer->imageData[columnIndex][rowIndex]);
            }
            /* ELSE: the image is in binary format: */
            else 
            {
                /* write the entry in binary */
                fwrite(&imagePointer->imageData[columnIndex][rowIndex], 1, 1, outputFile);
            }

            /* sanity check on write by calling checknBytesWritten */
            if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return returnVal;
        }

        /* If the image is in ASCII format add a newline at the end of row column cycle */
        if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
        {
            fprintf(outputFile, "%c", '\n');
        }
    }
    
    /* no errors so exit with success return code */
    return EXIT_NO_ERRORS;
}