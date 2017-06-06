PROG = Cript
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
OBJS = mod.o ppm.o main.o bpm.o png.o jpg.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

	mod.o:
		$(CC) $(CFLAGS) -c mod.h
	fatorial.o:
		$(CC) $(CFLAGS) -c ppm.c
	main.o:
		$(CC) $(CFLAGS) -c main.c
	maiorprimoanterior.o:
		$(CC) $(CFLAGS) -c bpm.c
	primalidade.o:
		$(CC) $(CFLAGS) -c png.c
	primo.o:
		$(CC) $(CFLAGS) -c jpg.c
	clean:
		rm -f core $(PROG) $(OBJS)