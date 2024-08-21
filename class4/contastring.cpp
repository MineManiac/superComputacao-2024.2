#include <iostream>
#include <string>

int main() {
    // Declara uma variável para armazenar a string do usuário
    std::string inputString;

    // Solicita ao usuário para inserir uma string
    std::cout << "Digite uma string: ";
    std::getline(std::cin, inputString);

    // Obtém o comprimento da string
    std::size_t length = inputString.length();

    // Exibe o número de caracteres na string
    std::cout << "A string \"" << inputString << "\" tem " << length << " caracteres." << std::endl;

    return 0;
}