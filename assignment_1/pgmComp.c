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
/* Reads two pgm files and compares*/
/* them to see if they are         */
/* logically equivalent.           */ 
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

//compareImages function declared
void compareImages(Image *inputImage1, Image *inputImage2);

/***********************************/
/* main routine                    */
/*                                 */
/* 3 CLI parameters:               */
/* argv[0]: executable name        */
/* argv[1]: 1st input file name    */
/* argv[2]: 2nd input file name    */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{ /* main() */

	/* check for correct number of arguments */
    int returnVal; //return value variable
    /* check if there were 3 CLI arguments   */
	if((returnVal = checkArgumentCount(argc, 3)) != 0)
    {
        /* if there weren't 3 CLI arguments:   */
        if (returnVal == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: %s inputImage.pgm inputImage.pgm\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() method */
        return returnVal;
    }

	/* create an imagePtr to store the pgm image data as an Image struct */
    Image *imagePtr1 = malloc(sizeof(Image)); // dynamically allocate memory for imagePtr
    createNewImage(imagePtr1); // fills imagePtr1 struct field values with NULL data 

    /* do the same for imagePtr2/second input file */
    Image *imagePtr2 = malloc(sizeof(Image));
    createNewImage(imagePtr2);

    /* Read data from both input files and only return returnVal if it wasn't successful (i.e. func doesn't return 0) */
	if ((returnVal = readpgmFile(argv[1], imagePtr1, 0)) != 0) return returnVal;
    if ((returnVal = readpgmFile(argv[2], imagePtr2, 0)) != 0) return returnVal;

    /* Compare the two files: */
    compareImages(imagePtr1, imagePtr2);
	return EXIT_NO_ERRORS;
} /* main() */

/***********************************/
/* FUNC: compareImages             */
/* -> compares the two input image */
/* pointers and prints "DIFFERENT" */
/* if inputs are different or      */
/* prints "IDENTICAL" if inputs are*/
/* identical.                      */
/*                                 */
/* Parameters:                     */
/* - inputImage1: Image pointer    */
/* - inputImage2: Image pointer    */
/* Returns: (none)                 */
/***********************************/
void compareImages(Image *inputImage1, Image *inputImage2)
{
    //COMPARE: magic number, width, height & maxGray
    if (!(
    strcmp((const char *)inputImage1->magic_number, (const char *)inputImage2->magic_number) == 0 ||
    inputImage1->width==inputImage2->width ||
    inputImage1->height==inputImage2->height ||
    inputImage1->maxGray==inputImage2->maxGray
    ))
    {
        /* files are different */
        printf("DIFFERENT\n");
        return; //exit function
    }

    //COMPARE: image data
    
    /* define for loop variables: */
    int columnIndex;
    int rowIndex;

    /* iterate through each imageData array from each input image */
    /* file simultaneously and compare the two values.            */
    for (columnIndex = 0; columnIndex < inputImage1->height; columnIndex++)
    {
        for (rowIndex = 0; rowIndex < inputImage1->width; rowIndex++)
        {
            /* IF: the data at the same position in each of the images 2d imageData */
            /* array are not equivalent, then the images are different.             */                                             
            if(inputImage1->imageData[columnIndex][rowIndex] != inputImage2->imageData[columnIndex][rowIndex])
            {
                /* files are different */
                printf("DIFFERENT\n");
                return; //exit function
            }
        }
    }

    /* if no differences found -> files are identical */
    printf("IDENTICAL\n");
}