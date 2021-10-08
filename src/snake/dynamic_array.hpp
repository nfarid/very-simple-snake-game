
#ifndef CONTAINER_DYNAMIC_ARRAY_HPP_34
#define CONTAINER_DYNAMIC_ARRAY_HPP_34

#include <new>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <initializer_list>

#ifndef NDEBUG
	#include <iostream>
#endif // NDEBUG


namespace Container
{

using std::size_t;
using std::ptrdiff_t;

// A contiguous Front & Back Insertion Container (halfway done)
//Probably full of bugs and memory leaks, but oh well
template <typename T>
class DynamicArray
{
public:
	void pop_back()
	{
		(*--endArrayM).~T();
	}

	void push_forward(const T& elem)
	{
		if( beginArrayM == beginCapacityM ) //if there's no space left in the beginning
		{
			auto temp = elem;	//assuming that T is copy constructible

			if( endArrayM == endCapacityM ) //if there's no space left in the end either
				reserve( capacity() + 1 );
			else
				move_back();
			*--beginArrayM = temp;
		}
		else
			*--beginArrayM = elem;
	}



	void reserve(size_t n)
	{
		if( n <= size() )
			return;

        size_t oldCapacity = this->capacity();
        size_t oldSize = size();

		size_t cap = 1;
		for(size_t m = n; m; m>>=1, cap<<=1); //capacity a power of 2 (at least bigger than n)


		T* tempBeginCapacity = beginCapacityM;
		T* tempBeginArray = beginArrayM;

		beginCapacityM = static_cast<T*>( ::operator new[](cap * sizeof(T) )   );
		//std::cout<<"Capcity change: "<<oldCapacity<<" to "<<cap<<'\n';
		beginArrayM = beginCapacityM + (cap - oldCapacity );
		assert( beginArrayM > beginCapacityM );


		std::uninitialized_copy_n(std::make_move_iterator(tempBeginArray),oldSize,beginArrayM);

		endArrayM = beginArrayM + oldSize;
		endCapacityM = beginCapacityM + cap;

		::operator delete[](tempBeginCapacity);
	}

	inline T& front() {
		return *beginArrayM;
	}

	inline const T& front() const {
		return *beginArrayM;
	}

	inline T& back() {
		return *(endArrayM - 1);
	}

	inline const T& back() const {
		return *(endArrayM - 1);
	}

	DynamicArray(const std::initializer_list<T>& lst)
	{
		size_t n = lst.size();
		size_t cap= 1;
		for(size_t m = n; m; m>>=1, cap<<=1); //capacity a power of 2 (at least bigger than n)

		beginCapacityM = static_cast<T*>( ::operator new[](cap * sizeof(T) )   );
		endCapacityM = beginCapacityM + cap;
		endArrayM = endCapacityM;
		beginArrayM = endArrayM - n;

		assert( beginCapacityM <= beginArrayM );
		assert( beginArrayM <= endArrayM );
		assert( endArrayM <= endCapacityM );

		std::uninitialized_copy( lst.begin(), lst.end(), beginArrayM );
	}

	template <typename... Args>
	DynamicArray(size_t n, Args&&... args)
	{
		size_t cap = 1;
		for(size_t m = n; m; m>>=1, cap<<=1); //capacity a power of 2 (at least bigger than n)

		beginCapacityM = static_cast<T*>( ::operator new[](cap * sizeof(T) )   );
		endCapacityM = beginCapacityM + cap;
		endArrayM = endCapacityM;
		beginArrayM = endArrayM - n;

		assert( beginCapacityM <= beginArrayM );
		assert( beginArrayM <= endArrayM );
		assert( endArrayM <= endCapacityM );

		T val{ std::forward<Args>(args)... };
		std::uninitialized_fill( beginArrayM, endArrayM, val);
	}

	~DynamicArray()
	{
		const size_t s = size();
		for(size_t i=0; i<s; ++i)
			beginArrayM[i].~T();

		::operator delete[](beginCapacityM);
		nulls();
	}

	DynamicArray( const DynamicArray& rhs )
	{
		beginCapacityM = static_cast<T*>( ::operator new[](rhs.capacity() * sizeof(T) )   );
		endCapacityM = beginCapacityM + rhs.capacity();
		endArrayM = endCapacityM;
		beginArrayM = endArrayM - rhs.size();

		assert( beginCapacityM <= beginArrayM );
		assert( beginArrayM <= endArrayM );
		assert( endArrayM <= endCapacityM );

		std::uninitialized_copy( rhs.beginArrayM, rhs.endArrayM, beginArrayM );
	}

	DynamicArray( DynamicArray&& rhs )
	{
		std::memmove( this, &rhs, sizeof(rhs) );
		rhs.nulls();

		assert( beginCapacityM <= beginArrayM );
		assert( beginArrayM <= endArrayM );
		assert( endArrayM <= endCapacityM );
	}

	DynamicArray& operator=(DynamicArray rhs)
	{
		std::memmove( this, &rhs, sizeof(rhs) );
		rhs.nulls();
		assert( beginCapacityM <= beginArrayM );
		assert( beginArrayM <= endArrayM );
		assert( endArrayM <= endCapacityM );
		return *this;
	}

	inline const T& operator[](size_t i) const {
		return beginArrayM[i];
	}

	inline T& operator[](size_t i) {

		return beginArrayM[i];
	}

	inline const T& at(size_t i) const
	{
		if( i >= size() )
			throw std::out_of_range("DynamicArray.at() exception: tried to access outside of range.\n");
		return beginArrayM[i];
	}

	inline T& at(size_t i)
	{
		if( i >= size() )
			throw std::out_of_range("DynamicArray.at() exception: tried to access outside of range.\n");
		return beginArrayM[i];
	}

	inline T* begin() {
		return beginArrayM;
	}

	inline const T* begin() const {
		return beginArrayM;
	}

	inline T* end() {
		return endArrayM;
	}

	inline const T* end() const{
		return endArrayM;
	}

	inline size_t size() const{
		return endArrayM - beginArrayM;
	}

	inline size_t capacity() const {
		return endCapacityM - beginCapacityM;
	}

private:
	T* beginArrayM;
	T* endArrayM;
	T* beginCapacityM;
	T* endCapacityM;

	inline void nulls()
	{
		beginArrayM = nullptr;
		endArrayM = nullptr;
		beginCapacityM = nullptr;
		endCapacityM = nullptr;
	}

	void move_back()
	{
		auto oldSize = size();
        beginArrayM = std::move_backward(beginArrayM,endArrayM,endCapacityM);
        endArrayM = beginArrayM + oldSize;

        assert(endArrayM == endCapacityM );
        assert( beginArrayM <= endArrayM );
        assert( oldSize == size() );
        assert( beginArrayM == beginCapacityM + capacity() - size() );
	}
};

} //end of namespace Container

#endif //CONTAINER_DYNAMIC_ARRAY_HPP_34
