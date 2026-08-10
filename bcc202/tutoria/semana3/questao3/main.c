// Pedro Henrique Menezes

#include <stdio.h>

#define TAM_MAX 10

typedef struct {
	int chave;
} Registro;

typedef struct {
	Registro registro[TAM_MAX];
	int primeiro, ultimo;
} Lista;

void listaCria(Lista *lista);
int listaEhVazia(Lista *lista);
int listaTamanho(Lista *lista);
int listaInsere(Lista *lista, Registro r);
int listaRetira(Lista *lista, int pos, Registro *r);

int main() {
	Lista l;
	listaCria(&l);
	
	int vazio = listaEhVazia(&l);
	if (vazio)
		printf("lista é vazia\n");
	else 
		printf("lista nao é vazia\n");

	int tam = listaTamanho(&l);
	printf("lista tamanho: %d\n", tam);
	
	for (int i = 0; i < 5; i++) {
		Registro r;
		r.chave = i;
		int insere = listaInsere(&l, r);
		if (!insere)
			printf("nao foi possivel inserir o elemento %d\n", i);
	}

	tam = listaTamanho(&l);
	printf("lista tamanho: %d\n", tam);

	for (int i = 0; i < 5; i++) {
		Registro r;
		r.chave = i;
		int removed = listaRetira(&l, 0, &r);
		if (!removed)
			printf("nao foi possivel remover o elemento %d\n", i);
	}

	tam = listaTamanho(&l);
	printf("lista tamanho: %d\n", tam);

	return 0;
}

void listaCria(Lista *lista) {
	lista->primeiro = 0;
	lista->ultimo = lista->primeiro;
}

int listaEhVazia(Lista *lista) {
	return (lista->primeiro == lista->ultimo);
}

int listaTamanho(Lista *lista) {
	int count = 0;
	for (int i = lista->primeiro; i < lista->ultimo; i++)
		count++;

	return count;
}

int listaInsere(Lista* lista, Registro r) {
	if (lista->ultimo == TAM_MAX)
		return 0;

	lista->registro[lista->ultimo] = r;
	lista->ultimo++;
	return 1;
}

int listaRetira(Lista* lista, int pos, Registro *r) {
	if (listaEhVazia(lista) || pos >= lista->ultimo)
		return 0;

	*r = lista->registro[pos];
	for (int i = pos; i < lista->ultimo - 1; i++)
		lista->registro[i] = lista->registro[i + 1];

	lista->ultimo--;
	return 1;
}
