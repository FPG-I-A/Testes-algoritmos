#include "dataset.h"
#include "structs.h"

int main(int argc, char** argv) {
    int k;
    switch (argc) {
    case 1:
        k = 5;
        break;
    case 2:
        k = atoi(argv[1]);
        if (k == 0) {
            fprintf(stderr,
                    "Você deve inserir um número inteiro como argumento.\n");
            exit(1);
        }
        break;
    default:
        fprintf(stderr, "Uso: ./%s k\n", argv[0]);
        fprintf(stderr, "\tk: número de vizinhos mais próximos. (opcional)\n");
        exit(1);
    }

    Tabela X_treino = tabela(4, 100, x_treino);
    Tabela X_teste = tabela(4, 50, x_teste);
    Tabela Y_treino = tabela(3, 100, y_treino);
    Tabela Y_teste = tabela(3, 50, y_teste);

    print_tabela(X_treino);
    print_tabela(X_teste);
    print_tabela(Y_treino);
    print_tabela(Y_teste);

    float acertos = 0;

    for (int i = 0; i < X_teste.num_linhas; i++) {
        float* distancias = distancia_tabela(X_treino, X_teste.linhas[i]);
        Linha candidatos = linha(X_treino.num_linhas, 0, distancias);

        int* indices = n_menores(candidatos, k);

        // Cria array de palpites
        float* init = malloc(Y_treino.tamanho_linha * sizeof(float));
        for (int j = 0; j < Y_treino.tamanho_linha; j++) {
            init[j] = 0.;
        }
        Linha palpites = linha(Y_treino.tamanho_linha, 0, init);

        // Calcula os palpites
        for (int j = 0; j < k; j++) {
            int argmax = maior_linha(Y_treino.linhas[indices[j]]);

            palpites.elementos[argmax]++;
        }

        // Checa se acertou ou não
        if (Y_teste.linhas[i].elementos[maior_linha(palpites)] == 1) {
            acertos++;
        }
    }

    printf("\nAcurácia: %d/%.2d = %.2f%%\n", (int)acertos, Y_teste.num_linhas,
           100 * (acertos / Y_teste.num_linhas));
    return 0;
}