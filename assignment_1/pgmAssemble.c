/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_1                    */
/* TASK VI                         */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 13/03/22        */
/***********************************/

/***********************************/
/* Assembles a large image from    */
/* smaller ones.                   */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* Libraries */
#include <stdio.h> //library for I/O routines
#include <stdlib.h> //library for memory routines
#include <string.h> //library for string manipulation

/* Header files */
#include "pgmImage.h"
#include "pgmErrors.h"

/* NOTE: the following 4 functions are declared locally, rather than */
/* declared in pgmImage.c, because pgmAssemble.c is the only file    */
/* which uses this function.                                         */

/* FUNC: checks the number of arguments is correct */
int checkArgumentCountAssemble(int argc);

/* FUNC: checks if the inputted width and height are both integers and greater than 0 */
int validateWidthAndHeight(char *width, char *height);

/* FUNC: checks that both inputted row and column of the subimage are both integers and greater than or equal to 0 */
int validateRowAndColumnPosition(char *row, char *column);

/***********************************/
/* main routine                    */
/*                                 */
/* 4+3i CLI parameters:            */
/* argv[0]: executable name        */
/* argv[1]: output file name       */
/* argv[2]: width of output image  */
/* argv[3]: height of output image */
/* Remainder: triplets of:         */
/* argv[3i+1]: start row position  */
/* argv[3i+2]: start column position */
/* argv[3i+3]: subimage to insert  */
/*                                 */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{ /* main() */

    /* check for correct number of arguments */
    int returnVal; //return value variable
    /* check if there were correct CLI arguments   */
	if((returnVal = checkArgumentCountAssemble(argc)) != 0)
    {
        /* if there weren't correct CLI arguments:   */
        if (returnVal == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: %s outputImage.pgm width height (row column inputImage.pgm)+\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() method */
        return returnVal;
    }
	
	/* create an imagePtr to store the main pgm image data as an Image struct */
    Image *mainImage = malloc(sizeof(Image)); // dynamically allocate memory for mainImage
    initialiseImage(mainImage); //initialise the fields of the Image to NULL

    /* first validate the width and height of the mainImage, returning if they are not valid */
	if ((returnVal = validateWidthAndHeight(argv[2], argv[3])) != 0) return returnVal;
    /* now that the inputted width and height have been validated, we can allocate memory for the Image's imageData */
    mallocImageDataArray(mainImage, atoi(argv[2]), atoi(argv[3]));
    mainImage->width=atoi(argv[2]); //set the width of the mainImage
    mainImage->height=atoi(argv[3]); //set the height of the mainImage

    /* create another Image as a temporary store of the image to insert's data */
    Image *subImage = malloc(sizeof(Image)); // dynamically allocate memory for subImage

    for (int tripletIndex = 4; tripletIndex<argc-2; tripletIndex+=3)
    {
        /* NOTE:                                       */
        /* argv[tripletIndex]: start row position      */
        /* argv[tripletIndex+1]: start column position */
        /* argv[tripletIndex+2]: subimage to insert    */

        /* first validate the inputted row and column position of the subImage, returning if they are not valid */
	    if ((returnVal = validateRowAndColumnPosition(argv[tripletIndex], argv[tripletIndex+1])) != 0) return returnVal;

        /* Read data from the provided filename, and store the data in subImage */
	    if ((returnVal = readpgmFile(argv[tripletIndex+2], subImage, 0)) != 0) return returnVal;

        /* define for-loop variable counters: */
        int rowIndex;
        int columnIndex;
        /* nested iteratation through each element/pixelValue in the imageData array,   */
        /* BUT each loop increments by the reductionFactor in order to reduce the image */
        for (rowIndex = 0; rowIndex < subImage->height; rowIndex++)
        { /*per row of pixels*/
            for (columnIndex = 0; columnIndex < subImage->width; columnIndex++)
            { /*per pixel*/

                /* replace pixel of mainImage with the corresponding pixel of the subImage */
                mainImage->imageData[atoi(argv[tripletIndex])+rowIndex][atoi(argv[tripletIndex+1])+columnIndex] = subImage->imageData[rowIndex][columnIndex];

            } /*per pixel*/
        }
    }

    /* set the magic number and maxGray of the mainImage */
    mainImage->magic_number[0]=subImage->magic_number[0];
    mainImage->magic_number[1]=subImage->magic_number[1];
    mainImage->maxGray=subImage->maxGray;

    /* Write mainImage data to filename, returning returnVal if it wasn't successful */
    if ((returnVal = writepgmFile(argv[1], mainImage, 1)) != 0) return returnVal;

	/* at this point, we are done and can exit with a success code */
    printf("ASSEMBLED\n");
	return EXIT_NO_ERRORS;
} /* main() */

/******************************************/
/* FUNC: checkArgumentCountAssemble       */
/* -> checks the number of arguments      */
/* supplied against the specified number  */
/* of arguments.                          */
/*                                        */
/* Parameters:                            */
/* - argc: integer num of arguments       */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int checkArgumentCountAssemble(int argc)
{
    /* Check that the number of arguments are at least 8 and that */
    /* in addition to the first 4 mandatory arguments, check that */
    /* additional arguments are only provided in triplets (i.e.   */
    /* must be divisible by 3).                                   */
    if (argc <= 7 || (argc-4)%3 != 0)
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

/******************************************/
/* FUNC: validateWidthAndHeight           */
/* ->  checks that inputted width and     */
/* height are both integers and greater   */
/* than zero.                             */
/*                                        */
/* Parameters:                            */
/* - width: char pointer to CL argument   */
/* - height: char pointer to CL argument  */
/* Returns: - 0 on success                */
/*          - ERROR_MISCELLANEOUS on fail */
/******************************************/
int validateWidthAndHeight(char *width, char *height)
{
    /* Check IF width and height are both integers */
    if (atoi(width) && atoi(height))
    {
        /* Convert both width and height to integers */
        int widthInt = atoi(width);
        int heightInt = atoi(height);
        /* Check IF width or height are greater than 0 */
        if (widthInt > 0 && heightInt > 0)
        {
            /* return with success code */
            return EXIT_NO_ERRORS;
        }
    }

    /* ELSE: Unsuccessful, so print an error message: */ 
    printf("ERROR: Miscellaneous (width or height parameter invalid)\n");
    /* and return an error code.         */
    return ERROR_MISCELLANEOUS; 
}

/******************************************/
/* FUNC: validateRowAndColumnPosition     */
/* ->  checks that inputted row and       */
/* column positions are both integers and */
/* greater than zero.                     */
/*                                        */
/* Parameters:                            */
/* - row: char pointer to CL argument   */
/* - column: char pointer to CL argument  */
/* Returns: - 0 on success                */
/*          - ERROR_MISCELLANEOUS on fail */
/******************************************/
int validateRowAndColumnPosition(char *row, char *column)
{
    /* check IF row and column are both integers (including 0)*/
    if ((atoi(row) || strcmp(row, "0") == 0) &&
    (atoi(column) || strcmp(column, "0") == 0))
    {
        /* Convert both width and height to integers */
        int rowInt = atoi(row);
        int columnInt = atoi(column);
        /* check IF row and column are both greater than or equal to 0 */
        if (rowInt >= 0 || columnInt >= 0)
        {
            /* return with success code */
            return EXIT_NO_ERRORS;
        }
    }
    /* print an error message        */
    printf("ERROR: Miscellaneous (row or column parameter invalid)\n");
    /* return an error code          */
    return ERROR_MISCELLANEOUS;
}