CCOPTIONS=-g
CC=gcc $(CCOPTIONS)


all : lecteurs-redacteurs-mutex lecteurs-redacteurs-moniteur

clean : 
	rm "lecteurs-redacteurs-mutex" "lecteurs-redacteurs-moniteur" semaphore-moniteur.o tprintf.o



lecteurs-redacteurs-mutex : lecteurs-redacteurs-mutex.c tprintf.o
	$(CC) -o "lecteurs-redacteurs-mutex"  "lecteurs-redacteurs-mutex.c" tprintf.o -lpthread


lecteurs-redacteurs-moniteur : lecteurs-redacteurs-moniteur.c tprintf.o
	$(CC) -o "lecteurs-redacteurs-moniteur"  "lecteurs-redacteurs-moniteur.c" tprintf.o -lpthread





semaphore-moniteur.o : semaphore-moniteur.c semaphore-moniteur.h
	$(CC)  -c "semaphore-moniteur.c"

tprintf.o : tprintf.c tprintf.h
	$(CC)  -c tprintf.c

