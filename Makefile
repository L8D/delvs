CC=gcc
CFLAGS=-Wall -std=gnu99
LDFLAGS=
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(OBJECTS)

clean:
	rm *.o
