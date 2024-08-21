#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Item {
    std::string nome;
    int quantidade;
};

// Função para adicionar um item ao estoque
void adicionarItem(std::vector<Item>& estoque) {
    Item novoItem;
    std::cout << "Digite o nome do item: ";
    std::cin.ignore(); // Limpa o buffer de entrada
    std::getline(std::cin, novoItem.nome);
    std::cout << "Digite a quantidade: ";
    std::cin >> novoItem.quantidade;

    // Verifica se o item já existe no estoque
    auto it = std::find_if(estoque.begin(), estoque.end(), [&](const Item& item) {
        return item.nome == novoItem.nome;
    });

    if (it != estoque.end()) {
        it->quantidade += novoItem.quantidade; // Atualiza a quantidade se o item já existir
    } else {
        estoque.push_back(novoItem); // Adiciona o item se não existir
    }

    std::cout << "Item adicionado/atualizado com sucesso!" << std::endl;
}

// Função para remover um item do estoque
void removerItem(std::vector<Item>& estoque) {
    std::string nomeItem;
    std::cout << "Digite o nome do item a ser removido: ";
    std::cin.ignore(); // Limpa o buffer de entrada
    std::getline(std::cin, nomeItem);

    auto it = std::find_if(estoque.begin(), estoque.end(), [&](const Item& item) {
        return item.nome == nomeItem;
    });

    if (it != estoque.end()) {
        estoque.erase(it); // Remove o item do estoque
        std::cout << "Item removido com sucesso!" << std::endl;
    } else {
        std::cout << "Item não encontrado no estoque." << std::endl;
    }
}

// Função para visualizar o estoque atual
void visualizarEstoque(const std::vector<Item>& estoque) {
    std::cout << "Estoque atual:" << std::endl;
    for (const auto& item : estoque) {
        std::cout << "Nome: " << item.nome << ", Quantidade: " << item.quantidade << std::endl;
    }
}

int main() {
    std::vector<Item> estoque;
    int opcao;

    do {
        std::cout << "\nControle de Estoque" << std::endl;
        std::cout << "1. Adicionar item" << std::endl;
        std::cout << "2. Remover item" << std::endl;
        std::cout << "3. Visualizar estoque" << std::endl;
        std::cout << "4. Sair" << std::endl;
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarItem(estoque);
                break;
            case 2:
                removerItem(estoque);
                break;
            case 3:
                visualizarEstoque(estoque);
                break;
            case 4:
                std::cout << "Saindo do programa." << std::endl;
                break;
            default:
                std::cout << "Opção inválida. Tente novamente." << std::endl;
                break;
        }
    } while (opcao != 4);

    return 0;
}
