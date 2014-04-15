#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>
#include <algorithm>

namespace task5_5
{
	template< typename T >
	class vector
	{
	public:
		typedef T* iterator ; // you could change this
		typedef const T* const_iterator; // you could change this
	public:
		explicit vector();
		vector( const vector& copy );
		vector& operator=( const vector& copy_from );

		~vector();

		void push_back( const T& value );
		void insert( const size_t index, const T& value );

		T& operator[]( const size_t index );
		const T& operator[]( const size_t index ) const;

		void resize( const size_t amount );
		void reserve( const size_t amount );

		size_t size() const;
		size_t capacity() const;
		bool empty() const;

		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;

	private:
		static const size_t factor = 2,
			unitSize = sizeof( T ),
			initialSize = 4;
		T* array_;
		size_t size_,
			capacity_;
	};

	// TODO, please realise the rest methods according to the tests

	template< typename T >
	vector< T >::vector()
		: array_( new T [ initialSize ] )
		, size_( 0 )
		, capacity_( initialSize )
	{
	}

	template< typename T >
	vector< T >::vector( const vector< T >& image )
		: array_( new T [ image.size_ ] )
		, size_( image.size_ )
		, capacity_( image.capacity_)
	{
		std::copy( image.begin(), image.end(), array_ );
	}

	template< typename T >
	vector< T >& vector< T >::operator=( const vector< T >& image )
	{
		if ( &image != this )
		{
			delete array_;
			size_ = image.size_;
			capacity_ = image.capacity_;
			array_ = new T [ size_ ];
			std::copy( image.begin(), image.end(), array_ );
		}
		return *this;
	}

	template< typename T >
	vector< T >::~vector()
	{
		delete [] array_;
	}

	template< typename T >
	void vector< T >::push_back( const T& val )
	{
		if ( size_ < capacity_ )
		{
			array_[ size_++ ] = val;
		}
		else
		{
			reserve( capacity_ * factor );
			array_[ size_++ ] = val;
		}
	}

	template< typename T >
	void vector< T >::insert( const size_t pos, const T& val )
	{
		if ( pos > size_ )
			throw std::out_of_range( "out_of_range" );
		if ( size_++ == capacity_ )
			reserve( capacity_ * factor );
		for ( size_t i = size_; i > pos; --i )
			array_[ i ] = array_[ i - 1 ];
		array_[ pos ] = val;
	}

	template< typename T >
	T& vector< T >::operator[]( const size_t pos )
	{
		if( pos >= size_ ) 
		{
			throw( std::out_of_range( "out_of_range" ) );
		}		
		return array_[ pos ];
	}

	template< typename T >
	const T& vector< T >::operator[]( const size_t pos ) const
	{
		if( pos >= size ) 
		{
			throw( std::out_of_range( "out_of_range" ) );
		}		
		return storage_[ pos ];
	}

	template< typename T >
	void vector< T >::resize( const size_t newSize )
	{
		T* buf = array_;
		size_t bufSize = std::min( newSize, size_ );
		size_ = newSize;
		capacity_ = std::max( capacity_ , newSize );
		array_ = new T [ capacity_ ];

		std::copy( buf, buf + bufSize, array_ );

		delete [] buf;
		for( size_t i = bufSize; i < size_; i++ )
			array_[ i ] = static_cast< T >( 0 );
	}
	template< typename T >
	void vector< T >::reserve( const size_t newSize )
	{
		if( newSize > capacity_ )
		{
			T* buf = array_;
			capacity_ = newSize;
			array_ = new T [ capacity_ ];
			std::copy( buf, buf + size_, array_ );
			delete [] buf;
		}
	}

	template< typename T >
	size_t vector< T >::size() const
	{
		return size_;
	}
	template< typename T >
	size_t vector< T >::capacity() const
	{
		return capacity_;
	}
	template< typename T >
	bool vector< T >::empty() const
	{
		return !size_;
	}

	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return &array_[ 0 ];
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return &array_[ size_ ];
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return &array_[ 0 ];
	}
	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return &array_[ size_ ];
	}
}

#endif // _TASK5_5_VECTOR_H_

