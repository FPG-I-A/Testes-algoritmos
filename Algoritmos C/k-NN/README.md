# Algoritmo em C para utilização de k-NN

Nesta pasta há atualmente 4 arquivos: um [`Makefile`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20C/k-NN/Makefile) para compilação de execução de códigos utilizando [GNU Make](https://www.gnu.org/software/make/), o script [`cria_main.py`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20C/k-NN/cria_main.py) utilizado para criar o arquivo `main.C`, ponto de entrada do k-NN e por fim os arquivos [`structs.h`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20C/k-NN/structs.h) e [`structs.c`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20C/k-NN/structs.c) que implementam uma interface de vetores e matrizes utilizada para o algoritmo.

## Makefile
Arquivo de compilação e execução de scripts.
- `make gera_main`: executa `python cria_main.py` para criar `main.c`
- `make knn`: compila `main.c` e `structs.c` em um executável `main.o`
- `make clean`: apaga arquivos de compilação e auxiliares
- `make` ou `make all`: executa `clean`,`gera_main` e `knn`

## `cria_main.py`

Esse é um arquivo auxiliar, o objetivo deste script é ler o conjunto de dados da pasta `FPG-I-A/Dados` gerado por [`FPG-I-A/Algoritmos python/download.py`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20python/download.py) e criar uma função `main` em um arquivo chamado `main.c` para a realização do k-NN. Isso é feito desta forma por um único motivo: conjuntos de dados diferentes possuem diferentes números de entradas e saídas, desta forma é mais simples trabalhar com diversos conjuntos de dados fazendo o mínimo de modificações no código. Ele deve ser executado antes de todos, a não ser que se use o [`Makefile`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20C/k-NN/Makefile) para compilação.

## `structs.c` e `structs.h`

Esses arquivos implementam as matrizes (tabela) e vetores (linha) utilizadas no algoritmo, bem como as funções realizadas sobre elas.

### Linhas

Uma linha é um struct contendo seu tamanho, um índice (útil para criação de matrizes e aplicação do algoritmo) e um _array_ de _floats_ contendo os elementos. Para essa estrutura de dados foram criadas funções para mostrá-la, de forma elegante, no terminal `print_linha`, uma função construtora, que cria uma linha, `linha`, as outras funções, vale a pena detalhar mais um pouco.

#### `n_menores`

Essa função, dado uma linha e um inteiro n, menor que quantidade de elementos da linha, retorna um ponteiro para inteiros contendo os índices dos menores elementos do _array_ da linha. O _array_ retornado vem ordenado sendo que o seu primeiro elemento é o maior de todos e o último é o menor. Esse _array_ de indíces é construído utilizando [_insertion sort_](https://pt.wikipedia.org/wiki/Insertion_sort), que é muito eficiente para valores pequenos de n.

#### `maior_linha`

Similar à função `n_menores`, porém ao contrário e sempre com $n=1$. Desta forma, esta função retorna um único número inteiro que é o índice do maior elemento do _array_ da linha. O funcionamento não é nada sofisticado, apenas um loop que busca o maior elemento.

#### `distancia`

Função que recebe duas linhas e produz como resultado um _float_ contendo a [distância euclidiana](https://pt.wikipedia.org/wiki/Dist%C3%A2ncia_euclidiana) entre as linhas. A função é apenas um loop que executa  a fórmula:

$$
y = \sqrt{\sum_{i=0}^N(x_i - y_i)^2}
$$

### Tabelas

As tabelas possuem implementação um pouco mais sofisticada, isso pois devem ser matrizes de tamanho variável, por isso ela é implementada como uma [lista dinâmica](https://en.wikipedia.org/wiki/Dynamic_array) de linhas. Assim, possuí como propriedades o tamanho das linhas, o número de linhas, o número máximo de linhas (capacidade), e um ponteiro para as linhas. As funções existentes, além das mais simples de contrução e de _display_, respectivamente `tabela` e `print_tabela` estão explicadas abaixo.

#### `tabela_loc`

Além de uma tabela, esta função recebe um inteiro, índice, o que ela faz é retornar a linha com o índice fornecido na tabela. Trata-se de um `df.loc` extremamente rudimentar. Se não houver linha com este índice na tabela, o programa é fechado com um erro.

#### `tabela_add`

Adiciona uma nova linha na tabela, lembrando que todas as linhas em uma tabela deve ter o mesmo tamanho. Essa função implementa a operação de adição em uma lista dinâmica, desta forma, antes de realizar a adição em si, ela verifica se há espaço disponível e, caso não haja, aloca o dobro de espaço para uma nova lista, copia todos os elementos existentes para o novo espaço alocado e, por fim, apaga a lista anterior para só então adicionar o novo elemento.

#### `distancia_tabela`

Calcula a distância de uma linha para todas as linhas de uma tabela, o resultado é uma lista de _floats_ e é calculado apenas como um loop nas linhas da tabela que coloca o valor de `distancia` da linha fornecida com a linha atual da tabela na lista de resultado.


