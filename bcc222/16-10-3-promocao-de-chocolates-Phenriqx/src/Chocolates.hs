module Chocolates
  ( calculaPreco,
    loopDeCompras,
    main,
  )
where

import System.IO (BufferMode (NoBuffering), hFlush, hSetBuffering, stdout)
import Text.Printf (printf)

-- | Calcula o valor total da compra (sem desconto) com base na quantidade de caixas.
calculaPreco :: Int -> Double
calculaPreco qtde
  | qtde <= 10 = fromIntegral qtde * 20.0
  | qtde <= 30 = fromIntegral qtde * 15.0
  | qtde <= 60 = fromIntegral qtde * 10.0
  | otherwise  = fromIntegral qtde * 5.0

-- | Ação de E/S recursiva que implementa o laço principal de compras.
loopDeCompras :: IO ()
loopDeCompras = do
  putStr "Informe a quantidade de caixas: "
  inputQtde <- getLine
  let qtde = read inputQtde :: Int

  if qtde <= 0
    then do
      printf "ERRO: Quantidade inválida: %d\n" qtde
      perguntaNovaCompra
    else do
      let precoTotal = calculaPreco qtde
      printf "Valor da compra: R$ %.2f\n" precoTotal

      putStr "Informe pagamento com Pix (s/n): "
      pixResp <- getLine

      if pixResp == "s"
        then do
          let precoComPix = precoTotal * 0.92  
          printf "Valor da compra com Pix: R$ %.2f\n" precoComPix
        else return ()

      perguntaNovaCompra

-- | Função auxiliar para evitar duplicação da pergunta de repetição do laço.
perguntaNovaCompra :: IO ()
perguntaNovaCompra = do
  putStr "Informe se deseja comprar novamente (s/n): "
  resposta <- getLine
  if resposta == "s"
    then loopDeCompras
    else putStrLn "Fim das compras, obrigado!"

-- | Ação principal que inicia o programa.
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering

  putStrLn "Rotten Cocoa Market"
  putStr "Informe se deseja comprar (s/n): "
  resposta <- getLine

  if resposta == "s"
    then loopDeCompras
    else putStrLn "Fim das compras, obrigado!"
