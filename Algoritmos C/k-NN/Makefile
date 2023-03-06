CC=gcc
CFLAGS=-Wall --pedantic -pipe -lm

.PHONY: all knn gera_main clean

all: clean gera_main knn

knn:
	$(CC) structs.c main.c -o main.o $(CFLAGS)

gera_main:
	python cria_main.py

clean:
	-rm *.o *.exe main.c