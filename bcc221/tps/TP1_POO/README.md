
# TP1 - Sistema de Gestão Bancária | Programação Orientada a Objetos (BCC221)

Este projeto consiste na implementação de um **Sistema de Gestão Bancária** simulado via linha de comando (CLI). O sistema foi desenvolvido como o Trabalho Prático I da disciplina **BCC221 - Programação Orientada a Objetos**, no Departamento de Computação da **Universidade Federal de Ouro Preto (UFOP)**.

A aplicação manipula contas, utilizadores (Clientes e Gerentes) e transações financeiras, aplicando os pilares de POO de forma coesa e garantindo a persistência dos dados através da manipulação de ficheiros de texto plano.

---

## 🎯 Objetivos do Projeto

O propósito principal é consolidar de forma prática a modelagem orientada a objetos na linguagem C++, focando nos seguintes aspetos:
1. **Modelagem Hierárquica:** Criação de perfis administrativos (Gerentes) e de utilizadores comuns (Clientes) com suporte completo a strings complexas (nomes compostos).
2. **Operações Financeiras Consolidadas:** Mecanismos rigorosos de validação de saldo para saques, depósitos e transferências bancárias em Contas Correntes e Poupanças.
3. **Automatização de Rendimentos:** Atualização de saldos de contas poupança baseada na taxa de rendimento mensal estipulada pela remuneração do titular.
4. **Módulo Avançado de Crédito (Diferencial):** Implementação de uma subestrutura independente para cartões de crédito, compras parceladas, controlo de limites dinâmicos e emissão/pagamento de faturas.

---

## 🛠️ Especificações Técnicas e Arquitetura

### 1. Tecnologias Utilizadas
* **Linguagem:** C++ (Padrão de compilação C++17 recomendado).
* **Biblioteca Padrão (STL):** Uso extensivo de *containers* dinâmicos (`std::vector`), manipulação avançada de cadeias de caracteres (`std::string`), e controlo de fluxos de entrada/saída de dados de ficheiros (`std::ifstream`, `std::ofstream`, `std::stringstream`).
* **Persistência de Dados:** Organizada em formato plano delimitado por vírgulas (`.csv`), mapeando de forma transparente os dados da memória para o disco rígido nos ficheiros `clientes.csv` e `gerentes.csv`.

### 2. Padrões de POO Aplicados
* **Abstração e Herança:** A classe base `Pessoa` atua como uma entidade abstrata que centraliza os dados cadastrais protegidos (`nome`, `trabalho`) e privados (`login`, `senha`). Dela derivam as especializações `Cliente` e `Gerente`.
* **Polimorfismo:** Implementado através do método virtual puro `getHeader()` e do método virtual `exibirDados()`, garantindo que cada classe filha execute o seu comportamento específico em tempo de execução.
* **Encapsulamento Rígido:** Atributos críticos (como saldos, faturas e senhas) estão fortemente protegidos por modificadores de acesso privados, sendo acedidos unicamente por métodos seletores (*getters*) e modificadores (*setters*) com validações internas.
* **Associação por Ponteiros:** A carteira de clientes de um `Gerente` e a lista de `clientesEnvolvidos` de uma `Transacao` utilizam vetores de ponteiros (`std::vector<Cliente*>`). Isto previne a duplicação desnecessária de dados em memória RAM e garante que qualquer alteração de saldo seja propagada instantaneamente em todo o sistema.
* **Composição Estrita:** O ciclo de vida da classe `CartaoCredito` e das instâncias de `CompraParcelada` está intrinsecamente ligado ao objeto `Cliente`. Se o cliente for destruído, os seus cartões e faturas deixam de existir simultaneamente.
* **Programação Genérica (Templates):** A função de escrita `escreverCSV` e o motor de buscas `buscaPessoa` foram modularizados através de *templates* de tipo (`template<typename T>`), permitindo que o mesmo código processe conjuntos distintos de dados de forma reutilizável.

---

## 📂 Estrutura de Ficheiros

O projeto encontra-se modularizado, dividindo as especificações de interface (`.hpp`) das lógicas de implementação (`.cpp`):

```text
├── auxiliares.hpp / auxiliares.cpp   # Funções de IO, buffers, templates e carga de CSV
├── pessoa.hpp / pessoa.cpp           # Classe base abstrata (Pessoa)
├── cliente.hpp / cliente.cpp         # Especialização de conta, extrato e composição do cartão
├── gerente.hpp / gerente.cpp         # Especialização administrativa e carteira de clientes
├── transacao.hpp / transacao.cpp     # Motor de movimentações financeiras e histórico
├── credito.hpp / credito.cpp         # Lógica do Cartão de Crédito e sub-módulo de parcelamento
├── main.cpp                          # Ponto de entrada da aplicação e Menu de Controlo CLI
├── Makefile                          # Script automatizado de compilação nativa
├── .gitignore                        # Restrições de rastreamento do Git (ignora objetos e bins)
├── clientes.csv                      # Banco de dados de persistência dos clientes
└── gerentes.csv                      # Banco de dados de persistência dos gerentes

```

---

## 🚀 Como Compilar e Executar

O projeto conta com um script de automação de compilação (**Makefile**) estruturado com as flags `-Wall -std=c++17 -g`.

### 1. Compilação Limpa e Construção

Para remover ficheiros binários residuais antigos e compilar o projeto do zero gerando o executável final `banco`, execute no terminal:

```bash
make clean
make

```

### 2. Execução Direta

Para compilar (caso existam modificações recentes) e rodar o ambiente do banco imediatamente através do atalho automatizado:

```bash
make run

```

Ou, alternativamente, invoque o binário gerado na raiz:

```bash
./banco

```

---

## ⚙️ Guia de Utilização (Exemplos de Fluxo)

A aplicação é guiada inteiramente por escolhas digitadas no terminal. Abaixo constam os principais fluxos de operação:

### Menu Principal
Ao iniciar o executável `./banco`, os ficheiros de persistência são lidos e as seguintes ações ficam disponíveis:
* **Opções 1 e 2:** Permitem registar clientes ou gerentes no sistema utilizando `std::getline`, aceitando nomes completos e espaços sem quebrar o buffer de entrada.
* **Opção 3 (Criar Transação):** Solicita o tipo de movimentação. No caso de uma **Transferência**, o sistema pede o nome do pagador e do recebedor, faz a busca na memória via ponteiro, valida se há saldo suficiente na conta de origem e efetua a operação realocando a transação no extrato de ambos os envolvidos.
* **Opção 5 (Associar Gerente a Cliente):** Vincula uma conta de cliente existente à carteira de controlo de um gerente específico.
* **Opção 9 (Salvar e Sair):** Grava de forma segura todas as modificações em memória nos ficheiros `.csv` correspondentes e encerra a execução.

### Submenu: Módulo de Crédito (Opção 8)
Ao acessar o painel de gerenciamento de crédito, abre-se um ciclo (`do-while`) de autoatendimento exclusivo:
* **Opção 1 (Criar Cartão):** Cria uma instância de cartão com limite automático definido estritamente como o dobro da remuneração cadastrada do cliente.
* **Opções 2 e 6 (Bloqueio/Desbloqueio):** Permite que restrições administrativas sejam aplicadas ao cartão do utilizador, impedindo compras indesejadas, com a possibilidade de reversão.
* **Opção 4 (Pagamento Parcelado):** Realiza compras registando a descrição e o número de parcelas desejado, abatendo o valor total imediatamente do limite disponível do cartão.
* **Opção 5 (Acessar Fatura):** Exibe o extrato detalhado de parcelas em aberto, permitindo gerar a fatura do mês atual e quitá-la. O pagamento debita o dinheiro diretamente do saldo em conta do cliente e restabelece o limite de crédito do cartão na mesma hora.