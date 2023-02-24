CC=gcc
CFLAGS=-Wall --pedantic -pipe -lm -g

.PHONY: mlp clean


mlp:
	$(CC) structs.c ativacoes.c mlp.c -o mlp.o $(CFLAGS)


clean:
	rm *.o *.exe