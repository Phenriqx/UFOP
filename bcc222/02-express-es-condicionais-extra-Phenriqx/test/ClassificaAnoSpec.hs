module Main (main) where

import Test.Hspec
import Test.Hspec.QuickCheck
import Test.QuickCheck (Gen, choose, forAll)

import qualified ClassificaAno as T

main :: IO ()
main = hspec $ do
  describe "ClassificaAno" $ do
    prop "anos múltiplos de 400 são bissextos e seculares" $
      forAll genMultiplo400 $ \ano ->
        T.classificaAno ano == "bissexto e secular"

    prop "anos múltiplos de 100, mas não de 400, são apenas seculares" $
      forAll genMultiplo100Nao400 $ \ano ->
        T.classificaAno ano == "apenas secular"

    prop "anos múltiplos de 4, mas não de 100, são apenas bissextos" $
      forAll genMultiplo4Nao100 $ \ano ->
        T.classificaAno ano == "apenas bissexto"

    prop "anos que não são múltiplos de 4 são anos comuns" $
      forAll genAnoComum $ \ano ->
        T.classificaAno ano == "ano comum"

genMultiplo400 :: Gen Int
genMultiplo400 = do
  k <- choose (1, 2500)
  pure (400 * k)

genMultiplo100Nao400 :: Gen Int
genMultiplo100Nao400 = do
  k <- choose (1, 2500)
  let ano = 100 * k
  if ano `mod` 400 == 0
    then genMultiplo100Nao400
    else pure ano

genMultiplo4Nao100 :: Gen Int
genMultiplo4Nao100 = do
  k <- choose (1, 250000)
  let ano = 4 * k
  if ano `mod` 100 == 0
    then genMultiplo4Nao100
    else pure ano

genAnoComum :: Gen Int
genAnoComum = do
  ano <- choose (1, 1000000)
  if ano `mod` 4 == 0
    then genAnoComum
    else pure ano
