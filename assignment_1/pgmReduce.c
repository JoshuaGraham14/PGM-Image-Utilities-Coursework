 /***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_1                    */
/* TASK IV                         */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 07/03/22        */
/***********************************/

/***********************************/
/* pgmReduce                       */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>
#include <stdbool.h>

#include "pgmImage.h"
#include "pgmErrors.h"

#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_INPUT_FILE 2
#define EXIT_BAD_OUTPUT_FILE 3

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250

int main(int argc, char **argv)
{ /* main() */
	/* check for correct number of arguments */
	if (argc != 4)
    { /* wrong arg count *//* main routine                    */
		/* print an error message        */
		printf("Usage: %s input_file n output_file\n", argv[0]);
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
    } /* wrong arg count */

    if (argv[2] < 1)
    {
        //reduction factor n must be greater than 0
    }
	
	/* variables for storing the image - stored in an Image struct       */
    Image inputImage = {.magic_number={'0','0'}, .magic_Number=(unsigned short *) inputImage.magic_number, .commentLine=NULL, .width=0, .height=0, .maxGray=255, .imageData=NULL};
    Image *inputImagePtr = &inputImage;

    /* now start reading in the data         */
    int returnValue = readpgmFile(argv[1], inputImagePtr);
	if (returnValue != 0)
    {
        return EXIT_BAD_INPUT_FILE;
    }

    //REDUCE

	/* open a file for writing               */
    char* filename = argv[3];
    int reductionFactor = atoi(argv[2]);
	FILE *outputFile = fopen(filename, "w");

    /* check whether file opening worked     */
    if (checkOutputFile(outputFile, filename, inputImage.imageData, inputImage.commentLine) == 1) return 1;
    
    int reducedWidth = (inputImage.width+reductionFactor-1)/reductionFactor;
    int reducedHeight = (inputImage.height+reductionFactor-1)/reductionFactor;
    int originalWidth = inputImage.width;
    int originalHeight = inputImage.height;
    /* write magic number, size & gray value */
    size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", inputImage.magic_number[1], reducedWidth, reducedHeight, inputImage.maxGray);

	/* check that dimensions wrote correctly */
	if (checknBytesWritten(outputFile, filename, inputImage.imageData, inputImage.commentLine, nBytesWritten) == 1) return 1;

    long nImageBytes = inputImage.width * inputImage.height * sizeof(unsigned char);

    unsigned char *nextGrayValue;
    int widthCounter = 0;
    int heightCounter = 0;
    /* pointer for efficient write code      */
    for (nextGrayValue = inputImage.imageData; nextGrayValue < inputImage.imageData + nImageBytes; nextGrayValue++)
    { /* per gray value */
    /* get next char's column        */
		int nextCol = (nextGrayValue - inputImage.imageData + 1) % inputImage.width;

        //printf("nextCol:%d, nextGray: %s\n", nextCol, nextGrayValue);
        //printf("widthCounter:%d, heightCounter: %d\n", widthCounter, heightCounter);
        
        int newCol = 1;

        if (widthCounter%reductionFactor==0 && heightCounter%reductionFactor==0)
        {
            if ((widthCounter+reductionFactor+1) > originalWidth)
            {
                newCol = 0;
            }
            //printf("AAA: widthCounter:%d, heightCounter: %d\n", widthCounter, heightCounter);
            if(*inputImage.magic_Number == MAGIC_NUMBER_ASCII_PGM)
            {
                nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (newCol ? ' ' : '\n'));
            }
            else 
            {
                fwrite(nextGrayValue, 1, 1, outputFile);
            }
        }
        
		/* sanity check on write         */
		if (checknBytesWritten(outputFile, filename, inputImage.imageData, inputImage.commentLine, nBytesWritten) == 1) return 1;

        if(nextCol == 0)
        {
            heightCounter++;
            widthCounter=0;
        }
        else
        {
            widthCounter++;
        }
    } /* per gray value */

	/* at this point, we are done and can exit with a success code */
    printf("REDUCED\n");
	return EXIT_NO_ERRORS;
} /* main() */