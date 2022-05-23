/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_2                    */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 04/05/22        */
/***********************************/

/***********************************/
/* Module for handling gtopo errors*/
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* Libraries */
#include <stdio.h> //library for I/O routines
#include <stdlib.h> //library for memory routines
#include <string.h> //library for string manipulation

/* Header files */
#include "gtopoErrors.h"
#include "gtopoImage.h"

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
/* FUNC: validateWidthAndHeight           */
/* ->  checks that inputted width and     */
/* height are both integers and greater   */
/* than zero.                             */
/*                                        */
/* Parameters:                            */
/* - width: char pointer to CL argument   */
/* - height: char pointer to CL argument  */
/* Returns: - 0 on success                */
/*          - ERROR_MISCELLANEOUS on fail */
/******************************************/
int validateWidthAndHeight(char *width, char *height)
{
    /* Check IF width and height are both integers */
    if (atoi(width) && atoi(height))
    {
        /* Convert both width and height to integers */
        int widthInt = atoi(width);
        int heightInt = atoi(height);
        /* Check IF width or height are greater than 0 */
        if (widthInt > 0 && heightInt > 0)
        {
            /* return with success code */
            return EXIT_NO_ERRORS;
        }
    }

    /* ELSE: Unsuccessful, so print an error message: */
    printf("ERROR: Miscellaneous (width or height parameter invalid)\n");
    /* and return an error code.         */
    return ERROR_MISCELLANEOUS; 
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
/* - pixelValue: int value of the pixel   */
/* Returns: - 0 on success                */
/*          - ERROR_BAD_DATA on fail      */
/******************************************/
int checkPixelValue(Image *imagePointer, int pixelValue)
{
    if ((pixelValue < MIN_IMAGE_DIMENSION) || (pixelValue > MAX_IMAGE_DIMENSION))
    { /* fscanf failed */

        /* return error code */
        return ERROR_BAD_DATA;

    } /* fscanf failed */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: checkOutputFile                  */
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
/* FUNC: validateFactorInput              */
/* -> checks that inputted reduction      */
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
    /* IF reduction factor is an integer */
    if (atoi(charFactorInput))
    {
        int intFactor = atoi(charFactorInput);
        /* and check IF reduction factor is greater than 0 */
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
/* -> Check tiling output file template   */
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
    /* template string which we are expecting  */
    char *targetString = "_<row>_<column>";

    /* define for-loop variable counters: */
    int charIndex;

    /* iterate through the indexes of each character in the targetString string */
    for (charIndex = 0; charIndex < strlen(targetString); charIndex++)
    { /* per character index */

        /* compares the characters at the same index (starting from the end */
        /* of each string) to check IF they are not identical.              */
        /* i.e. as the loop runs, it will check that the last 19 characters */
        /* of the outputTemplateString parameter match the targetString.    */
        if (outputTemplateString[strlen(outputTemplateString)-charIndex-1] != targetString[strlen(targetString)-charIndex-1])
        {
            /* print an error message        */
            printf("ERROR: Miscellaneous (invalid output template)\n");
            /* return an error code          */
            return ERROR_MISCELLANEOUS;
        }
    } /* per character index */
    
    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: validateRowAndColumnPosition     */
/* ->  checks that inputted row and       */
/* column positions are both integers and */
/* greater than zero.                     */
/*                                        */
/* Parameters:                            */
/* - row: char pointer to CL argument   */
/* - column: char pointer to CL argument  */
/* Returns: - 0 on success                */
/*          - ERROR_MISCELLANEOUS on fail */
/******************************************/
int validateRowAndColumnPosition(char *row, char *column)
{
    /* check IF row and column are both integers (including 0)*/
    if ((atoi(row) || strcmp(row, "0") == 0) &&
    (atoi(column) || strcmp(column, "0") == 0))
    {
        /* Convert both row and column to integers */
        int rowInt = atoi(row);
        int columnInt = atoi(column);
        /* check IF row and column are both greater than or equal to 0 */
        if (rowInt >= 0 || columnInt >= 0)
        {
            /* return with success code */
            return EXIT_NO_ERRORS;
        }
    }

    /* Unsuccessful, so print an error message: */ 
    printf("ERROR: Miscellaneous (row or column parameter invalid)\n");
    /* return an error code          */
    return ERROR_MISCELLANEOUS;
}


/******************************************/
/* FUNC: handleError                      */
/* -> handles the string output message & */
/* closing variables and pointers after   */
/* an error occurs. This function is      */
/* called every time an error is triggered.*/
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
    /* Array containing all the error messages (except from miscellaneous) */
    /* NOTE: The first two error codes EXIT_NO_ERRORS and ERROR_BAD_ARGUMENT_COUNT */ 
    /* are not stored in the errorStringsArray, so each index of the array is      */
    /* shifted by 2 to its corresponding error code & message.                     */
    char *errorStringsArray[8];
    errorStringsArray[0] = "Bad File Name";
    errorStringsArray[1] = "Bad Magic Number";
    errorStringsArray[2] = "Bad Comment Line";
    errorStringsArray[3] = "Bad Dimensions";
    errorStringsArray[4] = "Bad Max Gray Value";
    errorStringsArray[5] = "Image Malloc Failed";
    errorStringsArray[6] = "Bad Data";
    errorStringsArray[7] = "Output Failed";

    /* If errorCode = 7 (i.e. ERROR_IMAGE_MALLOC_FAILED) print the error code without '(filename)' format */ 
    if (errorCode == 7)
    {
        /* Print the error message          */
        /* NOTE: We minus 2 from errorCode because the first two error codes     */
        /* EXIT_NO_ERRORS and ERROR_BAD_ARGUMENT_COUNT are not stored in the     */
        /* errorStringsArray, so each index of the array is shifted by 2 to its  */
        /* corresponding error code & message.                                   */
        printf("ERROR: %s\n", errorStringsArray[errorCode-2]);
        
    }
    /* ELSE: print error codes which have '(filename)' format: */
    else
    {
        printf("ERROR: %s (%s)\n", errorStringsArray[errorCode-2], filename);
    }

    /* if block to handle closing file and freeing memory on failure: */
    /* IF: after file open stage and before file write stage -> close the file on failure */
    if(errorCode >= 3 && errorCode <= 8)
    {
        /* close the file       */
        fclose(filePointer);

        /* IF: after comment readGtopoFile stage -> free imageData on failure */
        if(errorCode >= 8)
        {
            /* calls freeImageData() func to free imageData from memory */
            freeImageData(imagePointer);
        }
    }

    /* Pass the errorCode (the error code detected) through the function */
    return errorCode;
}

/******************************************/
/* FUNC: freeImageData                    */
/* -> frees the imagePointer->imageData   */
/* 2d array.                              */
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer          */
/* Returns: - (none)                      */
/******************************************/
void freeImageData (Image *imagePointer)
{
    /* define for-loop variable counter: */
    int pointerIndex;

    /* iterate through each row in the 2d array */
    for (pointerIndex = 0; pointerIndex < imagePointer->height; pointerIndex++)
    {
        /* free memory for the data at each index at the current row of the 2d array */
        free(imagePointer->imageData[pointerIndex]);
    }
    /* free memory of the 2d array */
    free(imagePointer->imageData);
}