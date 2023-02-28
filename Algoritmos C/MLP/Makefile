CC=gcc
CFLAGS=-Wall --pedantic -pipe -lm -g

.PHONY: all main gera_main mlp clean

all: gera_main main

gera_main:
    python cria_main.py

main:
	$(CC) structs.c ativacoes.c main.c -o main.o $(CFLAGS)

mlp:
	$(CC) structs.c ativacoes.c mlp.c -o mlp.o $(CFLAGS)

clean:
	rm *.o *.exe