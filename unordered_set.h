#pragma once
#include <stdexcept>
#include <iterator>
#include <optional>
#include <vector>
#include <list>
#include <bits/stdc++.h>

template<typename KeyT>
struct UnorderedSet{
	using T=KeyT;
	using L=std::list<T>;
	size_t size=0;
	std::vector<L> data;
	UnorderedSet() = default;
	UnorderedSet(size_t len):data(len){}
	template <
		typename Y,typename=std::enable_if_t<
			std::is_base_of_v<
				std::forward_iterator_tag,
				typename std::iterator_traits<Y>::iterator_category
			>
		>
	>
	UnorderedSet(Y b,Y e){
		for(auto w=b;w!=e;++w){
			insert(*w);
		}
	}
	size_t Size()const{
		return size;
	}
	bool Empty()const{
		return size==0;
	}
	void Clear(){
		data.clear();
	}
	template<typename Y=T>
	std::pair<L*,typename L::iterator> FindF(Y&&val){
		L&l=data[std::hash<T>()(val)%data.size()];
		for (auto w=l.begin();w!=l.end();++w){
			if (*w==val){
				return {&l,w};
			}
		}
		return {&l,l.end()};
	}
	template<typename Y=T>
	bool Find(Y&&val){
		auto [lp,li]=FindF(std::forward<T>(val));
		return li and li!=lp->end();
	}
	template<typename Y=T>
	void Insert(Y&&val){
		auto [lp,li]=FindF(std::forward<T>(val));
		auto&l=*lp;
		if (li==l.end()){
			l.push_back(val);
		}
	}
	template<typename Y=T>
	void Erase(Y&&val){
		auto [lp,li]=FindF(std::forward<T>(val));
		auto&l=*lp;
		if (li!=l.end()){
			l.erase(li);
		}
	}
	void Rehash(size_t count){
		if (count!=data.size() and count>=size){
			auto t=UnorderedSet(count);
			for (auto&w:data){
				for (auto&e:w){
					t.Insert(e);
				}
			}
			*this=std::move(t);
		}
	}	
	void Reserve(size_t count){
		if (count>data.size()){
			Rehash(count);
		}
	}
	void BucketCount(){
		return data.size();
	}
	void BucketSize(size_t f){
		return data[f].size();
	}
	template <typename Y=T>
	void Bucket(Y&&val){
		auto [lp,li]=FindF(std::forward<T>(val));
		return lp-&data[0];
	}
};
