module ClassificaAno where

-- | Recebe um ano positivo e retorna sua classificação de acordo com as regras
-- de ano bissexto e/ou secular descritas no README.
classificaAno :: Int -> String
classificaAno ano
    | mod ano 400 == 0   = "bissexto e secular"
    | mod ano 100 == 0   = "apenas secular"
    | mod ano 4   == 0   = "apenas bissexto"
    | otherwise          = "ano comum"