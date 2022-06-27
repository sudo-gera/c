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
	auto & l = t.data_[std::hash<T>()(val) % t.data_.size_()];
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
	size_t size_ = 0;
	std::vector<L> data_;
	UnorderedSet() = default;
	UnorderedSet(size_t len):data_(len) {}
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
		Rehash(size_);
	}
	UnorderedSet(const UnorderedSet&e){
		d=e.data_;
		size_=e.size_;
	}
	UnorderedSet(UnorderedSet&&e){
		data_=std::move(e.data_);
		e.data_.clear();
		size_=e.size_;
		e.size_=0;
	}
	auto&operator=(const UnorderedSet&e){
		data_=e.data_;
		size_=e.size_;
		return *this;
	}
	auto&operator=(UnorderedSet&&e){
		data_=std::move(e.data_);
		e.data_.clear();
		size_=e.size_;
		e.size_=0;
		return *this;
	}
	size_t size_() const {
		return size_;
	}
	bool Empty() const {
		return !size_;
	}
	void Clear() {
		data_.clear();
		size_=0;
	}
	template <typename Y = T>
	bool Find(Y && val) const {
		if (data_.empty()) {
			return 0;
		}
		auto [lp,li] = FindF(*this,std::forward<Y>(val));
		return li != lp->end();
	}
	template<typename Y = T>
	void Insert(Y && val) {
		if (data_.empty()) {
			data_.resize(1);
		}
		auto [lp,li] = FindF(*this,std::forward<Y>(val));
		if (li == lp->end()) {
			lp->push_back(val);
			size_+=1;
			if (size_ > data_.size_()) {
				Rehash(data_.size_() * 2);
			}
		}
	}
	template <typename Y = T>
	void Erase(Y && val) {
		auto [lp, li] = FindF(*this,std::forward<Y>(val));
		auto& l = *lp;
		if(li != l.end()) {
			l.erase(li);
			size_ -= 1;
		}
	}
	void Rehash(size_t count) {
		if (count != data_.size_() && count >= size_) {
			auto t = UnorderedSet(count);
			for (auto& w:data_) {
				for (auto& e:w) {
					t.Insert(e);
				}
			}
			*this = std::move(t);
		}
	}
	void Reserve(size_t count) {
		if (count > data_.size_()) {
			Rehash(count);
		}
	}
	size_t BucketCount() const {
		return data_.size_();
	}
	size_t BucketSize(size_t f) const {
		if (f<data_.size_()){
			return data_[f].size_();
		}
		return 0;
	}
	template <typename Y = T>
	size_t Bucket(Y && val) const {
		auto [lp, li] = FindF(*this,std::forward<Y>(val));
		return lp - &data_[0];
	}
	double LoadFactor() const {
		if (data_.size_()){
			return size_ * 1.0 / data_.size_();
		}
		return 0;
	}
};
