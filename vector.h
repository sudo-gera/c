#pragma once
#include <stdexcept>
#include <iterator>
#include <optional>
#include <bits/stdc++.h>

template <typename T>
class Vector{
private:
	size_t size=0;
	size_t capacity=0;
	T* data=nullptr;
	void memresize(size_t len){
		assert(size<=capacity);
		if (len and len!=capacity){
			auto tmp=static_cast<T*>(
				len
					?
				operator new(sizeof(T)*len)
					:
				nullptr
			);
			for (size_t w=0;w<size;++w){
				new(tmp+w)T(std::move(data[w]));
			}
			operator delete(data);
			data=tmp;
		}
		capacity=len;
		assert(size<=capacity);
	}
public:
	size_t Size()const{
		return size;
	}
	size_t Capacity()const{
		return size;
	}
	const T* Data()const{
		return data;
	}
	bool empty()const{
		return size==0;
	}
	T& operator[](size_t n){
		return data[n];
	}
	const T& operator[](size_t n)const{
		return data[n];
	}
	T& At(size_t n){
		if (n>=size){
			throw std::out_of_range("IndexError: list index out of range");
		}
		return data[n];
	}
	const T& At(size_t n)const{
		if (n>=size){
			throw std::out_of_range("IndexError: list index out of range");
		}
		return data[n];
	}
	T& front(){
		return data[0];
	}
	const T& front()const{
		return data[0];
	}
	T& back(){
		return data[size-1];
	}
	const T& back()const{
		return data[size-1];
	}
	Vector(){

	}
	template<typename...Y>
	void Resize(size_t len,const Y&...val){
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
				new(data+w)T(val...);
			}
		}
		size=len;
		assert(size<=capacity);
	}
	Vector(size_t len){
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
		delete[] data;
		std::memset(this,0,sizeof(o));
		Vector t(o.begin(),o.end());
		*this=std::move(t);
	}
	auto&operator=(Vector&&o)noexcept{
		delete[] data;
		std::memset(this,0,sizeof(o));
		Swap(o);
		return *this;
	}
	~Vector(){
		delete[] data;
	}
	void Reserve(size_t len){
		memresize(std::max(capacity,len));
	}
	void ShrinkToFit(size_t len){
		if (size>len){
			Resize(len);
		}
		memresize(len);
	}
	void Clear(){
		Resize(0);
	}
	void PushBack(const T&w){
		if (capacity==size){
			memresize(2*capacity+1);
		}
		Resize(size+1,w);
	}
	void PushBack(T&&w){
		if (capacity==size){
			memresize(2*capacity+1);
		}
		Resize(size+1,w);
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
	const T*cbegin(){
		return data;
	}
	const T*cend(){
		return data+size;
	}
	std::reverse_iterator<T*> rbegin(){
		return end();
	}
	std::reverse_iterator<T*> rend(){
		return begin();
	}
	std::reverse_iterator<const T*> crbegin(){
		return cend();
	}
	std::reverse_iterator<const T*> crend(){
		return cbegin();
	}
	using ValueType=T;
	using Pointer=T*;
	using ConstPointer=const T*;
	using Reference=T&;
	using ConstReference=const T&;
	using SizeType=size_t;
	using Iterator=T*;
	using ConstIterator=const T*;
	Vector(std::initializer_list<T> o){
		Vector t(o.begin(),o.end());
		*this=std::move(t);
	}
};

