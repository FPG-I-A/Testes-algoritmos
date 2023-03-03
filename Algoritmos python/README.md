# Algoritmos em pythoncom funcionalidades diversas

Atualmente há 4 _scripts_ nesta pasta: `download.py`,`k-nn.py`, `mlp-treino.py` e `mlp-teste.py`. Eles podem ser divididos em duas classes: setup e inferência.

## _Scripts_ de configuração
São eles [`download.py`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20python/download.py) e [`mlp-treino.py`](https://github.com/luis705/FPG-I-A/blob/main/Algoritmos%20python/mlp-treino.py). Os nomes dos _script_s são auto explicatórios, mas é interessante explicar alguns detalhes sobre eles.

### `download.py`
Esse _script_ realiza o download do conjunto de dados utilizado, no caso o dataset iris. Após fazer este download ele salva tanto os dados crus baixados, quanto os dados já separados em treino e teste em uma pasta criada na raiz do repositório chamada `Dados`. 

Esse arquivo sempre deve ser o primeiro a ser executado, já que todos os outros, tanto os em _python_ quanto os em _C_ dependem dos dados baixados.

Detalhe, caso se queira utilizar um outro conjunto de dados, esse arquivo deve ser modificado. Além de mudar a _url_ da qual os dados são baixados (linha 16), deve-se mudar também  a codificação _one-hot_ feita na saída do algoritmo, o Y (linhas 33 a 40).

### `mlp-treino.py`
Este arquivo realiza o treinamento de uma rede neural _feed-forward_, ou perceptron multicamadas que consiste em diversas camadas de neurônios simples.  Por mais que nele é realizada inferência também, o objetivo principal deste script é treinar a rede, para que ela possa ser implementada de forma crua, sem auxilio de _frameworks_ de aprendizagem profunda.

Para que o treino ocorra, foi utilizado o _framework_ _PyTorch_, assim nele há implementada uma classe para o conjunto de dados, que apenas lê os arquivos salvos por [`download.py`](#downloadpy).

Há também uma segunda classe utilizada para a criação do modelo da rede neural. Caso haja uma mudança de conjunto de dados, este é o outro arquivo que deve ser modificado, na definição das camadas da rede, (linhas 51 a 53) deve se modificar o número de entradas da primeira camada para o número de características do conjunto de dados e o número de neurônios na última, para o número de saídas, ou classes, do conjunto de dados.

Ao finalizar o treino, este arquivo salva os pesos e viéses na pasta `modelo` criada dentro desta pasta, de forma conveniente para a criação do MLP de outros modos.

## _Scripts_ de inferência

Os outros dois _scripts_ nesta pasta realizam a inferência nos dados, cada um com um algoritmo diferente e, novamente, com nomes auto explicativos.

### `k-nn.py`
O algoritmo de [k-nn](https://www.ibm.com/topics/knn) ou _K nearest neighbors_ apenas verifica quais amostras do conjunto de treino estão mais próximas da amostra do conjunto de teste e, atribuí como saída, a moda das saídas desses k mais próximos. 

Por causa disso, não há uma etapa de treino neste algoritmo, mas toda vez que acontece uma inferência deve ser olhado o conjunto de treino inteiro para encontrar os k vizinhos mais próximos. 

Porém, para que o algoritmo pudesse ser utilizado como algoritmos comuns, com uma etapa de treino, em que você fornece os dados de treino, e uma de teste, onde você fornece apenas os dados de teste, a função que realiza o cálculo do algoritmo foi implementada como uma [closure](https://imasters.com.br/back-end/apresentando-o-conceito-de-closures) que é, basicamente, uma função que retorna uma outra função. A vantagem disso é que a função interna, a retornada pela externa, tem acesso ao escopo de variáveis da função externa.

Desta forma, a função interna, nomeada dentro, se comporta como a função de inferência e recebe como argumento apenas os dados de teste, enquanto a função externa, chamda knn, se comporta como a função de treino recebendo como argumento somente os dados de treino.

### `mlp.py`
O arquivo que implementa o perceptron multicamadas utiliza uma abordagem de blocos funcionais. Nele são implementadas uma classe para realizar a função de um único neurônio artificial, uma classe para implementar a função de uma única camada linear (uma lista de neurônios) e uma classe para implementar a função de uma rede MLP (uma lista de camadas).

Essa forma simplifica a implementação, já que o processamento do dado de entrada segue sempre o mesmo princípio:

- Neurônio: $O = ativacao(W \cdot I + b)$
- Camada: $O_i = Neuronio_i(I)$
- Rede: $O = Camada_n(Camada_{n-1}(\cdots Camada_1(I)))$

Sendo $W$ os pesos do neurônio $b$ o seu viés, $I$ o vetor de entradas e $O$ as saídas (um número no caso do neurônio, um vetor no caso de camadas e da rede).

No código há uma terceira classe também que serve para agrupar as funções de ativação todas juntas. Além disso o arquivo lê os pesos e viéses salvos por [`mlp-treino.py`](#mlp-treinopy) e realiza a inferência.