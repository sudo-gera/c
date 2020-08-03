n,h,v=map(int,input().split())
all=[]
le=lambda e: [e,-1]
for w in range(h):
 all+=[list(map(le,input().split()))]
szcn=[]
for ith in range(h):
 for itv in range(v):
  if all[ith][itv][0] == '.':
   #print(szcn)
   if ith:
    if itv:
     if ith % 2:
      if all[ith-1][itv][0] == '.':
       #print(*all,sep='\n')
       inc=all[ith-1][itv][1]
       if szcn[inc] < 0:
        inc = -2-szcn[inc]
       szcn[inc]+=1
       all[ith][itv][1]=inc
      elif itv + 1 < v:
       #print(*all,ith,itv,sep='\n')
       if all[ith-1][itv+1][0] == '.' and all[ith][itv-1][0] == '.':
        in1 = all[ith-1][itv+1][1]
        if szcn[in1] < 0:
         in1 = -2-szcn[in1]
        in2 = all[ith][itv-1][1]
        if szcn[in2] < 0:
         in2 = -2-szcn[in2]
        if in1 == in2:
         inc=all[ith][itv-1][1]
         if szcn[inc] < 0:
          inc = -2-szcn[inc]
         szcn[inc]+=1
         all[ith][itv][1]=inc
        else:
         #print(11111,ith,itv,*all,sep='\n')
         all[ith][itv][1]=in1
         szcn[in1]+=1+szcn[in2]
         #print(szcn)
         szcn[in2]=-2-in1
       elif all[ith-1][itv+1][0] == '.':
        inc=all[ith-1][itv+1][1]
        if szcn[inc] < 0:
         inc = -2-szcn[inc]
        szcn[inc]+=1
        all[ith][itv][1]=inc
       elif all[ith][itv-1][0] == '.':
        inc=all[ith][itv-1][1]
        if szcn[inc] < 0:
         inc = -2-szcn[inc]
        szcn[inc]+=1
        all[ith][itv][1]=inc
       else:
        all[ith][itv][1]=len(szcn)
        szcn.append(1)
      else:
       #print(11111111,ith,itv,all)
       if all[ith][itv-1][0]=='.':
        inc=all[ith][itv-1][1]
        if szcn[inc] < 0:
         inc = -2-szcn[inc]
        szcn[inc]+=1
        all[ith][itv][1]=inc
       else:
        all[ith][itv][1]=len(szcn)
        szcn.append(1)
     else:
      if all[ith-1][itv-1][0] == '.':
       inc=all[ith-1][itv-1][1]
       if szcn[inc] < 0:
        inc = -2-szcn[inc]
       szcn[inc]+=1
       all[ith][itv][1]=inc
      else:
       if all[ith-1][itv][0] == '.' and all[ith][itv-1][0] == '.':
        in1 = all[ith-1][itv][1]
        if szcn[in1] < 0:
         in1=-2-szcn[in1]
        in2 = all[ith][itv-1][1]
        if szcn[in2] < 0:
         in2=-2-szcn[in2]
        if in1 == in2:
         inc=all[ith][itv-1][1]
         if szcn[inc] < 0:
          inc = -2-szcn[inc]
         szcn[inc]+=1
         all[ith][itv][1]=inc
        else:
         #print(*all,ith,itv,in1,in2,sep='\n')
         szcn[in1]+=1+szcn[in2]
         szcn[in2]=-2-in1
         all[ith][itv][1]=in1
         #print(*all,11111,ith,itv,sep='\n')
       elif all[ith-1][itv][0] == '.':
        inc=all[ith-1][itv][1]
        if szcn[inc] < 0:
         inc = -2-szcn[inc]
        szcn[inc]+=1
        all[ith][itv][1]=inc
       elif all[ith][itv-1][0] == '.':
        inc=all[ith][itv-1][1]
        if szcn[inc] < -1:
         inc = -2-szcn[inc]
        szcn[inc]+=1
        all[ith][itv][1]=inc
       else:
        all[ith][itv][1]=len(szcn)
        szcn.append(1)
    else:
     if ith % 2:
      if all[ith-1][itv][0] == '.':
       inc=all[ith-1][itv][1]
       if szcn[inc] < -1:
        inc = -2-szcn[inc]
       szcn[inc]+=1
       all[ith][itv][1]=inc
      else:
       if itv +1 < v and all[ith-1][itv+1][0] == '.':
        inc=all[ith-1][itv+1][1]
        if szcn[inc] < 0:
         inc = -2-szcn[inc]
        szcn[inc]+=1
        all[ith][itv][1]=inc
       else:
        all[ith][itv][1]=len(szcn)
        szcn.append(1)
     else:
      if all[ith-1][itv][0] == '.':
       inc=all[ith-1][itv][1]
       if szcn[inc] < 0:
        inc = -2-szcn[inc]
       szcn[inc]+=1
       all[ith][itv][1]=inc
      else:
       all[ith][itv][1]=len(szcn)
       szcn.append(1)
   else:
    if itv:
     if all[ith][itv-1][0] == '.':
      inc=all[ith][itv-1][1]
      if szcn[inc] < 0:
       inc = -2-szcn[inc]
      szcn[inc]+=1
      all[ith][itv][1]=inc
     else:
      all[ith][itv][1]=len(szcn)
      szcn.append(1)
    else:
     szcn.append(1)
     all[ith][itv][1]=0

szcn=[w for w in szcn if w > 0]
#print(*all,sep='\n')
szcn.sort()
#print(szcn)
#exit()
s=szcn
s=s[::-1]
x=0
while n > 0:
 x+=1
 n-=s[0]
 s=s[1:]
print(x)
