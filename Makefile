CC=gcc

all: main.o init.o import.o scope.o timescale.o vars.o vars_first.o
	$(CC) main.o init.o import.o scope.o timescale.o vars.o vars_first.o -o simtovcd
	rm main.o init.o import.o scope.o timescale.o vars.o vars_first.o

main.o: main.c
	$(CC) main.c -c -o main.o

init.o: init.c init.h
	$(CC) init.c -c -o init.o

import.o: import.c import.h
	$(CC) import.c -c -o import.o

scope.o: scope.c scope.h
	$(CC) scope.c -c -o scope.o

timescale.o: timescale.c timescale.h
	$(CC) timescale.c -c -o timescale.o

vars.o: vars.c vars.h
	$(CC) vars.c -c -o vars.o

vars_first.o: vars_first.c vars_first.h
	$(CC) vars_first.c -c -o vars_first.o

clean:	
	rm main.o init.o import.o scope.o timescale.o vars.o vars_first.o
