#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// ------------------------------------ NEURÔNIO ------------------------------------
typedef struct Neuronio {
    int entradas;
    float* pesos;
    float (*ativacao)(float x);
} Neuronio;


Neuronio neuronio(int entradas, float pesos[entradas], float (*ativacao)(float));

float processa_neuronio(Neuronio n, float entradas[n.entradas]);

void printa_neuronio(Neuronio n);

// ------------------------------------ CAMADA ------------------------------------

typedef struct Camada {
    int entradas;
    int saidas;
    Neuronio *neuronios;
} Camada;

Camada camada(int entradas, int saidas, float pesos[saidas][entradas], float (*ativacao)(float));

float *processa_camada(Camada c, float entradas[c.entradas]);

void printa_camada(Camada c, bool pesos);

// ------------------------------------ REDE ------------------------------------

typedef struct Rede {
    int entradas;
    int saidas;
    int num_camadas;
    int max_camadas;
    Camada *camadas;
} Rede;

Rede rede(int entradas, int saidas, float pesos[saidas][entradas], float (*ativacao)(float));
Rede adiciona_camada(Rede r, int entradas, int saidas, float pesos[saidas][entradas], float (*ativacao)(float));

float *processa_rede(Rede r, float entradas[r.entradas]);

void printa_rede(Rede r, bool camadas);

#endif // STRUCTS_H
