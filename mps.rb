

(1..12).map{|k|
 n=0
 (1..k).to_a.select{|w|w%2==1}.permutation.map{|d|
  if n==0
   (1..k).to_a.select{|w|w%2==0}.permutation.map{|s|
    if n==0
     a=d+s
     b=0
     a.size.times{|w|
      if b==0
       w.times{|e|
        if b==0
         e.times{|r|
          if a[e]*2==a[w]+a[r]
           b=1
          end
         }
        end
       }
      end
     }
     if b==0
      a.map{|t|print t,' '}
      puts
      n=1
     end
    end
   }
  end
 }
}

