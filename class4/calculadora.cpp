#include <iostream>

int main(){
    float a, b;
    std::string op;

    std::cout << "Digite dois números inteiros: " << std::endl;
    std::cin >> a;
    std::cin >> b;

    std::cout << "Digite uma operação" << std::endl;
    std::cout << "soma, sub, multi, divi" << std::endl;
    std::cin >> op;

    if(op == "soma"){
        std::cout << "Resultado: " << a + b << std::endl;
    } else if(op == "sub"){
        std::cout << "Resultado: " << a - b << std::endl;
    } else if(op == "multi"){
        std::cout << "Resultado: " << a * b << std::endl;
    } else if(op == "divi"){
        std::cout << "Resultado: " << a / b << std::endl;
    } else {
        std::cout << "Operação inválida" << std::endl;
    }

}