CC=gcc

CFLAGS=-Wall -Wextra -Werror -fopenmp -pthread

all: teste

test: bucketsort.c tests.c
	$(CC) -o test bucketsort.c tests.c $(CFLAGS)

teste: test
	./test

clean:
	rm -rf *.o test
