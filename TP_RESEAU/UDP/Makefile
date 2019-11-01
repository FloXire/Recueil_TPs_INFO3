CC=gcc

all: clientUDP.out serveurUDP.out clean

clientUDP.out: clientUDP.o
	$(CC) -Wall -o $@ $^

serveurUDP.out: serveurUDP.o
	$(CC) -Wall -o $@ $^

clientUDP.o:
	$(CC) -Wall -c clientUDP.c

	$(CC) -Wall -c serveurUDP.c
serveurUDP.o:

clean:
	rm *.o
