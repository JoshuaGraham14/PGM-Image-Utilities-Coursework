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

int readMagicNumber (FILE *filePointer, char *filename, Image *imagePointer)
{
    imagePointer->magic_number[0] = getc(filePointer);
	imagePointer->magic_number[1] = getc(filePointer);

    printf("pgmImage: %s\n", imagePointer->magic_number);

    return checkMagicNumber(filePointer, filename, *imagePointer->magic_Number, MAGIC_NUMBER_ASCII_PGM);
}

//void scanWhitespace()

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