#include <iostream>
#include <stdexcept> // Para std::out_of_range

class Vector {
public:
    // Construtor para inicializar o vetor com um tamanho específico
    Vector(int tamanho) : tam(0), capacidade(tamanho) {
        if (tamanho <= 0) {
            throw std::invalid_argument("Tamanho deve ser maior que zero.");
        }
        dados = new int[capacidade];
    }

    // Destruidor para liberar a memória alocada
    ~Vector() {
        delete[] dados;
    }

    // Inicializa o vetor com um valor específico
    void inicializa(int valor) {
        for (int i = 0; i < capacidade; ++i) {
            dados[i] = valor;
        }
        tam = capacidade; // Ajusta o tamanho do vetor
    }

    // Obtém o valor no índice especificado
    int get(int index) const {
        if (index < 0 || index >= tam) {
            throw std::out_of_range("Índice fora do intervalo.");
        }
        return dados[index];
    }

    // Define o valor no índice especificado
    void set(int index, int valor) {
        if (index < 0 || index >= tam) {
            throw std::out_of_range("Índice fora do intervalo.");
        }
        dados[index] = valor;
    }

    // Insere um valor no índice especificado
    void inserir(int index, int valor) {
        if (index < 0 || index > tam) {
            throw std::out_of_range("Índice fora do intervalo.");
        }
        if (tam == capacidade) {
            redimensiona(capacidade * 2); // Dobra a capacidade se necessário
        }
        for (int i = tam; i > index; --i) {
            dados[i] = dados[i - 1];
        }
        dados[index] = valor;
        ++tam;
    }

    // Remove o valor no índice especificado
    void remover(int index) {
        if (index < 0 || index >= tam) {
            throw std::out_of_range("Índice fora do intervalo.");
        }
        for (int i = index; i < tam - 1; ++i) {
            dados[i] = dados[i + 1];
        }
        --tam;
    }

    // Imprime todos os valores do vetor
    void imprime() const {
        for (int i = 0; i < tam; ++i) {
            std::cout << dados[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    int* dados;       // Ponteiro para a memória alocada do vetor
    int tam;          // Número atual de elementos no vetor
    int capacidade;   // Capacidade total do vetor

    // Redimensiona o vetor para uma nova capacidade
    void redimensiona(int novaCapacidade) {
        int* novoDados = new int[novaCapacidade];
        for (int i = 0; i < tam; ++i) {
            novoDados[i] = dados[i];
        }
        delete[] dados;
        dados = novoDados;
        capacidade = novaCapacidade;
    }
};

int main() {
    Vector vec(5);
    vec.inicializa(1);
    vec.imprime();

    vec.inserir(2, 10);
    vec.imprime();

    vec.remover(1);
    vec.imprime();

    return 0;
}
