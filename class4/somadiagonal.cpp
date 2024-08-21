#include <iostream>

int main() {
    const int tamanho = 3;
    int matriz[tamanho][tamanho]; // Declara a matriz 3x3
    int somaDiagonalPrincipal = 0;

    // Solicita ao usuário para inserir os elementos da matriz
    std::cout << "Digite os elementos da matriz 3x3:" << std::endl;
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            std::cout << "Elemento [" << i << "][" << j << "]: ";
            std::cin >> matriz[i][j];
        }
    }

    // Calcula a soma dos elementos na diagonal principal
    for (int i = 0; i < tamanho; ++i) {
        somaDiagonalPrincipal += matriz[i][i];
    }

    // Exibe a soma dos elementos na diagonal principal
    std::cout << "A soma dos elementos na diagonal principal é: " << somaDiagonalPrincipal << std::endl;

    return 0;
}
