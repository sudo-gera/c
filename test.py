import math

print('выполнеие задания', 1)
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

print('выполнеие задания', 2)
a = int(input())
b = int(input())
c = int(input())
if a < 0 and b < 0 and c >= 0 or a < 0 and b >= 0 and c < 0 or a < 0 and b < 0 and c >= 0:
    print(True)
else:
    print(False)

print('выполнеие задания', 3)
x = float(input())
y = math.floor(x)
print(x-y)

print('выполнеие задания', 4)
x = float(input())
y = float(input())
print(math.sqrt(x-math.sqrt(y)))

print('выполнеие задания', 5)
a = int(input())
b = int(input())
c = int(input())
print((a//c)*(b//c))
print(a*b-(a//c*c)*(b//c*c))

print('выполнеие задания', 6)
x = int(input())
if x % 2 == 0 and 100 <= x <= 999:
    print(True)
else:
    print(False)

print('выполнеие задания', 7)
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

print('выполнеие задания', 8)
edu = input()
if len(edu) == '':
    edu = 'NoInfo'
print(edu)

print('выполнеие задания', 9)
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

print('выполнеие задания', 10)
x1 = int(input())
y1 = int(input())
x2 = int(input())
y2 = int(input())
dx = abs(x2-x1)
dy = abs(y2-y1)
if dx == 0 or dy == 0 or dx == dy:
    print(True)
else:
    print(False)

print('выполнеие задания', 11)
x = float(input())
if x > -1:
    y=math.log(3*x**2-15)
else:
    x = math.pi*x/180
    y=math.sqrt(math.sin(x))
print(y)

print('выполнеие задания', 12)
a = float(input())
b = float(input())
x = float(input())
y=math.sqrt(a-a*x)/(x*x-math.sqrt(b))
print(y)

print('выполнеие задания', 13)
c = float(input())
x = float(input())
if -4 <= x <= 5:
    y=math.sin(c*x)
elif x > 7:
    y=math.cos(c*x-11)
else:
    y=1/x
print(y)

print('выполнеие задания', 14)
b = float(input())
c = float(input())
x = float(input())
if -8 <= x <= 1:
    y=math.sin(c*x)
elif 6 <= x <= 9 and c != 0:
    y=math.cos(c*x-11)
else:
    y=1/(b*x+5)
print(y)

print('выполнеие задания', 15)
c = input()
c = 'СЗЮВсзювCP>Dcp.d'.index(c)
n1 = int(input())
n2 = int(input())
print('СЗЮВ'[(c+n1+n2) % 4])

print('выполнеие задания', 16)
h = int(input())
m = int(input())
t = h*60+m
t *= 22
t %= 24*60
t -= 12*60
t = abs(t)
t = 12*60-t
t /= 4
print(t)

print('выполнеие задания', 17)
k = int(input())
print(((k-1)//2+10)//10**(k % 2) % 10)

print('выполнеие задания', 18)
x1 = float(input())
y1 = float(input())
x2 = float(input())
y2 = float(input())
x3 = float(input())
y3 = float(input())
x4 = float(input())
y4 = float(input())
x = [x1, x2, x3, x4]
y = [y1, y2, y3, y4]
dx = [0, 0, 0, 0]
dy = [0, 0, 0, 0]
for i in range(4):
    dx[i] = x[i]-x[i-1]
    dy[i] = y[i]-y[i-1]
if all([dx[i]*dy[i-3]-dy[i]*dx[i-3] <= 0 for i in range(4)]) or all([dx[i]*dy[i-3]-dy[i]*dx[i-3] >= 0 for i in range(4)]):
    print('выпуклый')
    if all([dx[i]*dx[i-3]+dy[i]*dy[i-3] == 0 for i in range(4)]):
        print('прямоугольник')
    elif all([dx[i]*dy[i-2]-dy[i]*dx[i-2] == 0 for i in range(4)]):
        print('параллелограмм')
    elif [dx[i]*dy[i-2]-dy[i]*dx[i-2] == 0 for i in range(4)].count(True) == 2:
        print('трапеция')
    else:
        print('произвольный')
else:
    print('невыпуклый')

print('выполнеие задания', 19)
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
bx = max(bx1, bx2)
by = max(by1, by2)
ex = min(ex1, ex2)
ey = min(ey1, ey2)
print(bx, by, ex, ey)

print('выполнеие задания', 20)
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
bx = min(bx1, bx2)
by = min(by1, by2)
ex = max(ex1, ex2)
ey = max(ey1, ey2)
print(bx, by, ex, ey)

print('выполнеие задания', 21)
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
print([
    'воскресенье',
    'понедельник',
    'вторник',
    'среда',
    'четверг',
    'пятница',
    'суббота',
][w % 7])
