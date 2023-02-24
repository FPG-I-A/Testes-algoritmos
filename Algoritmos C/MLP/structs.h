#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// ------------------ NEURÔNIO ------------------
typedef struct Neuronio {
    int entradas;
    float* pesos;
    float (*ativacao)(float x);
} Neuronio;


Neuronio neuronio(int entradas, float pesos[entradas], float (*ativacao)(float));

float processa_neuronio(Neuronio n, float entradas[n.entradas]);

void printa_neuronio(Neuronio n);

// ------------------ CAMADA ------------------

typedef struct Camada {
    const int entradas;
    const int saidas;
    Neuronio *neuronios;
} Camada;

Camada camada(int entradas, int saidas, float pesos[saidas][entradas], float (*ativacao)(float));

float *processa_camada(Camada c, float entradas[c.entradas]);
void printa_camada(Camada c, bool pesos);

#endif // STRUCTS_H