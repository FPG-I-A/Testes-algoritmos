from pathlib import Path

import numpy as np


def cabecalho(f):
    f.write('#include "structs.h"\n')
    f.write('#include "dataset.h"')
    f.write('\n\nint main(int argc, char** argv){')


def recebe_argumentos(f):
    string = r"""
    int k;
    switch (argc) {
    case 1:
        k = 5;
        break;
    case 2:
        k = atoi(argv[1]);
        if (k == 0) {
            fprintf(stderr, "Você deve inserir um número inteiro como argumento.\n");
            exit(1);
        }
        break;
    default:
        fprintf(stderr, "Uso: ./%s k\n", argv[0]);
        fprintf(stderr, "\tk: número de vizinhos mais próximos. (opcional)\n");
        exit(1);
    }
    
"""
    f.write(string)


def gera_dataset(f, xy, treino_teste):
    dados = np.loadtxt(
        Path('..', '..', 'Dados', xy + '_' + treino_teste + '.csv'),
        delimiter=',',
    )

    with open('dataset.h', mode='a') as f2:
        string = (
            'float '
            + xy
            + '_'
            + treino_teste
            + f'[][{dados.shape[1]}] ='
            + ' {\n'
        )

        for i, linha in enumerate(dados):
            string += '\t\t{'
            for j, valor in enumerate(linha):
                if j != linha.shape[0] - 1:
                    string += f'{valor:.2f}, '
                else:
                    string += f'{valor:.2f}' + '},\n'

        string += '};\n\n'
        f2.write(string)

    f.write(
        f'\tTabela {xy.upper()}_{treino_teste} = tabela({dados.shape[1]}, {dados.shape[0]}, {xy}_{treino_teste});\n'
    )
    f.write(f'\tprintf("' + r'\n' + f'{xy}_{treino_teste}:");\n')
    f.write(f'\tprint_tabela({xy.upper()}_{treino_teste});\n\n')


def predicao_e_acuracia(f):
    string = r"""
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

    """
    f.write(string)


with open('main.c', mode='w') as f:
    cabecalho(f)
    recebe_argumentos(f)

    if Path('dataset.h').exists():
        Path('dataset.h').unlink()

    for treino_teste in ['treino', 'teste']:
        for xy in 'xy':
            gera_dataset(f, xy, treino_teste)

    predicao_e_acuracia(f)
