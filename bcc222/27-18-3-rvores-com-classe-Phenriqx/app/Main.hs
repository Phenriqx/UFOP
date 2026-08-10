module Main (main) where

import Atividade.ArvoresComClasses

main :: IO ()
main = do
  let arv =
        Node 2
          (Node 1 Empty Empty)
          (Node 3 Empty Empty)
  putStrLn "Árvore:"
  print arv
  putStrLn "Percurso em ordem:"
  print (emOrdem arv)
  putStrLn "Árvore mapeada:"
  print (mapear (* 10) arv)
