module Figuras
  ( Figura(..), -- Exporta o tipo e seus construtores
    area,
    perimetro,
    ehRegular
  )
where

-- Tarefa 1: Adicione o construtor Triangulo a este tipo de dado.
data Figura = Circulo Double
            | Retangulo Double Double
            | Triangulo Double Double Double
            deriving (Show, Eq) -- Adicionado Eq para facilitar os testes

-- Uma função para calcular a área de uma figura.
-- Tarefa 2: Estenda esta função para lidar com Triangulos.
area :: Figura -> Double
area (Circulo r)     = pi * r^2
area (Retangulo b a) = b * a
area (Triangulo a b c) = sqrt (p * (p - a) * (p - b) * (p - c))
  where
    p = (a + b + c) / 2
-- Adicione a equação para Triangulo aqui...

-- Tarefa 3.1: Implemente a função perimetro.
-- Uma função que recebe uma Figura e calcula o seu perímetro.
perimetro :: Figura -> Double
perimetro (Circulo r)       = 2 * pi * r
perimetro (Retangulo b a)   = 2 * (b + a)
perimetro (Triangulo a b c) = a + b + c

-- Tarefa 3.2: Implemente a função ehRegular.
-- Uma função que retorna True se a figura for "regular".
ehRegular :: Figura -> Bool
ehRegular (Circulo _)         = True
ehRegular (Retangulo b a)     = b == a
ehRegular (Triangulo a b c)   = a == b && b == c
