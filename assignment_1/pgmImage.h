typedef struct ImageStruct
{
    unsigned char magic_number[2];
	unsigned short *magic_Number;
	char *commentLine;
	unsigned int width;
    unsigned int height;
	unsigned int maxGray;
	unsigned char *imageData;
} Image;

void createNewImage(Image *imagePointer);
int readpgmFile(char *filename, Image *imagePointer);
int readMagicNumber (FILE *filePointer, char *filename, Image *imagePointer);
int readCommentLine (FILE *filePointer, char *filename, Image *imagePointer);
int readDimensions (FILE *filePointer, char *filename, Image *imagePointer);
int readMaxGray (FILE *filePointer, char *filename, Image *imagePointer);
int readImageData (FILE *filePointer, char *filename, Image *imagePointer);

int writepgmFile(char *filename, Image *imagePointer);