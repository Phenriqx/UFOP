#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "auxiliares.h"
#include "acessoSequencial.h"
#include "arvBinaria.h"
#include "arvB.h"
#include "arvBE.h"

bool validaEntrada(int argc, char *argv[],Config *config){
    if (argc < 5 || argc > 6) {
        printf("O formato é inválido.\nSiga esse formato: ./exe <método> <quantidade> <situação> <chave> [-P]\n");
        return false;
    }

    config->metodo = atoi(argv[1]);
    if (config->metodo < 1 || config->metodo > 4) { // verifica se o valor recebido é válido
        printf("Método deve ter os valores entre 1 e 4\n");
        return false;
    }

    config->qnt_registros = atoi(argv[2]);
    bool aux;
    for(int i = 100; i <= 1000000; i = i * 10){
        if(config->qnt_registros == i){
            aux = true;
            break;
        }
        aux = false;
    }

    if(!aux){
        printf("A quantidade de registros deve ser exatamente: 100, 1000, 10000, 100000 ou 1000000.\n");
        return false;
    }

    config->situacao = atoi(argv[3]);
    if (config->situacao < 1 || config->situacao > 3) { // verifica se o valor recebido é válido
        printf("Situação deve ter os valores entre 1 e 3\n");
        return false;
    }

    config->chave = atoi(argv[4]);

    if (argc == 6){
        if (strcmp(argv[5], "-P") == 0) {
            config->p = 1;
        } else {
            printf("O sexto argumento deve ser '-P' ou vazio \n");
            return false;
        }
    } else {
        config->p = 0;
    }

    return true;
}

int criarArquivo(const char* caminho, int qnt_registros, int situacao) {
    FILE *arquivo = fopen(caminho, "w+b");
    if (!arquivo) {
        printf("Erro ao abrir/criar arquivo.\n");
        return 0;
    }

    Registro reg;
    switch (situacao) {
        // ordenação ascendente das chaves
        case 1:
            for (int chave = 1; chave <= qnt_registros; chave++) {
                reg.chave = chave;
                reg.dado1 = (rand() % qnt_registros) + 1;
                preencherDados(&reg);
                fwrite(&reg, sizeof(Registro), 1, arquivo);
            }
            break;
        // ordenação descendente das chaves
        case 2:
            for (int chave = qnt_registros; chave >= 1; chave--) {
                reg.chave = chave;
                reg.dado1 = (rand() % qnt_registros) + 1;
                preencherDados(&reg);
                fwrite(&reg, sizeof(Registro), 1, arquivo);

            }
            break;
        // ordenação aleatória
        case 3:
            criarArquivoAleatorio(arquivo, qnt_registros);
            break;
    }

    fclose(arquivo);
    return 1;
}

void preencherDados(Registro *reg) {
    // a funcão memset() preenche os primeiros n bytes de um bloco com algum valor
    // preenche os primeiros 999 bytes com A e depois o último como \0

    snprintf(reg->dado2, sizeof(reg->dado2), "chave:%d|", reg->chave);
    int prefixo = strlen(reg->dado2);
    memset(reg->dado2 + prefixo, 'A', sizeof(reg->dado2) - prefixo - 1);
    reg->dado2[sizeof(reg->dado2) - 1] = '\0';

    snprintf(reg->dado3, sizeof(reg->dado3), "chave:%d|", reg->chave);
    prefixo = strlen(reg->dado3);
    memset(reg->dado3 + prefixo, 'B', sizeof(reg->dado3) - prefixo - 1);
    reg->dado3[sizeof(reg->dado3) - 1] = '\0';
}

void printRegistro(Registro reg, Metricas metricas, bool encontrado, const char* nomeArquivo, Config config) {
    if (!encontrado)
        printf("Registro não encontrado no arquivo %s\n", nomeArquivo);
    else {
        printf("Registro encontrado.\n");
        if (config.p)
            printf("  Chave: %d\n  Dado1: %ld\n  Dado2: %s\n  Dado3: %s\n", reg.chave, reg.dado1, reg.dado2, reg.dado3);

        printf("\n\t\tMétricas \n");
        printf("  Comparações    : %6d \n", metricas.comparacoes);
        printf("  Transferências : %6d \n", metricas.transferencias);
        printf("  Tempo Total    : %.6lf s\n\n", metricas.tempo);
    }
}

void printCriaReg(Metricas metricas) {
    printf("\n\t\tMétricas da Criação do Índice (Acesso Sequencial):\n");
    printf("  Comparações    : %6d \n", metricas.comparacoes);
    printf("  Transferências : %6d \n", metricas.transferencias);
    printf("  Tempo Total    : %.6lf s\n\n", metricas.tempo);
}

int* criaVetor(int tamanho) {
    int *vetor = (int *) malloc(sizeof(int) * tamanho);
    if (!vetor) {
        printf("Erro ao alocar memória para o vetor.\n");
        exit(1);
    }
    return vetor;
}

void destroiVetor(int *vet){
    free(vet);
}

void inicializaMetricas(Metricas *metricas){
    metricas->transferencias = 0;
    metricas->comparacoes = 0;
    metricas->tempo = 0.0;
}

void criarArquivoAleatorio(FILE* arquivo, int qnt_registros) {
    int *v = malloc(qnt_registros * sizeof(int));
    for (int i = 0; i < qnt_registros; i++)
        v[i] = i + 1;

    for (int i = qnt_registros - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }

    Registro reg;
    for (int i = 0; i < qnt_registros; i++) {
        reg.chave = v[i];
        reg.dado1 = (rand() % qnt_registros) + 1;
        preencherDados(&reg);
        fwrite(&reg, sizeof(Registro), 1, arquivo);
    }

    free(v);
}

void modoAut1(FILE *arquivo, int *vetorIndices, int numPaginas,Moldura *moldura, Config *config) {
    // 10 buscas aleatorias e calcula medias
    printf("\n\t\tBuscas Aleatoria Sequencial Indexado\n");
    bool encontrado;
    double totalTransf = 0.0, totalComp = 0.0, totalTempo = 0.0;
    clock_t comeco, fim;

    for (int i = 0; i < 10; i++)
    {
        Metricas m;
        inicializaMetricas(&m);

        Registro reg;
        reg.chave = (rand() % config->qnt_registros) + 1;

        comeco = clock();
        encontrado = acessoSequencialIndexado(vetorIndices, arquivo, &reg, numPaginas, moldura, config, &m);
        fim = clock();

        double tempo = (double)(fim - comeco) / CLOCKS_PER_SEC;

        if(encontrado) {
            printf("Busca %2d (Chave %6d) -> Transf: %2d | Comp: %3d | Tempo: %.6lf s\n",
                    i + 1, reg.chave,m.transferencias,m.comparacoes,tempo);;
        }
        else{
            i--;
            continue;
        }

        totalTransf += m.transferencias;
        totalComp += m.comparacoes;
        totalTempo += tempo;
    }


    printf("\n\t\tMEDIAS\n");
    printf("  Transferências : %6.2lf \n", totalTransf / 10);
    printf("  Comparações    : %6.2lf \n", totalComp / 10);
    printf("  Tempo          : %.6lf s\n\n", totalTempo / 10.0);
}

void modoAut2(FILE *arqArv, PaginaArv *buffer, Config *config){
    // 10 buscas aleatorias e calcula medias
    printf("\n\t\tBuscas Aleatoria Arvore Binaria\n");
    bool encontrado;
    double totalTransf = 0.0, totalComp = 0.0, totalTempo = 0.0;
    clock_t comeco, fim;


    for (int i = 0; i < 10; i++) {
        Metricas m;
        inicializaMetricas(&m);
        Registro reg;
        reg.chave = (rand() % config->qnt_registros) + 1;

        comeco = clock();
        encontrado = pesquisaArvoreBinaria(arqArv, buffer, &reg, &m);
        fim = clock();

        double tempo = (double)(fim - comeco) / CLOCKS_PER_SEC;

        if(encontrado) {
            printf("Busca %2d (Chave %6d) -> Transf: %2d | Comp: %3d | Tempo: %.6lf s\n",
                    i + 1, reg.chave,m.transferencias,m.comparacoes,tempo);
        }
        else {
            i--;
            continue;
        }

        totalTransf += m.transferencias;
        totalComp += m.comparacoes;
        totalTempo += tempo;
    }

    printf("\n\t\tMEDIAS\n");
    printf("  Transferências : %6.2lf \n", totalTransf / 10);
    printf("  Comparações    : %6.2lf \n", totalComp / 10);
    printf("  Tempo          : %.6lf s\n\n", totalTempo / 10.0);
}

void modoAut3(FILE *arq, Config *config, TipoApontador posRaizReal,MolduraB *buffer){
    // 10 buscas aleatorias e calcula medias
    printf("\n\t\tBuscas Aleatoria Arvore B\n");
    bool encontrado;
    double totalTransf = 0.0, totalComp = 0.0, totalTempo = 0.0;
    clock_t comeco, fim;


    for (int i = 0; i < 10; i++) {
        Metricas m;
        inicializaMetricas(&m);
        Registro reg;
        reg.chave = (rand() % config->qnt_registros) + 1;

        comeco = clock();
        // pesquisaArvoreB(&reg, &m, &encontrado, posRaizReal, arq);
        pesquisaArvoreBBuffer(&reg, &m, &encontrado, posRaizReal, arq, buffer);
        fim = clock();

        double tempo = (double)(fim - comeco) / CLOCKS_PER_SEC;

        if (encontrado) {
            printf("Busca %2d (Chave %6d) -> Transf: %2d | Comp: %3d | Tempo: %.6lf s\n",
                    i + 1, reg.chave,m.transferencias,m.comparacoes,tempo);
        }
        else {
            i--;
            continue;
        }

        totalTransf += m.transferencias;
        totalComp += m.comparacoes;
        totalTempo += tempo;
    }

    printf("\n\t\tMEDIAS\n");
    printf("  Transferências : %6.2lf \n", totalTransf / 10);
    printf("  Comparações    : %6.2lf \n", totalComp / 10);
    printf("  Tempo          : %.6lf s\n\n", totalTempo / 10.0);
}

void modoAut4(TipoApontadorBE* Ap,  Config *config) {
    // 10 buscas aleatorias e calcula medias
    printf("\n\t\tBuscas Aleatoria Arvore B*\n");
    bool encontrado;
    double totalTransf = 0.0, totalComp = 0.0, totalTempo = 0.0;
    clock_t comeco, fim;

    for (int i = 0; i < 10; i++) {
        Metricas m;
        inicializaMetricas(&m);
        Registro reg;
        reg.chave = (rand() % config->qnt_registros) + 1;

        comeco = clock();
        pesquisaArvoreBE(&reg, Ap, &encontrado, &m);
        fim = clock();

        double tempo = (double)(fim - comeco) / CLOCKS_PER_SEC;

        if (encontrado) {
            printf("Busca %2d (Chave %6d) -> Transf: %2d | Comp: %3d | Tempo: %.6lf s\n",
                    i + 1, reg.chave,m.transferencias,m.comparacoes,tempo);
        }
        else {
            i--;
            continue;
        }

        totalTransf += m.transferencias;
        totalComp += m.comparacoes;
        totalTempo += tempo;
    }

    printf("\n\t\tMEDIAS\n");
    printf("  Transferências : %6.2lf \n", totalTransf / 10);
    printf("  Comparações    : %6.2lf \n", totalComp / 10);
    printf("  Tempo          : %.6lf s\n\n", totalTempo / 10.0);
}