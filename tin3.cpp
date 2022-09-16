#include <bits/stdc++.h>
using namespace std;

#define bisect(b, e, ...)														\
	({																			\
		int64_t beg = b;														\
		int64_t end = e;														\
		while (beg + 1 < end) {													\
			int64_t cen = (beg + end) / 2;										\
			if (__VA_ARGS__) {													\
				end = cen;														\
			} else {															\
				beg = cen;														\
			}																	\
		}																		\
		int64_t cen = beg;														\
		if (beg != end and (__VA_ARGS__)) {										\
			end = cen;															\
		}																		\
		end;																	\
	})

int main(){
	string s;
	cin>>s;
	long k;
	cin>>k;
	cout<<bisect(0,s.size()+1,
		({
			long c=0;
			for (long w=0;w<cen;++w){
				if (s[w]=='.'){
					c++;
				}
			}
			long min_k=c;
			for (long w=cen;w<s.size();++w){
				if (s[w]=='.'){
					c++;
				}
				if (s[w-cen]=='.'){
					c--;
				}
				if (c<min_k){
					min_k=c;
				}
			}
			min_k>k;
		})
	)-1<<endl;
}
