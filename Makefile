CC = gcc
CFLAGS = -I. -g -Wall
TARGET = scanner
OBJS = main.o scanner.o functions.o fileCheck.o table.o testScanner.o
.SUFFIXES: .c .o

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET) *.txt
