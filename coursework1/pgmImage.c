/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "pgmErrors.h"
#include "pgmImage.h"

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

int readpgmFile(char *filename, Image *imagePointer)
{
    FILE *inputFile = fopen(filename, "r");

    /* if it fails, return error code        */
	checkInputFile(inputFile);

	/* read in the magic number              */
    if (readMagicNumber (inputFile, filename, imagePointer) == 0)
    {
        return 0;
    }

	/* scan whitespace if present            */
	int scanCount = fscanf(inputFile, " ");

    if (readCommentLine (inputFile, filename, imagePointer) == 0)
    {
        return 0;
    }

    if (readDimensionsAndGrays (inputFile, filename, imagePointer) == 0)
    {
        return 0;
    }

    if (readImageData (inputFile, filename, imagePointer) == 0)
    {
        return 0;
    }

    /* we're done with the file, so close it */
    fclose(inputFile);
    return 1;
}

int readMagicNumber (FILE *filePointer, char *filename, Image *imagePointer)
{
    imagePointer->magic_number[0] = getc(filePointer);
	imagePointer->magic_number[1] = getc(filePointer);

    return checkMagicNumber(filePointer, filename, *imagePointer->magic_Number, MAGIC_NUMBER_ASCII_PGM);
}

int readCommentLine (FILE *filePointer, char *filename, Image *imagePointer)
{
    /* check for a comment line              */
	char nextChar = fgetc(filePointer);
	if (nextChar == '#')
    { /* comment line                */
		/* allocate buffer               */
		imagePointer->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
        /* fgets() reads a line          */
        /* capture return value          */
        if (checkCommentLine(filePointer, filename, imagePointer->commentLine, MAX_COMMENT_LINE_LENGTH) == 0)
        {
            free(imagePointer->commentLine);

            return 0;
        }
    }
	else
    { /* not a comment line */
		/* put character back            */
		ungetc(nextChar, filePointer);
    } /* not a comment line */
    return 1;
}

int readDimensionsAndGrays (FILE *filePointer, char *filename, Image *imagePointer)
{
    /* read in width, height, grays          */
	/* whitespace to skip blanks             */
	int scanCount = fscanf(filePointer, " %u %u %u", &(imagePointer->width), &(imagePointer->height), &(imagePointer->maxGray));

	/* sanity checks on size & grays         */
	if (checkDimensionsAndGrays(filePointer, filename, scanCount, imagePointer->width, imagePointer->width, MIN_IMAGE_DIMENSION, MAX_IMAGE_DIMENSION, imagePointer->maxGray, imagePointer->commentLine) == 0)
    {
        return 0;
    }
    return 1;
}

int readImageData (FILE *filePointer, char *filename, Image *imagePointer)
{
    /* allocate the data pointer             */
	long nImageBytes = imagePointer->width * imagePointer->height * sizeof(unsigned char);
	imagePointer->imageData = (unsigned char *) malloc(nImageBytes);

	/* sanity check for memory allocation    */
	if (checkImageDataMemoryAllocation(filePointer, filename, imagePointer->imageData, imagePointer->commentLine) == 0)
    {
        return 0;
    }

	/* pointer for efficient read code       */
	for (unsigned char *nextGrayValue = imagePointer->imageData; nextGrayValue < imagePointer->imageData + nImageBytes; nextGrayValue++)
    { /* per gray value */
		/* read next value               */
		int grayValue = -1;
		int scanCount = fscanf(filePointer, " %u", &grayValue);

		/* sanity check	                 */
		if (checkPixelValue(filePointer, filename, imagePointer->imageData, imagePointer->commentLine, scanCount, grayValue) == 0)
        {
            return 0;
        }

		/* set the pixel value           */
		*nextGrayValue = (unsigned char) grayValue;
    } /* per gray value */
    return 1;
}

int writepgmFile(char *filename, Image *imagePointer)
{
    /* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");

    /* check whether file opening worked     */
    if (checkOutputFile(outputFile, filename, imagePointer->imageData, imagePointer->commentLine) == 0)
    {
        return 0;
    }
	
	/* write magic number, size & gray value */
	size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", imagePointer->width, imagePointer->height, imagePointer->maxGray);

	/* check that dimensions wrote correctly */
	if (checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten) == 0)
    {
        return 0;
    }

    long nImageBytes = imagePointer->width * imagePointer->height * sizeof(unsigned char);

    /* pointer for efficient write code      */
    for (unsigned char *nextGrayValue = imagePointer->imageData; nextGrayValue < imagePointer->imageData + nImageBytes; nextGrayValue++)
    { /* per gray value */
    /* get next char's column        */
		int nextCol = (nextGrayValue - imagePointer->imageData + 1) % imagePointer->width;

		/* write the entry & whitespace  */
		nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );

		/* sanity check on write         */
		if (checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten) == 0)
        {
            return 0;
        }
    } /* per gray value */
    return 1;
}