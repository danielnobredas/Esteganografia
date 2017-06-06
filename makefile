PROG = Cript
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
OBJS = mod.o ppm.o main.o bpm.o png.o jpg.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

	mod.o:
		$(CC) $(CFLAGS) -c mod.h
	ppm.o:
		$(CC) $(CFLAGS) -c ppm.c
	main.o:
		$(CC) $(CFLAGS) -c projet.c
	bpm.o:
		$(CC) $(CFLAGS) -c bpm.c
	png.o:
		$(CC) $(CFLAGS) -c png.c
	jpg.o:
		$(CC) $(CFLAGS) -c jpg.c
	clean:
		rm -f core $(PROG) $(OBJS)