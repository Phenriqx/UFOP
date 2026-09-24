// TESTES FUNCIONAIS
#include <iostream>
#include <assert.h>

// Testes funcionais SÓ DEVEM CONHECER INTERFACES
#include "..\..\src\include\modulo.h"

using namespace std;


// TESTES FUNCIONAIS

bool testFat( void ) {

    ///cout << fat(3);
    assert ( fat(0) == 1); 
	assert ( fat(1) == 1); 
	assert ( fat(2) == 2);
	assert ( fat(3) == 6); 
	assert ( fat(32) == (unsigned long int) 2147483648L);
	
	return true;
}


// Inclui os testes funcionais da plataforma
#include "func.h"

// Porém, você só conegue intanciar objetos para os quais conhece as classs concretas
#include "..\..\src\moduloDoMeuApp\moduloIMPL.h"

// TESTE FUNCIONAL REGRESSIVO
int main(void){

	cout << "inicio teste..." << endl;
	
	cout << "\t Funcional: " << testFat() << endl;
	
	
	//  VOCÊ AINDA NÂO SABE COMO IMPLEMENTAR UM TESTE FUNCIONAL SEM CRIAR UM OBJETO A PARTIR 
	//  DE UMA CLASSE CONCRETA!
	// 	
	//		Calculadora &calc = CalculadoraIMPL_();
	//
	//  VOCÊ NÂO PODERIA DAR INCLUDE NO ARQUIVO "BibliotecaIMPL_.h"
	//  POIS ELE REVELARIA A IMPLEMENTAÇÂO DA CLASSE!
	//
	//  O TESTE FUNCIONAL PRECISA DEPENDER SOMENTE DE "Biblioteca.h"...
	//  VEREMOS COM RESOLVER ISSO MAIS A FRENTE!!!
	//  
	//  INFELIZMENTE...
	//  POR ENQUANTO VOCE TERÁ DE FAZER O INCLUDE DA IMPLEMENTAÇÂO PARA CONSEGUIR 
	//  DESENVOLVER OS TESTES FUNCIONAIS.
	//
	//  OU...
	//  VOCÊ PODE USAR A TECNICA DE "INJEÇÂO DE DEPENDENCIAS" PARA RESOLVER A QUESTÂO
	//  NESTE CASO, "CaluladoraIMPL_ calc" É A DEPDENCIA INJETADA!!!
	Calculadora *calc = new CalculadoraIMPL_();
	cout << "\t Funcional: " << teste_func_Calculadora( *calc ) << endl;
  
	cout << "fim teste!";

}