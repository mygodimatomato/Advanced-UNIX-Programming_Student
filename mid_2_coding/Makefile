CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = q1 q2 q3 q4
SRCS = q1.c q2.c q3.c q4.c
OBJS = q1.o q2.o q3.o q4.o

all: q1 q2 q3 q4

q1: q1.o
	$(CC) $(CFLAG) -o q1 q1.o
q2: q2.o
	$(CC) $(CFLAG) -o q2 q2.o
q3: q3.o
	$(CC) $(CFLAG) -o q3 q3.o
q4: q4.o
	$(CC) $(CFLAG) -o q4 q4.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
