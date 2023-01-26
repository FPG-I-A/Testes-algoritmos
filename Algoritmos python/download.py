import os

import requests

response = requests.get(
    'https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data'
)
with open(os.path.join('Dados', 'iris.csv'), mode='wb') as f:
    f.write(response.content)
