CC=gcc
CCFLAGS=-ggdb -lm -std=c99 -Wall -Werror
CFLAGS=-std=c99
MODULES=gtopoErrors.o gtopoImage.o
MAINS=gtopoEcho.o gtopoComp.o
TARGETS=gtopoEcho gtopoComp

all:	${TARGETS}

clean:
	rm 	${TARGETS} ${MAINS} ${MODULES}

gtopoEcho:	gtopoEcho.o 	${MODULES}
	${CC} 	${CCFLAGS} 	-o gtopoEcho	 gtopoEcho.o	 ${MODULES}

gtopoComp:	gtopoComp.o 	${MODULES}
	${CC} 	${CCFLAGS} 	-o gtopoComp	 gtopoComp.o	 ${MODULES}