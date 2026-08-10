#include <stdio.h>

#include "tad.h"

int main() {
	int n;
	printf("Quantos funcionários deseja inserir? ");
	scanf("%d", &n);

	Funcionario* funcionarios = criarFuncionarios(n);
	
	printf("Insira o nome, a matrícula e o salário do funcionário: \n");
	char nome[64];
	int matricula;
	float salario;

	for (int i = 0; i < n; i++) {
		scanf("%s %d %f", nome, &matricula, &salario);	

		adicionaFuncionario(funcionarios, nome, matricula, salario, i);
	}

	imprimeUsuários(funcionarios, n);

	freeFuncionario(&funcionarios);
	return 0;
}
