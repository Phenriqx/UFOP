module Atividade.ClassesDeFormas
  ( TemArea(..)
  , Circulo(..)
  , Retangulo(..)
  , Triangulo(..)
  , areaTotal
  , maioresQue
  , resumoAreas
  ) where

data Circulo = Circulo Double
  deriving (Eq, Show)

data Retangulo = Retangulo Double Double
  deriving (Eq, Show)

data Triangulo = Triangulo Double Double
  deriving (Eq, Show)

class TemArea a where
  area :: a -> Double

  areaEhMaiorQue :: a -> Double -> Bool
  areaEhMaiorQue x limite = area x > limite

instance TemArea Circulo where
  area (Circulo r) = pi * r * r

instance TemArea Retangulo where
  area (Retangulo largura altura) = largura * altura

instance TemArea Triangulo where
  area (Triangulo base altura) = (base * altura) / 2

areaTotal :: TemArea a => [a] -> Double
areaTotal formas = sum (map area formas)

maioresQue :: TemArea a => Double -> [a] -> [a]
maioresQue limite formas = filter (\x -> areaEhMaiorQue x limite) formas

resumoAreas :: TemArea a => [a] -> [Double]
resumoAreas formas = map area formas