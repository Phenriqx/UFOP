#ifndef TAD_H
#define TAD_H

typedef struct funcionario Funcionario;

Funcionario* criarFuncionarios(int n);
void freeFuncionario(Funcionario** f);

void adicionaFuncionario(Funcionario* f, char* nome, int matricula, float salario, int idx);
void imprimeUsuários(Funcionario *f, int n);
void calculaNovoSalario(Funcionario* f, int i);

#endif
