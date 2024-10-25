#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Processo 0 envia mensagens exclusivas para cada processo
        for (int i = 1; i < size; i++) {
            char mensagem[50];
            snprintf(mensagem, sizeof(mensagem), "Mensagem para o processo %d", i);
            MPI_Send(mensagem, sizeof(mensagem), MPI_CHAR, i, 0, MPI_COMM_WORLD);
            printf("Processo 0 enviou: %s\n", mensagem);
        }
    } else {
        // Outros processos recebem sua mensagem do processo 0
        char mensagem[50];
        MPI_Recv(mensagem, sizeof(mensagem), MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo %d recebeu: %s\n", rank, mensagem);
    }

    MPI_Finalize();
    return 0;
}
