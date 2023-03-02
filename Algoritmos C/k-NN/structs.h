#ifndef STRUCTS_H
#define STUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct linha {
    int tamanho;
    int indice;
    float *elementos;
} Linha;

typedef struct tabela {
    int tamanho_linha;
    int num_linhas;
    int max_linhas;
    Linha *linhas;
} Tabela;


Linha linha(int tamanho, int indice, float elementos[tamanho]);
Linha tabela_loc(Tabela t, int indice);

Tabela tabela(int tamanho_linha, int num_linhas, float elementos_linhas[num_linhas][tamanho_linha]);
Tabela tabela_add(Tabela t, float elementos_linha[t.tamanho_linha]);

int *n_menores(Linha l, int n);
int maior_linha(Linha l);

float distancia(Linha l1, Linha l2);
float *distancia_tabela(Tabela t, Linha l);

void print_linha(Linha l);
void print_tabela(Tabela t);
void troca(int* a, int* b);



#endif // STRUCTS_H