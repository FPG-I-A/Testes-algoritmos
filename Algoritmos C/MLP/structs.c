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
    printf("Camada com %d neurônios de %d entradas.\n", c.saidas, c.entradas);
    if (pesos){
        printf("Neurônios:\n");
        for (int i = 0; i < c.saidas; i++){
            printf("\t");
            printa_neuronio(c.neuronios[i]);
        }
    }
}

// ------------------ CAMADA ------------------

Rede rede(int entradas, int saidas, float pesos[saidas][entradas], float (*ativacao)(float)){
    Camada *c = malloc(sizeof(Camada));
    c[0] = camada(entradas, saidas, pesos, ativacao);
    Rede r = {entradas, saidas, 1, 1, c};
    return r;
}

Rede adiciona_camada(Rede r, int entradas, int saidas, float pesos[saidas][entradas], float (*ativacao)(float)) {
    if (entradas != r.camadas[r.num_camadas-1].saidas) {
        fprintf(stderr,
                "ERRO: A camada adicionada deve ter o mesmo numero de entradas"
                "que a ultima camada tem de saidas, porem ela possui %d entradas"
                " e a camada anterior possui %d saidas.\n\n\n", entradas, r.camadas[r.num_camadas-1].entradas);
        exit(1);
    }
    Camada c = camada(entradas, saidas, pesos, ativacao);
    if (r.max_camadas > r.num_camadas) {
        r.camadas[r.num_camadas] = c;
        r.num_camadas++;
        return r;
    }

    Camada *tmp = r.camadas;
    r.camadas = malloc(r.max_camadas * sizeof(Camada));
    for (int i = 0; i < r.num_camadas; i++) {
        r.camadas[i] = tmp[i];
    }
    free(tmp);
    r.camadas[r.num_camadas] = c;
    r.num_camadas++;
    return r;
}

float *processa_rede(Rede r, float entradas[r.entradas]) {
    // TO-DO: algoritmo de feedforward
    // Dificuldade: tamanho do vetor deve mudar a cada camada
}

void printa_rede(Rede r, bool camadas) {
    printf("Rede neural com %d camadas, %d entradas e %d saidas.\n", r.num_camadas, r.camadas[0].entradas, r.camadas[r.num_camadas-1].saidas);
    if (camadas) {
        printf("Camadas:\n");
        for (int i = 0; i < r.num_camadas; i++) {
            printf("\t");
            printa_camada(r.camadas[i], false);
        }
    }

}
