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
       all[ith][itv][1]=all[ith-1][itv][1]
       szcn[all[ith][itv][1]]+=1
      elif itv + 1 < v:
       #print(*all,ith,itv,sep='\n')
       if all[ith-1][itv+1][0] == '.' and all[ith][itv-1][0] == '.':
        if all[ith-1][itv+1][1] == all[ith][itv-1][1]:
         all[ith][itv][1]=all[ith][itv-1][1]
         szcn[all[ith][itv][1]]+=1
        else:
         #print(11111,ith,itv,*all,sep='\n')
         all[ith][itv][1]=all[ith][itv-1][1]
         szcn[all[ith][itv][1]]+=1+szcn[all[ith-1][itv+1][1]]
         #print(szcn)
         szcn[all[ith-1][itv+1][1]]=0
         frm=all[ith-1][itv+1][1]
         to=all[ith][itv-1][1]
         for w in range(itv):
          if all[ith][w][1] == frm:
           all[ith][w][1] = to
         for w in range(itv,v):
          if all[ith-1][w][1] == frm:
           all[ith-1][w][1] = to
       elif all[ith-1][itv+1][0] == '.':
        all[ith][itv][1]=all[ith-1][itv+1][1]
        szcn[all[ith][itv][1]]+=1
       elif all[ith][itv-1][0] == '.':
        all[ith][itv][1]=all[ith][itv-1][1]
        szcn[all[ith][itv][1]]+=1
       else:
        all[ith][itv][1]=len(szcn)
        szcn.append(1)
      else:
       #print(11111111,ith,itv,all)
       if all[ith][itv-1][0]=='.':
        all[ith][itv][1]=all[ith][itv-1][1]
        szcn[all[ith][itv][1]]+=1
       else:
        all[ith][itv][1]=len(szcn)
        szcn.append(1)
     else:
      if all[ith-1][itv-1][0] == '.':
       all[ith][itv][1]=all[ith-1][itv-1][1]
       szcn[all[ith][itv][1]]+=1
      else:
       if all[ith-1][itv][0] == '.' and all[ith][itv-1][0] == '.':
        if all[ith-1][itv][1] == all[ith][itv-1][1]:
         all[ith][itv][1]=all[ith][itv-1][1]
         szcn[all[ith][itv][1]]+=1
        else:
         #print(*all,11111,ith,itv,sep='\n')
         all[ith][itv][1]=all[ith][itv-1][1]
         szcn[all[ith][itv][1]]+=1+szcn[all[ith-1][itv][1]]
         #print(szcn)
         szcn[all[ith-1][itv][1]]=0
         frm=all[ith-1][itv-1+1][1]
         to=all[ith][itv-1][1]
         for w in range(itv):
          if all[ith][w][1] == frm:
           all[ith][w][1] = to
         for w in range(itv-1,v):
          if all[ith-1][w][1] == frm:
           all[ith-1][w][1] = to
         #print(*all,11111,ith,itv,sep='\n')
       elif all[ith-1][itv][0] == '.':
        all[ith][itv][1]=all[ith-1][itv][1]
        szcn[all[ith][itv][1]]+=1
       elif all[ith][itv-1][0] == '.':
        all[ith][itv][1]=all[ith][itv-1][1]
        szcn[all[ith][itv][1]]+=1
       else:
        all[ith][itv][1]=len(szcn)
        szcn.append(1)
    else:
     if ith % 2:
      if all[ith-1][itv][0] == '.':
       all[ith][itv][1]=all[ith-1][itv][1]
       szcn[all[ith][itv][1]]+=1
      else:
       if itv +1 < v and all[ith-1][itv+1][0] == '.':
        all[ith][itv][1]=all[ith-1][itv+1][1]
        szcn[all[ith][itv][1]]+=1
       else:
        all[ith][itv][1]=len(szcn)
        szcn.append(1)
     else:
      if all[ith-1][itv][0] == '.':
       all[ith][itv][1]=all[ith-1][itv][1]
       szcn[all[ith][itv][1]]+=1
      else:
       all[ith][itv][1]=len(szcn)
       szcn.append(1)
   else:
    if itv:
     if all[ith][itv-1][0] == '.':
      all[ith][itv][1]=all[ith][itv-1][1]
      szcn[all[ith][itv][1]]+=1
     else:
      all[ith][itv][1]=len(szcn)
      szcn.append(1)
    else:
     szcn.append(1)
     all[ith][itv][1]=0
szcn=[w for w in szcn if w != 0]
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
