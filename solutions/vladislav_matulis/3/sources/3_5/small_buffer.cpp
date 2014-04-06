#include "market_message.h"
#include <map>
#include <vector>
#include <string>
#include <boost\thread.hpp>

namespace consts
{
	const boost::uint32_t BUFMAX = 2048; 
	const char inBegin[] = "/input_";
	const char nameEnd[] = ".txt";
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

inline boost::uint32_t size( binary_reader::market_message &mess )
{
	return static_cast< boost::uint32_t > ( sizeof( mess.type() ) + sizeof( mess.time() ) + sizeof( *(mess.msg() ) ) + sizeof( strlen( mess.msg() ) + 1 ) );
}

struct typeInfo
{
	boost::uint32_t typeCount;
	boost::uint32_t timeCount;
	std::vector< boost::uint32_t > memory;
	bool was;
	typeInfo( )
		: typeCount( 0 )
		, timeCount( 0 )
		, was( false )
	{
		memory = std::vector< boost::uint32_t > (1000, consts::BUFMAX );
	}
};

typedef std::map< boost::uint32_t, typeInfo > Map;

class Solution3_5
{
	boost::mutex mtx;
public:
	static Map types;
	static boost::uint32_t current;
	static bool firstStep;
	void process( int number )
	{
		std::ifstream in( ( std::string( BINARY_DIR ) + makeNameIn( number ) ).c_str(), std::ios::binary );
		if ( !in.is_open() )
			return;
		while ( !in.eof() )
		{
			binary_reader::market_message buf( in );
			if ( in.eof() )
				break;
			{
				boost::mutex::scoped_lock lock( mtx );
				if ( firstStep )
				{
					current = buf.time();
					firstStep = false;
				}
			}

			{
				boost::mutex::scoped_lock lock ( mtx );
				if ( buf.time() > current )
				{
					for ( Map::iterator i = Solution3_5::types.begin(); i != Solution3_5::types.end(); ++i )
					{
						i->second.was = false;
						i->second.memory[ number ] = consts::BUFMAX;
					}
					current = buf.time();
				}
			}

			if ( size( buf ) <= types[ buf.type() ].memory[ number ] )
			{
				boost::uint32_t btype = buf.type();
				types[ btype ].memory[ number ] -= size( buf );
				{
					boost::mutex::scoped_lock lock ( mtx );
					types[ btype ].typeCount++;
					if ( !(types[ btype ].was) )
					{
						types[ btype ].timeCount++;
						types[ btype ].was = true;
					}
				}
			}
		}
		in.close();
	}
};

boost::uint32_t Solution3_5::current = 0;
bool Solution3_5::firstStep = true;
Map Solution3_5::types;

int main()
{
	Solution3_5 a;
	boost::thread_group threads;
	for ( int i = 0; i < 1000; ++i )
		threads.create_thread( boost::bind( &Solution3_5::process, &a, i ) );
	threads.join_all();
	std::ofstream out( BINARY_DIR "/output.txt", std::ios::binary );
	if ( !out.is_open() )
		return 1;
	for ( Map::iterator i = Solution3_5::types.begin(); i != Solution3_5::types.end(); ++i )
	{
		if ( !out.write( reinterpret_cast< const char * > ( &( i->first ) ), sizeof( i->first ) ) )
			return 1;
		boost::uint32_t aver = i->second.typeCount / i->second.timeCount;
		if ( !out.write( reinterpret_cast< char * > ( &( aver ) ), sizeof( aver ) ) )
			return 1;
	}
	out.close();
	return 0;
}