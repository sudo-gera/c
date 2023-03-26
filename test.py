import math

task_num = 18

if task_num == 1:
    x = int(input())
    y = int(input())
    x = x % 100
    y = y % 100
    x = str(x)
    y = str(y)
    if len(x) == 1:
        x = '0'+x
    if len(y) == 1:
        y = '0'+y
    x = x+y
    x = int(x)
    print(x)

if task_num == 2:
    a = int(input())
    b = int(input())
    c = int(input())
    if a < 0 and b < 0 and c >= 0 or a < 0 and b >= 0 and c < 0 or a < 0 and b < 0 and c >= 0:
        print(True)
    else:
        print(False)

if task_num == 3:
    x = float(input())
    y = math.floor(x)
    print(x-y)

if task_num == 4:
    x = float(input())
    y = float(input())
    print(math.sqrt(x-math.sqrt(y)))

if task_num == 5:
    a = int(input())
    b = int(input())
    c = int(input())
    print((a//c)*(b//c))
    print(a*b-(a//c*c)*(b//c*c))

if task_num == 6:
    x = int(input())
    if x % 2 != 0 and 100 <= x <= 999:
        print(True)
    else:
        print(False)

if task_num == 7:
    x = float(input())
    y = float(input())
    z = float(input())
    max_ = x
    min_ = x
    if y > max_:
        max_ = y
    if y < min_:
        min_ = y
    if z > max_:
        max_ = z
    if z < min_:
        min_ = z
    u = (max_-min_)/min_
    print(u)

if task_num == 8:
    edu = input()
    if len(edu) == '':
        edu = 'NoInfo'
    print(edu)

if task_num == 9:
    r = float(input())
    r = int(r*100)
    x = r//100
    y = r % 100
    print(x, end=' ')
    if x % 10 == 1 and x % 100 != 11:
        print('рубль', end=' ')
    elif x % 10 == 2 and x % 100 != 12:
        print('рубля', end=' ')
    elif x % 10 == 3 and x % 100 != 13:
        print('рубля', end=' ')
    elif x % 10 == 4 and x % 100 != 14:
        print('рубля', end=' ')
    else:
        print('рублей', end=' ')
    print(y, end=' ')
    if y % 10 == 1 and y % 100 != 11:
        print('копейка', end=' ')
    elif y % 10 == 2 and y % 100 != 12:
        print('копейки', end=' ')
    elif y % 10 == 3 and y % 100 != 13:
        print('копейки', end=' ')
    elif y % 10 == 4 and y % 100 != 14:
        print('копейки', end=' ')
    else:
        print('копеек', end=' ')
    print()

if task_num == 10:
    x1 = int(input())
    y1 = int(input())
    x2 = int(input())
    y2 = int(input())
    if x2 < x1:
        dx = x1-x2
    else:
        dx = x2-x1
    if y2 < y1:
        dy = y1-y2
    else:
        dy = y2-y1
    if dx == 0 or dy == 0 or dx == dy:
        print(True)
    else:
        print(False)

if task_num == 11:
    x = float(input())
    if x > -1:
        y = math.log(3*x**2-15)
    else:
        x = math.pi*x/180
        y = math.sqrt(math.sin(x))
    print(y)

if task_num == 12:
    a = float(input())
    b = float(input())
    x = float(input())
    y = math.sqrt(a-a*x)/(x*x-math.sqrt(b))
    print(y)

if task_num == 13:
    c = float(input())
    x = float(input())
    if -4 <= x <= 5:
        y = math.sin(c*x)
    elif x > 7:
        y = math.cos(c*x-11)
    else:
        y = 1/x
    print(y)

if task_num == 14:
    b = float(input())
    c = float(input())
    x = float(input())
    if -8 <= x <= 1:
        y = math.sin(c*x)
    elif 6 <= x <= 9 and c != 0:
        y = math.cos(c*x-11)
    else:
        y = 1/(b*x+5)
    print(y)

if task_num == 15:
    c = input()

    if c == 'С':
        c = 0
    if c == 'З':
        c = 1
    if c == 'Ю':
        c = 2
    if c == 'В':
        c = 3

    if c == 'с':
        c = 0
    if c == 'з':
        c = 1
    if c == 'ю':
        c = 2
    if c == 'в':
        c = 3

    if c == 'C':
        c = 0
    if c == 'P':
        c = 1
    if c == '>':
        c = 2
    if c == 'D':
        c = 3

    if c == 'c':
        c = 0
    if c == 'p':
        c = 1
    if c == '.':
        c = 2
    if c == 'd':
        c = 3

    n1 = int(input())
    n2 = int(input())
    c = c+n1+n2
    c %= 4
    if c == 0:
        c = 'С'
    if c == 1:
        c = 'З'
    if c == 2:
        c = 'Ю'
    if c == 3:
        c = 'В'
    print(c)

if task_num == 16:
    h = int(input())
    m = int(input())
    t = h*60+m
    t *= 22
    t %= 24*60
    t -= 12*60
    if t<0:
        t=-t
    t = 12*60-t
    t /= 4
    print(t)

if task_num == 17:
    k = int(input())
    print(((k-1)//2+10)//10**(k % 2) % 10)

if task_num == 18:
    x_0 = float(input())
    y_0 = float(input())
    x_1 = float(input())
    y_1 = float(input())
    x_2 = float(input())
    y_2 = float(input())
    x_3 = float(input())
    y_3 = float(input())
    dx_0 = x_0-x_3
    dy_0 = y_0-y_3
    dx_1 = x_1-x_0
    dy_1 = y_1-y_0
    dx_2 = x_2-x_1
    dy_2 = y_2-y_1
    dx_3 = x_3-x_2
    dy_3 = y_3-y_2
    if dx_0*dy_1-dy_0*dx_1 <= 0 and dx_1*dy_2-dy_1*dx_2 <= 0 and dx_2*dy_3-dy_2*dx_3 <= 0 and dx_3*dy_0-dy_3*dx_0 <= 0:
        a1 = 1
    else:
        a1 = 0
    if dx_0*dy_1-dy_0*dx_1 >= 0 and dx_1*dy_2-dy_1*dx_2 >= 0 and dx_2*dy_3-dy_2*dx_3 >= 0 and dx_3*dy_0-dy_3*dx_0 >= 0:
        a2 = 1
    else:
        a2 = 0
    if dx_0*dx_1+dy_0*dy_1 == 0 and dx_1*dx_2+dy_1*dy_2 == 0 and dx_2*dx_3+dy_2*dy_3 == 0 and dx_3*dx_0+dy_3*dy_0 == 0:
        a3 = 1
    else:
        a3 = 0
    if dx_0*dy_2-dy_0*dx_2 == 0 and dx_1*dy_3-dy_1*dx_3 == 0 and dx_2*dy_0-dy_2*dx_0 == 0 and dx_3*dy_1-dy_3*dx_1 == 0:
        a4 = 1
    else:
        a4 = 0
    a5 = 0
    if dx_0*dy_2-dy_0*dx_2 == 0:
        a5 += 1
    if dx_1*dy_3-dy_1*dx_3 == 0:
        a5 += 1
    if dx_2*dy_0-dy_2*dx_0 == 0:
        a5 += 1
    if dx_3*dy_1-dy_3*dx_1 == 0:
        a5 += 1
    if a1 or a2:
        print('выпуклый')
        if a3:
            print('прямоугольник')
        elif a4:
            print('параллелограмм')
        elif a5 == 2:
            print('трапеция')
        else:
            print('произвольный')
    else:
        print('невыпуклый')

if task_num == 19:
    bx1 = float(input())
    by1 = float(input())
    lx1 = float(input())
    ly1 = float(input())
    ex1 = bx1+lx1
    ey1 = by1+ly1
    bx2 = float(input())
    by2 = float(input())
    lx2 = float(input())
    ly2 = float(input())
    ex2 = bx2+lx2
    ey2 = by2+ly2
    if bx1 > bx2:
        bx = bx1
    else:
        bx = bx2
    if by1 > by2:
        by = by1
    else:
        by = by2
    if ex1 < ex2:
        ex = ex1
    else:
        ex = ex2
    if ey1 < ey2:
        ey = ey1
    else:
        ey = ey2
    print(bx, by, ex, ey)

if task_num == 20:
    bx1 = float(input())
    by1 = float(input())
    lx1 = float(input())
    ly1 = float(input())
    ex1 = bx1+lx1
    ey1 = by1+ly1
    bx2 = float(input())
    by2 = float(input())
    lx2 = float(input())
    ly2 = float(input())
    ex2 = bx2+lx2
    ey2 = by2+ly2
    if bx1 < bx2:
        bx = bx1
    else:
        bx = bx2
    if by1 < by2:
        by = by1
    else:
        by = by2
    if ex1 > ex2:
        ex = ex1
    else:
        ex = ex2
    if ey1 > ey2:
        ey = ey1
    else:
        ey = ey2
    print(bx, by, ex, ey)

if task_num == 21:
    d = int(input())
    m = int(input())
    g = int(input())
    m -= 2
    if m < 1:
        m += 12
        g -= 1
    y = g % 100
    x = g//100
    w = (26*m-2)//10+d+y+y//4+x//4-2*x
    if w % 7 == 0:
        print('воскресенье',)
    if w % 7 == 1:
        print('понедельник',)
    if w % 7 == 2:
        print('вторник',)
    if w % 7 == 3:
        print('среда',)
    if w % 7 == 4:
        print('четверг',)
    if w % 7 == 5:
        print('пятница',)
    if w % 7 == 6:
        print('суббота',)
