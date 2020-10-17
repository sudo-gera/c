

t=2
q=gets.to_i
a=q*100**t
g=-t
while a>100**t
a/=100
g+=1
end
a=(a**0.5).to_i*10**g
c=a+10**g
f=a*a
d=c*c
#puts a,f,c,d
e=q
#b=(d-e)*(c-a)-c*(d-f)
#b*=1.0
#b/=f-d
b=c*(a+1)*2.0/(c+a)
puts (b/(b-q**0.5)).abs.to_s.index '.'
puts (b/(b-q**0.5)).abs
puts b,q**0.5
