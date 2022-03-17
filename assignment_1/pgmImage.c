/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>
#include <math.h>
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
    //checkInputFile
    int r;
    if ((r = checkInputFile(inputFile, filename)) != 0) return r;

    /*//*/if ((r = readCommentLine (inputFile, filename, imagePointer)) != 0) return r;
    if ((r = readMagicNumber (inputFile, filename, imagePointer)) != 0) return r;
    /*//*/if ((r = readCommentLine (inputFile, filename, imagePointer)) != 0) return r;
    if ((r = readDimensions (inputFile, filename, imagePointer)) != 0) return r;
    /*//*/if ((r = readCommentLine (inputFile, filename, imagePointer)) != 0) return r;
    if ((r = readMaxGray (inputFile, filename, imagePointer)) != 0) return r;
    /*//*/if ((r = readCommentLine (inputFile, filename, imagePointer)) != 0) return r;
    if ((r = readImageData (inputFile, filename, imagePointer)) != 0) return r;
    /*//*/if ((r = readCommentLine (inputFile, filename, imagePointer)) != 0) return r;

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
    int scanCount = fscanf(filePointer, " "); // scan whitespace if present */
    //printf("SC:%d\n", scanCount);
    /* check for a comment line              */
	char nextChar = fgetc(filePointer);
	if (nextChar == '#')
    { /* comment line                */
        //printf("COMMENT!!!");
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

int readDimensions (FILE *filePointer, char *filename, Image *imagePointer)
{
    /* read in width, height          */
	/* whitespace to skip blanks             */
	int scanCount = fscanf(filePointer, " %u %u", &(imagePointer->width), &(imagePointer->height));
    return checkDimensions(filePointer, filename, scanCount, imagePointer->width, imagePointer->height, imagePointer->commentLine);
}

int readMaxGray (FILE *filePointer, char *filename, Image *imagePointer)
{
    int scanCount = fscanf(filePointer, " %u", &(imagePointer->maxGray));
    return checkMaxGray(filePointer, filename, scanCount, imagePointer->maxGray, imagePointer->commentLine);
}

int readImageData (FILE *filePointer, char *filename, Image *imagePointer)
{
    /* allocate the data pointer             */
	long nImageBytes = imagePointer->width * imagePointer->height * sizeof(unsigned char);
	imagePointer->imageData = (unsigned char *) malloc(nImageBytes);

	/* sanity check for memory allocation    */
    int r;
	if ((r = checkImageDataMemoryAllocation(filePointer, filename, imagePointer->imageData, imagePointer->commentLine)) != 0) return r;

    unsigned char *nextGrayValue;

	/* pointer for efficient read code       */
    // if(*imagePointer->magic_Number == MAGIC_NUMBER_RAW_PGM){
    //     //getc(filePointer);
    // }

    int grayValue;
    int scanCount = 1;
    
	for (nextGrayValue = imagePointer->imageData; nextGrayValue < imagePointer->imageData + nImageBytes; nextGrayValue++)
    { /* per gray value */
		/* read next value               */
        // /* */if (readCommentLine (filePointer, filename, imagePointer) == 1) return 1;
	    grayValue = -1;
        if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
        {
            scanCount = fscanf(filePointer, " %u", &grayValue);
        }
        else
        {
            scanCount = fread(&grayValue, 1, 1, filePointer);
            grayValue=256+(int) grayValue;
            grayValue=(grayValue*imagePointer->maxGray)/255;
        }

		/* sanity check	                 */
        //printf("%d, %d\n", scanCount, grayValue);
        int r;
        if ((r = checkPixelValue(filePointer, filename, imagePointer->imageData, imagePointer->commentLine, scanCount, grayValue)) != 0) return r;
        
		/* set the pixel value           */
		*nextGrayValue = (unsigned char) grayValue;
    } /* per gray value */
    scanCount = fscanf(filePointer, " %u", &grayValue);
    //printf("%d, %d\n", scanCount, grayValue);
    //IF too many pixels return 1 - //ELSE return 0.
    return checkIfTooManyPixels(filePointer, filename, imagePointer->imageData,  imagePointer->commentLine, scanCount);
}

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
            double proportionateValue = ceil(((double)*nextGrayValue/imagePointer->maxGray)*255);
            //printf("%i\n", proportionateValue);
            *nextGrayValue = proportionateValue;
            fwrite(nextGrayValue, 1, 1, outputFile);
        }

		/* sanity check on write         */
		if ((r = checknBytesWritten(outputFile, filename, imagePointer->imageData, imagePointer->commentLine, nBytesWritten)) != 0) return r;
    } /* per gray value */
    return 0;
}