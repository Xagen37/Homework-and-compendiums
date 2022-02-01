module HW1.T3
  (
    Tree (..)
  , tdepth
  , tFromList
  , tinsert
  , tmember
  , tsize
  ) where

data Tree a
  = Leaf
  | Branch Int (Tree a) a (Tree a)
  deriving Show

-- | helper
mkBranch :: Tree a -> a -> Tree a -> Tree a
mkBranch Leaf val Leaf = Branch 1 Leaf val Leaf
mkBranch Leaf val (Branch sz l v r) = Branch (sz + 1) Leaf val right
  where
    right = Branch sz l v r
mkBranch (Branch sz l v r) val Leaf = Branch (sz + 1) left val Leaf
  where
    left  = Branch sz l v r
mkBranch (Branch leftSz ll lv lr) val (Branch rightSz rl rv rr) = Branch (leftSz + rightSz + 1) left val right
  where
    left  = Branch leftSz ll lv lr
    right = Branch rightSz rl rv rr

-- | Size of the tree, O(1).
tsize :: Tree a -> Int
tsize Leaf              = 0
tsize (Branch sz _ _ _) = sz

-- | Depth of the tree.
tdepth :: Tree a -> Int
tdepth Leaf                    = 0
tdepth (Branch _ left _ right) = max (tdepth left) (tdepth right) + 1

-- | Check if the element is in the tree, O(log n)
tmember :: Ord a => a -> Tree a -> Bool
tmember _ Leaf = False
tmember x (Branch _ left val right)
  | x < val   = tmember x left
  | x > val   = tmember x right
  | otherwise = True

-- | Insert an element into the tree, O(log n)
tinsert :: Ord a => a -> Tree a -> Tree a
tinsert x Leaf = mkBranch Leaf x Leaf
tinsert x (Branch _ left val right)
  | x < val   = mkBranch (tinsert x left) val right
  | x > val   = mkBranch left val (tinsert x right)
  | otherwise = mkBranch left val right

-- | Build a tree from a list, O(n log n)
tFromList :: Ord a => [a] -> Tree a
tFromList = foldr tinsert Leaf
