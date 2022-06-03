CC = gcc

#Release Flags
CFLAGS = -O2 -Wall -I .

#DebugFlags
#CFLAGS = -g -Wall -I .

# This flag includes the Pthreads library on a Linux box.
# Others systems will probably require something different.
LIB = -lpthread

all: tiny adder client hashexample

tiny: tiny.c csapp.o
	$(CC) $(CFLAGS) -o tiny tiny.c csapp.o $(LIB)

csapp.o:
	$(CC) $(CFLAGS) -c csapp.c

adder:
	(cd cgi-bin; make)

hashexample: 
	(cd libtomcrypt ; make)

client: client.c
	$(CC) $(CFLAGS) -o client client.c csapp.o $(LIB)
	

clean:
	rm -f *.o tiny *~
	(cd cgi-bin; make clean)
	(cd libtomcrypt ; make clean)

