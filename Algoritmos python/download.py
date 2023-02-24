from pathlib import Path

import numpy as np
import pandas as pd
import requests
from sklearn.model_selection import train_test_split

# Cria pasta de dados
dir = Path('..', 'Dados')
dir.mkdir(exist_ok=True)


# Baixa conjunto de dados e salva dados crus
dados_crus = dir / 'iris.csv'
response = requests.get(
    'https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data'
)
with open(dados_crus, mode='wb') as f:
    f.write(response.content)


# Carrega conjuntos de dados
x = np.loadtxt(dados_crus, delimiter=',', usecols=[0, 1, 2, 3])
y = pd.read_csv(
    dados_crus,
    sep=',',
    usecols=[4],
    header=None,
    names=['Nome'],
)

# One-hot
y.loc[:, 'setosa'] = 0
y.loc[:, 'virginica'] = 0
y.loc[:, 'versicolor'] = 0
y.loc[y['Nome'] == 'Iris-setosa', 'setosa'] = 1
y.loc[y['Nome'] == 'Iris-virginica', 'virginica'] = 1
y.loc[y['Nome'] == 'Iris-versicolor', 'versicolor'] = 1
del y['Nome']
y = np.array(y)

# Separa conjunto de treino e teste e calcula resultados
separados = train_test_split(x, y, test_size=0.33, random_state=42)

# Salva dados de treino e de teste
for nome, array in zip(['x_treino', 'x_teste', 'y_treino', 'y_teste'], separados):
    nome += '.csv'
    np.savetxt(dir / nome, array, delimiter=',')
