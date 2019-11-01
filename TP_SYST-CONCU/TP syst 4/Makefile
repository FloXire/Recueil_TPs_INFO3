CFLAGS=-Wall -Wextra

all: main clean

main: main.o daemon.o
	gcc -o main main.o daemon.o

main.o: main.c
	gcc -o main.o -c main.c $(CFLAGS)

deamon.o: daemon.c daemon.h
	gcc -o daemon.o -c daemon.c $(CFLAGS)

clean:
	@rm *.o
