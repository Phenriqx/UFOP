[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/ac7nK5R5)
# Tarefa: Vendas

Nesta tarefa, você implementará um programa interativo em Haskell para calcular o valor total de uma compra de frutas.

Uma feirante vende morangos e maçãs com a seguinte tabela de preços:

| Produto | Até 5 kg | Acima de 5 kg |
| --- | ---: | ---: |
| Morango | R$ 8,50 por kg | R$ 7,20 por kg |
| Maçã | R$ 5,25 por kg | R$ 4,75 por kg |

A situação é simples, mas realista: pequenos sistemas comerciais precisam combinar cálculo numérico, validação de entrada e apresentação clara do resultado ao usuário. O objetivo da atividade é separar essas duas responsabilidades: a regra de cálculo deve ficar em uma função pura, enquanto a interação com o usuário deve ficar na ação `main`.

## O que você deve implementar

Complete o arquivo `src/Vendas.hs`.

### Função pura

Implemente a função:

```haskell
valorTotal :: Double -> Double -> Double
```

A função recebe:

1. a quantidade de morangos, em kg;
2. a quantidade de maçãs, em kg.

Ela deve retornar o valor total da compra, usando a tabela de preços acima.

Nesta função, considere apenas o cálculo do valor. A validação de entradas negativas será feita na ação `main`.

### Ação principal

Implemente também:

```haskell
main :: IO ()
```

A ação `main` deve:

1. configurar a saída padrão sem bufferização;
2. perguntar a quantidade de morangos;
3. perguntar a quantidade de maçãs;
4. se alguma quantidade for negativa, imprimir `Entrada inválida`;
5. caso contrário, imprimir o valor total da compra com duas casas decimais.

Use exatamente estas mensagens nos prompts:

```text
Digite a quantidade de morangos (em kg):
Digite a quantidade de maçãs (em kg):
```

A saída final para uma entrada válida deve ter a forma:

```text
O valor total da compra é R$ 104.01
```

## Exemplos de execução

```shellsession
Digite a quantidade de morangos (em kg): -15
Digite a quantidade de maçãs (em kg): 8
Entrada inválida
```

```shellsession
Digite a quantidade de morangos (em kg): 10
Digite a quantidade de maçãs (em kg): -1
Entrada inválida
```

```shellsession
Digite a quantidade de morangos (em kg): 0
Digite a quantidade de maçãs (em kg): 10.5
O valor total da compra é R$ 49.88
```

```shellsession
Digite a quantidade de morangos (em kg): 0
Digite a quantidade de maçãs (em kg): 0
O valor total da compra é R$ 0.00
```

```shellsession
Digite a quantidade de morangos (em kg): 10.8
Digite a quantidade de maçãs (em kg): 5
O valor total da compra é R$ 104.01
```

## Dicas

Para formatar um número com duas casas decimais, use a função `printf`, importada do módulo `Text.Printf`:

```haskell
import Text.Printf (printf)
```

Em Haskell, `printf` é uma função de formatação. Quando indicamos que o resultado esperado é uma `String`, ela se comporta de modo semelhante à função `sprintf` da linguagem C: em vez de imprimir diretamente na tela, ela produz uma string formatada.

Por exemplo:

```haskell
mensagem :: String
mensagem = printf "O valor total da compra é R$ %.2f\n" valor
```

Depois de produzir essa string, você pode enviá-la para a saída padrão com `putStr`:

```haskell
putStr mensagem
```

Também é possível combinar as duas etapas em uma única linha:

```haskell
putStr (printf "O valor total da compra é R$ %.2f\n" valor :: String)
```

O especificador `%.2f` indica que o número deve ser mostrado com duas casas decimais. O `\n` no final representa uma quebra de linha.

Para que os prompts apareçam antes da leitura da entrada, configure a saída padrão sem bufferização:

```haskell
import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)

hSetBuffering stdout NoBuffering
```

## Como testar

Você pode editar os arquivos fonte em um editor de texto e testá-los com Cabal:

```shellsession
$ cabal build       # compila o projeto
$ cabal repl vendas # abre o GHCi com o módulo da atividade carregado
$ cabal run vendas  # executa o programa interativo
$ cabal test        # executa os testes automáticos
```

O projeto será corrigido automaticamente pelo GitHub Classroom. Seu código deve passar em todos os testes fornecidos.
