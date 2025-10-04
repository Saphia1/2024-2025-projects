second1 :: [a] -> Maybe a
second1 n = if length n >= 2 then Just(head (tail n)) else Nothing

second2 :: [a] -> Maybe a
second2 n = if length n >= 2 then Just(n !! 1) else Nothing

second3 :: [a] -> Maybe a
second3 (_:n:_) = Just n
second3 _     = Nothing

xor1 :: Bool -> Bool -> Bool
xor1 True True = False
xor1 True False = True
xor1 False True = True
xor1 False False = False

xor2 :: Bool -> Bool -> Bool
xor2 x y = if x == True && y == True
           then False
           else if x == False && y == False
           then False
           else True

xor3 :: Bool -> Bool -> Bool
xor3 x y = x /= y 

sumsqr :: Int -> Int
sumsqr n = sum[x^2| x <- [1..n]]

grid :: Int -> [(Int,Int)]
grid n = [(x,y) | x <- [1..n], y <- [1..n]]

euclid :: Int -> Int -> Int
euclid x y 
    |x == y     = x
    |x>y        = euclid (x-y) y
    |otherwise  = euclid x (y-x) 

fastrev :: [a] -> [a]
fastrev xs = rev xs []

rev :: [a] -> [a] -> [a]
rev [] ys = ys
rev (x:xs) ys = rev xs (x:ys)