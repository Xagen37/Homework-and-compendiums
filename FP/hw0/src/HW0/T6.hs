module HW0.T6
  ( a
  , a_whnf
  , b
  , b_whnf
  , c
  , c_whnf
  ) where

import Data.Char (isSpace)
import HW0.T1 (distrib)

a :: (Either [Char] b, Either [Char] c)
a = distrib (Left ("AB" ++ "CD" ++ "EF"))     -- distrib from HW0.T1

b :: [Bool]
b = map isSpace "Hello, World"

c :: [Char]
c = if 1 > 0 || error "X" then "Y" else "Z"

a_whnf :: (Either [Char] b1, Either [Char] c)
a_whnf = (Left ("AB" ++ "CD" ++ "EF"), Left ("AB" ++ "CD" ++ "EF"))  -- constructor (,)

b_whnf :: [Bool]
b_whnf = [False, False, False, False, False, False,
          True, False, False, False, False, False]  -- constructor []

c_whnf :: [Char]
c_whnf = "Y"  -- constructor []
