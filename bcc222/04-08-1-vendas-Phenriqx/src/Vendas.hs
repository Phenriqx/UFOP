module Vendas (main, valorTotal) where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout, NewlineMode (inputNL))
import Text.Printf (printf)
import Data.Monoid (Last(getLast))

valorTotal :: Double -> Double -> Double
valorTotal morangos macas = totalMorango + totalMaca
  where
    totalMorango = if morangos <= 5 then morangos * 8.5 else morangos * 7.2
    totalMaca    = if macas <= 5 then macas * 5.25 else macas * 4.75

main :: IO ()
main = do
  hSetBuffering stdout NoBuffering

  putStr "Digite a quantidade de morangos (em kg): "
  inputMorangos <- getLine
  let m = read inputMorangos :: Double

  putStr "Digite a quantidade de maçãs (em kg): "
  inputMacas <- getLine
  let a = read inputMacas :: Double

  if m < 0 || a < 0
        then putStrLn "Entrada inválida"
        else do
            let resultado = valorTotal m a
            printf "O valor total da compra é R$ %.2f\n" resultado