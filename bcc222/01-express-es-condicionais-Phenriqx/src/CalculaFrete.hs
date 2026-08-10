module CalculaFrete where

-- | Calcula o valor final do frete a partir do peso do pacote
--   e do tipo de entrega.
--
--   Regras:
--   * até 1 kg: R$ 15,00
--   * acima de 1 kg e até 10 kg: R$ 25,00
--   * acima de 10 kg: R$ 40,00
--   * entrega "Expressa": acréscimo de 30% sobre o valor base
calculaFrete :: Float -> String -> Float
calculaFrete peso tipoEntrega
    | peso <= 1 && tipoEntrega /= "Expressa" = 15
    | peso <= 1 && tipoEntrega == "Expressa" = 15 * 1.3
    | peso <= 10 && tipoEntrega /= "Expressa" = 25
    | peso <= 10 && tipoEntrega == "Expressa" = 25 * 1.3
    | peso > 10 && tipoEntrega /= "Expressa" = 40
    | peso > 10 && tipoEntrega == "Expressa" = 40 * 1.3