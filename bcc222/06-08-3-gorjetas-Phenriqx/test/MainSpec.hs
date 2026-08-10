module Main (main) where

import Test.Hspec
import Test.Hspec.QuickCheck
import Test.QuickCheck
import Data.Maybe (fromMaybe)
import Text.Printf (printf)

import Run (runWithInput)
import qualified Gorjeta as T

-- Comparação aproximada local para valores de ponto flutuante.
-- Evita uma dependência extra apenas para os testes e deixa explícita a tolerância usada.
aproxima :: Double -> Double -> Bool
aproxima x y = abs (x - y) < 1e-9

valorDe :: Maybe Double -> Double
valorDe = fromMaybe (error "era esperado um valor Just")

genContaValida :: Gen Double
genContaValida = choose (0, 10000)

genContaNegativa :: Gen Double
genContaNegativa = negate <$> choose (0.01, 10000)

genQualidadeValida :: Gen String
genQualidadeValida = elements ["ruim", "bom", "excelente"]

genQualidadeInvalida :: Gen String
genQualidadeInvalida = elements ["medio", "regular", "ok", "", "BOOM"]

main :: IO ()
main = hspec $ do
  describe "Função gorjeta" $ do
    it "calcula 5% para serviço ruim" $
      T.gorjeta 100.0 "ruim" `shouldSatisfy`
        maybe False (`aproxima` 5.0)

    it "calcula 10% para serviço bom" $
      T.gorjeta 100.0 "bom" `shouldSatisfy`
        maybe False (`aproxima` 10.0)

    it "calcula 15% para serviço excelente" $
      T.gorjeta 100.0 "excelente" `shouldSatisfy`
        maybe False (`aproxima` 15.0)

    it "retorna Nothing para qualidade inválida" $
      T.gorjeta 100.0 "medio" `shouldBe` Nothing

    it "retorna Nothing para conta negativa" $
      T.gorjeta (-50.0) "bom" `shouldBe` Nothing

    prop "retorna Just para contas não negativas e qualidades válidas" $
      forAll genContaValida $ \conta ->
        forAll genQualidadeValida $ \qualidade ->
          T.gorjeta conta qualidade /= Nothing

    prop "retorna Nothing para contas negativas" $
      forAll genContaNegativa $ \conta ->
        forAll genQualidadeValida $ \qualidade ->
          T.gorjeta conta qualidade == Nothing

    prop "retorna Nothing para qualidades inválidas" $
      forAll genContaValida $ \conta ->
        forAll genQualidadeInvalida $ \qualidade ->
          T.gorjeta conta qualidade == Nothing

    prop "calcula corretamente a porcentagem para serviço ruim" $
      forAll genContaValida $ \conta ->
        valorDe (T.gorjeta conta "ruim") `aproxima` (conta * 0.05)

    prop "calcula corretamente a porcentagem para serviço bom" $
      forAll genContaValida $ \conta ->
        valorDe (T.gorjeta conta "bom") `aproxima` (conta * 0.10)

    prop "calcula corretamente a porcentagem para serviço excelente" $
      forAll genContaValida $ \conta ->
        valorDe (T.gorjeta conta "excelente") `aproxima` (conta * 0.15)

  describe "Programa principal" $ do
    let promptConta = "Digite o valor da conta: "
    let promptQualidade = "Qualidade do serviço (ruim, bom, excelente): "

    it "imprime entrada inválida para qualidade inválida" $ do
      let input = unlines ["150.0", "medio"]
      let expectedOutput = promptConta ++ promptQualidade ++ "Entrada inválida!\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "calcula a gorjeta para serviço ruim" $ do
      let conta = 75.50 :: Double
      let gorjetaEsperada = conta * 0.05
      let totalEsperado = conta + gorjetaEsperada
      let input = unlines [show conta, "ruim"]
      let expectedOutput =
            promptConta
              ++ promptQualidade
              ++ printf "Gorjeta: R$ %.2f\n" gorjetaEsperada
              ++ printf "Total a pagar: R$ %.2f\n" totalEsperado
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "calcula a gorjeta para serviço bom" $ do
      let conta = 100.0 :: Double
      let gorjetaEsperada = conta * 0.10
      let totalEsperado = conta + gorjetaEsperada
      let input = unlines [show conta, "bom"]
      let expectedOutput =
            promptConta
              ++ promptQualidade
              ++ printf "Gorjeta: R$ %.2f\n" gorjetaEsperada
              ++ printf "Total a pagar: R$ %.2f\n" totalEsperado
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "calcula a gorjeta para serviço excelente" $ do
      let conta = 200.0 :: Double
      let gorjetaEsperada = conta * 0.15
      let totalEsperado = conta + gorjetaEsperada
      let input = unlines [show conta, "excelente"]
      let expectedOutput =
            promptConta
              ++ promptQualidade
              ++ printf "Gorjeta: R$ %.2f\n" gorjetaEsperada
              ++ printf "Total a pagar: R$ %.2f\n" totalEsperado
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "imprime entrada inválida para valor textual da conta" $ do
      let input = unlines ["abc", "bom"]
      let expectedOutput = promptConta ++ "Entrada inválida!\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "imprime entrada inválida para conta negativa" $ do
      let input = unlines ["-50.0", "bom"]
      let expectedOutput = promptConta ++ promptQualidade ++ "Entrada inválida!\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput
