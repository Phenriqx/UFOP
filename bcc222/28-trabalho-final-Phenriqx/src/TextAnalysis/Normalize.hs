module TextAnalysis.Normalize
  ( normalizeChar
  , normalizeWord
  , normalizeText
  ) where

import Data.Char (isAlphaNum, isSpace, toLower)

-- | Remove acentos e diacríticos mantendo os caracteres base.
removeAccents :: Char -> Char
removeAccents c = case c of
  'á' -> 'a'; 'à' -> 'a'; 'ã' -> 'a'; 'â' -> 'a'; 'ä' -> 'a'
  'é' -> 'e'; 'ê' -> 'e'; 'ë' -> 'e'
  'í' -> 'i'; 'î' -> 'i'; 'ï' -> 'i'
  'ó' -> 'o'; 'ô' -> 'o'; 'õ' -> 'o'; 'ö' -> 'o'
  'ú' -> 'u'; 'ü' -> 'u'
  'ç' -> 'c'
  'Á' -> 'a'; 'À' -> 'a'; 'Ã' -> 'a'; 'Â' -> 'a'; 'Ä' -> 'a'
  'É' -> 'e'; 'Ê' -> 'e'; 'Ë' -> 'e'
  'Í' -> 'i'; 'Î' -> 'i'; 'Ï' -> 'i'
  'Ó' -> 'o'; 'Ô' -> 'o'; 'Õ' -> 'o'; 'Ö' -> 'o'
  'Ú' -> 'u'; 'Ü' -> 'u'
  'Ç' -> 'c'
  _   -> c

-- | Normaliza um caractere.
--
-- Regras esperadas:
--
-- * letras e dígitos são preservados em minúsculas;
-- * espaços continuam sendo espaços;
-- * sinais de pontuação simples são convertidos em espaço.
--
-- Essa decisão faz com que, por exemplo, "Haskell!" e "haskell"
-- sejam tratados como a mesma palavra.
normalizeChar :: Char -> Char
normalizeChar c
  | isAlphaNum c = toLower c
  | isSpace c    = c
  | otherwise    = ' '
-- | Normaliza uma palavra isolada.
--
-- A função deve converter a palavra para minúsculas e remover caracteres
-- que não sejam letras nem dígitos.
--
-- Exemplos esperados:
--
-- >>> normalizeWord "Haskell!"
-- "haskell"
--
-- >>> normalizeWord "2026."
-- "2026"
normalizeWord :: String -> String
normalizeWord = map toLower . filter isAlphaNum

-- | Normaliza um texto completo e retorna a lista de palavras normalizadas.
--
-- A lista resultante não deve conter palavras vazias.
--
-- Exemplo esperado:
--
-- >>> normalizeText "Haskell, Haskell! Funções."
-- ["haskell","haskell","funções"]
normalizeText :: String -> [String]
normalizeText = words . map normalizeChar