#!/bin/sh

#----------- Testing valid gtopo files ----------#
echo -n -e "* TESTING VALID gtopo FILES *\n"

echo -n "Test 1 - gtopoEcho: "
EXPECTED="ECHOED"
RESULT=$(./gtopoEcho /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem 10 20 nobackup/temp.dem )
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 2 - gtopoComp - identical: "
EXPECTED="IDENTICAL"
RESULT=$(./gtopoComp /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem 10 20 nobackup/temp.dem )
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 3 - gtopoComp - different: "
EXPECTED="DIFFERENT"
RESULT=$(./gtopoComp /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem 10 20 /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_5_5.dem )
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 6 - gtopoReduce: "
EXPECTED="REDUCED"
RESULT=$(./gtopoReduce /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_5_5.dem 10 20 2 nobackup/temp.dem)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 7 - gtopoReduce: "
EXPECTED="REDUCED"
RESULT=$(./gtopoReduce /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_5_5.dem 10 20 2 nobackup/temp2.dem)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 8 - gtopoReduce and gtopoComp: "
EXPECTED="IDENTICAL"
RESULT=$(./gtopoComp nobackup/temp.dem 10 20 nobackup/temp2.dem)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi