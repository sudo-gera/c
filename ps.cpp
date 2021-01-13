#include <bits/stdc++.h>
#define fast_int
#include "../pony/pony.hpp"
pony_wakeup
def1 (issq,q){
	if q&4 and q&1 or q&2 or q&8 and (q&4 or q&2 or !(q&1)) do{
		return false;
	}
	let s=sqrt(q);
	return s-int(s+0.5)==0;
}
pony_run{
	for a in range(10000) do{
		let sa=a*a;
		for b in range(a) do{
			let sb=b*b;
			if !!(sa%3)==!!(sb%3) do{
				for c in range(b) do{
					let sc=c*c;
					if (sa+sb+sc)%3==0 do{
						let sm=(a*a+b*b+c*c)/3;
						if issq(sm) and issq(2*sm-sa) and issq(2*sm-sb) and issq(2*sm-sc) and issq(sm-sa+sc) and issq(sm-sc+sa) do{
							cout<<a<<' '<<b<<' '<<c<<endl;
						}						
					}
				}				
			}
		}
	}
}