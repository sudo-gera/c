#include "/Users/gera/pony/pony.hpp"
using namespace std;
type(num) iiii=1;
def0(printnum){
	print("<<<<<<",iiii++,">>>>>>>");
	return 1;
}
pony_run{
	let n=scan(num);
	print("--");
	let a=vector<vector<any>>();
	print("--");
	for w in range(n) do{
		a.append(vector<any>());
		a[len(a)-1].append(scan(str));
		a[len(a)-1].append(scan(str));
		a[len(a)-1].append(scan(num));
		a[len(a)-1].append(scan(num));
		a[len(a)-1].append(w);
	}
	print("--");
	for w in a do{
		for e in w do{
			write(e,' ');
		}
		print();
	}
	a=filter(a,w,num(w[2]));
	print("--");
	sort(a.begin(),a.end(),[](auto a,auto s){return num(a[3])<num(s[3]);});
	print("--");
	if printnum() and  len(a)==0 do{
		print("1");
		print(0);
	}elif printnum() and  len(a)==1 do{
		print("2");
		print((a[-1][0]),(a[-1][1]));
	}elif printnum() and  len(a)==2 and num(a[-1][4])<num(a[-2][4]) do{
		print("3");
		print((a[-1][0]),(a[-1][1]));
		print((a[-2][0]),(a[-2][1]));
	}elif printnum() and  len(a)==2 and num(a[-1][4])>num(a[-2][4]) do{
		print("4");
		print((a[-2][0]),(a[-2][1]));
		print((a[-1][0]),(a[-1][1]));
	}elif printnum() and  num(a[-3][3])==num(a[-2][3]) and printnum() and num(a[-2][3])==num(a[-1][3]) and printnum() do{
		print("5");
		print(len(filter(a,w,num(w[3])==num(a[len(a)-1][3]))));
	}elif printnum() and  num(a[-3][3])==num(a[-2][3])do{
		print("6");
		print((a[-2][0]),(a[-2][1]));
	}elif printnum() and  num(a[-1][3])==num(a[-2][3]) and num(a[-1][4])<num(a[-2][4]) do{
		print("7");
		print((a[-1][0]),(a[-1][1]));
		print((a[-2][0]),(a[-2][1]));
	}elif printnum() and  num(a[-1][3])==num(a[-2][3]) and num(a[-1][4])>num(a[-2][4]) do{
		print("8");
		print((a[-2][0]),(a[-2][1]));
		print((a[-1][0]),(a[-1][1]));
	}else{
		print("9");
		print((a[-1][0]),(a[-1][1]));
		print((a[-2][0]),(a[-2][1]));
	}
	print("--");
}