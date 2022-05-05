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
/* Takes in as input a file of     */
/* type .dem and outputs it to a   */
/* different file.                 */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* Libraries */
#include <stdio.h> //library for I/O routines
#include <stdlib.h> //library for memory routines

/* Header files */
#include "gtopoImage.h"
#include "gtopoErrors.h"

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: width                  */
/* argv[3]: height                 */
/* argv[4]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

short readValue(FILE *filePointer);

int main(int argc, char **argv)
{ /* main() */

	/* check for correct number of arguments */
    int r; //return value variable
    /* check if there were 3 CLI arguments   */
	// if((r = checkArgumentCount(argc, 3)) != 0)
    // {
    //     /* if there weren't 3 CLI arguments:   */
    //     if (r == -1)
    //     {
    //         /* if there were no CLI arguments    */
    //         /* output usage message and return 0 */
    //         printf("Usage: %s inputFile width height outputFile\n", argv[0]);
    //         return EXIT_NO_ERRORS;
    //     }
    //     /* else return the return value of the checkArgumentCount() */
    //     /* method (i.e, ERROR_BAD_ARGUMENT_COUNT=1)                 */
    //     return r;
    // }

    FILE *filePointer = fopen(argv[1], "r"); //open file in read mode.

	/* create an imagePtr to store the pgm image data as an Image struct */
    Image *imagePtr = malloc(sizeof(Image)); // dynamically allocate memory for imagePtr
    if ((r = createNewImage(imagePtr, argv[2], argv[3])) != 0) return r; // fills imagePtr struct field values with NULL data

    short x;

    for (int i=0; i<imagePtr->height; i++)
    {
        for (int j=0; j<imagePtr->width; j++)
        {
            short x = readValue(filePointer);
            printf("%d ", x);
        }
        printf("\n");
    }

    /* Read data from input file, store data in imagePtr                */
    /* Only return r (the return value) if it reading wasn't successful */
	if ((r = readGtopoFile(argv[1], imagePtr)) != 0) return r;

    /* Write data to output file and only return r (the return value) if it wasn't successful */
	if ((r = writeGtopoFile(argv[4], imagePtr)) != 0) return r;

	/* at this point, we are done and can exit with a success code */
    printf("ECHOED\n");
	return EXIT_NO_ERRORS;
} /* main() */

short readValue(FILE *filePointer)
{
    int left8bit;
    int right8bit;
    int scanCount;

    left8bit = 0;
    scanCount = fread(&left8bit, 1, 1, filePointer);
    left8bit -= 256;
    right8bit = 0;
    scanCount = fread(&right8bit, 1, 1, filePointer);
    right8bit -= 256;
    int16_t positiveRight8bit = right8bit & 255; //remove negative
    int16_t result = (left8bit << 8) | positiveRight8bit; // shift by 8 then join with right positiveRight8bit.

    return result;
}