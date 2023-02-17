#ifndef TABELA_H
#define TABELA_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// ------------------------ Tabelas de 1 elemento ------------------------
typedef struct V1f {
    float x;
} V1f;
typedef struct Linha_v_1_f {
    V1f v;
    int indice;
} Linha_v_1_f;
typedef struct Tabela_v_1_f {
    Linha_v_1_f* linhas;
    int tamanho;
    int tamanho_maximo;
} Tabela_v_1_f;

V1f v1f(float x);

Linha_v_1_f linha_v_1_f(float x, int indice);

Tabela_v_1_f tabela_v_1_f(int tamanho_maximo);
Tabela_v_1_f tabela_v_1_f_ad(Tabela_v_1_f tabela, Linha_v_1_f linha);

void procura_v_1_f(Tabela_v_1_f tabela, int quantidade, int indices[quantidade],
                   float resultado[quantidade]);
void print_tabela_v_1_f(Tabela_v_1_f tabela);
void n_menores(int n, int buff[n], Tabela_v_1_f tabela);

// ------------------------ Tabelas de 3 elementos ------------------------
typedef struct V3f {
    float x1;
    float x2;
    float x3;
} V3f;
typedef struct Linha_v_3_f {
    V3f v;
    int indice;
} Linha_v_3_f;
typedef struct Tabela_v_3_f {
    Linha_v_3_f* linhas;
    int tamanho;
    int tamanho_maximo;
} Tabela_v_3_f;

V3f v3f(float x1, float x2, float x3);
V3f v_3_f_ad(V3f x, V3f y);

Linha_v_3_f linha_v_3_f(float x1, float x2, float x3, int indice);

Tabela_v_3_f tabela_v_3_f(int tamanho_maximo);
Tabela_v_3_f tabela_v_3_f_ad(Tabela_v_3_f tabela, Linha_v_3_f linha);

int v_3_f_maior(V3f v);

void print_tabela_v_3_f(Tabela_v_3_f tabela);

// ------------------------ Tabelas de 4 elementos ------------------------
typedef struct V4f {
    float x1;
    float x2;
    float x3;
    float x4;
} V4f;
typedef struct Linha_v_4_f {
    V4f v;
    int indice;
} Linha_v_4_f;
typedef struct Tabela_v_4_f {
    Linha_v_4_f* linhas;
    int tamanho;
    int tamanho_maximo;
} Tabela_v_4_f;

V4f v4f(float x1, float x2, float x3, float x4);

Linha_v_4_f linha_v_4_f(float x1, float x2, float x3, float x4, int indice);

Tabela_v_4_f tabela_v_4_f(int tamanho_maximo);
Tabela_v_4_f tabela_v_4_f_ad(Tabela_v_4_f tabela, Linha_v_4_f linha);

void print_tabela_v_4_f(Tabela_v_4_f tabela);

#endif // TABELA_H