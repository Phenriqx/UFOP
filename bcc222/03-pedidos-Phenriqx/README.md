[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/8p7iD0uL)
# Pedidos

Esta atividade prática do **capítulo 6 — estruturas de dados básicas** propõe a implementação de funções puras em Haskell para manipular dados de um pequeno sistema de preparação de pedidos de uma loja virtual.

A ideia é trabalhar, em um contexto único e coerente, com os principais temas do capítulo:

- **tuplas**, para agrupar informações relacionadas;
- **listas**, para representar coleções de itens;
- **`Maybe`**, para tratar a possível ausência de um valor;
- **listas de associação** com `lookup`;
- **sinônimos de tipo** com `type`, para tornar a modelagem mais legível.

A atividade deve ser **iniciada na aula prática** e pode ser concluída ao longo da semana.

## Objetivo

Ao final da atividade, você deverá ser capaz de:

- interpretar e manipular valores compostos por tuplas e listas;
- usar `Maybe` para tratar campos opcionais de forma segura;
- consultar informações em listas de associação;
- definir funções simples sobre uma modelagem de dados realista;
- começar a explorar a ideia de **recursão sobre listas**, em preparação para o capítulo dedicado a esse tema.

## Estrutura do projeto

Você deve editar **apenas** o arquivo:

- `src/Pedidos.hs`

Os testes automáticos estão em:

- `test/MainSpec.hs`

O projeto também inclui:

- `app/Main.hs`, apenas para execução manual simples;
- `pedidos.cabal`, com a configuração do projeto;
- arquivos de GitHub Classroom para autograding.

## Contexto do problema

Uma loja virtual precisa representar pedidos de clientes, consultar informações básicas sobre cada pedido e tratar situações em que o valor total ainda não foi calculado.

Nesta atividade, usaremos os seguintes tipos:

```haskell
type Cliente = String
type NomeProduto = String
type Quantidade = Int
type ValorTotal = Double

type ItemPedido = (NomeProduto, Quantidade)
type Pedido = (Cliente, [ItemPedido], Maybe ValorTotal)
type TabelaDescontos = [(Cliente, Double)]
```

A ideia é que cada pedido registre:

- o nome do cliente;
- a lista de itens comprados;
- o valor total do pedido, que pode estar ausente enquanto o cálculo ainda não foi realizado.

Além disso, teremos uma tabela de descontos por cliente.

## Biblioteca permitida para acessar componentes de triplas

Nesta atividade, você **pode** usar as funções `fst3`, `snd3` e `thd3`, do módulo `Data.Tuple.Extra`, para acessar os componentes de uma tripla:

```haskell
import Data.Tuple.Extra (fst3, snd3, thd3)
```

Isso evita a necessidade de usar casamento de padrão neste momento e deixa o foco da atividade nos conceitos do capítulo.

## Funções que devem ser implementadas

Implemente as funções abaixo no arquivo `src/Pedidos.hs`.

### 1. Acesso aos componentes do pedido

```haskell
clientePedido :: Pedido -> Cliente
itensPedido :: Pedido -> [ItemPedido]
totalPedido :: Pedido -> Maybe ValorTotal
```

Essas funções apenas selecionam os componentes da tripla que representa um pedido.

### 2. Informações derivadas do pedido

```haskell
quantidadeTiposItens :: Pedido -> Int
temTotalCalculado :: Pedido -> Bool
totalOuPadrao :: ValorTotal -> Pedido -> ValorTotal
```

Essas funções trabalham com listas e com `Maybe`:

- `quantidadeTiposItens` deve contar quantos tipos de itens aparecem no pedido;
- `temTotalCalculado` deve indicar se o pedido já possui um total;
- `totalOuPadrao` deve devolver o total do pedido ou um valor padrão fornecido.

### 3. Consulta em tabela de descontos

```haskell
consultarDesconto :: Cliente -> TabelaDescontos -> Double
clienteTemDesconto :: Cliente -> TabelaDescontos -> Bool
```

Aqui, a ideia é consultar uma **lista de associação**:

- `consultarDesconto` deve devolver o desconto do cliente;
- se o cliente não estiver presente na tabela, a função deve devolver `0.0`;
- `clienteTemDesconto` deve indicar se o cliente aparece na tabela.

### 4. Recursão sobre a lista de itens

```haskell
quantidadeTotalUnidades :: [ItemPedido] -> Int
```

Esta função deve somar as quantidades de todos os itens da lista.

Este é o exercício mais desafiador da atividade e deve ser resolvido com a ideia de **recursão sobre listas**.

#### Dica

Pense em dois casos:

- o que deve acontecer quando a lista estiver vazia;
- o que deve acontecer quando a lista tiver um primeiro item e o restante da lista.

Mesmo que recursão ainda não tenha sido estudada formalmente nesta disciplina, você já teve contato com essa ideia em outras disciplinas, e esta função serve como preparação para o capítulo futuro sobre recursividade em Haskell.

## Exemplos

```haskell
pedido1 :: Pedido
pedido1 = ("Alice", [("Notebook", 1), ("Mouse", 2)], Just 5050.0)

pedido2 :: Pedido
pedido2 = ("Bob", [("Cadeira", 4)], Nothing)

clientePedido pedido1         == "Alice"
itensPedido pedido2           == [("Cadeira", 4)]
temTotalCalculado pedido1     == True
temTotalCalculado pedido2     == False
totalOuPadrao 0.0 pedido2     == 0.0

tabela :: TabelaDescontos
tabela = [("Alice", 0.10), ("Carlos", 0.05)]

consultarDesconto "Alice" tabela   == 0.10
consultarDesconto "Bob" tabela     == 0.0
clienteTemDesconto "Carlos" tabela == True
clienteTemDesconto "Bob" tabela    == False

quantidadeTotalUnidades [("Notebook", 1), ("Mouse", 2), ("Teclado", 3)]
  == 6
```

## Como compilar e testar

Para abrir o projeto no ambiente interativo:

```bash
cabal repl
```

Para compilar o projeto:

```bash
cabal build
```

Para executar todos os testes:

```bash
cabal test
```

Para executar a suíte principal explicitamente:

```bash
cabal test test-pedidos
```

## Avaliação automática

A correção automática está dividida por função. Assim, cada parte da atividade é avaliada separadamente.

A distribuição de pontos é a seguinte:

- `clientePedido`: 1 ponto
- `itensPedido`: 1 ponto
- `totalPedido`: 1 ponto
- `quantidadeTiposItens`: 1 ponto
- `temTotalCalculado`: 1 ponto
- `totalOuPadrao`: 1 ponto
- `consultarDesconto`: 1 ponto
- `clienteTemDesconto`: 1 ponto
- `quantidadeTotalUnidades`: 2 pontos

Total: **10 pontos**.

## Entrega

- **Data regular de entrega:** até **28 de abril**
- **Data limite com penalização:** até **5 de maio**

Após a data regular, haverá **9 dias de tolerância com penalização de 10% por dia de atraso**.

## Observações finais

- não altere os nomes das funções nem das assinaturas de tipo;
- não mova os arquivos de lugar;
- leia com atenção os testes automáticos para entender melhor o comportamento esperado;
- caso precise relembrar o fluxo de trabalho com GitHub Classroom, Git, Cabal e GHCi, consulte o roteiro da atividade prática do capítulo 5.
