module HW1.T7
  (
    DotString (..)
  , Fun (..)
  , Inclusive (..)
  , ListPlus (..)
  ) where

-- | Implement instances Semigroup and Monoid
data ListPlus a = a :+ ListPlus a | Last a
infixr 5 :+

instance Semigroup (ListPlus a)
  where
    (Last x) <> ys  = x :+ ys
    (x :+ xs) <> ys = x :+ (xs <> ys)

data Inclusive a b = This a | That b | Both a b

instance (Semigroup a, Semigroup b) => Semigroup (Inclusive a b)
  where
    (This a) <> (This b)     = This (a <> b)
    (That a) <> (That b)     = That (a <> b)
    (This a) <> (That b)     = Both a b
    (That a) <> (This b)     = Both b a
    (This a) <> (Both l r)   = Both (a <> l) r
    (That a) <> (Both l r)   = Both l (a <> r)
    (Both l r) <> (This a)   = Both (l <> a) r
    (Both l r) <> (That a)   = Both l (r <> a)
    (Both l r) <> (Both a b) = Both (l <> a) (r <> b)

newtype DotString = DS String

instance Semigroup DotString
  where
    (DS "")  <> (DS ds)  = DS ds
    (DS ds)  <> (DS "")  = DS ds
    (DS ds1) <> (DS ds2) = DS (ds1 ++ "." ++ ds2)

instance Monoid DotString
  where
    mempty = DS ""

newtype Fun a = F (a -> a)

instance Semigroup (Fun a)
  where
    (F a) <> (F b) = F (a . b)

instance Monoid (Fun a)
  where
    mempty = F id
