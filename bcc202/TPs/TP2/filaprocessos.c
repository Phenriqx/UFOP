#include <stdio.h>
#include <stdlib.h>

#include "filaprocessos.h"

struct processo {
    int identificador;
    float tempoChegada;
    int prioridade;
    int ciclos;
};

struct filaProcessos {
    Processo *processos; // Vetor de processos (fila de processos)
    int tam;
};

void filaRemove(FilaProcessos *fila, int pos);

// cria fila baseado na quantidade de processos
FilaProcessos* criaFila(int n) {
    FilaProcessos *fila = (FilaProcessos* ) malloc(sizeof(FilaProcessos));
    if (fila) {
        fila->tam = n;
        fila->processos = (Processo *) malloc(sizeof(Processo) * fila->tam);
        if (!fila->processos) {
            printf("Erro ao alocar processos.\n");
            free(fila);
            return NULL;
        }
    }

    return fila;
}

// libera a memória alocada pela função criaFila()
void destroiFila(FilaProcessos** fila) {
    if (!fila || !*fila)
        return;

    free((*fila)->processos);
    free(*fila);
    *fila = NULL; // evita dangling pointer
}

// remove um processo da fila para processamento
void filaRemove(FilaProcessos* fila, int pos) {
    for (int i = pos; i < fila->tam - 1 ; i++)
        fila->processos[i] = fila->processos[i + 1];

    fila->tam--;
}

void escalonador(FilaProcessos* fila) {
    int ciclos = 0;
    Processo chave;

    // chama o Merge Sort apenas na primeira iteração
    mergeSort(fila, fila->tam);

    // Enquanto ainda houver processos
    while(fila->tam > 0){
        chave = fila->processos[0];

        // executa 100 ciclos ou até os ciclos do processo acabarem
        while (ciclos < 100 && chave.ciclos > 0) {
            chave.ciclos--;
            ciclos++;
        }

        filaRemove(fila, 0);

        Processo temp = chave;
        temp.ciclos = ciclos;
        imprimeLog(temp);

        // Se o processo ainda possui ciclos, incrementa um em sua prioridade e o re-adiciona na fila e ordenamos novamente usando Insertion Sort
        if (chave.ciclos > 0) {
            chave.prioridade++;
            fila->processos[fila->tam] = chave;
            fila->tam++;
            insertionSort(fila);
        }

        ciclos = 0;
    }
}

void imprimeLog(Processo p) {
    printf("%d %d %d\n", p.identificador, p.prioridade, p.ciclos);
}

// Escaneia os valores informados e os adiciona à fila de processos
void adicionaFila(FilaProcessos* fila, int i){
    if (fila) {
        Processo process;
        scanf("%d", &process.identificador);
        scanf("%f", &process.tempoChegada);
        scanf("%d %d", &process.prioridade, &process.ciclos);

        fila->processos[i] = process;
    }
}

//Função que realiza o insertionSort.
//Irá analisar o tempoChegada apenas se very == 0. Apenas colocaremos o very = 0 na primeira ordenação
void insertionSort(FilaProcessos* fila){

    for (int i = 1; i < fila->tam; i++) {
        //Vou salvar em chave o Processo que será verificado
        Processo chave = fila->processos[i];
        //Esse for é o do insertionSort normal, vou de 0 até o índice da posição sendo analisada
        for (int j = 0; j < i; j++) {
            //Se a prioridade da chave analisada for menor que a da posição j
            if (chave.prioridade < fila->processos[j].prioridade) {
                    // salvo a chave
                    Processo salvo = chave;
                    //Chamo a função que move todos os elementos, da forma que o insertionSort comanda
                    moveAll(fila, i, j);
                    //Coloco o item salvo na posição correta
                    fila->processos[j] = salvo;
                    break;
                
            }
        }
    }
}

void mergerec(Processo* fila, int l, int r);
void merge(Processo* fila, int l, int m, int r);

// So chama o merge recursivo
void mergeSort(FilaProcessos *fila, int n) {
    mergerec(fila->processos, 0, n - 1);
}

void mergerec(Processo* fila, int l, int r) {
    if (l < r) {
        // acha o meio do vetor e o divide em dois sub vetores menores
        int m = (l + r) / 2;
        mergerec(fila, l, m);
        mergerec(fila, m + 1, r);
        merge(fila, l, m, r);
    }
}

void merge(Processo* fila, int l, int m, int r) {
    int tamL = m - l + 1; // tamanho do vetor da esquerda
    int tamR = r - m; // tamanho do vetor da direita
    Processo *fl = (Processo* ) malloc(sizeof(Processo) * tamL);
    Processo *fr = (Processo* ) malloc(sizeof(Processo) * tamR);

    for (int i = 0; i < tamL; i++)
        fl[i] = fila[l + i];
    for (int j = 0; j < tamR; j++)
        fr[j] = fila[m + 1 + j];

    int k = l;
    int i = 0;
    int j = 0;

    // enquanto tem elementos em um dos vetores
    while (i < tamL && j < tamR) {
        if (fl[i].prioridade < fr[j].prioridade || (fl[i].prioridade == fr[j].prioridade && fl[i].tempoChegada < fr[j].tempoChegada))
            fila[k++] = fl[i++];
        else
            fila[k++] = fr[j++];
    }

    // se algum vetor acabou primeiro, só copia o resto
    while (i < tamL)
        fila[k++] = fl[i++];
    while (j < tamR)
        fila[k++] = fr[j++];

    free(fl);
    free(fr);
}

//Nessa função eu movimento todos os valores do n até o j em
void moveAll(FilaProcessos *fila, int n, int j){
    for(int i = n; i >j; i--)
        fila->processos[i] = fila->processos[i - 1];
}
