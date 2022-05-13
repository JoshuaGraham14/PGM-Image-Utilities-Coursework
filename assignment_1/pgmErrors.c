/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_1                    */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 09/03/22        */
/***********************************/

/***********************************/
/* Module for handling pgm errors  */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* Libraries */
#include <stdio.h> //library for I/O routines
#include <stdlib.h> //library for memory routines
#include <string.h> //library for string manipulation

/* Header files */
#include "pgmErrors.h"
#include "pgmImage.h"

/* FUNC: checks the number of arguments supplied against the specified number of arguments */
int checkArgumentCount(int argc, int numOfArgs)
{
    if (argc != numOfArgs)
    { /* wrong arg count */
        /* IF there were no arguments */
        if (argc == 1) return -1;

        /* ELSE output error message and return with error code */ 
        printf("ERROR: Bad Argument Count\n");
        return ERROR_BAD_ARGUMENT_COUNT;
    } /* wrong arg count */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: checks the input file is valid */
int checkInputFile(FILE *filePointer, char *filename)
{
    /* if it fails, return error code        */
    if (filePointer == NULL)
    {
         /* print an error message */
        printf("ERROR: Bad File Name (%s)\n", filename);
        return ERROR_BAD_FILE_NAME;
    }

    /* ELSE return with success code */
	return EXIT_NO_ERRORS;
}

/* FUNC: checks if the magic number is valid */
int checkMagicNumber(FILE *filePointer, char *filename, Image *imagePointer, int mode)
{
    /* sanity check on the magic number      */
    /* if it fails, return error code        */
	if ((*imagePointer->magic_Number != MAGIC_NUMBER_ASCII_PGM  && *imagePointer->magic_Number != MAGIC_NUMBER_RAW_PGM) ||
    (mode == 1 && *imagePointer->magic_Number == MAGIC_NUMBER_RAW_PGM) || 
    (mode == 2 && *imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM))
    { /* failed magic number check   */
        /* close the file       */
        fclose(filePointer);

        /* print an error message */
        printf("ERROR: Bad Magic Number (%s)\n", filename);
        
        /* and return error code             */
        return ERROR_BAD_MAGIC_NUMBER;
    } /* failed magic number check   */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: checks if the comment line is valid */
int checkCommentLine(FILE *filePointer, char *filename, Image *imagePointer)
{
    int x = 1; //variable to count number of characters read.
    char *commentString = imagePointer->commentLine; //prepare pointer
    /* while the comment string hasn't finished: */
    while(*commentString != '\n')
    {
        /* read one character */
        *commentString=fgetc(filePointer);
        /* if comment is invalid: */
        if(x>MAX_COMMENT_LINE_LENGTH || commentString == NULL)
        {
            /* close file            */
            fclose(filePointer);

            /* free memory           */
            free(imagePointer->commentLine);

            /* print an error message */
            printf("ERROR: Bad Comment Line (%s)\n", filename);
    
            /* and return error code */
            return ERROR_BAD_COMMENT_LINE;
        }
        x++; //increment number of characters found
    }

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: checks if the dimensions is valid */
int checkDimensions(FILE *filePointer, char *filename, int scanCount, Image *imagePointer)
{
	/* must read exactly three values         */
    /* + check width and height are in bounds */
	if 	(
		(scanCount != 2				    )	||
		(imagePointer->width 	< MIN_IMAGE_DIMENSION	) 	||
		(imagePointer->width 	>= MAX_IMAGE_DIMENSION	) 	||
		(imagePointer->height < MIN_IMAGE_DIMENSION	) 	||
		(imagePointer->height >= MAX_IMAGE_DIMENSION	)
    )
	{ /* failed size sanity check    */
        /* free memory           */
        free(imagePointer->commentLine);

		/* close file pointer   */
		fclose(filePointer);

		/* print an error message */
		printf("ERROR: Bad Dimensions (%s)\n", filename);	
		
		/* and return error code */
		return ERROR_BAD_DIMENSIONS;
	} /* failed size sanity check    */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: checks if the max gray is valid */
int checkMaxGray(FILE *filePointer, char *filename, int scanCount, Image *imagePointer)
{
	/* must read exactly three values        */
    /* + check maxGray is in bounds          */
	if 	(
		(scanCount != 1	    )	            ||
        (imagePointer->maxGray	< 0		)   ||
        (imagePointer->maxGray  > 255   )
		)
	{ /* failed size sanity check    */
        /* free memory           */
        free(imagePointer->commentLine);

		/* close file pointer   */
		fclose(filePointer);

		/* print an error message */
		printf("ERROR: Bad Max Gray Value (%s)\n", filename);	
		
		/* and return error code */
		return ERROR_BAD_MAX_GRAY_VALUE;
	} /* failed size sanity check    */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: checks if the image malloc is valid for the 2d array*/
int check2dImageDataMemoryAllocation(FILE *filePointer, char *filename, Image *imagePointer)
{
    /* sanity check for memory allocation    */
    if (imagePointer->imageData == NULL)
    { /* malloc failed */
        /* free up memory                */
        free(imagePointer->commentLine);

        /* close file pointer            */
        fclose(filePointer);

        /* print an error message */
        printf("ERROR: Image Malloc Failed\n");
        
        /* return error code             */
        return ERROR_IMAGE_MALLOC_FAILED;
    } /* malloc failed */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: checks if the image malloc is valid for each 1d array*/
int check1dImageDataMemoryAllocation(FILE *filePointer, char *filename, Image *imagePointer, int rowNum)
{
    /* sanity check for memory allocation    */
    if (imagePointer->imageData[rowNum] == NULL)
    { /* malloc failed */
        /* free up memory                */
        free(imagePointer->commentLine);

        /* close file pointer            */
        fclose(filePointer);

        /* print an error message */
        printf("ERROR: Image Malloc Failed\n");
        
        /* return error code             */
        return ERROR_IMAGE_MALLOC_FAILED;
    } /* malloc failed */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: checks if the image pixel value is valid */
int checkPixelValue(FILE *filePointer, char *filename, Image *imagePointer, int scanCount, int pixelValue)
{
    //printf("sc: %d; gv: %d", scanCount, pixelValue);
    if ((scanCount != 1) || (pixelValue < 0) || (pixelValue > 255))
    { /* fscanf failed */
        /* free memory           */
        free(imagePointer->commentLine);
        freeImageData (imagePointer);

        /* close file            */
        fclose(filePointer);

        /* print error message   */
        printf("ERROR: Bad Data (%s)\n", filename);

        /* and return error code */
        return ERROR_BAD_DATA;
    } /* fscanf failed */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: checks if the imageData contains more pixels than specified by dimensions */
int checkIfTooManyPixels (FILE *filePointer, char *filename, Image *imagePointer, int scanCount)
{
    //too many characters
    if (scanCount >=1)
    {
        /* free memory           */
        free(imagePointer->commentLine);
        freeImageData (imagePointer);

        /* close file            */
        fclose(filePointer);

        /* print error message   */
        printf("ERROR: Bad Data (%s)\n", filename);

        /* and return error code */
        return ERROR_BAD_DATA;
    }
    return EXIT_NO_ERRORS;
}

/* FUNC: checks if the output file is valid */
int checkOutputFile(FILE *filePointer, char *filename, Image *imagePointer)
{
    /* check whether file opening worked     */
    if (filePointer == NULL)
    { /* NULL output file */
        /* free memory                   */
        free(imagePointer->commentLine);
        freeImageData (imagePointer);

        /* print an error message        */
        printf("ERROR: Output Failed (%s)\n", filename);

        /* and return error code         */
        return ERROR_OUTPUT_FAILED;
    } /* NULL output file */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: checks the n bytes written to is valid */
int checknBytesWritten(FILE *filePointer, char *filename, Image *imagePointer, size_t nBytesWritten)
{
    /* check that dimensions wrote correctly */
    if (nBytesWritten < 0)
    { /* dimensional write failed    */
        /* free memory                   */
        free(imagePointer->commentLine);
        freeImageData(imagePointer);

        /* print an error message        */
        printf("ERROR: Output Failed (%s)\n", filename);

        /* return an error code          */
        return ERROR_OUTPUT_FAILED;
    } /* dimensional write failed    */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: Check reduction factor is an integer and is greater than 0 */
int validateFactorInput(char *charFactorInput)
{
    /* if reduction factor is an integer */
    if (atoi(charFactorInput))
    {
        int intFactor = atoi(charFactorInput);
        /* if reduction factor is less than or equal to 0 */
        if (intFactor > 0)
        {
            /* Return with success code */
            return EXIT_NO_ERRORS;
        }
    }

    //IF ABOVE FAILS:
    /* print an error message        */
    printf("ERROR: Miscellaneous (factor invalid)\n");
    /* return an error code          */
    return ERROR_MISCELLANEOUS; 
}

/* FUNC: Check tiling output file template is correct */
int validateTileOutputTemplate(char *outputTemplateString)
{
    /* if reduction factor is an integer */
    char *targetString = "_<row>_<column>.pgm";

    int i;
    for (i = 0; i < strlen(targetString); i++)
    {
        if (outputTemplateString[strlen(outputTemplateString)-i-1] != targetString[strlen(targetString)-i-1])
        {
            /* print an error message        */
            printf("ERROR: Miscellaneous (invalid output template)\n");
            /* return an error code          */
            return ERROR_MISCELLANEOUS;
        }
    }
    
    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: Frees the image data 2d array */
void freeImageData (Image *imagePointer)
{
    int i;
    for (i = 0; i < imagePointer->height; i++)
    {
        free(imagePointer->imageData[i]);
    }
    free(imagePointer->imageData);
}