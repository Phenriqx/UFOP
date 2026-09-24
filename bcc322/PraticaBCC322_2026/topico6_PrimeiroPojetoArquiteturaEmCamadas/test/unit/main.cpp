// TESTES UNITÁRIOS
#include <iostream>
#include <assert.h>


using namespace std;

/////////////////////////////////////////////////////////////////////
// TESTES UNITARIOS - devem ser rapidos/baratos e independentes.
// 		Eles testam implementações!
/////////////////////////////////////////////////////////////////////
#include "..\..\src\moduloDoMeuApp\moduloIMPL.h"

class unit_CalculadoraIMPL_ {

public:
	
	bool test_getParcela1( void ) { 
		CalculadoraIMPL_ calc;
		calc.p1 = 10; // independencia: não pode depender do metódo set
		assert( calc.getParcela1() == 10);
		return true;
	}

	bool test_getParcela2( void ) { 
		CalculadoraIMPL_ calc;
		calc.p2 = 20; // independencia: não pode depender do metódo set
		assert( calc.getParcela2() == 20);
		return true;
	}
	
	bool test_setParcela1( void ){ 
		CalculadoraIMPL_ calc;
		calc.setParcela1(10); 
		assert( calc.p1 == 10); // independencia: não pode depender do metódo get
		return true;
	}
	
	bool test_setParcela2( void ){ 
		CalculadoraIMPL_ calc;
		calc.setParcela1(-3); 
		assert( calc.p1 == -3); // independencia: não pode depender do metódo get
		return true;
	}
	
	bool test_getSoma( void ){ 
		CalculadoraIMPL_ calc;
		calc.p1 = 7; 
		calc.p2 = 3; 
		assert( calc.getSoma() == 10); // independencia: não pode depender de outros metódos
		return true;
	} 

};

// TESTE UNITARIO REGRESSIVO
int main(void){

	cout << "inicio teste..." << endl;
	
	unit_CalculadoraIMPL_ calc;
	
	calc.test_getParcela1();
	calc.test_getParcela2();
	
	calc.test_setParcela1();
	calc.test_setParcela2();

	calc.test_getSoma();
  
	cout << "fim teste!";
	cout.flush();
}