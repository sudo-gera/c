#include <bits/stdc++.h>
using namespace std;
#define set(q,w)\
 	if (globals[globals.size()-1].find(q) == globals[globals.size()-1].end()){\
		locals[q]=w;\
		globals[globals.size()-1][q]=&(locals[q]);\
	}else{\
		*(globals[globals.size()-1][q])=w;\
	}

#define global(q)\
 	if (globals[globals.size()-1].find(q) == globals[globals.size()-1].end()){\
		locals[q]=0;\
		globals[globals.size()-1][q]=&(locals[q]);\
	}\
	globals[globals.size()-1][q]=globals[0][q];
	
#define nonlocal(q)\
 	if (globals[globals.size()-1].find(q) == globals[globals.size()-1].end()){\
		locals[q]=0;\
		globals[globals.size()-1][q]=&(locals[q]);\
	}\
	globals[globals.size()-1][q]=globals[globals.size()-2][q];
	
#define get(q) (*(globals[globals.size()-1][q]))

#define init()\
	globals.emplace_back();\
	map<int,int> locals;

#define uninit()\
	globals.pop_back();

vector<map<int,int*>> globals;
int main(){
	init()

	set(1,10)
	set(2,20)
	set(3,30)

	{
		init()

		set(1,11)
		set(2,21)
		set(3,31)

		{
			init()

			set(1,12)
			set(2,22)
			set(3,32)

			{
				init()

				nonlocal(3)

				set(1,13)
				set(2,23)
				set(3,33)

				{
					init()

					global(1)
					nonlocal(2)
					nonlocal(3)

					set(1,14)
					set(2,24)
					set(3,34)

					cout<<get(1)<<endl;
					cout<<get(2)<<endl;
					cout<<get(3)<<endl;
					cout<<"--"<<endl;

					uninit()
				}

				cout<<get(1)<<endl;
				cout<<get(2)<<endl;
				cout<<get(3)<<endl;
				cout<<"--"<<endl;

				uninit()
			}

			cout<<get(1)<<endl;
			cout<<get(2)<<endl;
			cout<<get(3)<<endl;
			cout<<"--"<<endl;

			uninit()
		}
		uninit()
	}
	cout<<get(1)<<endl;
	cout<<get(2)<<endl;
	cout<<get(3)<<endl;
	cout<<"--"<<endl;
	uninit()
}