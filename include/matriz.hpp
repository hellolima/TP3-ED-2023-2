#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#define MODULO (100000000)

/**
 * @brief Classe que representa uma matriz 2x2.
 */
class Matriz {
public:
    /** @brief Conteúdo da matriz 2x2. */
    long long int conteudo[2][2];

    /**
     * @brief Construtor padrão que inicializa a matriz como a identidade.
     */
    Matriz();

    /**
     * @brief Multiplica duas matrizes 2x2.
     * 
     * @param a Primeira matriz a ser multiplicada.
     * @param b Segunda matriz a ser multiplicada.
     */
    void multiplicar(const Matriz& a, const Matriz& b);
};

#endif
