-- Task 1.a
task1a = \a b -> a . b
-- ghci> :t task1a
-- task1a :: (b -> c) -> (a -> b) -> a -> c

-- Task 1.b

task1b = \f a -> floor . f $ (0::Double) + fromInteger a

-- for testing
double_abs:: Double -> Double
double_abs n
    | n < 0 = (0::Double) - n
    | otherwise = n

int_abs = task1b double_abs

-- ghci> :t task1b
-- task1b :: (Double -> Double) -> Integer -> Integer
-- ghci> int_abs 99
-- 99
-- ghci> int_abs (-99)
-- 99
-- ghci> double_abs 99.99
-- 99.99
-- ghci> double_abs (-99.99)
-- 99.99

-- Task 2
-- Выражение: \f -> f $ ($) $ (.)
-- Добавим скобок: \f -> (f $ (($) $ (.)))
-- Выражение ($) имеет тип (a1 -> b1) -> (a1 -> b1) (принимает на вход функцию и возвращает функцию того же типа)
-- Выражение (.) имеет тип (b2 -> c2) -> (a2 -> b2) -> a2 -> c2
-- Выражение ($) $ (.) имеет тип (b2 -> c2) -> (a2 -> b2) -> a2 -> c2, такой же как у (.)
-- Функция f принимает на вход выражение ($) $ (.) и может возвращать произвольный тип a3
-- Тогда f имеет тип ((b2 -> c2) -> (a2 -> b2) -> a2 -> c2) -> a3
-- Выражение \f -> f $ ($) $ (.) принимает на вход f и возвращает тот же тип, что и f.
-- Тогда \f -> f $ ($) $ (.) имеет тип (((b2 -> c2) -> (a2 -> b2) -> a2 -> c2) -> a3) -> a3
-- Проверяем: компилятор сообщает тип  (((b1 -> c ) -> (a  -> b1) -> a  -> c ) -> b2) -> b2

-- Task 3a

task3a :: Bool -> Bool -> Bool
task3a False b = b
task3a a False = a
task3a True True = False

-- ghci> task3a True True
-- False
-- ghci> task3a True False 
-- True
-- ghci> task3a False True 
-- True
-- ghci> task3a False False 
-- False

-- Task 3b

maj a b c | a == b = a
maj a b c | a == c = a
maj a b c | b == c = b

-- ghci> maj 1 1 2
-- 1
-- ghci> maj 1 2 1
-- 1
-- ghci> maj 2 1 1
-- 1
-- ghci> maj 1 1 1
-- 1

-- Task 4

fib n
    | n < 2 = n
    | otherwise = (fib $ n - 1) + (fib $ n - 2)

-- ghci> [[n,fib n] | n <- [0..9]]
-- [[0,0],[1,1],[2,1],[3,2],[4,3],[5,5],[6,8],[7,13],[8,21],[9,34]]

f_part n start
    | start == n+1 = 0
    | otherwise = start ^ (fib n) + f_part n (start + 1)

-- ghci> fib 0
-- 0
-- ghci> f_part 0 0
-- 1
-- ghci> fib 1
-- 1
-- ghci> f_part 1 1
-- 1
-- ghci> f_part 1 0
-- 1
-- ghci> fib 2
-- 1
-- ghci> f_part 2 2
-- 2
-- ghci> f_part 2 1
-- 3
-- ghci> f_part 2 0
-- 3
-- ghci> fib 3
-- 2
-- ghci> f_part 3 3
-- 9
-- ghci> f_part 3 2
-- 13
-- ghci> f_part 3 1
-- 14
-- ghci> f_part 3 0
-- 14

f n = f_part n 0

task4 = f

-- Task 5

triples = [
    (w,e,q-w-e)
    |   q <- [0..]
    ,   w <- [0..q]
    ,   e <- [0..q-w]
    ]

pythagorean_triples = [
    (a,b,c)
    |   (a,b,c) <- triples
    ,   a^2 + b^2 == c^2
    ]

-- ghci> take 13 pythagorean_triples 
-- [(0,0,0),(0,1,1),(1,0,1),(0,2,2),(2,0,2),(0,3,3),(3,0,3),(0,4,4),(4,0,4),(0,5,5),(5,0,5),(0,6,6),(3,4,5)]

-- Task 6

get_own_dividers_from :: Integer -> Integer -> [Integer]
get_own_dividers_from n k
    | k == n = []
    | n `mod` k == 0 = k : get_own_dividers_from n (k+1)
    | otherwise = get_own_dividers_from n (k+1)

get_own_dividers n = get_own_dividers_from n 1

task6 m n = n == (sum . get_own_dividers $ m) && m == (sum . get_own_dividers $ n)

-- Task 7

curry' :: ((a, b) -> c) -> a -> b -> c
uncurry' :: (a -> b -> c) -> ((a, b) -> c)

curry' f a b = f (a,b)
uncurry' f p = f (fst p) (snd p)

-- Task 8

f8 = curry(h . (uncurry g))

-- for testing
g a b = [a, b]
h a = 0 : a
f8' x y = h (g x y)

-- ghci> f8 1 2
-- [0,1,2]
-- ghci> f8' 1 2
-- [0,1,2]
-- ghci> 

-- Task 9a

-- Объекты данных типов могут быть легко преобзованы с помощью этих функций:
task9a_left_to_right f
    = (
        fst . f,
        snd . f
    )

task9a_right_to_left f c
    = (
        fst f c,
        snd f c
    )

-- Task 9b

-- Объекты данных типов могут быть легко преобзованы с помощью этих функций:
task9b_left_to_right = uncurry

task9b_right_to_left = curry
