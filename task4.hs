-- Task 2
data Nat = Z | S Nat
    deriving (Eq, Show)

data NatB = ZB | Db NatB | DbI NatB
    deriving (Eq, Show)

-- Nat и NatB изоморфны неотрицательным значениям типа Integer
-- следовательно, изоморфны.

-- интерпретация понятна из двух функций ниже

convert_NatB_to_Integer ZB = 0
convert_NatB_to_Integer (Db  n) = (convert_NatB_to_Integer n) * 2 + 1
convert_NatB_to_Integer (DbI n) = (convert_NatB_to_Integer n) * 2 + 2

convert_Integer_to_NatB n
    | n == 0 = ZB
    | n `mod` 2 == 0 = DbI . convert_Integer_to_NatB $ n `div` 2 - 1
    | n `mod` 2 /= 0 = Db  . convert_Integer_to_NatB $ n `div` 2 - 0


convert_Integer_to_Nat n
    | n == 0 = Z
    | otherwise = (S . convert_Integer_to_Nat) $ (n - 1)

convert_Nat_to_Integer Z = 0
convert_Nat_to_Integer (S n) = 1 + convert_Nat_to_Integer n

nat2natb = convert_Integer_to_NatB . convert_Nat_to_Integer
natb2nat = convert_Integer_to_Nat . convert_NatB_to_Integer

-- for testing

generate_all_NatB_with_given_length_impl r n
    | n == 0 = [r]
    | n /= 0 = [r]
    ++ generate_all_NatB_with_given_length_impl (Db  r) (n - 1)
    ++ generate_all_NatB_with_given_length_impl (DbI r) (n - 1)

generate_all_Nat_with_given_length_impl r n
    | n == 0 = [r]
    | n /= 0 = [r]
    ++ generate_all_Nat_with_given_length_impl (S  r) (n - 1)

generate_all_NatB_with_given_length = generate_all_NatB_with_given_length_impl ZB
generate_all_Nat_with_given_length  = generate_all_Nat_with_given_length_impl  Z
 
sort a
    | length a < 2 = a
    | otherwise =
        let x = a !! 0 in
        sort [q | q <- a, q < x]
        ++ [q | q <- a, q == x] ++
        sort [q | q <- a, q > x]


-- ghci> nats = generate_all_Nat_with_given_length 9
-- ghci> natbs = generate_all_NatB_with_given_length 9
-- ghci> int_nats = sort [convert_Nat_to_Integer q | q <- nats]
-- ghci> int_nats == [0..(length int_nats)-1]
-- True
-- ghci> int_natbs = sort [convert_NatB_to_Integer q | q <- natbs]
-- ghci> int_natbs == [0..(length int_natbs)-1]
-- True
-- ghci> natbs == [convert_Integer_to_NatB . convert_NatB_to_Integer $ q | q <- natbs]
-- True
-- ghci> nats == [convert_Integer_to_Nat . convert_Nat_to_Integer $ q | q <- nats]
-- True

-- Task 3

pairs_with_sum n = [(a,n-a) | a <- [0..n]]

pairs_with_sum_le n = [p | q <- [0..n], p <- pairs_with_sum q]

segs a = [ take ((length a) - (snd p) - (fst p)) (drop (fst p) a) | p <- pairs_with_sum_le ((length a)-1)]

-- ghci> segs "hello"
-- ["hello","hell","ello","hel","ell","llo","he","el","ll","lo","h","e","l","l","o"]
-- ghci> segs "123"
-- ["123","12","23","1","2","3"]

-- Task 4

nrem n a = [fst q | q <- (zip a [1..]), (snd q) `mod` n /= 0]

-- ghci> nrem 3 [1,2,3,4,5,6,7]
-- [1,2,4,5,7]

-- Task 5

uniq l = foldr (\e l -> if elem e l then l else e : l) [] l

-- ghci> uniq [1,2,3,2,1,2,3]
-- [1,2,3]

-- Task 6

array_mul_by_concat a s = [q ++ w | q <- a, w <- s]

array_pow_by_concat_impl l n = foldr array_mul_by_concat [[0]] [l | q <- [1..n]]

array_pow l n = [take ((length q) - 1) q | q <- (array_pow_by_concat_impl [[q] | q<-l] n)]

part m n = [q | q <- array_pow [0..n] m, (sum q) == n]

-- Task 7

map' f l = foldr (\e l -> (f e) : l) [] l

filter' f l = foldr (\e l -> if (f e) then e : l else l) [] l

all' f l = foldr ((&&) . f) True l

any' f l = foldr ((||) . f) False l

-- Task 8

-- takeWhile берёт префикс массива до первого элемента, который не удовлетворяет условию
-- dropWhile берёт суффикс массива с  первого элемента, который не удовлетворяет условию

takeWhile' f l
    | l == [] = []
    | (f (l !! 0)) = l!!0 : takeWhile' f (drop 1 l)
    | otherwise = []

dropWhile' f l
    | l == [] = []
    | (f (l !! 0)) = dropWhile' f . drop 1 $ l
    | otherwise = l

-- Task 9

-- foldr1 применяет функцию к двум последним элементам, потом к элементу перед ними и результату и так далее

foldr1' f l = foldr f ((reverse l)!!0) . reverse . drop 1 . reverse $ l

lmax l = foldr1 max l

-- Task 10

prefixes l = [take n l | n <- [0..length l]]

-- Task 11

rotts1 l = take ((length l)) (iterate (\l -> (drop 1 l) ++ (take 1 l)) l)

rotts2 l = scanl (\l _ -> (drop 1 l) ++ (take 1 l)) l [2..length l]

-- Task 12

-- unzip превращает список пар в пару списков

unzip1 l = (map fst l, map snd l)

unzip2 l = (
    foldr ((:) . fst) [] l,
    foldr ((:) . snd) [] l
    )




