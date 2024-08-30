#include <iostream>
#include <vector>

using namespace std;

// Estrutura para representar um item
struct Item {
    int id;
    int peso;
    int valor;
};

// Função recursiva 
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

    cout << "Valor máximo: " << mochila(N - 1, W, itens) << endl;

    return 0;
}


