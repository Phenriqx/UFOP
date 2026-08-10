module Main (main) where

import Test.Hspec
import Test.Hspec.QuickCheck
import Test.QuickCheck.Modifiers
import Data.AEq ((~==))

import qualified CalculaFrete as T

main :: IO ()
main = hspec $ do
  describe "CalculaFrete" $ do
    prop "entrega normal segue a regra por faixas" $
      \(Positive peso) ->
        T.calculaFrete peso "Normal" ~== freteEsperado peso "Normal"

    prop "entrega expressa segue a regra por faixas" $
      \(Positive peso) ->
        T.calculaFrete peso "Expressa" ~== freteEsperado peso "Expressa"

    prop "entrega expressa custa 30% a mais do que a normal para o mesmo peso" $
      \(Positive peso) ->
        let normal = T.calculaFrete peso "Normal"
            expressa = T.calculaFrete peso "Expressa"
        in expressa ~== normal * 1.3

    it "trata corretamente a fronteira de 1 kg" $
      T.calculaFrete 1 "Normal" `shouldSatisfy` (~== freteEsperado 1 "Normal")

    it "trata corretamente a fronteira de 10 kg" $
      T.calculaFrete 10 "Expressa" `shouldSatisfy` (~== freteEsperado 10 "Expressa")

freteEsperado :: Float -> String -> Float
freteEsperado peso tipoEntrega =
  if tipoEntrega == "Expressa"
    then base * 1.3
    else base
  where
    base
      | peso <= 1  = 15
      | peso <= 10 = 25
      | otherwise  = 40
