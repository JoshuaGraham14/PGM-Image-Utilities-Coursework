/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_2                    */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 22/05/22        */
/***********************************/

/***********************************/
/*                                      */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* Libraries */
#include <stdio.h> //library for I/O routines
#include <stdlib.h> //library for memory routines
#include <string.h> //library for string manipulation

/* Header files */
#include "gtopoImage.h"
#include "gtopoErrors.h"

int validateSeaHillMountain(char *sea, char *hill, char *mountain);

//printImageToFile function declared
int printImageToFile(Image *imageToPrint, char *filename, char *sea, char *hill, char *mountain);

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: width                  */
/* argv[3]: height                 */
/* argv[4]: output file name       */
/* argv[5]: sea value              */
/* argv[6]: hill value             */
/* argv[7]: mountain value         */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{ /* main() */

	/* check for correct number of arguments */
    int returnVal; //return value variable
    /* check if there were 8 CLI arguments   */
	if((returnVal = checkArgumentCount(argc, 8)) != 0)
    {
        /* if there weren't 8 CLI arguments:   */
        if (returnVal == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: %s inputFile width height outputFile sea hill mountain\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() method */
        return returnVal;
    }

	/* create an imagePtr to store the gtopo image data as an Image struct */
    Image *imageToPrint = malloc(sizeof(Image)); //dynamically allocate memory for imagePtr

    /* Read data from the Image file and only return returnVal if it wasn't successful */
    if ((returnVal = readGtopoFile(argv[1], imageToPrint, argv[2], argv[3])) != 0) return returnVal;

    /* print the data of imageToPrint to the file: */
    if ((returnVal = printImageToFile(imageToPrint, argv[4], argv[5], argv[6], argv[7])) != 0) return returnVal;
    
    printf("PRINTED\n");
	return EXIT_NO_ERRORS;
} /* main() */


int printImageToFile(Image *imageToPrint, char *filename, char *sea, char *hill, char *mountain)
{
    int returnVal;  //return value variable

    //Validate sea, hill and mountain inputs
    if ((returnVal = validateSeaHillMountain(sea, hill, mountain)) != 0) return returnVal;

    /* open a file for writing */
	FILE *outputFile = fopen(filename, "w");
    /* check whether file opening worked - return returnVal only if not successful */
    if ((returnVal = checkOutputFile(outputFile)) != 0) return returnVal;

    /* define for-loop variable counters: */
    int rowIndex;
    int columnIndex;
    /* nested iteratation through each element/pixelValue in the imageData array   */
    for (rowIndex = 0; rowIndex < imageToPrint->height; rowIndex++)
    { /*per row of pixels*/
        for (columnIndex = 0; columnIndex < imageToPrint->width; columnIndex++)
        { /*per pixel*/

            /* write the entry  */
            if (imageToPrint->imageData[rowIndex][columnIndex] <= atoi(sea))
            {
                fprintf(outputFile, "%c", ' ');
            }
            else if (imageToPrint->imageData[rowIndex][columnIndex] > atoi(sea) && imageToPrint->imageData[rowIndex][columnIndex] <= atoi(hill))
            {
                fprintf(outputFile, "%c", '.');
            }
            else if (imageToPrint->imageData[rowIndex][columnIndex] > atoi(hill) && imageToPrint->imageData[rowIndex][columnIndex] <= atoi(mountain))
            {
                fprintf(outputFile, "%c", '^');
            }
            else if (imageToPrint->imageData[rowIndex][columnIndex] > atoi(mountain))
            {
                fprintf(outputFile, "%c", 'A');
            }

        } /*per pixel*/

        fprintf(outputFile, "%c", '\n');
    } /*per row of pixels*/

    fclose(outputFile);
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
int validateSeaHillMountain(char *sea, char *hill, char *mountain)
{
    if ((atoi(sea) || strcmp(sea, "0") == 0) &&
    (atoi(hill) || strcmp(hill, "0") == 0) &&
    (atoi(mountain) || strcmp(mountain, "0") == 0))
    {
        int seaInt = atoi(sea);
        int hillInt = atoi(hill);
        int mountainInt = atoi(mountain);
        /* if width or height are greater than 0 */
        if ((seaInt >= -9999 && seaInt <= 9999) &&
        (hillInt >= -9999 && hillInt <= 9999) &&
        (mountainInt >= -9999 && mountainInt <= 9999))
        {
            /* return with success code */
            return EXIT_NO_ERRORS;
        }
    }

    /* Unsuccessful, so print an error message: */ 
    printf("ERROR: Miscellaneous (sea hill or mountain values not valid)\n");
    /* and return an error code.         */
    return ERROR_MISCELLANEOUS; 
}