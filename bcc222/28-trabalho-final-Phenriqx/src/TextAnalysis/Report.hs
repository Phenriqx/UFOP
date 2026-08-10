module TextAnalysis.Report
  ( formatStats
  , formatFrequency
  , buildReport
  , exportCSV
  ) where

import TextAnalysis.Types (FrequencyTable, TextStats(..))

-- | Formata as estatísticas básicas para exibição no terminal.
formatStats :: TextStats -> String
formatStats stats = unlines
  [ "Estatísticas Básicas:"
  , "--------------------"
  , "Linhas: " ++ show (lineCount stats)
  , "Palavras: " ++ show (wordCount stats)
  , "Caracteres: " ++ show (charCount stats)
  , "Palavras distintas: " ++ show (distinctWordCount stats)
  ]

-- | Formata uma tabela de frequência para exibição no terminal.
--
-- Cada linha deve conter a palavra e sua quantidade.
formatFrequency :: FrequencyTable -> String
formatFrequency ft = unlines (map (\(w, f) -> w ++ ": " ++ show f) ft)

-- | Constrói o relatório textual completo.
buildReport :: TextStats -> FrequencyTable -> String
buildReport stats ft =
  "Relatório de Análise de Texto\n"
  ++ "===========================\n\n"
  ++ formatStats stats
  ++ "\nRanking de Palavras:\n-------------------\n"
  ++ formatFrequency ft

-- | Exporta o ranking de frequências no formato CSV.
exportCSV :: FrequencyTable -> String
exportCSV ft = "palavra,frequencia\n" ++ unlines (map (\(w, f) -> w ++ "," ++ show f) ft)