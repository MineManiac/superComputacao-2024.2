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
int mochilaAleatoria(int W, vector<Item>& itens, vector<bool>& usado, int& pesoAtual) {
    random_device rd;
    mt19937 g(rd());
    shuffle(itens.begin(), itens.end(), g);

    int valorTotal = 0;
    pesoAtual = 0;

    // Adiciona itens aleatoriamente
    for (size_t i = 0; i < itens.size(); ++i) {
        if (pesoAtual + itens[i].peso <= W) {
            pesoAtual += itens[i].peso;
            valorTotal += itens[i].valor;
            usado[i] = true;  // Marca o item como usado
        } else {
            usado[i] = false;  // Marca o item como não usado
        }
    }

    return valorTotal;
}

// Função para tentar melhorar a solução inicial por meio de substituições
int mochilaComSubstituicao(int W, vector<Item>& itens, int valorAtual, vector<bool>& usado, int& pesoAtual) {
    bool melhorou;
    
    do {
        melhorou = false;
        
        // Tentar substituir cada item na mochila por um item fora da mochila
        for (size_t i = 0; i < itens.size(); ++i) {
            if (usado[i]) {  // Se o item está na mochila
                for (size_t j = 0; j < itens.size(); ++j) {
                    if (!usado[j] && itens[j].peso <= W - pesoAtual + itens[i].peso) {  // Tentar trocar por um item não usado
                        int novoValor = valorAtual - itens[i].valor + itens[j].valor;
                        int novoPeso = pesoAtual - itens[i].peso + itens[j].peso;
                        
                        if (novoValor > valorAtual) {  // Se a troca aumenta o valor total
                            usado[i] = false;  // Retira o item i da mochila
                            usado[j] = true;   // Adiciona o item j à mochila
                            valorAtual = novoValor;
                            pesoAtual = novoPeso;
                            melhorou = true;
                            break;  // Volta para o início para reiniciar a busca
                        }
                    }
                }
            }
            if (melhorou) break;  // Reinicia a busca desde o início se houve uma melhora
        }
    } while (melhorou);

    return valorAtual;
}

int main() {
    int N, W;
    cin >> N >> W;

    vector<Item> itens(N);
    for (int i = 0; i < N; ++i) {
        cin >> itens[i].peso >> itens[i].valor;
        itens[i].id = i + 1;
    }

    vector<bool> usado(N, false);  // Vetor para marcar quais itens estão na mochila
    int pesoAtual = 0;

    auto start = high_resolution_clock::now();

    // Gera uma solução inicial aleatória
    int valorMaximo = mochilaAleatoria(W, itens, usado, pesoAtual);

    // Tenta melhorar a solução por meio de substituições
    valorMaximo = mochilaComSubstituicao(W, itens, valorMaximo, usado, pesoAtual);

    auto stop = high_resolution_clock::now();
    duration<double> duration = stop - start;

    cout << "Valor máximo após substituições: " << valorMaximo << endl;
    cout << fixed << setprecision(6);
    cout << "Tempo de execução: " << duration.count() << " segundos" << endl;

    return 0;
}
