PROG = Cript
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
OBJS = projet.o wrPpm.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

	projet.o:
		$(CC) $(CFLAGS) -c projet.c
	wrPpm.o:
		$(CC) $(CFLAGS) -c wrPpm.c		
	clean:
		rm -f core $(PROG) $(OBJS)