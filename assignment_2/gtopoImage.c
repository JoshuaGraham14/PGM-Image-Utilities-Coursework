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

    if ((r = readImageData(filePointer, filename, imagePointer)) != 0) return r;

    /* we're done with the file, so close it */
    fclose(filePointer);
    return EXIT_NO_ERRORS; //success
}

/* FUNC: reads the Image imageData */
int readImageData (FILE *filePointer, char *filename, Image *imagePointer)
{
    int height = imagePointer->height;
    int width = imagePointer->width;
    int r;

    /* allocate the data pointer             */
    imagePointer->imageData = malloc(height * sizeof(*imagePointer->imageData));
    /* sanity check for memory allocation    */
    if ((r = check2dImageDataMemoryAllocation(filePointer, filename, imagePointer->imageData)) != 0) return r;
	int i;
    int j;
    for (i = 0; i < height; i++)
    {
        imagePointer->imageData[i] = malloc (width * sizeof(short));
        if ((r = check1dImageDataMemoryAllocation(filePointer, filename, imagePointer->imageData[i])) != 0) return r;
    }

    //Read data:
    short pixelValue;
    int scanCount = 1;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            pixelValue = readValue(filePointer);
            //printf("%d ", pixelValue);
            // printf("\nx: %d ", x);
            // printf("\tNextpixelvalue: %d ", nextPixelValue);
            // printf("\tpixelValue: %d ", pixelValue);
            // printf("\tmax: %d ", (imagePointer->imageData + nImageBytes));

            if ((r = checkPixelValue(filePointer, filename, imagePointer->imageData, pixelValue, height) != 0)) return r;

            imagePointer->imageData[i][j] = pixelValue;
        }
    }

    return EXIT_NO_ERRORS;
}

/* FUNC: writes to an input file data from an input Image */
int writeGtopoFile(char *filename, Image *imagePointer)
{
    //printf("\nWRITE: \n");
    /* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");

    int height = imagePointer->height;
    int width = imagePointer->width;
 
    /* check whether file opening worked     */
    int r;
    if ((r = checkOutputFile(outputFile, filename, imagePointer->imageData, height)) != 0) return r;

    int i;
    int j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            writeValue(outputFile, &imagePointer->imageData[i][j]);

            if ((r = checknBytesWritten(outputFile, filename, imagePointer->imageData, height)) != 0) return r;
        }
    }

    return EXIT_NO_ERRORS;
}

int getImageSize(FILE *filePointer)
{
    short x=1;
    int t = 0;

    while (x!=0)
    {
        t+=1;
        x = readValue(filePointer);
    }

    return t-1;
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
    short positiveRight8bit = right8bit & 255; //remove negative
    short result = (left8bit << 8) | positiveRight8bit; // shift by 8 then join with right positiveRight8bit.

    return result;
}

void writeValue(FILE *filePointer, short *valueToWrite)
{
    char c1 = *valueToWrite >> 8;
    char c2 = *valueToWrite & 0x00ff;

    // printf("\nc1: %d", c1);
    // printf("\tc2: %d", c2);

    fwrite(&c1, 1, 1, filePointer);
    fwrite(&c2, 1, 1, filePointer);
}