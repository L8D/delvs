CC=gcc
CFLAGS=-Wall -std=gnu99 -Werror
LDFLAGS=
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)

all: objects
	mv main.o delvs

objects:
	$(CC) $(CFLAGS) $(SOURCES) -o $(OBJECTS)

clean:
	rm delvs
