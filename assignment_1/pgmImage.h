#ifndef IMAGE_HEADER_FILE
#define IMAGE_HEADER_FILE

//ImageStruct will store the data for a pgm image.
typedef struct ImageStruct
{
    unsigned char magic_number[2]; //A "magic number" for identifying the file type (either 'P2' or 'P5').
	unsigned short *magic_Number; //A pointer to the magic_number char array.
	char *commentLine; //A string of characters forming a comment line (if a line starts with #).
	unsigned int width; //Width of the pgm image.
    unsigned int height; //Height of the pgm image.
	unsigned int maxGray; //The maximum gray value in the pgm image.
	unsigned char **imageData; //A 2d array containing the grey value of every pixel in the image.
} Image;

/* FUNC: collection of other pgmImage methods - used to read in a pgm file */
int readpgmFile(char *filename, Image *imagePointer, int mode);

/* FUNC: fills imagePointer with NULL data values for Image struct */
void createNewImage(Image *imagePointer);

/* FUNC: reads the Image magic number */
int readMagicNumber (FILE *filePointer, Image *imagePointer, int mode);

/* FUNC: reads the Image comment line */
int readCommentLine (FILE *filePointer, Image *imagePointer);

/* FUNC: reads the Image dimensions */
int readDimensions (FILE *filePointer, Image *imagePointer);

/* FUNC: reads the Image max gray */
int readMaxGray (FILE *filePointer, Image *imagePointer);

/* FUNC: reads the Image imageData */
int readImageData (FILE *filePointer, Image *imagePointer);

/* FUNC: dynamically allocates memory to imageData array */
int mallocImageDataArray(Image *imagePointer);

/* FUNC: writes to an input file data from an input Image */
int writepgmFile(char *filename, Image *imagePointer, int reductionFactor);

#endif