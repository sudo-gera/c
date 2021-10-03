x1,y1=[int(w) for w in input().split()]
x2,y2=[int(w) for w in input().split()]
x3,y3=[int(w) for w in input().split()]
x,y=[int(w) for w in input().split()]
if (x1-x)*(y1-y2)-(y1-y)*(x1-x2) >=0 and (x2-x)*(y2-y3)-(y2-y)*(x2-x3) >=0 and (x3-x)*(y3-y1)-(y3-y)*(x3-x1) >=0 or (x1-x)*(y1-y2)-(y1-y)*(x1-x2) <=0 and (x2-x)*(y2-y3)-(y2-y)*(x2-x3) <=0 and (x3-x)*(y3-y1)-(y3-y)*(x3-x1) <=0:
	print('In')
else:
	print('Out')