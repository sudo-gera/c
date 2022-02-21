#include <set>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <vector>
#include <iostream>
#include <string>

int main(){
	size_t n,m,k;
	scanf("%zu%zu%zu",&n,&m,&k);
	std::vector<std::set<size_t>> set_to_int(m+1);
	std::map<size_t,std::set<size_t>> int_to_set;
	size_t e,s;
	char q[50];
	for (size_t w=0;w<k;++w){
		scanf("%s",q);
		if (q[0]=='A'){
			scanf("%zu%zu",&e,&s);
			set_to_int[s].insert(e);
			int_to_set[e].insert(s);
		}
		else
		if (q[0]=='D'){
			scanf("%zu%zu",&e,&s);
			set_to_int[s].erase(e);
			int_to_set[e].erase(s);
		}
		else
		if (q[0]=='C'){
			scanf("%zu",&s);
			for (size_t e:set_to_int[s]){
				int_to_set[e].erase(s);
			}
			set_to_int[s].clear();
		}
		else
		if (q[0]=='L' and q[7]==0){
			scanf("%zu",&s);
			if (set_to_int[s].size()){
				for (auto e:set_to_int[s]){
					printf("%zu ",e);
				}
			}else{
				printf("%i ",-1);
			}
			printf("\n");
		}
		else
		if (q[0]=='L'){
			scanf("%zu",&e);
			if (int_to_set[e].size()){
				for (auto s:int_to_set[e]){
					printf("%zu ",s);
				}
			}else{
				printf("%i ",-1);
			}
			printf("\n");
		}
	}
}
