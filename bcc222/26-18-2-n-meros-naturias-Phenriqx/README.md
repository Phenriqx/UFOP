[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/_X_qirT0)
# Atividade 18.2: números naturais

Nesta atividade, você deve implementar um tipo para números naturais e fornecer instâncias de classes predefinidas.

O objetivo é praticar:

- instâncias de `Eq`, `Ord` e `Show`;
- instância de `Num` para operações aritméticas;
- instância de `Enum`;
- instâncias de `Real` e `Integral`, incluindo quociente e resto.

## Tarefa

Abra o arquivo `src/Atividade/NumerosNaturais.hs` e substitua as definições marcadas com `undefined`.

O tipo usado na atividade é:

```haskell
data Nat = Zero | Succ Nat
```

Essa representação segue a ideia dos naturais de Peano:

- `Zero` representa 0;
- `Succ Zero` representa 1;
- `Succ (Succ Zero)` representa 2;
- e assim por diante.

Você deve implementar as funções auxiliares:

```haskell
natToInteger :: Nat -> Integer
integerToNat :: Integer -> Nat
```

Depois, implemente instâncias para:

```haskell
Eq Nat
Ord Nat
Show Nat
Num Nat
Enum Nat
Real Nat
Integral Nat
```

## Convenções desta atividade

Use as seguintes convenções:

- `integerToNat` deve rejeitar inteiros negativos com erro;
- `fromInteger` deve usar `integerToNat`;
- a subtração em `Nat` deve ser truncada em `Zero`, isto é, `2 - 5 == 0`;
- divisão por zero pode produzir erro;
- `show` deve exibir o número em base decimal, por exemplo, `show (Succ (Succ Zero)) == "2"`.

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
