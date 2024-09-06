#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>  // Para shuffle
#include <random>     // Para random_device e mt19937

using namespace std;
using namespace std::chrono;

struct Item {
    int id;
    int peso;
    int valor;
};

// Função para gerar uma solução aleatória e adicionar itens à mochila
int mochilaAleatoria(int W, vector<Item>& itens) {
    random_device rd;
    mt19937 g(rd());
    shuffle(itens.begin(), itens.end(), g);

    int pesoAtual = 0;
    int valorTotal = 0;

    // Adiciona itens aleatoriamente
    for (const auto& item : itens) {
        if (pesoAtual + item.peso <= W) {
            pesoAtual += item.peso;
            valorTotal += item.valor;
        }
    }

    return valorTotal;
}

// Função para adicionar itens à mochila na ordem de entrada
int mochilaOrdemOriginal(int W, vector<Item>& itens) {
    int pesoAtual = 0;
    int valorTotal = 0;

    // Percorre os itens na ordem original e adiciona os que couberem
    for (const auto& item : itens) {
        if (pesoAtual + item.peso <= W) {
            pesoAtual += item.peso;
            valorTotal += item.valor;
        }
    }

    return valorTotal;
}

int main() {
    int N, W;
    cin >> N >> W;

    vector<Item> itens(N);
    vector<Item> itensOrdemOriginal;

    for (int i = 0; i < N; ++i) {
        cin >> itens[i].peso >> itens[i].valor;
        itens[i].id = i + 1;
    }

    // Mantém a ordem original dos itens
    itensOrdemOriginal = itens;

    auto startAleatoria = high_resolution_clock::now();

    // Chama a função que usa uma solução aleatória
    int valorMaximoAleatoria = mochilaAleatoria(W, itens);

    auto stopAleatoria = high_resolution_clock::now();
    duration<double> durationAleatoria = stopAleatoria - startAleatoria;

    cout << "Valor máximo (aleatória): " << valorMaximoAleatoria << endl;
    cout << fixed << setprecision(6);
    cout << "Tempo de execução (aleatória): " << durationAleatoria.count() << " segundos" << endl;

    auto startOrdemOriginal = high_resolution_clock::now();

    // Chama a função que usa a ordem original
    int valorMaximoOrdemOriginal = mochilaOrdemOriginal(W, itensOrdemOriginal);

    auto stopOrdemOriginal = high_resolution_clock::now();
    duration<double> durationOrdemOriginal = stopOrdemOriginal - startOrdemOriginal;

    cout << "Valor máximo (ordem original): " << valorMaximoOrdemOriginal << endl;
    cout << "Tempo de execução (ordem original): " << durationOrdemOriginal.count() << " segundos" << endl;

    return 0;
}
