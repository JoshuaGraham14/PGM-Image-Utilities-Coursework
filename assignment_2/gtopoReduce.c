/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_2                    */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 12/05/22        */
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
#include "gtopoErrors.h"
#include "gtopoImage.h"

//writeReduced function declared
int writeReduced(char *filename, Image *imagePointer, int reductionFactor);

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */ 
/* argv[2]: width                  */
/* argv[3]: height                 */
/* argv[4]: reduction_factor       */
/* argv[5]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{ /* main() */

    /* check for correct number of arguments */
    int r; //return value variable
    /* check if there were 6 CLI arguments   */
	if((r = checkArgumentCount(argc, 6)) != 0)
    {
        /* if there weren't 4 CLI arguments:   */
        if (r == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: %s input width height reduction_factor output\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() method */
        return r;
    }

    /* Check reduction factor is valid */
    if((r = checkReductionFactor(argv[4])) != 0) return r;
	
	/* create an imagePtr to store the pgm image data as an Image struct */
    Image *imagePtr = malloc(sizeof(Image)); // dynamically allocate memory for imagePtr
    if ((r = createNewImage(imagePtr, argv[2], argv[3])) != 0) return r; // fills imagePtr struct field values with NULL data

    /* Read data from input file, store data in imagePtr                */
    /* Only return r (the return value) if it reading wasn't successful */
	if ((r = readGtopoFile(argv[1], imagePtr)) != 0) return r;

    /* Reduce the file */
    int reductionFactor = atoi(argv[2]); //get the reduction factor.
    /* Call the write reduced function - return r only if not successful */
    if ((r = writeReduced(argv[5], imagePtr, reductionFactor)) != 0) return r;

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

    int height = imagePointer->height;
    int width = imagePointer->width;

    int r;  //return value variable
    /* check whether file opening worked - return r only if not successful */
    if ((r = checkOutputFile(outputFile, filename, imagePointer->imageData, height)) != 0) return r;

    int i;
    int j;
    for (i = 0; i < height; i+=reductionFactor)
    {
        for (j = 0; j < width; j+=reductionFactor)
        {
            writeValue(outputFile, &imagePointer->imageData[i][j]);
        }
    }
    
    /* no errors so exit with return with success code */
    return EXIT_NO_ERRORS;
}