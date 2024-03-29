# Pgm Utlities Tool

**_Tools for the manipulation of pgm images_**

Instructions
------------

To run:
- First clean the makefile: 'make clean'.
- Then make the makefile: 'make all'
- Then run either one of the following programs by writing ".\\\<name>" followed by the arguments:
    - pgmEcho
    - pgmComp
    - pgma2b
    - pgmb2a
    - pgmReduce
    - pgmTile
    - pgmAssemble


Modules
-------

**Module pgmEcho.c**
- Takes in as input a file of type .pgm and outputs it to a different file.
    - INPUTS: command-line parameters: inputImage, outputImage.
    - OUTPUTS: outputImage file contains a copy of the inputImage pgm file.

**Module pgmComp.c**
- Takes in two inputs as file of type .pgm and compares them to see if they are 'logically identical'.
    - INPUTS: command-line parameters: image1, image2.
     - OUTPUTS: return 0 (success) + print statement reading "IDENTICAL: The two files were identical" if the two images are identical OR print statement reading "DIFFERENT: The two files were not identical".

**Module pgma2b.c**
- Takes in ASCII form of pgm file and converts to binary
    - INPUTS: command-line parameters: ASCII formatted pgm file, fileLocation2.
    - OUTPUTS: return 0 (success) + print statement reading "CONVERTED: The file was converted".

**Module pgma2a.c**
- Takes in binary form of pgm file and converts to ASCII
    - INPUTS: command-line parameters: binary formatted pgm file, fileLocation2.
    - OUTPUTS: return 0 (success) + print statement reading "CONVERTED: The file was converted".

**Module pgmReduce.c**
- Takes in an input file of type .pgm (either ASCII or binary) and firstly convert it to ASCII if it is of type binary, using the pgma2a.c module. The input file is then reduced by a factor of 'intFactor' in each dimension.
    - INPUTS: 3 command-line parameters:
        - inputFile - pgm file,
        - intFactor - integer factor n,
        - outputFile - pgm file.
    - OUTPUTS: outputImage file contains a copy of the inputImage pgm file.

**Module pgmTile.c**
- Takes in an input file of type .pgm (either ASCII or binary) and given reduction factor x, splits the image into n * n smaller images, with corresponing positions to the original image.
    - INPUTS: 3 command-line parameters:
        - inputFile - pgm file,
        - intFactor - integer factor n,
        - outputFile - output file template name.
    - OUTPUTS: n * n smaller images, tiled according to rows and columns.

**Module pgmAssemble.c**
- Assembles a large image from smaller ones. 
    - INPUTS: 3+3i command-line parameters:
        - outputFile - pgm file name,
        - width - of outputFile
        - height - of outputFile    
        - Remainder: triplets of:
            - row - start row position
            - column - start column position
            - subimage to insert
    - OUTPUTS: the assembled image from the provided smaller images.
