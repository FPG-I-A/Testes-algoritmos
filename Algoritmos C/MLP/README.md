# Algoritmo em C para utilização de MLP

Nesta pasta há atualmente 4 arquivos: um [`Makefile`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20C/MLP/Makefile) para compilação de execução de códigos utilizando [GNU Make](https://www.gnu.org/software/make/), o script [`cria_main.py`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20C/MLP/cria_main.py) utilizado para criar o arquivo `main.c` e `entradas-saidas.h`, ponto de entrada do MLP e por fim os arquivos [`structs.h`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20C/MLP/structs.h), [`structs.c`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20C/MLP/structs.c) que implementam uma interface de vetores e matrizes utilizada para o algoritmo e, por fim, [`ativacoes.h`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20C/MLP/ativacoes.h) e [`ativacoes.c`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20C/MLP/ativacoes.c) com a implementação das funções de ativação. 

## Makefile
Arquivo de compilação e execução de scripts.
- `make gera_main`: executa `python cria_main.py` para criar `main.c` e `entradas-saidas.h`
- `make knn`: compila `main.c`, `structs.c` e `ativacoes.c` em um executável `main.o`
- `make clean`: apaga arquivos de compilação e auxiliares
- `make` ou `make all`: executa `clean`,`gera_main` e `knn`

## `cria_main.py`

Esse é um arquivo auxiliar, o objetivo deste script é ler o conjunto de dados da pasta `FPG-I-A/Dados` gerado por [`FPG-I-A/Algoritmos python/download.py`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20python/download.py) e da pasta `FPG-I-A/Algoritmos python/modelo`, criados por `FPG-I-A/Algoritmos python/mlp-treino.py` e criar uma função `main` em um arquivo chamado `main.c` para a realização da inferência de MLP. Isso é feito dessa forma para que seja mais simples trazer para linguagem C qualquer rede, com qualquer arquitetura, desde que utilize apenas MLP, a partir do que foi treinado pelo PyTorch.

## `ativacoes.c` e `ativacoes.h`

Arquivos que implementam duas funções de ativação: sigmoide e relu com definições abaixo:

- sigmoide: $ y = \dfrac{1}{1 + e^{-x}} $
- relu: $ y = 0 if x \geq 0 else 1 $
  
## `structs.c` e `structs.h`

Esses arquivos implementam as estruturas de neurônio, camada e rede. Todas as três possuem no mínimo uma função construtora, que cria uma estrutura daquele tipo e uma de print, que mostra na tela a estrutura, e uma de processamento, que calcula a saída daquela estrutura dada uma entrada.

Obs.: no caso do neurônio, a saída é $ativacao(pesos \cdot entrada + viés)$, no caso de uma cada é um vetor contendo a saída de cada neurônio da camada e no caso da rede é a saída da última camada, o algoritmo de processamento da rede vai ser explicado com maior detalhes em [`processa_rede`](#processa_rede).

### Neurônios

A estrutura de neurônio possuí um número inteiro, representando o número de entradas do neurônio, um _float_ contendo o viés do nuerônio, uma lista, ou pontiro, de _floats_ contendo os seus pesos e um ponteiro para uma função, que é a sua função de ativação.

### Camada

A estrutura de camada é simplesmente uma lista de neurônios. Como a quantidade de neurônios em uma camada não pode mudar, trata-se de uma lista comum, além disso essa estrutura armazena o número de entradas e o número de saídas da camada. O número de entradas é igual ao número de entradas de cada neurônio, o número de saídas é igual ao número de neurônios.

### Rede

A estrutura de rede é a mais complexa de todas. Ela possuí uma [lista dinâmica](https://en.wikipedia.org/wiki/Dynamic_array) de camadas, pois o número de camadas na rede pode aumentar, na verdade a rede foi implementada de forma que, inicialmente ela possuí apenas uma camada, e as outras camadas devem ser adicionadas a ela.

Os outros campos da estrutura da rede são a quantidade de camadas e a quantidade máxima de camadas, o número de entradas e o número de saídas.

#### `adiciona_camada`

Função para adicionar uma nova camada à rede. Essa função implementa a operação de adição em uma lista dinâmica, desta forma, antes de realizar a adição em si, ela verifica se há espaço disponível e, caso não haja, aloca o dobro de espaço para uma nova lista, copia todos os elementos existentes para o novo espaço alocado e, por fim, apaga a lista anterior para só então adicionar o novo elemento.

#### `processa_rede`

Função de processamento de uma entrada. Essa função é um pouco mais complexa pois possuí um vetor que deve ter tamanho variável já que o número de saídas não é constante para todas as camadas. Por isso são criados dois vetores, `tmp1` e `tmp2`, o primeiro com o intuíto de armazenar as entradas e o segundo com o intuíto de armazenar as saídas e, a cada camada que passa, memória é alocada e desalocada para que o tamanho desses vetores possa ser modificado.

#### `processa_lote`

Essa função tem o objetivo de calcular a saída para diversas entradas diferentes. Desta forma, ela recebe uma matriz de entradas em que cada linha é uma entrada diferente, itera sobre essa matriz, e coloca os resultados em um vetor de saídas.
