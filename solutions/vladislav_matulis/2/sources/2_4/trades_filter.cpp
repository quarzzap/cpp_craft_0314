#include "market_message.h"

namespace consts
{
	const boost::uint32_t MIN = 1, MAX = 4, TIMEDEF = 2;
}

inline bool check( const boost::uint32_t type )
{
	return  type <= consts::MAX && type >= consts::MIN;
}

int main()
{
	std::ifstream in( BINARY_DIR "/input.txt", std::ios::binary );
	std::ofstream out( BINARY_DIR "/output.txt", std::ios::binary );
	if ( !in.is_open() || !out.is_open() )
		return 1;
	boost::uint32_t curTime = 0;
	while ( !in.eof() )
	{
		binary_reader::market_message msg( in );
		if ( in.eof() )
			break;
		curTime = ( msg.time() > curTime ) ? msg.time() : curTime;
		if ( check( msg.type() ) && ( msg.time() + consts::TIMEDEF > curTime ) )
		{
			msg.write( out );
		}
	}
	in.close();
	out.close();
	return 0;
}

