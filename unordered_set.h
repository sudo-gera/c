#pragma once
#include <stdexcept>
#include <iterator>
#include <optional>
#include <vector>
#include <list>
#include <bits/stdc++.h>

template <typename D,typename Y>
auto FindF(D && t, Y && val){
	using T=std::remove_cv_t<std::remove_reference_t<decltype(val)>>;
	auto & l = t.data[std::hash<T>()(val) % t.data.size()];
	using R=std::pair<decltype(&l),decltype(l.begin())>;
	for(auto w = l.begin(); w != l.end(); ++w) {
		if(*w == val) {
			return R({&l, w});
		}
	}
	return R({&l, l.end()});
}

template <typename KeyT>
struct UnorderedSet {
	using T = KeyT;
	using L = std::list<T>;
	using C = const std::list<T>;
	size_t size = 0;
	std::vector<L> data;
	UnorderedSet() = default;
	UnorderedSet(size_t len):data(len) {}
	template <typename Y, typename = std::enable_if_t<
			std::is_base_of_v <std::forward_iterator_tag,
				typename std::iterator_traits<Y>::iterator_category
			>
		>
	>
	UnorderedSet(Y b,Y e) {
		for(auto w = b; w != e; ++w) {
			Insert(*w);
		}
	}
	size_t Size() const {
		return size;
	}
	bool Empty() const {
		return !size;
	}
	void Clear() {
		data.clear();
	}
	template <typename Y = T>
	bool Find(Y && val) const {
		auto [lp,li] = FindF(*this,std::forward<Y>(val));
		return lp and li != lp->end();
	}
	template<typename Y = T>
	void Insert(Y && val) {
		if (data.empty()) {
			data.resize(1);
		}
		auto [lp,li] = FindF(*this,std::forward<Y>(val));
		if (li == lp->end()) {
			lp->push_back(val);
			size+=1;
			if (size > data.size()) {
				Rehash(data.size() * 2);
			}
		}
	}
	template <typename Y = T>
	void Erase(Y && val) {
		auto [lp, li] = FindF(*this,std::forward<Y>(val));
		auto& l = *lp;
		if(li != l.end()) {
			l.erase(li);
			size -= 1;
		}
	}
	void Rehash(size_t count) {
		if (count != data.size() && count >= size) {
			auto t = UnorderedSet(count);
			for (auto& w:data) {
				for (auto& e:w) {
					t.Insert(e);
				}
			}
			*this = std::move(t);
		}
	}
	void Reserve(size_t count) {
		if (count > data.size()) {
			Rehash(count);
		}
	}
	size_t BucketCount() const {
		return data.size();
	}
	size_t BucketSize(size_t f) const {
		return data[f].size();
	}
	template <typename Y = T>
	size_t Bucket(Y && val) const {
		auto [lp, li] = FindF(*this,std::forward<Y>(val));
		return lp - &data[0];
	}
	double LoadFactor() const {
		return size * 1.0 / data.size();
	}
};
