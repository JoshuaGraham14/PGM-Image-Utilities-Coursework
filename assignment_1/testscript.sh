#!/bin/sh

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
EXPECTED="ERROR: Miscellaneous (too many pixels for specified dimensions)"
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
EXPECTED="Usage: ./pgmComp inputImage.pgm outputImage.pgm"
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