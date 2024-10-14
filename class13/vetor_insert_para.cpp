#include <vector>
#include <iostream>
#include <omp.h>

double conta_complexa(int i) {
    return 2 * i;
}

int main() {
    int N = 10000; 
    std::vector<double> vec;
    vec.reserve(N);  // Reservamos espaço para evitar realocações e melhorar a performance

    double init_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        double value = conta_complexa(i);
        
        #pragma omp critical
        vec.push_back(value);  // Seção crítica para evitar acessos simultâneos
    }

    double final_time = omp_get_wtime() - init_time;

    std::cout << "Tempo de execução com #pragma omp critical: " << final_time << " segundos\n";

    // Apenas para ilustrar o preenchimento, não recomendado para vetores grandes
    for (int i = 0; i < N; i++) {
        std::cout << vec[i] << " ";
    }

    return 0;
}
