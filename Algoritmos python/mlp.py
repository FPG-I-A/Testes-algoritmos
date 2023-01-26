from typing import Callable

import numpy as np
import numpy.typing as npt


class Ativacoes:
    def __init__(self):
        return

    def sigmoide(self, x):
        return 1 / (1 + np.exp(x))

    def relu(self, x):
        if x.shape == 1:
            return x if x > 0 else 0
        resultados = []
        for valor in x:
            resultados.append(valor if valor > 0 else 0)
        return resultados

    def tanh(self, x):
        exp = np.exp(2 * x)
        return (exp - 1) / (exp + 1)


class Neuronio:
    def __init__(self, pesos: npt.ArrayLike, vies: npt.DTypeLike):
        self.pesos = pesos
        self.entradas = len(pesos)
        self.vies = vies

    def __len__(self):
        return self.entradas

    def __str__(self):
        return f"""Neurônio com {self.entradas} entradas"""

    def processa(
        self, entradas: npt.ArrayLike, ativacao: Callable
    ) -> npt.ArrayLike:
        entradas = np.array(entradas)
        assert entradas.T.shape[0] == len(
            self
        ), f'O número de entradas deve ser o mesmo que o número de pesos, mas são, respectivamente, {entradas.shape[1]} e {len(self)}'
        produto = self.pesos @ entradas.T + self.vies

        return ativacao(produto)


ativ = Ativacoes()
n_entradas = 4
n_amostras = 5
neuronio = Neuronio(np.random.randn(n_entradas), np.random.randn(1))
entradas = np.random.randn(n_amostras, n_entradas)
resultado_tanh = neuronio.processa(entradas, ativ.tanh)
resultado_relu = neuronio.processa(entradas, ativ.relu)
resultado_sigmoide = neuronio.processa(entradas, ativ.sigmoide)
print('Resultado para função de ativação tanh:')
print(resultado_tanh)
print('\nResultado para função de ativação relu:')
print(resultado_relu)
print('\nResultado para função de ativação sigmoide:')
print(resultado_sigmoide)
