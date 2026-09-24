#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 1024

void to_uppercase(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main() {
    int pipe1[2], pipe2[2], pipe3[2];
    pid_t pid, pid2;
    char buffer[BUFFER_SIZE];

    // Cria os pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork(); // Cria um novo processo
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Processo filho
        close(pipe1[1]); // Fecha o lado de escrita do primeiro pipe
        close(pipe2[0]); // Fecha o lado de leitura do segundo pipe
        close(pipe3[0]); // Não utiliza o pipe3
        close(pipe3[1]);

        while (1) {
            ssize_t num_bytes = read(pipe1[0], buffer, BUFFER_SIZE); // Lê a string do pai
            if (num_bytes <= 0)
                break;
            if (strcmp(buffer, "exit") == 0) { 
                write(pipe2[1], buffer, strlen(buffer) + 1);
                break;
            }

            to_uppercase(buffer); // Converte para maiúsculas
            write(pipe2[1], buffer, strlen(buffer) + 1); // Envia a string convertida para o pai
        }

        close(pipe1[0]);
        close(pipe2[1]);
    } else { // Processo pai
        pid2 = fork();

        if (pid2 < 0) {
            perror("fork1");
            exit(EXIT_FAILURE);
        }
        if (pid2 == 0) {
            close(pipe1[0]); // Não utiliza o pipe1
            close(pipe1[1]);
            close(pipe2[1]); // Não escreve no pipe2
            close(pipe3[0]); // Não lê do pipe3

            while (1) {
                ssize_t bytes_read = read(pipe2[0], buffer, BUFFER_SIZE);
                if (bytes_read <= 0) break;

                if (strcmp(buffer, "exit") == 0) {
                    break;
                }

                // 2ª Transformação: Inversão (Ex: UFOP -> POFU)
                reverse_string(buffer);

                // Envia a string invertida de volta ao Pai via pipe3
                write(pipe3[1], buffer, strlen(buffer) + 1);
            }

            close(pipe2[0]);
            close(pipe3[1]);
            exit(EXIT_SUCCESS);

        } else {
            // Fecha as extremidades não utilizadas pelo Pai
            close(pipe1[0]); // Não lê do pipe1
            close(pipe2[0]); // Não utiliza o pipe2
            close(pipe2[1]);
            close(pipe3[1]); // Não escreve no pipe3

            while (1) {
                printf("Digite uma string (ou 'exit' para sair): ");
                fflush(stdout);

                if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
                    break;
                }

                buffer[strcspn(buffer, "\n")] = '\0';

                // Envia a string original para o Filho 1 via pipe1
                write(pipe1[1], buffer, strlen(buffer) + 1);

                if (strcmp(buffer, "exit") == 0) {
                    break;
                }

                read(pipe3[0], buffer, BUFFER_SIZE);
                printf("String final (Maiúsculas + Invertida): %s\n\n", buffer);
            }

            close(pipe1[1]);
            close(pipe3[0]);
        }
    }
    return 0;
}

