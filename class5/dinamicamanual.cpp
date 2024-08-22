#include <iostream>
#include <chrono>

int main() {
    int N = 1000;  // Define o tamanho da matriz como N x N, onde N é 1000.

    // Alocação dinâmica de memória para uma matriz N x N.
    int** matriz = new int*[N];
    for (int i = 0; i < N; ++i) {
        matriz[i] = new int[N];
    }

    // Inicialização e soma dos elementos da matriz
    int soma = 0;
    auto start = std::chrono::high_resolution_clock::now();  // Marca o início do tempo

    // Preenchendo a matriz e calculando a soma
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matriz[i][j] = i + j;  // Exemplo de inicialização
            soma += matriz[i][j];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();  // Marca o fim do tempo
    std::chrono::duration<double> duration = end - start;
    std::cout << "Soma dos elementos: " << soma << std::endl;
    std::cout << "Tempo (alocação manual): " << duration.count() << " segundos" << std::endl;

    // Liberação da memória alocada dinamicamente
    for (int i = 0; i < N; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}
