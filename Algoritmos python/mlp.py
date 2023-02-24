from pathlib import Path
from typing import Callable

import numpy as np
import numpy.typing as npt

from time import time


class Ativacoes:
    def sigmoide(x):
        return 1 / (1 + np.exp(-x))

    def relu(x):
        if x.ndim == 0:
            return x if x > 0 else 0
        resultados = []
        for valor in x:
            resultados.append(valor if valor > 0 else 0)
        return resultados

    def tanh(x):
        exp = np.exp(2 * x)
        return (exp - 1) / (exp + 1)


class Neuronio:
    def __init__(self, pesos: npt.ArrayLike, vies: npt.DTypeLike = 0):
        pesos = np.array(pesos)
        assert (
            pesos.ndim == 1
        ), f'O vetor de pesos deve ter apenas uma dimensão, porém ela possuí {pesos.ndim}'
        self.pesos = pesos
        self.entradas = len(pesos)
        self.vies = vies

    def __len__(self):
        return self.entradas

    def __str__(self):
        string = f'Neurônio com {self.entradas} entradas'
        string += f'\n\tPesos: {self.pesos}'
        string += f'\n\tViés:  {self.vies}'
        return string

    def processa(
        self, entradas: npt.ArrayLike, ativacao: Callable
    ) -> npt.ArrayLike:
        entradas = np.array(entradas)
        assert entradas.T.shape[0] == len(
            self
        ), f'O número de entradas deve ser o mesmo que o número de pesos, mas são, respectivamente, {entradas.shape[1]} e {len(self)}'
        produto = self.pesos @ entradas.T + self.vies

        return ativacao(produto)


class Camada:
    def __init__(
        self, neuronios: list, ativacao: Callable = Ativacoes.sigmoide
    ):
        for neuronio in neuronios[1:]:
            assert (
                neuronios[0].entradas == neuronio.entradas
            ), f'O número de entradas de todos os neurônios de uma mesma camada deve ser igual, mas os neurônios escolhidos têm {[neuronio.entradas for neuronio in neuronios]}'
        self.neuronios = neuronios
        self.tamanho = len(neuronios)
        self.entradas = self.neuronios[0].entradas
        self.ativacao = ativacao

    def __len__(self):
        return self.tamanho

    def __str__(self):
        return f'Camada contendo {self.tamanho} neurônios de {self.entradas} entradas.'

    def processa(self, entradas: npt.ArrayLike) -> npt.ArrayLike:
        entradas = np.array(entradas)
        assert (
            entradas.ndim <= 2
        ), f'A matriz de entradas deve ter duas dimensões, porém ela possuí {entradas.ndim}'
        if entradas.ndim == 1:
            entradas = np.array([entradas])
        saida = []
        for neuronio in self.neuronios:
            saida.append(neuronio.processa(entradas, self.ativacao))
        return np.array(saida)


class MLP:
    def __init__(self, camadas: list = []):
        self.camadas = camadas
        self.n_camadas = len(self.camadas)

    def __len__(self):
        return self.n_camadas

    def __str__(self):
        return f'Rede neural do tipo MLP com {self.n_camadas} camadas, {self.camadas[0].entradas} entradas e {len(self.camadas[-1])} saidas'

    def adiciona_camada(self, camada):
        self.camadas.append(camada)
        self.n_camadas += 1

    def processa(self, entradas: npt.ArrayLike) -> npt.ArrayLike:
        entradas = np.array(entradas)
        assert (
            entradas.ndim <= 2
        ), f'A matriz de entradas deve ter duas dimensões, porém ela possuí {entradas.ndim}'
        if entradas.ndim == 1:
            entradas = np.array([entradas])
        assert (
            entradas.shape[1] == self.camadas[0].entradas
        ), f'A matriz de entradas deve ter {self.camadas[0].entradas} colunas, mas possuí {entradas.shape[1]}.'
        for camada in self.camadas:
            entradas = camada.processa(entradas).T
        return entradas


if __name__ == '__main__':
    # Carrega dados de teste
    dir_dados = Path('Dados')
    X_teste = np.loadtxt(dir_dados / 'X_teste.csv')
    y_teste = np.loadtxt(dir_dados / 'y_teste.csv')

    # Carrega modelo treinado
    dir_modelo = Path('modelo')
    modelo = MLP()
    pastas = list(dir_modelo.glob('*'))
    pastas.sort(key=lambda i: int(str(i).strip('modelo/l')))
    for pasta in pastas:
        print(pasta, end=':\n')
        vieses = np.loadtxt(pasta / 'bias.txt')
        pesos = np.loadtxt(pasta / 'weight.txt')
        neuronios = [
            Neuronio(peso, vies) for (peso, vies) in zip(pesos, vieses)
        ]
        #for neuronio in neuronios:
        #    print(neuronio)

        camada = Camada(neuronios)
        print(camada, end='\n\n')

        modelo.adiciona_camada(camada)

    print(modelo)

    inicio = time()
    acc = (modelo.processa(X_teste).argmax(1) == y_teste.argmax(1)).mean()
    print(f'{1000 * (time() - inicio)}ms')
    print(
        f'Acurácia: { acc * 100:>0.1f}%'
    )
