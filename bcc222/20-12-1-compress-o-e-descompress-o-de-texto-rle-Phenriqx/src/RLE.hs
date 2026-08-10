module RLE
  ( comprime,
    descomprime,
    main,
  )
where

import Data.List (group)
import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)
import Text.Read (readMaybe)

-- | Comprime uma string em uma lista de pares (caractere, contagem).
comprime :: String -> [(Char, Int)]
comprime texto = [ (x, length bloco) | bloco@(x:_) <- group texto ]

-- | Descomprime uma lista de pares para uma string.
-- Retorna Nothing se a lista contiver uma contagem inválida (<= 0).
descomprime :: [(Char, Int)] -> Maybe String
descomprime [] = Just ""
descomprime ((c, n):xs)
  | n <= 0    = Nothing
  | otherwise = case descomprime xs of
                  Nothing   -> Nothing
                  Just rest -> Just (replicate n c ++ rest)

-- | Ação principal que implementa o menu interativo.
main :: IO ()
main = do
  -- Desativa o buffering do stdout para garantir que os prints apareçam antes dos gets
  hSetBuffering stdout NoBuffering
  loopMenu

-- | Laço recursivo que gerencia o fluxo de controle do menu.
loopMenu :: IO ()
loopMenu = do
  putStrLn "-- Menu --"
  putStrLn "1) Comprimir"
  putStrLn "2) Descomprimir"
  putStrLn "*) Sair"
  putStr "Opção: "
  opcao <- getLine
  case opcao of
    "1" -> do
      fluxoCompressao
      loopMenu
    "2" -> do
      fluxoDescompressao
      loopMenu
    _   -> return () -- Encerra o programa graciosamente

-- | Executa os passos específicos para a opção de compressão.
fluxoCompressao :: IO ()
fluxoCompressao = do
  putStr "Digite o texto para comprimir: "
  texto <- getLine
  let resultado = comprime texto
  putStrLn $ "Resultado: " ++ show resultado

  -- Verificação (ida e volta): descomprime (comprime texto) == Just texto
  case descomprime resultado of
    Just verificado | verificado == texto -> putStrLn "Verificação (ida e volta): OK"
    _                                     -> putStrLn "Verificação (ida e volta): FALHOU"

-- | Executa os passos específicos para a opção de descompressão.
fluxoDescompressao :: IO ()
fluxoDescompressao = do
  putStr "Digite a lista de pares: "
  entrada <- getLine
  case readMaybe entrada :: Maybe [(Char, Int)] of
    Nothing   -> putStrLn "Entrada da lista inválida."
    Just lista -> case descomprime lista of
      Nothing -> putStrLn "Resultado da descompressão: Falha (dados inválidos)"
      Just str -> do
        putStrLn $ "Resultado: " ++ show str
        if comprime str == lista
          then putStrLn "Verificação (ida e volta): OK"
          else putStrLn "Verificação (ida e volta): FALHOU"
