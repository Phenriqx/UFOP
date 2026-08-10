module Atividade.NumerosNaturais
  ( Nat(..)
  , natToInteger
  , integerToNat
  ) where

data Nat = Zero | Succ Nat

natToInteger :: Nat -> Integer
natToInteger Zero = 0
natToInteger (Succ n) = 1 + natToInteger n

integerToNat :: Integer -> Nat
integerToNat n
  | n < 0     = error "Números naturais não podem ser negativos."
  | n == 0    = Zero
  | otherwise = Succ (integerToNat (n - 1))

instance Eq Nat where
  Zero == Zero         = True
  (Succ a) == (Succ b) = a == b
  _ == _               = False

instance Ord Nat where
  compare Zero Zero         = EQ
  compare Zero (Succ _)     = LT
  compare (Succ _) Zero     = GT
  compare (Succ a) (Succ b) = compare a b

instance Show Nat where
  show n = show (natToInteger n)

instance Num Nat where
  Zero + y     = y
  Succ x + y   = Succ (x + y)

  Zero - _            = Zero
  x - Zero            = x
  (Succ x) - (Succ y) = x - y

  Zero * _     = Zero
  Succ x * y   = y + (x * y)

  abs n = n

  signum Zero     = Zero
  signum (Succ _) = Succ Zero

  fromInteger = integerToNat

instance Enum Nat where
  toEnum = integerToNat . toInteger
  fromEnum = fromInteger . natToInteger

instance Real Nat where
  toRational = toRational . natToInteger

instance Integral Nat where
  toInteger = natToInteger

  quotRem _ Zero = error "Divisão por zero"
  quotRem x y
    | x < y     = (Zero, x)
    | otherwise = let (q, r) = quotRem (x - y) y
                  in (Succ q, r)