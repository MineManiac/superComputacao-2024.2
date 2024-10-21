#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <cmath>    // For sqrt()

int main() {
    const long N = 100000; // Número de pontos aleatórios
    long count_inside_circle = 0;
    double x, y;

    // Inicializar a semente do gerador de números aleatórios
    srand(time(0));

    // Registrar o tempo de início
    clock_t start_time = clock();

    // Gerar N pontos aleatórios e contar quantos caem dentro do círculo
    for (long i = 0; i < N; i++) {
        // Gerar coordenadas aleatórias (x, y) no intervalo [0, 1)
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        // Verificar se o ponto está dentro do círculo de raio 1
        if (x * x + y * y <= 1.0) {
            count_inside_circle++;
        }
    }

    // Estimar o valor de pi
    double pi_estimate = 4.0 * count_inside_circle / N;

    // Calcular o tempo de execução
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    // Imprimir os resultados
    std::cout << "Estimativa de Pi: " << pi_estimate << std::endl;
    std::cout << "Tempo de execução: " << elapsed_time << " segundos" << std::endl;

    return 0;
}
