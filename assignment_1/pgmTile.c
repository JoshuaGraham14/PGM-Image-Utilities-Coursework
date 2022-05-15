/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_1                    */
/* TASK V                          */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 13/03/22        */
/***********************************/

/***********************************/
/* Reads two pgm files and compares*/
/* them to see if they are         */
/* logically equivalent.           */ 
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* Libraries */
#include <stdio.h> //library for I/O routines
#include <stdlib.h> //library for memory routines
#include <string.h> //library for string manipulation

/* Header files */
#include "pgmImage.h"
#include "pgmErrors.h"

//tileImages function declared
int writeTiles(char *filename, Image *imagePointer, int reductionFactor);

/***********************************/
/* main routine                    */
/*                                 */
/* 4 CLI parameters:               */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: int reduction factor   */
/* argv[3]: ouput file name        */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{ /* main() */

    /* check for correct number of arguments */
    int returnVal; //return value variable
    /* check if there were 4 CLI arguments   */
	if((returnVal = checkArgumentCount(argc, 4)) != 0)
    {
        /* if there weren't 4 CLI arguments:   */
        if (returnVal == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: %s inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() method */
        return returnVal;
    }

    /* Check reduction factor is valid */
    if((returnVal = validateFactorInput(argv[2])) != 0) return returnVal;
    if((returnVal = validateTileOutputTemplate(argv[3])) != 0) return returnVal;
	
	/* create an imagePtr to store the pgm image data as an Image struct */
    Image *imagePtr = malloc(sizeof(Image)); // dynamically allocate memory for imagePtr
    createNewImage(imagePtr); // fills imagePtr struct field values with NULL data 

    /* Read data from input file, store data in imagePtr                */
    /* Only return returnVal (the return value) if it reading wasn't successful */
	if ((returnVal = readpgmFile(argv[1], imagePtr, 0)) != 0) return returnVal;

    /* Tile the file */
    int reductionFactor = atoi(argv[2]); //get the reduction factor.
    /* Call the write reduced function - return returnVal only if not successful */
    if ((returnVal = writeTiles(argv[3], imagePtr, reductionFactor)) != 0) return returnVal;

	/* at this point, we are done and can exit with a success code */
    printf("TILED\n");
	return EXIT_NO_ERRORS;
} /* main() */

/***********************************/
/* FUNC: writeReduced              */
/*                                 */
/* Parameters:                     */
/* - filename: filename string     */
/* - imagePointer: Image pointer   */
/* - reductionFactor: Reduction Factor */
/*                                 */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int writeTiles(char *filename, Image *imagePointer, int reductionFactor)
{
    int height = imagePointer->height;
    int width = imagePointer->width;

    int ogSize = sizeof(filename);

    char *filenameToWrite = malloc(ogSize * 8 * reductionFactor * reductionFactor);
    filename[strlen(filename)-19] = '\0';
    //printf("%s", filenameToWrite);

    int i;
    int j;
    for (i = 0; i < reductionFactor; i++)
    {
        for (j = 0; j < reductionFactor; j++)
        {
            sprintf(filenameToWrite, "%s%c%d%c%d%s", filename,'_', i, '_', j,".pgm");
            /* open a file for writing               */
            FILE *outputFile = fopen(filenameToWrite, "w");
            int returnVal;  //return value variable
            /* check whether file opening worked - return returnVal only if not successful */
            if ((returnVal = checkOutputFile(outputFile)) != 0) return returnVal;

            int reducedWidth = (imagePointer->width)/(reductionFactor);
            int reducedHeight = (imagePointer->height)/(reductionFactor);

            /* write magic number, reduced size & gray value */
            size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", imagePointer->magic_number[1], reducedWidth, reducedHeight, imagePointer->maxGray);
            /* check that dimensions wrote correctly - return returnVal only if not successful */
            if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return returnVal;

            int x;
            int y;
            for (x = i*reducedHeight; x < i*reducedHeight + reducedHeight; x++)
            {
                for (y = j*reducedWidth; y < j*reducedWidth + reducedWidth; y++)
                {
                    //printf("%d\n", imagePointer->imageData[x][y]);
                    /* write the entry & whitespace  */
                    if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
                    {
                        nBytesWritten = fprintf(outputFile, "%d ", imagePointer->imageData[x][y]);
                    }
                    else 
                    {
                        //printf("\n%d, %d", imagePointer->imageData[i][j], &imagePointer->imageData[i][j]);
                        fwrite(&imagePointer->imageData[x][y], 1, 1, outputFile);
                    }

                    /* sanity check on write         */
                    if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return returnVal;
                }
                if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
                {
                    fprintf(outputFile, "%c", '\n');
                }
            }
            filenameToWrite[strlen(filenameToWrite)-8] = '\0';
        }
    }
    
    /* no errors so exit with return with success code */
    return EXIT_NO_ERRORS;
}