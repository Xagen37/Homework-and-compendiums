module HW0.T5
  ( -- * types
    Nat
    -- * functions
  , nFromNatural
  , nToNum
  , nmult
  , nplus
  , ns
  , nz
  ) where

import GHC.Natural (Natural)

-- | Church numeral.
type Nat a = (a -> a) -> a -> a

-- | Zero Church numeral.
nz :: Nat a
nz _ x = x

-- | Successor of Church numeral, i.e. the next numeral.
ns :: Nat a -> Nat a
ns nat f x = f (nat f x)

-- | Addition of Church numerals.
nplus :: Nat a -> Nat a -> Nat a
nplus nat1 nat2 f x = nat1 f $ nat2 f x

-- | Multuplication of Church numerals.
nmult :: Nat a -> Nat a -> Nat a
nmult nat1 nat2 = nat2 . nat1

-- | Converts Natural to Church numeral.
nFromNatural :: Natural -> Nat a
nFromNatural 0 = nz
nFromNatural n = \f x -> f (nFromNatural (n - 1) f x)

-- | Converts Church numeral to number.
nToNum :: Num a => Nat a -> a
nToNum nat = nat (+ 1) 0
