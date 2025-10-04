import Data.Char
chomp :: String -> String -- selects run of repeated chars from start of a string with run being as long as possible
chomp ""="" --empty string
chomp (x:xs) = x:takeWhile(==x)xs

--xs = if length(chomp(xs))> 9 
   -- then take 9 xs
  --  else chomp(xs)
munch :: String -> String -- selects a run of repeated characters from the start of a string, with the run comprising at most nine characters
munch = take 9.chomp -- composition of take 9 function and chomp function

runs :: String -> [String]--splits a string into a list of runs of repeated characters, with each run comprising at most nine characters.
runs "" = []
runs xs = munch xs:runs(drop(length(munch xs))xs)

encode :: String -> [(Char,Int)]--transforms a string into a list of pairs comprising the character from each run together with its number of repetitions.
encode xs = [(head run, length run)|run<-runs xs]

flatten :: [(Char,Int)] -> String-- flattens a list of pairs of characters and digits to a string
flatten xs =concat[a:show b |(a,b)<- xs]
--iterate over every pair
--for every pair create new string of the two
--concatinate every string

compress :: String -> String--compresses a string using run-length encoding
compress =flatten . encode

decode :: [(Char,Int)] -> String
decode xs = concat[replicate b  a |(a,b)<- xs]

expand :: String -> [(Char,Int)]
expand []=[]
expand (x:y:xs) =(x, digitToInt y): expand xs

decompress :: String -> String
decompress = decode. expand