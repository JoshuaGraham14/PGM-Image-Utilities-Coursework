/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_1                    */
/* TASK III                        */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 14/03/22        */
/***********************************/

/***********************************/
/* Takes in an ASCII pgm file      */
/* and outputs a binary pgm file.  */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* Libraries */
#include <stdio.h> //library for I/O routines
#include <stdlib.h> //library for memory routines

/* Header files */
#include "pgmErrors.h"
#include "pgmImage.h"

int main(int argc, char **argv)
{ /* main() */
	
    /* check for correct number of arguments */
    int r; //return value variable
    /* check if there were 3 CLI arguments   */
	if((r = checkArgumentCount(argc, 3)) != 0)
    {
        /* if there weren't 3 CLI arguments:   */
        if (r == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() method */
        return r;
    }

	/* create an imagePtr to store the pgm image data as an Image struct */
    Image *imagePtr = malloc(sizeof(Image)); // dynamically allocate memory for imagePtr
    createNewImage(imagePtr); // fills imagePtr1 struct field values with NULL data 

    /* Read data from input file, store data in imagePtr                */
    /* Only return r (the return value) if it reading wasn't successful */
    if ((r = readpgmFile(argv[1], imagePtr)) != 0) return r;

    /* Set the magicNumber to "P5" as the ASCII file will be written to in binary */
    imagePtr->magic_number[1] = '5';

    /* Write data to output file and only return r (the return value) if it wasn't successful */
    if ((r = writepgmFile(argv[2], imagePtr)) != 0) return r;

	/* at this point, we are done and can exit with a success code */
    printf("CONVERTED\n");
	return EXIT_NO_ERRORS;
} /* main() */