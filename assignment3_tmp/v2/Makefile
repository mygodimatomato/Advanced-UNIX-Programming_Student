CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = assignment3_v2 
SRCS = assignment3_v2.c 
OBJS = assignment3_v2.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
