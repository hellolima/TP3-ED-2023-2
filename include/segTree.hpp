#ifndef SEG_TREE_HPP
#define SEG_TREE_HPP

#include "matriz.hpp"

/**
 * @brief Estrutura que representa um nó da árvore de segmentação.
 */
struct NoArvore {
    Matriz valor;          ///< Valor armazenado no nó.
    NoArvore* filhoEsquerda;   ///< Ponteiro para o filho à esquerda.
    NoArvore* filhoDireita;    ///< Ponteiro para o filho à direita.
    NoArvore* pai;             ///< Ponteiro para o pai.
};

/**
 * @brief Classe que representa uma árvore de segmentação para operações com matrizes.
 */
class SegTree {
private:
    int n;                 ///< Tamanho da árvore.
    NoArvore* raiz;         ///< Raiz da árvore.

    /**
     * @brief Constrói a árvore de segmentação.
     * 
     * @param no Nó atual.
     * @param esquerda Limite esquerdo.
     * @param direita Limite direito.
     */
    void construir(NoArvore* no, int esquerda, int direita);

    /**
     * @brief Atualiza o valor de um nó na árvore.
     * 
     * @param no Nó atual.
     * @param esquerda Limite esquerdo.
     * @param direita Limite direito.
     * @param idx Índice do nó a ser atualizado.
     * @param valor Novo valor a ser atribuído ao nó.
     */
    void atualizar(NoArvore* no, int esquerda, int direita, int idx, const Matriz& valor);

    /**
     * @brief Consulta o valor de um intervalo na árvore.
     * 
     * @param no Nó atual.
     * @param esquerda Limite esquerdo.
     * @param direita Limite direito.
     * @param consultarEsquerda Limite esquerdo do intervalo a ser consultado.
     * @param consultarDireita Limite direito do intervalo a ser consultado.
     * @return Valor calculado para o intervalo consultado.
     */
    Matriz consultar(NoArvore* no, int esquerda, int direita, int consultarEsquerda, int consultarDireita);

    /**
     * @brief Libera a memória alocada para a árvore de segmentação (método auxiliar).
     * 
     * @param no Nó atual.
     */
    void liberarMemoria(NoArvore* no);

public:
    /**
     * @brief Construtor da árvore de segmentação.
     * 
     * @param tamanho Tamanho da árvore.
     */
    SegTree(int tamanho);

    /**
     * @brief Destrutor da árvore de segmentação.
     */
    ~SegTree();

    /**
     * @brief Atualiza o valor de um nó na árvore.
     * 
     * @param idx Índice do nó a ser atualizado.
     * @param valor Novo valor a ser atribuído ao nó.
     */
    void atualizar(int idx, const Matriz& valor);

    /**
     * @brief Consulta o valor de um intervalo na árvore.
     * 
     * @param consultarEsquerda Limite esquerdo do intervalo a ser consultado.
     * @param consultarDireita Limite direito do intervalo a ser consultado.
     * @return Valor calculado para o intervalo consultado.
     */
    Matriz consultar(int consultarEsquerda, int consultarDireita);
};

#endif
