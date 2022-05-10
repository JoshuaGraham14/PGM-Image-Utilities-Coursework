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
    return checkMagicNumber(filePointer, filename, *imagePointer->magic_Number, mode);
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
        return checkCommentLine(filePointer, filename, imagePointer->commentLine);
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
    return checkDimensions(filePointer, filename, scanCount, imagePointer->width, imagePointer->height, imagePointer->commentLine);
}

/* FUNC: reads the Image max gray */
int readMaxGray (FILE *filePointer, char *filename, Image *imagePointer)
{
    /* read in maxGray          */
    /* whitespace to skip blanks             */
    int scanCount = fscanf(filePointer, " %u", &(imagePointer->maxGray));
    /* check the max gray is valid */
    return checkMaxGray(filePointer, filename, scanCount, imagePointer->maxGray, imagePointer->commentLine);
}

/* FUNC: reads the Image imageData */
int readImageData (FILE *filePointer, char *filename, Image *imagePointer)
{
    /* allocate the data pointer             */
	long nImageBytes = imagePointer->width * imagePointer->height * sizeof(unsigned char);
	imagePointer->imageData = (unsigned char *) malloc(nImageBytes);

	/* sanity check for memory allocation    */
    int r; //return value variable.
	if ((r = checkImageDataMemoryAllocation(filePointer, filename, imagePointer->imageData, imagePointer->commentLine)) != 0) return r;

    unsigned char *nextGrayValue; //assign pointer

    int grayValue;
    int scanCount = 1;
    
	for (nextGrayValue = imagePointer->imageData; nextGrayValue < imagePointer->imageData + nImageBytes; nextGrayValue++)
    { /* per gray value */
	    grayValue = -1;

        /* check whether you are reading in ASCII or binary format */
        if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
        {
            /* read next value               */
            scanCount = fscanf(filePointer, " %u", &grayValue);
        }
        else
        {
            /* read next binary value               */
            scanCount = fread(&grayValue, 1, 1, filePointer);
            /* calibrate binary value by adding 256       */
            grayValue=256+(int) grayValue; 
            /* read binary value proportionate to 255     */
            grayValue=(grayValue*imagePointer->maxGray)/255;
        }

		/* sanity check	                 */
        int r;
        if ((r = checkPixelValue(filePointer, filename, imagePointer->imageData, imagePointer->commentLine, scanCount, grayValue)) != 0) return r;
        
		/* set the pixel value           */
		*nextGrayValue = (unsigned char) grayValue;
    } /* per gray value */
    scanCount = fscanf(filePointer, " %u", &grayValue);
    /* IF too many pixels return 1 - //ELSE return 0. */
    return checkIfTooManyPixels(filePointer, filename, imagePointer->imageData,  imagePointer->commentLine, scanCount);
}

/* FUNC: writes to an input file data from an input Image */
int writepgmFile(char *filename, Image *imagePointer)
{
    /* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");

    /* check whether file opening worked     */
    int r;
    if ((r = checkOutputFile(outputFile, filename, imagePointer->imageData, imagePointer->commentLine)) != 0) return r;
    
    /* write magic number, size & gray value */
    size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", imagePointer->magic_number[1], imagePointer->width, imagePointer->height, imagePointer->maxGray);

	/* check that dimensions wrote correctly */
	if ((r = checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten)) != 0) return r;

    /* allocate the data pointer             */
    long nImageBytes = imagePointer->width * imagePointer->height * sizeof(unsigned char);

    unsigned char *nextGrayValue; //assign pointer
    /* pointer for efficient write code      */
    for (nextGrayValue = imagePointer->imageData; nextGrayValue < imagePointer->imageData + nImageBytes; nextGrayValue++)
    { /* per gray value */
        /* get next char's column        */
		int nextCol = (nextGrayValue - imagePointer->imageData + 1) % imagePointer->width;

        /* write the entry & whitespace  */
        if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
        {
            nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n'));
        }
        else 
        {
            //double proportionateValue = (((double)*nextGrayValue/imagePointer->maxGray)*255);
            //*nextGrayValue = proportionateValue;
            fwrite(nextGrayValue, 1, 1, outputFile);
        }

		/* sanity check on write         */
		if ((r = checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten)) != 0) return r;
    } /* per gray value */
    return EXIT_NO_ERRORS;
}