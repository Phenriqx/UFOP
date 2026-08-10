module Main (main) where

import Test.Hspec
import Atividade.ArvoresComClasses

arv1 :: BinTree Int
arv1 =
  Node 2
    (Node 1 Empty Empty)
    (Node 3 Empty Empty)

arv2 :: BinTree Int
arv2 =
  Node 2
    (Node 1 Empty Empty)
    (Node 4 Empty Empty)

arvDesbalanceada :: BinTree Int
arvDesbalanceada =
  Node 10
    Empty
    (Node 20 Empty (Node 30 Empty Empty))

main :: IO ()
main = hspec $ do
  describe "funções sobre BinTree" $ do
    it "calcula o tamanho da árvore" $ do
      tamanho Empty `shouldBe` 0
      tamanho arv1 `shouldBe` 3

    it "calcula a altura da árvore" $ do
      altura Empty `shouldBe` 0
      altura arv1 `shouldBe` 2
      altura arvDesbalanceada `shouldBe` 3

    it "percorre a árvore em ordem" $
      emOrdem arv1 `shouldBe` [1, 2, 3]

  describe "instâncias com restrições" $ do
    it "compara árvores por igualdade estrutural" $ do
      arv1 == arv1 `shouldBe` True
      arv1 == arv2 `shouldBe` False
      Empty == (Empty :: BinTree Int) `shouldBe` True

    it "exibe árvores no formato esperado" $
      show arv1 `shouldBe` "Node 2 (Node 1 (Empty) (Empty)) (Node 3 (Empty) (Empty))"

    it "ordena árvores pelo percurso em ordem" $
      compare arv1 arv2 `shouldBe` LT

  describe "classe Mapeavel" $ do
    it "aplica uma função a todos os valores da árvore" $
      mapear (+ 1) arv1
        `shouldBe` Node 3 (Node 2 Empty Empty) (Node 4 Empty Empty)

    it "preserva a estrutura da árvore ao mapear" $
      tamanho (mapear show arvDesbalanceada) `shouldBe` tamanho arvDesbalanceada
