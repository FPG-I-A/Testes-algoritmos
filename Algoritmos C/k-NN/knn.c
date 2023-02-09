#include "tabela.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>

int main(void) {
    Tabela_v_4_f t = tabela_v_4_f(1);
    V4f vetor = v4f(0, 0, 0, 0);
    for (int i = 1; i <= 10; i++) {
        t = tabela_v_4_f_ad(t, linha_v_4_f(i * 1, i * 2, i * 3, i * 4, i));
    }
    t = tabela_v_4_f_ad(t, linha_v_4_f(1, 1, 0, 0, 11));
    Tabela_v_1_f resultado = distancia_v_t(vetor, t);

    printf("Tabela montada:\n");
    print_tabela_v_4_f(t);
    printf("\nDistancias calculadas:\n");
    print_tabela_v_1_f(resultado);

    int indices[3];
    n_menores(3, indices, resultado);
    for (int n = 0; n < 3; n++) {
        printf("%d\n", indices[n]);
    }
    return 0;
}
