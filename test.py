import math
import prettytable
import random
task=10
if task==1:
    n=int(input())
    s=0
    for i in range(1,2*n):
        s+=i*(i+1)
    print(s)
if task==2:
    a=int(input())
    b=int(input())
    p=prettytable.PrettyTable()
    p.field_names=['x','e^x-sin(x)']
    max_f=math.e**a-math.sin(a)
    min_f=math.e**b-math.sin(b)
    for x in range(a,b+1):
        p.add_row([x,math.e**x-math.sin(x)])
        max_f=max(max_f,p.rows[-1][1])
        min_f=min(min_f,p.rows[-1][1])
    print(p)
    print(min_f,max_f)
if task==3:
    a=0
    b=1
    a1=int(input())
    a2=int(input())
    while a<=a2:
        if a1<=a<=a2:
            print(a)
        b+=a
        a=b-a
if task==4:
    x1=float(input())
    x2=float(input())
    h=float(input())
    y1=float(input())
    y2=float(input())
    g=float(input())
    print(' '*18,end='|')
    y=y1
    while y<=y2:
        print('%18.7f'%y,end=' ')
        y+=g
    y=y1
    print()
    print('='*18,end='=')
    while y<=y2:
        print('='*18,end='=')
        y+=g
    print()
    x=x1
    while x<=x2:
        print('%18.7f'%x,end='|')
        y=y1
        while y<=y2:
            print('%18.7f'%(5*x**2-12*y),end=' ')
            y+=g
        print()
        x+=h
if task==5:
    n=int(input())
    x=float(input())
    m=0
    s=1
    f=1
    y=1
    while m<=n:
        print('|',m,'|','%18.7f'%math.e**x,'|','%18.7f'%s,'|','%18.7f'%abs(math.e**x-s))
        m+=1
        f*=m
        y*=x
        s+=y/f
if task==6:
    x=float(input())
    e=float(input())
    m=0
    s=1
    f=1
    y=1
    p=prettytable.PrettyTable()
    p.field_names=['num','cos(x)','sum','eps']
    p.add_row([m,math.cos(x),s,abs(math.cos(x)-s)])
    while p.rows[-1][-1]>=e:
        m+=1
        f*=2*m
        f*=2*m-1
        y*=x*x
        if m%2:
            s-=y/f
        else:
            s+=y/f
        p.add_row([m,math.cos(x),s,abs(math.cos(x)-s)])
    print(p)
    print(m)
if task==7:
    a=float(input())
    b=float(input())
    c=float(input())
    d=float(input())
    x1=float(input())
    x2=float(input())
    h=float(input())
    x=x1
    p=prettytable.PrettyTable()
    p.field_names=['x','ln(dx+1)^0.5','cmp to ax^2+bx+c']
    while x<=x2:
        if d*x+1>0 and math.log(d*x+1)>=0:
            y=math.log(x*d+1)**0.5
            if y>a*x*x+b*x+c:
                p.add_row([x,y,'above'])
            if y<a*x*x+b*x+c:
                p.add_row([x,y,'below'])
            if y==a*x*x+b*x+c:
                p.add_row([x,y,'equal'])
        else:
            p.add_row([x,'???','???'])
        x+=h
    print(p)
if task==8:
    n=int(input())
    n5=min(n,5)
    c2=0
    for i in range(n5):
        if n5-i<=3-c2:
            a=2
        elif c2>=3:
            a=random.randint(0,1)*2+1
        else:
            a=random.randint(1,3)
        c2+=a==2
        print(a)
    for i in range(5,n):
        a=random.randint(1,3)
        print(a)
if task==9:
    a=float(input())
    b=float(input())
    h=float(input())
    x=a
    while x<=b:
        print('%18.7f'%x,'%18.7f'%(math.sin(2*x)/x**2))
        x+=h
if task==10:
    s=input()
    s=s[-1:]+s[1:-1]+s[:1]
    print(s)
if task==11:
    