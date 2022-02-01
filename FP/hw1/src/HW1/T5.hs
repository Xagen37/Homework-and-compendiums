module HW1.T5
  (
    joinWith
  , splitOn
  ) where

import Data.List.NonEmpty (NonEmpty ((:|)))

splitOn :: Eq a => a -> [a] -> NonEmpty [a]
splitOn delim = foldr helper ([] :| [])
  where
    helper val (h :| t)
      | val == delim = [] :| (h : t)
      | otherwise    = (val : h) :| t

joinWith :: a -> NonEmpty [a] -> [a]
joinWith sep = foldl1 helper
  where
    helper accum x = accum ++ [sep] ++ x
