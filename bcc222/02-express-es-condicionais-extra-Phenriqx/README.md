[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/uPozCj0g)
# Condicionais extra

Esta atividade extra-classe consolida o conteúdo do capítulo 5 do livro-texto, com foco em
**expressões condicionais**, **guardas** e **definições locais com `where`**.

A proposta é semelhante à atividade `condicionais`, mas com **outros exercícios**. Em todos eles,
você deve implementar **funções puras** em Haskell, sem usar entrada interativa de dados.

## Organização do projeto

Cada exercício está em seu próprio módulo dentro de `src/`. Você deve completar as definições
pedidas nos arquivos:

- `src/ClassificaAno.hs`
- `src/PrecoTransmissao.hs`
- `src/AnalisaVulnerabilidade.hs`

Os testes automáticos estão em `test/`. Para verificar sua solução localmente, execute:

```bash
cabal test
```

Você também pode executar apenas os testes de um exercício:

```bash
cabal test test-classifica-ano
cabal test test-preco-transmissao
cabal test test-analisa-vulnerabilidade
```

---

## Exercício 1 — Classificação de ano

Em calendários civis, algumas regras são usadas para classificar anos como **bissextos** e/ou
**seculares**. Nesta atividade, considere as seguintes regras, na ordem de prioridade em que
devem ser aplicadas:

1. Anos múltiplos de 400 são **bissextos e seculares**.
2. Anos múltiplos de 100 são **apenas seculares**.
3. Anos múltiplos de 4 são **apenas bissextos**.
4. Todos os demais são **anos comuns**.

Implemente a função:

```haskell
classificaAno :: Int -> String
```

Ela recebe um ano positivo e deve retornar **exatamente** uma das seguintes classificações:

- `"bissexto e secular"`
- `"apenas secular"`
- `"apenas bissexto"`
- `"ano comum"`

### Exemplos

```haskell
classificaAno 1600 == "bissexto e secular"
classificaAno 1500 == "apenas secular"
classificaAno 1504 == "apenas bissexto"
classificaAno 1703 == "ano comum"
```

### Observação

A ordem das regras é importante. Por exemplo, um ano múltiplo de 400 também é múltiplo de 100,
mas deve ser classificado pela **primeira** regra.

---

## Exercício 2 — Cobrança por transmissão de dados

Uma empresa cobra R$ 2,50 por gigabyte transmitido. Neste mês, há promoções com desconto para
quantidades acima de certos limites, conforme as seguintes regras:

- até 5 GB: não há desconto;
- acima de 5 GB e até 10 GB: aplica-se desconto de 4% **apenas** sobre os GB acima de 5;
- acima de 10 GB e até 20 GB: aplica-se desconto de 6% **apenas** sobre os GB acima de 10;
- acima de 20 GB e até 40 GB: aplica-se desconto de 8% **apenas** sobre os GB acima de 20;
- acima de 40 GB: aplica-se desconto de 10% sobre **todos** os GB.

Além disso, uma quantidade de GB só é considerada válida se for **estritamente positiva**.

Implemente as funções:

```haskell
quantidadeValida :: Double -> Bool
precoTransmissao :: Double -> Double
```

### Requisitos

- `quantidadeValida` deve retornar `True` se a quantidade for maior que zero, e `False` caso
  contrário.
- `precoTransmissao` deve calcular o valor cobrado **assumindo que a quantidade fornecida é
  válida**.

### Exemplos

```haskell
quantidadeValida 10.0 == True
quantidadeValida 0.0  == False
quantidadeValida (-3) == False

precoTransmissao 5.0  == 12.5
precoTransmissao 10.0 == 24.5
precoTransmissao 38.0 == 91.4
precoTransmissao 50.0 == 112.5
```

### Observação

Leia com atenção as regras de desconto. Nas três primeiras promoções, o desconto não vale para
todos os gigabytes, mas apenas para a parte que ultrapassa o limite indicado.

---

## Exercício 3 — Análise de vulnerabilidade

A Defesa Civil de uma cidade classifica o nível de vulnerabilidade de uma residência a partir de
um **valor de referência** entre `0` e `1`. Para esta atividade, considere a seguinte tabela:

| Valor de referência | Classe de vulnerabilidade | Ação de remoção          | Ajuda de custo |
| --- | --- | --- | --- |
| `0 <= v < 0.2` | Muito baixa | Nenhuma ação de remoção | `0` |
| `0.2 <= v < 0.4` | Baixa | Nenhuma ação de remoção | `0` |
| `0.4 <= v < 0.6` | Média | Remoção em uma semana | `1000` |
| `0.6 <= v < 0.8` | Alta | Remoção em dois dias | `3000` |
| `0.8 <= v <= 1` | Muito alta | Remoção imediata | `5000` |

Implemente as funções:

```haskell
classeVulnerabilidade :: Double -> String
acaoRemocao :: Double -> String
ajudaCusto :: Double -> Double
```

### Requisitos

Para esta atividade, você pode assumir que o valor recebido pelas funções está sempre no intervalo
`[0,1]`.

As funções devem retornar **exatamente** os seguintes textos:

- `classeVulnerabilidade`:
  - `"Muito baixa"`
  - `"Baixa"`
  - `"Média"`
  - `"Alta"`
  - `"Muito alta"`

- `acaoRemocao`:
  - `"Nenhuma ação de remoção"`
  - `"Remoção em uma semana"`
  - `"Remoção em dois dias"`
  - `"Remoção imediata"`

### Exemplos

```haskell
classeVulnerabilidade 0.10 == "Muito baixa"
classeVulnerabilidade 0.55 == "Média"
classeVulnerabilidade 0.95 == "Muito alta"

acaoRemocao 0.10 == "Nenhuma ação de remoção"
acaoRemocao 0.70 == "Remoção em dois dias"
acaoRemocao 1.00 == "Remoção imediata"

ajudaCusto 0.10 == 0
ajudaCusto 0.55 == 1000
ajudaCusto 0.95 == 5000
```

### Observação

As três funções usam a **mesma divisão por faixas**. Tente escrever definições claras e
consistentes entre si.
