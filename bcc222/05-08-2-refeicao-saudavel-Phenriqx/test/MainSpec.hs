module Main (main) where

import Test.Hspec
import Test.Hspec.QuickCheck
import Test.QuickCheck
import Text.Printf (printf)

import Run (runWithInput)
import qualified RefeicaoSaudavel as T

aproxima :: Double -> Double -> Bool
aproxima x y = abs (x - y) < 1e-9

caloriasEsperadas :: Double -> Double
caloriasEsperadas gramas = 250 + gramas * 300 / 100

minutosEsperados :: Double -> Double
minutosEsperados gramas =
  if caloriasEsperadas gramas <= 600
    then 0
    else (caloriasEsperadas gramas - 600) * 30 / 300

main :: IO ()
main = hspec $ do
  describe "Função caloriasRefeicao" $ do
    it "calcula o total de calorias para 100 g de bife" $
      T.caloriasRefeicao 100.0 `shouldSatisfy` (`aproxima` 550.0)

    it "calcula o total de calorias para 200 g de bife" $
      T.caloriasRefeicao 200.0 `shouldSatisfy` (`aproxima` 850.0)

    prop "calcula as calorias por proporcionalidade" $
      forAll (choose (0, 1000)) $ \gramas ->
        T.caloriasRefeicao gramas `aproxima` caloriasEsperadas gramas

  describe "Função minutosEsteira" $ do
    it "retorna zero para refeição saudável" $
      T.minutosEsteira 100.5 `shouldSatisfy` (`aproxima` 0.0)

    it "calcula 25 minutos para 200 g de bife" $
      T.minutosEsteira 200.0 `shouldSatisfy` (`aproxima` 25.0)

    prop "nunca retorna valor negativo" $
      forAll (choose (0, 1000)) $ \gramas ->
        T.minutosEsteira gramas >= 0

    prop "calcula corretamente os minutos de esteira" $
      forAll (choose (0, 1000)) $ \gramas ->
        T.minutosEsteira gramas `aproxima` minutosEsperados gramas

  describe "Programa principal" $ do
    let prompt = "Informe as gramas do bife: "

    it "imprime refeição saudável para 100.5 g" $ do
      out <- runWithInput T.main "100.5\n"
      out `shouldBe` (prompt ++ "Refeição saudável!\n")

    it "imprime minutos de esteira para 200 g" $ do
      out <- runWithInput T.main "200\n"
      out `shouldBe` (prompt ++ "Excesso calórico, fazer 25.00 minuto(s) de esteira!\n")

    it "imprime minutos de esteira com duas casas decimais" $ do
      let gramas = 328.64 :: Double
      out <- runWithInput T.main (show gramas ++ "\n")
      out `shouldBe` (prompt ++ printf "Excesso calórico, fazer %.2f minuto(s) de esteira!\n" (minutosEsperados gramas))
