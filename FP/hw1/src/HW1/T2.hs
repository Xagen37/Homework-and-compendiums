module HW1.T2
  (
    N (..)
  , ncmp
  , ndiv
  , nEven
  , nFromNatural
  , nmod
  , nmult
  , nOdd
  , nplus
  , nsub
  , nToNum
  ) where

import Numeric.Natural (Natural)

data N = Z | S N
  deriving Show

nplus :: N -> N -> N        -- addition
nplus n Z     = n
nplus n (S m) = S $ nplus n m

nmult :: N -> N -> N        -- multiplication
nmult _ Z     = Z
nmult n (S m) = nplus n $ nmult n m

nsub :: N -> N -> Maybe N   -- subtraction     (Nothing if result is negative)
nsub n Z         = Just n
nsub Z _         = Nothing
nsub (S n) (S m) = nsub n m

ncmp :: N -> N -> Ordering  -- comparison      (Do not derive Ord)
ncmp n m =
  case nsub n m of
    Nothing -> LT
    Just Z  -> EQ
    _       -> GT

nFromNatural :: Natural -> N
nFromNatural 0 = Z
nFromNatural n = S $ nFromNatural(n - 1)

nToNum :: Num a => N -> a
nToNum Z     = 0
nToNum (S n) = 1 + nToNum n

-- | Advanced
nEven :: N -> Bool    -- parity checking
nEven Z     = True
nEven (S n) = not (nEven n)

nOdd :: N -> Bool     -- parity checking
nOdd = not . nEven

ndiv :: N -> N -> N   -- integer division
ndiv _ Z = error "Division by zero in ndiv"
ndiv n (S Z) = n
ndiv n m =
  case nsub n m of
    Nothing        -> Z
    Just remainder -> S $ ndiv remainder m

nmod :: N -> N -> N    -- modulo operation
nmod _ Z = error "Division by zero in nmod"
nmod _ (S Z) = Z
nmod n m =
  case nsub n m of
    Nothing        -> n
    Just remainder -> nmod remainder m
