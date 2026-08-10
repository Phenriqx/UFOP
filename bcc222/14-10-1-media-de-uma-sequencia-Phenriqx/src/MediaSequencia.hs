module MediaSequencia
  ( calculaMedia,
    lerNumeros,
    main,
  )
where

import System.IO (BufferMode (NoBuffering), hFlush, hSetBuffering, stdout)
import Text.Printf (printf)
import Text.Read (readMaybe)

-- | Calcula a média de uma lista de Doubles.
-- Retorna 0.0 para uma lista vazia.
calculaMedia :: [Double] -> Double
calculaMedia xs
  | null xs   = 0.0
  | otherwise = sum xs / fromIntegral (length xs)

-- | Lê n Doubles da entrada padrão e os retorna em uma lista.
-- Retorna uma lista vazia se n <= 0.
lerNumeros :: Int -> IO [Double]
lerNumeros n
  | n <= 0    = return []
  | otherwise = do
      putStr "Digite um número: "
      input <- getLine
      let numero = read input :: Double
      resto <- lerNumeros (n - 1)
      return (numero : resto)

-- | Ação principal que orquestra o programa.
main :: IO ()
main = do
  -- Configura o buffering para garantir a interatividade no terminal
  hSetBuffering stdout NoBuffering

  putStr "Quantidade de números a serem lidos: "
  inputQtd <- getLine
  let n = read inputQtd :: Int

  -- Chamada da ação de leitura
  numeros <- lerNumeros n

  -- Cálculo da média com a função pura
  let media = calculaMedia numeros

  -- Exibição formatada conforme os requisitos
  printf "A média dos números é: %.2f\n" media
