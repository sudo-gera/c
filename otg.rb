a=5.times.to_a
a.map!{|x|;x*2}
a.keep_if{|x|;x%4==0}
puts a
