module HW0.T4
  ( -- * functions
    fac
  , fib
  , map'
  , repeat'
  ) where

import Data.Function (fix)
import Data.List (genericIndex)
import GHC.Natural (Natural)

-- | Behaves like Data.List.repeat
repeat' :: a -> [a]
repeat' x = fix (x:)

-- | Behaves like Data.List.map
map' :: (a -> b) -> [a] -> [b]
map' g = fix m
  where
    m _ []       = []
    m f (x : xs) = g x : f xs

-- | Helper function for fib. Creates list of fibonacci numbers.
createFib :: [Natural]
createFib = 0 : 1 : fix fib' 0 1
  where
    fib' f prev1 prev2 = n : f prev2 n
      where
        n = prev1 + prev2

-- | Computes the n-th Fibonacci number
fib :: Natural -> Natural
fib = genericIndex createFib

-- | Computes the factorial
fac :: Natural -> Natural
fac = fix fac' 1
  where
    fac' _ acc 0 = acc
    fac' f acc n = f (acc * n) (n - 1)
