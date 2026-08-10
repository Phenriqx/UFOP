[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/3vx6JO_-)
# Atividade 18.1: classes de formas

Nesta atividade, você deve implementar uma pequena biblioteca de formas geométricas usando uma classe de tipos própria.

O objetivo é praticar:

- declaração de uma classe;
- implementação de instâncias;
- uso de um método com implementação padrão;
- escrita de funções polimórficas com restrições de classe.

## Tarefa

Abra o arquivo `src/Atividade/ClassesDeFormas.hs` e substitua as definições marcadas com `undefined`.

A classe principal da atividade é:

```haskell
class TemArea a where
  area :: a -> Double

  areaEhMaiorQue :: a -> Double -> Bool
  areaEhMaiorQue x limite = area x > limite
```

Você deve implementar instâncias de `TemArea` para os seguintes tipos:

```haskell
data Circulo = Circulo Double
data Retangulo = Retangulo Double Double
data Triangulo = Triangulo Double Double
```

As medidas devem ser interpretadas da seguinte forma:

- `Circulo r`: círculo de raio `r`;
- `Retangulo largura altura`: retângulo de largura `largura` e altura `altura`;
- `Triangulo base altura`: triângulo de base `base` e altura `altura`.

Além disso, implemente as funções:

```haskell
areaTotal :: TemArea a => [a] -> Double
maioresQue :: TemArea a => Double -> [a] -> [a]
resumoAreas :: TemArea a => [a] -> [Double]
```

## Comandos úteis

Para compilar:

```bash
cabal build all
```

Para executar os testes:

```bash
cabal test all --test-show-details=direct
```

Para executar o programa de exemplo:

```bash
cabal run
```

## Observação

A função `pi` já está disponível no `Prelude` e pode ser usada para calcular a área do círculo.
