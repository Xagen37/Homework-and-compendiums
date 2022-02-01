{-# LANGUAGE BlockArguments             #-}
{-# LANGUAGE DerivingStrategies         #-}
{-# LANGUAGE GeneralizedNewtypeDeriving #-}

module HW2.T6
  ( -- * Datatypes
    ParseError (..)
  , Parser (..)
    -- * functions
  , pChar
  , pEof
  , parseError
  , parseExpr
  , runP
  ) where

import Control.Applicative (Alternative (..), Applicative (..), many, optional, some)
import Control.Monad (MonadPlus, mfilter, msum, void)
import Data.Char (digitToInt, isDigit, isSpace)
import Data.Maybe (isNothing)
import Data.Scientific (scientific, toRealFloat)
import GHC.Natural (Natural)
import HW2.T1 (Annotated ((:#)), Except (Error, Success))
import HW2.T4 (Expr (Op, Val), Prim (Add, Div, Mul, Sub))
import HW2.T5 (ExceptState (ES, runES))

newtype ParseError = ErrorAtPos Natural

newtype Parser a = P (ExceptState ParseError (Natural, String) a)
  deriving newtype (Functor, Applicative, Monad)

runP :: Parser a -> String -> Except ParseError a
runP (P parser) str = answer where
  result = runES parser (0, str)
  answer = case result of
    Error e               -> Error e
    (Success (answ :# _)) -> Success answ

-- | This parses parses one character.
-- It takes current state: a positition and a string.
-- If the string is empty, then an error is returned.
-- Otherwise, it parses the next character of the string,
-- which results in changing its state by increasing the position by one
-- and removing a prefix, consisting of parsed character, from string.
pChar :: Parser Char
pChar = P $ ES \(pos, str) ->
  case str of
    []     -> Error (ErrorAtPos pos)
    (c:cs) -> Success (c :# (pos + 1, cs))

parseError :: Parser a
parseError = P (ES \(pos, _) -> Error (ErrorAtPos pos))

instance Alternative Parser where
  empty = parseError
  (<|>) (P firstP) (P secondP) = P (ES answer) where
    firstRes str = runES firstP str
    answer str = case firstRes str of
      Error _        -> runES secondP str
      (Success answ) -> Success answ

instance MonadPlus Parser   -- No methods.

pEof :: Parser ()
pEof = P (ES isEmpty) where
  isEmpty (pos, []) = Success (() :# (pos + 1, []))
  isEmpty (pos, _)  = Error (ErrorAtPos pos)

-- | Checks, if the next parsed value satisfies predicate
satisfy :: Parser Char -> (Char -> Bool) -> Parser Char
satisfy parser predicate = do
  ch <- parser
  if predicate ch
    then return ch
    else parseError

-- | Parse specific char or fail
isChar :: Char -> Parser Char
isChar ch = satisfy pChar (== ch)

-- | Parse one digit
pDigit :: Parser Int
pDigit = fmap digitToInt (satisfy pChar isDigit)

-- | Parse several digits
pSomeDigits :: Parser [Int]
pSomeDigits = some pDigit

-- | Concat lists of Int, i. e. make Integer from digits
concatDigits :: [Int] -> Integer
concatDigits = foldl concatter 0 where
  concatter accum digit = accum * 10 + toInteger digit

-- | Parse Integer value
pInteger :: Parser Integer
pInteger = fmap concatDigits pSomeDigits

-- | Parse Double value
pDouble :: Parser Double
pDouble = do
  trunc <- pSomeDigits
  dot   <- optional (isChar '.')
  if isNothing dot
    then return (fromInteger(concatDigits trunc))
    else do
      frac         <- pSomeDigits
      let fracSize = length frac
      let number   = concatDigits (trunc ++ frac)
      return (toRealFloat (scientific number (- fracSize)))

-- | Parse Val
pVal :: Parser Expr
pVal = fmap Val pDouble

-- | Skip whitespaces before the next parser
skipWhitespace :: Parser a -> Parser a
skipWhitespace parser = do
  _ <- many (mfilter isSpace pChar)
  parser

-- | Parse Expr in brackets
pBrackets :: Parser Expr
pBrackets = do
  _    <- isChar '('
  expr <- pLowOrder
  _    <- isChar ')'
  return expr

-- | Parse Val or Expr in brackets
pTerm :: Parser Expr
pTerm = pVal <|> pBrackets <|> parseError

-- | Parse Mul and Div operation
pHighOrder :: Parser Expr
pHighOrder = undefined

-- | Parse Add and Sub operations
pLowOrder :: Parser Expr
pLowOrder = undefined

parseExpr :: String -> Except ParseError Expr
parseExpr = undefined
