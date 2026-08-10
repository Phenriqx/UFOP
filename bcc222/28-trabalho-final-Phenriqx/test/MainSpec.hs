module Main (main) where

import Test.Hspec

import TextAnalysis.Frequency
  ( countFrequencies
  , rankFrequencies
  , topFrequencies
  )
import TextAnalysis.Normalize
  ( normalizeChar
  , normalizeText
  , normalizeWord
  )
import TextAnalysis.Report
  ( buildReport
  , formatFrequency
  , formatStats
  )
import TextAnalysis.Statistics (basicStats)
import TextAnalysis.Types (TextStats(..))

main :: IO ()
main = hspec $ do
  describe "TextAnalysis.Normalize" $ do
    it "converte letras maiúsculas para minúsculas" $ do
      normalizeChar 'H' `shouldBe` 'h'
      normalizeChar 'a' `shouldBe` 'a'

    it "converte pontuação simples em espaço" $ do
      normalizeChar '!' `shouldBe` ' '
      normalizeChar ',' `shouldBe` ' '
      normalizeChar '.' `shouldBe` ' '

    it "normaliza palavras removendo pontuação e mantendo dígitos" $ do
      normalizeWord "Haskell!" `shouldBe` "haskell"
      normalizeWord "Projeto-2026" `shouldBe` "projeto2026"

    it "normaliza um texto completo em palavras não vazias" $ do
      normalizeText "Haskell, Haskell! Funções." `shouldBe`
        ["haskell", "haskell", "funções"]

    it "separa palavras unidas por pontuação no texto completo" $ do
      normalizeText "map/filter.fold" `shouldBe`
        ["map", "filter", "fold"]

  describe "TextAnalysis.Statistics" $ do
    it "calcula estatísticas básicas de texto não vazio" $ do
      basicStats "Haskell\nHaskell funcional!\n" `shouldBe`
        TextStats
          { lineCount = 2
          , wordCount = 3
          , charCount = 27
          , distinctWordCount = 2
          }

    it "calcula estatísticas básicas de texto vazio" $ do
      basicStats "" `shouldBe`
        TextStats
          { lineCount = 0
          , wordCount = 0
          , charCount = 0
          , distinctWordCount = 0
          }

  describe "TextAnalysis.Frequency" $ do
    it "calcula frequências em ordem alfabética" $ do
      countFrequencies ["haskell", "função", "haskell", "map"] `shouldBe`
        [("função", 1), ("haskell", 2), ("map", 1)]

    it "ordena frequências por quantidade decrescente e palavra crescente" $ do
      rankFrequencies [("b", 2), ("a", 2), ("c", 1)] `shouldBe`
        [("a", 2), ("b", 2), ("c", 1)]

    it "retorna as n palavras mais frequentes" $ do
      topFrequencies 2 [("a", 5), ("b", 3), ("c", 1)] `shouldBe`
        [("a", 5), ("b", 3)]

    it "retorna lista vazia quando n não é positivo" $ do
      topFrequencies 0 [("a", 5), ("b", 3)] `shouldBe` []

  describe "TextAnalysis.Report" $ do
    it "formata estatísticas básicas contendo os valores principais" $ do
      let output =
            formatStats
              TextStats
                { lineCount = 2
                , wordCount = 5
                , charCount = 30
                , distinctWordCount = 4
                }

      output `shouldContain` "Linhas: 2"
      output `shouldContain` "Palavras: 5"
      output `shouldContain` "Caracteres: 30"
      output `shouldContain` "Palavras distintas: 4"

    it "formata frequências contendo palavra e quantidade" $ do
      let output = formatFrequency [("haskell", 3), ("map", 2)]

      output `shouldContain` "haskell"
      output `shouldContain` "3"
      output `shouldContain` "map"
      output `shouldContain` "2"

    it "constrói um relatório completo com estatísticas e ranking" $ do
      let output =
            buildReport
              TextStats
                { lineCount = 1
                , wordCount = 2
                , charCount = 15
                , distinctWordCount = 1
                }
              [("haskell", 2)]

      output `shouldContain` "Relatório"
      output `shouldContain` "Linhas: 1"
      output `shouldContain` "haskell"
