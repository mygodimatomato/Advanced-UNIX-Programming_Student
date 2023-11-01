CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = q2
TARGET2 = q1
SRCS = q2.c 
OBJS = q2.o 
OBJS2 = q1.o

all: $(TARGET) $(TARGET2)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

$(TARGET2): $(OBJS2)
	$(CC) $(CFLAG) -o $(TARGET2) $(OBJS2)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f $(OBJS2) $(TARGET2)
