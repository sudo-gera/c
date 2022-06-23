// #include "/home/olurin/pony/header.hpp"
#pragma once
#include <stdexcept>
#include <iterator>
#include <optional>
#include <bits/stdc++.h>

template <typename T>
class Vector {
private:
	size_t size = 0;
	size_t capacity = 0;
	T* data = nullptr;
	void memresize(size_t len) {
		assert(size <= capacity);
		if (len and len != capacity) {
			auto tmp = static_cast<T*> (
				len ? operator new(sizeof(T) * len) : nullptr);
			for (size_t w = 0; w < size; ++w){
				new(tmp + w)T(std::move(data[w]));
			}
			operator delete(data);
			data = tmp;
		}
		capacity = len;
		assert(size <= capacity);
		// ic(capacity,&capacity)
	}
public:
	size_t Size() const {
		return size;
	}
	size_t Capacity() const {
		return capacity;
	}
	T* Data() {
		return data;
	}
	const T* Data() const {
		return data;
	}
	bool Empty() const {
		return size==0;
	}
	T& operator[](size_t n) {
		return data[n];
	}
	const T& operator[](size_t n) const {
		return data[n];
	}
	T& At(size_t n) {
		if (n >= size) {
			throw std::out_of_range("IndexError: list index out of range");
		}
		return data[n];
	}
	const T& At(size_t n)const{
		if (n >= size){
			throw std::out_of_range("IndexError: list index out of range");
		}
		return data[n];
	}
	T& Front() {
		return data[0];
	}
	const T& Front() const {
		return data[0];
	}
	T& Back() {
		return data[size - 1];
	}
	const T& Back() const {
		return data[size - 1];
	}
	Vector() {
	}
private:
	template<typename...Y>
	void Resize_f(size_t len,Y&&...val){
		assert(size<=capacity);
		if (len<=size){
			for (size_t w=len;w<size;++w){
				data[w].~T();
			}
		}else{
			if (len>capacity){
				memresize(len);
			}
			for (size_t w=size;w<len;++w){
				new(data+w)T(std::forward<Y>(val)...);
			}
		}
		size=len;
		assert(size<=capacity);
	}
public:
	template<typename Y=T>
	void Resize(size_t len,Y&&val){
		using R=std::remove_reference_t<Y>;
		Resize_f(len,std::forward<R>(val));
	}
	void Resize(size_t len){
		Resize_f(len);
	}
	explicit Vector(size_t len){
		Resize(len);
	}
	Vector(size_t len,const T&val){
		Resize(len,val);
	}
	void Swap(Vector&o){
		std::swap(o.size,size);
		std::swap(o.data,data);
		std::swap(o.capacity,capacity);
	}
	template <
		typename Y,typename=std::enable_if_t<
			std::is_base_of_v<
				std::forward_iterator_tag,
				typename std::iterator_traits<Y>::iterator_category
			>
		>
	>
	Vector(Y b,Y e){
		for(auto w=b;w!=e;++w){
			PushBack(*w);
		}
	}
	Vector(const Vector&o){
		Vector t(o.begin(),o.end());
		*this=std::move(t);
	}
	Vector(Vector&&o)noexcept{
		Swap(o);
	}
	auto&operator=(const Vector&o){
		if (this==&o){
			return *this;
		}
		Resize(0);
		memresize(0);
		std::memset(this,0,sizeof(o));
		Vector t(o.begin(),o.end());
		*this=std::move(t);
		return *this;
	}
	auto&operator=(Vector&&o)noexcept{
		if (this==&o){
			return *this;
		}
		Resize(0);
		memresize(0);
		std::memset(this,0,sizeof(o));
		Swap(o);
		return *this;
	}
	~Vector(){
		Resize(0);
		memresize(0);
	}
	void Reserve(size_t len){
		memresize(std::max(capacity,len));
	}
	void ShrinkToFit(){
		memresize(size);
	}
	void Clear(){
		Resize(0);
	}
	template<typename Y=T>
	void PushBack(Y&&w){
		if (capacity==size){
			memresize(2*capacity+1);
		}
		Resize(size+1,std::forward<Y>(w));
	}
	void PopBack(){
		Resize(size-1);
	}
	T*begin(){
		return data;
	}
	T*end(){
		return data+size;
	}
	const T*begin()const{
		return data;
	}
	const T*end()const{
		return data+size;
	}
	const T*cbegin()const{
		return data;
	}
	const T*cend()const{
		return data+size;
	}
	using rev=std::reverse_iterator<T*>;
	using crev=std::reverse_iterator<const T*>;
	crev rbegin()const{
		return crev(end());
	}
	crev rend()const{
		return crev(begin());
	}
	rev rbegin(){
		return rev(end());
	}
	rev rend(){
		return rev(begin());
	}
	crev crbegin()const{
		return crev(cend());
	}
	crev crend()const{
		return crev(cbegin());
	}
	using ValueType=T;
	using Pointer=T*;
	using ConstPointer=const T*;
	using Reference=T&;
	using ConstReference=const T&;
	using SizeType=size_t;
	using Iterator=T*;
	using ConstIterator=const T*;
	using ReverseIterator=rev;
	using ConstReverseIterator=crev;
	Vector(std::initializer_list<T> o){
		Vector t(o.begin(),o.end());
		*this=std::move(t);
	}
	int cmp(const Vector&o)const{
		size_t minlen=std::min(size,o.size);
		for (size_t w=0;w<minlen;++w){
			if (data[w]<o.data[w]){
				return -1;
			}
			if (o.data[w]<data[w]){
				return 1;
			}
		}
		if (size<o.size){
			return -1;
		}
		if (o.size<size){
			return 1;
		}
		return 0;
	}
};

template<typename T>
bool operator<(const Vector<T>&q,const Vector<T>&e){
	return q.cmp(e)<0;
}

template<typename T>
bool operator>(const Vector<T>&q,const Vector<T>&e){
	return q.cmp(e)>0;
}

template<typename T>
bool operator==(const Vector<T>&q,const Vector<T>&e){
	return q.cmp(e)==0;
}

template<typename T>
bool operator<=(const Vector<T>&q,const Vector<T>&e){
	return q.cmp(e)<=0;
}

template<typename T>
bool operator>=(const Vector<T>&q,const Vector<T>&e){
	return q.cmp(e)>=0;
}

template<typename T>
bool operator!=(const Vector<T>&q,const Vector<T>&e){
	return q.cmp(e)!=0;
}

