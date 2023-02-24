#include "neuronio.h"
#include "ativacoes.h"

int main(){
    // Primeira camada
    float pesos1[][3] = {
        {1, 1, 1},
        {.3, -.7, -2},
        {.5, 1.4, .9},
        {-.2, -.5, -.2}
    };

    Neuronio c1[4];
    for (int i = 0; i < 4; i++){
        c1[i] = neuronio(3, pesos1[i], *relu);
    }
    

    // Segunda camada
    float pesos2[][2] = {
        {-.2, .3},
        {.3, -.2},
        {.5, 1.4}
    };

    Neuronio c2[3];
    for (int i = 0; i < 3; i++){
        c2[i] = neuronio(2, pesos2[i], *relu);
    }
    
    printf("Primeira camada:\n");
    for (int i = 0; i < 4; i++){
        printa_neuronio(c1[i]);
    }
    printf("Segunda camada:\n");
    for (int i = 0; i < 3; i++){
        printa_neuronio(c2[i]);
    }
    
    return 0;
}