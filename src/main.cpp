#include <iostream>
#include "../include/segTree.hpp"
#include "../include/matriz.hpp"

#define FALHA (1)
#define SUCESSO (0)
#define MODULO (100000000)

int main() {
    int n, q;
    std::cin >> n >> q;

    SegTree segtree(4*n);

    for (int i = 0; i < q; ++i) {
        char op;
        std::cin >> op;

        switch (op) {
            case 'u': {
                int a;
                std::cin >> a;
                Matriz novaMatriz;
                std::cin >> novaMatriz.conteudo[0][0] >> novaMatriz.conteudo[0][1] >> novaMatriz.conteudo[1][0] >> novaMatriz.conteudo[1][1];
                segtree.atualizar(a, novaMatriz);
                break;
            }
            case 'q': {
                int t0, td, x, y;
                std::cin >> t0 >> td >> x >> y;
                Matriz resultado = segtree.consultar(t0, td);
                
                std::cout << (resultado.conteudo[0][0] * x + resultado.conteudo[0][1] * y) % MODULO << " "
                          << (resultado.conteudo[1][0] * x + resultado.conteudo[1][1] * y) % MODULO << std::endl;
                break;
            }
            default:
                std::cerr << "Erro: Operação desconhecida." << std::endl;
                return FALHA;
        }
    }

    return SUCESSO;
}
