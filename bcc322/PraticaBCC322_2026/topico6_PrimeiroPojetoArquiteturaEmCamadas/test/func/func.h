// TESTE FUNCIONAL DO MODULO DO MEU APP
#define FUNC_MEU_MODULO
#ifdef FUNC_MEU_MODULO

// NÂO HÁ DEPENDÊNCIA DE IMPLEMENTAÇÃO
#include "..\..\src\include\modulo.h"

// A INJEÇÂO DE DEPENDENCIAS RESOLVEU ESTE PROBLEMA
// O objeto calc é a dependencia injetada, neste caso!!!
bool teste_func_Calculadora( Calculadora &calc ){
	
	// HISTÓRIA DE USUÀRIO COLHIDA DA VOZ DO USUÀRIO
	//
	// EU COMO um usuário 
	// GOSTARIA DE realizar a soma de duas parcelas
	// PARA OBTER o resultado correto da soma 
	
	
	// CENARIO DE TESTE COLHIDO DA VOZ DO USUÀRIO
	//
	// DADO QUE (parcela1 = 7) e (parcela2 = -3)
	// QUANDO invocar soma()
	// ENTÃO o resultado na tela será igual a 4
	
	calc.setParcela1(7);
	calc.setParcela2(-3);
	assert( calc.getSoma() == 4 );
	

	return true;
}

#endif