from typing import Callable

import numpy as np
import numpy.typing as npt


class Ativacoes:
    def __init__(self):
        return

    def sigmoide(self, x):
        return 1 / (1 + np.exp(x))

    def relu(self, x):
        if x.ndim == 0:
            return x if x > 0 else 0
        resultados = []
        for valor in x:
            resultados.append(valor if valor > 0 else 0)
        return resultados

    def tanh(self, x):
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
        return f'Neurônio com {self.entradas} entradas'

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
        self, neuronios: list, ativacao: Callable = Ativacoes().sigmoide
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


camadas = 7
entradas = 4
saidas = 2
tamanhos = [2, 4, 8, 16, 8, 4, 2]
print(tamanhos)

rede = MLP([Camada([Neuronio(np.random.randn(entradas)) for _ in range(4)])])
for camada, tamanho in enumerate(tamanhos):
    rede.adiciona_camada(
        Camada(
            [
                Neuronio(np.random.randn(rede.camadas[-1].tamanho))
                for _ in range(tamanho)
            ]
        )
    )

rede.adiciona_camada(
    Camada(
        [
            Neuronio(np.random.randn(rede.camadas[-1].tamanho))
            for i in range(saidas)
        ]
    )
)

for camada in rede.camadas:
    print(camada)

entradas = np.random.randn(10, entradas)
print(rede.processa(entradas))
