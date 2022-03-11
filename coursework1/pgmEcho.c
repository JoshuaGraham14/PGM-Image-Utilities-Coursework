/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Hamish Carr                     */
/***********************************/

/***********************************/
/* A first iteration to take a pgm */
/* file in binary and convert to   */
/* ASCII or vice versa             */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "pgmErrors.h"
#include "pgmImage.h"

#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_INPUT_FILE 2
#define EXIT_BAD_OUTPUT_FILE 3

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{ /* main() */
	/* check for correct number of arguments */
	if (argc != 3)	
    { /* wrong arg count */
		/* print an error message        */
		printf("Usage: %s input_file output_file\n", argv[0]);
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
    } /* wrong arg count */
	
	/* variables for storing the image - stored in an Image struct       */
    Image inputImage = {.magic_number={'0','0'}, .magic_Number=(unsigned short *) inputImage.magic_number, .commentLine=NULL, .width=0, .height=0, .maxGray=255, .imageData=NULL};
    Image *inputImagePtr = &inputImage;

	/* now start reading in the data         */
	/* try to open the file for text I/O     */
	/* in ASCII mode b/c the header is text  */
	FILE *inputFile = fopen(argv[1], "r");

	/* if it fails, return error code        */
	if (inputFile == NULL)
		return EXIT_BAD_INPUT_FILE;

	/* read in the magic number              */
    if (readMagicNumber (inputFile, argv[1], inputImagePtr) == 0)
    {
        return EXIT_BAD_INPUT_FILE;
    }

	/* scan whitespace if present            */
	int scanCount = fscanf(inputFile, " ");

    if (readCommentLine (inputFile, argv[1], inputImagePtr) == 0)
    {
        return EXIT_BAD_INPUT_FILE;
    }

    if (readDimensionsAndGrays (inputFile, argv[1], inputImagePtr) == 0)
    {
        return EXIT_BAD_INPUT_FILE;
    }

    if (readImageData (inputFile, argv[1], inputImagePtr) == 0)
    {
        return EXIT_BAD_INPUT_FILE;
    }

	/* we're done with the file, so close it */
	fclose(inputFile);

	/* open a file for writing               */
	FILE *outputFile = fopen(argv[2], "w");

    /* check whether file opening worked     */
    if (checkOutputFile(outputFile, argv[2], inputImage.imageData, inputImage.commentLine) == 0)
    {
        return EXIT_BAD_OUTPUT_FILE;
    }
	
	/* write magic number, size & gray value */
	size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", inputImage.width, inputImage.height, inputImage.maxGray);

	/* check that dimensions wrote correctly */
	if (checknBytesWritten(outputFile, argv[2], inputImage.imageData, inputImage.commentLine, nBytesWritten) == 0)
    {
        return EXIT_BAD_OUTPUT_FILE;
    }

    long nImageBytes = inputImage.width * inputImage.height * sizeof(unsigned char);

    /* pointer for efficient write code      */
    for (unsigned char *nextGrayValue = inputImage.imageData; nextGrayValue < inputImage.imageData + nImageBytes; nextGrayValue++)
    { /* per gray value */
    /* get next char's column        */
		int nextCol = (nextGrayValue - inputImage.imageData + 1) % inputImage.width;

		/* write the entry & whitespace  */
		nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );

		/* sanity check on write         */
		if (checknBytesWritten(outputFile, argv[2], inputImage.imageData, inputImage.commentLine, nBytesWritten) == 0)
        {
            return EXIT_BAD_OUTPUT_FILE;
        }
    } /* per gray value */

	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
} /* main() */