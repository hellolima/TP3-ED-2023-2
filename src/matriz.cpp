#include "../include/matriz.hpp"

Matriz::Matriz() {
    conteudo[0][0] = conteudo[1][1] = 1; // Inicializa como a matriz identidade
    conteudo[0][1] = conteudo[1][0] = 0;
}

void Matriz::multiplicar(const Matriz& a, const Matriz& b) { // Método para multiplicar duas matrizes. Como toda matriz é 2x2, conforme o enunciado, e só é possível criar matrizes 2x2, verificações relacionadas à dimensão das matrizes não foram adicionadas.
    long long int resultado[2][2]; 

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            resultado[i][j] = 0;
            for (int k = 0; k < 2; ++k) {
                resultado[i][j] += (a.conteudo[i][k] * b.conteudo[k][j]) % MODULO;
                resultado[i][j] %= MODULO;
            }
        }
    }

    // Atualiza a matriz que chamou o método(corrente) com o resultado
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            conteudo[i][j] = resultado[i][j];
        }
    }
}
