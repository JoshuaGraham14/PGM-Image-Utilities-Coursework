#!/bin/sh

#----------- Testing valid gtopo files ----------#
echo -n -e "* TESTING VALID gtopo FILES *\n"

echo -n "Test 1 - gtopoEcho: "
EXPECTED="ECHOED"
RESULT=$(./gtopoEcho /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem 20 10 nobackup/temp.dem )
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
RESULT=$(./gtopoComp /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem 20 10 nobackup/temp.dem )
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
RESULT=$(./gtopoComp /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem 20 10 /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_5_5.dem )
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
RESULT=$(./gtopoReduce /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_5_5.dem 20 10 2 nobackup/temp.dem)
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
RESULT=$(./gtopoReduce /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_5_5.dem 20 10 2 nobackup/temp2.dem)
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

echo -n "Test 10 - INVALID gtopoTile: "
EXPECTED="ERROR: Miscellaneous (invalid output template)"
RESULT=$(./gtopoTile /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_5_5.dem 20 10 2 nobackup/temp2)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 11 - VALID gtopoTile: "
EXPECTED="TILED"
RESULT=$(./gtopoTile /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo30full_reduced_216.dem 200 100 10 "nobackup/gtopo_reduced_<row>_<column>")
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 12a - Compare VALID gtopoTile result: "
EXPECTED="IDENTICAL"
RESULT=$(./gtopoComp /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem 20 10 nobackup/gtopo_reduced_4_4 )
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 12b - Compare VALID gtopoTile result: "
EXPECTED="IDENTICAL"
RESULT=$(./gtopoComp /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_0_0.dem 20 10 nobackup/gtopo_reduced_0_0 )
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 12c - Compare VALID gtopoTile result: "
EXPECTED="IDENTICAL"
RESULT=$(./gtopoComp /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_9_9.dem 20 10 nobackup/gtopo_reduced_9_9 )
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 13 - gtopoPrintLand: "
EXPECTED="PRINTED"
RESULT=$(./gtopoPrintLand /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo30full_reduced_216.dem 200 100 nobackup/aa_printedGtopo -9000 100 500)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 14 - gtopoAssemble: "
EXPECTED="PRINTED"
RESULT=$(./gtopoAssemble nobackup/assembleTest.dem 80 10 0 0 nobackup/gtopo_reduced_3_5 20 10 0 20 nobackup/gtopo_reduced_3_6 20 10 0 40 nobackup/gtopo_reduced_3_7 20 10 0 60 nobackup/gtopo_reduced_3_8 20 10)
RESULT=$(./gtopoPrintLand nobackup/assembleTest.dem 80 10 nobackup/aa_printedGtopo -9000 100 500)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 15 - gtopoReduceAssemble view: "
EXPECTED="PRINTED"
bash /vol/scratch/SoC/COMP1921/COMP1921A2_handout/gtopoReduce400.sh
#RESULT=$(./gtopoPrintLand /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo30full_reduced_400.dem 108 54 nobackup/aa_printedGtopo -9999 100 500)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi