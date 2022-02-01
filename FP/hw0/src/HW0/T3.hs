module HW0.T3
  ( -- * functions
    compose
  , contract
  , i
  , k
  , permute
  , s
  ) where

s :: (a -> b -> c) -> (a -> b) -> (a -> c)
s f g x = f x (g x)

k :: a -> b -> a
k x y = x

i :: a -> a
i = s k k

compose :: (b -> c) -> (a -> b) -> (a -> c)
compose = s (k s) k

contract :: (a -> a -> b) -> (a -> b)
contract = s s (k (s k k))

permute :: (a -> b -> c) -> (b -> a -> c)
permute = s ((s (k s) k) (s (k s) k) s) (k k)
