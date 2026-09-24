// BIBLIOTECAS E OUTROS PACOTES DE CODIGOS DA SUA APLICAÇÂO
//
// USE SENTINELAS NOS ARQUIVOS DE CABEÇALHO PARA QUE NÂO SEJAM INSERIDOS MAIS DE UMA VEZ 
// NA APLICAÇÃO
#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

long unsigned int fat(int n ) {
 
  long unsigned int result = 1;
  
  for (int i = 1; i <= n; i++) {
	  result = result * i;
  }

  return result;
}

#endif