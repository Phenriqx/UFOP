module Luhn
  ( toDigits,
    toDigitsRev,
    doubleEveryOther,
    sumDigits,
    validate,
    main
  )
where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)

toDigits :: Integer -> [Integer]
toDigits n = reverse (toDigitsRev n)

toDigitsRev :: Integer -> [Integer]
toDigitsRev n
  | n <= 0    = []
  | otherwise = (n `mod` 10) : toDigitsRev (n `div` 10)

doubleEveryOther :: [Integer] -> [Integer]
doubleEveryOther ns = reverse (doubleFromLeft (reverse ns))
  where
    doubleFromLeft :: [Integer] -> [Integer]
    doubleFromLeft []       = []
    doubleFromLeft [x]      = [x]
    doubleFromLeft (x:y:ys) = x : (y * 2) : doubleFromLeft ys

sumDigits :: [Integer] -> Integer
sumDigits []     = 0
sumDigits (x:xs) = sum (toDigits x) + sumDigits xs

validate :: Integer -> Bool
validate n = (sumDigits (doubleEveryOther (toDigits n)) `mod` 10) == 0

main :: IO ()
main = do
  hSetBuffering stdout NoBuffering -- Garante que o prompt apareça imediatamente
  putStr "Digite o número do cartão de crédito: "
  input <- getLine
  let number = read input :: Integer
  if validate number
    then putStrLn "Válido"
    else putStrLn "Inválido"