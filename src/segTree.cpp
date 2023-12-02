#include "../include/segTree.hpp"
#include <iostream>

SegTree::SegTree(int tamanho) {
    n = 1;
    while (n < tamanho) n <<= 1;
    raiz = new NoArvore();

    if (!raiz) {  // Verifica se a alocação de memória para a raiz foi bem sucedida
        std::cerr << "Erro: Falha na alocação de memória para a raiz da árvore." << std::endl;
        return;
    }
    construir(raiz, 0, n - 1);
}

SegTree::~SegTree() {
    liberarMemoria(raiz);
}

void SegTree::liberarMemoria(NoArvore* no) {
    if (no) { // Libera recursivamente a memória alocada para os nós da árvore
        liberarMemoria(no->filhoEsquerda);
        liberarMemoria(no->filhoDireita);
        delete no;
    }
}

void SegTree::construir(NoArvore* no, int esquerda, int direita) {
    if (!no) { // Verifica se a alocação de memória para o nó foi bem sucedida
        std::cerr << "Erro: Falha na alocação de memória para um nó da árvore." << std::endl;
        return;
    }

    if (esquerda == direita) {
        // Nó folha
        no->valor = Matriz();
        no->filhoEsquerda = no->filhoDireita = nullptr;
        return;
    }

    int meio = (esquerda + direita) / 2;

    // Aloca memória para os filhos e os inicializa recursivamente
    no->filhoEsquerda = new NoArvore();
    no->filhoDireita = new NoArvore();

    if (!no->filhoEsquerda || !no->filhoDireita) { // Verifica se a alocação de memória para os filhos foi bem sucedida
        std::cerr << "Erro: Falha na alocação de memória para os filhos de um nó da árvore." << std::endl;
        return;
    }

    no->filhoEsquerda->pai = no->filhoDireita->pai = no;

    // Inicializa recursivamente os filhos
    construir(no->filhoEsquerda, esquerda, meio);
    construir(no->filhoDireita, meio + 1, direita);

    // Calcula e atribui o valor do nó atual baseado nos filhos
    no->valor.multiplicar(no->filhoEsquerda->valor, no->filhoDireita->valor);
}

void SegTree::atualizar(int idx, const Matriz& novoValor) {
    if (!raiz) { // Verifica se a raiz foi alocada corretamente
        std::cerr << "Erro: A raiz da árvore não foi alocada corretamente." << std::endl;
        return;
    }
    atualizar(raiz, 0, n - 1, idx, novoValor);
}

void SegTree::atualizar(NoArvore* no, int esquerda, int direita, int idx, const Matriz& novoValor) {
    if (!no) { // Verifica se o ponteiro é nulo durante a operação de atualização
        std::cerr << "Erro: Ponteiro nulo durante a operação de atualização." << std::endl;
        return;
    }

    if (esquerda == direita) { // Nó folha correspondente ao índice desejado
        no->valor = novoValor;
        return;
    }

    int meio = (esquerda + direita) / 2;
    // Atualiza o filho correspondente ao índice desejado
    if (idx <= meio) {
        if (!no->filhoEsquerda) {
            no->filhoEsquerda = new NoArvore();
            if (!no->filhoEsquerda) {
                std::cerr << "Erro: Falha na alocação de memória para o filho esquerdo durante a atualização." << std::endl;
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
                return;
            }
            no->filhoDireita->pai = no;
        }
        atualizar(no->filhoDireita, meio + 1, direita, idx, novoValor);
    }
    // Recalcula o valor do nó atual baseado nos filhos
    no->valor.multiplicar(no->filhoEsquerda->valor, no->filhoDireita->valor);
}

Matriz SegTree::consultar(int consultarEsquerda, int consultarDireita) {
    // Inicia a operação de consulta na raiz da árvore
    return consultar(raiz, 0, n - 1, consultarEsquerda, consultarDireita);
}

Matriz SegTree::consultar(NoArvore* no, int esquerda, int direita, int consultarEsquerda, int consultarDireita) {
    if (!no) { // Verifica se o ponteiro é nulo durante a operação de consulta
        std::cerr << "Erro: Ponteiro nulo durante a operação de consulta." << std::endl;
        Matriz identidade;
        return identidade;
    }
    
    if (esquerda > consultarDireita || direita < consultarEsquerda) { // Verifica se o intervalo está fora do alcance do nó atual
        Matriz identidade;
        return identidade;
    }

    if (esquerda >= consultarEsquerda && direita <= consultarDireita) { // Caso o intervalo do nó atual esteja completamente dentro do intervalo 
        return no->valor;
    }

    int meio = (esquerda + direita) / 2;
    Matriz resultado;
    // Combina os resultados dos filhos recursivamente
    resultado.multiplicar(consultar(no->filhoEsquerda, esquerda, meio, consultarEsquerda, consultarDireita),
                    consultar(no->filhoDireita, meio + 1, direita, consultarEsquerda, consultarDireita));
    return resultado;
}
