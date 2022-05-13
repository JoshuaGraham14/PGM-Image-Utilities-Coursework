#ifndef IMAGE_HEADER_FILE
#define IMAGE_HEADER_FILE

typedef struct ImageStruct
{
    unsigned char magic_number[2];
	unsigned short *magic_Number;
	char *commentLine;
	unsigned int width;
    unsigned int height;
	unsigned int maxGray;
	unsigned char **imageData;
} Image;

/* FUNC: fills imagePointer with NULL data values for Image struct */
void createNewImage(Image *imagePointer);

/* FUNC: collection of other pgmImage methods - used to read in a pgmFile */
int readpgmFile(char *filename, Image *imagePointer, int mode);

/* FUNC: reads the Image magic number */
int readMagicNumber (FILE *filePointer, char *filename, Image *imagePointer, int mode);

/* FUNC: reads the Image comment line */
int readCommentLine (FILE *filePointer, char *filename, Image *imagePointer);

/* FUNC: reads the Image dimensions */
int readDimensions (FILE *filePointer, char *filename, Image *imagePointer);

/* FUNC: reads the Image max gray */
int readMaxGray (FILE *filePointer, char *filename, Image *imagePointer);

/* FUNC: reads the Image imageData */
int readImageData (FILE *filePointer, char *filename, Image *imagePointer);

/* FUNC: writes to an input file data from an input Image */
int writepgmFile(char *filename, Image *imagePointer);

#endif