#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size <= 2) {
        if (rank == 0) {
            fprintf(stderr, "Erro: O número de processos deve ser maior que 2.\n");
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    int mensagem_enviada = rank; // Cada processo envia seu próprio rank como mensagem
    int mensagem_recebida;

    int proximo = (rank + 1) % size;      // Calcula o próximo processo
    int anterior = (rank == 0) ? size - 1 : rank - 1; // Calcula o processo anterior no anel

    // Envio e recebimento das mensagens
    if (rank == 0) {
        // Processo 0 envia primeiro
        MPI_Send(&mensagem_enviada, 1, MPI_INT, proximo, 0, MPI_COMM_WORLD);
        MPI_Recv(&mensagem_recebida, 1, MPI_INT, anterior, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo %d recebeu: %d\n", rank, mensagem_recebida);
    } else {
        // Outros processos recebem primeiro e depois enviam
        MPI_Recv(&mensagem_recebida, 1, MPI_INT, anterior, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo %d recebeu: %d\n", rank, mensagem_recebida);
        MPI_Send(&mensagem_enviada, 1, MPI_INT, proximo, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
