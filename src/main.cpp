#include <iostream>
#include "../include/segTree.hpp"
#include "../include/matriz.hpp"

int main() {
    int n, q;
    std::cin >> n >> q;

    SegTree segtree(n);

    for (int i = 0; i < q; ++i) {
        char op;
        std::cin >> op;

        if (op == 'u') {
            int a;
            std::cin >> a;
            Matriz novaMatriz;
            std::cin >> novaMatriz.conteudo[0][0] >> novaMatriz.conteudo[0][1] >> novaMatriz.conteudo[1][0] >> novaMatriz.conteudo[1][1];
            segtree.atualizar(a, novaMatriz);
        } else if (op == 'q') {
            int t0, td, x, y;
            std::cin >> t0 >> td >> x >> y;
            Matriz resultado = segtree.consultar(t0, td);
            // Imprima os 8 dígitos menos significativos das coordenadas resultadoantes
            std::cout << (resultado.conteudo[0][0] * x + resultado.conteudo[0][1] * y) % 100000000 << " "
                      << (resultado.conteudo[1][0] * x + resultado.conteudo[1][1] * y) % 100000000 << std::endl;
        }
    }

    return 0;
}
