typedef struct ImageStruct
{
	unsigned int width;
    unsigned int height;
	short **imageData;
} Image;

int createNewImage(Image *imagePointer, char *width, char *height);

int readGtopoFile(char *filename, Image *imagePointer);
int readImageData (FILE *filePointer, char *filename, Image *imagePointer);

int writeGtopoFile(char *filename, Image *imagePointer);

int getImageSize(FILE *filePointer);
short readValue(FILE *filePointer);
void writeValue(FILE *filePointer, short *valueToWrite);