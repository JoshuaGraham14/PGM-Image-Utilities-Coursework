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

/* FUNC: fills imagePointer with NULL data values for Image struct */
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

/* FUNC: collection of other pgmImage methods - used to read in a pgmFile */
int readpgmFile(char *filename, Image *imagePointer, int mode)
{
    FILE *inputFile = fopen(filename, "r"); //open file in read mode.

    // NOTE: for the following functions, return the return value of the function only if it was not successful 
    // ********************************************************************************************************

    /* check the input file to see if can be opened*/
    int r; //return value variable.
    if ((r = checkInputFile(inputFile, filename)) != 0) return r;
    errorCheck(inputFile, filename, imagePointer);

    /* comment check */if ((r = readCommentLine (inputFile, filename, imagePointer)) != 0) return r;

    /* read the magic number: */
    if ((r = readMagicNumber (inputFile, filename, imagePointer, mode)) != 0) return r;
    
    /* comment check */if ((r = readCommentLine (inputFile, filename, imagePointer)) != 0) return r;

    /* read the dimensions: */
    if ((r = readDimensions (inputFile, filename, imagePointer)) != 0) return r;

    /* comment check */if ((r = readCommentLine (inputFile, filename, imagePointer)) != 0) return r;

    /* read the max gray value: */
    if ((r = readMaxGray (inputFile, filename, imagePointer)) != 0) return r;

    /* comment check */if ((r = readCommentLine (inputFile, filename, imagePointer)) != 0) return r;

    /* read the image data: */
    if ((r = readImageData (inputFile, filename, imagePointer)) != 0) return r;

    /* comment check */if ((r = readCommentLine (inputFile, filename, imagePointer)) != 0) return r;

    // ********************************************************************************************************

    /* we're done with the file, so close it */
    fclose(inputFile);
    return EXIT_NO_ERRORS; //success
}

/* FUNC: reads the Image magic number */
int readMagicNumber (FILE *filePointer, char *filename, Image *imagePointer, int mode)
{
    /* read in the magic number              */
    imagePointer->magic_number[0] = getc(filePointer);
    imagePointer->magic_number[1] = getc(filePointer);

    /* check the magic number is valid */
    return checkMagicNumber(filePointer, filename, imagePointer, mode);
}

/* FUNC: reads the Image comment line */
int readCommentLine (FILE *filePointer, char *filename, Image *imagePointer)
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
        return checkCommentLine(filePointer, filename, imagePointer);
    }
	else
    { /* not a comment line */
		/* put character back            */
		ungetc(nextChar, filePointer);
    } /* not a comment line */
    return EXIT_NO_ERRORS;
}

/* FUNC: reads the Image dimensions */
int readDimensions (FILE *filePointer, char *filename, Image *imagePointer)
{
    /* read in width, height          */
	/* whitespace to skip blanks             */
	int scanCount = fscanf(filePointer, " %u %u", &(imagePointer->width), &(imagePointer->height));
    /* check the dimensions are valid */
    return checkDimensions(filePointer, filename, scanCount, imagePointer);
}

/* FUNC: reads the Image max gray */
int readMaxGray (FILE *filePointer, char *filename, Image *imagePointer)
{
    /* read in maxGray          */
    /* whitespace to skip blanks             */
    int scanCount = fscanf(filePointer, " %u", &(imagePointer->maxGray));
    /* check the max gray is valid */
    return checkMaxGray(filePointer, filename, scanCount, imagePointer);
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
    if ((r = check2dImageDataMemoryAllocation(filePointer, filename, imagePointer)) != 0) return r;
	int i;
    int j;
    for (i = 0; i < height; i++)
    {
        imagePointer->imageData[i] = malloc (width * sizeof(unsigned char));
        if ((r = check1dImageDataMemoryAllocation(filePointer, filename, imagePointer, i)) != 0) return r;
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

            //int r;
            if ((r = checkPixelValue(filePointer, filename, imagePointer, scanCount, pixelValue)) != 0) return r;

            imagePointer->imageData[i][j] = pixelValue;
        }
    }
    
    scanCount = fscanf(filePointer, " %u", &pixelValue);
    /* IF too many pixels return 1 - //ELSE return 0. */
    return checkIfTooManyPixels(filePointer, filename, imagePointer, scanCount);
}

int errorCheck(FILE *filePointer, char *filename, Image *imagePointer)
{
    int errorCode[] = {EXIT_NO_ERRORS, ERROR_BAD_ARGUMENT_COUNT, ERROR_BAD_FILE_NAME, ERROR_BAD_MAGIC_NUMBER, 
ERROR_BAD_COMMENT_LINE, ERROR_BAD_DIMENSIONS, ERROR_BAD_MAX_GRAY_VALUE, ERROR_IMAGE_MALLOC_FAILED, 
ERROR_BAD_DATA, ERROR_OUTPUT_FAILED, ERROR_MISCELLANEOUS};

    printf("%d", errorCode[2]);
    return 0;
}

/* FUNC: writes to an input file data from an input Image */
int writepgmFile(char *filename, Image *imagePointer)
{
    /* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");

    int height = imagePointer->height;
    int width = imagePointer->width;

    /* check whether file opening worked     */
    int r;
    if ((r = checkOutputFile(outputFile, filename, imagePointer)) != 0) return r;
    
    /* write magic number, size & gray value */
    size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", imagePointer->magic_number[1], imagePointer->width, imagePointer->height, imagePointer->maxGray);

	/* check that dimensions wrote correctly */
	if ((r = checknBytesWritten(outputFile, filename, imagePointer, nBytesWritten)) != 0) return r;

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
            if ((r = checknBytesWritten(outputFile, filename, imagePointer, nBytesWritten)) != 0) return r;
        }
        if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
        {
            fprintf(outputFile, "%c", '\n');
        }
    }

    return EXIT_NO_ERRORS;
}