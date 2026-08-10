[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/P-Dm7nzh)
# Atividade: promoção de chocolates

## Descrição

Você implementará um programa interativo em Haskell para simular a compra de caixas de chocolate na rede Rotten Cocoa Market. O programa deve guiar um cliente através de um processo de compra que pode ser repetido várias vezes.

O valor unitário de uma caixa depende da quantidade adquirida:

| Quantidade de caixas | Preço por caixa |
| --- | ---: |
| Até 10 caixas | R$ 20,00 |
| Acima de 10 e até 30 | R$ 15,00 |
| Acima de 30 e até 60 | R$ 10,00 |
| Acima de 60 caixas | R$ 5,00 |

Se o cliente optar por pagar com Pix, recebe um desconto de 8% sobre o valor total da compra.

Esta atividade exercita:

- separação entre cálculo puro e interação com o usuário;
- ações de E/S recursivas controladas por uma resposta do usuário;
- uso de guardas para classificar faixas;
- formatação de valores monetários.

## Fluxo do programa

1. O programa imprime a mensagem inicial e pergunta se o cliente deseja comprar.
2. Se a resposta inicial for `n`, imprime `Fim das compras, obrigado!` e termina.
3. Se a resposta inicial for `s`, inicia o laço de compras.
4. Em cada iteração:
   - solicita a quantidade de caixas;
   - se a quantidade for inválida, imprime uma mensagem de erro;
   - se a quantidade for válida:
     - imprime o valor da compra sem desconto;
     - pergunta se o pagamento será feito com Pix;
     - se a resposta for `s`, imprime o valor com desconto;
   - pergunta se o cliente deseja comprar novamente.
5. Se a resposta para nova compra for `s`, o laço continua. Caso contrário, o programa imprime a mensagem final e termina.

## Funções e ações a implementar

Complete as definições no arquivo `src/Chocolates.hs`. Não altere os nomes nem as assinaturas exportadas pelo módulo.

### `calculaPreco :: Int -> Double`

Função pura que recebe a quantidade de caixas e retorna o valor total da compra sem desconto.

### `loopDeCompras :: IO ()`

Ação de E/S recursiva que implementa o laço principal de compras.

### `main :: IO ()`

Ação principal que imprime a mensagem de boas-vindas, pergunta se o cliente deseja comprar e inicia o laço quando necessário.

## Dicas

Para implementar a lógica de faixas, use guardas. Para ler a quantidade com mais robustez, `readMaybe` pode evitar que o programa aborte quando o usuário digita algo que não é um número.

Para exibir valores monetários com duas casas decimais, use `printf` do módulo `Text.Printf`.

## Exemplos de execução

**Exemplo 1 (Não compra):**
```shellsession
Rotten Cocoa Market
Informe se deseja comprar (s/n): n
Fim das compras, obrigado!
```

**Exemplo 2 (Compra simples, sem Pix):**
```shellsession
Rotten Cocoa Market
Informe se deseja comprar (s/n): s
Informe a quantidade de caixas: 10
Valor da compra: R$ 200.00
Informe pagamento com Pix (s/n): n
Informe se deseja comprar novamente (s/n): n
Fim das compras, obrigado!
```

**Exemplo 3 (Compra simples, com Pix):**
```shellsession
Rotten Cocoa Market
Informe se deseja comprar (s/n): s
Informe a quantidade de caixas: 30
Valor da compra: R$ 450.00
Informe pagamento com Pix (s/n): s
Valor da compra com Pix: R$ 414.00
Informe se deseja comprar novamente (s/n): n
Fim das compras, obrigado!
```

**Exemplo 4 (Fluxo complexo com erros):**
```shellsession
Rotten Cocoa Market
Informe se deseja comprar (s/n): s
Informe a quantidade de caixas: -8
ERRO: Quantidade inválida: -8
Informe se deseja comprar novamente (s/n): s
Informe a quantidade de caixas: 50
Valor da compra: R$ 500.00
Informe pagamento com Pix (s/n): s
Valor da compra com Pix: R$ 460.00
Informe se deseja comprar novamente (s/n): n
Fim das compras, obrigado!
```

## Desenvolvimento e testes

Compile, execute e teste o projeto com:

```shellsession
cabal build             # Compila o projeto
cabal repl chocolates   # Carrega o projeto no GHCi
cabal run chocolates    # Executa o programa
cabal test              # Executa os testes de verificação automática
```
