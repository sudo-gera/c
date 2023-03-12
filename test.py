task_num=12
if task_num == 1:
    x=int(input())
    y=int(input())
    x=x%100
    y=y%100
    x=str(x)
    y=str(y)
    if len(x)==1:
        x='0'+x
    if len(y)==1:
        y='0'+y
    x = x+y
    x=int(x)
    print(x)
if task_num == 2:
    a=int(input())
    b=int(input())
    c=int(input())
    if a<0 and b<0 and c>=0 or a<0 and b>=0 and c<0 or a<0 and b<0 and c>=0:
        print(True)
    else:
        print(False)
if task_num == 3:
    x=float(input())
    y=int(x)
    print(x-y)
if task_num == 4:
    x=float(input())
    y=float(input())
    import math
    print(math.sqrt(x-math.sqrt(y)))
if task_num == 5:
    a=int(input())
    b=int(input())
    c=int(input())
    print((a//c)*(b//c))
    print(a*b-(a//c*c)*(b//c*c))
if task_num == 6:
    x=int(input())
    if x%2 == 0 and 100<=x<=999:
        print(True)
    else:
        print(False)
if task_num == 7:
    x=float(input())
    y=float(input())
    z=float(input())
    max_=x
    min_=x
    if y>max_:
        max_=y
    if y<min_:
        min_=y
    if z>max_:
        max_=z
    if z<min_:
        min_=z
    u=(max_-min_)/min_
    print(u)
if task_num == 8:
    edu = input()
    if len(edu) == '':
        edu='NoInfo'
    print(edu)
if task_num == 9:
    r=float(input())
    import math
    r=int(r*100)
    x=r//100
    y=r%100
    print(x,end=' ')
    if x%10==1 and x%100!=11:
        print('рубль',end=' ')
    elif x%10==2 and x%100!=12:
        print('рубля',end=' ')
    elif x%10==3 and x%100!=13:
        print('рубля',end=' ')
    elif x%10==4 and x%100!=14:
        print('рубля',end=' ')
    else:
        print('рублей',end=' ')
    print(y,end=' ')
    if y%10==1 and y%100!=11:
        print('копейка',end=' ')
    elif y%10==2 and y%100!=12:
        print('копейки',end=' ')
    elif y%10==3 and y%100!=13:
        print('копейки',end=' ')
    elif y%10==4 and y%100!=14:
        print('копейки',end=' ')
    else:
        print('копеек',end=' ')
    print()
if task_num == 10:
    x1=int(input())
    y1=int(input())
    x2=int(input())
    y2=int(input())
    dx=abs(x2-x1)
    dy=abs(y2-y1)
    if dx==0 or dy==0 or dx==dy:
        print(True)
    else:
        print(False)
if task_num == 11:
    x=float(input())
    import math
    if x>-1:
        print(math.log(3*x**2-15))
    else:
        x=math.pi*x/180
        print(math.sqrt(math.sin(x)))
if task_num == 12:
    a=float(input())
    b=float(input())
    x=float(input())
    import math
    print(math.sqrt(a-a*x)/(x*x-math.sqrt(b)))
if task_num == 13:
    c=float(input())
    x=float(input())
    import math
    if -4<=x<=5:
        print(math.sin(c*x))
    elif x>7:
        print(math.cos(c*x-11))
    else:
        print(1/x)
if task_num == 14:
    b=float(input())
    c=float(input())
    x=float(input())
    import math
    if -8<=x<=1:
        print(math.sin(c*x))
    elif 6<=x<=9 and c!=0:
        print(math.cos(c*x-11))
    else:
        print(1/(b*x+5))
    

# if task_num == 15:
#     c='CЗЮВ'.index(input())
#     n1=int(input())
#     n2=int(input())
#     print('CЗЮВ'[(c+n1+n2)%4])




