module Main (main) where

import Data.AEq ((~==))
import Test.Hspec
import Test.Hspec.QuickCheck
import Test.QuickCheck (Gen, choose, chooseInt, forAll)

import qualified ValorFinal as T

main :: IO ()
main = hspec $ do
  describe "ValorFinal" $ do
    prop "segue a regra geral para qualquer região válida e valor não negativo" $
      forAll ((,) <$> chooseRegiao <*> choose (0, 1E3)) $ \(regiao, valorCompra) ->
        T.valorFinal regiao valorCompra ~== valorEsperado regiao valorCompra

    prop "compras acima de 5000 são isentas independentemente da região" $
      forAll ((,) <$> chooseRegiao <*> choose (1E-3, 1E3)) $ \(regiao, excedente) ->
        let valorCompra = 5000 + excedente
        in T.valorFinal regiao valorCompra ~== valorCompra

    prop "compras até 5000 recebem a taxa correspondente à região" $
      forAll ((,) <$> chooseRegiao <*> choose (0, 5000)) $ \(regiao, valorCompra) ->
        T.valorFinal regiao valorCompra ~== valorCompra * (1 + taxaEsperada regiao)

    it "mantém exatamente o valor quando a compra é isenta" $
      T.valorFinal 2 5879.87 `shouldSatisfy` (~== 5879.87)

    it "aplica corretamente a taxa do Sudeste em uma compra de 1000" $
      T.valorFinal 4 1000 `shouldSatisfy` (~== 1120)

chooseRegiao :: Gen Int
chooseRegiao = chooseInt (1, 5)

taxaEsperada :: Int -> Float
taxaEsperada regiao
  | regiao == 1 = 0.08
  | regiao == 2 = 0.06
  | regiao == 3 = 0.03
  | regiao == 4 = 0.12
  | otherwise   = 0.15

valorEsperado :: Int -> Float -> Float
valorEsperado regiao valorCompra
  | valorCompra > 5000 = valorCompra
  | otherwise          = valorCompra * (1 + taxaEsperada regiao)
