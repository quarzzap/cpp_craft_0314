#include "solution.h"
#include <algorithm>
#include <iostream>

namespace consts
{
	const size_t thread_count = 4;
}

task4_5::solution::solution( const data_type& data )
	: data_( data )
	, min_( 0 )
	, max_( 0 )
	, size_( data.size() )
	, number( 0 )
{
	boost::thread_group threads;
	for ( size_t i = 0; i < consts::thread_count; ++i )
		threads.create_thread( boost::bind( &solution::process, this ) );
	threads.join_all();
	min_ = ( minArray.empty() )? 0 : *(std::min_element( minArray.begin(), minArray.end() ));
	max_ = ( maxArray.empty() )? 0 : *(std::max_element( maxArray.begin(), maxArray.end() ));
}

const size_t task4_5::solution::getID()
{
	boost::mutex::scoped_lock lock ( mtx );
	return number++;
}

void task4_5::solution::process()
{
	if ( number < size_ )
		peekToThread( getID() );
}

void task4_5::solution::peekToThread( const size_t dNumber )
{
	
	if ( check( dNumber ) ) 
	{
		std::pair< iVec::const_iterator, iVec::const_iterator > pairMinMax = minmax_element( data_[ dNumber ].cbegin(), data_[ dNumber ].cend() );
		{
			boost::mutex::scoped_lock lock( mtx );
			minArray.push_back( *pairMinMax.first );
			maxArray.push_back( *pairMinMax.second );
		}
	}
	process();
}

bool task4_5::solution::check( const size_t a )
{
	boost::mutex::scoped_lock lock( mtx );
	return !( data_[ a ].empty() );
}

int task4_5::solution::get_min() const
{
	return min_;
}
int task4_5::solution::get_max() const
{
	return max_;
}
