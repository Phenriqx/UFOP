#include <stdio.h>
#include <string.h>

typedef struct {
	char nome[50];
	int matricula;
	int idade;
} Aluno;

void ordenaPorMatricula(Aluno *vet, int n);
void ordenaPorNomeSelection(Aluno *vet, int n);
void printAlunos(Aluno *vet, int n);
void troca(Aluno *a1, Aluno *a2);

int main() {
	Aluno alunos[] = {
		{"Carlos Silva", 2023005, 21},
		{"Ana Torres", 2023001, 19},
		{"Bia Souza", 2022010, 20},
		{"Daniel Lima", 2023008, 22},
		{"Eva Ferreira", 2022002, 18},
		{"Felipe Gomes", 2023003, 21}
	};
	int num = 6;
	printf("Vetor inicial: \n");
	
	printAlunos(alunos, num);
	
	ordenaPorMatricula(alunos, num);
	printAlunos(alunos, num);
	
	ordenaPorNomeSelection(alunos, num);
	printAlunos(alunos, num);

	return 0;
}

void ordenaPorMatricula(Aluno *vet, int n) {
	int aux, j;
	for (int i = 1; i < n; i++) {
		aux = vet[i].matricula;
		j = i - 1;
		while (j >= 0 && aux < vet[j].matricula) {
			vet[j + 1].matricula = vet[j].matricula;
			j--;
		}
		vet[j + 1].matricula = aux;
	}
}

void ordenaPorNomeSelection(Aluno *vet, int n) {
	int min;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
			if (strcmp(vet[j].nome, vet[min].nome) < 0)
				min = j;
		}
		if (i != min) {
			troca(&vet[i], &vet[min]);
		}
	}
}

void printAlunos(Aluno *vet, int n) {
	for (int i = 0; i < n; i++) 
		printf("Nome: %-10s | Matricula: %d | Idade: %d\n", vet[i].nome, vet[i].matricula, vet[i].idade);
	printf("\n\n");
}

void troca(Aluno *a1, Aluno *a2) {
	Aluno aux = *a1;
	*a1 = *a2;
	*a2 = aux;
}
