#include "ativacoes.h"

float sigmoide(float x) {
    return 1 / (1 + exp(-x));
}

float relu(float x) {
    if (x >= 0) {
        return x;
    }
    return 0;
}