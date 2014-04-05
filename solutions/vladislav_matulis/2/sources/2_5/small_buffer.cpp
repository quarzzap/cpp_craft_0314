#include "market_message.h"
#include <map>

namespace consts
{
	const boost::uint32_t BUFMAX = 2048; 
}

inline boost::uint32_t size( binary_reader::market_message &mess )
{
	return static_cast< boost::uint32_t > ( sizeof( mess.type() ) + sizeof( mess.time() ) + sizeof( *(mess.msg() ) ) + sizeof( static_cast< boost::uint32_t > ( strlen( mess.msg() ) + 1 ) ) );
}

struct typeInfo
{
	boost::uint32_t typeCount;
	boost::uint32_t timeCount;
	boost::uint32_t memory;
	bool was;
	typeInfo( boost::uint32_t a = 0 )
		: typeCount( a )
		, timeCount( 0 )
		, memory( consts::BUFMAX )
		, was( false )
	{}
};

typedef std::map< boost::uint32_t, typeInfo > Map;

int main()
{
	std::ifstream in( BINARY_DIR "/input.txt", std::ios::binary );
	std::ofstream out( BINARY_DIR "/output.txt", std::ios::binary );
	if ( !in.is_open() || !out.is_open() )
		return 1;
	Map types;
	boost:: uint32_t current = 0;
	bool firstStep = true;
	while ( !in.eof() )
	{

		binary_reader::market_message buf( in );
		if ( in.eof() )
			break;
		if ( firstStep )
		{
			current = buf.time();
			firstStep = false;
		}
		if ( buf.time() > current )
		{
			for ( Map::iterator i = types.begin(); i != types.end(); ++i )
			{
				i->second.was = false;
				i->second.memory = consts::BUFMAX;
			}
			current = buf.time();
		}
		if ( size( buf ) <= types[ buf.type() ].memory )
		{
			boost::uint32_t bType = buf.type();
			types[ bType ].memory -= size( buf );
			types[ bType ].typeCount++;
			if ( !( types[ bType ].was ) )
			{
				types[ bType ].timeCount++;
				types[ bType ].was = true;
			}
		}
	}
	in.close();
	for ( Map::iterator i = types.begin(); i != types.end(); ++i )
	{
		if ( !out.write( reinterpret_cast< const char * > ( &( i->first ) ), sizeof( i->first ) ) )
			return 1;
		boost::uint32_t aver = i->second.typeCount / i->second.timeCount;
		if ( !out.write( reinterpret_cast< char * > ( &( aver ) ), sizeof( aver ) ) )
			return 1;
	}
	out.close();
}

