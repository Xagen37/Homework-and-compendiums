module HW2.T3
  ( joinAnnotated
  , joinExcept
  , joinFun
  , joinList
  , joinOption
  ) where

import HW2.T1 (Annotated ((:#)), Except (Error, Success), Fun (F), List (Nil, (:.)),
               Option (None, Some))
import HW2.T2 (concatLists)

joinOption :: Option (Option a) -> Option a
joinOption None            = None
joinOption (Some None)     = None
joinOption (Some (Some a)) = Some a

joinExcept :: Except e (Except e a) -> Except e a
joinExcept (Error e)             = Error e
joinExcept (Success (Error e))   = Error e
joinExcept (Success (Success a)) = Success a

joinAnnotated :: Semigroup e => Annotated e (Annotated e a) -> Annotated e a
joinAnnotated ((a :# e1) :# e2) = a :# (e2 <> e1)

joinList :: List (List a) -> List a
joinList Nil                       = Nil
joinList (first :. Nil)            = first
joinList (first :. second :. rest) = joinList ((concatLists first second) :. rest)


joinFun :: Fun i (Fun i a) -> Fun i a
joinFun (F inner) = F joinedF where
  extractor (F func) arg = func arg
  joinedF arg = extractor (inner arg) arg
