#include <iostream>
#include <random>
#include <omp.h>

int main() {
    const int N = 100000; // Número de pontos
    int count = 0; // Contador de pontos dentro do círculo

    // Início do temporizador
    double start_time = omp_get_wtime();

    // Paralelização com OpenMP
    #pragma omp parallel
    {
        // Cada thread tem seu próprio gerador de números aleatórios
        std::mt19937 rng(omp_get_thread_num()); // Gerador Mersenne Twister
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        int local_count = 0; // Contador local para cada thread

        // Cada thread gera N pontos
        #pragma omp for
        for (int i = 0; i < N; ++i) {
            double x = dist(rng); // Gera um número aleatório entre 0 e 1
            double y = dist(rng); // Gera outro número aleatório entre 0 e 1

            // Verifica se o ponto está dentro do círculo
            if (x * x + y * y <= 1.0) {
                local_count++;
            }
        }

        // Reduz o contador local para o contador global
        #pragma omp atomic
        count += local_count;
    }

    // Cálculo do valor de pi
    double pi = 4.0 * count / N;

    // Final do temporizador
    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;

    // Resultados
    std::cout << "Estimativa de pi: " << pi << std::endl;
    std::cout << "Tempo de execução: " << execution_time << " segundos" << std::endl;

    return 0;
}
