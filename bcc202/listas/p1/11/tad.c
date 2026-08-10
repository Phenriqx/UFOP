#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tad.h"

struct funcionario {
	char nome[64];
	int matricula;
	float salario;
};

Funcionario* criarFuncionarios(int n) {
	Funcionario* f = (Funcionario*) malloc(sizeof(Funcionario) * n);
	if (!f) {
		printf("Erro ao alocar memória\n");
		return NULL;
	}
	
	return f;
}

void freeFuncionario(Funcionario **f) {
	if (*f)
		free((*f));

	(*f) = NULL;
}

void adicionaFuncionario(Funcionario *f, char *nome, int matricula, float salario, int idx) {
	strcpy(f[idx].nome, nome);
	f[idx].matricula = matricula;
	f[idx].salario = salario;
}

void imprimeUsuários(Funcionario *f, int n) {
	for (int i = 0; i < n; i++) {
		printf("Funcionário: %s - %d\n", f[i].nome, f[i].matricula);
		calculaNovoSalario(f, i);
		printf("Novo salário: %.2f\n", f[i].salario);
	}
}

void calculaNovoSalario(Funcionario *f, int i) {
	if (f[i].salario < 1000) 
		f[i].salario *= 1.15;

	else if (f[i].salario > 1000 && f[i].salario < 2000)
		f[i].salario *= 1.1;
	
	else 
		f[i].salario *= 1.05;
}
