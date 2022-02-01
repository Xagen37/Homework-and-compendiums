module HW2.T5
  ( -- * Datatypes
    EvaluationError (..)
  , ExceptState (..)
    -- * map functions
  , eval
  , joinExceptState
  , mapExceptState
  , modifyExceptState
  , throwExceptState
  , wrapExceptState
  ) where

import qualified Control.Monad
import HW2.T1 (Annotated ((:#)), Except (Error, Success), mapAnnotated, mapExcept)
import HW2.T4 (Expr (Op, Val), Prim (Abs, Add, Div, Mul, Sgn, Sub))

data ExceptState e s a = ES
  { runES :: s -> Except e (Annotated s a)
  }

mapExceptState :: (a -> b) -> ExceptState e s a -> ExceptState e s b
mapExceptState f exceptState = ES { runES = mappedRunES} where
  mappedRunES s = mapExcept (mapAnnotated f) (runES exceptState s)

wrapExceptState :: a -> ExceptState e s a
wrapExceptState a = ES { runES = Success . (:#) a }

joinExceptState :: ExceptState e s (ExceptState e s a) -> ExceptState e s a
-- joinExceptState (ES f) = ES { runES = \el -> case f el of
--   Error e -> Error e
--   Success ((ES g) :# res) -> g res }
joinExceptState (ES outerRunES) = ES { runES = joinedRunES } where
  joinedRunES s = case outerRunES s of
    Error e                        -> Error e
    Success ((ES innerRunES) :# a) -> innerRunES a


modifyExceptState :: (s -> s) -> ExceptState e s ()
modifyExceptState f = ES { runES = modifiedRunES } where
  modifiedRunES s = Success (() :# f s)

throwExceptState :: e -> ExceptState e s a
throwExceptState e = ES { runES = \_ -> (Error e)}

instance Functor (ExceptState e s) where
  fmap = mapExceptState

instance Applicative (ExceptState e s) where
  pure = wrapExceptState
  p <*> q = Control.Monad.ap p q

instance Monad (ExceptState e s) where
  m >>= f = joinExceptState (fmap f m)

data EvaluationError = DivideByZero

eval :: Expr -> ExceptState EvaluationError [Prim Double] Double
eval (Val x) = return x
eval (Op (Add x y)) = do
  xEval <- eval x
  yEval <- eval y
  modifyExceptState (Add xEval yEval :)
  return (xEval + yEval)
eval (Op (Sub x y)) = do
  xEval <- eval x
  yEval <- eval y
  modifyExceptState (Sub xEval yEval :)
  return (xEval - yEval)
eval (Op (Mul x y)) = do
  xEval <- eval x
  yEval <- eval y
  modifyExceptState (Mul xEval yEval :)
  return (xEval * yEval)
eval (Op (Div x y)) = do
  xEval <- eval x
  yEval <- eval y
  if yEval == 0.0
    then throwExceptState DivideByZero
    else modifyExceptState (Div xEval yEval :)
  return (xEval / yEval)
eval (Op (Abs x)) = do
  xEval <- eval x
  modifyExceptState (Abs xEval :)
  return (abs xEval)
eval (Op (Sgn x)) = do
  xEval <- eval x
  modifyExceptState (Sgn xEval :)
  return (signum xEval)
