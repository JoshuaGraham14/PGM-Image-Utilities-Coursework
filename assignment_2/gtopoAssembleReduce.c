/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_2                    */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 22/05/22        */
/***********************************/

/***********************************/
/* Assembles a large image from    */
/* smaller ones and then reduces   */
/* the large image by the reduction*/
/* factor.                         */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* Libraries */
#include <stdio.h> //library for I/O routines
#include <stdlib.h> //library for memory routines
#include <string.h> //library for string manipulation

/* Header files */
#include "gtopoImage.h"
#include "gtopoErrors.h"

/* FUNC: checks the number of arguments is correct */
int checkArgumentCountAssembleReduce(int argc);

/***********************************/
/* main routine                    */
/*                                 */
/* 5+5i CLI parameters:            */
/* argv[0]: executable name        */
/* argv[1]: output file name       */
/* argv[2]: width of output image  */
/* argv[3]: height of output image */
/* argv[4]: reduction factor       */
/* Remainder: quintuplets of:      */
/* argv[3i+1]: start row position  */
/* argv[3i+2]: start column position */
/* argv[3i+3]: subimage to insert  */
/* argv[3i+4]: width of subimage   */
/* argv[3i+5]: height of subimage  */
/*                                 */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{ /* main() */

    /* check for correct number of arguments */
    int returnVal; //return value variable
    /* check if there were correct CLI arguments   */
	if((returnVal = checkArgumentCountAssembleReduce(argc)) != 0)
    {
        /* if there weren't correct CLI arguments:   */
        if (returnVal == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: ./%s outputArray.gtopo width height (row column inputArray.gtopo width height)+\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() method */
        return returnVal;
    }
	
	/* create an imagePtr to store the main gtopo image data as an Image struct */
    Image *mainImage = malloc(sizeof(Image)); // dynamically allocate memory for mainImage

    /* first validate the width and height of the mainImage, returning if they are not valid */
	if ((returnVal = validateWidthAndHeight(argv[2], argv[3])) != 0) return returnVal;

    /* now that the inputted width and height have been validated, we can initialise the width and height and allocate memory for the Image's imageData */
    initialiseImage(mainImage, argv[2], argv[3]); //initialise the fields of the Image
    mallocImageDataArray(mainImage); //allocate memory for the Image's imageData

    /* create another Image as a temporary store of the image to insert's data */
    Image *subImage = malloc(sizeof(Image)); // dynamically allocate memory for subImage

    /* ----- ASSEMBLE TO MEMORY ----- */

    /* iterate through quintuplets of command line arguments */
    for (int quintupletIndex = 5; quintupletIndex<argc-5; quintupletIndex+=5)
    {
        /* NOTE: */
        /* argv[quintupletIndex]:  start row position     */
        /* argv[quintupletIndex+1]: start column position */
        /* argv[quintupletIndex+2]: subimage to insert    */
        /* argv[quintupletIndex+3]: width of subimage     */
        /* argv[quintupletIndex+4]: height of subimage    */

        /* first validate the row and column position of the subImage, returning if they are not valid */
	    if ((returnVal = validateRowAndColumnPosition(argv[quintupletIndex], argv[quintupletIndex+1])) != 0) return returnVal;

        /* Read data from input subImage file and store data in subImage */
	    if ((returnVal = readGtopoFile(argv[quintupletIndex+2], subImage, argv[quintupletIndex+3], argv[quintupletIndex+4])) != 0) return returnVal;

        /* define for-loop variable counters: */
        int rowIndex;
        int columnIndex;
        /* nested iteratation through each element/pixelValue in the imageData array */
        for (rowIndex = 0; rowIndex < subImage->height; rowIndex++)
        { /*per row of pixels*/
            for (columnIndex = 0; columnIndex < subImage->width; columnIndex++)
            { /*per pixel*/

                /* replace pixel of mainImage with the corresponding pixel of the subImage */
                mainImage->imageData[atoi(argv[quintupletIndex])+rowIndex][atoi(argv[quintupletIndex+1])+columnIndex] = subImage->imageData[rowIndex][columnIndex];

            } /*per pixel*/
        }
    }

    /* ----- REDUCE AND WRITE TO FILE ----- */

    int reductionFactor = atoi(argv[4]); //get the reduction factor.
    /* Call the writeGtopoFile function with the 3rd parameter being the reduction factor */
    if ((returnVal = writeGtopoFile("testfile.dem", mainImage, reductionFactor)) != 0) return returnVal;

	/* at this point, we are done and can exit with a success code */
    printf("REDUCED\n");
	return EXIT_NO_ERRORS;
} /* main() */

/******************************************/
/* FUNC: checkArgumentCountAssembleReduce */
/* -> checks the number of arguments      */
/* supplied against the specified number  */
/* of arguments.                          */
/*                                        */
/* Parameters:                            */
/* - argc: integer num of arguments       */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int checkArgumentCountAssembleReduce(int argc)
{
    /* Check that the number of arguments are at least 10 and that */
    /* in addition to the first 5 mandatory arguments, check that */
    /* additional arguments are only provided in quintuplets (i.e.*/
    /* must be divisible by 5).                                   */
    if (argc < 10 || (argc-5)%5 != 0)
    { /* wrong arg count */
        /* IF there were no arguments */
        if (argc == 1) return -1;

        /* ELSE output error message and return with error code */ 
        printf("ERROR: Bad Argument Count\n");
        return ERROR_BAD_ARGUMENT_COUNT;
    } /* wrong arg count */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}