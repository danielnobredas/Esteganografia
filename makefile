PROG = Cript
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
OBJS = projet.o wrPpm.o ppm.o lerBMP.o bits.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

	projet.o:
		$(CC) $(CFLAGS) -c projet.c
	bits.o:
		$(CC) $(CFLAGS) -c bits.c	
	wrPpm.o:
		$(CC) $(CFLAGS) -c wrPpm.c		
	ppm.o:
		$(CC) $(CFLAGS) -c ppm.c	
	lerBMP.o:
		$(CC) $(CFLAGS) -c lerBMP.c					
	clean:
		rm -f core $(PROG) $(OBJS)