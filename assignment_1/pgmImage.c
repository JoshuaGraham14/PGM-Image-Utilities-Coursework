/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_1                    */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 08/03/22        */
/***********************************/

/***********************************/
/* Module for handling pgm Image   */
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
#include "pgmErrors.h"
#include "pgmImage.h"

/******************************************/
/* FUNC: readpgmFile                      */
/* -> collection of other pgmImage        */
/* methods - used to read in a pgmFile    */
/*                                        */
/* Parameters:                            */
/* - filename: char pointer               */
/* - imagePointer: Image pointer          */
/* - mode: integer (either 0, 1, 2)       */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int readpgmFile(char *filename, Image *imagePointer, int mode)
{
    FILE *inputFile = fopen(filename, "r"); //open file in read mode.

    /* fills imagePtr struct field values with NULL data */
    initialiseImage(imagePointer); 

    /* NOTE: for the following functions, return the return value of the function only if it was not successful */
    // **********************************************************************************************************
    int returnVal; //return value variable.

    /* check the input file to see if can be opened*/
    if ((returnVal = checkInputFile(inputFile)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);

    /* comment check */if ((returnVal = readCommentLine (inputFile, imagePointer)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);

    /* read the magic number: */
    if ((returnVal = readMagicNumber (inputFile, imagePointer, mode)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);
    
    /* comment check */if ((returnVal = readCommentLine (inputFile, imagePointer)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);

    /* read the dimensions: */
    if ((returnVal = readDimensions (inputFile, imagePointer)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);

    /* comment check */if ((returnVal = readCommentLine (inputFile, imagePointer)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);

    /* read the max gray value: */
    if ((returnVal = readMaxGray (inputFile, imagePointer)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);

    /* comment check */if ((returnVal = readCommentLine (inputFile, imagePointer)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);

    /* read the image data: */
    if ((returnVal = readImageData (inputFile, imagePointer)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);

    /* comment check */if ((returnVal = readCommentLine (inputFile, imagePointer)) != 0) return handleError(inputFile, filename, imagePointer, returnVal);

    // ********************************************************************************************************

    /* we're done with the file, so close it */
    fclose(inputFile);
    return EXIT_NO_ERRORS; //success
}

/******************************************/
/* FUNC: createNewImage                   */
/* -> fills imagePointer with NULL data   */
/* values for Image struct.               */
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer          */
/* Returns: (none)                        */
/******************************************/
void initialiseImage(Image *imagePointer)
{
    imagePointer -> magic_number[0]='0';
    imagePointer -> magic_number[1]='0';
    imagePointer -> magic_Number= (unsigned short *) imagePointer->magic_number;
    imagePointer -> commentLine=NULL;
    imagePointer -> width=0;
    imagePointer -> height=0;
    imagePointer -> maxGray=255;
    imagePointer->imageData=NULL;
}

/******************************************/
/* FUNC: readMagicNumber                  */
/* -> reads the magic number from the     */
/* file and stores the data in the        */
/* imagePointer struct.                   */
/*                                        */
/* Parameters:                            */
/* - filePointer: FILE pointer to read    */
/* - imagePointer: Image pointer          */
/* - mode: integer (either 0, 1, 2)       */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int readMagicNumber (FILE *filePointer, Image *imagePointer, int mode)
{
    /* read in the magic number              */
    imagePointer->magic_number[0] = getc(filePointer);
    imagePointer->magic_number[1] = getc(filePointer);

    /* check the magic number is valid */
    return checkMagicNumber(imagePointer, mode);
}

/******************************************/
/* FUNC: readCommentLine                  */
/* -> reads the comment line from the     */
/* file and stores the data in the        */
/* imagePointer struct.                   */
/*                                        */
/* Parameters:                            */
/* - filePointer: FILE pointer to read    */
/* - imagePointer: Image pointer          */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int readCommentLine (FILE *filePointer, Image *imagePointer)
{
    /* scan whitespace if present */
    int scanCount = fscanf(filePointer, " "); 

    /* check for a comment line              */
	char nextChar = fgetc(filePointer);
	if (nextChar == '#')
    { /* comment line */
		/* allocate buffer               */
		imagePointer->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
        /* check the comment line is valid */
        return checkCommentLine(filePointer, imagePointer);
    } /* comment line */
	else
    { /* not a comment line */
		/* put character back            */
		ungetc(nextChar, filePointer);
    } /* not a comment line */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: readDimensions                   */
/* -> reads the Image dimensions from the */
/* file and stores the data in the        */
/* imagePointer struct.                   */
/*                                        */
/* Parameters:                            */
/* - filePointer: FILE pointer to read    */
/* - imagePointer: Image pointer          */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int readDimensions (FILE *filePointer, Image *imagePointer)
{
    /* read in width, height          */
	/* whitespace to skip blanks             */
	int scanCount = fscanf(filePointer, " %u %u", &(imagePointer->width), &(imagePointer->height));
    /* check the dimensions are valid */
    return checkDimensions(imagePointer, scanCount);
}

/******************************************/
/* FUNC: readMaxGray                      */
/* -> reads the Max Gray value from the   */
/* file and stores the data in the        */
/* imagePointer struct.                   */
/*                                        */
/* Parameters:                            */
/* - filePointer: FILE pointer to read    */
/* - imagePointer: Image pointer          */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int readMaxGray (FILE *filePointer, Image *imagePointer)
{
    /* read in maxGray          */
    /* whitespace to skip blanks             */
    int scanCount = fscanf(filePointer, " %u", &(imagePointer->maxGray));
    /* check the max gray is valid */
    return checkMaxGray(imagePointer, scanCount);
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
    if ((returnVal = mallocImageDataArray(imagePointer, imagePointer->width, imagePointer->height)) != 0) return returnVal;

    /* Variables which store data during for-loop: */
    int pixelValue;
    int scanCount = 1;

    /* define for-loop variable counters: */
    int columnIndex;
    int rowIndex;

    for (columnIndex = 0; columnIndex < imagePointer->height; columnIndex++)
    {
        for (rowIndex = 0; rowIndex < imagePointer->width; rowIndex++)
        {
            /* IF: the image is in ASCII format:   */
            if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
            {
                /* read next value               */
                scanCount = fscanf(filePointer, " %u", &pixelValue);
            }
            /* ELSE: the image is in binary format: */
            else
            {
                /* read next binary value               */
                scanCount = fread(&pixelValue, 1, 1, filePointer);
                /* calibrate binary value by adding 256       */
                pixelValue=(int)(unsigned char)pixelValue;
                // /* read binary value proportionate to 255     */
                // pixelValue=(pixelValue*imagePointer->maxGray)/255;
            }

            /* sanity check that the pixelValue is valid */
            if ((returnVal = checkPixelValue(imagePointer, scanCount, pixelValue)) != 0) return returnVal;

            /* Set corresponding index in the imageData 2d array to the pixelValue which has just been read */ 
            imagePointer->imageData[columnIndex][rowIndex] = pixelValue;
        }
    }
    
    /* Try read one more pixel from the file */
    scanCount = fscanf(filePointer, " %u", &pixelValue);
    /* sanity check for there being more pixels than specified by the Image dimensions  */
    /* IF too many pixels are detected, return error code carried forwards from checkIfTooManyPixels function */
    /* ELSE still return error code carried forwards from checkIfTooManyPixels function; but this time it will be 0 (success)*/
    return checkIfTooManyPixels(scanCount);
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
int mallocImageDataArray(Image *imagePointer, int width, int height)
{
    int returnVal; //return value variable created

    /* dynamically allocate memory to imageData 2d array */
    imagePointer->imageData = malloc(height * sizeof(*imagePointer->imageData));
    /* sanity check for memory allocation for the whole 2d array */
    if ((returnVal = check2dImageDataMemoryAllocation(imagePointer)) != 0) return returnVal;

	/* define for-loop variable counter: */
    int pointerIndex;
    /* iterate through each row in the 2d array */
    for (pointerIndex = 0; pointerIndex < height; pointerIndex++)
    {
        /* dynamically allocate memory for each row in 2d array */
        imagePointer->imageData[pointerIndex] = malloc (width * sizeof(unsigned char));
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
int writepgmFile(char *filename, Image *imagePointer, int reductionFactor)
{
    /* open a file for writing */
	FILE *outputFile = fopen(filename, "w");

    int returnVal;  //return value variable
    /* check whether file opening worked - return returnVal only if not successful */
    if ((returnVal = checkOutputFile(outputFile)) != 0) return returnVal;
    
    /* Create variables which store the width and height of the image after it has been reduced */
    int reducedWidth = (imagePointer->width+reductionFactor-1)/reductionFactor;
    int reducedHeight = (imagePointer->height+reductionFactor-1)/reductionFactor;

    /* write magic number, reduced size & gray value */
    size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", imagePointer->magic_number[1], reducedWidth, reducedHeight, imagePointer->maxGray);

	/* check that dimensions wrote correctly - only return returnVal if not successful */
	if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return returnVal;

    /* define for-loop variable counters: */
    int columnIndex;
    int rowIndex;
    /* nested iteratation through each element/pixelValue in the imageData array,   */
    /* BUT each loop increments by the reductionFactor in order to reduce the image */
    for (columnIndex = 0; columnIndex < imagePointer->height; columnIndex+=reductionFactor)
    { /*per row of pixels*/
        for (rowIndex = 0; rowIndex < imagePointer->width; rowIndex+=reductionFactor)
        { /*per pixel*/
            /* IF: the image is in ASCII format:   */
            if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
            {
                /* write the entry & whitespace  */
                nBytesWritten = fprintf(outputFile, "%d ", imagePointer->imageData[columnIndex][rowIndex]);
            }
            /* ELSE: the image is in binary format: */
            else 
            {
                /* write the entry in binary */
                fwrite(&imagePointer->imageData[columnIndex][rowIndex], 1, 1, outputFile);
            }

            /* sanity check on write, by calling checknBytesWritten */
            if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return returnVal;
        } /*per pixel*/

        /* If the image is in ASCII format add a newline at the end of row column cycle */
        if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
        {
            fprintf(outputFile, "%c", '\n');
        }
    } /*per row of pixels*/
    
    /* no errors so exit with success return code */
    return EXIT_NO_ERRORS;
}