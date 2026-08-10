[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/KuwuJazX)
# Atividade: urna eletrônica

## Descrição

Nesta atividade, você desenvolverá um programa interativo em Haskell que simula o funcionamento básico de uma urna eletrônica. O programa deve coletar votos sequencialmente até receber o comando de encerramento. Ao final, deve exibir o boletim de urna com os totais.

Esta atividade exercita:

- ações de E/S recursivas;
- acumuladores para manter o estado da contagem de votos;
- atualização seletiva de acumuladores;
- condicionais para processar diferentes códigos de voto.

## Cenário

Está ocorrendo uma eleição para escolher o mascote do Laboratório de Programação Funcional.

Os candidatos são:

- `1`: Lambda
- `2`: Monad
- `3`: Curry

## Fluxo do programa

1. O programa inicia exibindo o menu de candidatos.
2. Em seguida, entra em um laço recursivo de leitura de votos.
3. A cada iteração, solicita que o eleitor digite o número do voto.
4. O comportamento deve seguir a tabela:

| Entrada | Ação do sistema |
| :---: | --- |
| `1` | Computa um voto para Lambda e reinicia o laço. |
| `2` | Computa um voto para Monad e reinicia o laço. |
| `3` | Computa um voto para Curry e reinicia o laço. |
| `0` | Encerra a votação e exibe o relatório final. |
| Outro número | Computa um voto nulo e reinicia o laço. |

Ao receber `0`, o programa deve exibir:

- total de votos para cada candidato;
- total de votos nulos;
- total geral de votos computados.

## Funções e ações a implementar

Complete a definição de `computaVotos` no arquivo `src/Urna.hs`. Não altere os nomes nem as assinaturas exportadas pelo módulo.

### `computaVotos :: Int -> Int -> Int -> Int -> IO ()`

Ação de E/S recursiva que recebe os contadores atuais de votos para Lambda, Monad, Curry e nulos.

### `main :: IO ()`

A ação `main` já configura o buffering, imprime o cabeçalho e chama `computaVotos` com os contadores zerados.

## Exemplo de execução

```shellsession
=== Urna Eletronica ===
Opcoes: [1] Lambda | [2] Monad | [3] Curry | [0] Encerrar

Digite o voto: 1
Voto computado para Lambda.

Digite o voto: 3
Voto computado para Curry.

Digite o voto: 5
Voto Nulo computado.

Digite o voto: 1
Voto computado para Lambda.

Digite o voto: 0

=== Boletim de Urna ===
Lambda: 2
Monad:  0
Curry:  1
Nulos:  1
-----------------------
Total:  4
```

## Desenvolvimento e testes

Compile, execute e teste o projeto com:

```shellsession
cabal build                   # Compila o projeto
cabal repl urna-eletronica    # Carrega o projeto no GHCi
cabal run urna-eletronica     # Executa o programa
cabal test                    # Executa os testes de verificação automática
```
