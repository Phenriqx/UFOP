module Main (main) where

import Test.Hspec
import Atividade.NumerosNaturais

n0, n1, n2, n3, n4, n5, n6, n7 :: Nat
n0 = Zero
n1 = Succ Zero
n2 = Succ n1
n3 = Succ n2
n4 = Succ n3
n5 = Succ n4
n6 = Succ n5
n7 = Succ n6

main :: IO ()
main = hspec $ do
  describe "conversões auxiliares" $ do
    it "converte Nat para Integer" $
      natToInteger n4 `shouldBe` 4

    it "converte Integer não negativo para Nat" $
      integerToNat 3 `shouldBe` n3

  describe "instâncias Eq, Ord e Show" $ do
    it "compara naturais por igualdade" $ do
      n3 == integerToNat 3 `shouldBe` True
      n3 == n4 `shouldBe` False

    it "ordena naturais" $ do
      compare n2 n3 `shouldBe` LT
      n4 > n1 `shouldBe` True

    it "exibe naturais em base decimal" $
      show n5 `shouldBe` "5"

  describe "instância Num" $ do
    it "soma naturais" $
      n2 + n3 `shouldBe` n5

    it "subtrai naturais com truncamento em Zero" $ do
      n5 - n3 `shouldBe` n2
      n2 - n5 `shouldBe` Zero

    it "multiplica naturais" $
      n2 * n3 `shouldBe` n6

    it "implementa fromInteger, abs e signum" $ do
      fromInteger 4 `shouldBe` n4
      abs n3 `shouldBe` n3
      signum Zero `shouldBe` Zero
      signum n7 `shouldBe` n1

  describe "instâncias Enum, Real e Integral" $ do
    it "converte de e para Int usando Enum" $ do
      toEnum 2 `shouldBe` n2
      fromEnum n4 `shouldBe` 4

    it "converte para Rational" $
      toRational n3 `shouldBe` 3

    it "calcula quociente e resto" $
      quotRem n7 n3 `shouldBe` (n2, n1)
