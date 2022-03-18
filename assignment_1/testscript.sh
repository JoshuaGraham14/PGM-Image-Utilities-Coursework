#!/bin/sh

#----------- Testing invalid pgm files ----------#

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