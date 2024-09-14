CC = gcc
CFLAGS = -g -Wall -Wextra

SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

LDFLAGS = -L.
LDLIBS = -lm
INC = -I.

EXECUTABLE = main

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(EXECUTABLE) $(OBJECTS)

$(OBJECTS) : %.o : %.c
	$(CC) $(INC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *o $(EXECUTABLE)
