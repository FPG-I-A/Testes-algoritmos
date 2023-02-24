#include "neuronio.h"

Neuronio neuronio(int entradas, float pesos[entradas], float (*ativacao)(float)){
    Neuronio n = {entradas, pesos, ativacao};
    return n;
}

float processa_neuronio(Neuronio n, float entradas[n.entradas]){
    float soma = 0;
    for (int i = 0; i < n.entradas; i++) {
        soma += n.pesos[i] * entradas[i];
    }
    return n.ativacao(soma);
}

void printa_neuronio(Neuronio n){
    printf("Neuronio com %d entradas. Pesos: [", n.entradas);
    for (int i = 0; i < n.entradas; i++) {
        if (i != n.entradas -1){
            printf("%f, ", n.pesos[i]);
        }
        else{
            printf("%f]\n", n.pesos[i]);
        }
    }
}