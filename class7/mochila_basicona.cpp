#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip> 

using namespace std;
using namespace std::chrono;

struct Item {
    int id;
    int peso;
    int valor;
};

int mochila(int index, int W, const vector<Item>& itens) {
    if (index < 0 || W == 0) {
        return 0;
    }

    if (itens[index].peso > W) {
        return mochila(index - 1, W, itens);
    }

    int exclude = mochila(index - 1, W, itens);

    int include = itens[index].valor + mochila(index - 1, W - itens[index].peso, itens);

    return max(include, exclude);
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

    int valorMaximo = mochila(N - 1, W, itens);

    auto stop = high_resolution_clock::now();
    duration<double> duration = stop - start;

    cout << "Valor máximo: " << valorMaximo << endl;

    cout << fixed << setprecision(6);
    cout << "Tempo de execução: " << duration.count() << " segundos" << endl;

    return 0;
}
