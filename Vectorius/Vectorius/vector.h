#include <algorithm>
#include <stdexcept>
#include <memory>
#include <iterator>
#include <limits>
#include <iostream>
#include <vector>

#ifndef VECTOR_H
#define VECTOR_H


template<class T>
class Vector {
private:
	size_t sz{};
	size_t max{};
	T *elem;

public:

	//membertypes

	typedef T value_type; //+
	typedef unsigned int size_type; //+
	typedef ptrdiff_t difference_type;//+
	typedef T & reference;//+
	typedef const T & const_reference;//+
	typedef T * pointer;//+
	typedef const T * const_pointer;//+
	typedef T * iterator;//+
	typedef const T * const_iterator;//+
	typedef std::reverse_iterator<iterator> reverse_iterator; // +
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;//+
	typedef iterator InputIt;

	//constructors

	Vector() : sz(0), elem(new T[sz]), max(0) { /*std::cout << "1st c-tor empty" << std::endl;*/ }
	explicit Vector(size_t size) : sz(size), max(size), elem(new T[max]) { std::cout << "2nd c-tor size" << std::endl; }

	Vector(unsigned int d, T reiksme) : sz(d), elem(new T[sz]), max(d)
	{
		std::fill_n(elem, d, reiksme);
		//std::cout << "3nd c-tor fill values" << std::endl;
	}

	Vector(iterator first, iterator last) : sz(last - first), max(sz), elem(new T[sz])
	{
		for (size_t i = 0; i < sz; ++i) {
			elem[i] = *first + i;
		}
		//std::cout << "4nd c-tor iterators" << std::endl;
	}

	Vector(const Vector<T> &v) : sz{ v.sz }, max{ v.max }, elem{ new T[v.sz] }
	{
		for (size_t i = 0; i != sz; i++)
			elem[i] = v.elem[i];
		//std::cout << "5nd c-tor copy" << std::endl;
	}

	Vector(std::initializer_list<T> list) : sz{ static_cast<size_t>(list.size()) }, elem{ new T[list.size()] }
	{
		std::copy(list.begin(), list.end(), elem);
		//std::cout << "6nd c-tor list" << std::endl;
	}

	Vector(Vector&& v1) noexcept : elem{ v1.elem }, sz{ v1.sz }
	{
		v1.elem = nullptr;
		v1.sz = 0;
		//std::cout << "7nd c-tor copy " << std::endl;
	}
	//destructor

	~Vector() { /*std::cout << "d-tor" << std::endl;*/  delete[]elem; }

	//operators
	Vector& operator=(const Vector& v)
	{
		//std::cout << "==1 " << std::endl;
		auto*p = new T[v.max];
		for (int i = 0; i != v.sz; i++) p[i] = v.elem[i];
		delete[]elem;

		elem = p;
		sz = v.sz;

		return *this;
	}
	Vector& operator=(Vector&& v) noexcept
	{
		//std::cout << "==2 " << std::endl;
		auto*p = new T[v.max];
		for (int i = 0; i != v.sz; i++) p[i] = std::move(v.elem[i]);

		delete[]elem;

		elem = p;
		sz = v.sz;

		return *this;
	}
	Vector& operator=(std::initializer_list<T>)
	{
		//std::cout << "==3 " << std::endl;
		if (cpt < nariai.size()) size = nariai.size();
		sz = 0;
		for (auto &item : nariai)
			elem[sz++] = item;
	}

	//assigns
	void assign(size_t size, const T& value)
	{
		//std::cout << "asign 1 " << std::endl;
		clear();
		if (size > max) max = size;
		sz = size;
		elem = new T[sz];
		for (size_t i = 0; i != sz; ++i) {
			elem[i] = value;
		}
	}
	void assign(iterator first, iterator last)
	{
		//std::cout << "asign 2 " << std::endl;
		clear();
		for (auto iterator = first; iterator != last; iterator++) {
			push_back(*iterator);
		}
	}
	void assign(std::initializer_list<T> list)
	{
		//std::cout << "asign 3 " << std::endl;
		clear();
		sz = static_cast<size_t>(list.size());
		max = sz;
		elem = new T[sz];
		std::copy(list.begin(), list.end(), elem);
	}

	//element access

	reference at(size_type pos)
	{
		//std::cout << "at " << std::endl;
		if (pos >= sz)
		{
			throw std::out_of_range("Position is out of range");
		}
		return elem[pos];
	}
	const_reference at(size_type pos) const
	{
		//std::cout << "at const " << std::endl;
		if (pos >= sz)
		{
			throw std::out_of_range("Position is out of range");
		}
		return elem[pos];
	}

	reference operator[](size_type i)
	{
		//std::cout << "[] " << std::endl;
		return elem[i];
	}
	const_reference operator[](size_type i) const
	{
		//std::cout << "[] const " << std::endl;
		return elem[i];
	}

	reference front()
	{
		return elem[0];
	}
	const_reference front() const
	{
		return elem[0];
	}

	reference back()
	{
		return elem[sz - 1];
	}
	const_reference back()const
	{
		return elem[sz - 1];
	}

	//iterator need to fix it

	iterator begin() noexcept { return elem; }
	const_iterator cbegin()const noexcept { return elem; }

	reverse_iterator rbegin() noexcept { return reverse_iterator(elem + sz); }
	reverse_iterator rcbegin() const noexcept { return reverse_iterator(elem + sz); }

	iterator end() noexcept { return elem + sz; }
	const_iterator cend() noexcept { return elem + sz; }

	reverse_iterator rend() noexcept { return reverse_iterator(elem); }
	reverse_iterator rcend() const noexcept { return reverse_iterator(elem); }

	iterator data() noexcept { return elem; }
	const_iterator data() const noexcept { return elem; }

	//capacity

	bool empty() { if (sz == 0) return true; }
	size_t size() { return sz; }
	size_t max_size() const noexcept
	{
		return size_type(-1);
	}
	void reserve(size_t request)
	{
		//std::cout << "reserve " << std::endl;
		if (request > max) {
			T *newelem = new T[request];
			for (size_t i = 0; i < sz; i++)
			{
				newelem[i] = elem[i];
			}
			max = request;
			delete[] elem;
			elem = newelem;
		}
	}
	size_t capacity() { return max; }
	void shrink_to_fit() { max = sz; }

	// modifiers

	void clear() {
		//std::cout << "clear " << std::endl;
		if (sz < 2)
		{
			delete elem;
		}
		else delete[] elem;
		T* newelem = new T[0];
		max = 0;
		sz = 0;
		elem = newelem;
	}


	//5 inserts:


	//push_backs

	void push_back(const T &value) {
		//std::cout << "push_back 1 " << std::endl;
		if (max == 0)
		{

			sz = 1;
			max = 1;
			auto elem = new T[2];
			elem[0] = value;

		}

		if (sz + 1 >= max)
		{
			max *= 2;
			auto newelem = new T[max];
			for (unsigned int i = 0; i < sz; i++)
			{
				newelem[i] = elem[i];
			}
			delete[] elem;
			elem = newelem;
		}

		elem[sz++] = value;
	}

	void push_back(T &&value) {
		if (max == 0)
		{
			max = 2; sz = 0; T* elem = new T[2];
		}
		else {
			if (sz + 1 >= max)
			{
				max = max * 2;
				T* newelem = new T[max];
				for (size_t i = 0; i < sz; i++)
				{
					newelem[i] = elem[i];
				}
				delete[] elem;
				elem = newelem;
			}
			elem[sz++] = value;
		}
	}

	//pop_back
	void pop_back()
	{
		sz--;
	}

	//swap
	void swap(Vector &other) {
		Vector<T> tmp{ std::move(other) };
		other.elem = std::move(elem);
		other.max = max;
		other.sz = sz;
		elem = std::move(tmp.elem);
		max = tmp.max;
		sz = tmp.sz;
	}

	//erase
	iterator erase(iterator pos) {
		auto newelem = new T[max];
		size_t in = 0;
		for (auto i = begin(); i != pos; ++i)
		{
			newelem[in] = *i;
			in++;
		}
		for (auto j = pos; j != end(); ++j)
		{
			newelem[in] = *(j + 1);
			in++;
		}
		delete[] elem;
		elem = newelem;
		sz--;
		return pos;
	}
	iterator erase(iterator first, iterator last) {
		auto newelem = new T[max];
		auto diff = last - first;
		size_t in = 0;
		for (auto i = begin(); i != first + 1; ++i)
		{
			newelem[in] = *i;
			in++;
		}
		for (auto j = last - 1; j != end(); ++j)
		{
			newelem[in] = *(j + diff);
			in++;
		}
		delete[] elem;
		elem = newelem;
		sz -= diff;
		return last;
	}

	//resize
	void resize(unsigned int newsize) {

		if (max<newsize)  max = newsize;

		auto *  newelem = new T[cpt];
		for (unsigned int i = 0; i != sz; i++)
		{
			newelem[i] = elem[i];
		}
		sz = newsize;

		delete[] elem;
		elem = newelem;

	}

	void resize(unsigned int count, const T& value) {

		if (max < sz + count)
		{
			cpt = count;
		}

		auto * newelem = new T[max];

		for (unsigned int i = 0; i != size(); i++)
		{
			newelem[i] = elem[i];
		}
		for (unsigned int j = sz; j < count; ++j)
		{
			newelem[j] = value;
		}

		sz = count;
		delete[] elem;
		elem = newelem;
	}

	//emplace back
	template< class... Args > void emplace_back(Args&&... args)
	{
		if (sz == cpt) cpt *= 2;
		elem[sz] = std::move(T(std::forward<Args>(args) ...));
		sz++;
	}


};


template<class T>
void swap(Vector<T>&v1, Vector<T>&v2)
{
	Vector<T> tmp{ std::move(v1) };
	v1 = std::move(v2);
	v2 = std::move(tmp);
}

#endif