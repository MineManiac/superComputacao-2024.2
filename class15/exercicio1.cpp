#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // Processo 0 envia "Olá" para o processo 1
        char mensagem_envio[] = "Olá";
        MPI_Send(mensagem_envio, strlen(mensagem_envio) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        printf("Processo %d enviou: %s\n", rank, mensagem_envio);

        // Processo 0 recebe a resposta "Oi" do processo 1
        char mensagem_recebida[10];
        MPI_Recv(mensagem_recebida, 10, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo %d recebeu: %s\n", rank, mensagem_recebida);

    } else if (rank == 1) {
        // Processo 1 recebe "Olá" do processo 0
        char mensagem_recebida[10];
        MPI_Recv(mensagem_recebida, 10, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo %d recebeu: %s\n", rank, mensagem_recebida);

        // Processo 1 envia "Oi" de volta para o processo 0
        char mensagem_envio[] = "Oi";
        MPI_Send(mensagem_envio, strlen(mensagem_envio) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        printf("Processo %d enviou: %s\n", rank, mensagem_envio);
    }

    MPI_Finalize();
    return 0;
}


