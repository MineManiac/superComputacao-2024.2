#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

struct Item {
    int peso;
    int valor;
};

// Função para calcular o valor total e o peso de uma solução (string binária)
pair<int, int> calcularQualidade(const vector<Item>& itens, const vector<int>& solucao) {
    int valorTotal = 0;
    int pesoTotal = 0;
    
    for (size_t i = 0; i < itens.size(); ++i) {
        if (solucao[i] == 1) {  // Se o item está incluído na mochila
            valorTotal += itens[i].valor;
            pesoTotal += itens[i].peso;
        }
    }
    
    return {valorTotal, pesoTotal};
}

// Função para gerar vizinhos, mudando um bit por vez na solução atual
vector<vector<int>> gerarVizinhos(const vector<int>& solucao) {
    vector<vector<int>> vizinhos;
    
    for (size_t i = 0; i < solucao.size(); ++i) {
        vector<int> vizinho = solucao;
        vizinho[i] = 1 - solucao[i];  // Inverte o bit na posição i
        vizinhos.push_back(vizinho);
    }
    
    return vizinhos;
}

// Função para ajustar a solução inicial para que ela respeite a capacidade
vector<int> ajustarSolucaoInicial(const vector<Item>& itens, vector<int>& solucao, int capacidade) {
    auto [valorAtual, pesoAtual] = calcularQualidade(itens, solucao);
    
    // Se o peso inicial exceder a capacidade, removemos itens até ajustar
    while (pesoAtual > capacidade) {
        for (size_t i = 0; i < itens.size(); ++i) {
            if (solucao[i] == 1) {
                solucao[i] = 0;  // Removemos o item
                pesoAtual -= itens[i].peso;
                valorAtual -= itens[i].valor;
                
                if (pesoAtual <= capacidade) {
                    break;  // Paramos quando o peso estiver ajustado
                }
            }
        }
    }
    
    return solucao;
}

// Função de Hill Climbing para resolver o problema da mochila
vector<int> hillClimbing(const vector<Item>& itens, int capacidade) {
    random_device rd;
    mt19937 g(rd());
    
    // Gera uma solução inicial aleatória
    vector<int> solucaoAtual(itens.size());
    for (size_t i = 0; i < itens.size(); ++i) {
        solucaoAtual[i] = g() % 2;
    }

    // Ajusta a solução inicial para garantir que não exceda a capacidade
    solucaoAtual = ajustarSolucaoInicial(itens, solucaoAtual, capacidade);
    auto [valorAtual, pesoAtual] = calcularQualidade(itens, solucaoAtual);
    
    bool melhorou = true;
    while (melhorou) {
        melhorou = false;
        
        // Gera os vizinhos da solução atual
        vector<vector<int>> vizinhos = gerarVizinhos(solucaoAtual);
        
        for (const auto& vizinho : vizinhos) {
            auto [valorVizinho, pesoVizinho] = calcularQualidade(itens, vizinho);
            
            // Verifica se o vizinho é melhor e respeita a capacidade
            if (pesoVizinho <= capacidade && valorVizinho > valorAtual) {
                solucaoAtual = vizinho;
                valorAtual = valorVizinho;
                pesoAtual = pesoVizinho;
                melhorou = true;
                break;  // Encontra um vizinho melhor e reinicia
            }
        }
    }
    
    return solucaoAtual;
}

int main() {
    int N, C;
    cin >> N >> C;

    vector<Item> itens(N);
    for (int i = 0; i < N; ++i) {
        cin >> itens[i].peso >> itens[i].valor;
    }

    auto start = high_resolution_clock::now();

    // Aplica o algoritmo de Hill Climbing
    vector<int> melhorSolucao = hillClimbing(itens, C);

    auto stop = high_resolution_clock::now();
    duration<double> duration = stop - start;

    // Calcula o valor e o peso da melhor solução
    auto [valorFinal, pesoFinal] = calcularQualidade(itens, melhorSolucao);

    // Exibe a solução
    cout << "Melhor solução: ";
    for (int bit : melhorSolucao) {
        cout << bit;
    }
    cout << endl;

    cout << "Valor final: " << valorFinal << endl;
    cout << "Peso final: " << pesoFinal << endl;
    cout << "Tempo de execução: " << duration.count() << " segundos" << endl;

    return 0;
}
