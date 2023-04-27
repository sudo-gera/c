import math
import random
task = 14
if task == 1:
    val = input()
    while val != 0:
        val = int(input())
if task == 2:
    val = int(input())
    sq_sum = val**2
    while val != 0:
        val = int(input())
        sq_sum += val
    print(sq_sum)
if task == 3:
    n = int(input())
    q = 1
    while q <= n:
        print(q*q)
        q += 1
if task == 4:
    x = int(100*float(input()))
    p = int(input())
    y = int(100*float(input()))
    years = 0
    while x < y:
        x *= p+100
        x //= 100
        years += 1
    print(years)
if task == 5:
    n = int(input())
    while n and n % 2 == 0:
        n //= 2
    if n == 1:
        print('YES')
    else:
        print('NO')
if task == 6:
    a = int(input())
    b = int(input())
    while b:
        a %= b
        c = a
        a = b
        b = c
    print(a)
if task == 7:
    n = int(input())
    if n < 2:
        print('Не простое')
    else:
        q = 2
        while q < n:
            if n % q == 0:
                print('Не простое')
                break
            q += 1
        else:
            print('Простое')
if task == 8:
    n = int(input())
    q = 0
    w = 1
    while n:
        print(q)
        w += q
        q = w-q
        n -= 1
if task == 9:
    n = float(input())
    a = float(input())
    b = float(input())
    if n > math.pi**2*(3*a+b)/24:
        print(float('inf'))
    else:
        k = 0
        c = a
        s = 0
        while s <= n:
            k += 1
            s += c/k/k
            c = a+b-c
        print(k)
if task == 10:
    n = int(input())
    while n:
        print(random.randint(1, 10))
        n -= 1
if task == 11:
    n = int(input())
    for q in range(n):
        print(random.random()*10-5)
if task == 12:
    n = int(input())-1
    _min = 0
    while n:
        r = random.randint(-10, 10)
        print(r)
        if r < _min:
            _min = r
        n -= 1
    print(0)
    print(_min)
if task == 13:
    n = int(input())
    _max = 0
    index_max = -1
    index = 0
    while index < n-1:
        r = random.randint(-10, 10)
        print(r)
        if r > _max:
            _max = r
            index_max = index
        index += 1
    print(0)
    index_max %= n
    print(index_max)
if task == 14:
    n = int(input())
    while n:
        r = random.randint(0, 1)
        print(r)
        n -= r
    print(0)
