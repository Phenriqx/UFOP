module Main (main) where

import Data.AEq ((~==))
import Test.Hspec
import Test.Hspec.QuickCheck
import Test.QuickCheck (Gen, choose, elements, conjoin, forAll)

import qualified ValorPremio as T

main :: IO ()
main = hspec $ do
  describe "ValorPremio" $ do
    prop "segue a regra geral para qualquer combinação válida de frutas" $
      forAll ((,,,) <$> chooseFruta <*> chooseFruta <*> chooseFruta <*> chooseAposta) $ \(f1, f2, f3, aposta) ->
        T.valorPremio f1 f2 f3 aposta ~== premioEsperado f1 f2 f3 aposta

    prop "quando não há banana, o prêmio é zero" $
      forAll chooseAposta $ \aposta ->
        T.valorPremio 'a' 'm' 'u' aposta ~== 0

    prop "quando há exatamente uma banana, o prêmio é igual ao valor da aposta" $
      forAll ((,,) <$> chooseFrutaSemBanana <*> chooseFrutaSemBanana <*> chooseAposta) $ \(f2, f3, aposta) ->
        conjoin [ case xs of
                    [a,b,c] -> T.valorPremio a b c aposta ~== aposta
                    _       -> False
                | xs <- insertEverywhere 'b' [f2, f3]
                ]

    prop "quando há exatamente duas bananas, o prêmio é cinco vezes a aposta" $
      forAll ((,) <$> chooseFrutaSemBanana <*> chooseAposta) $ \(f3, aposta) ->
        conjoin [ case xs of
                    [a,b,c] -> T.valorPremio a b c aposta ~== 5 * aposta
                    _       -> False
                | xs <- insertEverywhere f3 ['b', 'b']
                ]

    prop "quando há três bananas, o prêmio é dez vezes a aposta" $
      forAll chooseAposta $ \aposta ->
        T.valorPremio 'b' 'b' 'b' aposta ~== 10 * aposta

insertEverywhere :: a -> [a] -> [[a]]
insertEverywhere x [] = [[x]]
insertEverywhere x ys =
  [ take i ys ++ [x] ++ drop i ys
  | i <- [0 .. length ys]
  ]

chooseAposta :: Gen Float
chooseAposta = choose (1e-3, 1e3)

chooseFruta :: Gen Char
chooseFruta = elements ['a', 'b', 'm', 'u']

chooseFrutaSemBanana :: Gen Char
chooseFrutaSemBanana = elements ['a', 'm', 'u']

premioEsperado :: Char -> Char -> Char -> Float -> Float
premioEsperado fruta1 fruta2 fruta3 aposta
  | qtdBananas == 3 = 10 * aposta
  | qtdBananas == 2 = 5 * aposta
  | qtdBananas == 1 = aposta
  | otherwise       = 0
  where
    qtdBananas = contaBananas [fruta1, fruta2, fruta3]

contaBananas :: [Char] -> Int
contaBananas = length . filter (== 'b')
