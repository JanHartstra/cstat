CC = gcc
CFLAGS = -g -Wall -lm

# Link
dscstat : dscstat.o cdist.o
	$(CC) -o dscstat.o cdist.o

dscstat.o : dscstat.c
	$(CC) -c $(CFLAGS) dscstat.c

cdist.o : cdist.c
	$(CC) -c $(CFLAGS) cdist.c



