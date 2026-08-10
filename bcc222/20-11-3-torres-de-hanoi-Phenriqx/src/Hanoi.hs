module Hanoi
  ( Pino,
    Movimento,
    hanoi,
    main
  )
where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)

type Pino = String
type Movimento = (Pino, Pino)

-- | Calcula a sequência de movimentos para resolver as Torres de Hanói.
-- Argumentos: número de discos, pino de origem, pino de destino, pino auxiliar.
hanoi :: Integer -> Pino -> Pino -> Pino -> [Movimento]
hanoi n origem destino auxiliar
  | n <= 0    = [] -- Caso base: nenhum disco para mover
  | otherwise =
      -- 1. Move n-1 discos da Origem para o Auxiliar (usando Destino como temporário)
      hanoi (n - 1) origem auxiliar destino
      -- 2. Move o disco maior diretamente da Origem para o Destino
      ++ [(origem, destino)]
      -- 3. Move os n-1 discos do Auxiliar para o Destino (usando Origem como temporário)
      ++ hanoi (n - 1) auxiliar destino origem

formatMovimento :: Movimento -> String
formatMovimento (de, para) = "Mova o disco de " ++ de ++ " para " ++ para

-- | Ação de E/S principal para interagir com o usuário.
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering -- Desativa o buffer para o prompt aparecer na hora

  putStr "Quantos discos? "
  input <- getLine
  let n = read input :: Integer

  putStrLn $ "A solução para mover " ++ show n ++ " discos de A para B é:"

  -- Gera a lista de movimentos
  let movimentos = hanoi n "A" "B" "C"

  -- Converte cada tupla (Pino, Pino) em String e imprime uma por linha
  -- Como não há restrição de funções de ordem superior aqui, usar mapM_ é o padrão idiomático
  mapM_ (putStrLn . formatMovimento) movimentos