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

int checkCommentLine(FILE *filePointer, char *filename, char *commentLine, int MAX_COMMENT_LINE_LENGTH)
{
	char *commentString = fgets(commentLine, MAX_COMMENT_LINE_LENGTH, filePointer);
    /* NULL means failure            */
    if (commentString == NULL)
    {
          /* close file            */
        fclose(filePointer);

        /* print an error message */
        printf("Error: Failed to read pgm image from file %s\n", filename);
    
        /* and return            */
        return 0;
    } /* NULL comment read   */
     /* comment line */
    return 1;
}

int checkSizeAndGrays(FILE *filePointer, char *filename, int scanCount, int width, int height, int MIN_IMAGE_DIMENSION, int MAX_IMAGE_DIMENSION, int maxGray, char *commentLine)
{
	/* must read exactly three values        */
	if 	(
		(scanCount != 3				)	||
		(width 	< MIN_IMAGE_DIMENSION	) 	||
		(width 	> MAX_IMAGE_DIMENSION	) 	||
		(height < MIN_IMAGE_DIMENSION	) 	||
		(height > MAX_IMAGE_DIMENSION	) 	||
		(maxGray	!= 255		)
		)
	{ /* failed size sanity check    */
        free(commentLine);

		/* be tidy: close file pointer   */
		fclose(filePointer);

		/* print an error message */
		printf("Error: Failed to read pgm image from file %s\n", filename);	
		
		/* and return                    */
		return 0;
	} /* failed size sanity check    */
    return 1;
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
        return 0;
    } /* malloc failed */
    return 1;
}

int checkImageValue(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine, int scanCount, int grayValue)
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
        return 0;
    } /* fscanf failed */
    return 1;
}