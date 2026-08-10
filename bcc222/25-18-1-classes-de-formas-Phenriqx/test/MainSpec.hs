module Main (main) where

import Test.Hspec
import Atividade.ClassesDeFormas

aprox :: Double -> Double -> Bool
aprox x y = abs (x - y) < 1.0e-6

main :: IO ()
main = hspec $ do
  describe "instâncias de TemArea" $ do
    it "calcula a área de um círculo" $
      area (Circulo 2) `shouldSatisfy` aprox (4 * pi)

    it "calcula a área de um retângulo" $
      area (Retangulo 3 4) `shouldSatisfy` aprox 12

    it "calcula a área de um triângulo" $
      area (Triangulo 3 4) `shouldSatisfy` aprox 6

  describe "método padrão areaEhMaiorQue" $ do
    it "usa a área para comparar com o limite" $ do
      areaEhMaiorQue (Retangulo 2 3) 5 `shouldBe` True
      areaEhMaiorQue (Retangulo 2 3) 6 `shouldBe` False

  describe "funções polimórficas com restrição de classe" $ do
    it "calcula a área total de uma lista" $
      areaTotal [Triangulo 3 4, Triangulo 2 5] `shouldSatisfy` aprox 11

    it "filtra elementos cuja área é maior que o limite" $
      maioresQue 5 [Retangulo 2 2, Retangulo 2 3, Retangulo 1 10]
        `shouldBe` [Retangulo 2 3, Retangulo 1 10]

    it "produz um resumo das áreas" $
      resumoAreas [Retangulo 1 2, Retangulo 3 4]
        `shouldBe` [2, 12]
