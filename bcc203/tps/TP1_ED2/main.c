#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "auxiliares.h"
#include "acessoSequencial.h"
#include "arvBinaria.h"
#include "arvB.h"
#include "arvBE.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    Config config;
    if(!validaEntrada(argc,argv, &config))
        return 1;

    // nomenclatura dos arquivos: arquivos/bin_{qnt-registros}_{situacao}
    char nomeArquivo[64];
    sprintf(nomeArquivo, "arquivos/bin_%d_situacao%d.bin", config.qnt_registros, config.situacao);

    FILE* arquivo = fopen(nomeArquivo, "rb");
    if (!arquivo) { // se o arquivo não existe, cria ele
        if(criarArquivo(nomeArquivo, config.qnt_registros, config.situacao))
            printf("A criação foi um sucesso, digite o comando novamente da pesquisa e terá o resultado\n");

        return 0;
    }

    char nomeArq[64];
    bool encontrado = false;
    Metricas metricas;
    Registro reg;
    clock_t comeco, fim;

    switch(config.metodo){
        // Acesso sequencial indexado
        case 1: {
            if (config.situacao == 3){
                printf("Esse metodo nao aceita esse tipo de ordenação.\n");
                return 0;
            }

            Metricas metricasIndice;
            inicializaMetricas(&metricasIndice);

            reg.chave = config.chave;
            int numPaginas = getNumPaginas(&config);
            int *vetorIndices = criaVetor(numPaginas);

            clock_t comecoIndice = clock();
            criarIndice(arquivo, vetorIndices, &config, &metricasIndice);
            clock_t fimIndice = clock();
            metricasIndice.tempo = (double) (fimIndice - comecoIndice) / CLOCKS_PER_SEC;
            printCriaReg(metricasIndice);

            Metricas metricasPesquisa;
            inicializaMetricas(&metricasPesquisa);

            Moldura *moldura = inicializaMoldura();

            if (config.chave != Chave_Teste) {
                reg.chave = config.chave;

                comeco = clock();
                encontrado = acessoSequencialIndexado(vetorIndices, arquivo, &reg, numPaginas, moldura, &config, &metricasPesquisa);
                fim = clock();

                metricasPesquisa.tempo = (double) (fim - comeco) / CLOCKS_PER_SEC;
                printRegistro(reg, metricasPesquisa, encontrado, nomeArquivo, config);
            }
            else{
                modoAut1(arquivo, vetorIndices, numPaginas, moldura, &config);
            }

            destroiVetor(vetorIndices);
            destroiMoldura(moldura);

            break;
        }

        // Árvore Binária de Pesquisa
        case 2:
        {
            inicializaMetricas(&metricas);

            sprintf(nomeArq, "arvBin/bin_%dreg_situacao%d.bin", config.qnt_registros, config.situacao);

            FILE *arqArv = fopen(nomeArq, "rb+");
            if (!arqArv) {
                if(criarArvBinaria(&config, arquivo, nomeArq, &metricas))
                    printf("A criação foi um sucesso, digite o comando novamente.\n");
                return 0;

            }

            PaginaArv *buffer = inicializaArv();

            if(config.chave != Chave_Teste){
                reg.chave = config.chave;

                comeco = clock();
                encontrado = pesquisaArvoreBinaria(arqArv, buffer, &reg, &metricas);
                fim = clock();

                metricas.tempo = (double)(fim - comeco) / CLOCKS_PER_SEC;
                printRegistro(reg, metricas, encontrado, nomeArquivo, config);
            }
            else{
                modoAut2(arqArv, buffer, &config);
            }

            destroiArv(buffer);
            fclose(arqArv);
            break;
        }

        // Árvore B
        case 3:
            inicializaMetricas(&metricas);

            reg.chave = config.chave;

            sprintf(nomeArq, "arvB/bin_%dreg_situacao%d.bin", config.qnt_registros, config.situacao);

            FILE *arqB = fopen(nomeArq, "rb+");
            if (!arqB) {
                if(criarArvB(&config, arquivo, nomeArq, &metricas))
                    printf("A criação foi um sucesso, digite o comando novamente.\n");

                return 0;
            }

            /* Para a pesquisa, nós precisamos achar em qual posição a raiz da árvore está para começarmos a pesquisa
            Devido a dinâmica da árvore B de poder mudar a raiz e seus e elementos, a raiz muda várias vezes de lugar no arquivo, por isso precisamos
            dessa função
            */
            TipoApontador posRaizReal;
            acharPosicaoRaiz(arqB, &posRaizReal);

            MolduraB *bufferB = inicializaMolduraB();
            if (config.chave != Chave_Teste) {
                reg.chave = config.chave;

                comeco = clock();
                // pesquisaArvoreB(&reg, &metricas, &encontrado, posRaizReal, arqB);
                pesquisaArvoreBBuffer(&reg, &metricas, &encontrado, posRaizReal, arqB, bufferB);

                fim = clock();

                metricas.tempo = (double)(fim - comeco) / CLOCKS_PER_SEC;
                printRegistro(reg, metricas, encontrado, nomeArquivo, config);
            }
            else
                modoAut3(arqB, &config, posRaizReal,bufferB);

            destroiMolduraB(bufferB);
            fclose(arqB);

            break;

        // Arvore B*
        case 4:
            inicializaMetricas(&metricas);
            reg.chave = config.chave;

            TipoApontadorBE arvoreBE = NULL;
            criarArvoreBE(&config, &metricas, &arvoreBE, arquivo);

            if (config.chave != Chave_Teste) {
                reg.chave = config.chave;

                comeco = clock();

                pesquisaArvoreBE(&reg, &arvoreBE, &encontrado, &metricas);
                fim = clock();
                metricas.tempo = (double)(fim - comeco) / CLOCKS_PER_SEC;

                printRegistro(reg, metricas, encontrado, nomeArquivo, config);
            }
            else
                modoAut4(&arvoreBE, &config);

            liberaArvoreBE(arvoreBE);
            break;
    }

    fclose(arquivo);
    return 0;
}