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

    //int n = getImageSize(filePointer);
    //printf("\nImage Size: %d\n", n);

    if ((r = readImageData(filePointer, filename, imagePointer)) != 0) return r;

    /* we're done with the file, so close it */
    fclose(filePointer);
    return EXIT_NO_ERRORS; //success
}

/* FUNC: reads the Image imageData */
int readImageData (FILE *filePointer, char *filename, Image *imagePointer)
{
    /* allocate the data pointer             */
	long nImageBytes = imagePointer->width * imagePointer->height * (sizeof(short));
	imagePointer->imageData = (short*) malloc(nImageBytes);

    /* sanity check for memory allocation    */
    int r; //return value variable.
	if ((r = checkImageDataMemoryAllocation(filePointer, filename, imagePointer->imageData) != 0)) return r;
    
    // short x;
    
    // for (int i=0; i<imagePointer->height; i++)
    // {
    //     for (int j=0; j<imagePointer->width; j++)
    //     {
    //         x = readValue(filePointer);
    //         printf("%d ", x);
    //     }
    //     printf("\n");
    // }

    short *nextPixelValue; //assign pointer

    int pixelValue;
    int scanCount = 1;

    for (nextPixelValue = imagePointer->imageData; nextPixelValue < imagePointer->imageData + nImageBytes; nextPixelValue++)
    { /* per pixel value */
        pixelValue = readValue(filePointer);
        //printf("%d ", pixelValue);

        if ((r = checkPixelValue(filePointer, filename, imagePointer->imageData, pixelValue) != 0)) return r;

        *nextPixelValue = (short) pixelValue;
    }

    return EXIT_NO_ERRORS;
}

/* FUNC: writes to an input file data from an input Image */
int writeGtopoFile(char *filename, Image *imagePointer)
{
    //printf("\nWRITE: \n");
    /* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");
 
    /* check whether file opening worked     */
    int r;
    if ((r = checkOutputFile(outputFile, filename, imagePointer->imageData)) != 0) return r;

    /* allocate the data pointer             */
    long nImageBytes = imagePointer->width * imagePointer->height;

    short *nextPixelValue; //assign pointer

    for (nextPixelValue = imagePointer->imageData; nextPixelValue < imagePointer->imageData + nImageBytes; nextPixelValue++)
    { /* per pixel value */
        printf("%d ", *nextPixelValue);
        //writeValue(outputFile, nextPixelValue);
        
        /* sanity check on write         */
		if ((r = checknBytesWritten(outputFile, filename, imagePointer->imageData)) != 0) return r;
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
    // uint8_t bytes [sizeof(int)] = 
    // {
    //     ((short)*valueToWrite >> 0) & 0xFF,  // shift by 0 not needed, of course, just stylistic
    //     ((short)*valueToWrite >> 8) & 0xFF,
    // };

    // //printf("%d ", bytes[1]);
    // //printf("%d ", bytes[0]);

    // unsigned char *byte1 = &bytes[0];
    // unsigned char *byte2 = &bytes[1];

    // fwrite(byte2, 1, 1, filePointer);
    // fwrite(byte1, 1, 1, filePointer);
}