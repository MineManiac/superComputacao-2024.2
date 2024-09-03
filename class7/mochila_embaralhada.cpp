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

// Função para embaralhar e adicionar itens à mochila de forma gulosa
int mochila(int W, vector<Item>& itens) {
    // Embaralha o vetor de itens
    random_device rd;
    mt19937 g(rd());
    shuffle(itens.begin(), itens.end(), g);

    int pesoAtual = 0;
    int valorTotal = 0;

    // Percorre os itens e adiciona aqueles que couberem na mochila
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

    for (int i = 0; i < N; ++i) {
        cin >> itens[i].peso >> itens[i].valor;
        itens[i].id = i + 1;
    }

    auto start = high_resolution_clock::now();

    int valorMaximo = mochila(W, itens);

    auto stop = high_resolution_clock::now();
    duration<double> duration = stop - start;

    cout << "Valor máximo: " << valorMaximo << endl;

    cout << fixed << setprecision(6);
    cout << "Tempo de execução: " << duration.count() << " segundos" << endl;

    return 0;
}
