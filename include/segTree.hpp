#ifndef SEG_TREE_HPP
#define SEG_TREE_HPP

#include "matriz.hpp"

struct NoArvore {
    Matriz valor;
    NoArvore* filhoEsquerda;
    NoArvore* filhoDireita;
    NoArvore* pai;
};

class SegTree {
private:
    int n;
    NoArvore* raiz;

    void construir(NoArvore* no, int esquerda, int direita);
    void atualizar(NoArvore* no, int esquerda, int direita, int idx, const Matriz& valor);
    Matriz consultar(NoArvore* no, int esquerda, int direita, int consultarEsquerda, int consultarDireita);

public:
    SegTree(int size);
    ~SegTree();
    void atualizar(int idx, const Matriz& valor);
    Matriz consultar(int consultarEsquerda, int consultarDireita);
};

#endif
