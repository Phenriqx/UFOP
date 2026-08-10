module Main (main) where

import qualified Exercicios as E
import Test.Hspec
import Test.QuickCheck

main :: IO ()
main = hspec $ do
  describe "Exercício 1: refatorando para expressões lambda" $ do
    it "somaQuadradosParesLambda funciona corretamente em um exemplo fixo" $
      E.somaQuadradosParesLambda [1, 2, 3, 4, 5, 6] `shouldBe` 56

    it "somaQuadradosParesLambda coincide com a função original" $
      property $ \xs ->
        E.somaQuadradosParesLambda xs == E.somaQuadradosPares xs

    it "stringsMaioresQue5Lambda filtra apenas strings com mais de cinco caracteres" $
      E.stringsMaioresQue5Lambda ["haskell", "lambda", "map", "função", "é"] `shouldBe`
        ["haskell", "lambda", "função"]

    it "adicionaExclamacaoParLambda preserva apenas strings de comprimento par e adiciona !" $
      E.adicionaExclamacaoParLambda ["oi", "tudo", "bem", "com", "voce"] `shouldBe`
        ["oi!", "tudo!", "voce!"]

  describe "Exercício 2: funções especializadas com aplicação parcial e seções" $ do
    it "ehVogal reconhece apenas vogais minúsculas" $ do
      E.ehVogal 'a' `shouldBe` True
      E.ehVogal 'e' `shouldBe` True
      E.ehVogal 'b' `shouldBe` False
      E.ehVogal 'A' `shouldBe` False

    it "adicionaCom acrescenta o sufixo .com" $ do
      E.adicionaCom "google" `shouldBe` "google.com"
      E.adicionaCom "ufop" `shouldBe` "ufop.com"

    it "subtraiDe10 calcula 10 menos o argumento" $ do
      E.subtraiDe10 3 `shouldBe` 7
      E.subtraiDe10 10 `shouldBe` 0
      E.subtraiDe10 (-2) `shouldBe` 12

  describe "Exercício 3: processamento de dados" $ do
    it "aplicaTaxa altera apenas itens com preço maior que 50" $
      let vendas = [("Produto A", 25.0), ("Produto B", 120.0), ("Produto C", 50.0)]
      in E.aplicaTaxa vendas `shouldBe`
          [("Produto A", 25.0), ("Produto B", 132.0), ("Produto C", 50.0)]

    it "alunosAprovados retorna apenas os nomes de alunos com média pelo menos 7" $
      let alunos = [("Ana", 8.0, 8.0), ("Beto", 5.0, 7.0), ("Carla", 9.0, 10.0)]
      in E.alunosAprovados alunos `shouldBe` ["Ana", "Carla"]

    it "aplicaDesconto aplica desconto de 5% a todos os produtos" $
      let vendas = [("A", 100.0), ("B", 20.0)]
      in E.aplicaDesconto vendas `shouldBe` [("A", 95.0), ("B", 19.0)]
