module HW0.T2
  ( -- * types
    Not
    -- * functions
  , doubleNeg
  , reduceTripleNeg
  ) where

import Data.Void (Void)

type Not a = a -> Void

-- a -> Not (Not a) ~ a -> ((a -> Void) -> Void) ~ a -> (a -> Void) -> Void
doubleNeg :: a -> Not (Not a)
doubleNeg a negA = negA a

reduceTripleNeg :: Not (Not (Not a)) -> Not a
reduceTripleNeg tripleNegA a = tripleNegA (doubleNeg a)
