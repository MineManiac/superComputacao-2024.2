#include <vector>
#include <iostream>
#include <omp.h>

double conta_complexa(int i) {
    return 2 * i;
}

int main() {
    int N = 10000;
    std::vector<double> vec(N);  // Pré-alocamos o vetor com tamanho N

    double init_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        vec[i] = conta_complexa(i);  // Atribuição direta ao índice
    }

    double final_time = omp_get_wtime() - init_time;

    std::cout << "Tempo de execução com pré-alocação e atribuição direta: " << final_time << " segundos\n";

    // Apenas para verificar os valores (pode ser omitido em vetores grandes)
    for (int i = 0; i < N; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}