/***********************************/
/* COMP 1921  Programming Project  */
/* Assignment_2                    */
/*                                 */
/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */
/*                                 */
/* Date commenced: 20/05/22        */
/***********************************/

/***********************************/
/* Reads a gtopo file and splits it*/
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
#include "gtopoImage.h"
#include "gtopoErrors.h"

//writeTiled function declared
int writeTiled(char *filename, Image *imagePointer, int reductionFactor);

/***********************************/
/* main routine                    */
/*                                 */
/* 4 CLI parameters:               */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: width                  */
/* argv[3]: height                 */
/* argv[4]: int tiling factor      */
/* argv[5]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{ /* main() */

    /* check for correct number of arguments */
    int returnVal; //return value variable
    /* check if there were 6 CLI arguments   */
	if((returnVal = checkArgumentCount(argc, 6)) != 0)
    {
        /* if there weren't 4 CLI arguments:   */
        if (returnVal == -1)
        {
            /* if there were no CLI arguments    */
            /* output usage message and return 0 */
            printf("Usage: %s inputFile width height tiling_factor outputFile_<row>_<column>\n", argv[0]);
            return EXIT_NO_ERRORS;
        }
        /* else return the return value of the checkArgumentCount() method */
        return returnVal;
    }

    /* Check tiling factor is valid */
    if((returnVal = validateFactorInput(argv[4])) != 0) return returnVal;
    /* Check outputfile template format is valid */
    if((returnVal = validateTileOutputTemplate(argv[5])) != 0) return returnVal;
	
	/* create an imagePtr to store the gtopo image data as an Image struct */
    Image *imagePtr = malloc(sizeof(Image)); // dynamically allocate memory for imagePtr

    /* Read data from input file, store data in imagePtr                */
    /* Only return returnVal if it reading wasn't successful */
    if ((returnVal = readGtopoFile(argv[1], imagePtr, argv[2], argv[3])) != 0) return returnVal;

    /* - Tile the file - */
    int tilingFactor = atoi(argv[4]); //get the tiling factor.
    /* Call the writeTiled - only return returnVal if not successful */
    if ((returnVal = writeTiled(argv[5], imagePtr, tilingFactor)) != 0) return returnVal;

	/* at this point, we are done and can exit with a success code */
    printf("TILED\n");
	return EXIT_NO_ERRORS;
} /* main() */

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
    int sizeOfTileSuffix = strlen("_x_y");
    char *tiledImageFilename = malloc(sizeof(filename) * tilingFactor * tilingFactor * sizeOfTileSuffix);

    /* filename is truncated so that it removes the template suffix, */
    /* so that it only contains the base name of the file.           */
    int sizeOfTemplateSuffix = strlen("_<row>_<column>");
    filename[strlen(filename)-sizeOfTemplateSuffix] = '\0';

    /* define for-loop variable counters: */
    int rowPosition;
    int columnPosition;

    /* iterate through the row and column tilingFactor permutations */
    for (rowPosition = 0; rowPosition < tilingFactor; rowPosition++)
    {
        for (columnPosition = 0; columnPosition < tilingFactor; columnPosition++)
        { /*per tiled image*/
            /* Construct tiledImageFilename (the current tile file to write to) to by */
            /* concatenating: (filename, '_', rowPosition, '_', columnPosition).      */
            sprintf(tiledImageFilename, "%s%c%d%c%d", filename,'_', rowPosition, '_', columnPosition);

            /* open the current tile as a file for writing               */
            FILE *outputFile = fopen(tiledImageFilename, "w");
            int returnVal;  //return value variable
            /* check whether file opening worked - only return returnVal if unsuccessful */
            if ((returnVal = checkOutputFile(outputFile)) != 0) return returnVal;

            /* Create variables for the tile image's width and height after it has been reduced */
            int reducedWidth = (imagePointer->width)/(tilingFactor);
            int reducedHeight = (imagePointer->height)/(tilingFactor);

            /* define for-loop variable counters: */
            int rowIndex;
            int columnIndex;
            /* nested iteration through each element/pixelValue in the imageData array, */
            /* BUT each loop starts at the relative position on the grid for that tile.   */
            for (rowIndex = rowPosition*reducedHeight; rowIndex < rowPosition*reducedHeight + reducedHeight; rowIndex++)
            { /*per row of pixels*/
                for (columnIndex = columnPosition*reducedWidth; columnIndex < columnPosition*reducedWidth + reducedWidth; columnIndex++)
                { /*per pixel*/

                    /* write the current pixel to the file */
                    writeValue(outputFile, &imagePointer->imageData[rowIndex][columnIndex]);

                } /*per pixel*/
            } /*per row of pixels*/

            /* reset tiledImageFilename by removing suffix (i.e. "_x_y")     */
            tiledImageFilename[strlen(tiledImageFilename)-sizeOfTileSuffix] = '\0';


        } /*per tiled image*/
    }
    
    /* no errors so exit with success return code */
    return EXIT_NO_ERRORS;
}