// INTERFACE DA APLICAÇÂO ( parte API )
#ifndef MODULO_H
#define MODULO_H

long unsigned int fat( int n );

// TODA INTERFACE DEVE TER UM DESTRUTOR VIRTUAL PARA GARATIR O REPASSE DE MENSAGENS
// PARA AS SUBCLASSES QUE DELA HERDAREM, ISTO È, CLASSES QUE IMPLEMENTAREM A INTERFACE
// 
class Calculadora{
public:

	virtual ~Calculadora(){ } // forma padrão

	virtual int getParcela1( void ) = 0;
	virtual int getParcela2( void ) = 0;
	
	virtual void setParcela1( int ) = 0;
	virtual void setParcela2( int ) = 0;
	
	virtual int getSoma( void ) = 0; 
};
	

#endif