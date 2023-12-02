#ifndef MATRIZ_HPP
#define MATRIZ_HPP

class Matriz {
public:
    long long int conteudo[2][2];

    Matriz();

    void multiplicar(const Matriz& a, const Matriz& b);
};

#endif
