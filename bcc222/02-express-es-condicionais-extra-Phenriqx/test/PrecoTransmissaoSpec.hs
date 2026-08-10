module Main (main) where

import Data.AEq ((~==))
import Test.Hspec
import Test.Hspec.QuickCheck
import Test.QuickCheck (Gen, choose, forAll)

import qualified PrecoTransmissao as T

main :: IO ()
main = hspec $ do
  describe "PrecoTransmissao" $ do
    prop "quantidade positiva é válida" $
      forAll genPositivo $ \qtd ->
        T.quantidadeValida qtd

    prop "quantidade nula ou negativa é inválida" $
      forAll genNaoPositivo $ \qtd ->
        not (T.quantidadeValida qtd)

    prop "até 5 GB não há desconto" $
      forAll genFaixa1 $ \qtd ->
        T.precoTransmissao qtd ~== precoEsperado qtd

    prop "entre 5 e 10 GB o desconto de 4% vale apenas acima de 5 GB" $
      forAll genFaixa2 $ \qtd ->
        T.precoTransmissao qtd ~== precoEsperado qtd

    prop "entre 10 e 20 GB o desconto de 6% vale apenas acima de 10 GB" $
      forAll genFaixa3 $ \qtd ->
        T.precoTransmissao qtd ~== precoEsperado qtd

    prop "entre 20 e 40 GB o desconto de 8% vale apenas acima de 20 GB" $
      forAll genFaixa4 $ \qtd ->
        T.precoTransmissao qtd ~== precoEsperado qtd

    prop "acima de 40 GB o desconto de 10% vale para toda a quantidade" $
      forAll genFaixa5 $ \qtd ->
        T.precoTransmissao qtd ~== precoEsperado qtd

precoEsperado :: Double -> Double
precoEsperado qtd
  | qtd <= 5   = qtd * precoGB
  | qtd <= 10  = 5 * precoGB + (qtd - 5) * precoGB * 0.96
  | qtd <= 20  = 10 * precoGB + (qtd - 10) * precoGB * 0.94
  | qtd <= 40  = 20 * precoGB + (qtd - 20) * precoGB * 0.92
  | otherwise  = qtd * precoGB * 0.90
  where
    precoGB = 2.50

genPositivo :: Gen Double
genPositivo = choose (1e-6, 1e3)

genNaoPositivo :: Gen Double
genNaoPositivo = choose (-1e3, 0)

genFaixa1 :: Gen Double
genFaixa1 = choose (1e-6, 5)

genFaixa2 :: Gen Double
genFaixa2 = choose (5.000001, 10)

genFaixa3 :: Gen Double
genFaixa3 = choose (10.000001, 20)

genFaixa4 :: Gen Double
genFaixa4 = choose (20.000001, 40)

genFaixa5 :: Gen Double
genFaixa5 = choose (40.000001, 1e3)
