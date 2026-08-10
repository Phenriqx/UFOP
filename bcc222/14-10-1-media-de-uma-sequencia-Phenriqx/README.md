[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/I1xf4PUS)
# Atividade: média de uma sequência de números

## Descrição

Nesta atividade, você implementará um programa interativo em Haskell que calcula a média aritmética de uma sequência de números.

O programa deve solicitar ao usuário um número inteiro `n`, que representa a quantidade de números que serão lidos. Em seguida, deve ler `n` números de ponto flutuante e, ao final, exibir a média aritmética calculada com duas casas decimais.

Esta atividade exercita:

- ações de E/S recursivas controladas por contador;
- uso de `return` para produzir um valor dentro de uma ação de E/S;
- separação entre lógica pura e interação com o usuário;
- conversão de `Int` para `Double` com `fromIntegral`.

## Funções e ações a implementar

Complete as definições no arquivo `src/MediaSequencia.hs`. Não altere os nomes nem as assinaturas exportadas pelo módulo.

### `calculaMedia :: [Double] -> Double`

Função pura que recebe uma lista de números e resulta na média aritmética.

Requisitos:

- se a lista for vazia, o resultado deve ser `0.0`;
- caso contrário, o resultado deve ser `sum xs / fromIntegral (length xs)`.

### `lerNumeros :: Int -> IO [Double]`

Ação de E/S recursiva que lê `n` números do teclado e retorna esses números em uma lista.

Requisitos:

- se `n <= 0`, a ação deve retornar `[]`;
- se `n > 0`, a ação deve solicitar um número, ler esse valor, chamar recursivamente `lerNumeros (n - 1)` e construir a lista de resultados.

### `main :: IO ()`

Ação principal que organiza o programa:

1. configura o buffering de saída;
2. solicita a quantidade de números;
3. chama `lerNumeros`;
4. calcula a média com `calculaMedia`;
5. exibe a saída final formatada.

## Formatação da saída

A média deve ser exibida com exatamente duas casas decimais. Use `printf` do módulo `Text.Printf`.

```haskell
printf "A média dos números é: %.2f\n" valorDaMedia
```

As mensagens devem ser exatamente as usadas nos exemplos e nos testes.

## Exemplos de execução

```shellsession
Quantidade de números a serem lidos: 4
Digite um número: 10.5
Digite um número: 20.0
Digite um número: 5.5
Digite um número: 4.0
A média dos números é: 10.00
```

```shellsession
Quantidade de números a serem lidos: 3
Digite um número: -10
Digite um número: 10
Digite um número: 30
A média dos números é: 10.00
```

```shellsession
Quantidade de números a serem lidos: 0
A média dos números é: 0.00
```

```shellsession
Quantidade de números a serem lidos: -5
A média dos números é: 0.00
```

## Desenvolvimento e testes

Compile, execute e teste o projeto com:

```shellsession
cabal build                 # Compila o projeto
cabal repl media-sequencia  # Carrega o projeto no GHCi
cabal run media-sequencia   # Executa o programa
cabal test                  # Executa os testes de verificação automática
```