#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>  // Para gerar números aleatórios

using namespace std;
using namespace std::chrono;

struct Item {
    int id;
    int peso;
    int valor;
};

// Função para simular a escolha dos itens com base em uma probabilidade
int mochilaProbabilistica(int W, const vector<Item>& itens, double limiar) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    int pesoAtual = 0;
    int valorTotal = 0;

    for (const auto& item : itens) {
        double probabilidade = dis(gen);

        // Verifica se a probabilidade é maior que o limiar e se o item cabe na mochila
        if (probabilidade > limiar && (pesoAtual + item.peso <= W)) {
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

    // Definindo o limiar de probabilidade (por exemplo, 0.5)
    double limiar = 0.5;

    auto start = high_resolution_clock::now();

    int valorMaximo = mochilaProbabilistica(W, itens, limiar);

    auto stop = high_resolution_clock::now();
    duration<double> duration = stop - start;

    cout << "Valor máximo: " << valorMaximo << endl;

    cout << fixed << setprecision(6);
    cout << "Tempo de execução: " << duration.count() << " segundos" << endl;

    return 0;
}
