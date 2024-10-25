#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int mensagem = 100; // Mensagem inicial a ser enviada
    if (rank == 0) {
        // Processo 0 inicia enviando a mensagem para o processo 1
        MPI_Send(&mensagem, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Processo %d enviou a mensagem: %d\n", rank, mensagem);
    } else {
        // Cada processo (exceto o 0) recebe a mensagem do processo anterior
        MPI_Recv(&mensagem, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo %d recebeu a mensagem: %d\n", rank, mensagem);

        // O último processo exibe a mensagem final
        if (rank < size - 1) {
            MPI_Send(&mensagem, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
