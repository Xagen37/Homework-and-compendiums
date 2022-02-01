module HW2.T1
  ( -- * Datatypes
    Annotated (..)
  , Except (..)
  , Fun (..)
  , List (..)
  , Option (..)
  , Pair (..)
  , Prioritised (..)
  , Quad (..)
  , Stream (..)
  , Tree (..)
    -- * map functions
  , mapAnnotated
  , mapExcept
  , mapFun
  , mapList
  , mapOption
  , mapPair
  , mapPrioritised
  , mapQuad
  , mapStream
  , mapTree
  ) where

import Prelude ()

data Option a
  = None
  | Some a

data Pair a = P a a

data Quad a = Q a a a a

data Annotated e a = a :# e
infix 0 :#

data Except e a
  = Error e
  | Success a

data Prioritised a
  = Low a
  | Medium a
  | High a

data Stream a = a :> Stream a
infixr 5 :>

data List a
  = Nil
  | a :. List a
infixr 5 :.

newtype Fun i a = F (i -> a)

data Tree a
  = Leaf
  | Branch
    (Tree a)
    a
    (Tree a)

mapOption :: (a -> b) -> (Option a -> Option b)
mapOption f = optionF where
  optionF None     = None
  optionF (Some a) = Some (f a)

mapPair :: (a -> b) -> (Pair a -> Pair b)
mapPair f = pairF where
  pairF (P a b) = P (f a) (f b)

mapQuad :: (a -> b) -> (Quad a -> Quad b)
mapQuad f = quadF where
  quadF (Q a b c d) = Q (f a) (f b) (f c) (f d)

mapAnnotated :: (a -> b) -> (Annotated e a -> Annotated e b)
mapAnnotated f = annotatedF where
  annotatedF (a :# e) = f a :# e

mapExcept :: (a -> b) -> (Except e a -> Except e b)
mapExcept f = exceptF where
  exceptF (Error e)   = Error e
  exceptF (Success a) = Success (f a)

mapPrioritised :: (a -> b) -> (Prioritised a -> Prioritised b)
mapPrioritised f = prioritisedF where
  prioritisedF (Low a)    = Low (f a)
  prioritisedF (Medium a) = Medium (f a)
  prioritisedF (High a)   = High (f a)

mapStream :: (a -> b) -> (Stream a -> Stream b)
mapStream f = streamF where
  streamF (a :> rest) = (f a) :> mapStream f rest

mapList :: (a -> b) -> (List a -> List b)
mapList f = listF where
  listF Nil         = Nil
  listF (a :. rest) = (f a) :. mapList f rest

mapFun :: (a -> b) -> (Fun i a -> Fun i b)
mapFun f = funF where
  funF (F inner) = F (\a -> f (inner a))

mapTree :: (a -> b) -> (Tree a -> Tree b)
mapTree f = treeF where
  treeF Leaf                  = Leaf
  treeF (Branch left a right) = Branch (mapTree f left) (f a) (mapTree f right)
