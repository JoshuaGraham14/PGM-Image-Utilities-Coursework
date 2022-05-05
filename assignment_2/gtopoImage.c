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
int createNewImage(Image *imagePointer, char *width, char *height)
{
    int r; //return value variable.
	if ((r = checkWidthAndHeight(width, height)) != 0) return r;

    //if width and height provided are valid
    imagePointer->width =atoi(width);
    imagePointer->height=atoi(height);
    imagePointer->imageData=NULL;

    return EXIT_NO_ERRORS;
}

/* FUNC: collection of other pgmImage methods - used to read in a pgmFile */
int readGtopoFile(char *filename, Image *imagePointer)
{
    FILE *filePointer = fopen(filename, "r"); //open file in read mode.

    int r; //return value variable.
    if ((r = checkInputFile(filePointer, filename)) != 0) return r;

    short x;

    for (int i=0; i<imagePointer->height; i++)
    {
        for (int j=0; j<imagePointer->width; j++)
        {
            short x = readValue(filePointer);
            printf("%d ", x);
        }
        printf("\n");
    }

    return EXIT_NO_ERRORS; //success
}

/* FUNC: writes to an input file data from an input Image */
int writeGtopoFile(char *filename, Image *imagePointer)
{
    return EXIT_NO_ERRORS;
}

short readValue(FILE *filePointer)
{
    int left8bit;
    int right8bit;
    int scanCount;

    left8bit = 0;
    scanCount = fread(&left8bit, 1, 1, filePointer);
    left8bit -= 256;
    right8bit = 0;
    scanCount = fread(&right8bit, 1, 1, filePointer);
    right8bit -= 256;
    int16_t positiveRight8bit = right8bit & 255; //remove negative
    int16_t result = (left8bit << 8) | positiveRight8bit; // shift by 8 then join with right positiveRight8bit.

    return result;
}