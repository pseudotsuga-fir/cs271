CC = gcc
CFLAGS = -std=c11 -Wall -ggdb3 -I.
LDFLAGS = 
OBJFILES = main.o parser.o symtable.o error.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
