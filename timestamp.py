from bisect import *
def len_month(y,m):
	return 1-((m-3)//10*m+1)%(5-((y%4-1)//4+(y%100-1)//100+(y%400-1)//400)%2)+31-(m-3)%5%2

def to_timestamp(a):
	'''[year,month,day,hour,minute,second]'''
	year,month,day,hour,minute,second=a
	month-=1
	day-=1
	year+=month//12
	month=month%12

	if (year%4==0 and year%100!=0 or year%400==0):
		a=[0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366]
	else:
		a=[0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365]
	day+=a[month]

	day+=year*365
	day+=(year-1)//4
	day-=year//100
	day+=year//400

	day-=719527
	return day*86400+hour*3600+minute*60+second

def from_timestamp(t):
	second=t%60
	t//=60
	minute=t%60
	t//=60
	hour=t%24
	t//=24
	g=t
	t+=719527
	year=t//146097*400
	t%=146097
	year+=t//365
	t=g*86400
	month=1
	day=1
	tm=to_timestamp([year,month,day,0,0,0])
	if tm>t:
		year-=1
	tm=(t-to_timestamp([year,month,day,0,0,0]))//86400
	if (year%4==0 and year%100!=0 or year%400==0):
		a=[0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366]
	else:
		a=[0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365]
	month=bisect_right(a,tm)
	day=tm-a[month-1]+1
	return [year,month,day,hour,minute,second]


if __name__ == '__main__':
	from json import *
	a=loads(open('stdin.txt').read()) 
	a={tuple(loads(w)):a[w] for w in a}
	a={w:a[w] for w in list(a)[:]}
	d=[w for w in enumerate([to_timestamp(list(w)+[0,0,0])==a[w] for w in a]) if w[1]==0]
	assert len(d)==0
	d=[w for w in enumerate([list(w)+[0,0,0]==from_timestamp(a[w]) for w in a]) if w[1]==0]
	assert len(d)==0
