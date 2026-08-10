module Overbooking
  ( loopProcessaVoos,
    main,
  )
where

import System.IO (BufferMode (NoBuffering), hFlush, hSetBuffering, stdout)

-- | Ação de E/S recursiva que processa os dados de cada voo.
-- Argumentos: vooAtual, totalDeVoos, voosComOverbooking, passageirosExcedentes
loopProcessaVoos :: Int -> Int -> Int -> Int -> IO ()
loopProcessaVoos vooAtual totalVoos overbookings excedentesTotais
  | vooAtual > totalVoos = do
      putStrLn "Fim da entrada dos voos:"
      putStrLn $ "Ocorreram " ++ show overbookings ++ " voos com overbooking"
      putStrLn $ "Ocorreram " ++ show excedentesTotais ++ " passageiros acima da capacidade"
  | otherwise = do
      putStrLn $ "Voo " ++ show vooAtual ++ ":"

      putStr "Capacidade da aeronave: "
      inputCap <- getLine
      let capacidade = read inputCap :: Int

      putStr "Quantidade de passagens: "
      inputPass <- getLine
      let passagens = read inputPass :: Int

      -- Verifica se houve overbooking e calcula as atualizações de estado
      let novoOverbooking = passagens > capacidade
      let excedenteVoo = if novoOverbooking then passagens - capacidade else 0

      -- Emite o alerta imediatamente se necessário
      if novoOverbooking
        then putStrLn "Alerta: Voo com overbooking!"
        else return ()

      -- Atualiza os acumuladores e passa para a próxima iteração
      let proxOverbookings = if novoOverbooking then overbookings + 1 else overbookings
      let proxExcedentes = excedentesTotais + excedenteVoo

      loopProcessaVoos (vooAtual + 1) totalVoos proxOverbookings proxExcedentes


-- | Ação principal que inicia o programa.
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering

  putStrLn "Rotten Cocoa Airlines Corp."
  putStr "Informe a quantidade de voos: "
  inputQtd <- getLine
  let totalVoos = read inputQtd :: Int

  -- Inicia o laço recursivo: voo atual = 1, acumuladores zerados
  loopProcessaVoos 1 totalVoos 0 0
