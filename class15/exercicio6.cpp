#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Processo 0 envia mensagens para cada processo e aguarda respostas
        for (int i = 1; i < size; i++) {
            char mensagem_envio[50];
            snprintf(mensagem_envio, sizeof(mensagem_envio), "Mensagem do processo 0 para o processo %d", i);

            // Envia mensagem para o processo i
            MPI_Send(mensagem_envio, sizeof(mensagem_envio), MPI_CHAR, i, 0, MPI_COMM_WORLD);
            printf("Processo 0 enviou para o processo %d: %s\n", i, mensagem_envio);

            // Recebe a resposta do processo i
            char mensagem_resposta[50];
            MPI_Recv(mensagem_resposta, sizeof(mensagem_resposta), MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Processo 0 recebeu de %d: %s\n", i, mensagem_resposta);
        }
    } else {
        // Processos i > 0 recebem mensagem do processo 0 e enviam uma resposta
        char mensagem_recebida[50];
        MPI_Recv(mensagem_recebida, sizeof(mensagem_recebida), MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo %d recebeu: %s\n", rank, mensagem_recebida);

        // Envia resposta de volta ao processo 0
        char mensagem_resposta[50];
        snprintf(mensagem_resposta, sizeof(mensagem_resposta), "Resposta do processo %d para o processo 0", rank);
        MPI_Send(mensagem_resposta, sizeof(mensagem_resposta), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
