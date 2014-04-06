#include "stock_data.h"
#include <boost\thread.hpp>
#include <string>
#include <map>
#include <deque>

namespace consts
{
	boost::uint32_t threads_count;
}

typedef std::map< std::string, std::deque< binary_reader::stock_data > > Map;

class Solution3_6
{
	std::ifstream in;
	Map heap;
	enum status { IN, OUT, CHANGE, SHOW };
	bool isReading;
	boost::mutex mtx;
public:
	Solution3_6()
		:isReading( false )
	{
		in.open( BINARY_DIR "/input.txt" , std::ios::binary );
	}

	void reading()
	{
		editReading( CHANGE );
		while( !in.eof() )
		{
			binary_reader::stock_data buf( in );
			if ( !in.eof() )
				break;
			crit( IN, "", buf );
		}
		in.close();
		editReading( CHANGE );
	}

	void writing()
	{
		boost::thread_group threads;
		for ( Map::iterator i = heap.begin(); i != heap.end(); ++i )
		{
			threads.create_thread( boost::bind( &Solution3_6::crit, this, OUT, i->first, boost::ref( binary_reader::stock_data( ) ) ) );
		}
		threads.join_all();
	}

	void crit( status st, std::string stn = "", binary_reader::stock_data & datum = binary_reader::stock_data() )
	{
		boost::mutex::scoped_lock lock( mtx );
		if ( st == IN )
		{
			heap[ datum.stock_name() ].push_back( datum );
		}
		else if ( st == OUT )
		{
			std::ofstream out( ( std::string( BINARY_DIR ) + std::string( "/output_" ) + stn + std::string( ".txt" ) ).c_str(), std::ios::binary | std::ios_base::ate );
			while ( !( heap[ stn ].empty() ) )
			{
				binary_reader::write_binary< binary_reader::stock_data >( out, heap[ stn ].front() );
				heap[ stn ].pop_front();
			}
			out.close();
		}
	}

	bool editReading( status stw )
	{
		boost::mutex::scoped_lock lock( mtx );
		if ( stw == SHOW )
			return isReading;
		else if ( stw == CHANGE )
			isReading = ( isReading ) ? false: true;
		return true;
	}

	void process()
	{
		boost::thread readThread( &Solution3_6::reading, this );
		while ( editReading( SHOW ) || !heap.empty() )
		{
			writing();
		}
		readThread.join();
	}
};

int main()
{
	Solution3_6 obj;
	obj.process();
	return 0;
}