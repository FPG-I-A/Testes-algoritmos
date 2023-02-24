import os

import requests
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split

response = requests.get(
    'https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data'
)

if not os.path.exists('Dados'):
    os.mkdir('Dados')
with open(os.path.join('Dados', 'iris.csv'), mode='wb') as f:
    f.write(response.content)

dados = np.loadtxt(
    os.path.join('Dados', 'iris.csv'), delimiter=',', usecols=[0, 1, 2, 3]
)
y = pd.read_csv(
    os.path.join('Dados', 'iris.csv'),
    sep=',',
    usecols=[4],
    header=None,
    names=['Nome'],
)
y.loc[:, 'setosa'] = 0
y.loc[:, 'virginica'] = 0
y.loc[:, 'versicolor'] = 0
y.loc[y['Nome'] == 'Iris-setosa', 'setosa'] = 1
y.loc[y['Nome'] == 'Iris-virginica', 'virginica'] = 1
y.loc[y['Nome'] == 'Iris-versicolor', 'versicolor'] = 1
del y['Nome']
y = np.array(y)

# Separa conjunto de treino e teste e calcula resultados
X_treino, X_teste, y_treino, y_teste = train_test_split(
    dados, y, test_size=0.33, random_state=42
)

pd.DataFrame(X_treino).to_csv('Dados/x_treino.csv', index=False)
pd.DataFrame(X_teste).to_csv('Dados/x_teste.csv', index=False)
pd.DataFrame(y_treino).to_csv('Dados/y_treino.csv', index=False)
pd.DataFrame(y_teste).to_csv('Dados/y_teste.csv', index=False)
