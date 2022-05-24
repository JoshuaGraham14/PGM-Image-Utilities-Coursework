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
/* Takes a single gtopo30 file and */
/* outputs the 2D array to a .txt  */
/* file as a visual representation.*/
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

/*FUNC: validates the three inputs to see if they are integers and greater than 0. */
int validateSeaHillMountain(char *sea, char *hill, char *mountain);

/*FUNC: prints inputted Image to file in the specified format, with terrain*/
/* outputted relative to the sea, hill and mountain inputted values.       */
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
    Image *imageToPrint = malloc(sizeof(Image)); //dynamically allocate memory for imageToPrint

    /* Read data from the Image file and only return returnVal if it wasn't successful */
    if ((returnVal = readGtopoFile(argv[1], imageToPrint, argv[2], argv[3])) != 0) return returnVal;

    /* print the data of imageToPrint to the file: */
    if ((returnVal = printImageToFile(imageToPrint, argv[4], argv[5], argv[6], argv[7])) != 0) return returnVal;
    
    printf("PRINTED\n");
	return EXIT_NO_ERRORS;
} /* main() */


/******************************************/
/* FUNC: printImageToFile                 */
/* ->  prints inputted Image to file in   */
/* the specified format, with terrain     */
/* outputted relative to the sea, hill    */
/* and mountain inputted values.          */
/*                                        */
/* Parameters:                            */
/* - imagePointer: Image pointer to print */
/* - filename: char pointer               */
/* - sea: char pointer to sea value       */
/* - hill: char pointer to hill value     */
/* - mountain: char pointer to mountain value */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int printImageToFile(Image *imageToPrint, char *filename, char *sea, char *hill, char *mountain)
{
    int returnVal; //return value variable

    //First validate sea, hill and mountain values
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

            /* Write the entry to the file:  */
            // Sea (i.e. value 􏰁 sea) -> print ' '
            if (imageToPrint->imageData[rowIndex][columnIndex] <= atoi(sea))
            {
                fprintf(outputFile, "%c", ' ');
                printf(" ");
            }
            // Low ground (sea < value <= hill) -> print '.'
            else if (imageToPrint->imageData[rowIndex][columnIndex] > atoi(sea) && imageToPrint->imageData[rowIndex][columnIndex] <= atoi(hill))
            {
                fprintf(outputFile, "%c", '.');
                printf(".");
            }
            // High ground (hill < value <= mountain) -> print '^'
            else if (imageToPrint->imageData[rowIndex][columnIndex] > atoi(hill) && imageToPrint->imageData[rowIndex][columnIndex] <= atoi(mountain))
            {
                fprintf(outputFile, "%c", '^');
                printf("^");
            }
            // Mountains (mountain < value) -> print 'A'
            else if (imageToPrint->imageData[rowIndex][columnIndex] > atoi(mountain))
            {
                fprintf(outputFile, "%c", 'A');
                printf("A");
            }

        } /*per pixel*/

        /* print newline at the end of every row */
        fprintf(outputFile, "%c", '\n');
        printf("\n");
    } /*per row of pixels*/

    fclose(outputFile); //close the file
    return EXIT_NO_ERRORS;
}

/******************************************/
/* FUNC: validateSeaHillMountain          */
/* ->  checks that inputted 'sea' and     */
/* 'hill' and 'mountain' values are all   */
/* integers and greater than or equal to  */
/* zero.                                  */
/*                                        */
/* Parameters:                            */
/* - sea: char pointer to sea value       */
/* - hill: char pointer to hill value     */
/* - mountain: char pointer to mountain value */
/* Returns: - 0 on success                */
/*          - ERROR_MISCELLANEOUS on fail */
/******************************************/
int validateSeaHillMountain(char *sea, char *hill, char *mountain)
{
    /* check IF sea, hill and mountain are both integers (including 0)*/
    if ((atoi(sea) || strcmp(sea, "0") == 0) &&
    (atoi(hill) || strcmp(hill, "0") == 0) &&
    (atoi(mountain) || strcmp(mountain, "0") == 0))
    {
        /* Convert sea, hill and mountain to integers */
        int seaInt = atoi(sea);
        int hillInt = atoi(hill);
        int mountainInt = atoi(mountain);
        /* check IF sea, hill and mountain are all within bounds */
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