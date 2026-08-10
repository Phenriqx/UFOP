[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/g8AT0K9f)
# Tarefa: Refeição saudável

Nesta tarefa, você implementará um programa interativo em Haskell para analisar o valor calórico de uma refeição.

A situação modela uma decisão cotidiana: uma pessoa deseja fazer uma refeição saudável com no máximo 600 calorias. Caso a refeição ultrapasse esse limite, será necessário compensar o excesso com exercício em uma esteira ergométrica.

No restaurante Phomy's, o prato do dia é composto por arroz, feijão e salada, totalizando 250 calorias. Além disso, o cliente deve informar a quantidade de bife consumida, em gramas. O bife possui 300 calorias a cada 100 g.

A atividade combina duas partes:

1. funções puras, responsáveis pelos cálculos;
2. uma ação `main`, responsável pela interação com o usuário.

## Regras do problema

O total de calorias da refeição é calculado por:

```text
calorias da refeição = 250 + calorias do bife
calorias do bife = gramas do bife * 300 / 100
```

Se o total de calorias for menor ou igual a 600, a refeição é considerada saudável.

Caso contrário, o programa deve calcular o excesso calórico. Sabe-se que 30 minutos de esteira queimam 300 calorias. Portanto, o tempo necessário de esteira é proporcional ao excesso calórico.

Nesta atividade, não é necessário validar a entrada.

## O que você deve implementar

Complete o arquivo `src/RefeicaoSaudavel.hs`.

### Funções puras

Implemente as funções:

```haskell
caloriasRefeicao :: Double -> Double
```

A função recebe a quantidade de bife em gramas e retorna o total de calorias da refeição.

Exemplos:

```haskell
caloriasRefeicao 100.0 == 550.0
caloriasRefeicao 200.0 == 850.0
```

Implemente também:

```haskell
minutosEsteira :: Double -> Double
```

A função recebe a quantidade de bife em gramas e retorna o número de minutos de esteira necessários para queimar as calorias excedentes.

Quando a refeição for saudável, o resultado deve ser `0`.

Exemplos:

```haskell
minutosEsteira 100.5 == 0.0
minutosEsteira 200.0 == 25.0
```

### Ação principal

Implemente também:

```haskell
main :: IO ()
```

A ação `main` deve:

1. configurar a saída padrão sem bufferização;
2. solicitar a quantidade de bife em gramas;
3. calcular o total de calorias da refeição;
4. imprimir uma mensagem indicando se a refeição é saudável;
5. caso exista excesso calórico, imprimir o tempo de esteira com duas casas decimais.

Use exatamente este prompt:

```text
Informe as gramas do bife:
```

Use exatamente estas mensagens de saída:

```text
Refeição saudável!
```

```text
Excesso calórico, fazer 25.00 minuto(s) de esteira!
```

O valor `25.00` acima é apenas um exemplo. Seu programa deve imprimir o valor calculado para cada entrada.

## Dicas

Para ler um número real digitado pelo usuário, você pode usar `readLn` com anotação de tipo:

```haskell
gramas <- readLn :: IO Double
```

Para formatar valores numéricos com duas casas decimais, use a função `printf`, importada do módulo `Text.Printf`:

```haskell
import Text.Printf (printf)
```

Em Haskell, `printf` é uma função de formatação. Quando indicamos que o resultado esperado é uma `String`, ela se comporta de modo semelhante à função `sprintf` da linguagem C: em vez de imprimir diretamente na tela, ela produz uma string formatada.

Por exemplo:

```haskell
mensagem :: String
mensagem = printf "Valor: %.2f\n" valor
```

Depois disso, você pode imprimir a string com `putStr`:

```haskell
putStr mensagem
```

Também é possível combinar as duas etapas em uma única linha:

```haskell
putStr (printf "Valor: %.2f\n" valor :: String)
```

O especificador `%.2f` indica que o número deve ser mostrado com duas casas decimais. O `\n` no final representa uma quebra de linha.

## Exemplos de execução

```shellsession
Informe as gramas do bife: 100.5
Refeição saudável!
```

```shellsession
Informe as gramas do bife: 200
Excesso calórico, fazer 25.00 minuto(s) de esteira!
```

```shellsession
Informe as gramas do bife: 328.64
Excesso calórico, fazer 63.59 minuto(s) de esteira!
```

```shellsession
Informe as gramas do bife: 298.50
Excesso calórico, fazer 54.55 minuto(s) de esteira!
```

## Como testar

Você pode editar os arquivos fonte em um editor de texto e testá-los com Cabal:

```shellsession
$ cabal build                    # compila o projeto
$ cabal repl refeicao-saudavel   # abre o GHCi com o módulo da atividade carregado
$ cabal run refeicao-saudavel    # executa o programa interativo
$ cabal test                     # executa os testes automáticos
```

O projeto será corrigido automaticamente pelo GitHub Classroom. Seu código deve passar em todos os testes fornecidos.
