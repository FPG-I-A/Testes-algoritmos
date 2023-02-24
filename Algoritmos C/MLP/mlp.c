#include "structs.h"
#include "ativacoes.h"

int main(){
    // Primeira camada
    float pesos1[][3] = {
        {1, 1, 1},
        {.3, -.7, -2},
        {.5, 1.4, .9},
        {-.2, -.5, -.2}
    };

    Camada c1 = camada(3, 4, pesos1, relu);
    

    // Segunda camada
    float pesos2[][4] = {
        {-.2, .3, -.2, .3},
        {.3, -.2, .3, -.2},
        {.5, 1.4, .5, 1.4}
    };

    Camada c2 = camada(4, 3, pesos2, relu);

    
    printf("Primeira camada:\n");
    printa_camada(c1, true);
    printf("\nSegunda camada:\n");
    printa_camada(c2, true);

    float entradas[] = {1, 1, 1};
    printf("Entradas: {%f, %f, %f}\n", entradas[0], entradas[1], entradas[2]);

    float *saida_c1 = processa_camada(c1, entradas);
    printf("Saídas c1: {%f, %f, %f, %f}\n", saida_c1[0], saida_c1[1], saida_c1[2], saida_c1[3]);

    float *saida_c2 = processa_camada(c2, saida_c1);
    printf("Saídas c1: {%f, %f, %f}\n", saida_c2[0], saida_c2[1], saida_c2[2]);
    
    return 0;
}