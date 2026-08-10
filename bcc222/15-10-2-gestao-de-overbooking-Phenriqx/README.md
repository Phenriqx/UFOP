[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/jRSfaXtv)
# Atividade: gestão de overbooking

## Descrição

A companhia aérea Rotten Cocoa Airlines Corp. precisa de um sistema simples para processar dados de check-in e identificar situações de overbooking.

O programa deve solicitar a quantidade total de voos a serem processados. Para cada voo, deve ler dois valores inteiros: a capacidade da aeronave e a quantidade de passagens vendidas. Se a quantidade de passagens for maior que a capacidade, o programa deve emitir imediatamente o alerta:

```text
Alerta: Voo com overbooking!
```

Ao final, o programa deve exibir um relatório com:

1. o número total de voos com overbooking;
2. o total de passageiros excedentes somando todos os voos com overbooking.

Esta atividade exercita:

- ações de E/S recursivas;
- uso de múltiplos acumuladores;
- atualização de estado por passagem de parâmetros;
- condicionais dentro de blocos `do`.

## Funções e ações a implementar

Complete as definições no arquivo `src/Overbooking.hs`. Não altere os nomes nem as assinaturas exportadas pelo módulo.

### `loopProcessaVoos :: Int -> Int -> Int -> Int -> IO ()`

Ação de E/S recursiva que processa os voos.

Os argumentos representam:

1. número do voo atual;
2. quantidade total de voos;
3. acumulador para o número de voos com overbooking;
4. acumulador para o total de passageiros excedentes.

O caso base ocorre quando o número do voo atual ultrapassa o total de voos. Nesse caso, a ação deve imprimir o relatório final.

O caso recursivo deve processar um voo, imprimir o alerta quando necessário e chamar `loopProcessaVoos` com os acumuladores atualizados.

### `main :: IO ()`

Ação principal que:

1. configura o buffering de saída;
2. imprime o nome da companhia;
3. solicita a quantidade total de voos;
4. inicia o laço recursivo com os acumuladores zerados.

## Exemplos de execução

As mensagens devem ser exatamente as usadas nos exemplos e nos testes.

```shellsession
Rotten Cocoa Airlines Corp.
Informe a quantidade de voos: 2
Voo 1:
Capacidade da aeronave: 560
Quantidade de passagens: 550
Voo 2:
Capacidade da aeronave: 350
Quantidade de passagens: 400
Alerta: Voo com overbooking!
Fim da entrada dos voos:
Ocorreram 1 voos com overbooking
Ocorreram 50 passageiros acima da capacidade
```

```shellsession
Rotten Cocoa Airlines Corp.
Informe a quantidade de voos: 4
Voo 1:
Capacidade da aeronave: 100
Quantidade de passagens: 99
Voo 2:
Capacidade da aeronave: 100
Quantidade de passagens: 100
Voo 3:
Capacidade da aeronave: 100
Quantidade de passagens: 101
Alerta: Voo com overbooking!
Voo 4:
Capacidade da aeronave: 100
Quantidade de passagens: 102
Alerta: Voo com overbooking!
Fim da entrada dos voos:
Ocorreram 2 voos com overbooking
Ocorreram 3 passageiros acima da capacidade
```

## Desenvolvimento e testes

Compile, execute e teste o projeto com:

```shellsession
cabal build             # Compila o projeto
cabal repl overbooking  # Carrega o projeto no GHCi
cabal run overbooking   # Executa o programa
cabal test              # Executa os testes de verificação automática
```
