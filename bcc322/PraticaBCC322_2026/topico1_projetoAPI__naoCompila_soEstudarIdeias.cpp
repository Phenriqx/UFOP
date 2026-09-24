
// camada de aplicação (superior) ---------------
// aplication - PRIMEIRAS PERGUNTAS (QUAL API?)
int main1(void) {
	
	// 1) usuários/atores???
	// 2) Como cada usuário pretende utilizar esta classe? (Quais são os casos de uso?)
	// listar todos os elementos no container
	// 
}

// aplication - PRIMEIRA RESPOSTA: ALTERNATIVA 1 DO PROJETO DE API
int main2(void) {
		
	// 1) usuários/atores???
	// 2) Como cada usuário pretende utilizar esta classe? (Quais são os casos de uso?)
	
	// ------------------
	// cliente
	send_resquet();
	receive_file()
	
	// servidor 
	receive_request();
	send_file();
}

// aplication - SEGUNDA RESPOSTA: ALTERNATIVA 2 DO PROJETO DE API
int main3(void) {
	
	
	// 1) usuários/atores???
	// 2) Como cada usuário pretende utilizar esta classe? (Quais são os casos de uso?)
	// listar todos os elementos no container
	
	
	// ---------------- precisa ter a certeza que 
	// ---------------- servidor está online antes
	// ---------------- de enviar um request
	// cliente
	Connection c = openConnection(); // sincrono
	c.send_resquet();
	c.receive_file();
	c.close();
	
	// servidor 
	while( true ) {
		Connection c;
		c.wait() // sincrono
		receive_request();
		send_file();
		c.close();
	}
}

// aplication - TERCEIRA RESPOSTA: ALTERNATIVA 3 - E SE O USUÀRIO QUISER ATENDER AOS DOIS CASOS COMO UMA UNICA API
int main4(void) {

	// ... depois, de estudar o possíveis "casos de uso" o DEV ainda teria reponser as seguinte 
	// perguntas para conseguir projetar a API:
	// 3) Quais funcionalidades cada usuário deseja? Qual comportamento do software 
	//    esperado por cada usuário? Qual seria o nome, parametros e valores de 
	//    retorno das funcões que implementariam esta funcionalidade?
	// 4) Quais são os critérios de aceitação para cada funcionalidade requerida? (US do BDD)
	// 5) Quais são os cenários de teste que materializam estes critérios de aceitação?
	// 
	// .. finalmente, O DEV realiza os proximos passos:
	// 6) implementa os cenários de teste incrementalmente
	// 7) para cada cenário implmentado, ele em seguida implementa a funcionalidade até
	// 	  que ela passe no teste
	// 8) volta ao passo 6 até que todas as funcionalidades sejam desenvolvidas
	// 9) caso ocorra mudanças nos requisitos, casos de uso, US ou cenários de testes, 
	//    o DEV deve retroceder ao passo especifico da concepção e refazer os passos
	//    subsequentes



// ----------- camada inferior
// biblioteca ou framework  - O MESMO PROCESSO SE REPETE NAS CAMADAS INFERIORES DA APLICAÇÃO
template <class T>
class Container {
	
   / CRUD é mesmo só isso ????? 
   // add(?)
   // remove(?)
   // update(?)
   // get(?)
   
   / vai ter ITERADOR????
   //iterator it;
   //begin()
   //end()
   
   / uma API CRUD certamente tem mais que os metodos Cadastrate, Read, Update e Delete
   // find(?)
   // sort(?)
   // print(?)
   // filter(?)
  
};