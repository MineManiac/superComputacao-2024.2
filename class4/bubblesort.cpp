#include <iostream>

// Função para realizar a ordenação Bubble Sort
void bubbleSort(int arr[], int n) {
    bool trocou; // Flag para verificar se houve troca
    for (int i = 0; i < n - 1; ++i) {
        trocou = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Troca os elementos se estiverem na ordem errada
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                trocou = true;
            }
        }
        // Se não houve troca, o vetor já está ordenado
        if (!trocou) break;
    }
}

// Função para exibir o vetor
void exibirVetor(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    const int tamanho = 10;
    int numeros[tamanho];

    // Solicita ao usuário para inserir 10 números
    std::cout << "Digite 10 números:" << std::endl;
    for (int i = 0; i < tamanho; ++i) {
        std::cout << "Número " << (i + 1) << ": ";
        std::cin >> numeros[i];
    }

    // Ordena o vetor usando Bubble Sort
    bubbleSort(numeros, tamanho);

    // Exibe o vetor ordenado
    std::cout << "Vetor ordenado:" << std::endl;
    exibirVetor(numeros, tamanho);

    return 0;
}