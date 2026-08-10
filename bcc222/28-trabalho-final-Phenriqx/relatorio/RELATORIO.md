# Relatório do projeto final

## Identificação

- Nome: Pedro Henrique Menezes Féo de Castro
- Matrícula: 25.1.4017
- Disciplina: Programação Funcional
- Projeto: Analisador de frequência de texto
- Data de entrega: 22 de julho de 2026

## Descrição geral

O objetivo do projeto é construir uma ferramenta de linha de comando (CLI) em Haskell para realizar a análise estatística e de frequência de termos em arquivos de texto. O programa recebe o caminho de um arquivo, processa seu conteúdo textualmente de forma puramente funcional, calcula métricas básicas e devolve ao usuário um ranking ordenado das palavras mais frequentes, permitindo customizar o tamanho do ranking exibido via argumentos de linha de comando.

## Organização do código

O projeto foi dividido de forma modular, separando estritamente os efeitos colaterais de Entrada/Saída (I/O) das regras de negócio compostas por funções puras:

- `TextAnalysis.Types`: Define as estruturas de dados fundamentais compartilhadas pela aplicação, especificamente o registro `TextStats` (que armazena as contagens de linhas, palavras, caracteres e termos distintos) e o sinônimo de tipo `FrequencyTable`.
- `TextAnalysis.Normalize`: Contém a lógica de higienização do texto. Transforma caracteres maiúsculos em minúsculos, descarta pontuações substituindo-as por espaços e tokeniza o texto final.
- `TextAnalysis.Statistics`: Responsável por computar os metadados do texto bruto e do texto normalizado, populando o registro `TextStats`.
- `TextAnalysis.Frequency`: Implementa as funções de contagem de ocorrências e os algoritmos de ordenação e truncagem do ranking de frequências.
- `TextAnalysis.Report`: Centraliza a formatação e estilização das strings que compõem o relatório final exibido no terminal.
- `Main`: Ponto de entrada do programa. É o único módulo com efeitos colaterais (impuro). É responsável por interagir com o sistema operacional, ler os argumentos da CLI (`--top`), ler o arquivo do disco com tratamento de exceções e imprimir o relatório gerado.

## Principais decisões de implementação

Explique as escolhas feitas durante o desenvolvimento. Por exemplo:

Explique as escolhas feitas durante o desenvolvimento. Por exemplo:

- **Normalização do texto:** Para evitar que caracteres colados a pontuações quebrassem a tokenização (ex: `"Haskell!"` ou `"palavra,"`), a função `normalizeChar` foi mapeada sobre todo o texto transformando qualquer caractere não alfanumérico e não espaço em um caractere de espaço `' '`. Posteriormente, a função nativa `words` foi aplicada para segmentar a string em uma lista de palavras puras, eliminando strings vazias automaticamente.
- **Cálculo de frequências:** Utilizou-se a composição das funções nativas `group` e `sort` do módulo `Data.List`. Ao ordernar alfabeticamente a lista de palavras normalizadas com `sort`, termos idênticos são agrupados consecutivamente por `group`. A função `countFrequencies` então mapeia esses subgrupos transformando-os em pares do tipo `(palavra, comprimento_do_grupo)`.
- **Tratamento de empates no ranking:** Na função `rankFrequencies`, utilizou-se a ordenação customizada via `sortBy`. O comparador avalia prioritariamente a frequência de forma decrescente utilizando `compare f2 f1`. Caso haja igualdade (`EQ`), o critério de desempate chaveia para a ordem alfabética crescente das palavras através de `compare w1 w2`.
- **Uso de funções puras:** Toda a manipulação de dados foi feita de forma pura e testável. Funções como `map`, `filter`, `words`, `lines`, `nub`, `take` e funções de alta ordem (lambdas) guiaram o processamento sem mutação de estado.

## Funcionalidades implementadas

Marque as funcionalidades implementadas.

- [x] Leitura de arquivo texto
- [x] Estatísticas básicas
- [x] Normalização de palavras
- [x] Frequência de palavras
- [x] Ranking das palavras mais frequentes
- [x] Tratamento de erros simples
- [ ] Funcionalidades extras

## Funcionalidades extras

## Testes

Os testes automatizados foram executados localmente utilizando o framework Hspec integrado ao Cabal. Eles validam unitariamente as propriedades funcionais de cada módulo isolado do core puro da aplicação.

Os testes verificam:

* Se a normalização lida corretamente com maiúsculas, minúsculas, dígitos e pontuações complexas/unidas.
* Se o cálculo estatístico computa valores exatos para textos povoados e casos limite como arquivos vazios.
* Se a ordenação e desempate de tabelas de frequência se mantêm determinísticas.
* Se a formatação do relatório gera a string final contendo exatamente os rótulos esperados pela interface de avaliação.

Comando utilizado:

```bash
cabal test
```

## Dificuldades encontradas

A principal dificuldade inicial residiu na adequação milimétrica da formatação das strings geradas no módulo `TextAnalysis.Report` com as asserções estritas configuradas no arquivo `test/MainSpec.hs`. O framework de testes esperava rótulos de dados curtos e exatos (como `"Linhas: "`) e a presença explícita de um título `"Relatório"`. O problema foi solucionado analisando as falhas geradas pelo `cabal test`, ajustando as strings estáticas do código puro para coincidir exatamente com os padrões de busca (substring) exigidos pela correção automatizada do Hspec.

## Link do vídeo

Inclua aqui o link para o vídeo de apresentação.

https://drive.google.com/file/d/1FQwYiWlAfUVdw781c3j2vBGlgdK65UeY/view?usp=sharing