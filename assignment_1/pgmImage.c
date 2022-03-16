/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>

#include "pgmErrors.h"
#include "pgmImage.h"

#define MAX_COMMENT_LINE_LENGTH 128
#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250

int readpgmFile(char *filename, Image *imagePointer)
{
    FILE *inputFile = fopen(filename, "r");

    /* if it fails, return error code        */
	checkInputFile(inputFile);

    if (readMagicNumber (inputFile, filename, imagePointer) == 1) return 1;
	int scanCount = fscanf(inputFile, " "); // scan whitespace if present */
    if (readCommentLine (inputFile, filename, imagePointer) == 1) return 1;
    if (readDimensionsAndGrays (inputFile, filename, imagePointer) == 1) return 1;
    if (readImageData (inputFile, filename, imagePointer) == 1) return 1;

    /* we're done with the file, so close it */
    fclose(inputFile);
    return 0;
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
        return checkCommentLine(filePointer, filename, imagePointer->commentLine);
    }
	else
    { /* not a comment line */
		/* put character back            */
		ungetc(nextChar, filePointer);
    } /* not a comment line */
    return 0;
}

int readDimensionsAndGrays (FILE *filePointer, char *filename, Image *imagePointer)
{
    /* read in width, height, grays          */
	/* whitespace to skip blanks             */
	int scanCount = fscanf(filePointer, " %u %u %u", &(imagePointer->width), &(imagePointer->height), &(imagePointer->maxGray));

	/* sanity checks on size & grays         */
	return checkDimensionsAndGrays(filePointer, filename, scanCount, imagePointer->width, imagePointer->width, imagePointer->maxGray, imagePointer->commentLine);
}

int readImageData (FILE *filePointer, char *filename, Image *imagePointer)
{
    /* allocate the data pointer             */
	long nImageBytes = imagePointer->width * imagePointer->height * sizeof(unsigned char);
	imagePointer->imageData = (unsigned char *) malloc(nImageBytes);

	/* sanity check for memory allocation    */
	if (checkImageDataMemoryAllocation(filePointer, filename, imagePointer->imageData, imagePointer->commentLine) == 1) return 1;

    unsigned char *nextGrayValue;

	/* pointer for efficient read code       */
    if(*imagePointer->magic_Number == MAGIC_NUMBER_RAW_PGM){
         getc(filePointer);
    }
   
	for (nextGrayValue = imagePointer->imageData; nextGrayValue < imagePointer->imageData + nImageBytes; nextGrayValue++)
    { /* per gray value */
		/* read next value               */
		int grayValue = -1;
        int scanCount;
        if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
        {
            scanCount = fscanf(filePointer, " %u", &grayValue);
        }
        else
        {
            scanCount = fread(&grayValue, 1, 1, filePointer);
            grayValue=256+(int) grayValue; 
        }

		/* sanity check	                 */
        if (checkPixelValue(filePointer, filename, imagePointer->imageData, imagePointer->commentLine, scanCount, grayValue) == 1) return 1;
        
		/* set the pixel value           */
		*nextGrayValue = (unsigned char) grayValue;
    } /* per gray value */
    return 0;
}

int writepgmFile(char *filename, Image *imagePointer)
{
    /* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");

    /* check whether file opening worked     */
    if (checkOutputFile(outputFile, filename, imagePointer->imageData, imagePointer->commentLine) == 1) return 1;
    
    /* write magic number, size & gray value */
    size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", imagePointer->magic_number[1], imagePointer->width, imagePointer->height, imagePointer->maxGray);

	/* check that dimensions wrote correctly */
	if (checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten) == 1) return 1;

    long nImageBytes = imagePointer->width * imagePointer->height * sizeof(unsigned char);

    unsigned char *nextGrayValue;
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
            fwrite(nextGrayValue, 1, 1, outputFile);
        }

		/* sanity check on write         */
		if (checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten) == 1) return 1;
    } /* per gray value */
    return 0;
}