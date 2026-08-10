module Main (main) where

import Test.Hspec
import Test.Hspec.QuickCheck
import Test.QuickCheck

import Run (runWithInput)
import qualified Vendas as T

-- Comparação aproximada local para valores de ponto flutuante.
-- Evita uma dependência extra apenas para os testes e deixa explícita a tolerância usada.
aproxima :: Double -> Double -> Bool
aproxima x y = abs (x - y) < 1e-9

main :: IO ()
main = hspec $ do
  describe "Função valorTotal" $ do
    it "retorna zero para quantidades zero" $
      (T.valorTotal 0 0 `aproxima` 0) `shouldBe` True

    prop "usa os preços menores quando as duas quantidades são de até 5 kg" $
      forAll (choose (0, 5)) $ \morangos ->
        forAll (choose (0, 5)) $ \macas ->
          T.valorTotal morangos macas
            `aproxima` (8.50 * morangos + 5.25 * macas)

    prop "usa preço reduzido para morangos acima de 5 kg" $
      forAll (choose (5.01, 100)) $ \morangos ->
        forAll (choose (0, 5)) $ \macas ->
          T.valorTotal morangos macas
            `aproxima` (7.20 * morangos + 5.25 * macas)

    prop "usa preço reduzido para maçãs acima de 5 kg" $
      forAll (choose (0, 5)) $ \morangos ->
        forAll (choose (5.01, 100)) $ \macas ->
          T.valorTotal morangos macas
            `aproxima` (8.50 * morangos + 4.75 * macas)

    prop "usa os preços reduzidos quando as duas quantidades são acima de 5 kg" $
      forAll (choose (5.01, 100)) $ \morangos ->
        forAll (choose (5.01, 100)) $ \macas ->
          T.valorTotal morangos macas
            `aproxima` (7.20 * morangos + 4.75 * macas)

  describe "Programa principal" $ do
    it "rejeita quantidade negativa de morangos" $ do
      out <- runWithInput T.main (unlines ["-10", "20"])
      out `shouldContain` "Entrada inválida"

    it "rejeita quantidade negativa de maçãs" $ do
      out <- runWithInput T.main (unlines ["10", "-20"])
      out `shouldContain` "Entrada inválida"

    it "imprime o valor total para entradas válidas" $ do
      out <- runWithInput T.main (unlines ["10.8", "5"])
      out `shouldContain` "O valor total da compra é R$ 104.01"
