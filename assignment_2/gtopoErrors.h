/* Constants */
#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

#define EXIT_NO_ERRORS 0
#define ERROR_BAD_ARGUMENT_COUNT 1
#define ERROR_BAD_FILE_NAME 2
#define ERROR_BAD_MAGIC_NUMBER 3
#define ERROR_BAD_COMMENT_LINE 4
#define ERROR_BAD_DIMENSIONS 5
#define ERROR_BAD_MAX_GRAY_VALUE 6
#define ERROR_IMAGE_MALLOC_FAILED 7
#define ERROR_BAD_DATA 8
#define ERROR_OUTPUT_FAILED 9
#define ERROR_MISCELLANEOUS 100

int checkArgumentCount(int argc, int numOfArgs);
int checkInputFile(FILE *filePointer, char *filename);
int checkWidthAndHeight(char *width, char *height);
int checkImageDataMemoryAllocation(FILE *filePointer, char *filename, short *imageData);
int checkPixelValue(FILE *filePointer, char *filename, short *imageData, int pixelValue);
int checkOutputFile(FILE *filePointer, char *filename, short *imageData);
int checknBytesWritten(FILE *filePointer, char *filename, short *imageData);