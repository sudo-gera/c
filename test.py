import math
import prettytable
import random
task = 21
if task == 1:
    n = int(input())
    s = 0
    for i in range(1, 2*n):
        s += i*(i+1)
    print(s)
if task == 2:
    a = int(input())
    b = int(input())
    p = prettytable.PrettyTable()
    p.field_names = ['x', 'e^x-sin(x)']
    max_f = math.e**a-math.sin(a)
    min_f = math.e**b-math.sin(b)
    for x in range(a, b+1):
        p.add_row([x, math.e**x-math.sin(x)])
        max_f = max(max_f, p.rows[-1][1])
        min_f = min(min_f, p.rows[-1][1])
    print(p)
    print(min_f, max_f)
if task == 3:
    a = 0
    b = 1
    a1 = int(input())
    a2 = int(input())
    while a <= a2:
        if a1 <= a <= a2:
            print(a)
        b += a
        a = b-a
if task == 4:
    x1 = float(input())
    x2 = float(input())
    h = float(input())
    y1 = float(input())
    y2 = float(input())
    g = float(input())
    print(' '*18, end='|')
    y = y1
    while y <= y2:
        print('%18.7f' % y, end=' ')
        y += g
    y = y1
    print()
    print('='*18, end='=')
    while y <= y2:
        print('='*18, end='=')
        y += g
    print()
    x = x1
    while x <= x2:
        print('%18.7f' % x, end='|')
        y = y1
        while y <= y2:
            print('%18.7f' % (5*x**2-12*y), end=' ')
            y += g
        print()
        x += h
if task == 5:
    n = int(input())
    x = float(input())
    m = 0
    s = 1
    f = 1
    y = 1
    while m <= n:
        print('|', m, '|', '%18.7f' % math.e**x, '|', '%18.7f' %
              s, '|', '%18.7f' % abs(math.e**x-s))
        m += 1
        f *= m
        y *= x
        s += y/f
if task == 6:
    x = float(input())
    e = float(input())
    m = 0
    s = 1
    f = 1
    y = 1
    p = prettytable.PrettyTable()
    p.field_names = ['num', 'cos(x)', 'sum', 'eps']
    p.add_row([m, math.cos(x), s, abs(math.cos(x)-s)])
    while p.rows[-1][-1] >= e:
        m += 1
        f *= 2*m
        f *= 2*m-1
        y *= x*x
        if m % 2:
            s -= y/f
        else:
            s += y/f
        p.add_row([m, math.cos(x), s, abs(math.cos(x)-s)])
    print(p)
    print(m)
if task == 7:
    a = float(input())
    b = float(input())
    c = float(input())
    d = float(input())
    x1 = float(input())
    x2 = float(input())
    h = float(input())
    x = x1
    p = prettytable.PrettyTable()
    p.field_names = ['x', 'ln(dx+1)^0.5', 'cmp to ax^2+bx+c']
    while x <= x2:
        if d*x+1 > 0 and math.log(d*x+1) >= 0:
            y = math.log(x*d+1)**0.5
            if y > a*x*x+b*x+c:
                p.add_row([x, y, 'above'])
            if y < a*x*x+b*x+c:
                p.add_row([x, y, 'below'])
            if y == a*x*x+b*x+c:
                p.add_row([x, y, 'equal'])
        else:
            p.add_row([x, '???', '???'])
        x += h
    print(p)
if task == 8:
    n = int(input())
    n5 = min(n, 5)
    c2 = 0
    for i in range(n5):
        if n5-i <= 3-c2:
            a = 2
        elif c2 >= 3:
            a = random.randint(0, 1)*2+1
        else:
            a = random.randint(1, 3)
        c2 += a == 2
        print(a)
    for i in range(5, n):
        a = random.randint(1, 3)
        print(a)
if task == 9:
    a = float(input())
    b = float(input())
    h = float(input())
    x = a
    while x <= b:
        print('%18.7f' % x, '%18.7f' % (math.sin(2*x)/x**2))
        x += h
if task == 10:
    s = input()
    s = s[-1:]+s[1:-1]+s[:1]
    print(s)
if task == 11:
    s = input()
    s = '<'+s+'>'
    print(s)
if task == 12:
    s = input()
    if len(s) > 7:
        s = s[:4]+'-'+s[-2:]
    print(s)
if task == 13:
    s = input()
    a = int(s[0])
    s = s[1:]
    for i in range(0, len(s), 2):
        if s[i] == '+':
            a += int(s[i+1])
        else:
            a -= int(s[i+1])
    print(a)
if task == 14:
    s = input()
    a = ''
    while s:
        a += '$'+s[:44]+'\n'
        s = s[44:]
    print(a)
if task == 15:
    s = input()
    s0 = input()
    s = s[::-1]
    s0 = s0[::-1]
    i = s.index(s0)
    print((s[:i]+s[i+len(s0):])[::-1])
    print(s.replace(s0, '', 1)[::-1])
if task == 16:
    x = float(input())
    n = int(input())
    s = 0
    for i in range(0, n):
        s += ((1-x)/(1+x))**(2*i+1)/(2*i+1)
    s //= 1
    s *= -2
    print(s)
if task == 17:
    x = float(input())
    n = int(input())
    s = math.log(2*x)
    num = 1
    den = 1
    y = 1
    for i in range(n):
        num *= i*2+1
        den *= i*2+2
        y *= x*x
        if i % 2:
            s -= num/den/(i*2+2)/y
        else:
            s += num/den/(i*2+2)/y
    print(s)
if task == 18:
    print('-inf')
if task == 19:
    n = input()
    for i in range(len(n)):
        for j in range(len(n)):
            if i < j and n[i] > n[j]:
                n = n[:i]+n[j]+n[i+1:j]+n[i]+n[j+1:]
    if n[0] == '0':
        for j in range(len(n)):
            if n[j] != '0':
                i = 0
                n = n[:i]+n[j]+n[i+1:j]+n[i]+n[j+1:]
                break
    print(n)
if task == 20:
    n = int(input())
    for i in range(1, n):
        c = 0
        for j in range(1, i):
            if i % j == 0:
                c += j
        if c == i:
            print(c)
if task == 21:
    n = int(input())
    a = 0
    b = 1
    while b <= n:
        b += a
        a = b-a
    while n:
        if n >= a:
            print(a)
            n -= a
        a = b-a
        b -= a
