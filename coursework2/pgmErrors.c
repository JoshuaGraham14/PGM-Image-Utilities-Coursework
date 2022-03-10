/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "pgmErrors.h"

int checkMagicNumber(FILE *filePointer, char *filename, unsigned short magic_number, int MAGIC_NUMBER_ASCII_PGM)
{
	if (magic_number != MAGIC_NUMBER_ASCII_PGM)
    { /* failed magic number check   */
    /* be tidy: close the file       */
        fclose(filePointer);

        /* print an error message */
        printf("Error: Failed to read pgm image from file %s\n", filename);
        
        /* and return                    */
        return 0;
    } /* failed magic number check   */
    return 1;
}