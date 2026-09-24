
// ARQUIVO DE DEFINIÇÃO DAS CLASSES CONCRETAS DE DEPENDENCIAS OU OUTROS PACOTES DE CODIGO 
// DA SUA APLICAÇÂO

// INTERFACES QUE PRECISAM SER IMPLEMENTADAS
#include "..\include\modulo.h"

class unit_CalculadoraIMPL_;

// DECLARAÇÃO DAS CLASSES CONCRETAS
class CalculadoraIMPL_ : public Calculadora{
	
	int p1;
	int p2;
	
	// PARA OS TESTES UNITARIOS ACESSAREM DIRETAMENTE OS ATRIBUTOS DA CLASSE E OBJETOS
	friend class unit_CalculadoraIMPL_; 
	
public:
	virtual ~CalculadoraIMPL_(){ } // forma padrão
	
	virtual int getParcela1( void );
	virtual int getParcela2( void );
	
	virtual void setParcela1( int p );
	virtual void setParcela2( int p ); 
	
	virtual int getSoma( void );
	
	
};
