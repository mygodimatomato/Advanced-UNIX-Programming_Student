CC=gcc
CFLAGS=-Wall
PTHREAD=-lpthread

all: q1 q2 q3

q1: q1.c
	$(CC) $(CFLAGS) -o q1 q1.c $(PTHREAD)

q2: q2.c
	$(CC) $(CFLAGS) -o q2 q2.c

q3: q3.c
	$(CC) $(CFLAGS) -o q3 q3.c

clean:
	rm -f q1 q2 q3
