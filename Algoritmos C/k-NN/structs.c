#include "structs.h"

Linha linha(int tamanho, int indice, float elementos[tamanho]) {
    // Construtor do struct de linha
    Linha l = {tamanho, indice, elementos};
    return l;
}
Linha tabela_loc(Tabela t, int indice) {
    // Encontra uma linha na tabela baseado no índice
    for (int i = 0; i < t.num_linhas; i++) {
        if (t.linhas[i].indice == indice) {
            return t.linhas[i];
        }
    }
    fprintf(stderr, "Não foi possível encontrar uma linha com índice %d na tabela.", indice);
    exit(1);

}

Tabela tabela(int tamanho_linha, int num_linhas, float elementos_linhas[num_linhas][tamanho_linha]) {
    // Construtor do struct de tabela
    Linha *l = malloc(num_linhas * sizeof(Linha));
    for (int i = 0; i < num_linhas; i++) {
        l[i] = linha(tamanho_linha, i, elementos_linhas[i]);
    }

    Tabela t = {tamanho_linha, num_linhas, num_linhas, l};
    return t;
}
Tabela tabela_add(Tabela t, float elementos_linha[t.tamanho_linha]) {
    Linha l =  linha(t.tamanho_linha, t.num_linhas, elementos_linha);

    if (t.num_linhas == t.max_linhas) {
        t.max_linhas *= 2;
        Linha *tmp = t.linhas;
        t.linhas = malloc(t.max_linhas * sizeof(Linha));
        for (int i = 0; i < t.num_linhas; i++) {
            t.linhas[i] = tmp[i];
        }
    }
    
    t.linhas[t.num_linhas] = l;
    t.num_linhas++;
    return t;
 
}

int *n_menores(Linha l, int n) {
    // Encontra os índices dos n menores valores de uma linha
    int *resultado = malloc(n * sizeof(int));

    // Popula o resulatdo com o indíce do maior elemento
    int ind_maior = maior_linha(l);
    for (int i = 0; i < n ; i++) {
        resultado[i] = ind_maior;
    }

    // Insertion sort
    for (int i = 0; i < l.tamanho; i++) {
        if (l.elementos[i] < l.elementos[resultado[0]]) {
            int j = 0;
            for (j = 0; j < n; j++) {
                if (l.elementos[i] > l.elementos[resultado[j]]) {
                    break;
                }
            }
            // Aqui j é o indíce, no buffer, em que i deve estar
            resultado[0] = i;
            for (int k = 0; k < j - 1; k++) {
                troca(&resultado[k], &resultado[k + 1]);
            }
        }
    }

    return resultado;
}
int maior_linha(Linha l) {
    // Encontra o índice do maior elemento de uma linha
    int ind_maior = 0;
    for (int i = 0; i < l.tamanho; i++) {
        if (l.elementos[i] > l.elementos[ind_maior]) {
            ind_maior = i;
        }
    }
    return ind_maior;
}

float distancia(Linha l1, Linha l2) {
    if (l1.tamanho != l2.tamanho) {
        fprintf(stderr, "As duas linhas devem ter o mesmo tamanho, mas tem %d e %d elementos respectivamente", l1.tamanho, l2.tamanho);
        exit(1);
    }
    
    float soma = 0;
    for (int i = 0; i < l1.tamanho; i++){
        soma += pow(l1.elementos[i] - l2.elementos[i], 2);
    }
    return sqrt(soma);
}
float *distancia_tabela(Tabela t, Linha l) {
    if (t.tamanho_linha != l.tamanho) {
        fprintf(stderr, "A tabela deve ter linhas com o mesmo número de elementos que a linha passada, mas tem %d e %d elementos respectivamente", t.tamanho_linha, l.tamanho);
        exit(1);
    }

    float *resultado = malloc(t.num_linhas * sizeof(float));
    for (int i = 0; i < t.num_linhas; i++) {
        resultado[i] = distancia(t.linhas[i], l);
    }

    return resultado;
}

void print_linha(Linha l) {
    printf("%.3d: ", l.indice);
    for (int i = 0; i < l.tamanho - 1; i++) {
        printf("%.3f, ", l.elementos[i]);
    }
    printf("%.3f\n", l.elementos[l.tamanho-1]);
}
void print_tabela(Tabela t) {
    printf("\nTabela com %d linhas de %d elementos:\n", t.num_linhas, t.tamanho_linha);
    // Printa a tabela no stdout
    if (t.num_linhas > 20) {
        for (int i = 0; i < 5; i++) {
            print_linha(t.linhas[i]);
        }
        for (int i = 0; i < 3; i++) {
            printf(" .  ");
            for (int j = 0; j < t.tamanho_linha - 1; j++) {
                printf("   .   ");
            }
            printf("   .\n");
        }
        for (int i = t.num_linhas - 6; i < t.num_linhas; i++) {
            print_linha(t.linhas[i]);
        }
    }

    else {
        for (int i = 0; i < t.num_linhas; i++) {
            print_linha(t.linhas[i]);
        }
    }
}
void troca(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
