#include "structs.h"


// ------------------------------------ NEURÔNIO ------------------------------------

Neuronio neuronio(int entradas, float vies, float pesos[entradas], float (*ativacao)(float)){
    Neuronio n = {entradas, vies, pesos, ativacao};
    return n;
}

float processa_neuronio(Neuronio n, float entradas[n.entradas]){
    float soma = n.vies;
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
            printf("%f] ", n.pesos[i]);
        }
    }
    printf("Viés: %f.\n", n.vies);
}

// ------------------------------------ CAMADA ------------------------------------

Camada camada(int entradas, int saidas, float vieses[saidas], float pesos[saidas][entradas], float (*ativacao)(float)){
    Neuronio *n = malloc(saidas * sizeof(Neuronio));

    // Cria todos os neuronios da camada
    for (int i = 0; i < saidas; i++){
        n[i] = neuronio(entradas, vieses[i], pesos[i], ativacao);
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

// ------------------------------------ REDE ------------------------------------

Rede rede(int entradas, int saidas, float vieses[saidas], float pesos[saidas][entradas], float (*ativacao)(float)){
    Camada *c = malloc(sizeof(Camada));
    c[0] = camada(entradas, saidas, vieses, pesos, ativacao);
    Rede r = {entradas, saidas, 1, 1, c};
    return r;
}

Rede adiciona_camada(Rede r, int entradas, int saidas, float vieses[saidas], float pesos[saidas][entradas], float (*ativacao)(float)) {
    if (entradas != r.camadas[r.num_camadas-1].saidas) {
        fprintf(stderr,
                "ERRO: A camada adicionada deve ter o mesmo numero de entradas"
                "que a ultima camada tem de saidas, porem ela possui %d entradas"
                " e a camada anterior possui %d saidas.\n\n\n", entradas, r.camadas[r.num_camadas-1].entradas);
        exit(1);
    }
    Camada c = camada(entradas, saidas, vieses, pesos, ativacao);
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
    float *tmp1 = malloc(r.camadas[0].entradas * sizeof(float));  // tmp1: guarda as entradas da camada atual
    float *tmp2 = malloc(r.camadas[0].saidas * sizeof(float));    // tmp2: guarda as saidas da camada atual

    // Popula primeiro vetor de entradas (entradas da segunda camada)
    tmp1 = processa_camada(r.camadas[0], entradas);
    // Percorre rede camada a camada
    for (int i = 0; i < r.num_camadas - 1; i++){
        Camada c = r.camadas[i+1];
        tmp2 = processa_camada(c, tmp1);
        free(tmp1);
        tmp1 = tmp2;                                          // tmp1 = saida da camada atual = entrada da próxima camada
        tmp2 = malloc(r.camadas[i+1].saidas * sizeof(float)); // tmp2 = saida da próxima camada
    }
    free(tmp2);
    return tmp1;

}
float **processa_lote(Rede r, int quantidade, float entradas[quantidade][r.entradas]) {
    float **resultado = malloc(quantidade * r.saidas * sizeof(float));
    for (int i = 0; i < quantidade; i++) {
        resultado[i] = processa_rede(r, entradas[i]);
    }
    return resultado;
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
 