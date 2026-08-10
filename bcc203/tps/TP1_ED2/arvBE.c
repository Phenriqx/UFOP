#include <stdio.h>
#include <stdlib.h>

#include "auxiliares.h"
#include "arvBE.h"

void insBE(Registro reg, TipoApontadorBE Ap, short *cresceu, Registro *regRetorno, TipoApontadorBE *ApRetorno);

void criarArvoreBE(Config* config, Metricas *metricas, TipoApontadorBE *arvoreBE, FILE* arqOriginal) {
    Registro reg;

    // inserimos na árvore até chegarmos no final do arquivo
    while (fread(&reg, sizeof(Registro), 1, arqOriginal) == 1)
        insereArvoreBE(arvoreBE, reg);
}

void inserePaginaExterna(TipoApontadorBE Ap, Registro reg) {
    short naoAchouPosicao;
    int k;
    k = Ap->pag.pagExterna.ne;
    naoAchouPosicao = k > 0;
    while (naoAchouPosicao) {
        if (reg.chave >= Ap->pag.pagExterna.re[k - 1].chave) {
            naoAchouPosicao = false;
            break;
        }
        Ap->pag.pagExterna.re[k] = Ap->pag.pagExterna.re[k - 1];
        k--;

        // se não achou nenhuma posição, o loop para e o elemento é inserido na posição r[0]
        if (k < 1)
            naoAchouPosicao = false;
    }
    // O elemento é inserido na posição correta e o tamanho da página é atualizado
    Ap->pag.pagExterna.re[k] = reg;
    Ap->pag.pagExterna.ne++;
    // aqui não manipulamos os ponteiros para as próximas páginas devido a propriedade da árvore B*, onde as páginas externas são as páginas folha
    // da árvore e, consequentemente, não possuem filhos
}

void inserePaginaInterna(TipoApontadorBE Ap, TipoApontadorBE ApDir, Chave retorno) {
    short naoAchouPosicao;
    int k;
    k = Ap->pag.pagInterna.ni;
    naoAchouPosicao = k > 0;
    while (naoAchouPosicao) {
        if (retorno >= Ap->pag.pagInterna.ri[k - 1]) {
            naoAchouPosicao = false;
            break;
        }
        Ap->pag.pagInterna.ri[k] = Ap->pag.pagInterna.ri[k - 1];
        Ap->pag.pagInterna.pi[k + 1] = Ap->pag.pagInterna.pi[k];
        k--;
        if (k < 1)
            naoAchouPosicao = false;
    }
    Ap->pag.pagInterna.ri[k] = retorno;
    Ap->pag.pagInterna.pi[k + 1] = ApDir; // diferente da página externa, aqui atualizamos os ponteiros pros filhos, uma vez que as páginas internas possuem filhos
    Ap->pag.pagInterna.ni++;
}

void insBE(Registro reg, TipoApontadorBE Ap, short *cresceu, Registro *regRetorno, TipoApontadorBE *ApRetorno) {
    long i = 0;
    long j;

    // Se a página atual que estamos é uma página interna, nós percorremos para encontrar o ponteiro correto para a próxima página
    if (Ap->tipoPag == Interna) {
        while (i < Ap->pag.pagInterna.ni && reg.chave > Ap->pag.pagInterna.ri[i])
            i++;

        Registro retFilho;
        TipoApontadorBE apRetFilho;

        // Chama a função novamente mas agora passando a página filho como Ap
        insBE(reg, Ap->pag.pagInterna.pi[i], cresceu, &retFilho, &apRetFilho);

        if (!*cresceu)
            return;
        // Se foi preciso de criar uma nova página externa, quer dizer que a árvore cresceu.
        // Como copiamos a chave o menor elemento da nova página a direita para a página interna pai, precisamos verificar se ela tem espaço ou
        // se não fazer um split interno, criando uma nova página
        else {
            // Verifica se tem espaço para inserir, se tiver apenas insere normalmente
            Chave retorno = retFilho.chave;
            if (Ap->pag.pagInterna.ni < 2 * M) {
                inserePaginaInterna(Ap, apRetFilho, retorno);
                *cresceu = false;
                return;
            }
            // caso não tenha precisamos de realizar um split da página interna
            else {
                splitInterno(Ap, ApRetorno, regRetorno, retorno, apRetFilho);
                *cresceu = true;
                return;
            }
        }
    }
    else {
        // Se a página tem espaço, apenas insere
        if (Ap->pag.pagExterna.ne < 2 * M) {
            inserePaginaExterna(Ap, reg);
            *cresceu = false;
            return;
        }

        // Se não tem espaço nós criamos uma nova página, que vai ser a página da direita.
        TipoApontadorBE temp = (TipoApontadorBE)malloc(sizeof(TipoPaginaBE));
        temp->tipoPag = Externa;
        temp->pag.pagExterna.ne = 0;

        // Nós passamos todos os elementos que estavam na página original + o que queremos inserir para esse vetor de registros temporário
        Registro buf[2 * M + 1];
        int total = 0, pos = 0;

        for (j = 0; j < 2 * M; j++) {
            buf[total] = Ap->pag.pagExterna.re[j];
            total++;
        }

        pos = total;
        // Achamos a posição que o novo registro deve estar e mudamos as posições dos elementos que vem depois para a direita
        while (pos > 0 && reg.chave < buf[pos - 1].chave) {
            buf[pos] = buf[pos - 1];
            pos--;
        }
        buf[pos] = reg; // inserimos o registro na posição correta
        total++;

        int meio = total / 2;

        // Com o meio do registro calculado, M registros vão para a página da esquerda e M + 1 registros vão para a página da direita.
        Ap->pag.pagExterna.ne = 0;
        for (j = 0; j < meio; j++)
            inserePaginaExterna(Ap, buf[j]);

        for (j = meio; j < total; j++)
            inserePaginaExterna(temp, buf[j]);

        *cresceu = true;
        *regRetorno = temp->pag.pagExterna.re[0];
        *ApRetorno = temp;
    }
}

void insereArvoreBE(TipoApontadorBE *Ap, Registro reg){
    short cresceu;
    Registro regRetorno;
    TipoApontadorBE ApRetorno;
    TipoPaginaBE* ApTemp;

    if ((*Ap) == NULL) {
        TipoPaginaBE* raizTemp = (TipoPaginaBE *) malloc(sizeof(TipoPaginaBE));
        raizTemp->tipoPag = Externa;
        raizTemp->pag.pagExterna.ne = 0;
        inserePaginaExterna(raizTemp, reg);

        *Ap = raizTemp;
        return;
    }

    insBE(reg, *Ap, &cresceu, &regRetorno, &ApRetorno);
    if (cresceu) {
        ApTemp = (TipoPaginaBE *) malloc(sizeof(TipoPaginaBE));
        ApTemp->tipoPag = Interna;
        ApTemp->pag.pagInterna.ni = 1;
        ApTemp->pag.pagInterna.ri[0] = regRetorno.chave;

        // inicializa todos os ponteiros como NULL antes
        for (int i = 0; i <= 2 * M; i++)
            ApTemp->pag.pagInterna.pi[i] = NULL;

        ApTemp->pag.pagInterna.pi[0] = *Ap;
        ApTemp->pag.pagInterna.pi[1] = ApRetorno;
        *Ap = ApTemp;
    }
}

// implementa o split interno, que é chamado quando criamos uma nova página externa mas ao copiar a chave para a página interna pai,
// ela não tenha espaço, então é necessário a divisão da página em duas, a ideia é bem semelhante a do split externo
void splitInterno(TipoApontadorBE Ap, TipoApontadorBE *ApRetorno, Registro *regRetorno, Chave retorno, TipoApontadorBE apFilhoDir) {
    long j;

    // cria um vetor de chaves que armazena as chaves que já estavam presentes + a que queremos copiar
    // cria também um vetor de ponteiros para os filhos da página atual
    Chave tempChaves[2 * M + 1];
    TipoApontadorBE tempPtrs[2 * M + 2];

    // copia as chaves e os ponteiros da página interna para os vetores temporários
    tempPtrs[0] = Ap->pag.pagInterna.pi[0];
    for (j = 0; j < 2 * M; j++) {
        tempChaves[j] = Ap->pag.pagInterna.ri[j];
        tempPtrs[j + 1] = Ap->pag.pagInterna.pi[j + 1];
    }

    // Insere retorno + apFilhoDir na posição correta do buffer
    int pos = 2 * M;
    while (pos > 0 && retorno < tempChaves[pos - 1]) { // move as chaves para a direita para que a nova chave possa ser inserida
        tempChaves[pos] = tempChaves[pos - 1];
        tempPtrs[pos + 1] = tempPtrs[pos];
        pos--;
    }
    tempChaves[pos] = retorno;
    tempPtrs[pos + 1] = apFilhoDir; // aponta para a nova página externa criada anteriormente

    // Chave do meio sobe para o pai
    int meio = M;
    regRetorno->chave = tempChaves[meio];

    // Esquerda (Ap) fica com M chaves
    Ap->pag.pagInterna.ni = 0;
    Ap->pag.pagInterna.pi[0] = tempPtrs[0];
    for (j = 0; j < meio; j++) {
        Ap->pag.pagInterna.ri[j] = tempChaves[j];
        Ap->pag.pagInterna.pi[j + 1] = tempPtrs[j + 1];
        Ap->pag.pagInterna.ni++;
    }

    // Zera apenas os ponteiros a partir de meio + 1
    for (j = meio + 1; j <= 2 * M; j++)
        Ap->pag.pagInterna.pi[j] = NULL;

    // alocamos uma nova página interna que irá ficar com as M + 1 chaves do vetor temporário
    TipoApontadorBE temp = (TipoApontadorBE)malloc(sizeof(TipoPaginaBE));
    temp->tipoPag = Interna;
    temp->pag.pagInterna.ni = 0;

    for (j = 0; j <= 2 * M; j++)
        temp->pag.pagInterna.pi[j] = NULL;

    temp->pag.pagInterna.pi[0] = tempPtrs[meio + 1];

    for (j = meio + 1; j < 2 * M + 1; j++) {
        temp->pag.pagInterna.ri[j - meio - 1] = tempChaves[j];
        temp->pag.pagInterna.pi[j - meio] = tempPtrs[j + 1];
        temp->pag.pagInterna.ni++;
    }

    *ApRetorno = temp;
}

void pesquisaArvoreBE(Registro *reg, TipoApontadorBE *Ap, bool *encontrado, Metricas *metricas) {
    if (*Ap == NULL) {
        *encontrado = false;
        return;
    }

    TipoApontadorBE Aptemp = *Ap;

    // quando estamos em uma página interna, comparamos as chaves com a chave do nosso registro para nos direcionar até uma página externa
    // a pesquisa só acaba quando chegamos em uma página externas. Chaves em páginas internas iguais às do registro que estamos procurando
    // não indicam que o registro realmente foi encontrado.
    if (Aptemp->tipoPag == Interna) {
        int i = 0;
        while (i < Aptemp->pag.pagInterna.ni && reg->chave > Aptemp->pag.pagInterna.ri[i]) {
            metricas->comparacoes++;
            i++;
        }
        // i agora aponta para o filho correto
        pesquisaArvoreBE(reg, &Aptemp->pag.pagInterna.pi[i], encontrado, metricas);
        return;
    }

    // página externa
    int i = 0;
    // percorremos a página externa procurando o registro desejado
    while (i < Aptemp->pag.pagExterna.ne) {
        metricas->comparacoes++;
        if (Aptemp->pag.pagExterna.re[i].chave == reg->chave) {
            *reg = Aptemp->pag.pagExterna.re[i];
            *encontrado = true; // registro encontrado
            return;
        }
        i++;
    }
    *encontrado = false;
}

void liberaArvoreBE(TipoApontadorBE Ap) {
    if (Ap == NULL)
        return;

    if (Ap->tipoPag == Interna) {
        for (int i = 0; i <= Ap->pag.pagInterna.ni; i++)
            liberaArvoreBE(Ap->pag.pagInterna.pi[i]);
    }

    free(Ap);
}