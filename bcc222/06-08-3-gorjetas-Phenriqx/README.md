[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/SrFWtNgD)
# Tarefa: Calculadora de gorjetas

Nesta tarefa, você implementará um programa interativo em Haskell que calcula uma gorjeta a partir do valor da conta e da avaliação da qualidade do serviço.

A situação modela uma pequena ferramenta de apoio para restaurantes, lanchonetes ou aplicativos de pagamento. O usuário informa o valor da conta e classifica o atendimento; o programa calcula a gorjeta sugerida e o total a pagar.

A atividade combina duas partes:

1. uma função pura, responsável pela regra de cálculo;
2. uma ação `main`, responsável pela interação com o usuário.

## Regras da gorjeta

As opções válidas para a qualidade do serviço são:

| Qualidade | Gorjeta |
| --- | ---: |
| `ruim` | 5% do valor da conta |
| `bom` | 10% do valor da conta |
| `excelente` | 15% do valor da conta |

Uma entrada é inválida quando:

- o valor da conta não pode ser lido como um número;
- o valor da conta é negativo;
- a qualidade do serviço não é uma das três opções válidas.

Em qualquer um desses casos, o programa deve imprimir:

```text
Entrada inválida!
```

## O que você deve implementar

Complete o arquivo `src/Gorjeta.hs`.

### Função pura

Implemente a função:

```haskell
gorjeta :: Double -> String -> Maybe Double
```

A função recebe o valor da conta e a qualidade do serviço.

Ela deve retornar:

- `Just valor`, quando a conta for não negativa e a qualidade for válida;
- `Nothing`, quando a conta for negativa ou a qualidade for inválida.

Exemplos:

```haskell
gorjeta 100.0 "ruim"      == Just 5.0
gorjeta 100.0 "bom"       == Just 10.0
gorjeta 100.0 "excelente" == Just 15.0
gorjeta 100.0 "medio"     == Nothing
gorjeta (-50.0) "bom"     == Nothing
```

### Ação principal

Implemente também:

```haskell
main :: IO ()
```

A ação `main` deve:

1. configurar a saída padrão sem bufferização;
2. solicitar o valor da conta;
3. tentar converter a entrada para `Double`;
4. solicitar a qualidade do serviço apenas se o valor da conta for um número válido;
5. usar a função `gorjeta` para calcular a gorjeta;
6. imprimir a gorjeta e o total a pagar com duas casas decimais;
7. imprimir `Entrada inválida!` quando a entrada não obedecer às regras.

Use exatamente estes prompts:

```text
Digite o valor da conta:
Qualidade do serviço (ruim, bom, excelente):
```

## Dicas

Para ler um número de forma segura, use `readMaybe`, importada do módulo `Text.Read`:

```haskell
import Text.Read (readMaybe)
```

A função `readMaybe` tenta converter uma string para um valor de algum tipo. Quando a conversão é possível, o resultado é `Just valor`; quando a conversão falha, o resultado é `Nothing`.

```haskell
readMaybe "123.45" :: Maybe Double  -- Just 123.45
readMaybe "abc"    :: Maybe Double  -- Nothing
```

Como ainda não estudamos casamento de padrões em detalhe, você pode verificar o resultado de `readMaybe` com uma expressão condicional. Por exemplo:

```haskell
-- Suponha que 'entrada' seja o retorno da ação 'getLine'.
do
  entrada <- getLine
  let maybeConta = readMaybe entrada :: Maybe Double
  if isNothing maybeConta
    then
      putStrLn "Entrada inválida!"
    else do
      let conta = fromJust maybeConta
      print conta
      putStrLn "A conversão funcionou."
```

Neste exemplo, o uso de `fromJust` no ramo `else` é seguro porque a própria condição já verificou que a estrutura `Maybe` não é vazia.

As funções `isNothing` e `fromJust` devem ser importadas do módulo `Data.Maybe`:

```haskell
import Data.Maybe (isNothing, fromJust)
```

A função `gorjeta` pode ser definida com equações com guardas, como nas atividades anteriores. Por exemplo, uma das guardas pode verificar se o valor da conta é negativo; outras guardas podem verificar as qualidades válidas (`"ruim"`, `"bom"` e `"excelente"`).

Para formatar valores monetários com duas casas decimais, use a função `printf`, importada do módulo `Text.Printf`:

```haskell
import Text.Printf (printf)
```

Em Haskell, `printf` é uma função de formatação. Quando indicamos que o resultado esperado é uma `String`, ela se comporta de modo semelhante à função `sprintf` da linguagem C: em vez de imprimir diretamente na tela, ela produz uma string formatada.

Por exemplo:

```haskell
linhaGorjeta :: String
linhaGorjeta = printf "Gorjeta: R$ %.2f\n" valorGorjeta
```

Depois disso, você pode imprimir a string com `putStr`:

```haskell
putStr linhaGorjeta
```

Também é possível combinar as duas etapas em uma única linha:

```haskell
putStr (printf "Total a pagar: R$ %.2f\n" total :: String)
```

O especificador `%.2f` indica que o número deve ser mostrado com duas casas decimais. O `\n` no final representa uma quebra de linha.

## Exemplos de execução

```shellsession
Digite o valor da conta: 100.0
Qualidade do serviço (ruim, bom, excelente): bom
Gorjeta: R$ 10.00
Total a pagar: R$ 110.00
```

```shellsession
Digite o valor da conta: 200.0
Qualidade do serviço (ruim, bom, excelente): excelente
Gorjeta: R$ 30.00
Total a pagar: R$ 230.00
```

```shellsession
Digite o valor da conta: 75.50
Qualidade do serviço (ruim, bom, excelente): ruim
Gorjeta: R$ 3.78
Total a pagar: R$ 79.28
```

```shellsession
Digite o valor da conta: 150.0
Qualidade do serviço (ruim, bom, excelente): medio
Entrada inválida!
```

```shellsession
Digite o valor da conta: abc
Entrada inválida!
```

## Como testar

Você pode editar os arquivos fonte em um editor de texto e testá-los com Cabal:

```shellsession
$ cabal build         # compila o projeto
$ cabal repl gorjetas # abre o GHCi com o módulo da atividade carregado
$ cabal run gorjetas  # executa o programa interativo
$ cabal test          # executa os testes automáticos
```

O projeto será corrigido automaticamente pelo GitHub Classroom. Seu código deve passar em todos os testes fornecidos.
