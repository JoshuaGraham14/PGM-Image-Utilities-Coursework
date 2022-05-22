#ifndef IMAGE_HEADER_FILE
#define IMAGE_HEADER_FILE

//ImageStruct will store the data for a gtopo image.
typedef struct ImageStruct
{
	unsigned int width; //Width of the gtopo image.
    unsigned int height; //Height of the gtopo image.
	short **imageData; //A 2d array containing the value of every pixel in the image.
} Image;

/* FUNC: collection of other gtopoImage methods - used to read in a gtopo file */
int readGtopoFile(char *filename, Image *imagePointer, char *width, char *height);

/* FUNC: fills imagePointer with NULL data values for Image struct */
int initialiseImage(Image *imagePointer, char *width, char *height);

/* FUNC: reads the Image imageData */
int readImageData (FILE *filePointer, Image *imagePointer);

/* FUNC: dynamically allocates memory to imageData array */
int mallocImageDataArray(Image *imagePointer);

/* FUNC: writes to an input file data from an input Image */
int writeGtopoFile(char *filename, Image *imagePointer, int reductionFactor);

/* FUNC: gets the size of a gtopo Image */
int getImageSize(FILE *filePointer);

/* FUNC: reads the next value from the provided file and returns it */
short readValue(FILE *filePointer);

/* FUNC: writes the provided pixel (valueToWrite) to the provided file */
void writeValue(FILE *filePointer, short *valueToWrite);

#endif