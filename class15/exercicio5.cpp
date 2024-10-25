#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int valor = rank + 1;  // Valor exclusivo de cada processo (pode ser ajustado conforme necessário)
    int soma = 0;

    if (rank == 0) {
        // Processo 0 inicia com seu valor e envia para o próximo
        soma = valor;
        MPI_Send(&soma, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        printf("Processo %d inicia com valor %d e envia soma %d\n", rank, valor, soma);
    } else {
        // Outros processos recebem o valor acumulado do processo anterior
        MPI_Recv(&soma, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        soma += valor;
        
        // Se não for o último processo, envia a soma acumulada ao próximo
        if (rank < size - 1) {
            MPI_Send(&soma, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        } else {
            // Último processo exibe a soma total
            printf("Processo %d recebeu a soma total: %d\n", rank, soma);
        }
    }

    MPI_Finalize();
    return 0;
}
