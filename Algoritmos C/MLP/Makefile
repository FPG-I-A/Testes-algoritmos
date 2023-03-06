CC=gcc
CFLAGS=-Wall --pedantic -pipe -lm -g

.PHONY: all main gera_main mlp clean

all: clean gera_main main

main:
	$(CC) structs.c ativacoes.c main.c -o main.o $(CFLAGS)

gera_main:
	python cria_main.py

clean:
	-rm *.o *.exe main.c entradas-saidas.h