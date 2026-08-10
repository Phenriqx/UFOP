#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "auxiliares.h"
#include "arvB.h"



// Função responsável por criar o arquivo da árvore B
int criarArvB(Config* config, FILE* arqOriginal, const char *arqArvB, Metricas *metricas) {
    FILE *arq = fopen(arqArvB, "w+b");
    if (!arq) {
        printf("Erro ao criar arquivo da árvore.\n");
        return 0;
    }

    /* Para a pesquisa, nós precisamos achar em qual posição a raiz da árvore está para começarmos a pesquisa
    Devido a dinâmica da árvore B de poder mudar a raiz e seus e elementos, a raiz muda várias vezes de lugar no arquivo.
    Para resolver esse problema, nas primeiras sizeof(TipoApontador) posições, colocamos um valor lixo/qualquer somente para preencher o espaço
    do que vai ser o endereço da raiz, aqui usamos o -1.
    */

    TipoApontador posRaizFalso = -1;
    fwrite(&posRaizFalso, sizeof(TipoApontador), 1, arq);

    // Cria a primeira página (raiz inicial)
    TipoPagina* raiz = criaPagina();
    raiz->n = 0;

    for(int k = 0; k <= 2 * M; k++) {
        raiz->p[k] = -1; // Mata o lixo de memória dos ponteiros
    }
    /* Como o ftell vai ler após o cabeçalho, a primeira página será criada no byte 8. Todos os bytes antes contém o valor -1 que colocamos acima para
    representar a raiz
    */

    fseek(arq, 0, SEEK_END);
    TipoApontador posAtual = ftell(arq);
    escreverNo(arq, posAtual, raiz, metricas);

    free(raiz);

    Registro reg;
    /* Agora insere o restante dos registros do arquivo original */
    metricas->transferencias++;
    while (fread(&reg, sizeof(Registro), 1, arqOriginal) == 1) {
        insere(reg, arq, &posAtual, metricas);
        metricas->transferencias++;
    }

    // Antes de fechar o arquivo, volta no byte 0 e grava onde a raiz terminou
    fseek(arq, 0, SEEK_SET);
    fwrite(&posAtual, sizeof(TipoApontador), 1, arq);

    fclose(arq);
    return 1;
}

// Insere um registro numa página já existente
void insereNaPagina(TipoPagina* Ap, Registro reg, TipoApontador ApDir, Metricas *metricas) {
    short naoAchouPosicao;
    int k;
    k = Ap->n; // índice do último elemento da pág
    naoAchouPosicao = k > 0;

    while (naoAchouPosicao) { // se a página não estiver vazia ou se a posição desejada não foi encontrada
        metricas->comparacoes++;
        if (reg.chave >= Ap->r[k - 1].chave) { // se a chave atual for menor ou igual, achamos a posição desejada
            naoAchouPosicao = false;
            break;
        }
        Ap->r[k] = Ap->r[k - 1];
        Ap->p[k + 1] = Ap->p[k]; // o p[k] agora guarda longs, que são onde a posição está no arquivo.
        k--;

        // se não achou nenhuma posição, o loop para e o elemento é inserido na posição r[0]
        if (k < 1)
            naoAchouPosicao = false;
    }
    // adiciona o registro na posição correta, atualiza seu ponteiro para a página filha a direita e
    // incrementa o número de elementos na página
    Ap->r[k] = reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;

    // Aqui ainda não salva no arquivo, temos que chamar o fwrite na função que chama essa.
}

void insNoDisco(FILE* arq, Registro reg, TipoApontador posAtual, short *cresceu, Registro *regRetorno, TipoApontador* posRetorno, Metricas *metricas) {
    // se chegou em uma página nula, sinaliza que a árvore cresceu e passa o elemento para cima com filho a direita nulo.
    if (posAtual == -1) {
        *cresceu = true;
        (*regRetorno) = reg;
        *posRetorno = -1;
        return;
    }

    long i = 0;
    long j;
    TipoPagina pagAtual;
    lerNo(arq, posAtual, &pagAtual, metricas);

    // busca a posição que a chave deve estar
    while (i < pagAtual.n) {
        metricas->comparacoes++;
        if (reg.chave > pagAtual.r[i].chave) {
            i++;
        } else {
            break;
        }
    }

    if (i < pagAtual.n) {
        metricas->comparacoes++;
        if (reg.chave == pagAtual.r[i].chave) {
            printf("Registro já está presente!\n");
            *cresceu = false;
            return;
        }
    }

    TipoApontador posRetornoFilho;
    insNoDisco(arq, reg, pagAtual.p[i], cresceu, regRetorno, &posRetornoFilho, metricas);
    if (!*cresceu)
        return;

    // Se a página tem espaço, apenas insere
    if (pagAtual.n < 2 * M) {
        insereNaPagina(&pagAtual, *regRetorno, posRetornoFilho, metricas);
        escreverNo(arq, posAtual, &pagAtual, metricas);
        *cresceu = false;
        return;
    }

    // como a página está cheia, criamos uma nova página que será a página da direita após a divisão
    TipoPagina temp;
    temp.n = 0;

    // tratar problema com lixo 
    for(int k = 0; k <= 2 * M; k++) {
        temp.p[k] = -1; 
    }

    fseek(arq, 0, SEEK_END);
    TipoApontador posTemp = ftell(arq);

    // Se o elemento novo deve ir para a página da direita (temp)
    if (i >= M + 1) {
        // Move os elementos da metade superior para a nova página
        for (j = M + 1; j < 2 * M; j++)
            insereNaPagina(&temp, pagAtual.r[j], pagAtual.p[j + 1], metricas);

        pagAtual.n = M + 1;
        insereNaPagina(&temp, *regRetorno, posRetornoFilho, metricas); // Insere o novo elemento na direita
    }

    // Se o elemento novo deve ir para a página da esquerda (Ap)
    else {
        // Move os elementos da metade superior para a nova página
        for (j = M; j < 2 * M; j++)
            insereNaPagina(&temp, pagAtual.r[j], pagAtual.p[j + 1], metricas);

        pagAtual.n = M;
        insereNaPagina(&pagAtual, *regRetorno, posRetornoFilho, metricas); // Insere o novo elemento na esquerda
    }

    // O elemento do meio (indíce M) sobe para o pai
    pagAtual.n = M;
    temp.p[0] = pagAtual.p[M + 1];
    *regRetorno = pagAtual.r[M];
    *posRetorno = posTemp;

    // Escreve as páginas no arquivo
    escreverNo(arq, posAtual, &pagAtual, metricas);
    escreverNo(arq, posTemp, &temp, metricas);
}

void insere(Registro reg, FILE* arqB, TipoApontador* posRaiz, Metricas *metricas) {
    short cresceu;
    Registro regRetorno;
    TipoApontador posRetorno;

    insNoDisco(arqB, reg, *posRaiz, &cresceu, &regRetorno, &posRetorno, metricas);
    if (cresceu) {
        TipoPagina nova;
        nova.n = 1;
        nova.r[0] = regRetorno;
        nova.p[1] = posRetorno;
        nova.p[0] = *posRaiz;

        // limpar ponteiros por problema de lixo, mesmo o n diminuindo  
        for(int k = 2; k <= 2 * M; k++) {
            nova.p[k] = -1;
        }

        fseek(arqB, 0, SEEK_END);
        long novaPosRaiz = ftell(arqB);

        escreverNo(arqB, novaPosRaiz, &nova, metricas);
        *posRaiz = novaPosRaiz;
    }
}

void pesquisaArvoreB(Registro *reg, Metricas *metricas, bool *encontrado, TipoApontador pos, FILE* arq) {
    if (pos == -1) {
        *encontrado = false;
        return;
    }

    long i = 0;
    TipoPagina pagAtual;
    // Lemos um nó do disco para a RAM
    lerNo(arq, pos, &pagAtual, metricas);

    while (i < pagAtual.n && reg->chave > pagAtual.r[i].chave) {
        metricas->comparacoes++;
        i++;
    }

    if (i < pagAtual.n) {
        metricas->comparacoes++;
        if (reg->chave == pagAtual.r[i].chave) {
            *reg = pagAtual.r[i];
            *encontrado = true;
            return;
        }
    }

    // se não achou, chama a função novamente passando a posição da página filha
    pesquisaArvoreB(reg, metricas, encontrado, pagAtual.p[i], arq);
}

TipoPagina* criaPagina() {
    TipoPagina* Ap = (TipoPagina* ) malloc(sizeof(TipoPagina));
    if (!Ap) {
        printf("Não foi possível criar a página\n");
        exit(1);
    }

    return Ap;
}

void lerNo(FILE* arqB, TipoApontador pos, TipoPagina *ap, Metricas *metricas) {
    if (pos == -1)
        return;
    fseek(arqB, pos, SEEK_SET);
    metricas->transferencias++;
    fread(ap, sizeof(TipoPagina), 1, arqB);
}

void escreverNo(FILE* arqB, TipoApontador pos, TipoPagina *ap, Metricas *metricas) {
    fseek(arqB, pos, SEEK_SET);
    fwrite(ap, sizeof(TipoPagina), 1, arqB);
}

TipoApontador criarNo(FILE *arq, TipoPagina *no, Metricas *metricas) {
    fseek(arq, 0, SEEK_END);
    long posNo = ftell(arq);

    escreverNo(arq, posNo, no, metricas);

    return posNo;
}

void acharPosicaoRaiz(FILE *arq, TipoApontador* posReal) {
    fseek(arq, 0, SEEK_SET);
    fread(posReal, sizeof(TipoApontador), 1, arq);
}

//---------------se der errado, tentativa de buffer
MolduraB* inicializaMolduraB() {
    MolduraB *buffer = malloc(sizeof(MolduraB) * NUM_MOLDURA_B);
    for (int i = 0; i < NUM_MOLDURA_B; i++) {
        buffer[i].enderecoDisco = -1;
        buffer[i].frequencia = 0;
    }
    return buffer; // inicializacao do Buffer
}

void destroiMolduraB(MolduraB *buffer) {
    free(buffer);
}

int buscarMolduraB(MolduraB *buffer, TipoApontador endereco) {
    for (int i = 0; i < NUM_MOLDURA_B; i++) {
        if (buffer[i].enderecoDisco == endereco)
            return i; // retorna o inidice do buffer a qual esta aquele enderecp
    }
    return -1; // s enao achar retorna -1
}

int escolherVitimaB(MolduraB *buffer, bool *vazia) {
    for (int i = 0; i < NUM_MOLDURA_B; i++) {
        if (buffer[i].enderecoDisco == -1) {
            *vazia = true;  // confere se o endereco e vazio 
            return i; 
        }
    }
    *vazia = false; 
    int vitima = 0;
    for (int i = 1; i < NUM_MOLDURA_B; i++) {
        if (buffer[i].frequencia < buffer[vitima].frequencia)
            vitima = i;
    }
    return vitima; // escolhe a vitima pra ser retirado
}

int carregarPaginaB(MolduraB *buffer, FILE *arq, TipoApontador endereco, Metricas *metricas) {
    int moldura = buscarMolduraB(buffer, endereco);

    if (moldura != -1) {
        buffer[moldura].frequencia++; 
        return moldura; // se achou na moldura tudo resolvido
    }

    bool vazia;
    moldura = escolherVitimaB(buffer, &vazia);

    if (vazia) {
        buffer[moldura].frequencia = 1; 
    } else {   
        int somaFreq = 0; 
        for (int i = 0; i < NUM_MOLDURA_B; i++) {
            if (i != moldura) somaFreq += buffer[i].frequencia;
        }
        buffer[moldura].frequencia = somaFreq / (NUM_MOLDURA_B - 1);  // faz a inserecao da media da frequenci a
    }

    fseek(arq, endereco, SEEK_SET);
    metricas->transferencias++; 
    fread(&buffer[moldura].pagina, sizeof(TipoPagina), 1, arq); // le uma nova pagina 

    buffer[moldura].enderecoDisco = endereco;
    return moldura;
}
  

void pesquisaArvoreBBuffer(Registro *reg, Metricas *metricas, bool *encontrado, TipoApontador pos, FILE* arq, MolduraB *buffer) {
    if (pos == -1) {
        *encontrado = false;
        return;
    }

    long i = 0;
    
    int idx = carregarPaginaB(buffer, arq, pos, metricas);
    TipoPagina *pagAtual = &buffer[idx].pagina; // o ponteiro da pagina carregada

    while (i < pagAtual->n && reg->chave > pagAtual->r[i].chave) {
        metricas->comparacoes++;
        i++;
    }

    if (i < pagAtual->n) {
        metricas->comparacoes++;
        if (reg->chave == pagAtual->r[i].chave) {
            *reg = pagAtual->r[i];
            *encontrado = true;
            return;
        }
    }

    // Passando o buffer na recursão
    pesquisaArvoreBBuffer(reg, metricas, encontrado, pagAtual->p[i], arq, buffer);
}