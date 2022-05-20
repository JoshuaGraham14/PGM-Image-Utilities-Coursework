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

    int height = imagePointer->height;
    int width = imagePointer->width;

    int returnVal;  //return value variable
    /* check whether file opening worked - return r only if not successful */
    if ((returnVal = checkOutputFile(outputFile)) != 0) return returnVal;
    
    int reducedWidth = (imagePointer->width+reductionFactor-1)/reductionFactor;
    int reducedHeight = (imagePointer->height+reductionFactor-1)/reductionFactor;

    /* write magic number, reduced size & gray value */
    size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", imagePointer->magic_number[1], reducedWidth, reducedHeight, imagePointer->maxGray);

	/* check that dimensions wrote correctly - return r only if not successful */
	if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return returnVal;

    int i;
    int j;
    for (i = 0; i < height; i+=reductionFactor)
    {
        for (j = 0; j < width; j+=reductionFactor)
        {
            //printf("%d ", imagePointer->imageData[i][j]);
            /* write the entry & whitespace  */
            if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
            {
                nBytesWritten = fprintf(outputFile, "%d ", imagePointer->imageData[i][j]);
            }
            else 
            {
                //printf("\n%d, %d", imagePointer->imageData[i][j], &imagePointer->imageData[i][j]);
                fwrite(&imagePointer->imageData[i][j], 1, 1, outputFile);
            }

            /* sanity check on write         */
            if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return returnVal;
        }
        if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
        {
            fprintf(outputFile, "%c", '\n');
        }
    }
    
    /* no errors so exit with return with success code */
    return EXIT_NO_ERRORS;
}