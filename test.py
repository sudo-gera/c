from functools import reduce
w=[1,2,3,4,5,6]
w=[reduce(lambda a,s:a[:-1]+[a[-1]+[s]] if a and len(a[-1])<2 else a+[[s]],w,[])]
print(w)