module TextAnalysis.Types
  ( TextStats(..)
  , FrequencyTable
  ) where

-- | Estatísticas básicas calculadas a partir de um texto.
--
-- Observação:
--
-- * 'lineCount' conta as linhas retornadas por 'lines'.
-- * 'wordCount' conta as palavras após normalização.
-- * 'charCount' conta os caracteres do texto original.
-- * 'distinctWordCount' conta as palavras distintas após normalização.
data TextStats = TextStats
  { lineCount :: Int
  , wordCount :: Int
  , charCount :: Int
  , distinctWordCount :: Int
  } deriving (Eq, Show)

-- | Tabela de frequências de palavras normalizadas.
--
-- Cada par tem a forma @(palavra, quantidade)@.
type FrequencyTable = [(String, Int)]
