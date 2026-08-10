module Main (main) where

import Data.AEq ((~==))
import Test.Hspec
import Test.Hspec.QuickCheck
import Test.QuickCheck (Gen, choose, forAll)

import qualified AnalisaVulnerabilidade as T

main :: IO ()
main = hspec $ do
  describe "AnalisaVulnerabilidade" $ do
    prop "na faixa [0,0.2) a classe é Muito baixa, sem remoção e sem ajuda" $
      forAll genFaixa1 $ \v ->
        tudoVerdadeiro
          [ T.classeVulnerabilidade v == "Muito baixa"
          , T.acaoRemocao v == "Nenhuma ação de remoção"
          , T.ajudaCusto v ~== 0
          ]

    prop "na faixa [0.2,0.4) a classe é Baixa, sem remoção e sem ajuda" $
      forAll genFaixa2 $ \v ->
        tudoVerdadeiro
          [ T.classeVulnerabilidade v == "Baixa"
          , T.acaoRemocao v == "Nenhuma ação de remoção"
          , T.ajudaCusto v ~== 0
          ]

    prop "na faixa [0.4,0.6) a classe é Média, remoção em uma semana e ajuda 1000" $
      forAll genFaixa3 $ \v ->
        tudoVerdadeiro
          [ T.classeVulnerabilidade v == "Média"
          , T.acaoRemocao v == "Remoção em uma semana"
          , T.ajudaCusto v ~== 1000
          ]

    prop "na faixa [0.6,0.8) a classe é Alta, remoção em dois dias e ajuda 3000" $
      forAll genFaixa4 $ \v ->
        tudoVerdadeiro
          [ T.classeVulnerabilidade v == "Alta"
          , T.acaoRemocao v == "Remoção em dois dias"
          , T.ajudaCusto v ~== 3000
          ]

    prop "na faixa [0.8,1] a classe é Muito alta, remoção imediata e ajuda 5000" $
      forAll genFaixa5 $ \v ->
        tudoVerdadeiro
          [ T.classeVulnerabilidade v == "Muito alta"
          , T.acaoRemocao v == "Remoção imediata"
          , T.ajudaCusto v ~== 5000
          ]

tudoVerdadeiro :: [Bool] -> Bool
tudoVerdadeiro = and

genFaixa1 :: Gen Double
genFaixa1 = choose (0, 0.199999)

genFaixa2 :: Gen Double
genFaixa2 = choose (0.2, 0.399999)

genFaixa3 :: Gen Double
genFaixa3 = choose (0.4, 0.599999)

genFaixa4 :: Gen Double
genFaixa4 = choose (0.6, 0.799999)

genFaixa5 :: Gen Double
genFaixa5 = choose (0.8, 1.0)
