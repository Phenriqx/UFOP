#include <stdio.h>

#include "filaprocessos.h"

int main(int argc, char *argv[]) {
    if (argc != 2)
        return 1;

    PilhaExecucao *pilha = criarPilha();
    //recebe 0 se deu tudo certo, e 1 se houve uma interrupção
    int execucao = executar(argv[1], pilha);

    //Se for 1 significa que ainda tinha pilhas que não foram removidas(faltou algum end)
    int destroi = destroiPilha(&pilha);

    //Se não houve interrupção no código e tinha pilhas não fechadas envia a mensagem
    if (destroi == 1 && execucao == 0)
        printf("Escopo não fechado\n");

    return 0;
}