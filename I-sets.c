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
	std::cin>>m>>k;
	std::map<size_t,std::set<size_t>> set_to_int;
	std::map<size_t,std::set<size_t>> int_to_set;
	size_t e,s;
	std::string q;
	for (size_t w=0;w<k;++w){
		std::cin>>q;
		if (q[0]=='+'){
			std::cin>>e>>s;
			set_to_int[s].insert(e);
			int_to_set[e].insert(s);
		}
		else
		if (q[0]=='-'){
			std::cin>>e>>s;
			set_to_int[s].erase(e);
			int_to_set[e].erase(s);
		}
		else
		if (q[0]=='='){
			std::cin>>s;
			for (size_t e:set_to_int[s]){
				int_to_set[e].erase(s);
			}
			set_to_int[s].clear();
		}
		else
		if (q[0]=='?' and q.size()==1){
			std::cin>>s;
			if (set_to_int[s].size()){
				for (auto e:set_to_int[s]){
					std::cout<<e<<' ';
				}
			}else{
				std::cout<<-1<<' ';
			}
			std::cout<<'\n';
		}
		else
		if (q[0]=='?'){
			std::cin>>e;
			if (int_to_set[e].size()){
				for (auto s:int_to_set[e]){
					std::cout<<s<<' ';
				}
			}else{
				std::cout<<-1<<' ';
			}
			std::cout<<'\n';
		}
	}
}
