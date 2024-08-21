#include <iostream>
#include <string>
#include <algorithm>

bool ePalindromo(const std::string& str) {
    int esquerda = 0;
    int direita = str.length() - 1;

    while (esquerda < direita) {
        // Ignora espaços e caracteres não alfanuméricos
        while (esquerda < direita && !std::isalnum(str[esquerda])) {
            ++esquerda;
        }
        while (esquerda < direita && !std::isalnum(str[direita])) {
            --direita;
        }
        
        // Compara os caracteres (em minúsculo para ser case-insensitive)
        if (std::tolower(str[esquerda]) != std::tolower(str[direita])) {
            return false;
        }
        
        ++esquerda;
        --direita;
    }
    
    return true;
}

int main() {
    std::string entrada;

    // Solicita ao usuário para inserir uma string
    std::cout << "Digite uma string: ";
    std::getline(std::cin, entrada);

    // Verifica se a string é um palíndromo
    if (ePalindromo(entrada)) {
        std::cout << "\"" << entrada << "\" é um palíndromo." << std::endl;
    } else {
        std::cout << "\"" << entrada << "\" não é um palíndromo." << std::endl;
    }

    return 0;
}
