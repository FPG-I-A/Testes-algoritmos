from pathlib import Path

import numpy as np

dir_dados = Path('..', '..', 'Dados')

tipos = ['treino', 'teste']
variaveis = ['x', 'y']

valores = dict()

for variavel in variaveis:
    for tipo in tipos:
        nome_arq = variavel + '_' + tipo + '.csv'
        valores[nome_arq[:-4]] = np.loadtxt(
            dir_dados / nome_arq, delimiter=','
        )

with open('dataset.h', mode='w') as f:
    for chave, valor in valores.items():
        # Variável declaracao representa a declaração da variável
        declaracao = 'float '

        declaracao += chave + f'[][{valor.shape[1]}]' + ' = {\n'
        f.write(declaracao)

        # Valores da variável (matriz)
        for i, linha in enumerate(valor):
            f.write('\t{')
            for elemento in linha:
                f.write(f'{elemento}, ')
            # A cada linha de código escreve 3 linhas da matriz
            if (i + 1) % 3 != 0:
                f.write('},')
            else:
                f.write('},\n')

        # Finalização da variável
        f.write('};\n\n')
