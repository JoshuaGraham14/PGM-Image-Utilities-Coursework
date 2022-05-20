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


/******************************************/
/* FUNC: readpgmFile                      */
/* -> collection of other gtopoImage      */
/* methods - used to read in a pgmFile.   */
/*                                        */
/* Parameters:                            */
/* - filename: char pointer               */
/* - imagePointer: Image pointer          */
/* - width: char pointer to CL argument   */
/* - height: char pointer to CL argument  */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int readGtopoFile(char *filename, Image *imagePointer, char *width, char *height)
{
    FILE *filePointer = fopen(filename, "r"); //open file in read mode.

    /* NOTE: for the following functions, return the return value of the function only if it was not successful */
    // **********************************************************************************************************
    int returnVal; //return value variable.

    /* fills imagePtr struct field values with NULL data */
    if ((returnVal = createNewImage(imagePointer, width, height)) != 0) return returnVal;

    /* check the input file to see if can be opened*/
    if ((returnVal = checkInputFile(filePointer)) != 0) return returnVal;

    /* read the image data: */
    if ((returnVal = readImageData(filePointer, imagePointer)) != 0) return returnVal;

    /* we're done with the file, so close it */
    fclose(filePointer);
    return EXIT_NO_ERRORS; //success
}

/******************************************/
/* FUNC: createNewImage                   */
/* -> fills imagePointer with NULL data   */
/* values for Image struct.               */
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer          */
/* - width: char pointer to CL argument   */
/* - height: char pointer to CL argument  */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int createNewImage(Image *imagePointer, char *width, char *height)
{
    int returnVal; //return value variable.

    /* first validate the width  and height */
	if ((returnVal = validateWidthAndHeight(width, height)) != 0) return returnVal;

    //if width and height provided are valid:
    imagePointer->width=atoi(width);
    imagePointer->height=atoi(height);
    imagePointer->imageData=NULL;

    return EXIT_NO_ERRORS; //return with success code
}

/******************************************/
/* FUNC: readImageData                    */
/* -> reads the Image data from the       */
/* file and stores the data in the        */
/* imagePointer struct in the imageData   */
/* field.                                 */
/*                                        */
/* Parameters:                            */
/* - filePointer: FILE pointer to read    */
/* - imagePointer: Image pointer          */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int readImageData (FILE *filePointer, Image *imagePointer)
{
    int returnVal; //return value variable created

    /* Calls func to dynamically allocate memory for the imageData 2d array, returning returnVal on error. */
    if ((returnVal = mallocImageDataArray(imagePointer)) != 0) return returnVal;

    /* Variables which store data during for-loop: */
    int pixelValue;
    //int scanCount = 1;

    /* define for-loop variable counters: */
    int columnIndex;
    int rowIndex;

    for (columnIndex = 0; columnIndex < imagePointer->height; columnIndex++)
    {
        for (rowIndex = 0; rowIndex < imagePointer->width; rowIndex++)
        {
            /* read pixel value by calling readValue() func */
            pixelValue = readValue(filePointer);
            //printf("%d ", pixelValue);
            //printf("\nx: %d ", x);
            //printf("\tNextpixelvalue: %d ", nextPixelValue);
            //printf("\tpixelValue: %d ", pixelValue);
            //printf("\tmax: %d ", (imagePointer->imageData + nImageBytes));

            /* sanity check that the pixelValue is valid */
            if ((returnVal = checkPixelValue(imagePointer, pixelValue)) != 0) return returnVal;

            /* Set corresponding index in the imageData 2d array to the pixelValue which has just been read */ 
            imagePointer->imageData[columnIndex][rowIndex] = pixelValue;
        }
    }

    /* return with success code */ 
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: mallocImageDataArray             */
/* -> dynamically allocates memory to the */
/* imageData array. This func is called   */
/* just before reading the pixel data     */
/* from the input pgm file.               */
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer          */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int mallocImageDataArray(Image *imagePointer)
{
    int returnVal; //return value variable created

    /* dynamically allocate memory to imageData 2d array */
    imagePointer->imageData = malloc(imagePointer->height * sizeof(*imagePointer->imageData));
    /* sanity check for memory allocation for the whole 2d array */
    if ((returnVal = check2dImageDataMemoryAllocation(imagePointer)) != 0) return returnVal;

	/* define for-loop variable counter: */
    int pointerIndex;
    /* iterate through each row in the 2d array */
    for (pointerIndex = 0; pointerIndex < imagePointer->height; pointerIndex++)
    {
        /* dynamically allocate memory for each row in 2d array */
        imagePointer->imageData[pointerIndex] = malloc (imagePointer->width * sizeof(unsigned char));
        /* sanity check for memory allocation for this row of the array */
        if ((returnVal = check1dImageDataMemoryAllocation(imagePointer, pointerIndex)) != 0) return returnVal;
    }

    return EXIT_NO_ERRORS;
}

/*******************************************/
/* FUNC: writepgmFile                      */
/* -> writes the data from the imagePointer*/
/* struct to the file with the input       */
/* filename. If the reductionFactor        */
/* parameter != 1, then the file is reduced*/
/* by that factor.                         */
/*                                         */
/* Parameters:                             */
/* - filename: filename string             */
/* - imagePointer: Image pointer           */
/* - reductionFactor: Reduction Factor     */
/*                    (1 = no reduction)   */
/* Returns: - 0 on success                 */
/*          - non-zero error code on fail  */
/*******************************************/
int writeGtopoFile(char *filename, Image *imagePointer, int reductionFactor)
{
    /* open a file for writing */
	FILE *outputFile = fopen(filename, "w");

    int returnVal;  //return value variable
    /* check whether file opening worked - return returnVal only if not successful */
    if ((returnVal = checkOutputFile(outputFile)) != 0) return returnVal;

    /* Create variables which store the width and height of the image after it has been reduced */
    int reducedWidth = (imagePointer->width+reductionFactor-1)/reductionFactor;
    int reducedHeight = (imagePointer->height+reductionFactor-1)/reductionFactor;

     /* define for-loop variable counters: */
    int columnIndex;
    int rowIndex;

    /* nested iteratation through each element/pixelValue in the imageData array,   */
    /* BUT each loop increments by the reductionFactor in order to reduce the image */
    for (columnIndex = 0; columnIndex < imagePointer->height; columnIndex+=reductionFactor)
    { /*per row of pixels*/
        for (rowIndex = 0; rowIndex < imagePointer->width; rowIndex+=reductionFactor)
        { /*per pixel*/
            
            writeValue(outputFile, &imagePointer->imageData[columnIndex][rowIndex]);

            /* sanity check on write, by calling checknBytesWritten */
            //if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return returnVal;

        } /*per pixel*/
    } /*per row of pixels*/

    return EXIT_NO_ERRORS;
}

/* FUNC: gets the size of a gtopo Image */
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

/* FUNC: reads the next value from the provided file and returns it */
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

/* FUNC: writes the provided pixel (valueToWrite) to the provided file */
void writeValue(FILE *filePointer, short *valueToWrite)
{
    char c1 = *valueToWrite >> 8;
    char c2 = *valueToWrite & 0x00ff;

    // printf("\nc1: %d", c1);
    // printf("\tc2: %d", c2);

    fwrite(&c1, 1, 1, filePointer);
    fwrite(&c2, 1, 1, filePointer);
}