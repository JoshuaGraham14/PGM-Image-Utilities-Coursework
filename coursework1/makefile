all: pgmEcho pgmComp

pgmEcho: pgmEcho.c pgmErrors.c pgmImage.c
	gcc -o pgmEcho pgmEcho.c pgmErrors.c pgmImage.c -I.

pgmComp: pgmComp.c pgmErrors.c pgmImage.c
	gcc -o pgmComp pgmComp.c pgmErrors.c pgmImage.c -I.