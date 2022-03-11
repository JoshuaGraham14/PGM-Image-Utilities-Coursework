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