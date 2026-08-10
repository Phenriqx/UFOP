[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/OA-E1Hzo)
# Condicionais

Atividade prática do capítulo 5: **Expressão condicional**.

Nesta atividade, você deverá implementar **três funções puras em Haskell**, cada uma em seu próprio módulo, aplicando os conceitos estudados no capítulo:

- expressões `if-then-else`;
- equações com guardas;
- definições locais com `where`.

## Organização do projeto

Você deve editar **apenas** os arquivos em `src/Condicionais/`:

- `src/Condicionais/CalculaFrete.hs`
- `src/Condicionais/ValorFinal.hs`
- `src/Condicionais/ValorPremio.hs`

Cada exercício possui um conjunto próprio de testes automatizados.

## Como testar

Para executar todos os testes:

```bash
cabal test all
```

Para executar os testes de um exercício específico:

```bash
cabal test test-calcula-frete
cabal test test-valor-final
cabal test test-valor-premio
```

## Exercício 1 — cálculo de frete

Arquivo: `src/CalculaFrete.hs`

Uma transportadora contratou você para implementar parte do sistema de cálculo de fretes. O valor cobrado depende do peso do pacote e da modalidade escolhida pelo cliente. Para manter o sistema simples, nesta atividade você não deverá lidar com entradas e saídas interativas: o seu trabalho é apenas definir a função que calcula o valor do frete.

Implemente a função:

```haskell
calculaFrete :: Float -> String -> Float
```

A função recebe:

- o peso do pacote, em quilogramas;
- o tipo de entrega, que pode ser `"Normal"` ou `"Expressa"`.

Regras:

1. o valor base do frete depende do peso:
   - até 1 kg: R$ 15,00;
   - acima de 1 kg e até 10 kg: R$ 25,00;
   - acima de 10 kg: R$ 40,00;
2. se o tipo de entrega for `"Expressa"`, deve ser aplicado um acréscimo de 30% sobre o valor base;
3. a função deve retornar o valor final do frete.

Exemplos:

```haskell
calculaFrete 0.8 "Normal"     == 15.0
calculaFrete 2.5 "Expressa"   == 32.5
calculaFrete 12.0 "Normal"    == 40.0
calculaFrete 12.0 "Expressa"  == 52.0
```

## Exercício 2 — valor final da compra por região

Arquivo: `src/ValorFinal.hs`

Uma loja virtual vende seus produtos para várias regiões do Brasil. O preço final da compra depende da região de entrega, pois cada região possui uma taxa diferente. Para estimular as vendas, compras acima de R$ 5000,00 são isentas dessa taxa.

Nesta atividade, você deverá implementar somente a função que calcula o valor final da compra.

Implemente a função:

```haskell
valorFinal :: Int -> Float -> Float
```

A função recebe:

- um código inteiro de região;
- o valor da compra.

Os códigos e taxas são:

- `1` → Centro-Oeste → 8%
- `2` → Nordeste → 6%
- `3` → Norte → 3%
- `4` → Sudeste → 12%
- `5` → Sul → 15%

Regras:

1. se o valor da compra for **maior** que R$ 5000,00, nenhuma taxa é aplicada;
2. caso contrário, deve ser aplicada a taxa correspondente à região;
3. a função retorna o valor final da compra.

Considere que os argumentos fornecidos à função são sempre válidos.

Exemplos:

```haskell
valorFinal 4 1000.0    == 1120.0
valorFinal 2 5879.87   == 5879.87
valorFinal 1 2000.0    == 2160.0
valorFinal 3 5000.0    == 5150.0
```

## Exercício 3 — valor do prêmio no caça-níqueis

Arquivo: `src/ValorPremio.hs`

Uma máquina de caça-níqueis possui três cilindros. Depois de uma aposta, cada cilindro para mostrando uma fruta. O valor devolvido ao jogador depende da quantidade de bananas que aparece na combinação. Se mais de uma regra puder ser aplicada, apenas o maior prêmio deve ser considerado.

Implemente a função:

```haskell
valorPremio :: Char -> Char -> Char -> Float -> Float
```

A função recebe:

- três caracteres representando as frutas mostradas nos cilindros:
  - `'a'` → abacaxi
  - `'b'` → banana
  - `'m'` → morango
  - `'u'` → uva
- o valor da aposta.

Regras de premiação:

- 3 bananas → devolve 10 vezes o valor da aposta;
- 2 bananas em qualquer posição → devolve 5 vezes o valor da aposta;
- 1 banana em qualquer posição → devolve o valor da aposta;
- nenhuma banana → devolve `0`.

Exemplos:

```haskell
valorPremio 'a' 'm' 'b' 8.0    == 8.0
valorPremio 'b' 'm' 'b' 5.5    == 27.5
valorPremio 'm' 'm' 'a' 50.0   == 0.0
valorPremio 'b' 'b' 'b' 100.0  == 1000.0
```

## Observações

- Considere que os valores de entrada fornecidos aos testes são sempre válidos.
- Procure escrever definições claras e bem organizadas.
- Sempre que fizer sentido, use guardas e definições locais com `where` ou `let`.
- O foco é a definição correta das funções pedidas.
