from pathlib import Path

import numpy as np


def cabecalho(f):
    f.write('#include "structs.h"\n')
    f.write('#include "ativacoes.h"\n')
    f.write('#include "entradas-saidas.h"\n')

    f.write(
        '\n\n// -------------------- Funções auxiliares --------------------\n'
    )
    f.write('int argmax(int tamanho, float vetor[tamanho]) {\n')
    f.write('\tint resultado = 0;\n')
    f.write('\tfor (int i = 1; i < tamanho; i++) {\n')
    f.write('\t\tif (vetor[i] > vetor[resultado]) {\n')
    f.write('\t\t\tresultado = i;\n\t\t}\n\t}\n\t return resultado;\n}\n')

    f.write('\n\nint main(){\n\n')


def cria_camada(f, pasta, camada):
    vieses = np.loadtxt(pasta / 'bias.txt', delimiter=',')
    pesos = np.loadtxt(pasta / 'weight.txt', delimiter=',')
    f.write(f'\t// ---------- Camada {camada} ----------\n')

    # Escreve os tamanhos de entrada e saída da camada
    with open('entradas-saidas.h', mode='a') as f2:
        f2.write(f'#define ENTRADAS_C{camada} {pesos.shape[1]}\n')
        f2.write(f'#define SAIDAS_C{camada} {vieses.shape[0]}\n')

    # Escreve os pesos da camada
    f.write(f'\tfloat b{camada}[{vieses.shape[0]}] = ' + '{\n')
    for i in range(vieses.shape[0] - 1):
        if vieses[i] >= 0:
            f.write(f'\t\t {vieses[i]:.5f},\n')
        else:
            f.write(f'\t\t{vieses[i]:.5f},\n')
    if vieses[-1] >= 0:
        f.write(f'\t\t {vieses[-1]:.5f}\n' + '\t};\n\n')
    else:
        f.write(f'\t\t{vieses[-1]:.5f}\n' + '\t};\n\n')

    f.write(f'\tfloat w{camada}[][{pesos.shape[1]}] = ' + '{\n')
    for i, linha in enumerate(pesos):
        f.write('\t\t{')
        for j, valor in enumerate(linha):
            if j != linha.shape[0] - 1:
                if valor >= 0:
                    f.write(f' {valor:.5f}, ')
                else:
                    f.write(f'{valor:.5f}, ')
            else:
                if valor >= 0:
                    f.write(f' {valor:.5f}')
                else:
                    f.write(f'{valor:.5f}')
        f.write('\t},\n')
    f.write('\t};\n\n')


def cria_dataset(f, pasta, xy):
    arquivo = xy + '_teste.csv'
    dados = np.loadtxt(pasta / arquivo, delimiter=',')

    # Escreve os tamanhos do dataset
    if xy == 'x':
        with open('entradas-saidas.h', mode='a') as f2:
            f2.write(f'#define AMOSTRAS_DADOS {dados.shape[0]}\n')

    f.write(f'\tfloat {xy}_teste[][{dados.shape[1]}] = ' + '{\n')
    for i, linha in enumerate(dados):
        f.write('\t\t{')
        for j, valor in enumerate(linha):
            if j != linha.shape[0] - 1:
                f.write(f'{valor:.2f}, ')
            else:
                f.write(f'{valor:.2f}' + '},\n')

    f.write('\t};\n\n')


def cria_rede(f, n_camadas):
    f.write(f'\t// Cria a rede neural\n')
    f.write(f'\tRede r = rede(ENTRADAS_C0, SAIDAS_C0, b0, w0, sigmoide);\n')

    for camada in range(1, n_camadas):
        f.write(
            f'\tr = adiciona_camada(r, ENTRADAS_C{camada}, SAIDAS_C{camada}, b{camada}, w{camada}, sigmoide);\n'
        )

    f.write('\tprinta_rede(r, true);\n\n')


def processa_dados(f):
    f.write(f'\t// Realiza inferência e calcula acurácia\n')
    f.write(
        f'\tfloat **resultado = processa_lote(r, AMOSTRAS_DADOS, x_teste);\n'
    )
    f.write('\tint acertos = 0;\n')

    f.write('\tfor (int i = 0; i < AMOSTRAS_DADOS; i++) {\n')
    f.write(
        '\t\tif (argmax(SAIDAS_C2, resultado[i]) == argmax(SAIDAS_C2, y_teste[i])) {\n'
    )
    f.write('\t\t\tacertos++;\n\t\t}\n\t}')

    f.write('\n\n\t// Mostra resultados\n')
    f.write('\tprintf("Quantidade de acertos: %d' + r'\n' + '", acertos);\n')
    f.write(
        '\tprintf("Acurácia: %.2f%%'
        + r'\n'
        + '", 100.0 * acertos / AMOSTRAS_DADOS);\n'
    )


with open('main.c', mode='w') as f:
    cabecalho(f)

    # Criação do arquivo com tamanhos de entradas e saidas
    if Path('entradas-saidas.h').exists():
        Path('entradas-saidas.h').unlink()

    # Criação dos vetores de pesos
    f.write(
        '\t// -------------------- Pesos de cada camada --------------------\n'
    )
    raiz_modelo = Path('..', '..', 'Algoritmos python', 'modelo')
    pastas = list(raiz_modelo.glob('*'))
    n_camadas = len(pastas)
    pastas.sort(key=lambda i: str(i).strip('modelo/l'))
    for camada, pasta in enumerate(pastas):
        cria_camada(f, pasta, camada)

    # Criação dos conjuntos de treino e teste
    f.write('\t// -------------------- Dados de teste --------------------\n')
    raiz_dados = Path('..', '..', 'Dados')
    for dado in 'xy':
        cria_dataset(f, raiz_dados, dado)

    # Criação da rede e cálculo de acurácia
    f.write(
        '\t// -------------------- Criação de rede e inferência --------------------\n'
    )
    cria_rede(f, n_camadas)
    processa_dados(f)

    f.write('\n}\n')
