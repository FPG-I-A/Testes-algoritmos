CC=gcc
CFLAGS=-Wall --pedantic -pipe -lm

.PHONY: all knn dataset clean

all: clean dataset knn

knn:
	$(CC) structs.c main.c -o main.o $(CFLAGS)

dataset:
	python gera_dataset.py

clean:
	-rm *.o *.exe dataset.h