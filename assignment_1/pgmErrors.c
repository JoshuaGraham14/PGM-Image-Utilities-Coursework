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

/******************************************/
/* FUNC: checkArgumentCount               */
/* -> checks the number of arguments      */
/* supplied against the specified number  */
/* of arguments.                          */
/*                                        */
/* Parameters:                            */
/* - argc: integer num of arguments       */
/* - numOfArgs: integer num of arguments  */
/*              expected                  */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
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

/******************************************/
/* FUNC: checkInputFile                   */
/* -> checks the input file is valid.     */
/*                                        */
/* Parameters:                            */
/* - filePointer: FILE pointer to read    */
/* Returns: - 0 on success                */
/*          - ERROR_BAD_FILE_NAME on fail */
/******************************************/
int checkInputFile(FILE *filePointer)
{
    /* if it fails, return error code        */
    if (filePointer == NULL)
    {
        /* return error code             */
        return ERROR_BAD_FILE_NAME;
    }

    /* ELSE return with success code */
	return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: checkMagicNumber                 */
/* -> checks if the magic number is valid.*/
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer          */
/* - mode: integer (either 0, 1, 2)       */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int checkMagicNumber(Image *imagePointer, int mode)
{
    /* sanity check on the magic number      */
    /* if it fails, return error code        */
	if ((*imagePointer->magic_Number != MAGIC_NUMBER_ASCII_PGM  && *imagePointer->magic_Number != MAGIC_NUMBER_RAW_PGM) ||
    (mode == 1 && *imagePointer->magic_Number == MAGIC_NUMBER_RAW_PGM) || 
    (mode == 2 && *imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM))
    { /* failed magic number check   */
        
        /* return error code             */
        return ERROR_BAD_MAGIC_NUMBER;
    } /* failed magic number check   */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: checkCommentLine                 */
/* -> checks if the comment line is valid.*/
/*                                        */
/* Parameters:                            */
/* - filePointer: FILE pointer to read    */
/* - imagePointer: Image pointer          */
/* Returns: - 0 on success                */
/*       - ERROR_BAD_MAGIC_NUMBER on fail */
/******************************************/
int checkCommentLine(FILE *filePointer, Image *imagePointer)
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
            /* return error code */
            return ERROR_BAD_COMMENT_LINE;
        }
        x++; //increment number of characters found
    }

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: checkDimensions                  */
/* -> checks if the dimensions is valid.  */
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer          */
/* - scanCount: int number of values read */
/* Returns: - 0 on success                */
/*         - ERROR_BAD_DIMENSIONS on fail */
/******************************************/
int checkDimensions(Image *imagePointer, int scanCount)
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

		/* return error code */
		return ERROR_BAD_DIMENSIONS;

	} /* failed size sanity check    */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: checkDimensions                  */
/* -> checks if the max gray's valid.     */
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer          */
/* - scanCount: int number of values read */
/* Returns: - 0 on success                */
/*     - ERROR_BAD_MAX_GRAY_VALUE on fail */
/******************************************/
int checkMaxGray(Image *imagePointer, int scanCount)
{
	/* must read exactly three values        */
    /* + check maxGray is in bounds          */
	if 	(
		(scanCount != 1	    )	            ||
        (imagePointer->maxGray	< 0		)   ||
        (imagePointer->maxGray  > 255   )
		)
	{ /* failed size sanity check    */

		/* return error code */
		return ERROR_BAD_MAX_GRAY_VALUE;

	} /* failed size sanity check    */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: check2dImageDataMemoryAllocation */
/* -> checks if the image malloc is valid */
/* for the 2d array.                      */
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer          */
/* Returns: - 0 on success                */
/*    - ERROR_IMAGE_MALLOC_FAILED on fail */
/******************************************/
int check2dImageDataMemoryAllocation(Image *imagePointer)
{
    /* sanity check for memory allocation of the 2d array */
    if (imagePointer->imageData == NULL)
    { /* malloc failed */

        /* return error code             */
        return ERROR_IMAGE_MALLOC_FAILED;

    } /* malloc failed */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: check1dImageDataMemoryAllocation */
/* -> checks if the image malloc is valid */
/* for each 1d array.                     */
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer          */
/* - rowNum: integer row number to free   */
/* Returns: - 0 on success                */
/*    - ERROR_IMAGE_MALLOC_FAILED on fail */
/******************************************/
int check1dImageDataMemoryAllocation(Image *imagePointer, int rowNum)
{
    /* sanity check for memory allocation of a value in that row of the 2d array */
    if (imagePointer->imageData[rowNum] == NULL)
    { /* malloc failed */
    
        /* return error code             */
        return ERROR_IMAGE_MALLOC_FAILED;

    } /* malloc failed */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: checkPixelValue                  */
/* -> checks if the image pixel value is  */
/* valid.                                 */
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer          */
/* - scanCount: int number of values read */
/* - pixelValue: int value of the pixel   */
/* Returns: - 0 on success                */
/*          - ERROR_BAD_DATA on fail      */
/******************************************/
int checkPixelValue(Image *imagePointer, int scanCount, int pixelValue)
{
    if ((scanCount != 1) || (pixelValue < 0) || (pixelValue > 255))
    { /* fscanf failed */

        /* return error code */
        return ERROR_BAD_DATA;

    } /* fscanf failed */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: checkIfTooManyPixels             */
/* -> checks if the imageData contains    */
/* more pixels than specified by          */
/* dimensions.                            */
/*                                        */
/* Parameters:                            */
/* - scanCount: int number of values read */
/* Returns: - 0 on success                */
/*          - ERROR_BAD_DATA on fail      */
/******************************************/
int checkIfTooManyPixels (int scanCount)
{
    /* YES IF: a pixel value has been detected after reading */
    /* number of pixels specified by dimensions.             */
    if (scanCount >=1)
    {
        /* and return error code */
        return ERROR_BAD_DATA;
    }
    /* else return with no error code */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: checkIfTooManyPixels             */
/* -> checks if the output file is valid. */
/*                                        */
/* Parameters:                            */
/* - filePointer: FILE pointer to read    */
/* Returns: - 0 on success                */
/*          - ERROR_OUTPUT_FAILED on fail */
/******************************************/
int checkOutputFile(FILE *filePointer)
{
    /* check whether file opening worked     */
    if (filePointer == NULL)
    { /* NULL output file */

        /* and return error code         */
        return ERROR_OUTPUT_FAILED;

    } /* NULL output file */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: checknBytesWritten               */
/* -> checks the num of bytes written is  */
/* valid.                                 */
/*                                        */
/* Parameters:                            */
/* - nBytesWritten: the num of bytes written */
/* Returns: - 0 on success                */
/*          - ERROR_OUTPUT_FAILED on fail */
/******************************************/
int checknBytesWritten(size_t nBytesWritten)
{
    /* check that dimensions wrote correctly */
    if (nBytesWritten < 0)
    { /* dimensional write failed    */

        /* return an error code          */
        return ERROR_OUTPUT_FAILED;

    } /* dimensional write failed    */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: validateFactorInput              */
/* ->  checks that inputted reduction     */
/* factor is an integer and greater than 0.*/
/*                                        */
/* Parameters:                            */
/* - charFactorInput: char pointer of     */
/*                  command line inputted */
/*                  factor.               */
/* Returns: - 0 on success                */
/*          - ERROR_MISCELLANEOUS on fail */
/******************************************/
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

/******************************************/
/* FUNC: validateTileOutputTemplate       */
/* ->  Check tiling output file template  */
/* is of correct format.                  */
/*                                        */
/* Parameters:                            */
/* - outputTemplateString: char pointer of*/
/*                  command line inputted */
/*                  template string.      */
/* Returns: - 0 on success                */
/*          - ERROR_MISCELLANEOUS on fail */
/******************************************/
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

/******************************************/
/* FUNC: validateTileOutputTemplate       */
/* ->  Handles the string output message  */
/* & closing variables and pointers after */
/* an error occurs.                       */
/*                                        */
/* Parameters:                            */
/* - filePointer: FILE pointer to read    */
/* - filename: char pointer               */
/* - imagePointer: Image pointer          */
/* - errorCode: integer corresponding to  */
/*              the error which occured.  */
/* Returns: - errorCode parameter         */
/******************************************/
int handleError(FILE *filePointer, char *filename, Image *imagePointer, int errorCode)
{
    char *errorStringsArray[8];
    errorStringsArray[0] = "ERROR: Bad File Name";
    errorStringsArray[1] = "ERROR: Bad Magic Number";
    errorStringsArray[2] = "ERROR: Bad Comment Line";
    errorStringsArray[3] = "ERROR: Bad Dimensions";
    errorStringsArray[4] = "ERROR: Bad Max Gray Value";
    errorStringsArray[5] = "ERROR: Image Malloc Failed";
    errorStringsArray[6] = "ERROR: Bad Data";
    errorStringsArray[7] = "ERROR: Output Failed";

    //print error codes which have '(filename)' format:
    if (errorCode >= 2 && errorCode <=6 || errorCode >=8 && errorCode <=9)
    {
        printf("%s (%s)\n", errorStringsArray[errorCode-2], filename);
    }
    //else print other errors with a newline
    else
    {
        printf("%s\n", errorStringsArray[errorCode-2]);
    }

    //Handle closing file and freeing memory
    if(errorCode >= 3 && errorCode <= 8)
    {
        /* close the file       */
        fclose(filePointer);

        if(errorCode >= 4)
        {
            /* free memory           */
            free(imagePointer->commentLine);
        }
        if(errorCode >= 8)
        {
            /* calls freeImageData func to free imageData from memory */
            freeImageData(imagePointer);
        }
    }

    return errorCode;
}

/******************************************/
/* FUNC: check1dImageDataMemoryAllocation */
/* -> frees the imagePointer.imageData 2d */
/* array.                                 */
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer          */
/* Returns: - (none)                      */
/******************************************/
/* FUNC:  */
void freeImageData (Image *imagePointer)
{
    int i;
    for (i = 0; i < imagePointer->height; i++)
    {
        free(imagePointer->imageData[i]);
    }
    free(imagePointer->imageData);
}