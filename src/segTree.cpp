#include "../include/segTree.hpp"

SegTree::SegTree(int tamanho) {
    n = 1;
    while (n < tamanho) n <<= 1;
    raiz = new NoArvore();
    construir(raiz, 0, n - 1);
}

SegTree::~SegTree() {
    // Implemente a lógica para liberar a memória alocada para a árvore (pode precisar de uma função recursiva)
}

void SegTree::construir(NoArvore* no, int esquerda, int direita) {
    if (esquerda == direita) {
        // Nó folha
        no->valor = Matriz();
        no->filhoEsquerda = no->filhoDireita = nullptr;
        return;
    }

    int meio = (esquerda + direita) / 2;
    
    no->filhoEsquerda = new NoArvore();
    no->filhoDireita = new NoArvore();
    
    no->filhoEsquerda->pai = no->filhoDireita->pai = no;

    construir(no->filhoEsquerda, esquerda, meio);
    construir(no->filhoDireita, meio + 1, direita);

    no->valor.multiplicar(no->filhoEsquerda->valor, no->filhoDireita->valor);
}

void SegTree::atualizar(int idx, const Matriz& novoValor) {
    atualizar(raiz, 0, n - 1, idx, novoValor);
}

void SegTree::atualizar(NoArvore* no, int esquerda, int direita, int idx, const Matriz& novoValor) {
    if (esquerda == direita) {
        no->valor = novoValor;
        return;
    }

    int meio = (esquerda + direita) / 2;
    if (idx <= meio) {
        if (no->filhoEsquerda == nullptr) {
            no->filhoEsquerda = new NoArvore();
            no->filhoEsquerda->pai = no;
        }
        atualizar(no->filhoEsquerda, esquerda, meio, idx, novoValor);
    } else {
        if (no->filhoDireita == nullptr) {
            no->filhoDireita = new NoArvore();
            no->filhoDireita->pai = no;
        }
        atualizar(no->filhoDireita, meio + 1, direita, idx, novoValor);
    }

    no->valor.multiplicar(no->filhoEsquerda->valor, no->filhoDireita->valor);
}

Matriz SegTree::consultar(int consultarEsquerda, int consultarDireita) {
    return consultar(raiz, 0, n - 1, consultarEsquerda, consultarDireita);
}

Matriz SegTree::consultar(NoArvore* no, int esquerda, int direita, int consultarEsquerda, int consultarDireita) {
    if (esquerda > consultarDireita || direita < consultarEsquerda) {
        Matriz identity;
        return identity;
    }

    if (esquerda >= consultarEsquerda && direita <= consultarDireita) {
        return no->valor;
    }

    int meio = (esquerda + direita) / 2;
    Matriz result;
    result.multiplicar(consultar(no->filhoEsquerda, esquerda, meio, consultarEsquerda, consultarDireita),
                    consultar(no->filhoDireita, meio + 1, direita, consultarEsquerda, consultarDireita));
    return result;
}
