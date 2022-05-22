#!/bin/sh

#----------- Testing valid pgm files ----------#
echo -n -e "* TESTING VALID PGM FILES *\n"

echo -n "Test 1 - pgmEcho: "
EXPECTED="ECHOED"
RESULT=$(./pgmEcho pgmFiles/saturn.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 2 - pgmComp - identical: "
EXPECTED="IDENTICAL"
RESULT=$(./pgmComp pgmFiles/saturn.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 3 - pgmComp - different: "
EXPECTED="DIFFERENT"
RESULT=$(./pgmComp pgmFiles/saturn.pgm pgmFiles/first.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 4 - pgma2b: "
EXPECTED="CONVERTED"
RESULT=$(./pgma2b pgmFiles/saturn.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 5 - pgmb2a: "
EXPECTED="CONVERTED"
RESULT=$(./pgmb2a pgmFiles/temp.pgm pgmFiles/temp2.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 6 - pgmReduce: "
EXPECTED="REDUCED"
RESULT=$(./pgmReduce pgmFiles/saturn.pgm 2 pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 7 - pgmTile: "
EXPECTED="TILED"
RESULT=$(./pgmTile pgmFiles/toTile.pgm 2 "pgmFiles/tileFile_<row>_<column>.pgm")
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 8 - pgmAssemble: "
EXPECTED="ASSEMBLED"
RESULT=$(./pgmAssemble pgmFiles/outputImage.pgm 8 8 0 0 pgmFiles/tileFile_0_0.pgm 0 4 pgmFiles/tileFile_0_1.pgm 4 0 pgmFiles/tileFile_1_0.pgm 4 4 pgmFiles/tileFile_1_1.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

#----------- Testing invalid pgm files ----------#
echo -n -e "* TESTING INVALID PGM FILES *\n"

echo -n "Test 1 - Bad Magic Number: "
EXPECTED="ERROR: Bad Magic Number (pgmFiles/saturn_invalidMagicNumber.pgm)"
RESULT=$(./pgmEcho pgmFiles/saturn_invalidMagicNumber.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 2 - Bad Comment Line: "
EXPECTED="ERROR: Bad Comment Line (pgmFiles/saturn_badCommentLine.pgm)"
RESULT=$(./pgmEcho pgmFiles/saturn_badCommentLine.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 3 - Width Too Small: "
EXPECTED="ERROR: Bad Dimensions (pgmFiles/saturn_widthTooSmall.pgm)"
RESULT=$(./pgmEcho pgmFiles/saturn_widthTooSmall.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 4 - Width Too Large: "
EXPECTED="ERROR: Bad Dimensions (pgmFiles/saturn_widthTooLarge.pgm)"
RESULT=$(./pgmEcho pgmFiles/saturn_widthTooLarge.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 5 - Height Too Small: "
EXPECTED="ERROR: Bad Dimensions (pgmFiles/saturn_heightTooSmall.pgm)"
RESULT=$(./pgmEcho pgmFiles/saturn_heightTooSmall.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 6 - Height Too Large: "
EXPECTED="ERROR: Bad Dimensions (pgmFiles/saturn_heightTooLarge.pgm)"
RESULT=$(./pgmEcho pgmFiles/saturn_heightTooLarge.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 7 - MaxGray Too Small: "
EXPECTED="ERROR: Bad Max Gray Value (pgmFiles/saturn_maxGrayTooLarge.pgm)"
RESULT=$(./pgmEcho pgmFiles/saturn_maxGrayTooLarge.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 8 - MaxGray Too Large: "
EXPECTED="ERROR: Bad Max Gray Value (pgmFiles/saturn_maxGrayTooLarge.pgm)"
RESULT=$(./pgmEcho pgmFiles/saturn_maxGrayTooLarge.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 9 - Invalid Image Data Pixel Value: "
EXPECTED="ERROR: Bad Data (pgmFiles/saturn_invalidImageDataPixel.pgm)"
RESULT=$(./pgmEcho pgmFiles/saturn_invalidImageDataPixel.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 10 - Too Many Image Data Pixels: "
EXPECTED="ERROR: Bad Data (pgmFiles/saturn_tooManyImageDataPixels.pgm)"
RESULT=$(./pgmEcho pgmFiles/saturn_tooManyImageDataPixels.pgm pgmFiles/temp.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

#----------- Testing invalid command line arguments ----------#
echo -n -e "* TESTING INVALID COMMMAND LINE ARGUMENTS *\n"

echo -n "Test 1 - 0 args for pgmEcho: "
EXPECTED="Usage: ./pgmEcho inputImage.pgm outputImage.pgm"
RESULT=$(./pgmEcho)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 2 - 1 args for pgmEcho: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./pgmEcho pgmFiles/saturn.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 3 - 0 args for pgmComp: "
EXPECTED="Usage: ./pgmComp inputImage.pgm inputImage.pgm"
RESULT=$(./pgmComp)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 4 - 1 args for pgmEcho: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./pgmComp pgmFiles/saturn.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 5 - 0 args for pgma2b: "
EXPECTED="Usage: ./pgma2b inputImage.pgm outputImage.pgm"
RESULT=$(./pgma2b)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 6 - 1 args for pgma2b: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./pgma2b pgmFiles/saturn.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 7 - 0 args for pgmb2a: "
EXPECTED="Usage: ./pgma2b inputImage.pgm outputImage.pgm"
RESULT=$(./pgma2b)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 8 - 1 args for pgmb2a: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./pgma2b pgmFiles/saturn.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 9 - 0 args for pgmReduce: "
EXPECTED="Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm"
RESULT=$(./pgmReduce)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 10 - 1 args for pgmReduce: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./pgmReduce pgmFiles/saturn.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 11 - 0 args for pgmTile: "
EXPECTED="Usage: ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm"
RESULT=$(./pgmTile)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 12 - 1 args for pgmTile: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./pgmTile pgmFiles/saturn.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 13 - 0 args for pgmAssemble: "
EXPECTED="Usage: ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+"
RESULT=$(./pgmAssemble)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 14 - 1 args for pgmAssemble: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./pgmAssemble pgmFiles/saturn.pgm)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi