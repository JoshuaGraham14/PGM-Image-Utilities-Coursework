/* Joshua Graham                   */
/* ID: 201496708                   */
/* sc21jg@leeds.ac.uk              */

GTOPO Utilities README file


INSTRUCTIONS
------------

To run:
- First clean the makefile: 'make clean'.
- Then make the makefile: 'make all'
- Then run either one of the following programs by writing ".\<name> <args>":
    - gtopoEcho
    - gtopoComp
    - gtopoReduce
    - gtopoTile
    - gtopoAssemble
    - gtopoPrintLand
    - gtopoAssembleReduce


MODULES
-------

- Module gtopoEcho.c -
Takes in as input a file and outputs it to a different file.
INPUTS: 4 command-line parameters: 
        - inputImage - gtopo filename
        - width of image
        - height of image
        - outputImage - gtopo filename
OUTPUTS: a copy of the inputImage gtopo file to the outputImage file. Return 0 (success) 
         + message reading "ECHOED".

- Module gtopoComp.c -
Takes in two inputs and compares them to see if they are 'logically identical'.
INPUTS: 4 command-line parameters:
        - firstImage - gtopo filename
        - width of image
        - height of image
        - secondImage - gtopo filename
OUTPUTS: return 0 (success) + message reading "IDENTICAL" if the two files were identical,
         OR message reading "DIFFERENT if the two files were not identical.

- Module gtopoReduce.c -
Takes in an input file (either ASCII or binary) and reduces the file by a factor of 
'intFactor' in each dimension.
INPUTS: 5 command-line parameters:
        - inputImage - gtopo filename
        - width of image
        - height of image
        - intFactor - reduction factor n,
        - outputImage - gtopo filename.
OUTPUTS: the reduced file. Return 0 (success) + message reading "REDUCED".

- Module gtopoTile.c -
Reads a gtopo file and splits it into nxn smaller images, with corresponding 
position to the original image.
INPUTS: 5 command-line parameters:
        - inputImage - gtopo filename
        - width of image
        - height of image
        - intFactor - reduction factor n,
        - outputFile - output file template name.
OUTPUTS: n * n smaller images, tiled according to rows and columns. Return 0 (success) + message reading "TILED".

- Module gtopoAssemble.c -
Assembles a large image from smaller ones. 
INPUTS: 3+5i command-line parameters:
        - outputFile - gtopo file name,
        - width - of outputFile
        - height - of outputFile
Remainder: quintuplets of:
        - row - start row position
        - column - start column position
        - subimage to insert
        - width - of subimage
        - height - of subimage
OUTPUTS: the assembled image from the provided smaller images. Return 0 (success) + message reading "ASSEMBLED".

- Module gtopoPrintLand.c -
Takes a single gtopo30 file and outputs the 2D array to a .txt file as a visual representation.
INPUTS: 7 command-line parameters:
        - inputFile - gtopo file name
        - width - of outputFile
        - height - of outputFile
        - outputFile - .txt file name
        - row - start row position
        - sea - int value of sea
        - hill - int value of hill
        - mountain - int value of mountain
OUTPUTS: A visual representation of the 2D array as a .txt file. Return 0 (success) + message reading "PRINTED".

- Module gtopoAssembleReduce.c -
Assembles a large image from smaller ones and then reduces the large image by the reduction factor.
INPUTS: 4+5i command-line parameters:
        - outputFile - gtopo file name
        - width - of outputFile
        - height - of outputFile
        - intFactor - reduction factor n,
Remainder: quintuplets of:
        - row - start row position
        - column - start column position
        - subimage to insert
        - width - of subimage
        - height - of subimage
OUTPUTS: a gtopo file of the assembled and then reduced image. Return 0 (success) + message reading "ASSEMBLERDEDUCED".