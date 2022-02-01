module HW1.T6
  (
    epart
  , mcat
  ) where

mcat :: Monoid a => [Maybe a] -> a
mcat = foldr helper mempty
  where
    helper Nothing accum    = accum
    helper (Just val) accum = mappend val accum

epart :: (Monoid a, Monoid b) => [Either a b] -> (a, b)
epart = foldr helper mempty
  where
    helper (Left left) (l, r)   = (mappend left l, r)
    helper (Right right) (l, r) = (l, mappend right r)
