from pathlib import Path
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


dir = Path('Dados')
X_treino = np.loadtxt(dir / 'X_treino.csv')
X_teste = np.loadtxt(dir / 'X_teste.csv')
y_treino = np.loadtxt(dir / 'y_treino.csv')
y_teste = np.loadtxt(dir / 'y_teste.csv')
inferencia = knn(11, X_treino, y_treino)
resultado = np.apply_along_axis(inferencia, 1, X_teste)

# Encontra acurácia
acertos = resultado == y_teste
acertos = acertos.all(axis=1)
print(
    f'Acurácia: {acertos.sum()} / {y_teste.shape[0]} = {acertos.mean() * 100}%'
)
