CC=gcc
CCFLAGS=-g -std=c99 -Wall -Werror
CFLAGS=-std=c99
MODULES=gtopoErrors.o gtopoImage.o 
MAINS=gtopoEcho.o gtopoComp.o gtopoReduce.o
TARGETS=gtopoEcho gtopoComp gtopoReduce

all:	${TARGETS}

clean:
	rm 	${TARGETS} ${MAINS} ${MODULES}

gtopoEcho:	gtopoEcho.o 	${MODULES}
	${CC} 	${CCFLAGS} 	-o gtopoEcho	 gtopoEcho.o	 ${MODULES}

gtopoComp:	gtopoComp.o 	${MODULES}
	${CC} 	${CCFLAGS} 	-o gtopoComp	 gtopoComp.o	 ${MODULES}

gtopoReduce:	gtopoReduce.o 	${MODULES}
	${CC} 	${CCFLAGS} 	-o gtopoReduce	 gtopoReduce.o	 ${MODULES}