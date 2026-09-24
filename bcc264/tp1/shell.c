#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

void parse_command(char *cmd, char **args) {
    while (*cmd != '\0') {       // Divide o comando em argumentos
        while (*cmd == ' ' || *cmd == '\t' || *cmd == '\n') {
            *cmd++ = '\0';       // Substitui espaços por null para criar strings separadas
        }
        *args++ = cmd;           // Salva a posição do argumento
        while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t' && *cmd != '\n') {
            cmd++;               // Move para o próximo espaço
        }
    }
    *args = '\0';                // Finaliza a lista de argumentos com null
}

int main() {
    char line[MAX_LINE];         // Linha de comando
    char *args[MAX_ARGS];        // Lista de argumentos
    pid_t pid;
    int status;
    int bg; // flag pro controle de background/foreground

    while (1) {                  // Loop principal do shell
        printf("shell> ");       // Prompt do shell
        if (fgets(line, sizeof(line), stdin) == NULL) { // Lê a linha de comando
            break;               // Sai do loop se fgets falhar
        }

        if (line[0] == '\n') {
            continue;            // Ignora linhas vazias
        }

        line[strcspn(line, "\n")] = '\0'; // Remove o caractere de nova linha

        bg = 0;
        char *bg_ptr = strstr(line, "&");
        if (bg_ptr != NULL) {
            bg = 1;
            *bg_ptr = '\0';
        }
        parse_command(line, args); // Analisa a linha de comando em argumentos

        if (strcmp(args[0], "exit") == 0) {
            break;               // Sai do shell se o comando for "exit"
        }

        pid = fork();            // Cria um novo processo
        if (pid < 0) {
            fprintf(stderr, "Fork falhou\n");
            continue;
        } else if (pid == 0) {
            // Processo filho
            if (execvp(args[0], args) < 0) { // Executa o comando
                fprintf(stderr, "Erro ao executar o comando\n");
                exit(1);
            }
        } else {
            if (bg == 0)
                waitpid(pid, &status, 0);
            else
                // Processo pai
                printf("Processo rodando em background com PID: %d\n", pid);
        }
    }

    return 0;
}

