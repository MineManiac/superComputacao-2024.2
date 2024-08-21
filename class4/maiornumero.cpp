#include <iostream>

int main() {
    const int tamanho = 10; // Definindo o tamanho do vetor
    int numeros[tamanho];   // Declarando um vetor para armazenar os números
    int maiorNumero;        // Variável para armazenar o maior número

    // Solicita ao usuário para inserir 10 números
    std::cout << "Digite 10 números:" << std::endl;

    // Leitura dos números e inicialização do maior número
    for (int i = 0; i < tamanho; ++i) {
        std::cout << "Número " << (i + 1) << ": ";
        std::cin >> numeros[i];

        // Inicializa o maior número com o primeiro valor inserido
        if (i == 0) {
            maiorNumero = numeros[i];
        } else if (numeros[i] > maiorNumero) {
            maiorNumero = numeros[i];
        }
    }

    // Exibe o maior número
    std::cout << "O maior número é: " << maiorNumero << std::endl;

    return 0;
}