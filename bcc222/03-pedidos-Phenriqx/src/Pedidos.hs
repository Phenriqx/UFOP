{- HLINT ignore "Eta reduce" -}
module Pedidos
  ( Cliente
  , NomeProduto
  , Quantidade
  , ValorTotal
  , ItemPedido
  , Pedido
  , TabelaDescontos
  , clientePedido
  , itensPedido
  , totalPedido
  , quantidadeTiposItens
  , temTotalCalculado
  , totalOuPadrao
  , consultarDesconto
  , clienteTemDesconto
  , quantidadeTotalUnidades
  ) where

import Data.Maybe (fromMaybe, isJust)
import Data.Tuple.Extra (fst3, snd3, thd3)

type Cliente = String
type NomeProduto = String
type Quantidade = Int
type ValorTotal = Double

type ItemPedido = (NomeProduto, Quantidade)
type Pedido = (Cliente, [ItemPedido], Maybe ValorTotal)
type TabelaDescontos = [(Cliente, Double)]

-- | Seleciona o nome do cliente associado ao pedido.
clientePedido :: Pedido -> Cliente
clientePedido pedido = fst3 pedido

-- | Seleciona a lista de itens do pedido.
itensPedido :: Pedido -> [ItemPedido]
itensPedido pedido = snd3 pedido

-- | Seleciona o valor total opcional do pedido.
totalPedido :: Pedido -> Maybe ValorTotal
totalPedido pedido = thd3 pedido

-- | Conta quantos tipos de itens aparecem no pedido.
quantidadeTiposItens :: Pedido -> Int
quantidadeTiposItens pedido = length (itensPedido pedido)

-- | Indica se o pedido já possui um total calculado.
temTotalCalculado :: Pedido -> Bool
temTotalCalculado pedido = isJust(totalPedido pedido)

-- | Devolve o total do pedido, ou um valor padrão quando ele estiver ausente.
totalOuPadrao :: ValorTotal -> Pedido -> ValorTotal
totalOuPadrao valorPadrao pedido = fromMaybe valorPadrao (totalPedido pedido)

-- | Consulta o desconto de um cliente em uma tabela de descontos.
-- | Se o cliente não estiver presente, devolve 0.0.
consultarDesconto :: Cliente -> TabelaDescontos -> Double
consultarDesconto cliente tabela = fromMaybe 0.0 (lookup cliente tabela)

-- | Verifica se um cliente aparece na tabela de descontos.
clienteTemDesconto :: Cliente -> TabelaDescontos -> Bool
clienteTemDesconto cliente tabela = isJust(lookup cliente tabela)

-- | Soma as quantidades de todos os itens da lista.
-- | Sugestão: resolva esta função com recursão.
quantidadeTotalUnidades :: [ItemPedido] -> Int
quantidadeTotalUnidades [] = 0
quantidadeTotalUnidades itens = snd(head itens) + quantidadeTotalUnidades(tail itens)
