module PrecoTransmissao where

-- | Retorna True se a quantidade de gigabytes for estritamente positiva.
quantidadeValida :: Double -> Bool
quantidadeValida qtd = qtd > 0

-- | Calcula o preço cobrado por uma quantidade válida de gigabytes transmitidos,
-- de acordo com as regras de desconto descritas no README.
precoTransmissao :: Double -> Double
precoTransmissao qtd
    | qtd < 5       = qtd * 2.5
    | qtd < 10      = preco10
    | qtd < 20      = preco20
    | qtd < 40      = preco40
    | otherwise     = preco
    where
        preco10 = (2.5 * 5) + (qtd - 5) * 2.5 * 0.96
        preco20 = (2.5 * 10) + (qtd - 10) * 2.5 * 0.94
        preco40 = (2.5 * 20) + (qtd - 20) * 2.5 * 0.92
        preco   = qtd * 2.5 * 0.9
