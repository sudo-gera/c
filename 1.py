import urllib.request
import os
def time(q=''):
    print(str(urllib.request.urlopen('http://kpml.ru/index.php?id=news0').info()).split()[5]+' '+str(q))
################################################################################
def popen():
    z = 1
    try:
        q=urllib.request.urlopen('http://kpml.ru/index.php?id=827',timeout=3600).read()
    except:
        z=0
    if os.path.exists('1.txt'):
        a = open('1.txt','wb')
    else:
        a = open('1.txt','xb')    
    if z:
        a.write(q)
    a.close()   
    a = open ('1.txt','rt',encoding='utf-8')
    s = a.read()
    a.close()
    s = str(s)
    return s
################################################################################
def pread(s):
    s = [w for w in s]
    q = 0
    a = s[:]
    for w in range(len(s)):
        if a[w] == '<':
            q += 1
        if a[w] == '>':
            q -= 1
        s[w] = q
    #time(10)
    a = [a[w] for w in range(len(a)-2) if s[w] <= min(s[w+1:])]
    #time(13)
    a = ''.join(a)
    a = a.split('>')
    a = ' '.join(a)
    a = a.split()
#    a = a[a.index('1-11-х'):]
    a = a[1:]
    try:
        a = a[a.index('1-11-х'):]
    except:
        pass
    try:
        a = a[2:a.index('Распределение')]
    except:
        try:
            a = a[2:a.index('ЗВОНКОВ')-1]
        except:
            pass
    a = '\n'.join(a)
    s = '         '+a+'         '
    s = [s[w] for w in range(6,len(s)-6)if s[w-0:w+6]!='&nbsp;' and s[w-1:w+5]!='&nbsp;' and s[w-2:w+4]!='&nbsp;' and s[w-3:w+3]!='&nbsp;' and s[w-4:w+2]!='&nbsp;' and s[w-5:w+1]!='&nbsp;']
    s = ''.join(s)
    s = [w for w in s.split() if w != '-']
    s = ' '.join(s)
    return s
################################################################################
def plook(s):
    a=''
    s = s.split()
    q = 'Понедельник Вторник Среда Четверг Пятница Суббота Воскресенье'.split()
    for w in range(len(s)):
        if s[w] != '^':
            if s[w] in q:
                a = ' '.join(s[w:w+5])
                s[w+0]='^'
                s[w+1]='^'
                s[w+2]='^'
                s[w+3]='^'
                s[w+4]='^'
            else:
                s[w] = [a,s[w]]
    s = [w for w in s if w != '^']
    q = 'АБВГД'
    for w in range(len(s)):
        if s[w][1] != '^':
            if s[w][1][-1] in q and s[w][1][0:-1] in [str(w) for w in range(12)]:
                a = s[w][1]
                s[w] = '^'
            elif '-е' in s[w][1]:
                a = s[w][1][:s[w][1].index('-е')]
                s[w] = '^'
            else:
                s[w] = [s[w][0],a,s[w][1]]
    s = [w for w in s if w != '^']
    s = [w for w in s if w[2] != 'классы']
    s = [w[0:2] + [' '.join([e[2] for e in s if e[0:2] == w[0:2]])] for w in s]
    s = [' ']+s
    s = [s[w] for w in range(1,len(s)) if s[w] != s[w-1]]
    p = len(s) * 11
    for w in range(p):
        if w < len(s):
            if '-' in s[w][1]:
                    z =[]
                    for e in range(int(s[w][1].split('-')[0]),int(s[w][1].split('-')[1])+1):
                        z.append([s[w][0],str(e),s[w][2]])
                    s = s[:w]+z+s[w+1:]        
    p = len(s)*5
    #print(len(s))
    for w in range(p):
        if w < len(s):
            #print(w)
            if s[w][1] in [str(w) for w in range(12)]:
                z =[]
                for e in q:
                    z.append([s[w][0],s[w][1]+e,s[w][2]])
                s = s[:w]+z+s[w+1:]
    return s
################################################################################
def pfind(s,q):
    return [w for w in s if w[1]==q]
################################################################################
def pwrite(s):
    if len(s)>0:
        s ='\n'.join([' '.join(w) for w in s])
    else:
        s = 'нет изменений'
    return s
################################################################################
def pall(q):
    #time(0)
    s = popen()
    #time(1)
    s = pread(s)
    #time(2)
    s = plook(s)
    #time(3)
    s = pfind(s,q)
    #time(4)
    s = pwrite(s)
    #time(5)
    return s
def rasp(q):
    print('несколько минут...')
    s = pall(q)
    try:
        s = pall(q)
    except:
        s = 'ошибка расписания'
    return s
print(rasp('8А'))
