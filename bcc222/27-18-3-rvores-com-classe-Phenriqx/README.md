[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/q7fDFKNZ)
# Atividade 18.3: árvores com classes

Nesta atividade, você deve implementar instâncias com restrições para uma árvore binária e declarar uma classe própria para estruturas que podem ser mapeadas.

O objetivo é praticar:

- instâncias condicionais, como `Eq a => Eq (BinTree a)`;
- instâncias de `Show` e `Ord` para um tipo parametrizado;
- declaração de uma classe própria;
- implementação de uma instância para um construtor de tipos.

## Tarefa

Abra o arquivo `src/Atividade/ArvoresComClasses.hs` e substitua as definições marcadas com `undefined`.

O tipo usado na atividade é:

```haskell
data BinTree a
  = Empty
  | Node a (BinTree a) (BinTree a)
```

Você deve implementar as funções:

```haskell
tamanho :: BinTree a -> Int
altura :: BinTree a -> Int
emOrdem :: BinTree a -> [a]
```

Depois, implemente as instâncias:

```haskell
Eq a => Eq (BinTree a)
Show a => Show (BinTree a)
Ord a => Ord (BinTree a)
```

Por fim, implemente a classe própria:

```haskell
class Mapeavel t where
  mapear :: (a -> b) -> t a -> t b
```

e sua instância para `BinTree`.

## Convenções desta atividade

Use as seguintes convenções:

- `tamanho` conta a quantidade de nós não vazios;
- `altura Empty == 0`;
- `altura (Node _ Empty Empty) == 1`;
- `emOrdem` percorre primeiro a subárvore esquerda, depois a raiz, depois a subárvore direita;
- a instância de `Eq` deve comparar a estrutura e os valores;
- a instância de `Ord` deve comparar as listas produzidas por `emOrdem`;
- a instância de `Show` deve seguir exatamente o formato testado pela suíte de testes.

A classe `Mapeavel` antecipa uma ideia que será estudada com mais profundidade posteriormente. Nesta atividade, ela deve ser tratada apenas como uma classe própria com um método sobrecarregado.

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
