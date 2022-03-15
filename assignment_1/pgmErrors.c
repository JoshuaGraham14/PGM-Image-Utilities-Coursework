/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "pgmErrors.h"

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

int checkInputFile(FILE *filePointer)
{
    if (filePointer == NULL)
    {
        return 1;
    }
	return 0;
}

int checkMagicNumber(FILE *filePointer, char *filename, unsigned short magic_number)
{
	if (magic_number != MAGIC_NUMBER_ASCII_PGM  && magic_number != MAGIC_NUMBER_RAW_PGM)
    { /* failed magic number check   */
    /* be tidy: close the file       */
        fclose(filePointer);

        /* print an error message */
        printf("Error: Failed to read pgm image from file%s\n", filename);
        
        /* and return                    */
        return 1;
    } /* failed magic number check   */
    return 0;
}

int checkCommentLine(FILE *filePointer, char *filename, char *commentLine)
{
	char *commentString = fgets(commentLine, MAX_COMMENT_LINE_LENGTH, filePointer);
    /* NULL means failure            */
    if (commentString == NULL)
    {
          /* close file            */
        fclose(filePointer);

        free(commentLine);

        /* print an error message */
        printf("Error: Failed to read pgm image from file %s\n", filename);
    
        /* and return            */
        return 1;
    } /* NULL comment read   */
     /* comment line */
    return 0;
}

int checkDimensionsAndGrays(FILE *filePointer, char *filename, int scanCount, int width, int height, int maxGray, char *commentLine)
{
	/* must read exactly three values        */
	if 	(
		(scanCount != 3				)	||
		(width 	< MIN_IMAGE_DIMENSION	) 	||
		(width 	> MAX_IMAGE_DIMENSION	) 	||
		(height < MIN_IMAGE_DIMENSION	) 	||
		(height > MAX_IMAGE_DIMENSION	) 	||
        (maxGray	< 0		)               ||
        (maxGray    > 255     )      
		)
	{ /* failed size sanity check    */
        free(commentLine);

		/* be tidy: close file pointer   */
		fclose(filePointer);

		/* print an error message */
		printf("Error: Failed to read pgm image from file %s\n", filename);	
		
		/* and return                    */
		return 1;
	} /* failed size sanity check    */
    return 0;
}

int checkImageDataMemoryAllocation(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine)
{
    if (imageData == NULL)
    { /* malloc failed */
        /* free up memory                */
        free(commentLine);

        /* close file pointer            */
        fclose(filePointer);

        /* print an error message */
        printf("Error: Failed to read pgm image from file %s\n", filename);
        
        /* return error code             */
        return 1;
    } /* malloc failed */
    return 0;
}

int checkPixelValue(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine, int scanCount, int grayValue)
{
    if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
    { /* fscanf failed */
        /* free memory           */
        free(commentLine);
        free(imageData);

        /* close file            */
        fclose(filePointer);

        /* print error message   */
        printf("Error: Failed to read pgm image from file %s\n", filename);	

        /* and return            */
        return 1;
    } /* fscanf failed */
    return 0;
}

int checkOutputFile(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine)
{
    if (filePointer == NULL)
    { /* NULL output file */
        /* free memory                   */
        free(commentLine);
        free(imageData);

        /* print an error message        */
        printf("Error: Failed to write pgm image to file %s\n", filename);

        return 1;
    } /* NULL output file */
    return 0;
}

int checknBytesWritten(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine, size_t nBytesWritten)
{
    if (nBytesWritten < 0)
    { /* dimensional write failed    */
        /* free memory                   */
        free(commentLine);
        free(imageData);

        /* print an error message        */
        printf("Error: Failed to write pgm image to file %s\n", filename);

        /* return an error code          */
        return 1;
    } /* dimensional write failed    */
    return 0;
}