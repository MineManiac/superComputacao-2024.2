#include <omp.h>
#include <iostream>
#include <iomanip>

static long num_steps = 1024l * 1024 * 1024 * 2; // Número de passos
#define MIN_BLK 1024 * 1024 * 512 // Altere este valor para observar diferentes tempos

double sum = 0; // Variável global para somatório

void pi_r(long Nstart, long Nfinish, double step) {
    if (Nfinish - Nstart < MIN_BLK) {
        double partial_sum = 0.0;
        for (long i = Nstart; i < Nfinish; i++) {
            double x = (i + 0.5) * step;
            partial_sum += 4.0 / (1.0 + x * x);
        }
        #pragma omp atomic
        sum += partial_sum;
    } else {
        long iblk = Nfinish - Nstart;
        #pragma omp task
        pi_r(Nstart, Nfinish - iblk / 2, step);
        #pragma omp task
        pi_r(Nfinish - iblk / 2, Nfinish, step);
        #pragma omp taskwait
    }
}

int main() {
    double step = 1.0 / (double)num_steps;
    double init_time, final_time;

    for (int test = 0; test < 3; ++test) { // Executa o teste 3 vezes
        sum = 0.0; // Zera o somatório para cada execução
        init_time = omp_get_wtime();
        
        #pragma omp parallel
        {
            #pragma omp single
            pi_r(0, num_steps, step);
        }
        
        double pi = step * sum;
        final_time = omp_get_wtime() - init_time;
        std::cout << "Test " << test + 1 << ": for " << num_steps << " steps, pi = " 
                  << std::setprecision(15) << pi 
                  << " in " << final_time << " secs with MIN_BLK = " << MIN_BLK << std::endl;
    }

    return 0;
}
