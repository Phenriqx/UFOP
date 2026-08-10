#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "auxiliares.h"
#include "arvBinaria.h"


PaginaArv* inicializaArv() {
    PaginaArv *arv = malloc(sizeof(PaginaArv) * NUM_MOLDURA_ARV);
    if (!arv) {
        printf("Erro na alocação de memórias\n");
        exit(1);
    }

    for (int i = 0; i < NUM_MOLDURA_ARV; i++) { // inicializa todas as molduras
        arv[i].numPagina = -1;
        arv[i].frequencia = 0;
        arv[i].qntNos = 0;
    }
    return arv;
}

void destroiArv(PaginaArv *arv) {
    free(arv); // desaloca
}

int buscarPaginaArv(PaginaArv *arv, int numPagina) {
    for (int i = 0; i < NUM_MOLDURA_ARV; i++) {
        if (arv[i].numPagina == numPagina) //confere o numero da pagina pra ver se ja tem
            return i; // retorna o indice da moldura
    }
    return -1;//nao esta na RAM
}

int escolherVitimaArv(PaginaArv *arv, bool *vazia) {
    for (int i = 0; i < NUM_MOLDURA_ARV; i++) {
        if (arv[i].numPagina == -1) {
            *vazia = true;  // se tiver ocupado uma vazia ela avisa
            return i; // retorna o indice da casa vazia
        }
    }

    //LFU
    *vazia = false;  // se tiver ocupado
    int vitima = 0;
    for (int i = 1; i < NUM_MOLDURA_ARV; i++) {
        if (arv[i].frequencia < arv[vitima].frequencia) // retorna o indice da casa que perde na frequencia, mas varrendo todas
            vitima = i;
    }
    return vitima;
}

int carregarPaginaArv(PaginaArv *arv, FILE *arq, int numPagina, Metricas *metricas) {

    int moldura = buscarPaginaArv(arv, numPagina); // confiro se ja tenho

    if (moldura != -1) {
        arv[moldura].frequencia++; // aumento a frequencia
        return moldura; // se eu ja tiver retorno a moldura
    }

    bool vazia;
    moldura = escolherVitimaArv(arv, &vazia);

    if (vazia)
        arv[moldura].frequencia = 1; // ate preencher todas, inicializa frequencia em 1

    else {
        // como estava ocupada, salva no disco antes de substituir
         salvarPaginaArv(arv, arq, moldura, metricas); // gravar as mudandas que fez nela em memoria

        int somaFreq = 0; // so entra aqui se tiver tudo cheio
        for (int i = 0; i < NUM_MOLDURA_ARV; i++) {
            if (i != moldura)
                somaFreq += arv[i].frequencia;
        }
        arv[moldura].frequencia = somaFreq / (NUM_MOLDURA_ARV - 1); // inicializa frequencia com a media
    }

    // procura a pagina atual no disco e mando pra dentro das molduras
    long deslocamento = (long)(numPagina * sizeof(PaginaArv));
    fseek(arq, deslocamento, SEEK_SET);
    metricas->transferencias++;
    fread(&arv[moldura], sizeof(PaginaArv), 1, arq);

    arv[moldura].numPagina = numPagina;
    return moldura;
}

void salvarPaginaArv(PaginaArv *arv, FILE *arq, int posMoldura, Metricas *metricas) {
    if (arv[posMoldura].numPagina == -1)  // se a moldura estiver vazia nao tem nada pra salvar
        return;

    // calcula onde essa pagina mora no arquivos e anda
    long deslocamento = (long)(arv[posMoldura].numPagina * sizeof(PaginaArv));

    fseek(arq, deslocamento, SEEK_SET); // posiciona o pont no inicio da pagina no disco
    fwrite(&arv[posMoldura], sizeof(PaginaArv), 1, arq);  //  coloca tudo no bin
    metricas->transferencias++;//soma as transferencias
}


int criarArvBinaria(Config *config, FILE *arqOriginal, const char *arqArvBin, Metricas *metricas) {
    FILE *arq = fopen(arqArvBin, "w+b");
    if (!arq) {
        printf("Erro ao criar arquivo da árvore.\n");
        return 0;
    }

    PaginaArv *arv = inicializaArv();
    int totalPaginas = 1;

    // cria página raiz na moldura
    arv[0].numPagina = 0;
    arv[0].qntNos = 0;
    arv[0].frequencia = 1;

    // insere o primeiro registro como raiz
    Registro reg;
    fread(&reg, sizeof(Registro), 1, arqOriginal);
    metricas->transferencias++;
//
    No raiz = inicializaNo(reg);

    arv[0].nos[0] = raiz;
    arv[0].qntNos = 1;

    // insere o resto do registros
    while (fread(&reg, sizeof(Registro), 1, arqOriginal) == 1) {
        metricas->transferencias++;
        insereNo(arq, arv, reg, &totalPaginas, metricas);
    }

    // para garantir ue nao sobrou nada so na principal, nserimos tudo no bin novamente
    for (int i = 0; i < NUM_MOLDURA_ARV; i++) {
        if (arv[i].numPagina != -1)
            salvarPaginaArv(arv, arq, i, metricas);
    }

    destroiArv(arv);
    fclose(arq);
    return 1;
}

void insereNo(FILE *arq, PaginaArv *arv, Registro reg, int *totalPaginas, Metricas *metricas) {
    No novo = inicializaNo(reg);

    // anda pela árvore para achar o pai
    int pagAtual = 0, posAtual = 0;
    int pagPai = -1, posPai = -1;
    bool foiEsquerda = false;

    while (pagAtual != -1) {
        int moldura = carregarPaginaArv(arv, arq, pagAtual, metricas);
        No *noAtual = &arv[moldura].nos[posAtual];
        metricas->comparacoes++;

        pagPai = pagAtual;
        posPai = posAtual;

        if (reg.chave < noAtual->reg.chave) {
            foiEsquerda = true;
            pagAtual = noAtual->esq.pagina;
            posAtual = noAtual->esq.pos;
        } else {
            foiEsquerda = false;
            pagAtual = noAtual->dir.pagina;
            posAtual = noAtual->dir.pos;
        }
    }

    // tenta inserir na mesma página do pai
    int molduraPai = carregarPaginaArv(arv, arq, pagPai, metricas);
    PaginaArv *pagina = &arv[molduraPai];

    int pagDestino, posDestino;

    if (pagina->qntNos < ITENS_PAG_ARV) {
        // página do pai tem espaço
        posDestino = pagina->qntNos;
        pagina->nos[posDestino] = novo;
        pagina->qntNos++;
        pagDestino = pagPai;
    } else {
        // página cheia —= cria nova página
        PaginaArv novaPagina;
        novaPagina.numPagina = *totalPaginas;
        novaPagina.qntNos = 1;
        novaPagina.frequencia = 1;
        novaPagina.nos[0] = novo;
        (*totalPaginas)++;

        // escreve a nova pagina no disco
        long deslocamento = (long)(novaPagina.numPagina *sizeof(PaginaArv));
        fseek(arq, deslocamento, SEEK_SET);
        fwrite(&novaPagina, sizeof(PaginaArv), 1, arq);
        metricas->transferencias++;

        // devolve as informacoes pro api
        pagDestino = novaPagina.numPagina;
        posDestino = 0;

    }

    // atualiza ponteiro do pai, para sa
    No *noPai = &arv[molduraPai].nos[posPai];
    if (foiEsquerda) {
        noPai->esq.pagina = pagDestino;
        noPai->esq.pos = posDestino;
    } else {
        noPai->dir.pagina = pagDestino;
        noPai->dir.pos = posDestino;
    }
}

bool pesquisaArvoreBinaria(FILE *arq, PaginaArv *arv, Registro *reg, Metricas *metricas) {
    int pagAtual = 0, posAtual = 0;

    while (pagAtual != -1) {
        int moldura = carregarPaginaArv(arv, arq, pagAtual, metricas);
        No *no = &arv[moldura].nos[posAtual];
        metricas->comparacoes++;

        if (reg->chave == no->reg.chave) {
            *reg = no->reg;
            return true;
        }

        if (reg->chave < no->reg.chave) {
            pagAtual = no->esq.pagina;
            posAtual = no->esq.pos;
        } else {
            pagAtual = no->dir.pagina;
            posAtual = no->dir.pos;
        }
    }

    return false;
}

No inicializaNo(Registro reg) {
    No novo;
    novo.reg = reg;
    novo.esq.pagina = -1;
    novo.esq.pos = -1;
    novo.dir.pagina = -1;
    novo.dir.pos = -1;
    return novo;
}