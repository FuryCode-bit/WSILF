CC = gcc

#Release
CFLAGS = -O2 -Wall -I ..
#Debug
#CFLAGS = -g -Wall -I ..

all: adder

adder: adder.c
	$(CC) $(CFLAGS) -o adder adder.c

clean:
	rm -f adder *~
