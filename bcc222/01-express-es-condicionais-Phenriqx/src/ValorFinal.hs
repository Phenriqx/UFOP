module ValorFinal where

-- | Calcula o valor final de uma compra a partir do código da região
--   e do valor da compra.
--
--   Taxas por região:
--   * 1 -> 8%
--   * 2 -> 6%
--   * 3 -> 3%
--   * 4 -> 12%
--   * 5 -> 15%
--
--   Compras acima de R$ 5000,00 não recebem taxa.
valorFinal :: Int -> Float -> Float
valorFinal regiao valorCompra
    | valorCompra > 5000 = valorCompra
    | regiao == 1        = valorCompra * 1.08
    | regiao == 2        = valorCompra * 1.06
    | regiao == 3        = valorCompra * 1.03
    | regiao == 4        = valorCompra * 1.12
    | regiao == 5        = valorCompra * 1.15
    | otherwise          = valorCompra