#include <iostream>

int main() {
    const int tamanho = 5; // Definindo o tamanho do vetor
    int numeros[tamanho];  // Declarando um vetor para armazenar os números
    int soma = 0;          // Variável para armazenar a soma dos números

    // Solicita ao usuário para inserir 5 números
    std::cout << "Digite 5 números:" << std::endl;

    for (int i = 0; i < tamanho; ++i) {
        std::cout << "Número " << (i + 1) << ": ";
        std::cin >> numeros[i];
        soma += numeros[i]; // Adiciona o número ao total da soma
    }

    // Exibe a soma dos números
    std::cout << "A soma dos números é: " << soma << std::endl;

    return 0;
}