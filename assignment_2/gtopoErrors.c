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

/* Header files */
#include "gtopoErrors.h"

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

/* FUNC: Check reduction factor is an integer and is greater than 0 */
int checkWidthAndHeight(char *width, char *height)
{
    /* if reduction factor is an integer */
    if (atoi(width) && atoi(height))
    {
        int widthInt = atoi(width);
        int heightInt = atoi(height);
        /* if reduction factor is less than or equal to 0 */
        if (widthInt <= 0 || heightInt <= 0)
        {
            /* print an error message        */
            printf("ERROR: Miscellaneous (width or height parameter invalid)\n");
            /* return an error code          */
            return ERROR_MISCELLANEOUS; 
        }
    }
    else
    {   
        /* print an error message        */
        printf("ERROR: Miscellaneous (width or height parameter invalid)\n");
        /* return an error code          */
        return ERROR_MISCELLANEOUS; 
    }

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: checks if the image malloc is valid */
int check2dImageDataMemoryAllocation(FILE *filePointer, char *filename, short **imageData)
{
    /* sanity check for memory allocation    */
    if (imageData == NULL)
    { /* malloc failed */

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

/* FUNC: checks if the image malloc is valid */
int check1dImageDataMemoryAllocation(FILE *filePointer, char *filename, short *imageData)
{
    /* sanity check for memory allocation    */
    if (imageData == NULL)
    { /* malloc failed */

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

/* FUNC: checks if the image pixel is valid */
int checkPixelValue(FILE *filePointer, char *filename, short **imageData, int pixelValue, int height)
{
    if ((pixelValue < -9999) || (pixelValue > 9999))
    { /* fscanf failed */
        /* free memory           */
        free(imageData);

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

/* FUNC: checks if the output file is valid */
int checkOutputFile(FILE *filePointer, char *filename, short **imageData, int height)
{
    /* check whether file opening worked     */
    if (filePointer == NULL)
    { /* NULL output file */
        /* free memory                   */
        free(imageData);

        /* print an error message        */
        printf("ERROR: Output Failed (%s)\n", filename);

        /* and return error code         */
        return ERROR_OUTPUT_FAILED;
    } /* NULL output file */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: checks the n bytes written to is valid */
int checknBytesWritten(FILE *filePointer, char *filename, short **imageData, int height)
{
    /* check that dimensions wrote correctly */
    // if (nBytesWritten < 0)
    // { /* dimensional write failed    */
    //     /* free memory                   */
    //     free(imageData);

    //     /* print an error message        */
    //     printf("ERROR: Output Failed (%s)\n", filename);

    //     /* return an error code          */
    //     return ERROR_OUTPUT_FAILED;
    // } /* dimensional write failed    */

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

/* FUNC: Check reduction factor is an integer and is greater than 0 */
int checkReductionFactor(char *reductionFactorCLI)
{
    /* if reduction factor is an integer */
    if (atoi(reductionFactorCLI))
    {
        int reductionFactor = atoi(reductionFactorCLI);
        /* if reduction factor is less than or equal to 0 */
        if (reductionFactor <= 0)
        {
            /* print an error message        */
            printf("ERROR: Miscellaneous (reduction factor invalid)\n");
            /* return an error code          */
            return ERROR_MISCELLANEOUS; 
        }
    }
    else
    {   
        /* print an error message        */
        printf("ERROR: Miscellaneous (reduction factor invalid)\n");
        /* return an error code          */
        return ERROR_MISCELLANEOUS; 
    }

    /* ELSE return with success code */
    return EXIT_NO_ERRORS;
}

void freeImageData (unsigned char **imageData, int height)
{
    int i;
    for (i = 0; i < height; i++)
    {
        free(imageData[i]);
    }
    free(imageData);
}