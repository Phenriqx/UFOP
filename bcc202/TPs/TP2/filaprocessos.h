#ifndef _FILAPROCESSOS
#define _FILAPROCESSOS

#define CICLOS_MAX 100

typedef struct filaProcessos FilaProcessos;
typedef struct processo Processo;

FilaProcessos* criaFila(int n);
void adicionaFila(FilaProcessos* fila, int i);
void destroiFila(FilaProcessos** fila);
void escalonador(FilaProcessos* fila);
void imprimeLog(Processo p);

void insertionSort(FilaProcessos* fila);
void moveAll(FilaProcessos *fila, int n, int j);
void mergeSort(FilaProcessos *fila, int n);

#endif
