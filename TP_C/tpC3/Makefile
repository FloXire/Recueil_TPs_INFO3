main: main.o Liste.o
	gcc -Wall -Wextra -o main main.o Liste.o

main.o: Liste.h main.c
	gcc -Wall -Wextra -o main.o -c main.c

Liste.o: Liste.c
	gcc -Wall -Wextra -o Liste.o -c Liste.c
