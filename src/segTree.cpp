#include "../include/segTree.hpp"
#include <iostream>

SegTree::SegTree(int tamanho) {
    n = 1;
    while (n < tamanho) n <<= 1;
    raiz = new NoArvore();
    if (!raiz) {
        std::cerr << "Erro: Falha na alocação de memória para a raiz da árvore." << std::endl;
        // Pode ser necessário tomar medidas adicionais em caso de falha de alocação
        return;
    }
    construir(raiz, 0, n - 1);
}

SegTree::~SegTree() {
    liberarMemoria(raiz);
}

void SegTree::liberarMemoria(NoArvore* no) {
    if (no) {
        liberarMemoria(no->filhoEsquerda);
        liberarMemoria(no->filhoDireita);
        delete no;
    }
}

void SegTree::construir(NoArvore* no, int esquerda, int direita) {
    if (!no) {
        std::cerr << "Erro: Falha na alocação de memória para um nó da árvore." << std::endl;
        // Pode ser necessário tomar medidas adicionais em caso de falha de alocação
        return;
    }

    if (esquerda == direita) {
        // Nó folha
        no->valor = Matriz();
        no->filhoEsquerda = no->filhoDireita = nullptr;
        return;
    }

    int meio = (esquerda + direita) / 2;

    no->filhoEsquerda = new NoArvore();
    no->filhoDireita = new NoArvore();

    if (!no->filhoEsquerda || !no->filhoDireita) {
        std::cerr << "Erro: Falha na alocação de memória para os filhos de um nó da árvore." << std::endl;
        // Pode ser necessário tomar medidas adicionais em caso de falha de alocação
        return;
    }

    no->filhoEsquerda->pai = no->filhoDireita->pai = no;

    construir(no->filhoEsquerda, esquerda, meio);
    construir(no->filhoDireita, meio + 1, direita);

    no->valor.multiplicar(no->filhoEsquerda->valor, no->filhoDireita->valor);
}

void SegTree::atualizar(int idx, const Matriz& novoValor) {
    if (!raiz) {
        std::cerr << "Erro: A raiz da árvore não foi alocada corretamente." << std::endl;
        return;
    }
    atualizar(raiz, 0, n - 1, idx, novoValor);
}

void SegTree::atualizar(NoArvore* no, int esquerda, int direita, int idx, const Matriz& novoValor) {
    if (!no) {
        std::cerr << "Erro: Ponteiro nulo durante a operação de atualização." << std::endl;
        return;
    }

    if (esquerda == direita) {
        no->valor = novoValor;
        return;
    }

    int meio = (esquerda + direita) / 2;
    if (idx <= meio) {
        if (!no->filhoEsquerda) {
            no->filhoEsquerda = new NoArvore();
            if (!no->filhoEsquerda) {
                std::cerr << "Erro: Falha na alocação de memória para o filho esquerdo durante a atualização." << std::endl;
                // Pode ser necessário tomar medidas adicionais em caso de falha de alocação
                return;
            }
            no->filhoEsquerda->pai = no;
        }
        atualizar(no->filhoEsquerda, esquerda, meio, idx, novoValor);
    } else {
        if (!no->filhoDireita) {
            no->filhoDireita = new NoArvore();
            if (!no->filhoDireita) {
                std::cerr << "Erro: Falha na alocação de memória para o filho direito durante a atualização." << std::endl;
                // Pode ser necessário tomar medidas adicionais em caso de falha de alocação
                return;
            }
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
    if (!no) {
        std::cerr << "Erro: Ponteiro nulo durante a operação de consulta." << std::endl;
        Matriz identity;
        return identity;
    }

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
