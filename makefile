PROG = Cript
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
OBJS = teste.o wrPpm.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

	teste.o:
		$(CC) $(CFLAGS) -c teste.c
	wrPpm.o:
		$(CC) $(CFLAGS) -c wrPpm.c		
	clean:
		rm -f core $(PROG) $(OBJS)