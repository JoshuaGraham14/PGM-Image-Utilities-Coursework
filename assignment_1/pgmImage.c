/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include <string.h>

#include "pgmErrors.h"
#include "pgmImage.h"

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

    return checkMagicNumber(filePointer, filename, *imagePointer->magic_Number);
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
        if (checkCommentLine(filePointer, filename, imagePointer->commentLine) == 0)
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
	if (checkDimensionsAndGrays(filePointer, filename, scanCount, imagePointer->width, imagePointer->width, imagePointer->maxGray, imagePointer->commentLine) == 0)
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

    unsigned char *nextGrayValue;

	/* pointer for efficient read code       */
	for (nextGrayValue = imagePointer->imageData; nextGrayValue < imagePointer->imageData + nImageBytes; nextGrayValue++)
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
    size_t nBytesWritten;
    if(imagePointer->magic_number[1] == (unsigned char)'2')
    {
        printf("%s\n", imagePointer->magic_number);
        nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", imagePointer->width, imagePointer->height, imagePointer->maxGray);
    }
    else 
    {
        fwrite(imagePointer->imageData, 4, 4, outputFile);
    }

	/* check that dimensions wrote correctly */
	if (checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten) == 0)
    {
        return 0;
    }

    long nImageBytes = imagePointer->width * imagePointer->height * sizeof(unsigned char);

    unsigned char *nextGrayValue;
    /* pointer for efficient write code      */
    for (nextGrayValue = imagePointer->imageData; nextGrayValue < imagePointer->imageData + nImageBytes; nextGrayValue++)
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