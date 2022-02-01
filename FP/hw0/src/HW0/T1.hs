{-# LANGUAGE TypeOperators #-}
module HW0.T1
  ( -- * Datatypes
    type (<->) (..)
    -- * functions
  , assocEither
  , assocPair
  , distrib
  , flipIso
  , runIso
  ) where

data a <-> b = Iso (a -> b) (b -> a)

flipIso :: (a <-> b) -> (b <-> a)
flipIso (Iso f g) = Iso g f

runIso :: (a <-> b) -> (a -> b)
runIso (Iso f _) = f

distrib :: Either a (b, c) -> (Either a b, Either a c)
distrib (Left l)         = (Left l, Left l)
distrib (Right (r1, r2)) = (Right r1, Right r2)

assocPair :: (a, (b, c)) <-> ((a, b), c)
assocPair = Iso to from
  where
    to (l, (r1, r2)) = ((l, r1), r2)
    from ((l1, l2), r) = (l1, (l2, r))

assocEither :: Either a (Either b c) <-> Either (Either a b) c
assocEither = Iso to from
  where
    to ei = case ei of
      Left a          -> Left (Left a)
      Right (Left b)  -> Left (Right b)
      Right (Right c) -> Right c
    from ei = case ei of
      Left (Left a)  -> Left a
      Left (Right b) -> Right (Left b)
      Right c        -> Right (Right c)
