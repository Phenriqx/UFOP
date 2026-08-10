module RefeicaoSaudavel (main, caloriasRefeicao, minutosEsteira) where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)
import Text.Printf (printf)

caloriasRefeicao :: Double -> Double
caloriasRefeicao gramas = 250 + (gramas * 300 / 100)

minutosEsteira :: Double -> Double
minutosEsteira gramas =
  let total = caloriasRefeicao gramas
      excesso = total - 600
  in if total <= 600 then 0.0 else excesso * 30 / 300

main :: IO ()
main = do
  hSetBuffering stdout NoBuffering

  putStr "Informe as gramas do bife: "

  gramas <- readLn :: IO Double

  let totalCals = caloriasRefeicao gramas
  let minutos = minutosEsteira gramas

  if totalCals <= 600
      then putStrLn "Refeição saudável!"
      else printf "Excesso calórico, fazer %.2f minuto(s) de esteira!\n" minutos
