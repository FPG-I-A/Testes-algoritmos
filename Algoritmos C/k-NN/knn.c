#include "dataset.h"
#include "tabela.h"
#include "utils.h"

int main(int argc, char* argv[]) {
    int k;
    switch (argc) {
    case 1:
        k = 5;
        break;
    case 2:
        k = atoi(argv[1]);
        break;
    default:
        printf("Você deve fornecer 1 argumento mas forneceu %d\n", argc - 1);
        exit(1);
        break;
    }
    if (k == 0) {
        printf("Você deve fornecer como argumento um número inteiro entre 1 e "
               "100\n");
        exit(1);
    }

    Tabela_v_4_f X_treino = tabela_v_4_f(100);
    for (int i = 0; i < 100; i++) {

        X_treino = tabela_v_4_f_ad(
            X_treino, linha_v_4_f(x_treino[i][0], x_treino[i][1],
                                  x_treino[i][2], x_treino[i][3], i));
    }

    Tabela_v_3_f Y_treino = tabela_v_3_f(100);
    for (int i = 0; i < 100; i++) {
        Y_treino = tabela_v_3_f_ad(
            Y_treino,
            linha_v_3_f(y_treino[i][0], y_treino[i][1], y_treino[i][2], i));
    }

    Tabela_v_4_f X_teste = tabela_v_4_f(50);
    for (int i = 0; i < 50; i++) {
        X_teste = tabela_v_4_f_ad(X_teste,
                                  linha_v_4_f(x_teste[i][0], x_teste[i][1],
                                              x_teste[i][2], x_teste[i][3], i));
    }

    Tabela_v_3_f Y_teste = tabela_v_3_f(50);
    for (int i = 0; i < 50; i++) {
        Y_teste =
            tabela_v_3_f_ad(Y_teste, linha_v_3_f(y_teste[i][0], y_teste[i][1],
                                                 y_teste[i][2], i));
    }

    printf("X_treino:\n");
    print_tabela_v_4_f(X_treino);
    printf("\nX_teste:\n");
    print_tabela_v_4_f(X_teste);
    printf("\nY_treino:\n");
    print_tabela_v_3_f(Y_treino);
    printf("\nY_teste:\n");
    print_tabela_v_3_f(Y_teste);
    float acertos = 0;

    for (int i = 0; i < 50; i++) {
        V4f analisando = X_teste.linhas[i].v;
        Tabela_v_1_f distancias = distancia_v_t(analisando, X_treino);
        int* indices = malloc(k * sizeof(int));
        n_menores(k, indices, distancias);
        V3f escolhas = v3f(0, 0, 0);

        // Adicionar 1 no indice em cada manor distância
        for (int j = 0; j < k; j++) {
            escolhas = v_3_f_ad(escolhas, Y_treino.linhas[indices[j]].v);
        }
        printf("Saída real: (%d, %d, %d). Saidas mais proximas: (%.0f, %.0f, "
               "%.0f)\n",
               y_teste[i][0], y_teste[i][1], y_teste[i][2], escolhas.x1,
               escolhas.x2, escolhas.x3);

        // Ver se as acertou
        int escolha = v_3_f_maior(escolhas);
        if (y_teste[i][escolha] == 1) {
            acertos++;
        }
    }

    printf("\nAcertos: %.0f/50 = %.2f%%\n", acertos, 100 * acertos / 50);

    return 0;
}
