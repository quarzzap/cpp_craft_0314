#include "market_message.h"
#include <string>
#include <iostream>
#include <boost\thread.hpp>

namespace consts
{
	const boost::uint32_t MIN = 1, MAX = 4, TIMEDEF = 2;
	const char inBegin[] = "/input_";
	const char outBegin[] = "/output_";
	const char nameEnd[] = ".txt";
}

inline bool check( const boost::uint32_t type )
{
	return  type <= consts::MAX && type >= consts::MIN;
}

std::string makeNameIn( int i )
{
	char number[4] = { 0 };
	sprintf( number, "%03d", i );
	std::string result( consts::inBegin );
	result.append( number );
	result.append( consts::nameEnd );
	return result;
}

std::string makeNameOut( int i )
{
	char number[4] = { 0 };
	sprintf( number, "%03d", i );
	std::string result( consts::outBegin );
	result.append( number );
	result.append( consts::nameEnd );
	return result;
}

class Solution3_4
{
public:
	void process( int i )
	{
		std::ifstream in( ( std::string( BINARY_DIR ) + makeNameIn( i ) ).c_str(), std::ios::binary );
		std::ofstream out( ( std::string( BINARY_DIR ) + makeNameOut( i ) ).c_str(), std::ios::binary );
		if ( !in.is_open() || !out.is_open() )
		{
			return;
		}
		boost::uint32_t curTime = 0;
		while ( !in.eof() )
		{
			binary_reader::market_message msg( in );
			if ( in.eof() )
				break;
			curTime = ( msg.time() > curTime ) ? msg.time() : curTime;
			if ( check( msg.type() ) && msg.time() + consts::TIMEDEF <= curTime )
				msg.write( out );
		}
		in.close();
		out.close();
	}
};

int main()
{
	boost::thread_group threads;
	Solution3_4 a;
	for ( int i = 1; i < 1000; ++i )
		threads.create_thread( boost::bind( &Solution3_4::process, &a, i ) );
	threads.join_all();
}