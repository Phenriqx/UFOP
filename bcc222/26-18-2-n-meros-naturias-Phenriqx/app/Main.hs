module Main (main) where

import Atividade.NumerosNaturais

main :: IO ()
main = do
  let a = integerToNat 7
      b = integerToNat 3
  putStrLn "a:"
  print a
  putStrLn "b:"
  print b
  putStrLn "a + b:"
  print (a + b)
  putStrLn "a * b:"
  print (a * b)
  putStrLn "quotRem a b:"
  print (quotRem a b)
