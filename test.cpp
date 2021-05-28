#include <bits/stdc++.h>
using namespace std;
#define python_set(q)\
 	if (globals[globals.size()-1].find(q) == globals[globals.size()-1].end()){\
		locals[q]=0;\
		globals[globals.size()-1][q]=&(locals[q]);\
	}else{\
		*(globals[globals.size()-1][q])=0;\
	}*(globals[globals.size()-1][q])

#define python_global(q)\
 	if (globals[globals.size()-1].find(q) == globals[globals.size()-1].end()){\
		locals[q]=0;\
		globals[globals.size()-1][q]=&(locals[q]);\
	}\
	globals[globals.size()-1][q]=globals[0][q];\
	
#define python_nonlocal(q)\
 	if (globals[globals.size()-1].find(q) == globals[globals.size()-1].end()){\
		locals[q]=0;\
		globals[globals.size()-1][q]=&(locals[q]);\
	}\
	globals[globals.size()-1][q]=globals[globals.size()-2][q];
	
#define python_get(q) (*(globals[globals.size()-1][q]))

#define python_create_level()\
	globals.emplace_back();\
	map<int,int> locals;

#define python_delete_level()\
	globals.pop_back();

vector<map<int,int*>> globals;
int main(){
	python_create_level()

	python_set(1)=10;
	python_set(2)=20;
	python_set(3)=30;
	python_set(4)=40;

	{
		python_create_level()

		python_set(1)=11;
		python_set(2)=21;
		python_set(3)=31;
		python_set(4)=41;

		{
			python_create_level()

			python_set(1)=12;
			python_set(2)=22;
			python_set(3)=32;
			python_set(4)=42;

			{
				python_create_level()

				python_nonlocal(3)

				python_set(1)=13;
				python_set(2)=23;
				python_set(3)=33;
				python_set(4)=43;

				{
					python_create_level()

					python_global(1)
					python_nonlocal(2)
					python_nonlocal(3)

					python_set(1)=14;
					python_set(2)=24;
					python_set(3)=34;
					python_set(4)=44;

					cout<<python_get(1)<<endl;
					cout<<python_get(2)<<endl;
					cout<<python_get(3)<<endl;
					cout<<python_get(4)<<endl;
					cout<<"--"<<endl;

					python_delete_level()
				}

				cout<<python_get(1)<<endl;
				cout<<python_get(2)<<endl;
				cout<<python_get(3)<<endl;
				cout<<python_get(4)<<endl;
				cout<<"--"<<endl;

				python_delete_level()
			}
			cout<<python_get(1)<<endl;
			cout<<python_get(2)<<endl;
			cout<<python_get(3)<<endl;
			cout<<python_get(4)<<endl;
			cout<<"--"<<endl;
			python_delete_level()
		}
		cout<<python_get(1)<<endl;
		cout<<python_get(2)<<endl;
		cout<<python_get(3)<<endl;
		cout<<python_get(4)<<endl;
		cout<<"--"<<endl;
		python_delete_level()
	}
	cout<<python_get(1)<<endl;
	cout<<python_get(2)<<endl;
	cout<<python_get(3)<<endl;
	cout<<python_get(4)<<endl;
	cout<<"--"<<endl;
	python_delete_level()
}