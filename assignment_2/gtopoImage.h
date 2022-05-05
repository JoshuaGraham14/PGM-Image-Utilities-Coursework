typedef struct ImageStruct
{
	unsigned int width;
    unsigned int height;
	unsigned char *imageData;
} Image;

void createNewImage(Image *imagePointer);
int readGtopoFile(char *filename, Image *imagePointer);
int writeGtopoFile(char *filename, Image *imagePointer);