CC=gcc
CFLAGS=-c -Wall -std=gnu99
LDFLAGS=
SOURCES=delvs.h
OBJECTS=$(SOURCES:.c=.o)

all:
	$(CC) $(CFLAGS) $(SOURCES)

clean:
	rm *.o
