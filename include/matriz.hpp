#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#define MODULO (100000000)

class Matriz {
public:
    long long int conteudo[2][2];

    Matriz();

    void multiplicar(const Matriz& a, const Matriz& b);
};

#endif
