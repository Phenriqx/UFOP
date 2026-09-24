
// IMPLEMENTAÇÃO DE UMA BIBLIOTECA OU DE OUTROS PACOTES DE CODIGO DA SUA APLICAÇÂO

// INCLUI AS FUÇÕES E OS MODELOS DE DADOS, OU SEJA, CLASSES CONCRETAS QUE AINDA
// PRECISAM SER IMPLEMENTADAS
#include "ModuloIMPL.h"


//////////////////////////////////
// implmentação de metodos globais
//////////////////////////////////

long unsigned int fat(int n ) {
 
  long int result = 1;
  
  for (int i = 1; i <= n; i++) {
	  result = result * i;
  }

  return result;
  
  // para testar a DLL, substitua a linha acima pela linha a seguir:
  // return 0;
}

//////////////////////////////////
// implmentação de classes concretas
//////////////////////////////////

int CalculadoraIMPL_::getParcela1( void ) { return p1; }

int CalculadoraIMPL_::getParcela2( void ) { return p2; }
	
void CalculadoraIMPL_::setParcela1( int p ) { p1 = p; }

void CalculadoraIMPL_::setParcela2( int p ) { p2 = p; };
	
int CalculadoraIMPL_::getSoma( void ) { return p1 + p2; }

