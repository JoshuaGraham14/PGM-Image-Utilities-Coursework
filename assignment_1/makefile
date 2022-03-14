all: pgmEcho pgmComp

pgmEcho: pgmEcho.c pgmErrors.c pgmImage.c
	gcc -o pgmEcho pgmEcho.c pgmErrors.c pgmImage.c -I.

pgmComp: pgmComp.c pgmErrors.c pgmImage.c
	gcc -o pgmComp pgmComp.c pgmErrors.c pgmImage.c -I.

pgma2b: pgma2b.c pgmErrors.c pgmImage.c
	gcc -o pgma2b pgma2b.c pgmErrors.c pgmImage.c -I.