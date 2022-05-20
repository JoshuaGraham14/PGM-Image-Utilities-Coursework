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
/* FUNC: createNewImage                   */
/* -> fills imagePointer with NULL data   */
/* values for Image struct.               */
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer          */
/* Returns: (none)                        */
/******************************************/
void createNewImage(Image *imagePointer)
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

    // NOTE: for the following functions, return the return value of the function only if it was not successful
    // ********************************************************************************************************

    /* check the input file to see if can be opened*/
    int returnVal; //return value variable.
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
    int scanCount = fscanf(filePointer, " "); // scan whitespace if present */
    //printf("SC:%d\n", scanCount);
    /* check for a comment line              */
	char nextChar = fgetc(filePointer);
	if (nextChar == '#')
    { /* comment line                */
		/* allocate buffer               */
		imagePointer->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
        /* check the comment line is valid */
        return checkCommentLine(filePointer, imagePointer);
    }
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
    int height = imagePointer->height;
    int width = imagePointer->width;
    int returnVal;

    /* allocate the data pointer             */
    imagePointer->imageData = malloc(height * sizeof(*imagePointer->imageData));
    /* sanity check for memory allocation    */
    if ((returnVal = check2dImageDataMemoryAllocation(imagePointer)) != 0) return returnVal;
	int i;
    int j;
    for (i = 0; i < height; i++)
    {
        imagePointer->imageData[i] = malloc (width * sizeof(unsigned char));
        if ((returnVal = check1dImageDataMemoryAllocation(imagePointer, i)) != 0) return returnVal;
    }

    //Read data:
    int pixelValue;
    int scanCount = 1;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            //break;
            if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
            {
                /* read next value               */
                scanCount = fscanf(filePointer, " %u", &pixelValue);
            }
            else
            {
                /* read next binary value               */
                scanCount = fread(&pixelValue, 1, 1, filePointer);
                /* calibrate binary value by adding 256       */
                pixelValue=(int)(unsigned char)pixelValue;
                /* read binary value proportionate to 255     */
                pixelValue=(pixelValue*imagePointer->maxGray)/255;
            }

            if ((returnVal = checkPixelValue(imagePointer, scanCount, pixelValue)) != 0) return returnVal;

            imagePointer->imageData[i][j] = pixelValue;
        }
    }
    
    scanCount = fscanf(filePointer, " %u", &pixelValue);
    /* IF too many pixels return 1 - //ELSE return 0. */
    return checkIfTooManyPixels(scanCount);
}

/******************************************/
/* FUNC: writepgmFile                     */
/* -> writes the data from the imagePointer*/
/* struct to the file with the input      */
/* filename.                              */
/*                                        */
/* Parameters:                            */
/* - filename: filename string            */
/* - imagePointer: Image pointer          */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int writepgmFile(char *filename, Image *imagePointer)
{
    /* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");

    int height = imagePointer->height;
    int width = imagePointer->width;

    /* check whether file opening worked     */
    int returnVal;
    if ((returnVal = checkOutputFile(outputFile)) != 0) return handleError(outputFile, filename, imagePointer, returnVal);
    
    /* write magic number, size & gray value */
    size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", imagePointer->magic_number[1], imagePointer->width, imagePointer->height, imagePointer->maxGray);

	/* check that dimensions wrote correctly */
	if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return handleError(outputFile, filename, imagePointer, returnVal);

    int i;
    int j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            /* write the entry & whitespace  */
            if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
            {
                nBytesWritten = fprintf(outputFile, "%d ", imagePointer->imageData[i][j]);
            }
            else 
            {
                //printf("\n%d, %d", imagePointer->imageData[i][j], &imagePointer->imageData[i][j]);
                fwrite(&imagePointer->imageData[i][j], 1, 1, outputFile);
            }

            /* sanity check on write         */
            if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return handleError(outputFile, filename, imagePointer, returnVal);
        }
        if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
        {
            fprintf(outputFile, "%c", '\n');
        }
    }

    return EXIT_NO_ERRORS;
}