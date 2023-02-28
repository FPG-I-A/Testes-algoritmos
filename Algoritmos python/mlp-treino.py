from pathlib import Path
import shutil

import numpy as np
import torch
import torch.nn.functional as F
from torch import nn
from torch.utils.data import DataLoader, Dataset


class Iris(Dataset):
    def __init__(
        self,
        dir_dados,
        transform=None,
        treino=True,
        trasnform=None,
        target_transform=None,
    ):
        # Lê conjunto de dados
        self.dir = Path(dir_dados)
        if treino:
            self.x = torch.tensor(np.loadtxt(self.dir / 'x_treino.csv', delimiter=','))
            self.y = torch.tensor(np.loadtxt(self.dir / 'y_treino.csv', delimiter=','))
        else:
            self.x = torch.tensor(np.loadtxt(self.dir / 'x_teste.csv', delimiter=','))
            self.y = torch.tensor(np.loadtxt(self.dir / 'y_teste.csv', delimiter=','))

        # Salva funções de transformação
        self.transform = transform
        self.target_transform = target_transform

    def __len__(self):
        return self.x.shape[0]

    def __getitem__(self, idx):
        x = self.x[idx, :]
        if self.transform:
            x = self.transform(x)
        y = self.y[idx, :]
        if self.target_transform:
            y = self.target_transform(y)

        return x, y


class Rede(nn.Module):
    def __init__(self):
        super(Rede, self).__init__()

        self.l1 = nn.Linear(4, 8, dtype=torch.float64)
        self.l2 = nn.Linear(8, 8, dtype=torch.float64)
        self.l3 = nn.Linear(8, 3, dtype=torch.float64)

    def forward(self, x):
        x = F.sigmoid(self.l1(x))
        x = F.sigmoid(self.l2(x))
        logitos = F.sigmoid(self.l3(x))
        return logitos


def treino(dataloader, modelo, fn_erro, otimizador):
    tamanho = len(dataloader.dataset)
    for batch, (X, y) in enumerate(dataloader):
        # Envia pra GPU
        X, y = X.to(dispositivo), y.to(dispositivo)

        # Calcula erro
        pred = modelo(X)
        erro = fn_erro(pred, y)

        # Backpropagation
        otimizador.zero_grad()
        erro.backward()
        otimizador.step()

        erro, atual = erro.item(), (batch + 1) * len(X)
        print(f'Erro: {erro:>7f}  [{atual:>5d}/{tamanho:>5d}]')


def teste(dataloader, modelo, fn_erro):
    # Inicialização de variáveis auxiliares
    tamanho = len(dataloader.dataset)
    n_batches = len(dataloader)
    modelo.eval()

    erro_teste, corretos = 0, 0

    with torch.no_grad():
        for X, y in dataloader:
            # Envia pra GPU
            X, y = X.to(dispositivo), y.to(dispositivo)

            # Calcula erro
            pred = modelo(X)
            erro_teste += fn_erro(pred, y).item()
            corretos += (pred.argmax(1) == y).type(torch.float).sum().item()

    erro_teste /= n_batches
    corretos /= tamanho
    print(
        f'Erro de teste: \n Acurácia: {(100 * corretos):>0.1f}, Erro médio: {erro_teste:>8f} \n'
    )


if __name__ == '__main__':
    # Criação dos dataloaders
    treino_set, teste_set = Iris(
        Path('..', 'Dados'), treino=True, target_transform=lambda x: x.argmax()
    ), Iris(Path('..', 'Dados'), treino=False, target_transform=lambda x: x.argmax())
    treino_loader, teste_loader = DataLoader(treino_set, batch_size=25), DataLoader(
        teste_set, batch_size=25
    )

    # Checagem de dispositivo disponível
    dispositivo = (
        'cuda'
        if torch.cuda.is_available()
        else 'mps'
        if torch.backends.mps.is_available()
        else 'cpu'
    )

    modelo = Rede().to(dispositivo)
    fn_erro = nn.CrossEntropyLoss()
    otimizador = torch.optim.SGD(modelo.parameters(), lr=0.1)

    epocas = 500

    for t in range(epocas):
        print(f'Época: {t+1}\n' + '-' * 15)
        treino(treino_loader, modelo, fn_erro, otimizador)
        teste(teste_loader, modelo, fn_erro)

    print('Finalizado!')

    dir_modelo = Path('modelo')
    if dir_modelo.exists():
        shutil.rmtree(dir_modelo)
    dir_modelo.mkdir()
    for nome, parametro in modelo.named_parameters():
        pasta, nome = nome.split('.')
        dir_camada = dir_modelo / pasta
        dir_camada.mkdir(exist_ok=True)
        nome += '.txt'
        np.savetxt(dir_camada / nome, parametro.cpu().detach().numpy(), delimiter=',')
