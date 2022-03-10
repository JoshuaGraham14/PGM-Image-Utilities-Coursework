int checkMagicNumber(FILE *filePointer, char *filename, unsigned short magic_number, int MAGIC_NUMBER_ASCII_PGM);
int checkCommentLine(FILE *filePointer, char *filename, char *commentLine, int MAX_COMMENT_LINE_LENGTH);
int checkSizeAndGrays(FILE *filePointer, char *filename, int scanCount, int width, int height, int MIN_IMAGE_DIMENSION, int MAX_IMAGE_DIMENSION, int maxGray, char *commentLine);
int checkImageDataMemoryAllocation(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine);
int checkImageValue(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine, int scanCount, int grayValue);
int checkOutputFile(FILE *filePointer, char *filename, unsigned char *imageData, char *commentLine);