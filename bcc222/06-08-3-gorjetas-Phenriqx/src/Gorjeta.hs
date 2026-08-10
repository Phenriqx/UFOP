module Gorjeta (main, gorjeta) where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)
import Data.Maybe (isNothing, fromJust)
import Text.Printf (printf)
import Text.Read (readMaybe)

gorjeta :: Double -> String -> Maybe Double
gorjeta valor qualidade
  | valor < 0 = Nothing
  | qualidade == "ruim"      = Just (valor * 0.05)
  | qualidade == "bom"       = Just (valor * 0.10)
  | qualidade == "excelente" = Just (valor * 0.15)
  | otherwise                = Nothing

main :: IO ()
main = do
  hSetBuffering stdout NoBuffering

  putStr "Digite o valor da conta: "
  inputValor <- getLine

  let maybeValor = readMaybe inputValor :: Maybe Double

  if isNothing maybeValor
      then putStrLn "Entrada inválida!"
      else do
          let valorConta = fromJust maybeValor

          putStr "Qualidade do serviço (ruim, bom, excelente): "
          qualidade <- getLine

          let maybeGorjeta = gorjeta valorConta qualidade

          if isNothing maybeGorjeta
              then putStrLn "Entrada inválida!"
              else do
                  let valorGorjeta = fromJust maybeGorjeta
                  let total = valorConta + valorGorjeta

                  printf "Gorjeta: R$ %.2f\n" valorGorjeta
                  printf "Total a pagar: R$ %.2f\n" total
