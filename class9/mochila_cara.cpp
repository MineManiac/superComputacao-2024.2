#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Item {
    int id;
    int peso;
    int valor;
};

// Função para ordenar os itens pela razão valor/peso em ordem decrescente
bool compara(Item a, Item b) {
    double razaoA = (double)a.valor / a.peso;
    double razaoB = (double)b.valor / b.peso;
    return razaoA > razaoB;
}

int mochilaGulosa(int W, vector<Item>& itens) {
    sort(itens.begin(), itens.end(), compara);

    int pesoAtual = 0;
    int valorTotal = 0;

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

    int valorMaximo = mochilaGulosa(W, itens);

    auto stop = high_resolution_clock::now();
    duration<double> duration = stop - start;

    cout << "Valor máximo (Gulosa): " << valorMaximo << endl;

    cout << fixed << setprecision(6);
    cout << "Tempo de execução: " << duration.count() << " segundos" << endl;

    return 0;
}

