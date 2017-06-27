PROG = steg
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
OBJS = main.o ppm.o BMP.o bits.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

	main.o:
		$(CC) $(CFLAGS) -c main.c
	bits.o:
		$(CC) $(CFLAGS) -c bits.c
	ppm.o:
		$(CC) $(CFLAGS) -c ppm.c
	BMP.o:
		$(CC) $(CFLAGS) -c BMP.c
	clean:
		rm -f core $(PROG) $(OBJS)
