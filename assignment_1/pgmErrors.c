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

#define EXIT_NO_ERRORS 0
#define ERROR_BAD_ARGUMENT_COUNT 1
#define ERROR_BAD_FILE_NAME 2
#define ERROR_BAD_MAGIC_NUMBER 3
#define ERROR_BAD_COMMENT_LINE 4
#define ERROR_BAD_DIMENSIONS 5
#define ERROR_BAD_MAX_GRAY_VALUE 6
#define ERROR_IMAGE_MALLOC_FAILED 7
#define ERROR_BAD_DATA 8
#define ERROR_OUTPUT_FAILED 9
#define ERROR_MISCELLANEOUS 100

int checkArgumentCount(int argc, int numOfArgs)
{
    if (argc != numOfArgs)
    { /* wrong arg count */
        if (argc == 0) return -1;

        printf("ERROR: Bad Argument Count\n");
        return ERROR_BAD_ARGUMENT_COUNT;
    } /* wrong arg count */
    return EXIT_NO_ERRORS;
}

int checkInputFile(FILE *filePointer, char *filename)
{
    if (filePointer == NULL)
    {
        printf("ERROR: Bad File Name (%s)\n", filename);
        return ERROR_BAD_FILE_NAME;
    }
	return EXIT_NO_ERRORS;
}

int checkMagicNumber(FILE *filePointer, char *filename, unsigned short magic_number)
{
	if (magic_number != MAGIC_NUMBER_ASCII_PGM  && magic_number != MAGIC_NUMBER_RAW_PGM)
    { /* failed magic number check   */
    /* be tidy: close the file       */
        fclose(filePointer);

        /* print an error message */
        printf("ERROR: Bad Magic Number (%s)\n", filename);
        
        /* and return                    */
        return ERROR_BAD_MAGIC_NUMBER;
    } /* failed magic number check   */
    return EXIT_NO_ERRORS;
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
        printf("ERROR: Bad Comment Line (%s)\n", filename);
    
        /* and return            */
        return ERROR_BAD_COMMENT_LINE;
    } /* NULL comment read   */
     /* comment line */
    return EXIT_NO_ERRORS;
}

int checkDimensions(FILE *filePointer, char *filename, int scanCount, int width, int height, char *commentLine)
{
	/* must read exactly three values        */
	if 	(
		(scanCount != 2				    )	||
		(width 	< MIN_IMAGE_DIMENSION	) 	||
		(width 	> MAX_IMAGE_DIMENSION	) 	||
		(height < MIN_IMAGE_DIMENSION	) 	||
		(height > MAX_IMAGE_DIMENSION	)
    )
	{ /* failed size sanity check    */
        free(commentLine);

		/* be tidy: close file pointer   */
		fclose(filePointer);

		/* print an error message */
		printf("ERROR: Bad Dimensions (%s)\n", filename);	
		
		/* and return                    */
		return ERROR_BAD_DIMENSIONS;
	} /* failed size sanity check    */
    return EXIT_NO_ERRORS;
}

int checkMaxGray(FILE *filePointer, char *filename, int scanCount, int maxGray, char *commentLine)
{
	/* must read exactly three values        */
	if 	(
		(scanCount != 1	    )	||
        (maxGray	< 0		)   ||
        (maxGray    > 255   )
		)
	{ /* failed size sanity check    */
        free(commentLine);

		/* be tidy: close file pointer   */
		fclose(filePointer);

		/* print an error message */
		printf("ERROR: Bad Max Gray Value (%s)\n", filename);	
		
		/* and return                    */
		return ERROR_BAD_MAX_GRAY_VALUE;
	} /* failed size sanity check    */
    return EXIT_NO_ERRORS;
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
        printf("ERROR: Image Malloc Failed\n");
        
        /* return error code             */
        return ERROR_IMAGE_MALLOC_FAILED;
    } /* malloc failed */
    return EXIT_NO_ERRORS;
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
        printf("ERROR: Bad Data (%s) \n", filename);

        /* and return            */
        return ERROR_BAD_DATA;
    } /* fscanf failed */
    return EXIT_NO_ERRORS;
}

int checkIfTooManyPixels (FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine, int scanCount)
{
    //too many characters
    if (scanCount >=1)
    {
        free(commentLine);
        free(imageData);

        printf("ERROR: Miscellaneous (too many pixels for specified dimensions)\n");
        return ERROR_MISCELLANEOUS;
    }
    return EXIT_NO_ERRORS;
}

int checkOutputFile(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine)
{
    if (filePointer == NULL)
    { /* NULL output file */
        /* free memory                   */
        free(commentLine);
        free(imageData);

        /* print an error message        */
        printf("ERROR: Output Failed (%s)\n", filename);

        return ERROR_OUTPUT_FAILED;
    } /* NULL output file */
    return EXIT_NO_ERRORS;
}

int checknBytesWritten(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine, size_t nBytesWritten)
{
    if (nBytesWritten < 0)
    { /* dimensional write failed    */
        /* free memory                   */
        free(commentLine);
        free(imageData);

        /* print an error message        */
        printf("ERROR: Output Failed (%s)\n", filename);

        /* return an error code          */
        return ERROR_OUTPUT_FAILED;
    } /* dimensional write failed    */
    return EXIT_NO_ERRORS;
}