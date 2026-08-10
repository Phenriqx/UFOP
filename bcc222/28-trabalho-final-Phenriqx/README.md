[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/qq80G6BW)
# Projeto final: Analisador de frequência de texto

## Visão geral

Neste projeto, você deverá implementar uma ferramenta de linha de comando em Haskell para analisar arquivos de texto.

O programa deverá ler um arquivo textual, calcular estatísticas básicas e apresentar um ranking das palavras mais frequentes. O objetivo principal é aplicar, de forma integrada, conceitos de programação funcional estudados durante o semestre, especialmente:

- definição de funções puras;
- decomposição de problemas;
- listas;
- recursão ou funções de alta ordem;
- tipos algébricos e registros;
- separação entre processamento puro e entrada/saída;
- uso básico de Cabal.

A entrega é individual e deverá ser realizada pelo GitHub Classroom.

## Data de entrega

A entrega final deverá ser feita até **22 de julho de 2026**.

Não haverá entregas parciais obrigatórias.

## O que deve ser entregue

Você deverá entregar:

1. O código completo no repositório do GitHub Classroom.
2. Um relatório curto, preenchendo o arquivo `relatorio/RELATORIO.md`.
3. Um vídeo de apresentação com duração entre **4 e 7 minutos**.

No vídeo, você deve mostrar o rosto e a tela do computador, explicando os pontos principais do trabalho.

## Estrutura do repositório

O repositório já contém a estrutura básica do projeto. Você não precisa criar o projeto Cabal do zero.

```text
.
├── app/
│   └── Main.hs
├── src/
│   └── TextAnalysis/
│       ├── Types.hs
│       ├── Normalize.hs
│       ├── Statistics.hs
│       ├── Frequency.hs
│       └── Report.hs
├── test/
│   └── MainSpec.hs
├── dados/
│   └── exemplo.txt
├── relatorio/
│   └── RELATORIO.md
├── analisador-texto.cabal
├── cabal.project
└── README.md
```

Você deverá completar as funções marcadas com `TODO` nos módulos de `src/`.

## Importante sobre os testes

Você não precisa criar testes Hspec.

Os testes já estão prontos no arquivo:

```text
test/MainSpec.hs
```

Sua tarefa é implementar as funções solicitadas para que os testes passem.

Para executar os testes, use:

```bash
cabal test
```

## Como executar o projeto

Para executar o programa com o arquivo de exemplo, use:

```bash
cabal run analisador-texto -- dados/exemplo.txt
```

Por padrão, o programa deve mostrar as 10 palavras mais frequentes.

Também é possível informar o tamanho do ranking com `--top`:

```bash
cabal run analisador-texto -- dados/exemplo.txt --top 5
```

## Funcionalidades mínimas

Para aprovação no projeto, sua implementação deverá conter as funcionalidades descritas a seguir.

### Leitura de arquivo texto

A aplicação deve receber o caminho de um arquivo texto como argumento de linha de comando e ler seu conteúdo.

Exemplo:

```bash
cabal run analisador-texto -- dados/exemplo.txt
```

Caso o arquivo não possa ser lido, a aplicação deve exibir uma mensagem de erro adequada.

### Estatísticas básicas

A aplicação deve calcular e exibir:

- número de linhas;
- número de palavras;
- número de caracteres;
- número de palavras distintas.

As contagens devem ser implementadas por funções puras, testáveis separadamente da parte de entrada e saída.

### Normalização de palavras

A aplicação deve implementar uma etapa de normalização textual. No mínimo, ela deve:

- converter letras maiúsculas para minúsculas;
- remover pontuação simples;
- separar o texto em palavras.

Por exemplo, as ocorrências `Haskell`, `haskell` e `Haskell!` devem ser tratadas como a mesma palavra normalizada.

### Frequência de palavras

A aplicação deve calcular quantas vezes cada palavra normalizada aparece no texto.

Você pode usar listas de pares, recursão, funções de alta ordem ou outras estratégias estudadas na disciplina. Caso use alguma estrutura ou função que não tenha sido discutida em aula, explique a decisão no relatório.

### Ranking das palavras mais frequentes

A aplicação deve exibir as palavras mais frequentes do texto em ordem decrescente de frequência.

Em caso de empate, as palavras devem ser ordenadas alfabeticamente.

### Organização modular

O módulo `Main` deve conter apenas a lógica de execução da aplicação, isto é, leitura de argumentos, leitura do arquivo e impressão do relatório.

A maior parte do processamento textual deve ser implementada nos módulos de `src/`, especialmente em funções puras.

Evite concentrar toda a solução em `app/Main.hs`.

## Módulos do projeto

### `TextAnalysis.Types`

Contém tipos compartilhados pelo projeto, como `TextStats` e `FrequencyTable`.

### `TextAnalysis.Normalize`

Contém funções de normalização textual:

- `normalizeChar`;
- `normalizeWord`;
- `normalizeText`.

### `TextAnalysis.Statistics`

Contém a função:

- `basicStats`.

Essa função calcula as estatísticas básicas do texto.

### `TextAnalysis.Frequency`

Contém funções relacionadas à frequência de palavras:

- `countFrequencies`;
- `rankFrequencies`;
- `topFrequencies`.

### `TextAnalysis.Report`

Contém funções responsáveis por formatar o relatório textual:

- `formatStats`;
- `formatFrequency`;
- `buildReport`.

### `Main`

Contém a função `main`, responsável pela execução da aplicação.

## Funcionalidades extras

As funcionalidades extras são opcionais e podem contribuir para uma nota maior.

Algumas possibilidades:

- suporte a uma lista de palavras ignoradas;
- leitura de palavras ignoradas a partir de um arquivo;
- exportação do relatório para `.txt`, `.csv` ou `.md`;
- análise de bigramas;
- tratamento mais sofisticado de acentuação;
- melhoria visual do relatório no terminal.

Implemente funcionalidades extras apenas depois de concluir corretamente o núcleo mínimo do projeto.

## Critérios de avaliação

A avaliação será feita com base nos seguintes critérios.

### Correção funcional: 45%

Será avaliado se o programa implementa corretamente as funcionalidades mínimas:

- leitura de arquivo texto;
- estatísticas básicas;
- normalização textual;
- frequência de palavras;
- ranking das palavras mais frequentes;
- tratamento adequado de erros simples.

Parte dessa avaliação poderá ser automatizada pela execução dos testes fornecidos.

### Qualidade do código Haskell: 25%

Será avaliado se o código é claro, modular e idiomático.

Serão considerados:

- uso adequado de funções puras;
- separação entre processamento e entrada/saída;
- decomposição em funções pequenas;
- nomes claros para funções e variáveis;
- ausência de duplicação desnecessária;
- uso coerente dos tipos fornecidos.

### Uso correto do template e dos testes: 10%

Será avaliado se você respeitou a estrutura fornecida no template e manteve os nomes dos módulos e das funções especificadas.

A correção automática depende dessa interface. Portanto, não altere os nomes dos módulos, dos arquivos ou das funções públicas sem autorização do professor.

### Relatório: 10%

O relatório deve ter aproximadamente 2 a 4 páginas quando convertido para PDF ou visualizado em formato equivalente.

Ele deve explicar:

- o objetivo do projeto;
- a organização do código;
- as principais decisões de implementação;
- as funcionalidades implementadas;
- as dificuldades encontradas;
- o link do vídeo de apresentação.

### Vídeo de apresentação: 10%

O vídeo deve ter entre **4 e 7 minutos**.

No vídeo, apresente:

- o objetivo geral do projeto;
- a estrutura do repositório;
- as principais funções implementadas;
- uma execução do programa;
- a execução de `cabal test`;
- as funcionalidades extras implementadas, se houver.

O vídeo não deve ser apenas uma leitura do relatório. Ele deve demonstrar que você compreende a implementação entregue.

## Sugestão de roteiro para o vídeo

Uma organização possível é:

1. Apresentação breve do objetivo do projeto.
2. Explicação da estrutura do repositório.
3. Explicação das funções principais.
4. Execução do programa com `dados/exemplo.txt`.
5. Execução dos testes com `cabal test`.
6. Comentário sobre dificuldades e funcionalidades extras.

## Recomendações finais

Antes de entregar, verifique se:

- o projeto compila;
- `cabal test` executa corretamente;
- o relatório foi preenchido;
- o link do vídeo foi incluído no relatório;
- o vídeo tem entre 4 e 7 minutos;
- o repositório foi enviado pelo GitHub Classroom.
