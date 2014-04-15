#ifndef _TASK5_6_THREAD_SAFE_QUEUE_H_
#define _TASK5_6_THREAD_SAFE_QUEUE_H_

#include <cstdlib>
#include <boost/thread.hpp>
#include <queue>

namespace task5_6
{
	template< typename T >
	class thread_safe_queue
	{
		mutable boost::mutex mtxPP, mtxEmpty, mtxSize;
		std::queue< T > data_;
	public:
		explicit thread_safe_queue();
		~thread_safe_queue();

		void push( const T& new_element );
		bool pop( T& result );

		bool empty() const;
		size_t size() const;
	};

	template< typename T >
	thread_safe_queue< T >::thread_safe_queue()
	{
	}

	template< typename T >
	thread_safe_queue< T >::~thread_safe_queue()
	{
	}

	template< typename T >
	void thread_safe_queue< T >::push( const T& val )
	{
		boost::mutex::scoped_lock lock( mtxPP );
		data_.push( val );
	}

	template< typename T >
	bool thread_safe_queue< T >::pop( T& val )
	{
		boost::mutex::scoped_lock lock( mtxPP );
		bool res = false;
		if ( !empty() )
		{
			val = data_.front();
			data_.pop();
			res = true;
		}
		return res;
	}

	template< typename T >
	bool thread_safe_queue< T >::empty() const
	{
		boost::mutex::scoped_lock lock( mtxEmpty );
		return data_.empty();
	}

	template< typename T >
	size_t thread_safe_queue< T >::size() const
	{
		boost::mutex::scoped_lock lock( mtxSize );
		return data_.size();
	}

}

#endif // _TASK5_6_THREAD_SAFE_QUEUE_H_
