module TextAnalysis.Statistics
  ( basicStats
  ) where

import Data.List (nub)

import TextAnalysis.Normalize (normalizeText)
import TextAnalysis.Types (TextStats(..))

-- | Calcula as estatísticas básicas de um texto.
--
-- A contagem de caracteres deve usar o texto original.
-- As contagens de palavras e palavras distintas devem usar o texto
-- normalizado por 'normalizeText'.
basicStats :: String -> TextStats
basicStats text = TextStats
  { lineCount         = length (lines text)
  , wordCount         = length normWords
  , charCount         = length text
  , distinctWordCount = length (nub normWords)
  }
  where
    normWords = normalizeText text