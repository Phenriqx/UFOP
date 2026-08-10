module ValorPremio where

-- | Calcula o valor devolvido por uma máquina de caça-níqueis.
--
--   As frutas são codificadas por:
--   * 'a' -> abacaxi
--   * 'b' -> banana
--   * 'm' -> morango
--   * 'u' -> uva
--
--   Regras:
--   * 3 bananas -> 10x a aposta
--   * 2 bananas -> 5x a aposta
--   * 1 banana  -> 1x a aposta
--   * nenhuma banana -> 0
valorPremio :: Char -> Char -> Char -> Float -> Float
valorPremio fruta1 fruta2 fruta3 aposta
    | qtdBananas == 3   = aposta * 10
    | qtdBananas == 2   = aposta * 5
    | qtdBananas == 1   = aposta
    | otherwise         = 0
    where
        qtdBananas = (if fruta1 == 'b' then 1 else 0) +
                     (if fruta2 == 'b' then 1 else 0) +
                     (if fruta3 == 'b' then 1 else 0)
