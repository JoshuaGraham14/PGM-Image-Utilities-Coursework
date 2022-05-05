typedef struct ImageStruct
{
	unsigned int width;
    unsigned int height;
	unsigned char *imageData;
} Image;

int createNewImage(Image *imagePointer, char *width, char *height);
int readGtopoFile(char *filename, Image *imagePointer);
int writeGtopoFile(char *filename, Image *imagePointer);
short readValue(FILE *filePointer);