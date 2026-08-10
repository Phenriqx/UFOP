module Urna
  ( computaVotos,
    main,
  )
where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)
import Text.Printf (printf)

-- | Função principal de inicialização
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  putStrLn "=== Urna Eletronica ==="
  putStrLn "Opcoes: [1] Lambda | [2] Monad | [3] Curry | [0] Encerrar"
  putStrLn ""
  -- Inicia a recursão com contadores zerados
  computaVotos 0 0 0 0

-- | Ação recursiva que gerencia o estado da votação.
-- Recebe os contadores atuais: (v1, v2, v3, nulos)
computaVotos :: Int -> Int -> Int -> Int -> IO ()
computaVotos v1 v2 v3 nulos = do
  putStr "Digite o voto: "
  input <- getLine
  let voto = read input :: Int

  case voto of
    1 -> do
      putStrLn "Voto computado para Lambda."
      computaVotos (v1 + 1) v2 v3 nulos

    2 -> do
      putStrLn "Voto computado para Monad."
      computaVotos v1 (v2 + 1) v3 nulos

    3 -> do
      putStrLn "Voto computado para Curry."
      computaVotos v1 v2 (v3 + 1) nulos

    0 -> do
      let totalGeral = v1 + v2 + v3 + nulos
      putStrLn "=== Boletim de Urna ==="
      printf "Lambda: %d\n" v1
      printf "Monad:  %d\n" v2
      printf "Curry:  %d\n" v3
      printf "Nulos:  %d\n" nulos
      putStrLn "-----------------------"
      printf "Total:  %d\n" totalGeral

    _ -> do
      putStrLn "Voto Nulo computado."
      computaVotos v1 v2 v3 (nulos + 1)
