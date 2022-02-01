module HW2.T4
  ( -- * Datatypes
    Expr (..)
  , Prim (..)
  , State (..)
    -- * map functions
  , eval
  , joinState
  , mapState
  , modifyState
  , wrapState
  ) where

import qualified Control.Monad
import HW2.T1 (Annotated ((:#)), mapAnnotated)

data State s a = S
  { runS :: s -> Annotated s a
  }

mapState :: (a -> b) -> State s a -> State s b
mapState f (S argRunS) = S { runS = mapAnnotated f . argRunS}

wrapState :: a -> State s a
wrapState a = S { runS = (:#) a}

joinState :: State s (State s a) -> State s a
joinState (S outerRunS) = S { runS = joinedRunS } where
  innerRunS (sIn :# a) = runS sIn a
  joinedRunS = innerRunS . outerRunS

modifyState :: (s -> s) -> State s ()
modifyState f = S { runS = modifiedRunS } where
  modifiedRunS s = () :# f s

instance Functor (State s) where
  fmap = mapState

instance Applicative (State s) where
  pure = wrapState
  p <*> q = Control.Monad.ap p q

instance Monad (State s) where
  m >>= f = joinState (fmap f m)

data Prim a =
    Add a a      -- ^ (+)
  | Sub a a      -- ^ (-)
  | Mul a a      -- ^ (*)
  | Div a a      -- ^ (/)
  | Abs a        -- ^ abs
  | Sgn a        -- ^ signum

data Expr =
  Val Double
  | Op (Prim Expr)

instance Num Expr where
  x + y         = Op (Add x y)
  x * y         = Op (Mul x y)
  x - y         = Op (Sub x y)
  abs x         = Op (Abs x)
  signum x      = Op (Sgn x)
  fromInteger x = Val (fromInteger x)

instance Fractional Expr where
  x / y          = Op (Div x y)
  fromRational x = Val (fromRational x)

eval :: Expr -> State [Prim Double] Double
eval (Val x) = return x
eval (Op (Add x y)) = do
  xEval <- eval x
  yEval <- eval y
  modifyState (Add xEval yEval :)
  return (xEval + yEval)
eval (Op (Sub x y)) = do
  xEval <- eval x
  yEval <- eval y
  modifyState (Sub xEval yEval :)
  return (xEval - yEval)
eval (Op (Mul x y)) = do
  xEval <- eval x
  yEval <- eval y
  modifyState (Mul xEval yEval :)
  return (xEval * yEval)
eval (Op (Div x y)) = do
  xEval <- eval x
  yEval <- eval y
  modifyState (Div xEval yEval :)
  return (xEval / yEval)
eval (Op (Abs x)) = do
  xEval <- eval x
  modifyState (Abs xEval :)
  return (abs xEval)
eval (Op (Sgn x)) = do
  xEval <- eval x
  modifyState (Sgn xEval :)
  return (signum xEval)
