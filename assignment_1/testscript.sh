#!/bin/sh

./pgmEcho pgmFiles/first.pgm pgmFiles/temp.pgm; echo $?
./pgma2b pgmFiles/first.pgm pgmFiles/temp.pgm; echo $?
./pgmb2a pgmFiles/first.pgm pgmFiles/temp.pgm; echo $?