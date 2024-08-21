#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

// Função para converter uma string para minúsculas
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Função para contar palavras e encontrar a palavra mais frequente
void contarEstatisticas(const std::string& nomeArquivoEntrada, int& totalPalavras, int& totalLinhas, std::map<std::string, int>& frequenciaPalavras) {
    std::ifstream arquivo(nomeArquivoEntrada);
    std::string linha;
    totalPalavras = 0;
    totalLinhas = 0;

    if (!arquivo.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo." << std::endl;
        return;
    }

    while (std::getline(arquivo, linha)) {
        ++totalLinhas;
        std::istringstream stream(linha);
        std::string palavra;
        while (stream >> palavra) {
            ++totalPalavras;
            palavra = toLowerCase(palavra); // Normaliza a palavra para minúsculas
            frequenciaPalavras[palavra]++;
        }
    }

    arquivo.close();
}

// Função para encontrar a palavra mais frequente
std::string encontrarPalavraMaisFrequente(const std::map<std::string, int>& frequenciaPalavras) {
    int maxFrequencia = 0;
    std::string palavraMaisFrequente;
    for (const auto& entry : frequenciaPalavras) {
        if (entry.second > maxFrequencia) {
            maxFrequencia = entry.second;
            palavraMaisFrequente = entry.first;
        }
    }
    return palavraMaisFrequente;
}

int main() {
    std::string nomeArquivoEntrada;
    std::string nomeArquivoSaida;

    std::cout << "Digite o nome do arquivo de entrada: ";
    std::cin >> nomeArquivoEntrada;

    std::cout << "Digite o nome do arquivo de saída: ";
    std::cin >> nomeArquivoSaida;

    int totalPalavras, totalLinhas;
    std::map<std::string, int> frequenciaPalavras;

    // Contar estatísticas
    contarEstatisticas(nomeArquivoEntrada, totalPalavras, totalLinhas, frequenciaPalavras);

    // Calcular número médio de palavras por linha
    double mediaPalavrasPorLinha = (totalLinhas > 0) ? static_cast<double>(totalPalavras) / totalLinhas : 0;

    // Encontrar a palavra mais frequente
    std::string palavraMaisFrequente = encontrarPalavraMaisFrequente(frequenciaPalavras);

    // Criar o arquivo de saída e gravar as estatísticas
    std::ofstream arquivoSaida(nomeArquivoSaida);
    if (!arquivoSaida.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo de saída." << std::endl;
        return 1;
    }

    arquivoSaida << "Número total de palavras: " << totalPalavras << std::endl;
    arquivoSaida << "Número total de linhas: " << totalLinhas << std::endl;
    arquivoSaida << "Número médio de palavras por linha: " << mediaPalavrasPorLinha << std::endl;
    arquivoSaida << "Palavra mais frequente: " << palavraMaisFrequente << std::endl;

    arquivoSaida.close();

    std::cout << "Estatísticas gravadas no arquivo: " << nomeArquivoSaida << std::endl;

    return 0;
}
