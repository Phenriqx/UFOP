module Main (main) where

import Data.Maybe (fromMaybe, isJust)
import Data.Tuple.Extra (fst3, snd3, thd3)
import Test.Hspec
import Test.Hspec.QuickCheck (prop)
import Test.QuickCheck (choose, chooseInt, elements, frequency, listOf, listOf1, forAll, Gen)

import qualified Pedidos as P

main :: IO ()
main = hspec $ do
  describe "clientePedido" $ do
    prop "seleciona o primeiro componente da tripla" $
      forAll genPedido $ \pedido ->
        P.clientePedido pedido == fst3 pedido

  describe "itensPedido" $ do
    prop "seleciona o segundo componente da tripla" $
      forAll genPedido $ \pedido ->
        P.itensPedido pedido == snd3 pedido

  describe "totalPedido" $ do
    prop "seleciona o terceiro componente da tripla" $
      forAll genPedido $ \pedido ->
        P.totalPedido pedido == thd3 pedido

  describe "quantidadeTiposItens" $ do
    prop "coincide com o comprimento da lista de itens do pedido" $
      forAll genPedido $ \pedido ->
        P.quantidadeTiposItens pedido == length (snd3 pedido)

    it "devolve 0 quando o pedido não possui itens" $
      P.quantidadeTiposItens ("Alice", [], Just 10.0) `shouldBe` 0

  describe "temTotalCalculado" $ do
    prop "coincide com isJust aplicado ao total do pedido" $
      forAll genPedido $ \pedido ->
        P.temTotalCalculado pedido == isJust (thd3 pedido)

    it "devolve False quando o total está ausente" $
      P.temTotalCalculado ("Bob", [("Caderno", 2)], Nothing) `shouldBe` False

  describe "totalOuPadrao" $ do
    prop "coincide com fromMaybe aplicado ao total do pedido" $
      forAll ((,) <$> choose (0.0, 100000.0) <*> genPedido) $ \(valorPadrao, pedido) ->
        P.totalOuPadrao valorPadrao pedido == fromMaybe valorPadrao (thd3 pedido)

  describe "consultarDesconto" $ do
    prop "coincide com lookup seguido de fromMaybe 0.0" $
      forAll ((,) <$> genCliente <*> genTabelaDescontos) $ \(cliente, tabela) ->
        P.consultarDesconto cliente tabela == fromMaybe 0.0 (lookup cliente tabela)

    it "devolve 0.0 quando o cliente não está presente" $
      let tabela = [("Alice", 0.10), ("Carlos", 0.05)]
      in P.consultarDesconto "Bob" tabela `shouldBe` 0.0

  describe "clienteTemDesconto" $ do
    prop "coincide com isJust sobre lookup" $
      forAll ((,) <$> genCliente <*> genTabelaDescontos) $ \(cliente, tabela) ->
        P.clienteTemDesconto cliente tabela == isJust (lookup cliente tabela)

    it "devolve True quando o cliente aparece na tabela" $
      let tabela = [("Alice", 0.10), ("Carlos", 0.05)]
      in P.clienteTemDesconto "Carlos" tabela `shouldBe` True

  describe "quantidadeTotalUnidades" $ do
    prop "coincide com a soma das quantidades presentes na lista de itens" $
      forAll genItensPedido $ \itens ->
        P.quantidadeTotalUnidades itens == sum (map snd itens)

    it "devolve 0 para a lista vazia" $
      P.quantidadeTotalUnidades [] `shouldBe` 0

    it "soma corretamente as quantidades de um pedido com vários itens" $
      P.quantidadeTotalUnidades [("Notebook", 1), ("Mouse", 2), ("Teclado", 3)]
        `shouldBe` 6

genCliente :: Gen P.Cliente
genCliente = listOf1 $ elements ['a' .. 'z']

genNomeProduto :: Gen P.NomeProduto
genNomeProduto = listOf1 $ elements ['a' .. 'z']

genItemPedido :: Gen P.ItemPedido
genItemPedido = (,) <$> genNomeProduto <*> chooseInt (0, 20)

genItensPedido :: Gen [P.ItemPedido]
genItensPedido = listOf genItemPedido

genPedido :: Gen P.Pedido
genPedido =
  (,,)
    <$> genCliente
    <*> genItensPedido
    <*> genTotalOpcional
  where
    genTotalOpcional =
      frequency
        [ (1, pure Nothing)
        , (3, Just <$> choose (0.0, 100000.0))
        ]

genTabelaDescontos :: Gen P.TabelaDescontos
genTabelaDescontos =
  listOf $ (,) <$> genCliente <*> choose (0.0, 0.50)
