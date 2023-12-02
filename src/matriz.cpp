#include "../include/matriz.hpp"

Matriz::Matriz() {
    conteudo[0][0] = conteudo[1][1] = 1; // Identidade
    conteudo[0][1] = conteudo[1][0] = 0;
}

void Matriz::multiplicar(const Matriz& a, const Matriz& b) {
    long long int resultado[2][2];

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            resultado[i][j] = 0;
            for (int k = 0; k < 2; ++k) {
                resultado[i][j] += (a.conteudo[i][k] * b.conteudo[k][j]) % 100000000;
                resultado[i][j] %= 100000000;
            }
        }
    }

    // Atualizar ambas as matrizes chamadoras com o resultadoado
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            conteudo[i][j] = resultado[i][j];
        }
    }
}
