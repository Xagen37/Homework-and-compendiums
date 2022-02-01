module HW1.T1
  (
    Day (..)
  , afterDays
  , daysToParty
  , isWeekend
  , nextDay
  ) where

import GHC.Natural

data Day = Monday | Tuesday | Wednesday | Thursday | Friday | Saturday | Sunday
  deriving (Show, Eq)

-- | Returns the day that follows the day of the week given as input.
nextDay :: Day -> Day
nextDay day =
  case day of
    Monday    -> Tuesday
    Tuesday   -> Wednesday
    Wednesday -> Thursday
    Thursday  -> Friday
    Friday    -> Saturday
    Saturday  -> Sunday
    Sunday    ->  Monday

-- | Returns the day of the week after a given number of days has passed.
afterDays :: Natural -> Day -> Day
afterDays n 
  | n == 0    = id
  | otherwise = nextDay . afterDays (n - 1)


-- | Checks if the day is on the weekend.
isWeekend :: Day -> Bool
isWeekend day = day == Saturday || day == Sunday

-- | Computes the number of days until the next Friday.
daysToParty :: Day -> Natural
daysToParty day
  | day == Friday = 0
  | otherwise = daysToParty (nextDay day) + 1
