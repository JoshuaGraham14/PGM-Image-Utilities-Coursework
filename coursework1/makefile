all: echo comp

echo: pgmEcho.c pgmErrors.c pgmImage.c
	gcc -o echo pgmEcho.c pgmErrors.c pgmImage.c -I.

comp: pgmComp.c pgmErrors.c pgmImage.c
	gcc -o comp pgmComp.c pgmErrors.c pgmImage.c -I.