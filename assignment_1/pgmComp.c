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

/* Constants */
#define EXIT_NO_ERRORS 0

//compareImages function declared
void compareImages(Image *inputImage1, Image *inputImage2);

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
    int r; //return value variable
    /* check if there were 3 CLI arguments   */
	if((r = checkArgumentCount(argc, 3)) != 0)
    {
        /* if there weren't 3 CLI arguments:   */
        if (r == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() method */
        return r;
    }

	/* create an imagePtr to store the pgm image data as an Image struct */
    Image *imagePtr1 = malloc(sizeof(Image)); // dynamically allocate memory for imagePtr
    createNewImage(imagePtr1); // fills imagePtr1 struct field values with NULL data 

    /* do the same for imagePtr2/second input file */
    Image *imagePtr2 = malloc(sizeof(Image));
    createNewImage(imagePtr2);

    /* Read data from both input files and only return r (the return value) if it wasn't successful */
	if ((r = readpgmFile(argv[1], imagePtr1)) != 0) return r;
    if ((r = readpgmFile(argv[2], imagePtr2)) != 0) return r;

    /* Compare the two files: */
    compareImages(imagePtr1, imagePtr2);
	return EXIT_NO_ERRORS;
} /* main() */

/***********************************/
/* FUNC: compareImages             */
/*                                 */
/* Parameters:                     */
/* - inputImage1: Image pointer    */
/* - inputImage2: Image pointer    */
/*                                 */
/* prints "DIFFERENT" if inputs    */
/* are different or prints         */
/* "IDENTICAL" if inputs are       */
/* identical                       */
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
        return;
    }

    //COMPARE: image data
    /* iterate through each imageData array from each input */
    /* file simultaneously and compare the two values       */
    long nImageBytes = inputImage1->width * inputImage1->height * sizeof(unsigned char);
    int i;
    for (i = 0; i<nImageBytes; i++)
    {
        /* check if the current pixel from each file match */
        if(inputImage1->imageData[i] != inputImage2->imageData[i])
        {
            /* files are different */
            printf("DIFFERENT\n");
            return;
        }
    }
    /* if no differences found -> files are identical */
    printf("IDENTICAL\n");
}