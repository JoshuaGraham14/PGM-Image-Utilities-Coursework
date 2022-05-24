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
RESULT=$(./gtopoComp nobackup/temp.dem 10 5 nobackup/temp2.dem)
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
EXPECTED=""
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
EXPECTED=""
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
EXPECTED=""
bash ./COMP1921A2_handout/gtopoReduce400.sh
RESULT=$(./COMP1921A2_handout/dems/gtopo30full_reduced_400.dem 108 54 nobackup/aa_printedGtopo -9999 0 2000)
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

echo -n "Test 1 - 0 args for gtopoEcho: "
EXPECTED="Usage: ./gtopoEcho inputFile width height outputFile"
RESULT=$(./gtopoEcho)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 2 - 1 args for gtopoEcho: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./gtopoEcho /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem )
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 3 - 0 args for gtopoComp: "
EXPECTED="Usage: ./gtopoComp firstFile width height secondFile"
RESULT=$(./gtopoComp)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 4 - 1 args for gtopoComp: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./gtopoComp /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem )
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 5 - 0 args for gtopoReduce: "
EXPECTED="Usage: ./gtopoReduce input width height reduction_factor output"
RESULT=$(./gtopoReduce)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 6 - 1 args for gtopoReduce: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./gtopoReduce /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 7 - 0 args for gtopoTile: "
EXPECTED="Usage: ./gtopoTile inputFile width height tiling_factor outputFile_<row>_<column>"
RESULT=$(./gtopoTile)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 8 - 1 args for gtopoReduce: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./gtopoTile /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 9 - 0 args for gtopoAssemble: "
EXPECTED="Usage: ./gtopoAssemble outputImage.gtopo width height (row column inputImage.gtopo)+"
RESULT=$(./gtopoAssemble)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 10 - 1 args for gtopoAssemble: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./gtopoAssemble /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 11 - 0 args for gtopoPrintLand: "
EXPECTED="Usage: ./gtopoPrintLand inputFile width height outputFile sea hill mountain"
RESULT=$(./gtopoPrintLand)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 12 - 1 args for gtopoPrintLand: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./gtopoPrintLand /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 13 - 0 args for gtopoAssembleReduce: "
EXPECTED="Usage: ././gtopoAssembleReduce outputArray.gtopo width height (row column inputArray.gtopo width height)+"
RESULT=$(./gtopoAssembleReduce)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi

echo -n "Test 14 - 1 args for gtopoAssembleReduce: "
EXPECTED="ERROR: Bad Argument Count"
RESULT=$(./gtopoAssembleReduce /vol/scratch/SoC/COMP1921/COMP1921A2_handout/dems/gtopo_reduced_4_4.dem)
VALUE=$?
if [ "$EXPECTED" == "$RESULT" ]
then
    echo -e "PASSED, code=${VALUE}"
else
    echo -e "FAILED, code=${VALUE}"
    echo -e "\t~ Expected: '${EXPECTED}'"
    echo -e "\t~ Received: '${RESULT}'"
fi