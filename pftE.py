dx,dy,ax,ay,bx,by=[int(w) for w in input().split()]
adS=(dx-ax)**2+(dy-ay)**2
bdS=(dx-bx)**2+(dy-by)**2
abS=(ax-bx)**2+(ay-by)**2
if abS+bdS<adS:
	print(bdS**0.5)
elif abS+adS<bdS:
	print(adS**0.5)
else:
	print(abs((ax-bx)*(ay-dy)-(ay-by)*(ax-dx))/(abS**0.5))
