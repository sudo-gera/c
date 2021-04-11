pony_run{
	let ps=vect(int(2));
	for w in range(3,400000) do{
		let isp=1;
		let cp=0;
		while cp<len(ps) and ps[cp]*ps[cp]<=w do{
			if w%ps[cp]==0 do{
				isp=0;
				break;
			}
			++cp;
		}
		if isp do{
			ps.append(w);
		}
	}
	let a=set<int>();
	for w in ps do{
		for e in ps do{
			if w%10==e%10 and w!=e and 264871<=w*e do{
				if w*e <=322989 do{
					a.insert(w*e);
				}else{
					break;
				}
			}
		}
	}
	let f=vect_by_type(int);
	for w in a do{
		f.append(w);
	}
	let rs=int(0);
	for w in f do{
		rs+=w;
	}
	print(rs,int(len(f)));
}