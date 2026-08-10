module TextAnalysis.Frequency
  ( countFrequencies
  , rankFrequencies
  , topFrequencies
  , filterStopwords
  ) where

import Data.List (sortBy, group, sort)

import TextAnalysis.Types (FrequencyTable)

-- Lista padrão de stop words em português
defaultStopwords :: [String]
defaultStopwords =
  [ "a", "o", "as", "os", "um", "uma", "uns", "umas"
  , "de", "do", "da", "dos", "das"
  , "em", "no", "na", "nos", "nas"
  , "por", "pelo", "pela", "pelos", "pelas"
  , "com", "para", "que", "e", "ou", "se", "como"
  ]

-- Conta a frequência de cada palavra em uma lista já normalizada.
filterStopwords :: [String] -> [String]
filterStopwords = filter (`notElem` defaultStopwords)

-- | Conta a frequência de cada palavra em uma lista já normalizada.
--
-- A tabela retornada deve estar em ordem alfabética crescente de palavra,
-- para tornar o resultado determinístico antes do ranqueamento.
--
-- Exemplo:
--
-- >>> countFrequencies ["haskell", "função", "haskell"]
-- [("função",1),("haskell",2)]
countFrequencies :: [String] -> FrequencyTable
countFrequencies wordsList = map (\g -> (head g, length g)) (group (sort wordsList))

-- | Ordena uma tabela de frequências por frequência decrescente.
--
-- Em caso de empate, as palavras devem ser ordenadas alfabeticamente.
--
-- Exemplo:
--
-- >>> rankFrequencies [("b",2),("a",2),("c",1)]
-- [("a",2),("b",2),("c",1)]
rankFrequencies :: FrequencyTable -> FrequencyTable
rankFrequencies = sortBy compareFreq
  where
    compareFreq (w1, f1) (w2, f2) =
      case compare f2 f1 of
        EQ    -> compare w1 w2
        other -> other

-- | Retorna as @n@ palavras mais frequentes.
--
-- Se @n <= 0@, o resultado deve ser a lista vazia.
topFrequencies :: Int -> FrequencyTable -> FrequencyTable
topFrequencies n ft
  | n <= 0    = []
  | otherwise = take n ft