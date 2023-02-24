#ifndef NEURONIO_H
#define NEURONIO_H

#include <stdio.h>

typedef struct Neuronio {
    int entradas;
    float* pesos;
    float (*ativacao)(float x);
} Neuronio;


Neuronio neuronio(int entradas, float pesos[entradas], float (*ativacao)(float));

float processa_neuronio(Neuronio n, float entradas[n.entradas]);

void printa_neuronio(Neuronio n);


#endif // NEURONIO_H