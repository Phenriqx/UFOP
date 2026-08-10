module Atividade.ArvoresComClasses
  ( BinTree(..)
  , Mapeavel(..)
  , tamanho
  , altura
  , emOrdem
  ) where

data BinTree a
  = Empty
  | Node a (BinTree a) (BinTree a)

class Mapeavel t where
  mapear :: (a -> b) -> t a -> t b

tamanho :: BinTree a -> Int
tamanho Empty = 0
tamanho (Node _ esq dir) = 1 + tamanho esq + tamanho dir

altura :: BinTree a -> Int
altura Empty = 0
altura (Node _ esq dir) = 1 + max (altura esq) (altura dir)

emOrdem :: BinTree a -> [a]
emOrdem Empty = []
emOrdem (Node v esq dir) = emOrdem esq ++ [v] ++ emOrdem dir

instance Eq a => Eq (BinTree a) where
  Empty == Empty = True
  (Node v1 esq1 dir1) == (Node v2 esq2 dir2) =
    v1 == v2 && esq1 == esq2 && dir1 == dir2
  _ == _ = False

instance Show a => Show (BinTree a) where
  show Empty = "Empty"
  show (Node v esq dir) = "Node " ++ show v ++ " (" ++ show esq ++ ") (" ++ show dir ++ ")"

instance Ord a => Ord (BinTree a) where
  compare t1 t2 = compare (emOrdem t1) (emOrdem t2)

instance Mapeavel BinTree where
  mapear _ Empty = Empty
  mapear f (Node v esq dir) = Node (f v) (mapear f esq) (mapear f dir)