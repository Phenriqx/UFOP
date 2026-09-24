////////////////////////////////////////////////
// ESTRUTURA GERAL DE UMA APLICAÇÂO
////////////////////////////////////////////////

//////////////////////////////////////////////// -- API
// classe puramente abstrata
class InterfaceOutraClasse { // Interface
    virtual int metodo1(...) = 0;
    virtual bool metodo2(...) = 0;
}

//////////////////////////////////////////////// -- IMPLENTAÇAO API
// Classe concreta DEVE ESTAR NA FORMA CANÔNICA
class OutraClasse: public InterfaceOutraClasse{
	protected:
		int variavel 
	public:
		
		OutraClasse(){...}
		virtual ~OutraClasse(){...}
		
		int metodo1(...);
		bool metodo2(...);
		
	public:
		OutraClasse ( const OutraClasse &o) {...}
		OutraClasse operator=( const OutraClasse &o) {...}
}
InterfaceOutraClasse obj; // não pode ser insetanciada pq é abstrata
OutraClasse obj; // sim, tudo bem

obj.metodo1(...);
////////////////////////////////////////////////


