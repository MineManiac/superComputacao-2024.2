#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <omp.h>

int main() {
    int N = 100000; // Número de pontos aleatórios
    int sum = 0;    // Número de pontos dentro do círculo
    double pi = 0.0;
    double start_time, end_time;

    // Inicializa a semente do gerador de números aleatórios
    srand(time(0));

    start_time = omp_get_wtime();  // Marca o tempo inicial

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        double x = (double)rand() / RAND_MAX;  // Sorteia x aleatório entre 0 e 1
        double y = (double)rand() / RAND_MAX;  // Sorteia y aleatório entre 0 e 1

        // Verifica se o ponto está dentro do círculo unitário
        if (x*x + y*y <= 1.0) {
            sum += 1;  // Incrementa o número de pontos dentro do círculo
        }
    }

    // Estima o valor de Pi
    pi = 4.0 * (double)sum / (double)N;

    end_time = omp_get_wtime();  // Marca o tempo final

    // Exibe os resultados
    std::cout << "Valor estimado de Pi (paralelo): " << pi << std::endl;
    std::cout << "Tempo de execução (paralelo): " << end_time - start_time << " segundos" << std::endl;

    return 0;
}
