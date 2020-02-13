#/*!
#* @programm binary-digits
#* @author Leonhard Alton 1624280
#*/

CC = gcc -lrt -pthread
DEFS = -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200809L
CFLAGS = -Wall -g -std=c99 -pedantic $(DEFS)

.PHONY: all clean
all: nanosleep_example

binary-digits: nanosleep_example.o
	$(CC) -o $@ $^

auth-server.o: nanosleep_example.c common.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o nanosleep_example
