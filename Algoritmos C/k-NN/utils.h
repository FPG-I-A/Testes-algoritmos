#ifndef UTILS_H
#define UTILS_H
#include <math.h>

#ifndef TABELA_H
#include "tabela.h"
#endif // TABELA_H

float distancia_v_v(V4f u, V4f v);
Tabela_v_1_f distancia_v_t(V4f vetor, Tabela_v_4_f t);

#endif // UTILS_H