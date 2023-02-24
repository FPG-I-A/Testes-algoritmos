CC=gcc
CFLAGS=-Wall --pedantic -pipe -lm

.PHONY: all knn dataset clean

all: dataset knn

knn:
	$(CC) utils.c tabela.c knn.c -o knn.o $(CFLAGS)

dataset:
	python gera_dataset.py

clean:
	rm *.o *.exe dataset.h