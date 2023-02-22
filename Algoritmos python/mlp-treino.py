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
            self.x = torch.tensor(np.loadtxt(self.dir / 'X_treino.csv'))
            self.y = torch.tensor(np.loadtxt(self.dir / 'y_treino.csv'))
        else:
            self.x = torch.tensor(np.loadtxt(self.dir / 'X_teste.csv'))
            self.y = torch.tensor(np.loadtxt(self.dir / 'y_teste.csv'))

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
        self.l2 = nn.Linear(8, 64, dtype=torch.float64)
        self.l3 = nn.Linear(64, 512, dtype=torch.float64)
        self.l4 = nn.Linear(512, 1024, dtype=torch.float64)
        self.l5 = nn.Linear(1024, 1024, dtype=torch.float64)
        self.l6 = nn.Linear(1024, 512, dtype=torch.float64)
        self.l7 = nn.Linear(512, 64, dtype=torch.float64)
        self.l8 = nn.Linear(64, 8, dtype=torch.float64)
        self.l9 = nn.Linear(8, 4, dtype=torch.float64)
        self.l10 = nn.Linear(4, 3, dtype=torch.float64)
        

    def forward(self, x):
        x = F.sigmoid(self.l1(x))
        x = F.sigmoid(self.l2(x))
        x = F.sigmoid(self.l3(x))
        x = F.sigmoid(self.l4(x))
        x = F.sigmoid(self.l5(x))
        x = F.sigmoid(self.l6(x))
        x = F.sigmoid(self.l7(x))
        x = F.sigmoid(self.l8(x))
        x = F.sigmoid(self.l9(x))
        logitos = F.sigmoid(self.l10(x))
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
        'Dados', treino=True, target_transform=lambda x: x.argmax()
    ), Iris('Dados', treino=False, target_transform=lambda x: x.argmax())
    treino_loader, teste_loader = DataLoader(
        treino_set, batch_size=25
    ), DataLoader(teste_set, batch_size=25)

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
    otimizador = torch.optim.SGD(modelo.parameters(), lr=.1)

    epocas = 500

    for t in range(epocas):
        print(f'Época: {t+1}\n' + '-' * 15)
        treino(treino_loader, modelo, fn_erro, otimizador)
        teste(teste_loader, modelo, fn_erro)

    print('Finalizado!')

    dir_modelo = Path('modelo')
    shutil.rmtree(dir_modelo)
    dir_modelo.mkdir()
    for nome, parametro in modelo.named_parameters():
        pasta, nome = nome.split('.')
        dir_camada = dir_modelo / pasta
        dir_camada.mkdir(exist_ok=True)
        nome += '.txt'
        np.savetxt(dir_camada / nome, parametro.cpu().detach().numpy())
