import os
from typing import Callable

import numpy as np
import numpy.typing as npt
import pandas as pd
from sklearn.model_selection import train_test_split


def calcula_distancias(u: npt.ArrayLike, v: npt.ArrayLike) -> npt.ArrayLike:
    assert isinstance(
        v, np.ndarray
    ), f'V deve ser um array numpy, e não {type(v)}'
    assert isinstance(
        u, np.ndarray
    ), f'U deve ser um array numpy, e não {type(u)}'
    assert (
        u.shape[1] == v.shape[0]
    ), f'U deve ter dimensão {v.shape} e não {u.shape}'
    return np.apply_along_axis(np.linalg.norm, 1, u - v)


def knn(k: int, X_treino: npt.ArrayLike, y_treino: npt.ArrayLike) -> Callable:
    def dentro(teste: np.ndarray) -> list:
        distancias = calcula_distancias(X_treino, teste)
        idx_menores = distancias.argsort()[:k]
        resultados_treino = y_treino[idx_menores]
        resultados_teste = [0, 0, 0]
        idx_teste = resultados_treino.sum(axis=0).argsort()[-1]
        resultados_teste[idx_teste] = 1
        return resultados_teste

    return dentro


dados = np.loadtxt(
    os.path.join('Dados', 'iris.csv'), delimiter=',', usecols=[0, 1, 2, 3]
)

# Ajusta dados de teste
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
inferencia = knn(11, X_treino, y_treino)
resultado = np.apply_along_axis(inferencia, 1, X_teste)

# Encontra o erro
erro = resultado - y_teste
print(erro)
