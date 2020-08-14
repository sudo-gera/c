q=gets.chomp
unless '+-'.include?(q[0])
 q='+'+q end
q=q.gsub("-","0-").gsub("+","0+")
q=q[1..q.size]
q=q.split('0').map{|w| w[0]=='-' ? w[1..w.size].reverse : w[1..w.size]}
c=q.size
while 1 do
 q.reject!{|e| e[0]==e[1]}
 e=q[0]
 w=q.sort.find{|w| e[1]<=w}
 c-=1
 if w and q[0][1]==w[0]
  c=q.size
  q << q[0][0]+w[1]
  q[q.index(w)]=nil
  q[0]=nil
  q=q.compact
 end
 q.rotate!
if c==0 ; break end
end
q=q.join('+')
puts q
