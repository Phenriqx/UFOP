module Main (main) where

import Atividade.ClassesDeFormas

main :: IO ()
main = do
  let formas = [Retangulo 2 3, Retangulo 4 5, Retangulo 1 1]
  putStrLn "Áreas dos retângulos:"
  print (resumoAreas formas)
  putStrLn "Área total:"
  print (areaTotal formas)
