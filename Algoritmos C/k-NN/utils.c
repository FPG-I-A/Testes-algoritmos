#include "utils.h"

float distancia_v_v(V4f u, V4f v) {
    float soma = pow(u.x1 - v.x1, 2) + pow(u.x2 - v.x2, 2) +
                 pow(u.x3 - v.x3, 2) + pow(u.x4 - v.x4, 2);
    return sqrt(soma);
}

Tabela_v_1_f distancia_v_t(V4f vetor, Tabela_v_4_f t) {
    Tabela_v_1_f resultado = tabela_v_1_f(t.tamanho);
    for (int i = 0; i < t.tamanho; i++) {
        float d = distancia_v_v(vetor, t.linhas[i].v);
        Linha_v_1_f l = linha_v_1_f(d, i);
        resultado = tabela_v_1_f_ad(resultado, l);
    }
    return resultado;
}
