q,w,e,a,s,d=gets.split.map{|e|e.to_i*0.1}
hs=[q,w+e].min
hp=[w,q+e].min
ps=[e,q+w].min
puts [hs/a+hs/s+hp/a+hp/s,hs/a+ps/s+hp/d,hp/a+ps/s+hs/d].min
