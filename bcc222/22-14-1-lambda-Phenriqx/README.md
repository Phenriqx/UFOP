[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/zwyh5iB3)
# Tarefa: expressões lambda, aplicação parcial e seções

## Descrição

Nesta atividade, você implementará uma coleção de pequenas funções em Haskell. O objetivo é praticar três ideias centrais do capítulo 14:

1. escrever expressões lambda quando uma função auxiliar é simples e usada apenas localmente;
2. criar funções especializadas por aplicação parcial;
3. usar seções de operadores para tornar definições simples mais diretas.

Todas as implementações devem ser feitas no arquivo `src/Exercicios.hs`. Os testes automatizados estão em `test/MainSpec.hs`.

---

## Exercícios a implementar

### Exercício 1: refatorando para expressões lambda

Funções de ordem superior, como `map` e `filter`, frequentemente recebem outras funções como argumento. Quando essas funções auxiliares são simples e usadas apenas uma vez, é comum substituir uma definição local por uma expressão lambda diretamente no ponto de uso.

Sua tarefa é criar novas versões das funções abaixo, substituindo as definições locais (`where`) por expressões lambda passadas diretamente para `map` e `filter`.

```haskell
-- 1.1: função a ser refatorada
somaQuadradosPares :: [Int] -> Int
somaQuadradosPares xs = sum (map f (filter g xs))
  where
    f x = x * x
    g x = even x

-- Sua implementação com lambdas:
somaQuadradosParesLambda :: [Int] -> Int
somaQuadradosParesLambda = undefined

-- 1.2: função a ser refatorada
stringsMaioresQue5 :: [String] -> [String]
stringsMaioresQue5 xs = filter g xs
  where
    g s = length s > 5

-- Sua implementação com lambdas:
stringsMaioresQue5Lambda :: [String] -> [String]
stringsMaioresQue5Lambda = undefined

-- 1.3: função a ser refatorada
-- Adiciona o sufixo "!" a todas as strings com comprimento par.
adicionaExclamacaoPar :: [String] -> [String]
adicionaExclamacaoPar xs = map f (filter g xs)
  where
    f s = s ++ "!"
    g s = even (length s)

-- Sua implementação com lambdas:
adicionaExclamacaoParLambda :: [String] -> [String]
adicionaExclamacaoParLambda = undefined
```

### Exercício 2: funções especializadas com aplicação parcial e seções

A aplicação parcial e as seções de operadores permitem criar novas funções a partir de funções já existentes sem escrever todos os argumentos explicitamente.

Implemente as funções abaixo usando apenas aplicação parcial ou seções de operadores. Neste exercício, você não deve usar a sintaxe `\x -> ...`, nem definições auxiliares com `where` ou `let`.

```haskell
-- 2.1: retorna True se um caractere for uma vogal minúscula.
-- Dica: use a função elem e uma string com as vogais.
ehVogal :: Char -> Bool
ehVogal = undefined
-- Exemplos: ehVogal 'a' == True; ehVogal 'b' == False

-- 2.2: adiciona o sufixo ".com" a uma string.
adicionaCom :: String -> String
adicionaCom = undefined
-- Exemplo: adicionaCom "google" == "google.com"

-- 2.3: retorna a diferença entre 10 e o argumento recebido.
-- Dica: use uma seção do operador (-).
subtraiDe10 :: Int -> Int
subtraiDe10 = undefined
-- Exemplo: subtraiDe10 3 == 7
```

Observe a diferença entre as duas seções possíveis do operador `(-)`:

```haskell
(10 -) 3 == 7
(- 10) 3 == -7
```

Portanto, para `subtraiDe10`, a seção adequada é aquela que fixa o operando da esquerda.

### Exercício 3: processamento de dados com lambdas e padrões

Nesta parte, você combinará `map` ou `filter` com expressões lambda. A lambda deve usar casamento de padrão na tupla de entrada, por exemplo:

```haskell
\(nome, preco) -> ...
```

Use os tipos definidos no arquivo `src/Exercicios.hs`:

```haskell
type Venda = (String, Double)
type Aluno = (String, Double, Double) -- nome, nota1, nota2
```

Implemente as seguintes funções:

```haskell
-- 3.1: aplica uma taxa de 10% apenas nos itens cujo preço seja maior que R$ 50,00.
aplicaTaxa :: [Venda] -> [Venda]
aplicaTaxa = undefined
-- Exemplo:
-- aplicaTaxa [("A", 120.0), ("B", 40.0)] == [("A", 132.0), ("B", 40.0)]

-- 3.2: retorna os nomes dos alunos aprovados, isto é, com média das notas >= 7.0.
alunosAprovados :: [Aluno] -> [String]
alunosAprovados = undefined
-- Exemplo:
-- alunosAprovados [("Ana", 8.0, 8.0), ("Beto", 5.0, 7.0)] == ["Ana"]

-- 3.3: retorna o nome do produto e o preço final após desconto de 5%.
aplicaDesconto :: [Venda] -> [(String, Double)]
aplicaDesconto = undefined
-- Exemplo:
-- aplicaDesconto [("A", 100.0), ("B", 20.0)] == [("A", 95.0), ("B", 19.0)]
```

---

## Desenvolvimento e testes

Complete as definições em `src/Exercicios.hs`. O projeto deve passar em todos os testes fornecidos.

### Comandos essenciais do Cabal

```shellsession
$ cabal build all --enable-tests  # Compila a biblioteca, o executável e os testes
$ cabal repl lib:exercicios-lambda # Carrega a biblioteca no GHCi
$ cabal run exe:exercicios-lambda  # Executa o programa de exemplos
$ cabal test all                  # Executa os testes de funcionalidade
```

### Verificação de estilo com HLint

Além da corretude funcional, esta atividade avalia o estilo da implementação. O arquivo `.hlint.yaml` contém regras específicas para esta prática.

Para executar a verificação localmente, instale o HLint se necessário:

```shellsession
$ cabal install hlint
```

Depois, execute:

```shellsession
$ hlint src --hint=.hlint.yaml
```

Se o comando terminar com `No hints`, o código está de acordo com as regras configuradas.

As regras de estilo mais importantes são:

- as funções com sufixo `Lambda` devem usar expressões lambda explícitas;
- as funções `ehVogal`, `adicionaCom` e `subtraiDe10` devem usar aplicação parcial ou seções, sem `where`, `let` ou lambdas;
- as funções do exercício 3 devem usar lambdas com padrões nas tuplas de entrada.

O HLint ajuda a detectar vários desvios, mas ele não substitui a revisão cuidadosa do código. Soluções que passam nos testes, mas não seguem as restrições do enunciado, podem ser penalizadas.

---

## Organização dos arquivos

```text
.
├── app/Main.hs
├── src/Exercicios.hs
├── test/MainSpec.hs
├── exercicios-lambda.cabal
├── cabal.project
├── .hlint.yaml
└── .github/
    ├── workflows/classroom.yml
    └── classroom/autograding.json
```

O diretório `solution/` contém uma solução de referência para o professor e não deve ficar disponível na branch entregue aos alunos.
