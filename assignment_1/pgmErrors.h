int checkInputFile(FILE *filePointer);
int checkMagicNumber(FILE *filePointer, char *filename, unsigned short magic_number);
int checkCommentLine(FILE *filePointer, char *filename, char *commentLine);
int checkDimensionsAndGrays(FILE *filePointer, char *filename, int scanCount, int width, int height, int maxGray, char *commentLine);
int checkImageDataMemoryAllocation(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine);
int checkPixelValue(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine, int scanCount, int grayValue);
int checkOutputFile(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine);
int checknBytesWritten(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine, size_t nBytesWritten);