/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_2                    */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 04/05/22        */
/***********************************/

/***********************************/
/* Module for handling gtopo Image */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* Libraries */
#include <stdio.h> //library for I/O routines
#include <stdlib.h> //library for memory routines
#include <math.h> //library for maths functions
#include <string.h> //library for string manipulation

/* Header files */
#include "gtopoErrors.h"
#include "gtopoImage.h"

/* FUNC: fills imagePointer with NULL data values for Image struct */
void createNewImage(Image *imagePointer)
{
    imagePointer -> width=0;
    imagePointer -> height=0;
    imagePointer->imageData=NULL;
}

/* FUNC: collection of other pgmImage methods - used to read in a pgmFile */
int readGtopoFile(char *filename, Image *imagePointer)
{
    FILE *inputFile = fopen(filename, "r"); //open file in read mode.

    return EXIT_NO_ERRORS; //success
}

/* FUNC: writes to an input file data from an input Image */
int writeGtopoFile(char *filename, Image *imagePointer)
{
    return EXIT_NO_ERRORS;
}