#include <iostream>
#include <vector>

using namespace std;

// CLASSES CONCRETAS DEVEM ESTAR NA FORMA CANÔNICA
// 
// EVITE LEAKS DE MEMORIA!!
// SUA IMPLEMENTAÇÃO DEVE FAZER SÓ O ESPERADO (somente o comportamento desejado)
//
// O construtor de copia e o operador atribuição são oferecidos ao usuário da sua API
// para que a copia de objetos seja realizada segundo seu projeto e toda API 
// funcione coerentemente. 
//
// Durante o projeto da sua API, você precisou decidir que tipos de objetos poderiam
// ser copiados e se a cópias seriam profundas ou rasas.
//  
// TODO DESTRUTOR DEVE SER VIRTUAL PARA EVITAR "SLICING" 
// TODO METODO VIRTUAL SOBRECARREGADO DEVE CONTINUAR VIRTUAL PARA QUE A CADEIA DE 
// MENSAGENS PARA AS SUBCLASSES NÂO SEJA QUEBRA

#define VIRTUAL_DESTRUCTOR

int memoryObjects = 0;

class MinhaClasse { 
	protected: 
		char c;
	public:
	
		 MinhaClasse( ) { 
			c = '#';  
			memoryObjects++;
		}

		 
		 // tendencia de slicing se remove o "virtual"
		 #ifdef  VIRTUAL_DESTRUCTOR 
			virtual ~MinhaClasse( ) { 
		 #else
			~MinhaClasse( ) { 
		 #endif
				cout << "End\n"; 
			} 
			
};

//////////////////////////////////////////////// -- IMPLENTAÇAO API
// Classe concreta
class OutraClasse: public MinhaClasse{
	private:
		int* p;
		int variavel[100];
	public:
		OutraClasse( ) { p = new int; }
		virtual ~OutraClasse() { 
			cout << "The" << c; 
			memoryObjects--;
			delete p;  
		}
};


//////////////////////////////////////////////// -- IMPLENTAÇAO API


int main( void ){
	const int N = 10;  // número grande para a variação ser visível
    
	vector<MinhaClasse*> objetos;

    cout << "Inciando alocacao de " << N << " objetos...\n";
    for (int i = 0; i < N; i++) {
        objetos.push_back(new OutraClasse());
    }
    cout << "Total de objetos alocados: "  << memoryObjects << " \n";

    for (MinhaClasse* obj : objetos) {
        delete obj;
    }
    objetos.clear();

    cout << "Total de objetos alocados: "  << memoryObjects << " \n";
	cout << "FIM";

    return 0;
}
////////////////////////////////////////////////