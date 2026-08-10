module AnalisaVulnerabilidade where

-- | Recebe um valor de referência no intervalo [0,1] e retorna a classe de
-- vulnerabilidade correspondente.
classeVulnerabilidade :: Double -> String
classeVulnerabilidade valor
    | valor <= 0.2   = "Muito baixa"
    | valor <= 0.4   = "Baixa"
    | valor <= 0.6   = "Média"
    | valor <= 0.8   = "Alta"
    | otherwise      = "Muito alta"

-- | Recebe um valor de referência no intervalo [0,1] e retorna a ação de
-- remoção correspondente.
acaoRemocao :: Double -> String
acaoRemocao valor
    | valor <= 0.4   = "Nenhuma ação de remoção"
    | valor <= 0.6   = "Remoção em uma semana"
    | valor <= 0.8   = "Remoção em dois dias"
    | otherwise      = "Remoção imediata"

-- | Recebe um valor de referência no intervalo [0,1] e retorna o valor da
-- ajuda de custo correspondente.
ajudaCusto :: Double -> Double
ajudaCusto valor
    | valor <= 0.4   = 0
    | valor <= 0.6   = 1000
    | valor <= 0.8   = 3000
    | otherwise      = 5000
