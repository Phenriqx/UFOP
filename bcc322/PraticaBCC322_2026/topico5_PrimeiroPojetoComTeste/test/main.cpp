// MAIN DO PACOTE DE TESTES
#include <iostream>
#include <assert.h>

// NÃO COPIE OU ALTERE ARQUIVOS DO PRODUTO EM TESTE
// FAÇA APENAS O INCLUDE 
#include "..\src\biblioteca.h"

using namespace std;


bool testFat( void ) {

    ///cout << fat(3);
    assert ( fat(0) == 1); 
	assert ( fat(1) == 1); 
	assert ( fat(2) == 2);
	assert ( fat(3) == 6); 
	assert ( fat(32) == (unsigned long int) 2147483648L);
	
	return true;
}

int main(void){

	cout << "inicio teste..." << endl;
	
	testFat();

  
	cout << "fim teste!";

}