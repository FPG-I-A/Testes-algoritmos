#include "structs.h"


// ------------------ NEURÔNIO ------------------

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

// ------------------ CAMADA ------------------

Camada camada(int entradas, int saidas, float pesos[saidas][entradas], float (*ativacao)(float)){
    Neuronio *n = malloc(saidas * sizeof(Neuronio));

    // Cria todos os neuronios da camada
    for (int i = 0; i < saidas; i++){
        n[i] = neuronio(entradas, pesos[i], ativacao);
    }
    Camada c = {entradas, saidas, n};
    return c;
}

float *processa_camada(Camada c, float entradas[c.entradas]){
    float *resultado = malloc(c.saidas * sizeof(float));

    // Coloca no vetor de saída a saída de cada neurônio
    for (int i = 0; i < c.saidas; i++){
        resultado[i] = processa_neuronio(c.neuronios[i], entradas);
    }

    return resultado;
}
void printa_camada(Camada c, bool pesos){
    printf("Camada com %d neurônios de %d entradas.", c.saidas, c.entradas);
    if (pesos){
        printf(" Neurônios:\n");
        for (int i = 0; i < c.saidas; i++){
            printf("\t");
            printa_neuronio(c.neuronios[i]);
        }
    }
    else{
        printf("\n");
    }
}
