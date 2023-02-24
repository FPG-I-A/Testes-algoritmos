#include "tabela.h"

// ------------------------ Tabelas de 1 elemento ------------------------
V1f v1f(float x) {
    V1f v = {x};
    return v;
}

Linha_v_1_f linha_v_1_f(float x, int indice) {
    Linha_v_1_f l = {v1f(x), indice};
    return l;
}

Tabela_v_1_f tabela_v_1_f(int tamanho_maximo) {
    Tabela_v_1_f t;
    t.linhas = malloc(tamanho_maximo * sizeof(Linha_v_1_f));
    t.tamanho = 0;
    t.tamanho_maximo = tamanho_maximo;
    return t;
}
Tabela_v_1_f tabela_v_1_f_ad(Tabela_v_1_f tabela, Linha_v_1_f linha) {
    for (int i = 0; i < tabela.tamanho; i++) {
        if (tabela.linhas[i].indice == linha.indice) {
            V1f v = tabela.linhas[i].v;
            fprintf(stderr,
                    "\n\nERROVoce esta tentando inserir uma linha com "
                    "indice %03d na "
                    "tabela, porem uma linha com esse indice ja existe.\n",
                    linha.indice);
            fprintf(stderr,
                    "\n\nERROA linha com indice %03d possui como "
                    "elemento: %2.0f\n\n\n",
                    linha.indice, v.x);
            exit(1);
        }
    }
    if (tabela.tamanho < tabela.tamanho_maximo) {
        tabela.linhas[tabela.tamanho] = linha;
        tabela.tamanho++;
        return tabela;
    }

    Linha_v_1_f* tmp = tabela.linhas;
    tabela.linhas = malloc(tabela.tamanho_maximo * sizeof(Linha_v_1_f));
    for (int i = 0; i < tabela.tamanho; i++) {
        tabela.linhas[i] = tmp[i];
    }
    tabela.linhas[tabela.tamanho] = linha;
    tabela.tamanho++;
    return tabela;
}

void procura_v_1_f(Tabela_v_1_f tabela, int quantidade, int indices[quantidade],
                   float resultado[quantidade]) {
    // Popula resultado com um valor qualquer
    // Isso é feito para que seja possível
    // identificar índices inexistentes
    for (int i = 0; i < quantidade; i++) {
        resultado[i] = -1;
    }

    for (int ind_indice = 0; ind_indice < quantidade; ind_indice++) {
        for (int ind_tabela = 0; ind_tabela < tabela.tamanho; ind_tabela++) {
            if (tabela.linhas[ind_tabela].indice == indices[ind_indice]) {
                resultado[ind_indice] = tabela.linhas[ind_tabela].v.x;
            }
        }
        if (resultado[ind_indice] == -1) {
            fprintf(stderr,
                    "\n\nERRO: Não há nenhuma linha com indice %d na "
                    "tabela\n",
                    indices[ind_indice]);
            fprintf(stderr, "Os indices existentes sao: (");
            for (int i = 0; i < tabela.tamanho - 1; i++) {
                fprintf(stderr, "%d, ", tabela.linhas[i].indice);
            }
            fprintf(stderr, "%d)\n\n\n",
                    tabela.linhas[tabela.tamanho - 1].indice);
            exit(1);
        }
    }
}
void print_tabela_v_1_f(Tabela_v_1_f tabela) {
    for (int i = 0; i < tabela.tamanho; i++) {
        printf("%03d: %3.3f\n", tabela.linhas[i].indice, tabela.linhas[i].v.x);
    }
}
void troca(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void n_menores(int n, int buff[n], Tabela_v_1_f tabela) {
    // Popula o buffer com o indíce do maior elemento
    int ind_maior = 0;
    for (int i = 0; i < tabela.tamanho; i++) {
        if (tabela.linhas[i].v.x > tabela.linhas[ind_maior].v.x) {
            ind_maior = i;
        }
    }
    for (int i = 0; i < n; i++) {
        buff[i] = ind_maior;
    }

    // Insertion sort
    for (int i = 0; i < tabela.tamanho; i++) {
        if (tabela.linhas[i].v.x < tabela.linhas[buff[0]].v.x) {
            int j = 0;
            for (j = 0; j < n; j++) {
                if (tabela.linhas[i].v.x > tabela.linhas[buff[j]].v.x) {
                    break;
                }
            }
            // Aqui j é o indíce, no buffer, em que i deve estar
            buff[0] = i;
            for (int k = 0; k < j - 1; k++) {
                troca(&buff[k], &buff[k + 1]);
            }
        }
    }
}

// ------------------------ Tabelas de 3 elementos ------------------------
V3f v3f(float x1, float x2, float x3) {
    V3f v = {x1, x2, x3};
    return v;
}
V3f v_3_f_ad(V3f x, V3f y) {
    x.x1 += y.x1;
    x.x2 += y.x2;
    x.x3 += y.x3;
    return x;
}

Linha_v_3_f linha_v_3_f(float x1, float x2, float x3, int indice) {
    Linha_v_3_f l = {v3f(x1, x2, x3), indice};
    return l;
}

Tabela_v_3_f tabela_v_3_f(int tamanho_maximo) {
    Tabela_v_3_f t;
    t.linhas = malloc(tamanho_maximo * sizeof(Linha_v_3_f));
    t.tamanho = 0;
    t.tamanho_maximo = tamanho_maximo;
    return t;
}
Tabela_v_3_f tabela_v_3_f_ad(Tabela_v_3_f tabela, Linha_v_3_f linha) {
    for (int i = 0; i < tabela.tamanho; i++) {
        if (tabela.linhas[i].indice == linha.indice) {
            V3f v = tabela.linhas[i].v;
            fprintf(stderr,
                    "\n\nERRO: Voce esta tentando inserir uma linha "
                    "com indice %03d "
                    "na tabela, porem uma linha com esse indice ja "
                    "existe.\n",
                    linha.indice);
            fprintf(stderr,
                    "A linha com indice %03d possui como elementos: "
                    "(%2.0f, %2.0f, "
                    "%2.0f)\n\n\n",
                    linha.indice, v.x1, v.x2, v.x3);
            exit(1);
        }
    }
    if (tabela.tamanho < tabela.tamanho_maximo) {
        tabela.linhas[tabela.tamanho] = linha;
        tabela.tamanho++;
        return tabela;
    }
    Linha_v_3_f* tmp = tabela.linhas;
    tabela.tamanho_maximo *= 2;
    tabela.linhas = malloc(tabela.tamanho_maximo * sizeof(Linha_v_3_f));
    for (int i = 0; i < tabela.tamanho; i++) {
        tabela.linhas[i] = tmp[i];
    }
    tabela.linhas[tabela.tamanho] = linha;
    tabela.tamanho++;
    return tabela;
}

int v_3_f_maior(V3f v) {
    if (v.x1 > v.x2 && v.x1 > v.x3) {
        return 0;
    }
    if (v.x2 > v.x1 && v.x2 > v.x3) {
        return 1;
    }
    return 2;
}

void print_tabela_v_3_f(Tabela_v_3_f tabela) {
    for (int i = 0; i < tabela.tamanho; i++) {
        Linha_v_3_f tmp = tabela.linhas[i];
        printf("%03d: %2.0f, %2.0f, %2.0f\n", tmp.indice, tmp.v.x1, tmp.v.x2,
               tmp.v.x3);
    }
}

// ------------------------ Tabelas de 4 elementos ------------------------
V4f v4f(float x1, float x2, float x3, float x4) {
    V4f v = {x1, x2, x3, x4};
    return v;
}

Linha_v_4_f linha_v_4_f(float x1, float x2, float x3, float x4, int indice) {
    Linha_v_4_f l = {v4f(x1, x2, x3, x4), indice};
    return l;
}

Tabela_v_4_f tabela_v_4_f(int tamanho_maximo) {
    Tabela_v_4_f t;
    t.linhas = malloc(tamanho_maximo * sizeof(Linha_v_4_f));
    t.tamanho = 0;
    t.tamanho_maximo = tamanho_maximo;
    return t;
}
Tabela_v_4_f tabela_v_4_f_ad(Tabela_v_4_f tabela, Linha_v_4_f linha) {
    for (int i = 0; i < tabela.tamanho; i++) {
        if (tabela.linhas[i].indice == linha.indice) {
            V4f v = tabela.linhas[i].v;
            fprintf(stderr,
                    "\n\nERRO: Voce esta tentando inserir uma linha "
                    "com indice %03d "
                    "na tabela, porem uma linha com esse indice ja "
                    "existe.\n",
                    linha.indice);
            fprintf(stderr,
                    "A linha com indice %03d possui como elementos: "
                    "(%2.0f, %2.0f, "
                    "%2.0f, %2.0f)\n\n\n",
                    linha.indice, v.x1, v.x2, v.x3, v.x4);
            exit(1);
        }
    }
    if (tabela.tamanho < tabela.tamanho_maximo) {
        tabela.linhas[tabela.tamanho] = linha;
        tabela.tamanho++;
        return tabela;
    }
    Linha_v_4_f* tmp = tabela.linhas;
    tabela.tamanho_maximo *= 2;
    tabela.linhas = malloc(tabela.tamanho_maximo * sizeof(Linha_v_4_f));
    for (int i = 0; i < tabela.tamanho; i++) {
        tabela.linhas[i] = tmp[i];
    }
    tabela.linhas[tabela.tamanho] = linha;
    tabela.tamanho++;
    return tabela;
}

void print_tabela_v_4_f(Tabela_v_4_f tabela) {
    for (int i = 0; i < tabela.tamanho; i++) {
        Linha_v_4_f tmp = tabela.linhas[i];
        printf("%03d: %.2f, %.2f, %.2f, %.2f\n", tmp.indice, tmp.v.x1, tmp.v.x2,
               tmp.v.x3, tmp.v.x4);
    }
}