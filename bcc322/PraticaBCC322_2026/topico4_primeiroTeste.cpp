#include <assert.h>
#include <iostream>

// TDD - Test Driven Development

using namespace std;

#define NOVO_CASO_DE_USO  

int func( void ){
	
	return true;
}


#ifndef NOVO_CASO_DE_USO  
	int fat(int n ) {
	 
	  int result = 1;
	  
	  for (int i = 1; i <= n; i++) {
		  result = result * i;
	  }

	  return result;
	}
#else
	long unsigned int fat(int n ) {
	 
	  long unsigned int result = 1;
	  
	  for (int i = 1; i <= n; i++) {
		  result = result * i;
	  }

	  return result;
	}

#endif

bool testFat( void ) {

	// COMO NÃO implementar um cenário de teste
	// pior ainda é o: 
	//             if( erro ) cout<< "Fudeu!";
	//
    cout << "\tFatorial de 3: " << fat(3) << endl; 
	
	// A MANEIRA CORRETA
    assert ( fat(1) == 1 ); 
	assert ( fat(2) == 2 );
	assert ( fat(3) == 6 ); 
	
	// QUER MAIS ROBUSTEZ?
	// O cenário que evita o caso classico de falha na implementação
	assert ( fat(0) == 1 ); 
	
	
	// DEPOIS DE ALGUM TEMPO SURGE UM NOVO CASO DE USO
	// QUE EXIGE MUDANÇA NA API
	// Implmente o teste e, então, reimplmente a funcionalidade para passar 
	// no novo teste
	#ifdef NOVO_CASO_DE_USO 
		assert ( fat(32) == (unsigned long int) 2147483648L);
	#endif
	
	return true;
}


int main(void){

	cout << "inicio..." << endl;
	
	testFat();

	#ifdef NOVO_CASO_DE_USO 
		cout <<"\tNOVO Caso de Uso: " << fat(32) << endl;	
	#endif
	
	cout << "fim!";
	cout.flush();
	
	return true;

}