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
/* Reads a pgm file and splits it  */
/* into nxn smaller images, with   */
/* corresponding position to the   */
/* original image.                 */ 
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

/* FUNC: Check tiling output file template is correct */
int validateTileOutputTemplate(char *outputTemplateString);

/* FUNC: splits the input image into tilingFactor *   */
/* tilingFactor smaller images corresponding to parts */
/* of the image.                                      */
int writeTiled(char *filename, Image *imagePointer, int reductionFactor);

/***********************************/
/* main routine                    */
/*                                 */
/* 4 CLI parameters:               */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: int tiling factor      */
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

    /* Check tiling factor is valid */
    if((returnVal = validateFactorInput(argv[2])) != 0) return returnVal;
    /* Check outputfile template format is valid */
    if((returnVal = validateTileOutputTemplate(argv[3])) != 0) return returnVal;
	
	/* create an imagePtr to store the pgm image data as an Image struct */
    Image *imagePtr = malloc(sizeof(Image)); // dynamically allocate memory for imagePtr

    /* Read data from input file, store data in imagePtr                */
    /* Only return returnVal if reading wasn't successful */
	if ((returnVal = readpgmFile(argv[1], imagePtr, 0)) != 0) return returnVal;

    /* - Tile the file - */
    int tilingFactor = atoi(argv[2]); //get the tiling factor.
    /* Call the writeTiled - only return returnVal if not successful */
    if ((returnVal = writeTiled(argv[3], imagePtr, tilingFactor)) != 0) return returnVal;

	/* at this point, we are done and can exit with a success code */
    printf("TILED\n");
	return EXIT_NO_ERRORS;
} /* main() */

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
    char *targetString = "_<row>_<column>.pgm";

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
/* FUNC: writeTiled                       */
/* -> splits the input image into         */
/* tilingFactor * tilingFactor smaller    */
/* images corresponding to parts of the   */
/* image.                                 */
/*                                        */
/* Parameters:                            */
/* - filename: filename string            */
/* - imagePointer: Image pointer          */
/* - tilingFactor: Tiling Factor          */
/* Returns: - 0 on success                */
/*          - non-zero error code on fail */
/******************************************/
int writeTiled(char *filename, Image *imagePointer, int tilingFactor)
{
    /* Dynamically allocate memory for tiledImageFilename.                              */
    int sizeOfTileSuffix = strlen("_x_y.pgm");
    char *tiledImageFilename = malloc(sizeof(filename) * tilingFactor * tilingFactor * sizeOfTileSuffix);

    /* filename is truncated so that it removes the template suffix, */
    /* so that it only contains the base name of the file.           */
    int sizeOfTemplateSuffix = strlen("_<row>_<column>.pgm");
    filename[strlen(filename)-sizeOfTemplateSuffix] = '\0';

    /* define for-loop variable counters: */
    int rowPosition;
    int columnPosition;

    /* iterate through the row and column tilingFactor permutations */
    for (rowPosition = 0; rowPosition < tilingFactor; rowPosition++)
    {
        for (columnPosition = 0; columnPosition < tilingFactor; columnPosition++)
        { /*per tiled image*/
            /* Construct tiledImageFilename (the current tile file to write to) to by   */
            /* concatenating: (filename, '_', rowPosition, '_', columnPosition, ".pgm"). */
            sprintf(tiledImageFilename, "%s%c%d%c%d%s", filename,'_', rowPosition, '_', columnPosition,".pgm");

            /* open the current tile as a file for writing               */
            FILE *outputFile = fopen(tiledImageFilename, "w");
            int returnVal;  //return value variable
            /* check whether file opening worked - only return returnVal if unsuccessful */
            if ((returnVal = checkOutputFile(outputFile)) != 0) return returnVal;

            /* Create variables for the tile image's width and height after it has been reduced */
            int reducedWidth = (imagePointer->width)/(tilingFactor);
            int reducedHeight = (imagePointer->height)/(tilingFactor);

            /* write magic number, reduced size & gray value for the tiled image */
            size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", imagePointer->magic_number[1], reducedWidth, reducedHeight, imagePointer->maxGray);
            /* check that dimensions wrote correctly - return returnVal only if not successful */
            if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return returnVal;

            /* define for-loop variable counters: */
            int columnIndex;
            int rowIndex;

            /* nested iteratation through each element/pixelValue in the imageData array, */
            /* BUT each loop starts at the relative position on the grid for that tile.   */
            for (columnIndex = rowPosition*reducedHeight; columnIndex < rowPosition*reducedHeight + reducedHeight; columnIndex++)
            { /*per row of pixels*/
                for (rowIndex = columnPosition*reducedWidth; rowIndex < columnPosition*reducedWidth + reducedWidth; rowIndex++)
                { /*per pixel*/
                    /* IF: the image is in ASCII format:   */
                    if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
                    {
                        /* write the entry & whitespace  */
                        nBytesWritten = fprintf(outputFile, "%d ", imagePointer->imageData[columnIndex][rowIndex]);
                    }
                    /* ELSE: the image is in binary format: */
                    else 
                    {
                        /* write the entry in binary */
                        fwrite(&imagePointer->imageData[columnIndex][rowIndex], 1, 1, outputFile);
                    }

                    /* sanity check on write, by calling checknBytesWritten */
                    if ((returnVal = checknBytesWritten(nBytesWritten)) != 0) return returnVal;
                } /*per pixel*/

                /* If the image is in ASCII format add a newline at the end of row column cycle */
                if(*imagePointer->magic_Number == MAGIC_NUMBER_ASCII_PGM)
                {
                    fprintf(outputFile, "%c", '\n');
                }

            } /*per row of pixels*/

            /* reset tiledImageFilename by removing suffix (i.e. "_x_y.pgm")     */
            tiledImageFilename[strlen(tiledImageFilename)-sizeOfTileSuffix] = '\0';
        } /*per tiled image*/
    }
    
    /* no errors so exit with success return code */
    return EXIT_NO_ERRORS;
}