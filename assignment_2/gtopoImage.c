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
/* FUNC: readGtopoFile                    */
/* -> collection of other gtopoImage      */
/* methods - used to read in a gtopo File.*/
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
    FILE *inputFile = fopen(filename, "r"); //open file in read mode.

    /* NOTE: for the following functions, return the return value of the function only if it was not successful */
    // **********************************************************************************************************
    int returnVal; //return value variable.

    /* fills imagePtr struct field values with NULL data */
    if ((returnVal = initialiseImage(imagePointer, width, height)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);

    /* check the input file to see if can be opened*/
    if ((returnVal = checkInputFile(inputFile)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);

    /* read the image data: */
    if ((returnVal = readImageData(inputFile, imagePointer)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);

    /* we're done with the file, so close it */
    fclose(inputFile);
    return EXIT_NO_ERRORS; //return with success code
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
int initialiseImage(Image *imagePointer, char *width, char *height)
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
int readImageData (FILE *inputFile, Image *imagePointer)
{
    int returnVal; //return value variable created

    /* Calls func to dynamically allocate memory for the imageData 2d array, returning returnVal on error. */
    if ((returnVal = mallocImageDataArray(imagePointer)) != 0) return returnVal;

    /* Variables which store data during for-loop: */
    int pixelValue;

    /* define for-loop variable counters: */
    int rowIndex;
    int columnIndex;
    /* nested iteratation through each element/pixelValue in the imageData array */
    for (rowIndex = 0; rowIndex < imagePointer->height; rowIndex++)
    { /*per row of pixels*/
        for (columnIndex = 0; columnIndex < imagePointer->width; columnIndex++)
        { /*per pixel*/

            /* Read pixel value by calling readValue() func: */
            pixelValue = readValue(inputFile);
            //printf("%d ", pixelValue);

            /* sanity check that the pixelValue is valid */
            if ((returnVal = checkPixelValue(imagePointer, pixelValue)) != 0) return returnVal;

            /* Set corresponding index in the imageData 2d array to the pixelValue which has just been read */ 
            imagePointer->imageData[rowIndex][columnIndex] = pixelValue;
        } /*per pixel*/
    } /*per row of pixels*/
    
    /* return with success code */ 
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: mallocImageDataArray             */
/* -> dynamically allocates memory to the */
/* imageData array. This func is called   */
/* just before reading the pixel data     */
/* from the input gtopo file.             */
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
        imagePointer->imageData[pointerIndex] = malloc (imagePointer->width * sizeof(short));
        /* sanity check for memory allocation for this row of the array */
        if ((returnVal = check1dImageDataMemoryAllocation(imagePointer, pointerIndex)) != 0) return returnVal;
    }

    return EXIT_NO_ERRORS;
}

/*******************************************/
/* FUNC: writeGtopoFile                    */
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
    int rowIndex;
    int columnIndex;

    /* nested iteratation through each element/pixelValue in the imageData array,   */
    /* BUT each loop increments by the reductionFactor in order to reduce the image */
    for (rowIndex = 0; rowIndex < imagePointer->height; rowIndex+=reductionFactor)
    { /*per row of pixels*/
        for (columnIndex = 0; columnIndex < imagePointer->width; columnIndex+=reductionFactor)
        { /*per pixel*/
            
            /* write the current pixel to the file */
            writeValue(outputFile, &imagePointer->imageData[rowIndex][columnIndex]);

            if (imagePointer->imageData[rowIndex][columnIndex] <= -9000)
            {
                printf(" ");
            }
            // Low ground (sea < value <= hill) -> print '.'
            else if (imagePointer->imageData[rowIndex][columnIndex] > -9000 && imagePointer->imageData[rowIndex][columnIndex] <= 0)
            {
                printf(".");
            }
            // High ground (hill < value <= mountain) -> print '^'
            else if (imagePointer->imageData[rowIndex][columnIndex] > 0 && imagePointer->imageData[rowIndex][columnIndex] <= 2000)
            {
                printf("^");
            }
            // Mountains (mountain < value) -> print 'A'
            else if (imagePointer->imageData[rowIndex][columnIndex] > 2000)
            {
                printf("A");
            }

        } /*per pixel*/

        printf("\n");
    } /*per row of pixels*/

    printf("C: %d ,R: %d\n", columnIndex, rowIndex);
    printf("Total wrote: %d\n", columnIndex/reductionFactor);

    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: readValue                        */
/* -> reads the next value from the       */
/* provided file and returns it.          */
/*                                        */
/* Parameters:                            */
/* - filePointer: FILE pointer to read    */
/* Returns: - the value read as a short   */
/******************************************/
short readValue(FILE *filePointer)
{
    /* NOTE:                                                                     */
    /* We read in values one byte at a time. Therefore: read two consecutive bytes */
    /* and combine them (in opposite order) to form a short (in big-endian format).*/ 

    int left8bit; //stores the first 8 bits read
    int right8bit; //stores the next 8 bits read
    int scanCount; //stores number of items read

    /* Read first byte from the file and store result in left8bit */
    scanCount = fread(&left8bit, 1, 1, filePointer);
    /* Check for fread error (i.e. if we haven't read just one value): */
    if (scanCount != 1)
    {
        /* return one larger value than the maximum possible image */
        /* dimensions, in order to trigger error.                  */
        return MAX_IMAGE_DIMENSION+1;
    }
    /* convert byte from unsigned to signed */
    left8bit -= 256; 
    
    /* Read next byte from the file and store result in right8bit */
    scanCount = fread(&right8bit, 1, 1, filePointer);
    /* Check for fread error (i.e. if we haven't read just one value): */
    if (scanCount != 1)
    {
        /* return one larger value than the maximum possible image */
        /* dimensions, in order to trigger error.                  */
        return MAX_IMAGE_DIMENSION+1; 
    }
    /* convert byte from unsigned to signed */
    right8bit -= 256;

    /* remove from right8bit */
    short positiveRight8bit = right8bit & 255; 
    /* shift the left8bit by 8 then join with right positiveRight8bit. */
    short result = (left8bit << 8) | positiveRight8bit; 

    /* return the final value */
    return result;
}

/******************************************/
/* FUNC: writeValue                       */
/* -> writes the provided pixel           */
/* (valueToWrite) to the provided file.   */
/*                                        */
/* Parameters:                            */
/* - filePointer: FILE pointer to read    */
/* Returns: - the value read as a short   */
/******************************************/
void writeValue(FILE *filePointer, short *valueToWrite)
{
    /* split the short into two bytes */
    char c1 = *valueToWrite >> 8; //leftshift by 8 to get first byte
    char c2 = *valueToWrite & 0x00ff; //AND comparison with 000000000111111111 to second byte.

    /* write both bytes to the file */
    fwrite(&c1, 1, 1, filePointer);
    fwrite(&c2, 1, 1, filePointer);
}