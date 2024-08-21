#include <iostream>

int main(){
    int numero;

    // Solicita ao usuário para inserir um número
    std::cout << "Digite um número: ";
    std::cin >> numero;

    // Verifica se o número é par ou ímpar
    if (numero % 2 == 0) {
        std::cout << "O número " << numero << " é par." << std::endl;
    } else {
        std::cout << "O número " << numero << " é ímpar." << std::endl;
    }

    return 0;
}